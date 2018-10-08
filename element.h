#ifndef ELEMENT_H
#define ELEMENT_H
#include <QtGui>
#include <QWidget>

/* Die Klasse element definiert die Gegnerelemente (enemies) des Spiels, sorgt durch ihre Methoden
 * für die zufällige Generierung der Objekte an zufälligen X-Positionen und für das
 * Fallen der Objekte, also ihre Bewegung auf der Y-Achse
 * Sie ist zuständig für die Definition des elementType. Von diesem hängt die Definition
 * der X- und Y-Werte, der Breite und Höhe, der Fallgeschwindigkeit auf der Y-Achse sowie
 * der Farbe, des Füllmusters, und der Außenlinie (Farbe und Breite) der Elemente ab.
 * Anhand des elementType wird auch die Form des Elements in der gameArea gezeichnet.
 */

class element
{

public:
    //Konstruktor
    element();
    //Methode zur Bestimmung eines neuen, zufälligen Elements
    void newElement();
    //Methode zum Erzeugen & Laden der Elemente (benötigt x, y und typ des Elements)
    void setElement (int x, int y, int type);
    //Methode zur Bewegung des Elements von oben nach unten ('Fallen')
    void moveElement();

    //elementTyp 0-5: Rechteck, Ellipse, Säule, Dreieck (Pie),
    //rundes Rechteck, roter Kreis
    int elementType;

    /* Layout eines Gegner-Elements */

    //Variable vom Typ QRectF, über das X- und Y-Werte sowie Breite
    //und Höhe der Enemies verwaltet werden
    QRectF rect;
    //Variable vom Typ QColor, über das Farbe der Enemies verwaltet wird
    QColor color;
    //Variable vom Typ Qt::BrushStyle, über das Muster der Enemies verwaltet wird
    Qt::BrushStyle pattern;
    //Variable vom Typ QPen, über das Außenlinie der Enemies verwaltet wird
    QPen pen;
    //Variable vom Typ int, über die Linienbreite des Pen verwaltet wird
    int penWidth;

    //Fallgeschwindigkeit eines Gegners auf der Y-Achse
    int yMovement;

};

#endif // ELEMENT_H
