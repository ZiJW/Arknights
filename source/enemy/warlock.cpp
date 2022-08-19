#include "../../header/enemy/warlock.h"
#include "../../header/agent/agent.h"

Warlock::Warlock(qreal width, qreal height, qreal block_width, qreal block_height, EnemyPath enemypath, qreal x_block, qreal y_block)
    : Enemy(width, height, block_width, block_height, enemypath, x_block, y_block)
{
    name = "Warlock";
    hp = totalhp = 1600;
    phydefence = 50;
    magdefence = 0.5;
    atktype = AttackType_Magic;

    attack = 200;
    atkspeed = 100;
    atkInterval = 4;
    atkradius = 1.8;

    fly = false;
    longDistanceAtk = true;
    resistNum = 1;
    speed = 0.8;
    this->setStateMoveAtk();
}
