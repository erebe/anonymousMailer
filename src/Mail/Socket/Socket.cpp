/* Auteur: Erebe (Romain Gerard)
 * Codé en l'an 10 de cette ère
 * Version 1.0
 * libre de droit, prevenez moi seulement
 *
 *
 * Librairie pour manipuler les sockets de facon simple
 * Construit pour respecter la RFC spécifiant
 * qu'une chaine de caractère doit se terminer par <CR> + <LF>
 *
 * A faire : Remplacer les messagew d'erreurs par des exceptions
 */

#include    <stdio.h>
#include    <stdexcept>
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
Socket::Socket ( string ip, unsigned short int port ):
_binded ( false ),
_connected ( false ),
_ip ( ip ),
_port ( port ) {

    int s;
    char num_port[25];
    struct addrinfo passeport;

    sprintf ( num_port, "%d", _port );
    memset ( &passeport, 0, sizeof ( struct addrinfo ) );
    passeport.ai_family = AF_INET;
    passeport.ai_socktype = SOCK_STREAM;
    passeport.ai_flags = AI_PASSIVE;
    passeport.ai_protocol = 0;
    passeport.ai_canonname = NULL;
    passeport.ai_addr = NULL;
    passeport.ai_next = NULL;

    if ( _ip == "0" ) {
        if ( ( s = getaddrinfo ( "127.0.0.1", num_port, &passeport, &_resul ) ) != 0 ) {
            cerr << "Impossible d'obtenir l'information sur l'hôte\n" <<
                gai_strerror ( s ) << endl;
        }
    }
    else {
        if ( ( s = getaddrinfo ( _ip.c_str (  ), num_port, &passeport, &_resul ) ) != 0 ) {
            cerr << "Impossible d'obtenir l'information sur l'hôte\n" <<
                gai_strerror ( s ) << endl;
        }
    }
    _resul0 = _resul;

}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  DESTRUCTEUR
 *  Description:  Libère les réssources associées à l'objet
 *   Parametres:
 * =====================================================================================
 */
Socket::~Socket () {
    if ( _resul0 )
        freeaddrinfo ( _resul0 );
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  init
 *  Description:  Permet d'initiliaser ou réinitialiser une socket
 *   Parametres:  ip -> chaine de caractères sous forme d'une adresse ip (ex: 88.171.90.19)
 *                      ou d'un d'hote (ex: larrun.iutbayonne.univ-pau.fr)
 *                port -> Détermine le port auquel est associé socket
 * =====================================================================================
 */
int Socket::init ( string ip, unsigned short int port ) {
    Socket::close (  );
    _binded = false;
    _connected = false;
    int s;
    char num_port[25];
    struct addrinfo passeport;
    _ip = ip;
    _port = port;

    sprintf ( num_port, "%d", _port );
    memset ( &passeport, 0, sizeof ( struct addrinfo ) );
    passeport.ai_family = AF_INET;
    passeport.ai_socktype = SOCK_STREAM;
    passeport.ai_flags = AI_PASSIVE;
    passeport.ai_protocol = 0;
    passeport.ai_canonname = NULL;
    passeport.ai_addr = NULL;
    passeport.ai_next = NULL;

    if ( _ip == "0" ) {
        if ( ( s = getaddrinfo ( "127.0.0.1", num_port, &passeport, &_resul ) ) != 0 ) {
            cerr << "Impossible d'obtenir l'information sur l'hôte\n" <<
                gai_strerror ( s ) << endl;
        }
    }
    else {
        if ( ( s = getaddrinfo ( _ip.c_str (  ), num_port, &passeport, &_resul ) ) != 0 ) {
            cerr << "Impossible d'obtenir l'information sur l'hôte\n" <<
                gai_strerror ( s ) << endl;
        }
    }
    _resul0 = _resul;

    return 1;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  accept
 *  Description:  mets la socket en mode écoute, et accepte les connections sur son port
 *   Parametres:
 * =====================================================================================
 */
Socket Socket::accept () {
    Socket distant;

    if ( _connected ) {
        throw std::logic_error("Désolé mais la socket est connecté");
    }

    if ( !_binded ) {
        for ( _resul = _resul0; _resul; _resul = _resul->ai_next ) {
            _descripteur = socket ( _resul->ai_family, _resul->ai_socktype, _resul->ai_protocol );
            if ( _descripteur < 0 )
                continue;
            if ( bind ( _descripteur, _resul->ai_addr, _resul->ai_addrlen ) != 0 )
                continue;
            if ( listen ( _descripteur, 2 ) < 0 )
                continue;
        }
        if ( _resul == NULL ) {
            throw std::logic_error("Désolé mais la socket n'a pu être bindé");
        }
        _binded = true;
    }
    distant._descripteur = ::accept ( _descripteur, distant._resul->ai_addr, &( distant._resul->ai_addrlen ) );
    distant._connected = true;

    return distant;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  connect
 *  Description:  Connect la socket vers un port distant
 *   Parametres:
 * =====================================================================================
 */
bool Socket::connect () {

    if ( _binded ) {
        throw std::logic_error("Désolé mais la socket est connecté");
    }

    for ( _resul = _resul0; _resul; _resul = _resul->ai_next ) {
        _descripteur = socket ( _resul->ai_family, _resul->ai_socktype, _resul->ai_protocol );

        if ( _descripteur < 0 )
            continue;

        if ( ::connect ( _descripteur, _resul->ai_addr, _resul->ai_addrlen ) == 0 )
            break;
    }

    if ( _resul == NULL ) {
        throw std::logic_error("Désolé mais la socket n'a pu être bindé");
    }
    _connected = true;

    return _connected;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get
 *  Description:  Recoit des informations de la socket sous forme d'un string
 *   Parametres:  max -> nombre d'octects maximaux à récupérer
 * =====================================================================================
 */
std::string Socket::get ( const unsigned int max ) const
{

    char *message;
    string chaine;

    if ( _binded ) {
        throw std::logic_error("Désolé mais vous ne pouvez pas recevoir d'informations de vous même");
    }
    if ( !_connected ) {
        throw std::logic_error("Vous devez connecter votre socket avant de pouvoir recevoir des informations");
    }

    message = new char[max + 1];

    memset ( message, 0x0, max + 1 );

    if ( recv ( _descripteur, message, max, 0 ) < 0 )
        cerr << "Connexion fermé par le distant" << endl;
    else
        chaine = message;

    delete[] message;
    return chaine;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  send
 *  Description:  Envoi des informations au travers de la socket
 *   Parametres:  chaine -> Chaine de caractère à transmettre
 * =====================================================================================
 */
int Socket::send (const std::string& chaine ) const
{
    if ( _binded ) {
        throw std::logic_error("Votre socket est bindé, elle ne peut envoyer des informations");
    }
    if ( !_connected ) {
        throw std::logic_error("Vous devez connecter votre socket avant de pouvoir transmettre des informations");
    }
    ssize_t length = ::send ( _descripteur, chaine.data(), chaine.size(), 0 );
    length += ::send ( _descripteur, "\r\n", sizeof(char)*2, 0 );

    return length;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  close
 *  Description:  Ferme la connection avec la socket
 *   Parametres:
 * =====================================================================================
 */
bool Socket::close ( ) {
    _connected = false;
    _binded = false;
    freeaddrinfo ( _resul0 );
    _resul0 = NULL;
    return ( shutdown ( _descripteur, 2 ) == 0 );
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getPort
 *  Description:  Retourne le port sur lequel est connecté la socket
 *   Parametres:
 * =====================================================================================
 */
unsigned short int Socket::getPort (  ) const
{
    return htons ( ( ( struct sockaddr_in * ) _resul->ai_addr )->sin_port );
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getIp
 *  Description:  Retourne l'ip de la socket
 *   Parametres:
 * =====================================================================================
 */
std::string Socket::getIp (  ) const
{
    return inet_ntoa ( ( ( struct sockaddr_in * ) _resul->ai_addr )->sin_addr );
}


bool Socket::isConnected (  ) const { return _connected; }

bool Socket::isBinded (  ) const { return _binded; }
