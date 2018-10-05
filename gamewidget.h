#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include "gamearea.h"
#include "player.h"

/* Die Klasse gameWidget erstellt das Spielfenster, die Buttons und ihre verknüpften Funktionen,
 * den Punkte-Counter und intialisiert das Zeichenfeld, in dem das Spiel stattfindet (gameArea)
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

    //Deklaration des Zeichenfeldes myGameArea
    //auf Basis der Klasse gameArea
    gameArea *myGameArea;

private:
    //Buttons innerhalb des Spiels

    //um das Spiel zu starten & stoppen
    QPushButton *startStopButton;
    //um das Spiel zu starten & stoppen
    QPushButton *saveButton;
    //um das Spiel zu starten & stoppen
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
