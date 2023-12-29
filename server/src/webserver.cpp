#include "../lib/webserver.h"
char *request;

void *handleClientSideRequests(void *req)
{
    struct Request *reqArgs = (struct Request *)req;
    apiRoute(reqArgs->request, reqArgs->clientSocket, cacheUserData, dbMan, cacheConnectionData, cacheNotificationData);
    free(reqArgs->request);
    close(reqArgs->clientSocket);
    printf("\n");
    return NULL;
}

void *handlePollingRequests(void *req){
    struct Request *reqArgs = (struct Request *)req;
    apiRoute(reqArgs->request, reqArgs->clientSocket, cacheUserData, dbMan, cacheConnectionData, cacheNotificationData);
    // free(reqArgs->request);
    // close(reqArgs->clientSocket);
    printf("\n");
    return NULL;
}

int runServer()
{
    // register signal handler
    signal(SIGINT, handleSignal);

    // server internet socket address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;         // IPv4
    serverAddress.sin_port = htons(PORT);       // port number in network byte order (host-to-network short)
    serverAddress.sin_addr.s_addr = INADDR_ANY; // Bind to any available interface

    // socket of type IPv4 using TCP protocol
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // reuse address and port
    // setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    int option = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int)) < 0)
    {
        perror("Error setting socket options");
        return 1;
    }

    // bind socket to address
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        printf("Error: The server is not bound to the address.\n");
        return 1;
    }

    // listen for connections
    if (listen(serverSocket, BACKLOG) < 0)
    {
        printf("Error: The server is not listening.\n");
        return 1;
    }

    // get server address information
    char hostBuffer[NI_MAXHOST], serviceBuffer[NI_MAXSERV];
    int error = getnameinfo((struct sockaddr *)&serverAddress, sizeof(serverAddress), hostBuffer,
                            sizeof(hostBuffer), serviceBuffer, sizeof(serviceBuffer), 0);

    if (error != 0)
    {
        printf("Error: %s\n", gai_strerror(error));
        return 1;
    }

    printf("\nServer is listening on http://%s:%s/\n\n", hostBuffer, serviceBuffer);
    preloadCacheIntoMemory();
    while (1)
    {
        request = (char *)malloc(SIZE * sizeof(char));
        char method[10], route[100];
        // accept connection and read data
        int clientSocket = accept(serverSocket, NULL, NULL);
        cout << "Accepted new connection. Client socket: " << clientSocket << endl;

        ssize_t bytesRead = read(clientSocket, request, SIZE);
        sscanf(request, "%s %s", method, route);
        printf("%s %s\n", method, route);

        struct Request req;

        req.clientSocket = clientSocket;
        req.request = request;

        if (strcmp(route, "/user/notification") == 0)
        {
            pthread_t pollingThread;
            pthread_create(&pollingThread, NULL, handlePollingRequests, (void *)&req);
            pthread_detach(pollingThread); // LONG POLLING   IMPLEMENT
        }
        else
        {
            pthread_t renderingThread;
            pthread_create(&renderingThread, NULL, handleClientSideRequests, (void *)&req);
            pthread_join(renderingThread, NULL);  //CLient side rendering
        }
    }
}

static void handleSignal(int signal)
{
    if (signal == SIGINT)
    {
        printf("\nShutting down server...\n");
        close(serverSocket);
        exit(0);
    }
}

void preloadCacheIntoMemory()
{
    dbMan = new DATABASEMANAGER(); // create a database connection

    cacheUserData = new USERCACHE();
    cacheConnectionData = new USERCONNECTIONCACHE();
    cacheNotificationData = new NOTIFICATIONCACHE();

    cacheUserData->preloadUserData(dbMan); // preload data into memory from the database
    cacheNotificationData->preloadNotificationData(dbMan);
    cacheConnectionData->preloadConnectionData(dbMan, cacheUserData);
}

int main()
{
    runServer();
    return EXIT_SUCCESS;
}