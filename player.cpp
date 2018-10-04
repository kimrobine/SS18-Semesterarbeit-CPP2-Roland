#include <QPainter>
#include <QDebug>

#include "gamewidget.h"
#include "gamearea.h"
#include "player.h"

/* Konstruktor & Definition der Starteinstellungen */
player::player(QWidget *parent) : QWidget(parent) {
    //Anfangs-X-Korrdinate des Spielers
    setPlayerX(350);
    //Anfangs-Y-Korrdinate des Spielers
    setPlayerY(515);
    //Schrittweite der Bewegung
    getPlayerMove(30);
    //Breite des Spielerrechtecks
    setPlayerWidth(40);
    //Höhe des Spielerrechtecks
    setPlayerHeight(40);
    //wird für keyPressEvent/Ausführung der Bewegung benötigt
    setFocusPolicy(Qt::StrongFocus);
}

/* Definition der player-Bewegung */
void player::movePlayer(Movement::playerMovement status) {

    switch (status) {
    //im Fall playerGoesLeft, also Spieler soll sich nach links bewegen
    case playerGoesLeft:
        //setze X-Position des Players auf Ergebnis
        //der Subtraktion von aktuellem X-Wert mit Schrittweite PlayerMove
        setPlayerX(getPlayerX() - getPlayerMove());
        break;
        //im Fall playerGoesRight, also Spieler soll sich nach rechts bewegen
    case playerGoesRight:
        //setze X-Position des Players auf Ergebnis
        //der Addition von aktuellem X-Wert mit Schrittweite PlayerMove
        setPlayerX(getPlayerX() + getPlayerMove());
        break;
        //Standard: führe nichts aus
    default:
        break;
    }

}

/* Defintion der Set- und Get-Methoden für die optische Darstellung des players */
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

/* Den Spieler ins Spielfeld malen */
void player::paintEvent(QPaintEvent *event) {

    Q_UNUSED(event);
    //definiere den Painter & beginne zu zeichnen
    QPainter painter;
    painter.begin(this);
    //definiere ein Rechteck mit den zuvor im Konstruktor definierten Koordinaten
    QRectF rectangle(getPlayerX(), getPlayerY(), getPlayerWidth(), getPlayerHeight());

    QBrush playerBrush (getPlayerColor(), playerPattern);
    painter.setBrush(playerBrush);
    //zeichne eine Aussenlinie um das Rechteck
    //in der Farbe des Spielers
    QPen playerPen (getPlayerColor());
    //und mache sie 3 pkt Breit
    playerPen.setWidth(3);
    painter.setPen(playerPen);

    //zeichne ein Rechteck mit den Definitionen aus rectangle
    painter.drawRect(rectangle);
    painter.end();
}

/* Defintion der Aktion bei Drücken der Pfeiltasten */
void player::keyPressEvent(QKeyEvent *keyEvent)
{ 
    switch (keyEvent->key()) {
    //wenn die linke Pfeiltaste gedrückt wird
    case Qt::Key_Left:
        //führe Funktion move mit Status playerGoesLeft aus
        movePlayer(playerGoesLeft);
        break;
        //wenn die rechte Pfeiltaste gedrückt wird
    case Qt::Key_Right:
        //führe Funktion move mit Status playerGoesRight aus
        movePlayer(playerGoesRight);
        break;
        //für alle anderen KeyPressEvents: führe nichts aus
    default:
        break;
    }

}

/* Defintion der Set- und Get-Methoden für die Position des players */
void player::setPlayerX(int pX)
{
    playerX = pX;

    /*Spieler-Rect soll sich nur innerhalb der gameArea bewegen*/

    //Bewegung nach links
    //wenn X-Koordinate des Spielers kleiner oder gleich 3
    if (playerX <=3) {
        //setze X-Koordinate auf 3
        //Bewegung weiter nach links so nicht möglich,
        //da sobald <=3 immer 3
        playerX = 3;
    }
    //Bewegung nach rechts
    //wenn X-Koordinate des Spielers größer oder gleich 675
    else if (pX >=675) {
        //setze X-Koordinate auf 675
        //Bewegung weiter nach rechts so nicht möglich,
        //da sobald >=675 immer 675
        playerX = 675;
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

//Dekonstruktor der Klasse Movement
Movement::~Movement()
{

}
