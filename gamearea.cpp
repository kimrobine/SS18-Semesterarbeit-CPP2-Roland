#include <QtGui>
#include <QString>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <cstdlib>

#include "gamewidget.h"
#include "gamearea.h"
#include "ui_gamearea.h"
#include "player.h"

gameArea::gameArea(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::gameArea)
{
    setAutoFillBackground(true);
    setMouseTracking(false);
    ui->setupUi(this);

    //erstelle den Player in der gameArea
    playerShape = new player(this);
    setCentralWidget(playerShape);

    setRunning(false);
    running = false;

    //Anfangswert der Punkte
    gamePoints = 0;

    //erstelle den Timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGame()));
    //starte den Timer mit einem timeout von 300 Millisekunden
    timer->start(300);

}

/*Lässt Punkteanzeige kontinuierlich ansteigen*/
void gameArea::updateGame()
{
    if(running){
        //Punkte sollen jeweils um 10 ansteigen
        gamePoints += 10;
        update();

        //Label 'Punkte' hinter steigende Punkteanzahl setzen
        gamePointsLabel->setText(QString::number(gamePoints) + " Punkte");

    }
}

void gameArea::paintEvent(QPaintEvent * ){
 //hier müssen fallende Objekte gemalt werden?
}


/* Legt die Farbgebung des Spielfeldes im aktiven und inaktiven Zustand fest */
void gameArea::setRunning(bool run)
{
    running = run;
    if (run) {
        setPalette(QPalette(QColor (0,0,0)));
        setAutoFillBackground (true);
    }

    else {
        setPalette(QPalette(QColor (169,169,169)));
        setAutoFillBackground (true);
    }
}

/*Festlegung der Aktion für die saveGame()-Funktion */
void gameArea::serialize(QFile &file)
{
    QTextStream out(&file);
    out << "xPosition" << endl;
    out << "x " << playerShape->getPlayerX() << endl;
}

/*Festlegung der Aktion für die loadGame()-Funktion */
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
    playerShape->setPlayerX(x);
    update();
}

gameArea::~gameArea()
{
    delete ui;
}
