#ifndef GHOST_H
#define GHOST_H

#include "../../header/enemy/enemy.h"

class Ghost : public Enemy
{
public:
    Ghost (qreal width, qreal height, qreal block_width, qreal block_height, EnemyPath enemypath, qreal x_block, qreal y_block);
};

#endif // GHOST_H
