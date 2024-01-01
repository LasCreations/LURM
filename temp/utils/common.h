#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>  // console input/output, perror
#include <stdlib.h> // exit
#include <string.h> // string manipulation
#include <netdb.h>  // getnameinfo

#include <arpa/inet.h>  // Include for htonl function
#include <sys/socket.h> // socket APIs
#include <netinet/in.h> // sockaddr_in
#include <unistd.h>     // open, close

#include <signal.h> // signal handling
#include <time.h> 

#include<string>
#include<iostream>
#include<regex>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>

#include <fstream>
#include <cstring>
#include <vector>

#include <stdbool.h>

#include <unordered_map>
#include <ctime>


using namespace std;

#define SIZE 1024


/*!
 * @function    generateRandomCode
 * @abstract    create a code with a given length
 * @param       int    lenght
 * @result      returns a string
*/
string generateRandomCode(int length);

/*!
 * @function    parseHttpRequest
 * @abstract    Removes the json data from a request
 * @param       char*   request
 * @result      returns a string
*/
string parseHttpRequest(char *request);

/*!
 * @function    getCurrentTime
 * @abstract    converts the current time on the server
 *              to a string
 * @param       null
 * @result      returns a string
*/
string getCurrentTime();

#endif