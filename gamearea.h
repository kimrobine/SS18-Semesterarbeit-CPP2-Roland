#ifndef GAMEAREA_H
#define GAMEAREA_H

#include <QWidget>
#include <QFile>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>


class gameArea : public QWidget
{
    Q_OBJECT

    public:
    gameArea(QWidget *parent = 0);
    void serialize(QFile &file);
    void deserialize(QFile &file);
    bool getRunning() {return running;}
    void setRunning(bool run);

    private:
    bool running;
    QPoint player;
    QColor playerColor;
    int buttonPressed;

    protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // GAMEAREA_H
