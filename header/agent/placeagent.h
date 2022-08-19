#ifndef PLACEAGENT_H
#define PLACEAGENT_H

#include "../../header/common.h"

class PlaceAgent : public QGraphicsItem
{
public:
    PlaceAgent();
    PlaceAgent(QGraphicsItem * parent, QString name, QPointF pos, int block_x, int block_y);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private:
    QGraphicsItem *parent;
    QString name;
    QPointF pos;
    int block_x;
    int block_y;
    QImage *image;
    qreal startx, starty;
};

#endif // PLACEAGENT_H
