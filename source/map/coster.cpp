#include "../../header/map/coster.h"

Coster::Coster(qreal cost, qreal maxcost, qreal speed,  int Windowwidth, int Windowheight) : cost(cost), maxcost(maxcost), speed(speed), Windowwidth(Windowwidth), Windowheight(Windowheight)
{
    setZValue(1);
    bgf = QPixmap(":/other/costerbgf");
    setX(Windowwidth - bgf.width());
    setY(Windowheight - bgf.height());
}

QRectF Coster::boundingRect() const
{
    return QRectF(0, 0, bgf.width(), bgf.height());
}

void Coster::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(0, 0, bgf.width(), bgf.height()), bgf);
    painter->setPen(Qt::white);
    QFont font;
    font.setPixelSize(50);
    painter->setFont(font);
    painter->drawText(QRectF(0, 0, bgf.width(), bgf.height()), Qt::AlignCenter, QString::number((int) cost));
}

void Coster::advance(int phase)
{
    if (not phase) return;
    cost += speed * (qreal) TOTALNEWMSEC / 1000.0;
    if (cost >= maxcost) cost = maxcost;
    update();
}
