#ifndef SILVERASH_H
#define SILVERASH_H

#include "../../header/common.h"
#include "../../header/agent/agent.h"

class SilverAsh : public Agent
{
public:
    SilverAsh(QGraphicsItem * parent, int x_block, int y_block, qreal x, qreal y, AgentTowards towards);
public:
    static bool Placed;
};

#endif // SILVERASH_H
