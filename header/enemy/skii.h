#ifndef SKII_H
#define SKII_H

#include "../../header/enemy/enemy.h"

class SKII : public Enemy
{
public:
    SKII (qreal width, qreal height, qreal block_width, qreal block_height, EnemyPath enemypath, qreal x_block, qreal y_block);
};

#endif // SKII_H
