#ifndef WARLOCK_H
#define WARLOCK_H

#include "../../header/enemy/enemy.h"

class Warlock : public Enemy
{
public:
    Warlock (qreal width, qreal height, qreal block_width, qreal block_height, EnemyPath enemypath, qreal x_block, qreal y_block);
};

#endif // WARLOCK_H
