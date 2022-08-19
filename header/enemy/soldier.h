#ifndef SOLDIER_H
#define SOLDIER_H

#include "../../header/enemy/enemy.h"

class Soldier : public Enemy
{
public:
    Soldier (qreal width, qreal height, qreal block_width, qreal block_height, EnemyPath enemypath, qreal x_block, qreal y_block);
};

#endif // SOLDIER_H
