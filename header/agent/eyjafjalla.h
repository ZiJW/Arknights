#ifndef EYJAFJALLA_H
#define EYJAFJALLA_H

#include "../../header/common.h"
#include "../../header/agent/agent.h"

class Eyjafjalla : public Agent
{
public:
    Eyjafjalla(QGraphicsItem * parent, int x_block, int y_block, qreal x, qreal y, AgentTowards towards);
public:
    static bool Placed;
};

#endif // EYJAFJALLA_H
