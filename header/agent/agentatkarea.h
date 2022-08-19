#ifndef AGENTATKAREA_H
#define AGENTATKAREA_H
#include "../../header/common.h"

class AgentAtkArea : public QGraphicsItem
{
public:
    AgentAtkArea();
    AgentAtkArea(QGraphicsItem *parent, AgentTowards towards, qreal blockHeight, qreal blockWidth, std::complex<qreal> originPlace, QVector<std::complex<qreal> > tmpatkBlock);
    AgentAtkArea& operator = (const AgentAtkArea& other);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const override;
    void advance(int phase) override;

private:
    QGraphicsItem *parent;
    AgentTowards towards;
    qreal blockHeight, blockWidth;
    std::complex<qreal> originPlace;
    QVector<std::complex<qreal> > atkBlock;
};

#endif // AGENTATKAREA_H
