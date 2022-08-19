#ifndef AGENTCARD_H
#define AGENTCARD_H

#include "../../header/common.h"
#include "../../header/agent/agent.h"
class AgentCard : public QGraphicsItem
{
public:
    AgentCard(QGraphicsItem* parent, QString name, int posx, int posy, int width, int height);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
public:
    QGraphicsItem* parent;
    QString name;
    bool canPlace;
    int posx, posy, width, height;
    bool placed;
    AgentPlaceType place;
    int cost;
    qreal needTime;
    qreal timeCounter;
    QGraphicsOpacityEffect *CannotPlaceEffect, *CanPlaceEffect;
};

#endif // AGENTCARD_H
