#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <gamearea.h>
#include <player.h>

/* Die Klasse gameWidget erstellt das Spielfenster, die Buttons und ihre verknüpften Funktionen
 * sowie den Punkte-Counter und intialisiert das Zeichenfeld, in dem das Spiel stattfindet (gameArea)
 * auf Basis der Klasse gameArea
 */

class gameWidget : public QWidget
{
    Q_OBJECT //Makro, Klasse enthält QT spezifische Anweisungen

public:
    gameArea *myGameArea;
    gameWidget(QWidget *parent = 0);
    QLabel *getGamePoints(){return gamePoints;}

private:
    QPushButton *startstop;
    QLabel *gamePoints;

private slots:
    void startStop(void);
    void saveGame(void);
    void loadGame(void);
};

#endif // GAMEWIDGET_H
