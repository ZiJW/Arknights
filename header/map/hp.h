#ifndef HP_H
#define HP_H

#include "../../header/common.h"


class HP : QGraphicsItem
{
public:
    HP();
    HP(QGraphicsItem * parent, qreal totalhp, qreal px, qreal py);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    HP& operator = (const HP& other);
protected:
    QGraphicsItem * parent;
    qreal hp, maxhp;
    qreal posx, posy;
};

#endif // HP_H
