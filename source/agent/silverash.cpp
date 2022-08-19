#include "../../header/agent/silverash.h"

SilverAsh::SilverAsh(QGraphicsItem *parent, int x_block, int y_block, qreal x, qreal y, AgentTowards towards)
    : Agent(parent, "SilverAsh", x_block, y_block, x, y, towards)
{
    handleInfo(":/agent/" + name + "/info");
    SilverAsh::Placed = true;
}

bool SilverAsh::Placed = false;
