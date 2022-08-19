#include "../../header/agent/skadi.h"
#include "../../header/enemy/enemy.h"


Skadi::Skadi(QGraphicsItem * parent, int x_block, int y_block, qreal x, qreal y, AgentTowards towards)
    : Agent(parent, "Skadi", x_block, y_block, x, y, towards)
{
    handleInfo(":/agent/" + name + "/info");
    Skadi::Placed = true;
}

bool Skadi::canAttackItem(QGraphicsItem *other)
{
    if (other->type() != Enemy::Type) return false;
    Enemy * tmp = static_cast<Enemy *>(other);
    if (tmp->fly) return false;
    else return true;
}

bool Skadi::Placed = false;
