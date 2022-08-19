#ifndef MAPBLOCK_H
#define MAPBLOCK_H

#include "../../header/common.h"

class MapBlock : public QGraphicsItem
{
public:
    MapBlock(int height = 128, int width = 128, int posx = 0, int posy = 0, QPixmap * fig = nullptr, BlockState state = BlockState_None);
    MapBlock(const MapBlock& a);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
public:
    enum {Type = UserType + 3};
    int height, width;
    int posx, posy;
    BlockState state;
    QPixmap * fig;
};

#endif // MAPBLOCK_H
