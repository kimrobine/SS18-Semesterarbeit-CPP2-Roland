#include <vector>
#include <cstdlib>

#include "element.h"

/* Konstruktor der Klasse element */
element::element()
{
    //rufe die Funktion newElement auf
    newElement();

}

/* Methode zur Erzeugung der Gegner-Elemente */
void element::newElement() {

    //Wahrscheinlichkeit für roten lebenaddierenden Kreis
    int wahrscheinlichkeit = 10;
    //generiere 100 unterschiedliche Werte von 0 bis 99
    int zufall = rand() % 100;

    //der Kreis soll mit 10% Wahrscheinlichkeit generiert werden
    if (zufall < wahrscheinlichkeit) {
        elementType = 5;
        //ansonsten sollen andere Elemente zufällig erzeugt werden
    } else {
        //generiere 5 unterschiedliche Werte von 0 bis 4
        //des elementType
        elementType = rand() % 5;
    }

    //generiere beliebige Position auf der x-Achse
    //zwischen 0 und 499
    int xPosition = rand() % 670;

    //Aufrug der setElement-Methode, um Gegner-Elemente zu erzeugen
    //Initalisierung mit y= -100, damit Elemente nicht angezeigt werden
    setElement(xPosition, -200, elementType);

}

/* Methode zur Bewegung der Gegner-Elemente */
void element::moveElement() {

    //Bewege das Element (immer vom Typ QRectF)
    //um 0, also gar nicht, auf der X-Achse
    //um einen beliebigen Wert (wird in new Element generiert) auf der Y-Achse
    rect.translate(0,yMovement);

}

/* Legt Form, Farbe und Geschwindigkeit der einzelnen Elemente fest */
void element::setElement (int x, int y, int type) {

    //bestimmter Type (0-5) wird dieser Funktion übergeben
    //und elemenType wird auf gleichen Wert gesetzt
    elementType = type;

    //Festlegung der Positionen und Abmessungen für die Form
    //Definiere eine Liste elemente vom Typ QRectF
    //und speichere darin 5 QRectF-Elemente
    //jeweils mit X- und Y-Position, Breite und Höhe
    //Reihenfolge für folgende Vektoren wichtig!
    std::vector <QRectF> elements;
    //Rechteck (rectangle)
    elements.push_back(QRectF(x,y,35,35));
    //langezogener Kreis (ellipse)
    elements.push_back(QRectF (x,y,30,50));
    //Säule (column)
    elements.push_back(QRectF (x,y,20,50));
    //Kuchenstück (pie)
    elements.push_back(QRectF (x, y, 60, 70));
    //rundes Rechteck (rounded Rect)
    elements.push_back(QRectF (x, y, 45, 40));
    //roter Kreis für Leben addieren
    elements.push_back(QRectF (x, y, 30, 30));

    //Festelgung der Farben
    //definiere eine Liste elementeFarbe vom Typ QColor
    //und speichere darin 5 QColor-Elemente
    //mit jeweils einer bestimmten Farbe
    //wichtig: gleiche Reihenfolge wie vector elemente
    //damit Farben wie gewollt & gleich zugewiesen werden
    std::vector <QColor> elementColor;
    elementColor.push_back(QColor("#7A4948"));
    elementColor.push_back(QColor("#AD94AB"));
    elementColor.push_back(QColor("#E2BD5F"));
    elementColor.push_back(QColor("#A0D1CE"));
    elementColor.push_back(QColor("#3D828F"));
    elementColor.push_back(QColor(Qt::red));

    std::vector <QPen> elementPen;
    elementPen.push_back(QPen("#7A4948"));
    elementPen.push_back(QPen("#AD94AB"));
    elementPen.push_back(QPen("#E2BD5F"));
    elementPen.push_back(QPen("#A0D1CE"));
    elementPen.push_back(QPen("#3D828F"));
    elementPen.push_back(QPen("#000000"));

    std::vector <int> elementPenWidth;
    elementPenWidth.push_back(4);
    elementPenWidth.push_back(4);
    elementPenWidth.push_back(4);
    elementPenWidth.push_back(4);
    elementPenWidth.push_back(4);
    elementPenWidth.push_back(1);

    //Festelgung des BrushStyle
    //definiere eine Liste elementeFarbe vom Typ Qt::BrushStyle
    //und speichere darin 5 Qt::BrushStyle-Elemente
    //mit jeweils einem bestimmten Pattern
    //wichtig: gleiche Reihenfolge wie vector elemente
    //damit BrushStyles wie gewollt & gleich zugewiesen werden
    std::vector <Qt::BrushStyle> elementBrush;
    elementBrush.push_back(Qt::BrushStyle(Qt::Dense3Pattern));
    elementBrush.push_back(Qt::BrushStyle(Qt::Dense3Pattern));
    elementBrush.push_back(Qt::BrushStyle(Qt::Dense3Pattern));
    elementBrush.push_back(Qt::BrushStyle(Qt::Dense3Pattern));
    elementBrush.push_back(Qt::BrushStyle(Qt::Dense3Pattern));
    elementBrush.push_back(Qt::BrushStyle(Qt::SolidPattern));

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
    //roter Kreis für Leben
    fallingRate.push_back(12);

    //generiere ein beliebiges der 5 definierten Elemente
    //durch Aufrufen der Listen mit zuvor in newElement
    //beliebigen generiertem Wert von elementType
    rect = QRectF (elements[elementType]);
    yMovement = fallingRate[elementType];
    color = QColor (elementColor[elementType]);
    pattern = Qt::BrushStyle (elementBrush[elementType]);
    pen = QPen (elementPen[elementType]);
    penWidth = int (elementPenWidth[elementType]);

}
