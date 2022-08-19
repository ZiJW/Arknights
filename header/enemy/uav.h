#ifndef UAV_H
#define UAV_H

#include "../../header/enemy/enemy.h"

class UAV : public Enemy
{
public:
    UAV (qreal width, qreal height, qreal block_width, qreal block_height, EnemyPath enemypath, qreal x_block, qreal y_block);
};

#endif // UAV_H
