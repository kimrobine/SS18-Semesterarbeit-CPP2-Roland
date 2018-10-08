#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QWidget>
#include <QKeyEvent>

#include "gamearea.h"

/* Die Klasse player beinhaltet die nötigen Methoden zur Erzeugung und Bewegung des Spieleravatars:
 * setter und getter für die Positions-, Größen- und Schrittweitenfestlegung sowie für die
 * veränderte Darstellung in Farbe und Füllmuster; paint- und keyPressEvent zur Zeichnung und
 * Bewegungsfähigkeit des Spielers in der gameArea.
 * Die Klasse movement dient als Hilfsklasse für die player-Klasse und definiert die Bewegungen des
 * Spielers in einem enum, um sie später in der movePlayer()-Methode verwenden zu können
 * Player ist angelehnt an folgendes Beispiel: https://www.badprog.com/c-qt-framework-moving-a-shape-with-arrow-keys
 */

/* Hilfsklasse für Bewegung des Spielers */
class movement {
public:
    //enumeration für switch-case der movePlayer()-Methode
    enum playerMovement {
        playerGoesLeft,
        playerGoesRight
    };

public:
    //virtuell = dynamisch änderbar, nicht statisch
    //Dekonstruktor der Klasse Movement
    virtual ~movement();
    //Initalisierung der virtuellen movePlayer-Methode
    virtual void movePlayer(playerMovement) = 0;
};

/* Klasse für Erzeugung und Bewegung des Spielers */
class player : public QWidget, public movement
{
public:
    //Konstruktor
    player(QWidget *parent = 0);
    //Methode für die links-rechts-Bewegung des Spielers
    void movePlayer(playerMovement);

    /* Set- und Get-Methoden für die Position des Spielers */
    void setPlayerX(int pX);
    int getPlayerX() const;
    void setPlayerY(int pY);
    int getPlayerY() const;

    /* Set- und Get-Methoden für die Schrittweite des Spielers */
    int getPlayerMove() const;
    void getPlayerMove(int pMove);

    /* Set- und Get-Methoden für Breite und Höhe des Spielers */
    void setPlayerWidth(int pWidth);
    int getPlayerWidth() const;
    void setPlayerHeight(int pHeight);
    int getPlayerHeight() const;

    /* Set- und Get-Methoden für wechselnde optische
     * Darstellung des Spielers. Benötigt für Stufe III:
     * abgeschwächte Darstellung bei Lebensverlust */
    void setPlayerColor(QColor c);
    QColor getPlayerColor();
    void setPlayerPattern (Qt::BrushStyle s);
    Qt::BrushStyle getPlayerPattern();
    void setPlayerStyle(int pType);
    int getPlayerStyle();


protected:
    /* Methode für Auslösung der Bewegungsfunktion
     * über Pfeiltasten */
    void keyPressEvent(QKeyEvent *keyEvent);

    /* Paint-Methode zum Zeichnen des Spielers */
    void paintEvent(QPaintEvent *event);

private:
    /* Variablen für Speicherung der Spieler-Eigenschaften */

    //X-Position
    int playerX;
    //Y-Position
    int playerY;
    //Schrittweite der Bewegung
    int playerMove;
    //Breite des Spieler-Rechtecks
    int playerWidth;
    //Höhe des Spieler-Rechtecks
    int playerHeight;

    //optische Darstellung des Spielers
    //0=volle Leben, 1= abgeschwächt, 2=leerer Rahmen
    int playerStyle;
    //Farbe
    QColor playerColor;
    //Muster
    Qt::BrushStyle playerPattern;

};

#endif // PLAYER_H
