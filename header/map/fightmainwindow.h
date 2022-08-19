#ifndef FIGHTMAINWINDOW_H
#define FIGHTMAINWINDOW_H

#include "../../header/enemy/enemy.h"
#include "../../header/map/fightmap.h"
#include "../../header/common.h"
#include "../../header/map/coster.h"
#include "../../header/agent/agentcard.h"

class FightMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit FightMainWindow(QWidget *parent = nullptr, QString fightname = "");
    void addEnemy();
    QQueue<QPair<int, Enemy*> > HandleEnemyInfo();

private:
    QTimer *timer;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QString fightname;
    int window_width, window_size;
    FightMap *fightmap;
    qreal block_width, block_height;

    QQueue<QPair<int, Enemy*> > enemyinfo;
    Coster * coster;

signals:


};

#endif // FIGHTMAINWINDOW_H
