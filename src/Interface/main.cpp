/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25/04/2011 01:00:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */

#include	<QApplication>
#include	<QtGui>
#include <QWidget>
#include	"Gui.hpp"

int main( int argc, char* argv[] ){

    QApplication app(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    Gui interface;
    interface.show();

    return app.exec();
}
