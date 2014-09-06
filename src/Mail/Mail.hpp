#ifndef  MAIL_H_INC
#define  MAIL_H_INC

#include "Socket/Socket.hpp"

#include    <vector>
#include    <string>
/*
 * =====================================================================================
 *        Class:  Mail
 *  Description: Permet d'envoyer des mails au format MIME contenant des pieces-jointes
 * =====================================================================================
 */
class Mail
{
    public:
        /* ====================  LIFECYCLE     ======================================= */
        Mail (const std::string& serveurSmtp, const std::string& expediteur, std::string& destinataires,
            const std::string& sujet, const std::string& message, std::string& piecesJointes);

        /* ====================  ACCESSORS     ======================================= */
        std::vector < std::string > getDestinataires () const;
        std::vector < std::string > getPiecesJointes () const;
        std::string getMessage () const;
        std::string getExpediteur () const ;
        std::string getsujet () const ;
        std::string getServeurSmtp () const ;

        /* ====================  MUTATORS      ======================================= */
        void addDestinataire (const std::string& adresse);
        void addPieceJointe (const std::string& filename);
        void setDestinataires (const std::string& destinataires);
        void setMessage (const std::string& message);
        void setSujet (const std::string& sujet);
        void setExpediteur (const std::string& expediteur);
        void setServeurSmtp (const std::string& serveur);

        /* ====================  OPERATORS     ======================================= */
        void send ();
        static std::string getMimeType( const std::string& nomFichier );

    private:
        std::string _serveurSmtp, _expediteur, _sujet, _message;
        std::vector < std::string > _piecesJointes;
        std::vector < std::string > _destinataires;
        Socket _socket;

        static void explodeString( std::string& chaine, std::string separator, std::vector <std::string>& conteneur );
        

};
#endif
