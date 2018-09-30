#ifndef ELEMENT_H
#define ELEMENT_H
#include <QtGui>
#include <QWidget>

/* Die Klasse element erstellt die Gegener im Spiel, die sich vom oberen
 * Spielfeldrand in unterschiedlichen Geschwindigkeiten nach unten bewegen
 * und denen der player ausweichen muss, um 'am Leben' zu bleiben und keine
 * Leben zu verlieren
 */

class element
{

public:
    //Konstruktor
    element();
    //erzeuge ein neues Element
    void newElement();
    //bewege das Element
    void moveElement();
    //Objekt vom Typ QRectF, über das Enemies verwaltet werden
    QRectF rect;
    //Objekt vom Typ QColor, über das Farbe der Enemies verwaltet wird
    QColor color;
    //Bewegung eines Elements auf der Y-Achse
    int yMovement;
    //elementTyp 0-4: grünes Rect, pinker Kreis, gelbe Säule,
    //cyan Pie, dunkeltürkises rundes Rechteck
    int elementType;
};

#endif // ELEMENT_H
