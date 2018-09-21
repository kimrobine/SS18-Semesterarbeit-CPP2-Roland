#include "gamewidget.h"
#include "gamearea.h"
#include "player.h"
#include <QPainter>
#include <QDebug>

/* Konstruktor & Definition der Starteinstellungen */
player::player(QWidget *parent) : QWidget(parent) {
    //Anfangs-X-Korrdinate des Spielers
    setPlayerX(350);
    //Anfangs-Y-Korrdinate des Spielers
    setPlayerY(510);
    //Schrittweite der Bewegung
    getPlayerMove(25);
    //Breite des Spielerrechtecks
    setPlayerWidth(30);
    //Höhe des Spielerrechtecks
    setPlayerHeight(30);
    //wird für keyPressEvent/Ausführung der Bewegung benötigt
    setFocusPolicy(Qt::StrongFocus);
}

/* Definition der player-Bewegung */
void player::move(Movement::playerMovement status) {

       switch (status) {
       case playerGoesLeft:
           setPlayerX(getPlayerX() - getPlayerMove());
           QWidget::update();
           break;
       case playerGoesRight:
           setPlayerX(getPlayerX() + getPlayerMove());
           QWidget::update();
           break;
       default:
           break;
       }
    }

/* Den Spieler ins Spielfeld malen */
void player::paintEvent(QPaintEvent *event) {

    Q_UNUSED(event);
    QPainter painter;
    //erschaffe ein Rechteck mit den zuvor im Konstruktor definierten Koordinaten
    QRectF rectangle(getPlayerX(), getPlayerY(), getPlayerWidth(), getPlayerHeight());
    painter.begin(this);

    //mit der Farbe Blau
    QColor playerRect ("#0000cc");
    //und schraffiere das Innere des Quadrates
    Qt::BrushStyle playerStyle = Qt::BDiagPattern;
    QBrush playerBrush (playerRect, playerStyle);
    painter.setBrush(playerBrush);
    //zeichne eine Aussenlinie
    painter.setPen(QPen(Qt::blue, 3));

    //zeichne das Rechteck
    painter.drawRect(rectangle);
    painter.end();
}

/* Defintion der Aktion bei Drücken der Pfeiltasten */
void player::keyPressEvent(QKeyEvent *keyEvent)
{ 
    /* Einbinden, dass Player sich bei running=false nicht bewegen lässt
    gameArea game;
    game.getRunning();
    if (game.getRunning()==false) //playerMove funktioniert
    //if (game.getRunning()==true) //playerMove funktioniert nicht
    */

    switch (keyEvent->key()) {
    //wenn die linke Pfeiltaste gedrückt wird
    case Qt::Key_Left:
        //führe Funktion move mit Status playerGoesLeft aus
        move(playerGoesLeft);
        break;
    //wenn die rechte Pfeiltaste gedrückt wird
    case Qt::Key_Right:
        //führe Funktion move mit Status playerGoesRight aus
        move(playerGoesRight);
        break;
    default:
        break;
    }
}

/* Defintion der Get- und Set-Methoden für die Position des players */
void player::setPlayerX(int pX)
{
    playerX = pX;

    //Festlegen, dass sich der Spieler nur innerhalb des Zeichenfeldes bewegen soll
    if (playerX <=3) {
        playerX = 3;
    }
    else if (pX >=687) {
        playerX = 687;
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
