#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H


#include "../../database/queries/lib/userQueries.h"

#include "../../jsonparsing/lib/jsonParser.h"

#include "../../middleware/cache/lib/userCache.h"
#include "../../middleware/cache/lib/userConnectionCache.h"

void addUser(char* request, int clientSocket, USERCACHE *userCacheData, DATABASEMANAGER *dbMan);

void updateUserProfile(char* request, int clientSocket, USERCACHE *userCacheData, DATABASEMANAGER *dbMan);

bool userExistsInCache(char* request, int clientSocket, USERCACHE *userCacheData);

void checkUserCredentials(char* request, int clientSocket, USERCACHE *userCacheData, DATABASEMANAGER *dbMan);

void userDataDashBoard(char* request, int clientSocket, USERCACHE *userCacheData, USERCONNECTIONCACHE *cacheConnectionData);

void searchUser(char* request, int clientSocket, USERCACHE *userCacheData, USERCONNECTIONCACHE *cacheConnectionData);

bool updateUserToken(USER* user, USERCACHE *userCacheData, DATABASEMANAGER *dbMan);

#endif