#include <QtGui>
#include <QString>
#include <QMessageBox>

#include <iostream>
#include "gamearea.h"

/* Definiert das Spielfeld (gameArea) zu Beginn als nicht aktiv & initialisiert die Position des Spielers */
gameArea::gameArea(QWidget *parent) : QWidget(parent)
{
    player.setX(this->width()/2+20);
    player.setY(460);

    setFocusPolicy(Qt::StrongFocus);
    setRunning(false);
    running = false;
}

/* Zeichnet den Spieler in das Spielfeld */
void gameArea::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect (player.x(), player.y(), 30, 30, playerColor);
    painter.end();
}


/* Ermöglicht die Bewegung des Spielers über linke und rechte Pfeiltaste
 * bestimmt, um wie viele Pixel der Avatar sich in die jeweilige Richtung bewegt */
void gameArea::keyPressEvent(QKeyEvent *event)
{
    if(running) {
        if(event->key() == Qt::Key_Right) {
            player.rx() += 25;
        } else if (event->key() == Qt::Key_Left) {
            player.rx() -= 25;
        }
        update();
    }
}

/* Legt die Farbgebung des Spielfeldes im aktiven und inaktiven Zustand fest */
void gameArea::setRunning(bool run)
{
    running = run;
    if (run) {
        playerColor.setRgb (101, 81, 255);
        setPalette(QPalette(QColor (0,0,0)));
        setAutoFillBackground (true);
    }

    else {
        playerColor.setRgb (207, 201, 255);
        setPalette(QPalette(QColor (169,169,169)));
        setAutoFillBackground (true);
    }
}

void gameArea::serialize(QFile &file)
{
    QTextStream out(&file);
    out << "xPosition" << endl;
    out << "x " << player.x() << endl;
}

 void gameArea::deserialize(QFile &file)
{
    char c;
    QTextStream in(&file);
    QString header;

    in >> header;
    if (header != "xPosition")
    {
        QMessageBox::warning(this, tr("Formatfehler"),
                             tr("Das ist keine xPositions-Datei."),QMessageBox::Ok);
        return;
    }
     in >> c; //Zeilenumbruch
     in >> c; //Steuerzeichen (x) einlesen

     if (c!='x')
    {
        QMessageBox::warning(this, tr("Objektfehler"),
                             tr("Unbekanntes Steuerzeichen"),QMessageBox::Ok);
        return;
    }

    int x;
    in >> x;
    player.setX(x);
    update();
}
