#include "../../header/map/mapblock.h"
MapBlock::MapBlock(int height, int width, int posx, int posy, QPixmap * fig, BlockState state)
    : height(height)
    , width(width)
    , posx(posx)
    , posy(posy)
    , fig(fig)
    , state(state)
{
    setZValue(0);
    assert(height == width);
    assert(state <= BlockState_None2 and state >= BlockState_None);
}

MapBlock::MapBlock(const MapBlock &a)
    : height(a.height)
    , width(a.width)
    , posx(a.posx)
    , posy(a.posy)
    , fig(a.fig)
    , state(a.state)
{
    assert(height == width);
    assert(state <= BlockState_None2 and state >= BlockState_None);
}

QRectF MapBlock::boundingRect() const
{
    return QRectF(posx, posy, width, height);
}

void MapBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(posx, posy, width, height), fig->scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
