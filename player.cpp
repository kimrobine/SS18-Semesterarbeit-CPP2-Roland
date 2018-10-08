#include <QPainter>
#include <QDebug>

#include "gamewidget.h"
#include "gamearea.h"
#include "player.h"

/* Konstruktor der Klasse player & Definition der Startwerte des Spielers */
player::player(QWidget *parent) : QWidget(parent) {

    //Initalisierung der Spielereigenschaften

    //Anfangs-X-Korrdinate des Spielers
    setPlayerX(330);
    //Anfangs-Y-Korrdinate des Spielers
    setPlayerY(470);
    //Schrittweite der Bewegung
    getPlayerMove(30);
    //Breite des Spielerrechtecks
    setPlayerWidth(40);
    //Höhe des Spielerrechtecks
    setPlayerHeight(40);
    //Darstellung des Players mit vollen Leben
    playerStyle = 0;

    //wird für keyPressEvent/Ausführung der Bewegung benötigt
    setFocusPolicy(Qt::StrongFocus);

}

/* Definition der Spieler-Bewegung */
void player::movePlayer(movement::playerMovement status) {

    switch (status) {
    //im Fall playerGoesLeft, also Spieler soll sich nach links bewegen
    case playerGoesLeft:
        //setze X-Position des Spielers auf Ergebnis der Subtraktion
        //von aktuellem X-Wert mit Schrittweite playerMove
        setPlayerX(getPlayerX() - getPlayerMove());
        break;
        //im Fall playerGoesRight, also Spieler soll sich nach rechts bewegen
    case playerGoesRight:
        //setze X-Position des Spielers auf Ergebnis der Addition
        //von aktuellem X-Wert mit Schrittweite playerMove
        setPlayerX(getPlayerX() + getPlayerMove());
        break;
    default:
        break;
    }

}

/* Defintion der Set- und Get-Methoden für die optische Darstellung des Spielers */
void player::setPlayerColor (QColor c) {
    playerColor = c;
}

void player::setPlayerPattern (Qt::BrushStyle s) {
    playerPattern = s;
}

QColor player::getPlayerColor() {
    return playerColor;
}

Qt::BrushStyle player::getPlayerPattern() {
    return playerPattern;
}

/* Methode, um Darstellung des Spielers abhängig von seiner Anzahl an Leben zu verändern */
void player::setPlayerStyle(int pStyle) {

    //bestimmter Style des Spielers (0-2) wurde übergeben
    //und playerStyle wird auf gleichen Wert gesetzt
    playerStyle = pStyle;

    //'gesunde' Darstellung des Spielers bei vollen Leben:
    //voller Blauton, schraffiert
    if (playerStyle==0) {
        setPlayerColor("#005BE5");
        setPlayerPattern(Qt::BDiagPattern);
    }

    //abgeschwächte Darstellung des Spielers Stufe 1:
    //mittelblau, gepunktet
    if (playerStyle==1) {
        setPlayerColor("#327BEA");
        setPlayerPattern(Qt::Dense7Pattern);
    }

    //abgeschwächte Darstellung des Spielers Stufe 2:
    //helles Blau, leerer Rahmen
    if (playerStyle==2) {
        setPlayerColor("#7FADF2");
        setPlayerPattern(Qt::NoBrush);
    }
}

/* Get-Methode für Darstellung des Spielers */
int player::getPlayerStyle () {
    return playerStyle;
}


/* Anweisungen für das Zeichnen des Spielers */
void player::paintEvent(QPaintEvent *event) {

    Q_UNUSED(event);
    //erstelle den Painter & beginne zu zeichnen
    QPainter painter;
    painter.begin(this);
    //definiere ein Rechteck mit den zuvor im Konstruktor definierten Koordinaten
    QRectF rectangle(getPlayerX(), getPlayerY(), getPlayerWidth(), getPlayerHeight());

    //setze die Farbe des Spielers und sein Muster
    //mithilfe der dafür definierten Methoden
    QBrush playerBrush (getPlayerColor(), getPlayerPattern());
    painter.setBrush(playerBrush);
    //zeichne eine Aussenlinie um das Rechteck
    //in der Farbe des Spielers
    QPen playerPen (getPlayerColor());
    //und mache sie 3 pkt Breit
    playerPen.setWidth(3);
    painter.setPen(playerPen);

    //zeichne ein Rechteck mit den erhaltenen Werten der Methoden
    //aus der Definition des rectangle
    painter.drawRect(rectangle);
    painter.end();
}


/* Defintion der Aktion bei Drücken der Pfeiltasten */
void player::keyPressEvent(QKeyEvent *keyEvent)
{ 
    switch (keyEvent->key()) {
    //wenn die linke Pfeiltaste gedrückt wird
    case Qt::Key_Left:
        //führe Methode movePlayer mit Status playerGoesLeft aus
        movePlayer(playerGoesLeft);
        break;
        //wenn die rechte Pfeiltaste gedrückt wird
    case Qt::Key_Right:
        //führe Methode movePlayer mit Status playerGoesRight aus
        movePlayer(playerGoesRight);
        break;
        //für alle anderen KeyPressEvents: führe nichts aus
    default:
        break;
    }

}

/* Defintion der Set- und Get-Methoden für die Position des Spielers */

void player::setPlayerX(int pX)
{
    playerX = pX;

    /* Spieler soll sich nur innerhalb der gameArea bewegen
     * und nicht darüber hinaus */

    //Bewegung nach links
    //wenn X-Koordinate des Spielers kleiner oder gleich 3
    if (playerX <=3) {
        //setze X-Koordinate auf 3
        //Bewegung weiter nach links so nicht möglich,
        //da sobald <=3 immer 3
        playerX = 3;
    }
    //Bewegung nach rechts
    //wenn X-Koordinate des Spielers größer oder gleich 637
    else if (pX >=637) {
        //setze X-Koordinate auf 637
        //Bewegung weiter nach rechts so nicht möglich,
        //da sobald >=637 immer 637
        playerX = 637;
    }
}

int player::getPlayerX() const
{
    return playerX;
}

void player::setPlayerY(int pY)
{
    playerY = pY;
}

int player::getPlayerY() const
{
    return playerY;
}

void player::getPlayerMove(int pMove)
{
    playerMove = pMove;
}

int player::getPlayerMove() const
{
    return playerMove;
}

void player::setPlayerWidth(int pWidth)
{
    playerWidth = pWidth;
}

int player::getPlayerWidth() const
{
    return playerWidth;
}

void player::setPlayerHeight(int pHeight)
{
    playerHeight = pHeight;
}

int player::getPlayerHeight() const
{
    return playerHeight;
}

/* Ende Defintion der Set- und Get-Methoden für die Position des Spielers */

//Dekonstruktor der Klasse Movement
movement::~movement()
{

}
