#ifndef GAMEAREA_H
#define GAMEAREA_H
#include <QMainWindow>
#include <QFile>
#include <QLabel>
#include <vector>

#include "player.h"
#include "element.h"

/* Die Klasse gameArea definiert das Zeichenfeld des Spiels, in dem sich der Spieler
 * und die Gegner bewegen. Sie ist zuständig für: den Timer und die Punkteanzeige,
 * die Aktualisierung, das Pausieren und das gameOver des Spiels, für das Zeichnen der
 * Gegner und der Leben, für die Kollisionsabfrage von Spieler und Gegnern sowie
 * für das Auslösen der veränderten Darstellung des Spielers bei einer Kollision
 * Die Klasse regelt sozusagen alles, was innerhalb des Spiels passiert
 */

//Namespace für gameArea festelgen
namespace Ui {
class gameArea;
}

//Deklaration der Klasse gameArea als child-Element von QMainWindow
class gameArea : public QMainWindow
{
    Q_OBJECT
    //Makro-Anweisung, enthält QT spezifische Befehle
    //wird benötigt, um slots nutzen zu können

public:
    //Konstruktor
    explicit gameArea(QWidget *parent = 0);
    //Dekonstruktor
    ~gameArea() { }

    //Methode, um Punktelabel mit Punktevariable zu verknüpfen
    void setGamePoints(QLabel *gamePoints){gamePointsLabel = gamePoints;}

    //Methode, um Lebensanzeige in die gameArea zu integrieren
    void drawLives(QPainter &painter);
    //Methode, die optische Darstellung des Spielers verändert
    void changePlayerStyle();
    //Methode, um Gegner in die gameArea zu integrieren
    void drawEnemies(QPainter &painter);

    //Methode, die die gameOver-Anzeige & Spielzurücksetzung regelt
    void gameIsOver();

    //set- und get-Methoden, die den Spielzustand (aktiv & inaktiv) regeln
    void setRunning (bool run);
    bool getRunning() {return running;}

    //Methode, die Speicherung der Spielinformationen definiert
    void serialize(QFile &file);
    //Methode, die Laden (Auslesen) der Spielinformationen ermöglicht
    void deserialize(QFile &file);

    //Vector vom Datentyp element (auf Basis der Klasse element)
    //mit Namen 'enemies' --> Liste der Gegnerelemente
    std::vector<element*> enemies;

private:
    //Für Definition des Namespace
    Ui::gameArea *ui;

    //Deklaration des Spielers auf Basis der Klasse player
    player *gamePlayer;
    //Deklaration des Spieltimers auf Basis der Qt-Klasse QTimer
    QTimer *timer;

    //Label
    //für Punkteanzeige
    QLabel *gamePointsLabel;
    //für GameOver-Text
    QLabel *gOText;
    QLabel *gOText2;
    //für GameOver-Punkteanzeige
    QLabel *gOPoints;

    //bool-Variable für Spielzustand
    //mögliche Werte: true oder false
    bool running;

    //Zustände des Spielers
    //mögliche Werte: true oder false
    bool unverwundbar;
    bool getroffen;
    bool gameOver;

    //Variablen, um Punkte & Leben zu speichern
    int gamePoints;
    int leben;

    //Timer für Timeouts, die eintreten
    //wenn der Spieler von einem Gegner getroffen wurde
    int unverwundbarTimer;
    int getroffenTimer;
    int gameOverTimer;

    //Defintion der Timeout-Länge
    //für den jeweilige Spielerzustand
    const int unverwundbarTimeout = 30;
    const int getroffenTimeout = 50;
    const int gameOverTimeout = 120;


private slots:
    //Methode, um Spiel zu aktualisieren
    void updateGame();

protected:
    //Methode, die Zeichnung von Gegnern und Leben auslöst
    void paintEvent(QPaintEvent *event);

};

#endif // GAMEAREA_H
