#include "./header/mainwindow/mainwindow.h"
#include "./header/map/fightmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FightMainWindow w(nullptr, "0-1");
    w.show();
    return a.exec();
}
