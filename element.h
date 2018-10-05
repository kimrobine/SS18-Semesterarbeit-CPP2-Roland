#ifndef ELEMENT_H
#define ELEMENT_H
#include <QtGui>
#include <QWidget>

/* Die Klasse element erstellt die Gegener (enemies) im Spiel, sorgt durch ihre Methoden
 * für die zufällige Generierung der Objekte an zufälligen X-Positionen und für das
 * Fallen der Objekte, also ihre Bewegung auf der Y-Achse
 * Sie ist zuständig für die Definition des elementType. Von diesem hängt die Definition
 * der X- und Y-Werte, der Breite und Höhe, der Fallgeschwindigkeit auf der Y-Achse sowie
 * der Farbe, des Füllmusters, und der Außenlinie (Farbe und Breite) der Objekte ab.
 * Anhand des elementType wird die Form des Elements in der gameArea gezeichnet
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

    //elementTyp 0-4: grünes Rect, pinker Kreis, gelbe Säule,
    //cyan Pie, dunkeltürkises rundes Rechteck
    int elementType;

    //Fallgeschwindigkeit eines Gegeners auf der Y-Achse
    int yMovement;

    /* Layout eines Gegner-Elements */

    //Objekt vom Typ QRectF, über das X- und Y-Werte sowie Breite
    //und Höhe derEnemies verwaltet werden
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
