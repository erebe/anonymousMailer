/* Auteur: Erebe (Romain Gerard)
 * Codé en l'an 10 de cette ère
 * Version 1.0
 *
 *
 */

#include    <stdio.h>
#include    <stdexcept>
#include    <cstring>
#include    <errno.h>
#include    "Socket.hpp"

using namespace std;

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  CONSTRUCTEUR
 *  Description:  Initialise l'objet
 *   Parametres:  ip -> chaine de caractères sous forme d'une adresse ip (ex: 88.171.90.19)
 *                      ou d'un d'hote (ex: larrun.iutbayonne.univ-pau.fr)
 *                port -> Détermine le port auquel est associé socket
 * =====================================================================================
 */
Socket::Socket (const string& ip, unsigned short int port )
{

    int s;
    char num_port[10];
    struct addrinfo passeport;

    snprintf ( num_port, sizeof(num_port), "%d", port );
    memset ( &passeport, 0, sizeof (passeport) );
    passeport.ai_family = AF_INET;
    passeport.ai_socktype = SOCK_STREAM;
    passeport.ai_flags = AI_PASSIVE;
    passeport.ai_protocol = 0;
    passeport.ai_canonname = NULL;
    passeport.ai_addr = NULL;
    passeport.ai_next = NULL;

    struct addrinfo* result;
    struct addrinfo* rp;
    if ( ( s = getaddrinfo ( ip.c_str(), num_port, &passeport, &result ) ) != 0 ) {
        throw runtime_error(string(  "Impossible d'obtenir l'information sur l'hôte\n")
                                  + "getaddrinfo: " + gai_strerror(s));
    }

    int socketFd;
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        socketFd = ::socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if (socketFd == -1)
            continue;

        if(::connect(socketFd, result->ai_addr, result->ai_addrlen ) == 0)
            break;                  /* Success */

        ::close(socketFd);
    }

    if(rp == NULL) {
        throw runtime_error(string("Cannot connect the socket\n")
                + strerror(errno));
    }

    _socketFd = socketFd;
   freeaddrinfo(result);


}



/*
 * ===  FUNCTION  ======================================================================
 *
 *
 *         Name:  DESTRUCTEUR
 *  Description:  Libère les réssources associées à l'objet
 *   Parametres:
 * =====================================================================================
 */
Socket::~Socket () {
    shutdown ( _socketFd, SHUT_RDWR);
    close(_socketFd);
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  get
 *  Description:  Recoit des informations de la socket sous forme d'un string
 *   Parametres:  max -> nombre d'octects maximaux à récupérer
 * =====================================================================================
 */
std::string Socket::read (unsigned int max ) const
{

    ssize_t length;
    string chaine;
    chaine.resize(max + 1);

    length = ::recv( _socketFd, (char*) chaine.data(), max, 0 );
    if ( length < 0 )
    {
        cerr << "Connexion fermé par le distant" << endl
             << "recv: " << strerror(errno);
        return string();
    }
    chaine.resize(length);

    return chaine;
}


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  send
 *  Description:  Envoi des informations au travers de la socket
 *   Parametres:  chaine -> Chaine de caractère à transmettre
 * =====================================================================================
 */
int Socket::write (const std::string& chaine ) const
{
    ssize_t length = ::send ( _socketFd, chaine.data(), chaine.size(), 0 );
    length += ::send ( _socketFd, "\r\n", sizeof(char)*2, 0 );

    return length;
}
