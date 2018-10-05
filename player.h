#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QWidget>
#include <QKeyEvent>

#include "gamearea.h"

/* Die Klasse player beinhaltet die nötigen Funktionen zur Erzeugung und Bewegung des Spieleravatars:
 * setter und getter für die Positions- und Schrittweitenfestlegung des Spielers,
 * setter und getter für die veränderte Darstellung des Spielers in Farbe und Füllmuster
 * paint- und keyPressEvent zur Zeichnung und Bewegungsfähigkeit in der gameArea
 * Die Klasse Movement dient als Hilfsklasse für die player-Klasse und definiert
 * die Bewegungen des Players in einem enum, um sie später in der movePlayer()-Funktion
 * verwenden zu können, und initalisiert die movePlayer()-Funktion der player-Klasse dynamisch,
 * mit dem enum und einem Ausgangswert
 * Player-Bewegung ist angelehnt an folgendes Beispiel:
 * https://www.badprog.com/c-qt-framework-moving-a-shape-with-arrow-keys
 */

/* Hilfsklasse für Bewegung des Spielers */
class Movement {
public:
    //enumeration für switch-case der movePlayer-Methode
    enum playerMovement {
        playerGoesLeft,
        playerGoesRight
    };

public:
    //Dekonstruktor der Klasse Movement
    virtual ~Movement();
    //initalisierung der virtuellen movePlayer-Methode
    //virtuell = Methode dynamisch änderbar, nicht statisch
    virtual void movePlayer(playerMovement) = 0;
};

/* Klasse für Generierung und Bewegung des Spielers */
class player : public QWidget, public Movement
{
public:
    //Konstruktor
    player(QWidget *parent = 0);
    //Methode für die links-rechts-Bewegung des Spielers
    //basierend auf enum der Klasse Movement
    void movePlayer(playerMovement);

    /* Set- und Get-Methoden für die Position des Spielers */
    void setPlayerX(int pX);
    int getPlayerX() const;
    void setPlayerY(int pY);
    int getPlayerY() const;

    /* Set- und Get-Methoden für die Schrittweite des Spielers */
    int getPlayerMove() const;
    void getPlayerMove(int pMove);

    /* Set- und Get-Methoden für die Breite und Höhe des
     * Spielers */
    void setPlayerWidth(int pWidth);
    int getPlayerWidth() const;
    void setPlayerHeight(int pHeight);
    int getPlayerHeight() const;

    /* Set- und Get-Methoden für wechselnde optische
     * Darstellung des Spielers. Benötigt für Stufe II:
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
    //Breite (des Spieler-Rechtecks)
    int playerWidth;
    //Höhe (des Spieler-Rechtecks)
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
