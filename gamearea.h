#ifndef GAMEAREA_H
#define GAMEAREA_H
#include <QMainWindow>
#include <QFile>
#include <QLabel>
#include <vector>

#include "player.h"
#include "element.h"

/* Die Klasse gameArea erstellt das Zeichenfeld, in dem sich der player und die Objekte bewegen,
 * und ist für den Timer und die Punkteanzeige zuständig
 */

//Namespace für Klasse gameArea festelgen
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
    //Methode, die Speicherung des Spiels definiert
    void serialize(QFile &file);
    //Methode, die Laden des Spiels definiert
    void deserialize(QFile &file);

    //set- und get-Methoden, die den Spielzustand (aktiv & inaktiv) regeln
    void setRunning(bool run);
    bool getRunning() {return running;}

    //Methode, um Punktelabel mit Punktevariable zu verknüpfen
    void setGamePoints(QLabel *gamePoints){gamePointsLabel = gamePoints;}

    //Methode, um Gegner in die gameArea zu integrieren
    void drawEnemies(QPainter& painter);
    //Methode, um Lebensanzeige in die gameArea zu integrieren
    void drawLives(QPainter& painter);
    //Methode, die (abgeschwächte) Darstellung des Spielers regelt
    void changePlayerStyle();
    //Methode, die die gameOver-Anzeige & Spielzurücksetzung regelt
    void gameIsOver();

    //erstellt Vectorliste vom Typ element mit dem Namen enemies
    std::vector<element*> enemies;

private:
    //Namespace-Variable
    Ui::gameArea *ui;

    //Deklaration des Spielers auf Basis der Klasse player
    player *playerRect;
    //Deklaration des Spielers auf Basis der QT-Klasse QTimer
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

    //Zustände der Spieler-Gegener-Interaktion
    //mögliche Werte: true oder false
    bool unverwundbar;
    bool getroffen;
    bool gameOver;

    //Punkte & Leben speichern
    int gamePoints;
    int leben;

    //Timer für Timeouts, die eintreten
    //wenn der Spieler getroffen wurde
    int unverwundbarTimer;
    int getroffenTimer;
    int gameOverTimer;

    //Defintion der Timeout-Länge
    //für das jeweilige Ereignis
    const int unverwundbarTimeout = 30;
    const int getroffenTimeout = 50;
    const int gameOverTimeout = 120;


private slots:
    //Methode, um Spiel mit dem Timer regelmäßig zu aktualisieren
    void updateGame();

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // GAMEAREA_H
