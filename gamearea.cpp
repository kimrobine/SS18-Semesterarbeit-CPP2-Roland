#include <QtGui>
#include <QString>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <iostream>

#include "gamewidget.h"
#include "gamearea.h"
#include "ui_gamearea.h"
#include "player.h"

/* Konstruktor der gameArea:
 * Initialisierung des Anfangszustandes des Spiels
 * und seiner Elemente */
gameArea::gameArea(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::gameArea)
{
    //setze den Namespace
    ui->setupUi(this);

    //Initalisierung des Spielers
    //erstelle den Player in der gameArea
    gamePlayer = new player(this);
    //an der momentanen X-Position
    gamePlayer->getPlayerX();
    //und mit der Darstellung bei vollen Leben
    gamePlayer->setPlayerStyle(0);
    //setze ihn ins Zentrum des Widget-Fensters
    setCentralWidget(gamePlayer);

    //initalisiere den Spielzustand als inaktiv
    setRunning(false);
    running = false;

    //Anfangswerte der Punkte & Leben
    gamePoints = 0;
    leben = 3;

    //Initalisierung der möglichen Spieler-Zustände
    unverwundbar = false;
    getroffen = false;
    gameOver = false;

    //Anfangswerte der Zustands-Timer
    unverwundbarTimer = 0;
    getroffenTimer = 0;
    gameOverTimer = 0;

    //erstelle den Timer
    timer = new QTimer(this);
    //verknüpfe ihn mit der updateGame()-Methode
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGame()));
    //starte den Timer
    timer->start(1000/30);
    //erzeuge unterschiedliche Anfangszustände der Time-Instanz
    //damit unterschiedliche Gegner erzeugt werden
    srand(time(0));

    //Initalisierung der Gegnerelemente
    //Hinzufügen neuer zufälliger Objekte zum Vektor enemies
    enemies.push_back(new element());
    enemies.push_back(new element());
    enemies.push_back(new element());
    enemies.push_back(new element());

}


/* Aktualsierung des Spiels und seiner Zustände */
void gameArea::updateGame()
{
    //wenn das Spiel läuft
    if(running){

        //sollen die Punkte jeweils um 1 ansteigen,
        gamePoints += 1;
        //das Widget geupdatet werden
        update();

        //und das Label 'Punkte' hinter die steigende Punkteanzahl gesetzt werden
        gamePointsLabel->setText(QString::number(gamePoints) + " Punkte");

    }

    //wenn der Spieler gerade getroffen wurde
    //also unverwundbar = true ist
    if (unverwundbar) {

        //starte den Timer für die Zeit der Unverwundbarkeit
        unverwundbarTimer++;

        //wenn der Timer größer oder gleich dem vordefiniereten Timeout (30) der Unverwundbarkeit ist
        if (unverwundbarTimer >= unverwundbarTimeout) {
            //setze den Timer wieder auf 0
            unverwundbarTimer=0;
            //und der Spieler ist wieder verwundbar
            unverwundbar = false;
        }
    }

    //wenn der Spieler getroffen wurde
    if (getroffen) {
        //starte den Timer für das Timeout nachdem er getroffen ist
        getroffenTimer++;

        //wenn der Timer größer oder gleich dem vordefiniereten Timeout (50) für einen Treffer ist
        if (getroffenTimer >= getroffenTimeout) {
            //ist der Spieler nicht mehr getroffen
            getroffen=false;
            //und somit unverwundbar (startet unverwundbarTimer)
            unverwundbar = true;
            //der getroffenTimer wird wieder auf Null gesetzt
            getroffenTimer=0;
            //und das Spiel geht weiter
            setRunning(true);
        }
    }

    //wenn das Spiel vorbei ist, also bei gameOver=true
    //(tritt beim Schneiden zweier Elemente und leben==0 ein, siehe drawEnemies()-Methode)
    if (gameOver) {
        //starte den Timer für das gameOver-Timeout
        gameOverTimer++;

        //wenn der Timer größer oder gleich dem vordefiniereten Timeout (120) für das Spielende ist
        if (gameOverTimer >= gameOverTimeout) {
            //setze den Timer auf 0
            gameOverTimer=0;
            //das Spiel ist nicht mehr vorbei
            gameOver=false;
            //entferne den gameOverScreen: Texte & Punktezahl
            delete gOText;
            delete gOText2;
            delete gOPoints;
            //Leben zurücksetzen
            leben = 3;
            //Spielerdarstellung auf Darstellung bei vollen Leben zurücksetzen
            gamePlayer->setPlayerStyle(0);
            //Leben & Spieler-Darstellung werden erst nach dem Timeout
            //zurückgesetzt, damit während dessen Lebensanzeige leer ist
            //und Spieler abgeschwächt dargestellt bleibt

            //nach dem gameOverTimeout beginnt das Spiel wieder
            setRunning(true);
        }
    }

}


/* Lebensanzeige */
void gameArea::drawLives(QPainter &painter) {

    //Definition von 3 QRectF-Objekten
    //mit Koordinaten (X,Y) und Abmessungen (Breite,Höhe)
    QRectF live1(570,20,30,30),live2(605,20,30,30),live3(640,20,30,30);

    //Füllung des Lebens-Objekts bei vorhandenem Leben
    QBrush liveFull (Qt::red);
    //Keine Füllung bei Verlust des Lebens
    Qt::BrushStyle liveLost = Qt::NoBrush;

    //Definition der Außenlinie
    QPen livesPen (Qt::red);
    livesPen.setWidth(2);
    painter.setPen(livesPen);

    //Bei voller Lebensanzahl
    if (leben == 3) {
        //Zeichne alle drei Leben ausgefüllt
        painter.setBrush(liveFull);
        painter.drawEllipse(live1);
        painter.drawEllipse(live2);
        painter.drawEllipse(live3);
    }

    //Bei Verlust des 1. Lebens:
    if (leben ==2) {
        //Zeichne das 1. Leben als leeren Rahmen
        painter.setBrush(liveLost);
        painter.drawEllipse(live1);

        painter.setBrush(liveFull);
        painter.drawEllipse(live2);
        painter.drawEllipse(live3);
    }

    //Bei Verlust des 2. Lebens:
    if (leben ==1) {
        //Zeichne das 1. & 2. Leben als leeren Rahmen
        painter.setBrush(liveLost);
        painter.drawEllipse(live1);
        painter.drawEllipse(live2);

        painter.setBrush(liveFull);
        painter.drawEllipse(live3);
    }

    //Bei Verlust aller Leben:
    if (leben == 0) {
        //Zeichne alle Leben als leeren Rahmen
        painter.setBrush(liveLost);
        painter.drawEllipse(live1);
        painter.drawEllipse(live2);
        painter.drawEllipse(live3);
    }
}

/* Methode, um Darstellung des Spielers abhängig von seiner Anzahl an Leben zu verändern */
void gameArea::changePlayerStyle() {

    //bei vollen Leben
    if (leben==3) {
        //Nutzung der class player-Methode setPlayerStyle()
        //Übergabe des Zahlenwertes zur Bestimmung des Style-Typs
        //0 = anfängliche, 'gesunde' Darstellung des Spielers
        gamePlayer->setPlayerStyle(0);
    }

    //bei Verlust eines Lebens
    if (leben==2) {
        //setze den PlayerStyle auf
        //die abgeschwächte Darstellung des Spielers Stufe 1
        //mittelblau und gepunktet
        gamePlayer->setPlayerStyle(1);
    }

    //bei Verlust des zweiten Lebens
    if (leben==1) {
        //setze den PlayerStyle auf
        //die abgeschwächte Darstellung des Spielers Stufe 2
        //helles blau, leerer Rahmen
        gamePlayer->setPlayerStyle(2);
    }
}


/* Zeichnen der Gegner (fallende Elemente)
 * Kollisionsfunktionalität bei Berührung des Spielers
 * mit einem Gegner-Element */
void gameArea::drawEnemies(QPainter &painter)
{
    //For-Schleife
    //Solange der vector enemies größer ist als Durchlaufvariable i
    for (int i = 0; i<enemies.size(); i++) {

        //definiere Pointer-Objekt e auf Basis der Klasse element
        //alle Elemente aus enemies an Stelle i lassen sich durch e verwalten
        element* e = enemies[i];

        //definiere Brush für Anwendung elementabhängiger Farbe & Muster
        QBrush enemyBrush (e->color,e->pattern);
        painter.setBrush(enemyBrush);

        //definiere Pen für Anwendung elementabhängiger PenFarbe & PenDicke
        QPen enemyPen (e->pen);
        enemyPen.setWidth(e->penWidth);
        painter.setPen(enemyPen);

        //Wechsle über dem elementType der Gegnerelemente
        //Zeichne die Gegnerelemente mit ihrer spezifischen
        //Form anhand des elementType
        switch (e->elementType) {
        //Rechteck
        case 0:
            painter.drawRect(e->rect);
            break;
        //lange Ellipse
        case 1:
            painter.drawEllipse(e->rect);
            break;
        //Säule
        case 2:
            painter.drawRect(e->rect);
            break;
        //Dreieck (pie)
        case 3:
            //vom Typ rect, mit startAngle & spanAngle
            painter.drawPie(e->rect,60 * 16,60 * 16);
            break;
        //rundes Rechteck
        case 4:
            //vom Typ rect, mit xRadius & yRadius
            painter.drawRoundedRect(e->rect, 25, 10);
            break;
        //lebenaddierender roter Kreis
        case 5:
            painter.drawEllipse(e->rect);
            break;
        }

        //Bewege alle Gegnerelemente
        e->moveElement();

        //Definition eines neuen QRectF-Elements
        //--> wird benötigt für Kollisionsabfrage mit intersects()-Methode
        //Gleichsetzung mit Eigenschaften des gamePlayers
        QRectF player(gamePlayer->getPlayerX(),gamePlayer->getPlayerY(),gamePlayer->getPlayerWidth(), gamePlayer->getPlayerHeight());

        //Definition eines neuen QRectF-Elements
        //als Verwaltungselement für enemies
        QRectF enemy (e->rect);

        //türkises pie-Element soll auch mit gamePlayer intersecten
        //Breite und Höhe müssen reduziert werden
        //da es sich sonst zu früh mit dem Spieler schneidet
        if (e->elementType == 3) {
            enemy.setHeight(30);
            enemy.setWidth(40);
        }

        //wenn ein Gegner mit dem Spieler kollidiert und der Spieler verwundbar ist
        if (enemy.intersects(player) && unverwundbar==false) {

            //mache den Spieler unverwundbar (startet den unverwundbar-Timer)
            unverwundbar=true;
            //der Spieler wurde getroffen (startet den getroffen-Timer)
            getroffen=true;
            //pausiere das Spiel
            setRunning(false);

            /* --- Definition Aktion lebenregenerierender Kreis --- */

            //wenn es sich bei dem elementType um den Wert 5, also um den roten Kreis handelt
            if (e->elementType==5) {
                //und der Spieler nicht über alle Leben verfügt
                if (leben!=3){
                    //addiere ein Leben bei der Kollision von rotem Kreis und Spieler
                    //statt eines zu entfernen
                    leben++;

                    //sorge für verbesserte Darstellung des Spielers
                    changePlayerStyle();

                }
             //verfügt der Spieler über volle Leben
             else {
                    //bleiben Leben unverändert
                    leben = 3;
                }

            /* --- Ende Definition Aktion lebenregenerierender Kreis --- */

            }

            //bei der Kollision des Spielers mit jedem anderen Gegner
            else {
                //ziehe ein Leben ab
                leben--;

            }

            //sorge für abgeschwächte Darstellung des Spielers
            changePlayerStyle();


            //wenn keine Leben mehr übrig sind
            if (leben==0) {
                //ist das Spiel vorbei
                //rufe die gameOver-Methode auf
                gameIsOver();
            }
        }


        //wenn das aktuelle Gegner-Rect die gameArea verlässt
        //die Y-Koordinate also größer als 670 ist
        if (e->rect.y() > 670) {
            //erzeuge ein neues zufälliges Element
            e->newElement();

        }
    }

}


/* Paint-Methode, um draw-Methoden der Lebensanzeige & der Gegner
 * auszulösen */
void gameArea::paintEvent(QPaintEvent * ){

    QPainter painter;

    painter.begin(this);

    for (int i =0; i <= leben; i++) {
        //rufe die Methode zum Zeichnen der Leben auf
        drawLives(painter);
    }

    //wenn gameOver=false ist, das Spiel also aktiv und nicht zuende ist
    if (!gameOver){
        //rufe die Methode zum Zeichnen der fallenden Gegner-Objekte auf
        drawEnemies(painter);
    }

    painter.end();
}


/* gameOver-Methode: regelt gameOver-Anzeige und setzt Spiel zurück */
void gameArea::gameIsOver() {

    //das Spiel ist vorbei
    gameOver=true;
    //der Spieler ist nicht getroffen, um nicht
    //den getroffen-Timer auszulösen
    getroffen=false;

    /* --- Definition der gameOver-Anzeige --- */

    //Defintion des Label-Textes
    gOText = new QLabel ("Game Over :(");
    //Label soll child-Element des Widget sein
    gOText->setParent(this);
    //Festlegung der Schriftart & Schriftgröße
    gOText->setFont(QFont("Helvetica", 34));
    //Nutzung der QWidget-Funktion move()
    //um Text innerhalb der gameArea zu platzieren
    gOText->move(350-120, 0);
    //Labeltext anzeigen
    gOText->show();

    //Defintion des Label-Textes und Verbindung mit Punkten
    gOPoints = new QLabel (QString("Erreichte Punkte: ").append(QString::number(gamePoints)));
    gOPoints->setParent(this);
    gOPoints->setFont(QFont("Helvetica", 26));
    gOPoints->move(350-120, 50);
    gOPoints->show();

    gOText2 = new QLabel ("Versuch es noch einmal!");
    gOText2->setParent(this);
    gOText2->setFont(QFont("Helvetica", 20));
    gOText2->move(350-120, 100);
    gOText2->show();

    /* --- Ende Defintion der gameOver-Anzeige --- */

    //die Punkte werden zurückgesetzt
    gamePoints = 0;

    //Lösche die aktuellen Gegner
    //und generiere neue Gegner
    for (element *e:enemies) {
        e->newElement();
    }

    //Zurücksetzung der Leben & Spieler-Darstellung
    //--> siehe updateGame()-Methode, if (gameOver)-Bedingung
}


/* Legt die Farbgebung des Spielfeldes im aktiven und inaktiven Zustand fest */
void gameArea::setRunning(bool run)
{
    //bool-Variable run (true/false) wird dieser Funktion übergeben
    //und running wird auf gleichen Wert gesetzt
    running = run;

    //wenn das Spiel läuft
    if (running) {
        //lege die Hintergrundfarbe auf dunkelgrau fest
        setPalette(QPalette(QColor("#2E2E2E")));
        setAutoFillBackground(true);

    }

    //wenn Spiel nicht läuft
    else {
        //lege die Hintergrundfarbe auf hellgrau fest
        setPalette(QPalette(QColor("#8A8A8A")));
        setAutoFillBackground(true);
    }
}


/* Festlegung der Aktion für die saveGame()-Funktion:
 * Speicherung des aktuellen Spielstandes */
void gameArea::serialize(QFile &file)
{
    //exportiere die Daten mit out in die Datei
    QTextStream out(&file);

    //speichere Überschrift; für Dateiabfrage beim Laden benötigt
    out << "Gespeicherte Spielinformationen" << endl;

    //speichere die momentane X-Koordinate des Spielers
    out << gamePlayer->getPlayerX() << endl;
    //speichere die momentane optische Darstellung (Farbe & Muster) des Spielers
    out << gamePlayer->getPlayerStyle() << endl;

    //für jedes Element des Vektors enemies
    for (element *e:enemies) {
        //speichere die aktuelle y-Position
        out << e->rect.y() << ",";
        //speichere die aktuelle x-Position
        out << e->rect.x() << ",";
        //speichere den elementType
        out << e->elementType << endl;
    }

    //speichere den aktuellen Punktestand
    out << gamePoints << endl;
    //speichere die aktuelle Lebensanzahl
    out << leben;

    /* WICHTIG: Speicherung erfolgt chronologisch in hier definierter Reihenfolge
     * Reihenfolge muss beim Laden übereinstimmen !!! */
}

/* Festlegung der Aktion für die loadGame()-Funktion:
 * Laden eines gespeicherten Spielstandes */
void gameArea::deserialize(QFile &file)
{
    //lese die Datei über in
    QTextStream in(&file);

    //QString liest ganze Zeile und gibt sie als String zurück
    QString zeile = in.readLine();

    //Abfrage, dass es sich um eine Datei mit Spielinformationen handelt
    if (zeile != "Gespeicherte Spielinformationen")
    {
        QMessageBox::warning(this, tr("Formatfehler"),
                             tr("Das ist keine Datei mit Spielinformationen."),QMessageBox::Ok);
        return;
    }

    //lies die nächste Zeile
    zeile = in.readLine();
    //setze die X-Position des Spielers auf den Wert der ersten Zeile
    //nachdem du die erste Zeile in eine int-Variable (Zahlenwert)
    //umgewandelt hast
    gamePlayer->setPlayerX(zeile.toInt());

    //lies die nächste Zeile
    zeile = in.readLine();
    //setze den Style des Spielers auf den Wert dieser Zeile
    //nachdem du die Zeile in eine int-Variable (Zahlenwert)
    //umgewandelt hast
    gamePlayer->setPlayerStyle(zeile.toInt());


    //für jedes Element des Vektors enemies
    for (element *e:enemies) {

        //lies die nächste Zeile
        zeile = in.readLine();
        //Teile jede Zeile in 3 Teile anhand des Kommas und erstelle eine Liste
        QStringList liste = zeile.split(",");
        //erster Teil der Liste: Y-Position des Elements
        QString y = liste[0];
        //zweiter Teil der Liste: X-Position des Elements
        QString x = liste[1];
        //dritter Teil der Liste: Element-Typ
        QString typ = liste[2];

        //rufe für jedes Gegner-Element die Methode setElement() auf
        //übergebe die aus der Datei ausgelesenen und in Zahlen umgewandelte
        //Werte, um Speicherzustand auf Gegnerelemente zu übertragen
        e->setElement(x.toInt(),y.toInt(),typ.toInt());

    }

    //lies die nächste Zeile
    zeile = in.readLine();
    //setze den Punktestand des Spielers auf den Wert der Zeile
    //nachdem sie in eine int-Variable (Zahlenwert) umgewandelt wurde
    gamePoints = zeile.toInt();
    //Punkteanzeige soll nach dem Laden direkt verändert werden und
    //die gespeicherte Punktzahl anzeigen
    gamePointsLabel->setText(QString::number(gamePoints) + " Punkte");

    //lies die nächste Zeile
    zeile = in.readLine();
    //setze die Leben des Spielers auf den Wert der Zeile
    //nachdem sie in eine int-Variable (Zahlenwert) umgewandelt wurde
    leben = zeile.toInt();

    //aktualisiere das Spiel, um den gespeicherten Spielstand
    //anzuzeigen
    update();
}
