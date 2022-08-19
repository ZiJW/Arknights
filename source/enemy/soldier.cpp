#include "../../header/enemy/soldier.h"
#include "../../header/agent/agent.h"

Soldier::Soldier(qreal width, qreal height, qreal block_width, qreal block_height, EnemyPath enemypath, qreal x_block, qreal y_block)
    : Enemy(width, height, block_width, block_height, enemypath, x_block, y_block)
{
    name = "Soldier";
    hp = totalhp = 1650.0;
    phydefence = 100.0;
    magdefence = 0.0;
    atktype = AttackType_Physical;

    attack = 100;
    atkspeed = 100;
    atkInterval = 2.0;
    atkradius = 0.0;

    fly = false;
    longDistanceAtk = false;
    resistNum = 1;
    speed = 1;
    this->setStateMove();
}
