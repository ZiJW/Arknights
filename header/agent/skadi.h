#ifndef SKADI_H
#define SKADI_H
#include "../../header/common.h"
#include "../../header/agent/agent.h"

class Skadi : public Agent
{
public:
    Skadi(QGraphicsItem * parent, int x_block, int y_block, qreal x, qreal y, AgentTowards towards);
    virtual bool canAttackItem(QGraphicsItem * other) override;
public:
    static bool Placed;
};


#endif // SKADI_H
