/*
 * =====================================================================================
 *
 *       Filename:  mail.cpp
 *
 *    Description:  Implémentation de la classe Mail. Cette classe permet d'envoyer des
 *                  mails au format MIME et pouvant contenir des pièces-jointes
 *
 *        Version:  1.0
 *        Created:  21/04/2011 20:33:46
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */

#include    "Mail.hpp"
#include	"Base64/Base64.hpp"
#include	<fstream>
#include    <string>

using namespace std;

Mail::Mail(const string& serveurSmtp, const string& expediteur, string& destinataires, const string& sujet,
           const string& message, string& piecesJointes):
    Socket(serveurSmtp, 25),
    _serveurSmtp(serveurSmtp),
    _expediteur(expediteur),
    _sujet(sujet),
    _message(message)
{
    explodeString( destinataires, ",", _destinataires );
    explodeString( piecesJointes, ",", _piecesJointes );
}


void Mail::send() {

    /*-----------------------------------------------------------------------------
     *  On contacte le serveur smtp et on se présente à lui
     *-----------------------------------------------------------------------------*/
    Socket::connect();

    cout << Socket::get( 500 ) << endl;

    string message = "EHLO erebe\nMAIL FROM:<" + _expediteur +  ">\n";
    for( auto& destinataire: _destinataires ) {
        message += "RCPT TO:<" + destinataire + ">\n";
    }
    message += "DATA";

    Socket::send( message );
    cout << Socket::get( 500 ) << endl;

    message.erase();

    /*-----------------------------------------------------------------------------
     *  On envoie le corps du message
     *-----------------------------------------------------------------------------*/
    message += "From: <" + _expediteur + ">\n";

    for( auto& destinataire: _destinataires) {
        message += "To: <" + destinataire + ">\n";
    }
    message += "Subject: " + _sujet + "\n"
    + "MIME-version: 1.0\n"
    + "Content-type: multipart/mixed;boundary=\"iletaitunefois\"\n"
    + "Ce message est au format MIME.\n"
    +  "                                                .                                               \n"
    +  "                                               ':'                                              \n"
    +  "   '                                          `;;;:.                                         '  \n"
    +  "  `;:'`.                                     ';;;;;:.                                    ..`:;;.\n"
    +  "  .;;;;;;;'`..                      .      .:;;;;;;;;`                              ..`:;;;;;;' \n"
    +  "   `;;;;;;;;;;;''..               .``     .;;;;;;;;;;;'.      `.               .`':;;;;;;;;;;;. \n"
    +  "    ;;;;;;;;;;;;;;;;:'`.         `;'     `:;;;;::::::::'.     ';`         .`':;;:;:;:;:;:;:;:'  \n"
    +  "    `;;;;;;;;;;;;;;;;;;;;:'`....';:     ';'           .';`     :;'....`':;;::;:;:;:;:;:;:;:;;.  \n"
    +  "     `'':::;;;;;;;;;;;;;;;;;;;;;;;`   .;;;;'.        .:;;;`    `;;;::;;;:;:;;:;;:;:;;;:::''.    \n"
    +  "             ....```''::::;;;;;;;;.  .:;;;;;:.      `:;;:;;'.  .;;;;;;;;;:::'''``....           \n"
    +  "                            ..:;;:  `;;;;;;;;;`   .';;:;;;;;:.  :;;:..                          \n"
    +  "                    .......```;;;;.';;;;;;;;;;;:..:;;;;;;;;;;:`.:;;;```......                   \n"
    +  "        `'''::::::;;;;;;;;;;x;;;;;:`...........................';;;;;;;;;;;;;;;;:::::''''.      \n"
    +  "        .;;;;;;;;;;;;;;;;;;;;::;;;;'.        E r e b e        ';;;;::;;;;;;;;;;;;;;;;;;;:.      \n"
    +  "         .:;;;;;;;;;;;;;:'`..  ';;;;:'`.       .::.       .`':;;;;'  ..`':;;;;;;;;;;;;;'        \n"
    +  "          .;;;;;;;;;'`..     .':;;;;;;;::'`   .:;;;.   `'::;;;;;;;:'.     ..`';;;;;;;;'         \n"
    +  "           .'::``.        .':;;;;:::;:::;;;` .:;;;;;. `;;;;::;;::;;;;:'.        .`'::'          \n"
    +  "                       .`:;;;;;:` .:;;;;;;: .:;;;;;;:. ':;;;;;:. .:;;;;;:`.                     \n"
    +  "                    .`:;;;;;;:`   ';;;:`.. .:;;;;;;;;:.  `:;;;'   `:;;;;;;'`.                   \n"
    +  "                  `':;;;;;;:`.   `;;;;'   .:;;;;;;;;;;;.    `;;;;`   .`:;;:;;;;'.               \n"
    +  "                  `':;;;;;'.    .:;:;:.   ':;;;;;;;;;:'    .:;;;;.    .';;;;;:'.                \n"
    +  "                    .`':'.     .:;;;;:      .':;;;;:`.      ';::;:.     .':'.                   \n"
    +  "                              .:;;;;;`   .''. .:;;:. .''.   `;;;;;:.                            \n"
    +  "                              .````''.  `;;;` ':;;:' `;;:.  .''````.                            \n"
    +  "                                       `;;:. .::::::. .';:.                                     \n"
    +  "                               ;;;;;;;;;;:`.  ':::::' .`:;:;;;;;;;;                             \n"
    +  "                              ';::::::::;;:.   ':::'  .:;;:''':;;;:'                            \n"
    +  "                                `':`   .`       ':'     ``.   ':'                               \n"
    +  "                                   `.            `           .`                                 \n"
    +  "--iletaitunefois\n"
    + "Content-Type: text/plain; charset=utf-8; format=flowed\n"
    + "Content-Transfer-Encoding: 8bit\n\n"
    + _message + "\n\n";

    /*-----------------------------------------------------------------------------
     *  On ajoute les pièces-jointes dans le message
     *-----------------------------------------------------------------------------*/
    for(auto& pieceJointe: _piecesJointes) { 
		char* fichierEncode = Base64::encode( pieceJointe );

		message += "\n--iletaitunefois\n";
		message += "Content-Type: " + Mail::getMimeType( pieceJointe ) + ";";
		message += " name=\"";
		message += pieceJointe;
		message += "\"\n";
		message += "Content-Transfer-Encoding: base64\n";
		message += "Content-Disposition: attachment;";
		message += " filename=\"";
		message += pieceJointe;
		message += "\"\n\n";
		message += fichierEncode;

		delete[] fichierEncode;
	}

    /*-----------------------------------------------------------------------------
     *  On termine l'echange avec le serveur smtp
     *-----------------------------------------------------------------------------*/
    message += "\n--iletaitunefois--\n";
    message += ".\r\n";
    message += "QUIT";

    Socket::send( message );
    cout << Socket::get( 500 ) << endl;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  explodeString
 *  Description:  Permet d'extraire toutes les sous-chaines séparées par un delimiteur
 *   Parametres:  chaine -> La chaine à découper
 *                separator -> Le delimiteur
 *                conteneur -> le vector dans lequel stocker les chaines extraites
 * =====================================================================================
 */
void Mail::explodeString( string& chaine, string separator, vector<string>& conteneur ) {

    int found = chaine.find_first_of( separator );

    while( found != ((int) string::npos) ) {
        if( found > 0 ) {
            conteneur.push_back( chaine.substr( 0, found ));
        }
        chaine = chaine.substr( found + 1 );
        found = chaine.find_first_of( separator );
    }

    if ( chaine.length() > 0 ) {
        conteneur.push_back( chaine );
    }

}

string Mail::getMimeType(const string& nomFichier ){

    string ligne, mime, nomFic;
    bool trouve = false;
    nomFic = nomFichier.substr( nomFichier.find_last_of( '.' ) );

    ifstream mimeListe( "mime.type", ios::in );
    if( !mimeListe.is_open() )
        throw ios_base::failure("Impossible d'ouvrir le fichier mime.type" );

    
    while( !trouve && getline( mimeListe, ligne ) ) {
        
        if( ligne.substr(0, ligne.find_first_of( '\t' ) - 1 ) == nomFic ){
            trouve = true;
            mime = ligne.substr( ligne.find_first_of( '\t' ) + 1 );
        }
    }
    if( mime.empty() ){
        mime = "application/octet-stream";
    }

    mimeListe.close();
    return mime;
}
