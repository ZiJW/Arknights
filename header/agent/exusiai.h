#ifndef EXUSIAI_H
#define EXUSIAI_H

#include "../../header/common.h"
#include "../../header/agent/agent.h"

class Exusiai : public Agent
{
public:
    Exusiai(QGraphicsItem * parent, int x_block, int y_block, qreal x, qreal y, AgentTowards towards);
public:
    static bool Placed;
};

#endif // EXUSIAI_H
