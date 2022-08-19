#include "../../header/agent/placeagent.h"

PlaceAgent::PlaceAgent()
{

}

PlaceAgent::PlaceAgent(QGraphicsItem *parent, QString name, QPointF pos, int block_x, int block_y)
    : parent(parent), name(name), pos(pos), block_x(block_x), block_y(block_y)
{
   image = new QImage(":/agent/" + name + "/Placing");
}

QRectF PlaceAgent::boundingRect() const
{
    return QRectF(pos.x(), pos.y(), CUSTOM_ATK_WIDTH, CUSTOM_ATK_HEIGHT);
}

void PlaceAgent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(boundingRect(), image->scaled(CUSTOM_ATK_WIDTH, CUSTOM_ATK_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void PlaceAgent::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    startx = event->pos().x();
    starty = event->pos().y();
}

void PlaceAgent::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    mime->setText(QString::number(startx) + " " + QString::number((starty)));
    drag->setMimeData(mime);
    drag->exec();
}
