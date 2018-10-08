#include <vector>
//für rand()-Methode benötigt
#include <cstdlib>

#include "element.h"


/* Konstruktor der Klasse element */
element::element()
{
    //rufe die Methode newElement auf
    newElement();

}

/* Methode zur Bestimmung der Gegner-Elemente */
void element::newElement() {

    //Wahrscheinlichkeit für roten lebenaddierenden Kreis
    int wahrscheinlichkeit = 10;
    //generiere 100 unterschiedliche Werte von 0 bis 99
    int zufall = rand() % 100;

    //der Kreis (elementType = 5) soll mit 10% Wahrscheinlichkeit generiert werden
    if (zufall < wahrscheinlichkeit) {
        elementType = 5;

    }
    //alle andere Elemente sollen zufällig erzeugt werden
    else {
        //generiere 5 unterschiedliche Werte von 0 bis 4
        //des elementType
        elementType = rand() % 5;
    }

    //generiere beliebige Position auf der x-Achse
    //zwischen 0 und 639
    int xPosition = rand() % 640;

    //Aufruf der setElement-Methode, um Gegner-Elemente an beliebiger
    //X-Position, überhalb des Spielfeldes und mit einem zufälligen Typ
    //zu erzeugen. Initalisierung mit y= -200, damit Elemente bei Spielstart
    //nicht angezeigt werden und erst durch die moveElement-Methode
    //'ins Spiel fallen'
    setElement(xPosition, -200, elementType);

}

/* Methode zur Erzeugung der Gegnerelemente
 * Legt Form, Farbe und Geschwindigkeit der einzelnen Elemente fest */
void element::setElement (int x, int y, int type) {

    //bestimmter Type (0-5) wurde übergeben
    //und elementType wird auf gleichen Wert gesetzt
    elementType = type;

    //Festlegung der Positionen und Abmessungen für die Form:
    //Definiere eine Liste elements vom Typ QRectF
    //und speichere darin 5 QRectF-Elemente
    //jeweils mit X- und Y-Position, Breite und Höhe
    //Reihenfolge für folgende Vektoren wichtig!
    std::vector <QRectF> elements;
    //Rechteck
    elements.push_back(QRectF(x,y,35,35));
    //lange Ellipse
    elements.push_back(QRectF (x,y,30,50));
    //Säule
    elements.push_back(QRectF (x,y,20,50));
    //Dreieck (pie)
    elements.push_back(QRectF (x, y, 60, 70));
    //rundes Rechteck
    elements.push_back(QRectF (x, y, 45, 40));
    //lebenaddierender roter Kreis
    elements.push_back(QRectF (x, y, 30, 30));

    //Festlegung der Farben:
    //Definiere eine Liste elementColor vom Typ QColor
    //und speichere darin 5 QColor-Elemente
    //mit jeweils einer bestimmten Farbe
    //wichtig: gleiche Reihenfolge wie vector 'elements'
    //damit Farben richtig zugewiesen werden
    std::vector <QColor> elementColor;
    //Rechteck
    elementColor.push_back(QColor("#227D4D"));
    //lange Ellipse
    elementColor.push_back(QColor("#BDA9BB"));
    //Säule
    elementColor.push_back(QColor("#E2BD5F"));
    //Dreieck (pie)
    elementColor.push_back(QColor("#A0D1CE"));
    //rundes Rechteck
    elementColor.push_back(QColor("#3D828F"));
    //lebenaddierender roter Kreis
    elementColor.push_back(QColor(Qt::red));

    //Festlegung der Pen-Farbe:
    //Definiere eine Liste elementPen vom Typ QPen
    //und speichere darin 5 QPen-Elemente
    //mit jeweils einer bestimmten Pen-Farbe
    //wichtig: gleiche Reihenfolge wie vector 'elements'
    //damit Pen richtig zugewiesen wird
    std::vector <QPen> elementPen;
    //Rechteck
    elementPen.push_back(QPen("#227D4D"));
    //lange Ellipse
    elementPen.push_back(QPen("#BDA9BB"));
    //Säule
    elementPen.push_back(QPen("#E2BD5F"));
    //Dreieck (pie)
    elementPen.push_back(QPen("#A0D1CE"));
    //rundes Rechteck
    elementPen.push_back(QPen("#3D828F"));
    //lebenaddierender roter Kreis
    elementPen.push_back(QPen(Qt::red));

    //Festlegung der Pen-Breite:
    //Definiere eine Liste elementPenWidth vom Typ int
    //und speichere darin 5 int-Elemente
    //mit jeweils einem bestimmten Zahlenwert
    //für die Breite der Außenlinie eines Objektes
    //wichtig: gleiche Reihenfolge wie vector 'elements'
    //damit Penbreite richtig zugewiesen wird
    std::vector <int> elementPenWidth;
    //Rechteck
    elementPenWidth.push_back(4);
    //lange Ellipse
    elementPenWidth.push_back(4);
    //Säule
    elementPenWidth.push_back(3);
    //Dreieck (pie)
    elementPenWidth.push_back(3);
    //rundes Rechteck
    elementPenWidth.push_back(4);
    //lebenaddierender roter Kreis
    elementPenWidth.push_back(2);

    //Festlegung des BrushStyle:
    //Definiere eine Liste elementBrush vom Typ Qt::BrushStyle
    //und speichere darin 5 Qt::BrushStyle-Elemente
    //mit jeweils einem bestimmten Pattern (Muster)
    //wichtig: gleiche Reihenfolge wie vector 'elements'
    //damit BrushStyles richtig zugewiesen werden
    std::vector <Qt::BrushStyle> elementBrush;
    //Rechteck
    elementBrush.push_back(Qt::BrushStyle(Qt::Dense3Pattern));
    //lange Ellipse
    elementBrush.push_back(Qt::BrushStyle(Qt::Dense3Pattern));
    //Säule
    elementBrush.push_back(Qt::BrushStyle(Qt::Dense3Pattern));
    //Dreieck (pie)
    elementBrush.push_back(Qt::BrushStyle(Qt::Dense3Pattern));
    //rundes Rechteck
    elementBrush.push_back(Qt::BrushStyle(Qt::Dense3Pattern));
    //lebenaddierender roter Kreis
    elementBrush.push_back(Qt::BrushStyle(Qt::SolidPattern));

    //Festlegung der Fallgeschwindigkeit
    //Definiere eine Liste fallingRate vom Typ int
    //und speichere darin 5 Zahlenwerte, die festlegen,
    //um wie viele Einheiten (wie schnell) sich die
    //Elemente bewegen
    //wichtig: gleiche Reihenfolge wie vector 'elements'
    //damit Fallgeschwindigkeit richtig zugewiesen wird
    std::vector <int> fallingRate;
    //Rechteck
    fallingRate.push_back(4);
    //lange Ellipse
    fallingRate.push_back(8);
    //Säule
    fallingRate.push_back(6);
    //Dreieck (pie)
    fallingRate.push_back(14);
    //rundes Rechteck
    fallingRate.push_back(18);
    //lebenaddierender roter Kreis
    fallingRate.push_back(10);

    //generiere ein beliebiges der 6 definierten Elemente
    //durch Aufrufen der Vectoren mit dem zuvor in newElement()
    //generiertem Wert von elementType
    rect = QRectF (elements[elementType]);
    color = QColor (elementColor[elementType]);
    pattern = Qt::BrushStyle (elementBrush[elementType]);
    pen = QPen (elementPen[elementType]);
    penWidth = int (elementPenWidth[elementType]);
    yMovement = fallingRate[elementType];

}

/* Methode zur Bewegung der Gegner-Elemente */
void element::moveElement() {

    //Bewege das Element (immer rect vom Typ QRectF)
    //auf der X-Achse: um 0, also gar nicht
    //auf der Y-Achse: mit der jeweiligen Fallgeschwindigkeit
    //(wird in setElement über elementType zugewiesen)
    rect.translate(0,yMovement);

}
