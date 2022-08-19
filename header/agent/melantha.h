#ifndef MELANTHA_H
#define MELANTHA_H

#include "../../header/agent/agent.h"

class Melantha : public Agent
{
public:
    Melantha(QGraphicsItem * parent, int x_block, int y_block, qreal x, qreal y, AgentTowards towards);
    virtual bool canAttackItem(QGraphicsItem * other) override;
public:
    static bool Placed;
};
#endif // MELANTHA_H
