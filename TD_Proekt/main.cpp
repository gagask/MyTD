#include "game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game* g;
    g = new Game();
    g->show();
    return a.exec();

}
