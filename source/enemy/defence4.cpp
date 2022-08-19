#include "../../header/enemy/defence4.h"

Defence4::Defence4(qreal width, qreal height, qreal block_width, qreal block_height, EnemyPath enemypath, qreal x_block, qreal y_block)
    : Enemy(width, height, block_width, block_height, enemypath, x_block, y_block)
{
    name = "Defence4";
    hp = totalhp = 4000;
    phydefence = 150;
    magdefence = 0;
    atktype = AttackType_None;

    attack = 0;
    atkspeed = 100;
    atkInterval = 0;
    atkradius = 0.0;

    fly = true;
    longDistanceAtk = true;
    resistNum = 99;
    speed = 0.8;
    this->setStateMoveAtk();
}

void Defence4::moveAtk()
{
    move();
    foreach(QGraphicsItem * item, scene()->items()) {
        if (item->type() == Enemy::Type) {
            Enemy * tmp = static_cast<Enemy *>(item);
            if (tmp->totalhp >= tmp->hp + 1) tmp->hp += 1;
            //qDebug() << item << tmp->hp;
        }
    }
}


