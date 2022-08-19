#include "../../header/enemy/skii.h"

SKII::SKII (qreal width, qreal height, qreal block_width, qreal block_height, EnemyPath enemypath, qreal x_block, qreal y_block)
    : Enemy(width, height, block_width, block_height, enemypath, x_block, y_block)
{
    name = "SKII";
    hp = totalhp = 1550;
    phydefence = 50;
    magdefence = 0;
    atktype = AttackType_Physical;

    attack = 220;
    atkspeed = 100;
    atkInterval = 3;
    atkradius = 2.0;

    fly = true;
    longDistanceAtk = true;
    resistNum = 98;
    speed = 0.9;
    this->setStateMoveAtk();
}
