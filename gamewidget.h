#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include "gamearea.h"
#include "player.h"

/* Die Klasse gameWidget definiert das Spielfenster, die Buttons und ihre verknüpften Funktionen,
 * den Punkte-Counter und legt den Bereich für das Zeichenfeld fest, in dem das Spiel stattfindet,
 * auf Basis der Klasse gameArea
 */

class gameWidget : public QWidget
{
    Q_OBJECT
    //Makro-Anweisung, enthält QT spezifische Befehle
    //wird benötigt, um slots nutzen zu können

public:
    //Konstruktor
    gameWidget(QWidget *parent = 0);

    //Spielfeld myGameArea
    //auf Basis der Klasse gameArea
    gameArea *myGameArea;

private:
    //Buttons innerhalb des Spiels

    //um das Spiel zu starten & stoppen
    QPushButton *startStopButton;
    //um das Spiel zu speichern
    QPushButton *saveButton;
    //um ein gespeichertes Spiel zu laden
    QPushButton *loadButton;
    //um die Anwendung zu beenden & das Widget zu schließen
    QPushButton *endButton;

    //Label für die Punkteanzeige
    QLabel *gamePoints;

private slots:   
    //Funktionen, um Spiel zu steuern

    //Spiel starten & pausieren
    void startStopGame(void);
    //Spiel speichern
    void saveGame();
    //Spiel laden
    void loadGame();
};

#endif // GAMEWIDGET_H
