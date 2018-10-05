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
    //(tritt beim Schneiden zweier Elemente und leben==0 ein, siehe drawEnemies-Funktion)
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
            //die Leben & Spieler-Darstellung werden erst nach dem Ende des Timers
            //zurückgesetzt, damit während des gameOver-Timeouts Lebensanzeige leer ist
            //und Spieler abgeschwächt dargestellt bleibt
            leben = 3;
            //Spielerdarstellung auf Darstellung bei vollen Leben zurücksetzen
            gamePlayer->setPlayerStyle(0);
            //nach dem gameOverTimeout beginnt das Spiel wieder
            setRunning(true);
        }
    }

}


/* Lebensanzeige */
void gameArea::drawLives(QPainter &painter) {

    //Definition von 3 QRectF-Objekten
    //mit Koordinaten (X,Y) und Abmessungen (Breite,Höhe)
    QRectF live1(600,20,30,30),live2(635,20,30,30),live3(670,20,30,30);

    //Füllung des Lebens-Objekts bei vorhandenem Leben
    QBrush liveFull (Qt::red);
    //Keine Füllung bei Verlust des Lebens
    Qt::BrushStyle liveLost = Qt::NoBrush;

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
        //Zeichne das erste Leben als leeren Rahmen
        painter.setBrush(liveLost);
        painter.drawEllipse(live1);
        painter.setBrush(liveFull);
        painter.drawEllipse(live2);
        painter.drawEllipse(live3);
    }

    //Bei Verlust des 2. Lebens:
    if (leben ==1) {
        //Zeichne das 1. Leben als leeren Rahmen
        //Zeichne das 2. Leben als leeren Rahmen
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
        //Nutzung der player-class Methode setPlayerStyle
        //und übergeben des Zahlenwertes zur Bestimmung des Style-Typs
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
        //sehr helles blau, leerer Rahmen
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

        //definiere Pointer-Objekt e
        //alle Elemente aus enemies an Stelle i lassen sich durch e verwalten
        element* e = enemies[i];

        //definiere Brush für Verwendung
        //elementabhängiger Farbe & Muster
        QBrush enemyBrush (e->color,e->pattern);
        painter.setBrush(enemyBrush);

        //definiere Pen für Verwendung
        //elementabhängiger PenFarbe & PenDicke
        QPen enemyPen (e->pen);
        enemyPen.setWidth(e->penWidth);
        painter.setPen(enemyPen);

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
        case 5:
            painter.drawEllipse(e->rect);
            break;
        }

        //Bewege alle Elemente in der Liste enemies
        e->moveElement();

        //Definition eines neuen QRectF-Elements
        //--> wird benötigt für Kollisionsabfrage mit intersects();-Methode
        //Gleichsetzung mit playerRect
        QRectF player(gamePlayer->getPlayerX(),gamePlayer->getPlayerY(),gamePlayer->getPlayerWidth(), gamePlayer->getPlayerHeight());

        //Definition eines neuen QRectF-Elements
        //als Verwaltungselement für enemies
        QRectF enemyRect (e->rect);

        //türkises pie-Element soll auch intersecten
        //Breite und Höhe müssen reduziert werden
        //da es sich sonst zu früh mit dem player schneidet
        if (e->elementType == 3) {
            enemyRect.setHeight(40);
            enemyRect.setWidth(50);
        }

        //wenn ein Element aus der Liste enemies mit dem Spieler kollidiert
        if (enemyRect.intersects(player) && unverwundbar==false) {

            //mache den Spieler unverwundbar (startet den unverwundbar-Timer)
            unverwundbar=true;
            //der Spieler wurde getroffen (startet den getroffen-Timer)
            getroffen=true;
            //pausiere das Spiel
            setRunning(false);

            /* --- Definition Aktion lebenregenerierender Kreis --- */

            //wenn es sich bei dem elementType 5, also um den roten Kreis handelt
            if (e->elementType==5) {
                //und der Spieler nicht über alle Leben verfügt
                if (leben!=3){
                    //addiere ein Leben bei der Kollision von rotem Kreis und Spieler
                    //statt eines zu entfernen
                    leben++;

                    //sorge für Wiederherstellung der Darstellung des Players
                    changePlayerStyle();

                }
                //verfügt der Spieler über volle Leben
                else {
                    //bleiben Leben unverändert
                    leben = 3;
                }
            }
            //bei jedem anderen enemy-Objekt
            else {
                //ziehe ein Leben ab
                leben--;

            }

            /* --- Ende Definition Aktion lebenregenerierender Kreis --- */

            //sorge für abgeschwächte Darstellung des Players
            changePlayerStyle();


            //wenn keine Leben mehr übrig sind
            if (leben==0) {
                //ist das Spiel vorbei
                //rufe die gameOver-Methode auf
                gameIsOver();
            }
        }


        //wenn das aktuelle Gegner-Rect die gameArea verlässt
        //die Y-Koordinate also größer als 700 ist
        if (e->rect.y() > 700) {
            //erzeuge ein neues zufälliges Element
            e->newElement();

        }
    }

}


/* Paint-Methode, um Zeichnen-Methoden der Lebensanzeige & der fallende Objekte
 * auszulösen und Zustände der Unverwundbarkeit des Spielers zu regeln */
void gameArea::paintEvent(QPaintEvent * ){
    QPainter painter;

    painter.begin(this);

    //solange Leben vorhanden sind
    for (int i =0; i <= leben; i++) {
        //rufe die Methode zum Zeichnen der Leben auf
        drawLives(painter);
    }

    //wenn gameOver=false ist, das Spiel also aktiv ist
    if (!gameOver){
        //rufe die Methode zum Zeichnen der fallenden Gegner-Objekte auf
        drawEnemies(painter);
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
            //und der Spieler ist nicht mehr unverwundbar
            unverwundbar = false;
        }
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
    //Label soll child-Element des Widger sein
    gOText->setParent(this);
    //Festlegung der Schriftart & Schriftgröße
    gOText->setFont(QFont("Helvetica", 34));
    //Nutzung der QWidget-Funktion move()
    //um Text innerhalb der gameArea zu platzieren
    gOText->move(350-120, 0);
    //Labeltext anzeigen
    gOText->show();

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

    //Lösche die aktuellen Gegener
    //und generiere neue Gegener
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
    if (run) {
        //lege die Hintergrundfarbe auf dunkelgrau fest
        setPalette(QPalette(QColor (70,70,70)));
        setAutoFillBackground(true);

    }

    //wenn Spiel nicht läuft
    else {
        //lege die Hintergrundfarbe auf hellgrau fest
        setPalette(QPalette(QColor (190,190,190)));
        setAutoFillBackground(true);
    }
}



/* Festlegung der Aktion für die saveGame()-Funktion:
 * Speicherung des aktuellen Spielstandes */
void gameArea::serialize(QFile &file)
{
    //exportiere die Daten mit out in die Datei
    QTextStream out(&file);

    //speichere die momentane X-Koordinate des Spielers
    out << gamePlayer->getPlayerX() << endl;
    //speichere die momentane optische Darstellung (Farbe & Muster) des Spielers
    out << gamePlayer->getPlayerStyle() << endl;

    //für jedes Objekt des Vektors enemies auf Basis der Klasse element
    for (element *e:enemies) {
        //speichere die aktuelle y-Position
        out << e->rect.y() << ",";
        //speichere die aktuelle y-Position
        out << e->rect.x() << ",";
        //speichere den elementType des Elements
        out << e->elementType << endl;
    }
    //speichere den aktuellen Punktestand
    out << gamePoints << endl;
    //speichere die aktuelle Lebensanzahl
    out << leben;

    /* WICHTIG: Speicherung erfolgt chronologisch in hier definierter Reihenfolge
     * Reihenfolge muss beim Laden demnach übereinstimmen !!! */
}

/* Festlegung der Aktion für die loadGame()-Funktion:
 * Laden eines gespeicherten Spielstandes */
void gameArea::deserialize(QFile &file)
{
    //lese die Datei ein
    QTextStream in(&file);

    //QString liest ganze Zeile und gibt sie als String zurück
    QString zeile = in.readLine();
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


    //für jedes Objekt des Vektors enemies auf Basis der Klasse element
    for (element *e:enemies) {

        //lies die nächste Zeile
        zeile = in.readLine();
        //Teile jede Zeile in 3 Teile anhand des Kommas und erstelle eine Liste
        QStringList liste = zeile.split(",");
        //erster Teil der Liste: Y-Position des Elements
        QString y = liste[0];
        //zweiter Teil der Liste: X-Position des Elements
        QString x = liste[1];
        //dritter Teil der Liste: Elementtyp
        QString typ = liste[2];

        //rufe für jedes Enemies-Element die Funktion setElement() auf
        //nutze so die aus der Datei ausgelesenen Werte, um die Gegnerelemente
        //zu verändern
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
    //zu laden
    update();
}
