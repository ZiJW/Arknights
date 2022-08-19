#include "../../header/mainwindow/jumpbutton.h"


JumpButton::JumpButton(int startwid, int starthei, int width, int height, QPixmap fig, QString name)
    : Startwid(startwid)
    , Starthei(starthei)
    , Width(width)
    , Height(height)
    , fig(fig)
    , name(name)
{
    setPos(0, 0);
}

QRectF JumpButton::boundingRect() const
{
    return QRectF(Startwid, Starthei, Width, Height);
}

void JumpButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(Startwid, Starthei, Width, Height), fig.scaled(Width, Height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QFont font("NSimSun", 32, true);
    painter->setFont(font);
    painter->drawText(this->boundingRect(), Qt::AlignCenter, name);
}

void JumpButton::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (event->button() == Qt::LeftButton) Handle();
}
