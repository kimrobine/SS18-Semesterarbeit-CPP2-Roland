#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QWidget>
#include <QKeyEvent>

/* Die Klasse player beinhaltet die nötigen Funktionen zur Erzeugung und Bewegung des Spieleravatars:
 * getter und setter-Methoden für die Positions- und Schrittweitenfestlegung des Spielers,
 * paint- und keyPressEvent zur Erzeugung und Bewegungsfähigkeit in der gameArea
 * Die Klasse Movement dient als Hilfsklasse für die player-Klasse und definiert die Bewegungen des Players
 * in einem enum, um sie später in der move()-Funktion verwenden zu können, und initalisiert die move()-Funktion
 * der player-Klasse dynamisch, mit dem enum und einem Ausgangswert
 */

/* Hilfsklasse für Bewegung des player */
class Movement {
public:
    enum playerMovement {
        playerGoesLeft,
        playerGoesRight
    };

public:
    virtual ~Movement();
    virtual void move(playerMovement) = 0;
};

/* Klasse für Generierung und Bewegung des player */
class player : public QWidget, public Movement
{
public:
    player(QWidget *parent = 0);
    void move(playerMovement);

    void setPlayerX(int pX);
    int getPlayerX() const;
    void setPlayerY(int pY);
    int getPlayerY() const;
    int getPlayerMove() const;
    void getPlayerMove(int pMove);

    void setPlayerWidth(int pWidth);
    int getPlayerWidth() const;
    void setPlayerHeight(int pHeight);
    int getPlayerHeight() const;


protected:
    void keyPressEvent(QKeyEvent *keyEvent);
    void paintEvent(QPaintEvent *event);

private:
    int playerX;
    int playerY;
    int playerMove;
    int playerWidth;
    int playerHeight;
};

/* Angelehnt an folgendes Beispiel: https://www.badprog.com/c-qt-framework-moving-a-shape-with-arrow-keys */

#endif // PLAYER_H
