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
            Socket ( std::string ip = "0", unsigned short int port = 0 );
            ~Socket ();

            /* ====================  ACCESSORS     ======================================= */
            std::string getIp () const;
            unsigned short int getPort () const;
            bool isConnected () const;
            bool isBinded () const;
            int send ( const std::string& chaine ) const;
            std::string get ( const unsigned int max ) const;

            /* ====================  MUTATORS      ======================================= */
            int init ( std::string ip = "0", unsigned short int port = 0 );
            Socket accept ();
            bool connect ();
            bool close ();

            /* ====================  OPERATORS     ======================================= */

        protected:
            int _descripteur;
            struct addrinfo *_resul, *_resul0;
            bool _binded;
            bool _connected;
            std::string _ip;
            unsigned short int _port;

    };
#endif
