#ifndef COSTER_H
#define COSTER_H

#include "../../header/common.h"

class Coster : public QGraphicsItem
{
public:
    Coster(qreal cost, qreal maxcost, qreal speed, int Windowwidth, int Windowheight);

public:
    qreal cost;
    qreal maxcost;
    qreal speed;
    int Windowwidth;
    int Windowheight;
    QPixmap bgf;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
};

#endif // COSTER_H
