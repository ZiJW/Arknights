#include "../../header/agent/eyjafjalla.h"

Eyjafjalla::Eyjafjalla(QGraphicsItem *parent, int x_block, int y_block, qreal x, qreal y, AgentTowards towards)
    : Agent(parent, "Eyjafjalla", x_block, y_block, x, y, towards)
{
    handleInfo(":/agent/" + name + "/info");
    Eyjafjalla::Placed = true;
}

bool Eyjafjalla::Placed = false;
