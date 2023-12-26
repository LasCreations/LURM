#ifndef USER_CONNECTION_CACHE_H
#define USER_CONNECTION_CACHE_H


#include "../../../database/queries/lib/userConnectionQueries.h"


class USERCONNECTIONCACHE{
    private:
        std::unordered_map<string, CONNECTION*> *cacheConnectionData;

    public:
        USERCONNECTIONCACHE();
        void preloadConnectionData(DATABASEMANAGER *dbMan, USERCACHE *userCacheData);
        CONNECTION* getConnectionFromCache(string user1_ID, string user2_ID);
        bool isConnected(string user1_ID, string user2_ID);
        uint32_t followerCount(string username); //Store unsigned value for memory purposes
        uint32_t followingCount(string username); //Store unsigned value for memory purposes
};


#endif