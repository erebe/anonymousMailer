/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Programme pour envoyer des emails avec la possibilité d'ajouter des pièces jointes en ligne de commande
 *
 *        Version:  1.0
 *        Created:  17/04/2011 11:59:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */

#include    <iostream>
#include    <cstdlib>
#include    <sstream>

#include    "../Mail/Mail.hpp"

using namespace std;

int
main (int argc, char *argv[]) {

    int c = 0;
    string sujet, destinataire, expediteur, piecesJointes, message, contacte;
    int bomber = 1;
    stringstream oss;

    while ((c = getopt (argc, argv, "c:s:d:e:p:m:b:")) != -1) {

        switch (c) {
            case 's':
                sujet = optarg;
                break;
            case 'd':
                destinataire = optarg;
                break;
            case 'e':
                expediteur = optarg;
                break;
            case 'p':
                piecesJointes = optarg;
                break;
            case 'm':
                message = optarg;
                break;
            case 'b':
                oss << optarg;
                oss >> bomber;
                break;
            case 'c':
                contacte = optarg;
                break;
            default:
                cerr << "mailme [csdepmb] :\n"
                    "-s Indique le sujet du mail\n"
                    "-c Indique le serveur smtp à contacter\n"
                    "-d Renseigne la liste des destinatires séparé par un virgule\n"
                    "-e Renseigne l'expediteur du mail\n"
                    "-p Renseigne la liste des pièces jointes à envoyer séparé par une virgule\n"
                    "-m Le message du mail\n"
                    "-b Le nombre de fois que vous souhaitez envoyer le mail..." << endl;
                exit( EXIT_FAILURE );
                break;
        }
    }

    if( message.empty() ) {
        bool messageEcrit = false;
        string buffer;

        cout << "Veuillez saisir votre message."
                " Pour le terminer saisissez une ligne ne contenant qu'un point"
                << endl;

        while( !messageEcrit ) {
            std::getline(cin, buffer);

            if( buffer == "." ) {
                messageEcrit = true;
            }else {
                 message += buffer + "\r\n";
            }

        }
    }

    Mail mail(contacte, expediteur, destinataire, sujet, message, piecesJointes);
    for(int i = 0; i < bomber; i++) {
        mail.send();
    }

    return EXIT_SUCCESS;
}
