#ifndef  GUI_INC
#define  GUI_INC

#include    <QtGui>
#include    <QWidget>
#include    "ui_interface.h"

/*
 * =====================================================================================
 *        Class:  Gui
 *  Description:  Classe qui gère l'interface du programme
 * =====================================================================================
 */
class Gui : public QWidget, private Ui::Interface
{
    Q_OBJECT

        public:
        /* ====================  LIFECYCLE     ======================================= */
        Gui ( QWidget* parent = 0 );

        /* ====================  ACCESSORS     ======================================= */

        /* ====================  MUTATORS      ======================================= */

        /* ====================  OPERATORS     ======================================= */

    protected:
        /* ====================  DATA MEMBERS  ======================================= */

    private slots:
        /* ====================  DATA MEMBERS  ======================================= */
        void on_bouttonEnvoyer_clicked();
        void on_linePiecesJointes_returnPressed();

};
#endif
