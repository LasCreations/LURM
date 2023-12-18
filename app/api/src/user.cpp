#include "../lib/user.h"

//first parse to get the cookie
//send the cookie to the database 
//return the data to client

void findUser(char *request, int clientSocket){
    parseCookieToken(parseHttpRequest(request));
    if (getUserData(cookie) != nullptr)
        {

            User *userData = new User(getUserData(cookie));

            std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" +
                                       ParseUserDataToJSON(userData->getUsername(), userData->getPassword(),
                                                           userData->getEmail(), userData->getAvatarURL());
            send(clientSocket, httpResponse.c_str(), httpResponse.length(), 0);
        }else{
            const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
            send(clientSocket, response, sizeof(response) - 1, 0);
        }
}

void parseCookieToken(string JsonString)
{
    // Your JSON string
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::istringstream jsonStream(JsonString);

    try
    {
        // Parse the JSON string
        Json::parseFromStream(readerBuilder, jsonStream, &jsonData, nullptr);

        // Access individual fields
        cookie = jsonData["cookie"].asString();
    }
    catch (const Json::Exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }
}

User *getUserData(string cookie)
{
    User *data = nullptr;
    if (dbConn->createConnection())
    {
        data = dbConn->getUserData(cookie);
    }
    return data;
}

string ParseUserDataToJSON(string username, string password, string email, string avatarurl)
{
    // Create a JSON object
    Json::Value jsonValue;

    // Add key-value pairs to the JSON object
    jsonValue["username"] = username;
    jsonValue["email"] = email;
    jsonValue["password"] = password;
    jsonValue["avatarurl"] = avatarurl;

    // Convert the JSON object to a JSON string
    std::string jsonString = jsonValue.toStyledString();

    // Print the resulting JSON string
    std::cout << "\n\n" << jsonString << std::endl;
    return jsonString;
}