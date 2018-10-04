#include <QApplication>

#include "gamearea.h"
#include "gamewidget.h"
#include "player.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Erzeuge ein Widget-Objekt w auf Basis der Klasse gameWidget
    gameWidget w;
    //Lege die Abmessungen des gameWidget fest
    //w.setGeometry(0 , 0, 700, 500);
    //Setze sie auf eine feste Größe
    w.setFixedSize(890,650);
    //Gebe dem Spielfenster einen Titel
    w.setWindowTitle("C++-Spiel von Kim Roland");
    //Sorge dafür, dass das Fenster auf allen Betriebssystemen
    //über die Buttons Größer, Kleiner und Schließen verfügt
    w.setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    //zeige das Widget
    w.show();

    return a.exec();
}
