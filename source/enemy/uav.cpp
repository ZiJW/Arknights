#include "../../header/enemy/uav.h"

UAV::UAV(qreal width, qreal height, qreal block_width, qreal block_height, EnemyPath enemypath, qreal x_block, qreal y_block)
    : Enemy(width, height, block_width, block_height, enemypath, x_block, y_block)
{
    name = "UAV";
    hp = totalhp = 800;
    phydefence = 50;
    magdefence = 0;
    atktype = AttackType_None;

    attack = 0;
    atkspeed = 100;
    atkInterval = 0;
    atkradius = 0.0;

    fly = true;
    longDistanceAtk = false;
    resistNum = 99;
    speed = 0.9;
    this->setStateMove();
}
