#ifndef ELEMENT_H
#define ELEMENT_H
#include <QtGui>
#include <QWidget>

/* Die Klasse element erstellt die Gegener (enemies) im Spiel, die sich vom oberen
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
    //setze x, y und typ des Elements (für Erzeugen & Laden benötigt)
    void setElement (int x, int y, int type);

    //Fallgeschwindigkeit eines Gegeners auf der Y-Achse
    int yMovement;
    //elementTyp 0-4: grünes Rect, pinker Kreis, gelbe Säule,
    //cyan Pie, dunkeltürkises rundes Rechteck
    int elementType;

    /* Layout eines Gegner-Elements */
    //Objekt vom Typ QRectF, über das Enemies verwaltet werden
    QRectF rect;
    //Objekt vom Typ QColor, über das Farbe der Enemies verwaltet wird
    QColor color;
    //Objekt vom Typ Qt::BrushStyle, über das Muster der Enemies verwaltet wird
    Qt::BrushStyle pattern;
    //Objekt vom Typ QPen, über das Außenlinie der Enemies verwaltet wird
    QPen pen;
    //Variable vom Typ int, über die Linienbreite des Pen verwaltet wird
    int penWidth;

};

#endif // ELEMENT_H
