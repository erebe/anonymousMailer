/*
 * =====================================================================================
 *
 *       Filename:  socket.hpp
 *
 *    Description:  Wrapper C++ pour manipuler des Sockets INET
 *
 *        Version:  1.0
 *        Created:  18/04/2011 22:38:46
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */

#ifndef H_SOCKET
#define H_SOCKET

#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>

    /*
     * =====================================================================================
     *        Class:  Socket
     *  Description:  Permet de manipuler facilement des Sockets en C++
     * =====================================================================================
     */
    class Socket
    {

        public:
            /* ====================  LIFECYCLE     ======================================= */
            Socket (const std::string& host, unsigned short int port);
            ~Socket ();

            /* ====================  ACCESSORS     ======================================= */
            int write ( const std::string& chaine ) const;
            std::string read (unsigned int max ) const;


        protected:
            int _socketFd;
            std::string _ip;
            unsigned short int _port;

    };
#endif
