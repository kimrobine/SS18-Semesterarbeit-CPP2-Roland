#include <vector>
#include <cstdlib>

#include "element.h"

/* Konstruktor der Klasse element */
element::element()
{
    //rufe die Funktion newElement auf
    newElement();

}

/* Funktion zur Erzeugung der Gegner-Elemente
 * Legt Form, Farbe und Geschwindigkeit der einzelnen Elemente fest */
void element::newElement() {

    //generiere beliebige Position auf der x-Achse
    //zwischen 0 und 499
    int xPosition = rand() % 500;

    //Festlegung der Form-Werte
    //Definiere eine Liste elemente vom Typ QRectF
    //und speichere darin 5 QRectF-Elemente
    //jeweils mit beliebiger X-Position
    //sowie Y, Breite und Höhe
    std::vector <QRectF> elements;
    //Rechteck (rectangle)
    elements.push_back(QRectF(xPosition,0,35,35));
    //Kreis (ellipse)
    elements.push_back(QRectF (xPosition,0,35,35));
    //Säule (column)
    elements.push_back(QRectF (xPosition,0,20,50));
    //Kuchenstück (pie)
    elements.push_back(QRectF (xPosition, 0, 80, 120));
    //rundes Rechteck (rounded Rect)
    elements.push_back(QRectF (xPosition, 0, 45, 40));

    //Festelgung der Farben
    //definiere eine Liste elementeFarbe vom Typ QColor
    //und speichere darin 5 QColor-Elemente
    //mit jeweils einer bestimmten Farbe
    //wichtig: gleiche Reihenfolge wie vector elemente
    //damit Farben wie gewollt & gleich zugewiesen werden
    std::vector <QColor> elementColor;
    elementColor.push_back(QColor(Qt::green));
    elementColor.push_back(QColor(Qt::magenta));
    elementColor.push_back(QColor(Qt::yellow));
    elementColor.push_back(QColor(Qt::cyan));
    elementColor.push_back(QColor("#3D828F"));

    //Festlegung der Fallgeschwindigkeit
     //definiere eine Liste fallingRate vom Typ int
    //und speichere darin 5 Zahlenwerte
    //die die Einheiten festlegen, um die sich die
    //Elemente bewegen
    //wichtig: gleiche Reihenfolge wie vector elemente
    //damit Fallgeschwindigkeit wie gewollt & gleich zugewiesen werden
    std::vector <int> fallingRate;
    //rect
    fallingRate.push_back(3);
    //ellipse
    fallingRate.push_back(10);
    //column
    fallingRate.push_back(6);
    //pie
    fallingRate.push_back(15);
    //roundedRect
    fallingRate.push_back(20);

    //generiere 5 unterschiedliche Werte von 0 bis 4
    elementType = rand() % 5;

    //generiere ein beliebiges der 5 definierten Elemente
    //durch Aufrufen der Listen mit beliebigen Wert von
    //elementType
    rect = QRectF (elements[elementType]);
    yMovement = fallingRate[elementType];
    color = QColor (elementColor[elementType]);

}

/* Funktion zur Bewegung der Gegner-Elemente */
void element::moveElement() {

    //Bewege das Element (immer vom Typ QRectF)
    //um 0, also gar nicht, auf der X-Achse
    //um einen beliebigen Wert (wird in new Element generiert) auf der Y-Achse
    rect.translate(0,yMovement);

}


