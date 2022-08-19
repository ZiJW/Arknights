#ifndef COMMON_H
#define COMMON_H

#include <iostream>

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QDebug>
#include <QPalette>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWidget>
#include <QGraphicsOpacityEffect>

#include <QTimer>
#include <QTime>
#include <QFile>

#include <QVector>
#include <QString>
#include <QPair>
#include <QQueue>
#include <qalgorithms.h>
#include <qglobal.h>
#include <qmath.h>
#include <QtGlobal>

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <complex>

#define TOTALNEWMSEC 33

#define TOTALFREQ (1000 / TOTALNEWMSEC)

#define AGENTCARD
#ifdef AGENTCARD
#define CUSTOM_AGTCARD_WIDTH  64
#define CUSTOM_AGTCARD_HEIGHT 64
#endif

#define AGENT
#ifdef AGENT
#define basicAttrNum 18
typedef int EliteLevel;
typedef int Level;
typedef int AttackDirection;
typedef int AgentState;
enum {
    AgentState_None = 0,
    AgentState_Wait,
    AgentState_Atk,
    AgentState_Start,
    AgentState_Dead,
    AgentState_None2
};
typedef int Place;

typedef int AgentPlaceType;
enum {
    AgentPlaceType_None = 0,
    AgentPlaceType_GroundOnly,
    AgentPlaceType_PlotOnly,
    AgentPlaceType_GroundPlot,
};
typedef int Type_Agent;

enum {
    Type_Melantha = 0,
    Type_Skadi,
};

#define GROUND_ONLY 1
#define PLAT_ONLY 2
#define CUSTOM_ATK_HEIGHT 128
#define CUSTOM_ATK_WIDTH 128
#define HP_WINDOW_HEIGHT 10
#define HP_WINDOW_WIDTH  CUSTOM_ATK_WIDTH
#endif

#define ATTACK_TYPE
#ifdef ATTACK_TYPE

typedef int AttackType;
enum {
    AttackType_None = 0,
    AttackType_Physical,
    AttackType_Magic,
    AttackType_Real
};

typedef std::complex<double> AgentTowards;
#define AgentTowards_None  (std::complex<double> (0.0, 0.0))
#define AgentTowards_Right  (std::complex<double> (1.0, 0.0))
#define AgentTowards_Up     (std::complex<double> (0.0, -1.0))
#define AgentTowards_Left   (std::complex<double> (-1.0, 0.0))
#define AgentTowards_Down   (std::complex<double> (0.0, 1.0))
#endif

#ifndef ENEMY
typedef int EnemyType;
enum {
    Type_Soldier = 0,
    Type_UAV,
    Type_Ghost,
    Type_Warlock,
    Type_SKII,
    Type_Defence4
};
typedef int EnemyState;
enum {
    EnemyState_None = 0,
    EnemyState_Move,
    EnemyState_Attack,
    EnemyState_Dead,
    EnemyState_MoveAttack
};

#define CustomEnemyWidth 64
#define CustomEnemyHeight 64
typedef int MovingDirection;
enum {
    MoveUp = 0,
    MoveRight,
    MoveDown,
    MoveLeft
};

typedef QVector<QPair<int, int> > AttackRange;

typedef QQueue<MovingDirection> EnemyPath;

#endif

#define MAPBLOCK
#ifdef MAPBLOCK
typedef int BlockState;
enum {
    BlockState_None = 0,
    BlockState_Ground,
    BlockState_Plat,
    BlockState_Start,
    BlockState_End,
    BlockState_None2
};
#endif

#define COSTER
#ifdef COSTER

#endif

#endif // COMMON_H
