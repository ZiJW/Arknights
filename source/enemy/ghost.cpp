#include "../../header/enemy/ghost.h"

Ghost::Ghost(qreal width, qreal height, qreal block_width, qreal block_height, EnemyPath enemypath, qreal x_block, qreal y_block)
    : Enemy(width, height, block_width, block_height, enemypath, x_block, y_block)
{
    name = "Ghost";
    hp = totalhp = 2300;
    phydefence = 120;
    magdefence = 0.35;
    atktype = AttackType_None;

    attack = 200;
    atkspeed = 100;
    atkInterval = 0;
    atkradius = 0.0;

    fly = false;
    longDistanceAtk = false;
    resistNum = 99;
    speed = 1.2;
    this->setStateMove();
}
