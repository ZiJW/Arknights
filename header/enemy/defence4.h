#ifndef DEFENCE4_H
#define DEFENCE4_H

#include "../../header/enemy/enemy.h"

class Defence4 : public Enemy
{
public:
    Defence4 (qreal width, qreal height, qreal block_width, qreal block_height, EnemyPath enemypath, qreal x_block, qreal y_block);
    void moveAtk() override;
};

#endif // DEFENCE4_H
