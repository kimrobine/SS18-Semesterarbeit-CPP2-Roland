#ifndef GAMEAREA_H
#define GAMEAREA_H
#include <QMainWindow>
#include <QFile>
#include <QLabel>
#include <player.h>

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

    player *playerShape;

private:
    QTimer *timer;
    Ui::gameArea *ui;
    bool running;
    QLabel *gamePointsLabel;
    int gamePoints;

private slots:
    void updateGame();

protected:
     void paintEvent(QPaintEvent *event);
};

#endif // GAMEAREA_H
