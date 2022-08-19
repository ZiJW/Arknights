#ifndef JUMPBUTTON_H
#define JUMPBUTTON_H

#include "../../header/common.h"

class JumpButton : public QGraphicsItem
{
public:
    JumpButton(int startwid = 0, int starthei = 0, int weight = 0, int height = 0, QPixmap fig = QPixmap(""), QString name = "");
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    int Startwid, Starthei, Width, Height;
    QPixmap fig;
    QString name;
    void (*Handle)();
};

#endif // JUMPBUTTON_H
