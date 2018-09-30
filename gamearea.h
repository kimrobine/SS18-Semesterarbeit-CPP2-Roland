#ifndef GAMEAREA_H
#define GAMEAREA_H
#include <QMainWindow>
#include <QFile>
#include <QLabel>
#include <vector>

#include "player.h"
#include "element.h"

/* Die Klasse gameArea erstellt das Zeichenfeld, in dem sich der player und die Objekte bewegen,
 * und ist für den Timer und die Punkteanzeige zuständig
 */

namespace Ui {
class gameArea;
}

class gameArea : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameArea(QWidget *parent = 0);
    ~gameArea();
    void serialize(QFile &file);
    void deserialize(QFile &file);
    bool getRunning() {return running;}
    void setRunning(bool run);
    void setGamePoints(QLabel *gamePoints){gamePointsLabel = gamePoints;}
    void createGegner();
    void drawEnemies(QPainter& painter);
    void drawLives(QPainter& painter);
    //void gameIsOver();

    //erstelle eine Vectorliste vom Typ element mit dem Namen enemies
    std::vector<element*> enemies;

private:
    player *playerRect;
    QTimer *timer;
    Ui::gameArea *ui;
    bool running;
    QLabel *gamePointsLabel;
    int gamePoints;
    int leben = 3;

    bool unverwundbar = false;
    bool getroffen = false;
    bool gameOver = false;

    int unverwundbarTimer = 0;
    int getroffenTimer = 0;
    int gameOverTimer = 0;

    const int unverwundbarTimeout = 30;
    const int getroffenTimeout = 50;
    const int gameOverTimeout = 100;


private slots:
    void updateGame();

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // GAMEAREA_H
