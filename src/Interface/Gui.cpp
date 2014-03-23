#include    "Gui.hpp"
#include	"../Mail/Mail.hpp"

Gui::Gui( QWidget* parent ):
QWidget(parent) {

    setupUi(this);
}

void Gui::on_bouttonEnvoyer_clicked(){

    Mail mail( lineServeur->text().toStdString(), lineExpediteur->text().toStdString(),
               lineDestinataire->text().toStdString(), lineSujet->text().toStdString(),
               textMessage->toPlainText().toStdString(), linePiecesJointes->text().toStdString()); 
    mail.send();
    QMessageBox::information(this, "Le mail à bien été envoyé", "Le mail a bien été envoyé"); 

}

void Gui::on_linePiecesJointes_returnPressed() {

    linePiecesJointes->setText(QFileDialog::getOpenFileNames(this).join(",")); 


} 
