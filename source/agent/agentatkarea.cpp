#include "../../header/agent/agentatkarea.h"
#include "../../header/enemy/enemy.h"
#include "../../header/agent/agent.h"


AgentAtkArea::AgentAtkArea()
{
    parent = nullptr;
    towards = AgentTowards_None;
    blockHeight = 0;
    blockWidth = 0;
    originPlace = {0, 0};
    QVector<std::complex<qreal> >tmp;
    tmp.push_back({0, 0});
    atkBlock = tmp;
}

AgentAtkArea::AgentAtkArea(QGraphicsItem *parent, AgentTowards towards, qreal blockHeight, qreal blockWidth, std::complex<qreal> originPlace, QVector<std::complex<qreal> > tmpatkBlock)
    : parent(parent), towards(towards), blockHeight(blockHeight), blockWidth(blockWidth), originPlace(originPlace), atkBlock(tmpatkBlock)
{
    for (int i = 0; i < atkBlock.size(); i++) {
        atkBlock[i] = atkBlock[i] * towards;
    }
}

AgentAtkArea &AgentAtkArea::operator =(const AgentAtkArea &other)
{
    this->parent = other.parent;
    this->towards = other.towards;
    this->blockHeight = other.blockHeight;
    this->blockWidth = other.blockWidth;
    this->originPlace = other.originPlace;
    this->atkBlock = other.atkBlock;
    return *this;
}

QRectF AgentAtkArea::boundingRect() const
{
    qreal maxx = 0, maxy = 0, minx = 0, miny = 0;
    foreach(std::complex<qreal> tmp, atkBlock) {
        if (tmp.real() > maxx) maxx = tmp.real();
        if (tmp.real() < minx) minx = tmp.real();
        if (tmp.imag() > maxy) maxy = tmp.imag();
        if (tmp.imag() < miny) miny = tmp.imag();
    }
    return QRectF((originPlace.real() + minx) * blockWidth, (originPlace.imag() + miny) * blockHeight, blockWidth * (maxx - minx + 1), blockHeight * (maxy - miny + 1));
}

void AgentAtkArea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Agent * pa = static_cast<Agent*>(parent);
    if (pa->pressed()) painter->drawPath(shape());
}

QPainterPath AgentAtkArea::shape() const
{
    QPainterPath ret;
    for (int i = 0; i < atkBlock.size(); i++) {
        qreal tmpx = atkBlock[i].real(), tmpy = atkBlock[i].imag();
        QRectF tmp = QRectF((tmpx + originPlace.real()) * blockWidth, (tmpy + originPlace.imag()) * blockHeight, blockWidth, blockHeight);
        ret.addRect(tmp);
    }
    return ret;
}

void AgentAtkArea::advance(int phase)
{
    if (!phase) return;
    update();
}
