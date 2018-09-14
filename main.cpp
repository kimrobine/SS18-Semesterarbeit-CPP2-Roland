#include "gamewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gameWidget w;
    w.setGeometry(0, 0, 700, 500);
    w.setWindowTitle("C++ Spiel von Kim Roland");
    w.show();
    return a.exec();
}
