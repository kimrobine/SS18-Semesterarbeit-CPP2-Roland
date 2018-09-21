#include "gamearea.h"
#include "gamewidget.h"
#include "player.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gameWidget w;
    w.setGeometry(0 , 0, 700, 500);
    w.setFixedSize(890,650);
    w.setWindowTitle("C++-Spiel von Kim Roland");
    w.setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    w.show();

    return a.exec();
}
