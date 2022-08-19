#include "../../header/map/fightmainwindow.h"
#include "../../header/enemy/defence4.h"
#include "../../header/enemy/soldier.h"
#include "../../header/enemy/skii.h"
#include "../../header/enemy/uav.h"
#include "../../header/enemy/ghost.h"
#include "../../header/enemy/warlock.h"
#include "../../header/agent/melantha.h"
#include "../../header/agent/agentatkarea.h"
#include "../../header/map/hp.h"


FightMainWindow::FightMainWindow(QWidget *parent, QString fightname)
    : QMainWindow(parent)
    , scene(new QGraphicsScene(this))
    , view(new QGraphicsView(scene, this))
    , timer(new QTimer)
    , fightname(fightname)
{
    //information should offered to constructor
    int fig_num;
    int x_num, y_num;
    int window_width, window_height;
    QVector<QVector<int> > map_fig, map_state;//the fig and state of each block

    //handle the info
    //offer the figure of each block first, then the state
    qsrand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));
    QFile info(":/map/" + fightname + "/info");
    if (info.open(QFile::ReadOnly)) {
        QTextStream in(&info);
        in >> fig_num;
        in >> x_num >> y_num >> block_width >> block_height;
        QVector<int> emp_int;
        int tmp;
        for (int i = 0; i < y_num; i++) {
            map_fig.push_back(emp_int);
            for (int j = 0; j < x_num; j++) {
                in >> tmp;
                map_fig[i].push_back(tmp);
            }
        }
        for (int i = 0; i < y_num; i++) {
            map_state.push_back(emp_int);
            for (int j = 0; j < x_num; j++) {
                in >> tmp;
                map_state[i].push_back(tmp);
            }
        }
    }
    else {
        qDebug() << "can't resolve the map info: /map/" + fightname + "/info";
        assert(0);
    }
    //handle the wihndow
    window_width = x_num * block_width, window_height = y_num * block_height + CUSTOM_AGTCARD_HEIGHT;
    //handle the map

    this->setFixedSize(window_width, window_height);
    scene->setSceneRect(0, 0, window_width, window_height);

    QVector<QPixmap *> appear;
    for (int i = 0; i < fig_num; i++) {
        appear.push_back(new QPixmap(":/map/" + fightname +"/" + QString::number(i)));
    }
    QVector<QPair<int, int> > emp;
    QVector<QVector<QPair<int, int> > >block2fig;
    //block2fig require fig num first, state second
    for (int i = 0; i < y_num; i++) {
        block2fig.push_back(emp);
        for (int j = 0; j < x_num; j++) {
            block2fig[i].push_back({map_fig[i][j], map_state[i][j]});
        }
    }
    fightmap = new FightMap(0, 0, x_num, y_num, block_width, block_height, appear, block2fig);
    scene->addItem(fightmap);

    //handle the enemy
    enemyinfo = HandleEnemyInfo();

    //handle the coster
    coster = new Coster(99, 99, 1.0, block_width * x_num, block_height* y_num);
    scene->addItem(coster);
    fightmap->coster = coster;

    //handle the agentcard
    //TODO
    //add new agent
    fightmap->addAgentCard("Eyjafjalla");
    fightmap->addAgentCard("SilverAsh");
    fightmap->addAgentCard("Skadi");
    fightmap->addAgentCard("Melantha");
    fightmap->addAgentCard("Exusiai");


    //test

    //connect the timer with function
    view->resize(window_width, window_height);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(timer, &QTimer::timeout, this, &FightMainWindow::addEnemy);

    timer->start(TOTALNEWMSEC);
    view->show();
}

void FightMainWindow::addEnemy()
{
    static int counter = 0;
    static int freq = TOTALFREQ;
    static int countersec = 0;
    if (counter++ >= freq) {
        counter = 0;
        countersec++;
    }
    while (not enemyinfo.empty() and countersec >= enemyinfo.front().first) {
        scene->addItem(enemyinfo.front().second);
        enemyinfo.dequeue();
    }
}

#define Helper(x) case Type_##x: addeditem = new x(width, height, block_width, block_height, path, startx, starty); break;
//the format of enemyinfo file like this
/*
 * 1(the number of enemy)
 * 5(the second appear, in the adding sequence) 0(type, soldier here) 128 128 (pix size) 8 2(start block x and y)
 * 4(the size of moving) 0 1 2 3 (the direction of each moving, 0-up, 1-right, 2-down, 3-left, which corresponding to the EnemyMovingDirection in common.h
 */
QQueue<QPair<int, Enemy *> > FightMainWindow::HandleEnemyInfo()
{
    int EnemyNum;
    EnemyType type;
    int startx, starty;
    qreal height, width;
    int dirnum;
    int time;
    MovingDirection tmp;
    EnemyPath path;
    Enemy *addeditem;
    QQueue<QPair<int, Enemy *> > ret;
    QFile info(":/map/" + fightname + "/enemyinfo");
    if (info.open(QFile::ReadOnly)) {
        QTextStream in(&info);
        in >> EnemyNum;
        for (int i = 0; i < EnemyNum; i++) {
            in >> time;
            in >> type;
            in >> width >> height;
            in >> startx >> starty;
            assert(startx >= 0 and starty >= 0);
            in>> dirnum;
            for (int j = 0; j < dirnum; j++) {
                in >> tmp;
                path.enqueue(tmp);
            }
            switch (type) {
                Helper(Soldier)
                Helper(UAV)
                Helper(Ghost)
                Helper(Warlock)
                Helper(SKII)
                Helper(Defence4)
            //TODO
            //Add more enemy
            default: assert(0);
            }
            ret.push_back({time, addeditem});
            path.clear();
        }
    }
    else {
        qDebug() << "can't resolve the map info: /map/" + fightname + "/enemyinfo";
        assert(0);
    }
    return ret;
}
