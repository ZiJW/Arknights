#include "../../header/agent/melantha.h"
#include "../../header/enemy/enemy.h"

Melantha::Melantha(QGraphicsItem * parent, int x_block, int y_block, qreal x, qreal y, AgentTowards towards)
    : Agent(parent, "Melantha", x_block, y_block, x, y, towards)
{
    handleInfo(":/agent/" + name + "/info");
    Melantha::Placed = true;
}

bool Melantha::canAttackItem(QGraphicsItem *other)
{
    if (other->type() != Enemy::Type) return false;
    Enemy * tmp = static_cast<Enemy *>(other);
    if (tmp->fly) return false;
    else return true;
}

bool Melantha::Placed = false;
