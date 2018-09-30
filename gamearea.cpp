#include <QtGui>
#include <QString>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include "gamewidget.h"
#include "gamearea.h"
#include "ui_gamearea.h"
#include "player.h"

/* Konstruktor der gameArea */
gameArea::gameArea(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::gameArea)
{
    ui->setupUi(this);

    //erstelle den Player in der gameArea
    playerRect = new player(this);
    //setze in ins Zentrum des Widget
    setCentralWidget(playerRect);

    setRunning(false);
    running = false;

    //Anfangswert der Punkte
    gamePoints = 0;

    //erstelle den Timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGame()));
    //starte den Timer
    timer->start(1000/30);
    //erzeuge unterschiedliche Anfangszustände
    srand(time(0));
}


/*Lässt Punkteanzeige kontinuierlich ansteigen*/
void gameArea::updateGame()
{
    //wenn das Programm läuft
    if(running){

        //sollen Punkte jeweils um 1 ansteigen
        gamePoints += 1;
        //das Widget geupdatet werden
        update();

        //und das Label 'Punkte' hinter die steigende Punkteanzahl gesetzt werden
        gamePointsLabel->setText(QString::number(gamePoints) + " Punkte");

    }

    //wenn der Spieler getroffen wurde
    if (getroffen) {
        //starte den Timer für das Timeout nachdem er getroffen ist
        getroffenTimer++;

        //wenn der Timer größer oder gleich dem vordefiniereten Timeout (50) für einen Treffer ist
        if (getroffenTimer >= getroffenTimeout) {
            //ist der Spieler nicht mehr getroffen
            getroffen=false;
            //und somit wieder unverwundbar
            unverwundbar = true;
            //das Spiel geht weiter
            setRunning(true);
            //der Timer wird wieder auf Null gesetzt
            getroffenTimer=0;
        }
    }

    //wenn das Spiel vorbei ist, also bei gameOver=true
    //(tritt beim Schneiden zweier Elemente und leben==0 ein)
    //sie drawEnemies-Funktion
    if (gameOver) {
        //ist der Spieler nicht getroffen, um nicht in die
        //getroffen-Bedingung zu springen
        getroffen=false;
        //starte den Timer für das Timeout nachdem er getroffen ist
        gameOverTimer++;

        //wenn der Timer größer oder gleich dem vordefiniereten Timeout (100) für das Spielende ist
        if (gameOverTimer >= gameOverTimeout) {
            //setze den Timer auf 0
            gameOverTimer=0;
            //das Spiel ist nicht mehr vorbei
            gameOver=false;
            //die Punkte & Leben werden zurückgesetzt
            gamePoints=0;
            leben = 3;
            //nach dem Timeout beginnt das Spiel wieder
            setRunning(true);
        }
    }

}

/* Lebensanzeige */
void gameArea::drawLives(QPainter &painter) {

    //Definition von 2 QRectF-Typ-Objekten
    //mit Koordinaten xPos,yPos und Größe width,height
    QRectF live3(670,20,30,30),live2(600,20,30,30),live1(635,20,30,30);
    //Füllung der Objekte
    QBrush live3brush (Qt::red);
    QBrush live2brush (Qt::red);
    QBrush live1brush (Qt::red);
    //Keine Füllung für verlorenes Leben
    Qt::BrushStyle liveLost = Qt::NoBrush;

    //Bei voller Lebensanzahl
    if (leben == 3) {
        //Zeichne alle drei Leben ausgefüllt
        painter.drawEllipse(live3);
        painter.setBrush(live3brush);
        painter.drawEllipse(live2);
        painter.setBrush(live2brush);
        painter.drawEllipse(live1);
        painter.setBrush(live1brush);

    }
    //Bei Verlust des 1. Lebens:
    if (leben ==2) {
        painter.drawEllipse(live3);
        painter.setBrush(live3brush);
        painter.drawEllipse(live2);
        painter.setBrush(live2brush);
        //Zeichne dieses Leben als leeren Rahmen
        painter.drawEllipse(live1);
        painter.setBrush(liveLost);
    }
    //Bei Verlust des 2. Lebens:
    if (leben ==1) {
        painter.drawEllipse(live3);
        painter.setBrush(live3brush);
        //Zeichne das 2. Lebens als leeren Rahmen
        painter.drawEllipse(live2);
        painter.setBrush(liveLost);
        //Zeichne das 1. Leben als leeren Rahmen
        painter.drawEllipse(live1);
        painter.setBrush(liveLost);
    }
    //Bei Verlust aller Leben:
    if (leben == 0) {
        //Zeichne alle Leben als leeren Rahmen
        painter.drawEllipse(live3);
        painter.setBrush(liveLost);
        painter.drawEllipse(live2);
        painter.setBrush(liveLost);
        painter.drawEllipse(live1);
        painter.setBrush(liveLost);
    }
}


void gameArea::drawEnemies(QPainter&painter )
{
    //For-Schleife
    //Solange der vector enemies größer ist als i
    for (int i = 0; i<enemies.size(); i++) {

        //definiere Pointer-Objekt e
        //alle Elemente aus enemies an Stelle i lassen sich durch e verwalten
        element* e = enemies[i];

        //setze Brush für ausgefüllte Farbdarstellung
        painter.setBrush(e->color);

        //wechsle über dem elementTyp (aus der Klasse element)
        switch (e->elementType) {
        //grünes Rechteck
        case 0:
            painter.drawRect(e->rect);
            break;
        //pinker Kreis
        case 1:
            painter.drawEllipse(e->rect);
            break;
        //gelbe Säule
        case 2:
            painter.drawRect(e->rect);
            break;
        //cyan Pie
        case 3:
            //vom Typ rect, mit startAngle & spanAngle
            painter.drawPie(e->rect,60 * 16,60 * 16);
            break;
        //dunkeltürkises rundes Rechteck
        case 4:
            //vom Typ rect, mit xRadius & yRadius
            painter.drawRoundedRect(e->rect, 25, 10);
            break;
        default:
            break;

        }

        //Bewege alle Elemente in der Liste enemies
        e->moveElement();

        //hole die aktuelle Position des Spielers (für Kollisionsabfrage)
        QRectF player(playerRect->getPlayerX(),playerRect->getPlayerY(),playerRect->getPlayerWidth(), playerRect->getPlayerHeight());

        //wenn ein Element aus der Liste enemies mit dem spieler kollidiert
        if (e->rect.intersects(player) && unverwundbar==false) {

            //mache den Spieler unverwundbar (starte den unverw.Timer)
            unverwundbar=true;
            //der Spieler wurde getroffen
            getroffen=true;
            //pausiere das Spiel
            setRunning(false);
            //ziehe ein Leben ab
            leben--;

            //wenn keine Leben mehr übrig sind
            if (leben==0) {
                //ist das Spiel vorbei
                gameOver=true;
            }
        }

        //wenn das aktuelle Rect die gameArea verlässt
        //die Y-Koordinate also größer als 700 ist
        if (e->rect.y() > 700) {
            //erzeuge ein neues Element
            e->newElement();

            //qDebug() << enemies.size();
            //Die QDebug Ausgabe der Vektorelemente ergibt immer 4,
            //da dem Vektor beim Klick auf Start 4 elements hinzugefügt werden
            //(siehe gamewidget.cpp)
            //diese Anzahl bleibt immer gleich; wenn Elemente die gameArea
            //also am unteren Rand verlassen, werden sie automatisch gelöscht
            //und verbleiben nicht im Vektor

        }
    }

}


void gameArea::paintEvent(QPaintEvent * ){
    QPainter painter;

    painter.begin(this);

    //zeichne die Leben
    for (int i =0; i <= leben; i++) {
        drawLives(painter);
    }

    //zeichne die Gegner in die gameArea
    drawEnemies(painter);

    //wenn unverwundbar = true ist
    if (unverwundbar) {

        //starte den Timer für die Zeit der Unverwundbarkeit
        unverwundbarTimer++;

        //wenn der Timer größer oder gleich dem vordefiniereten Timeout (30) der Unverwundbarkeit ist
        if (unverwundbarTimer >= unverwundbarTimeout) {
            //setze den Timer wieder auf 0
            unverwundbarTimer=0;
            //und der Spieler ist nicht mehr unverwundbar
            unverwundbar = false;
        }
    }

    painter.end();
}


/* Legt die Farbgebung des Spielfeldes im aktiven und inaktiven Zustand fest */
void gameArea::setRunning(bool run)
{
    running = run;
    //wenn das Spiel läuft
    if (run) {
        //lege die Hintergrundfarbe auf dunkelgrau fest
        setPalette(QPalette(QColor (105,105,105)));
        setAutoFillBackground(true);
        //bool status des Spiels ist true
    }
    //wenn Spiel nicht läuft
    else {
        //lege die Hintergrundfarbe auf hellgrau fest
        setPalette(QPalette(QColor (220,220,220)));
        setAutoFillBackground(true);
    }
}

/*Festlegung der Aktion für die saveGame()-Funktion */
void gameArea::serialize(QFile &file)
{
    QTextStream out(&file);
    out << "xPosition" << endl;
    out << "x " << playerRect->getPlayerX() << endl;
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
    playerRect->setPlayerX(x);
    update();
}

/*Dekonstruktor der Klasse gameArea*/
gameArea::~gameArea()
{

}
