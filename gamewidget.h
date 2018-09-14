#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "gamearea.h"

class gameWidget : public QWidget
{
    Q_OBJECT

private:
    gameArea *mygameArea;
    QPushButton *startstop;

public:
    gameWidget(QWidget *parent = 0);

private slots:
    void startStop(void);
    void saveGame(void);
    void loadGame(void);
};

#endif // GAMEWIDGET_H
