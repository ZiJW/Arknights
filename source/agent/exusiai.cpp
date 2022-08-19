#include "../../header/agent/exusiai.h"

Exusiai::Exusiai(QGraphicsItem * parent, int x_block, int y_block, qreal x, qreal y, AgentTowards towards)
    : Agent(parent, "Exusiai", x_block, y_block, x, y, towards)
{
    handleInfo(":/agent/" + name + "/info");
    Exusiai::Placed = true;
}

bool Exusiai::Placed = false;
