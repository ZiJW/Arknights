#include "../../header/map/hp.h"
#include "../../header/agent/agent.h"
#include "../../header/enemy/enemy.h"

HP::HP()
{
    hp = maxhp = 1;
}

HP::HP(QGraphicsItem * parent, qreal totalhp, qreal px, qreal py)
    : parent(parent)
{
    hp = maxhp = totalhp;
    posx = px + (CUSTOM_ATK_WIDTH - HP_WINDOW_WIDTH) / 2, posy = py + CUSTOM_ATK_HEIGHT;
    setPos(posx, posy);
}

QRectF HP::boundingRect() const
{
    return QRectF(0, 0, HP_WINDOW_WIDTH, HP_WINDOW_HEIGHT);
}

void HP::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawRect(boundingRect());
    painter->fillRect(QRectF(0, 0, hp / maxhp * HP_WINDOW_WIDTH, HP_WINDOW_HEIGHT), Qt::darkRed);
}

void HP::advance(int phase)
{
    assert(0);
    if (!phase) return;
    update();
    assert(parent != nullptr);
    if (parent->type() == Enemy::Type or parent->type() == Agent::Type) {
        if (parent->type() == Enemy::Type) {
            auto pa = static_cast<Enemy *>(parent);
            hp = pa->hp;
            maxhp = pa->totalhp;
            posx = pa->posx + (CUSTOM_ATK_WIDTH - HP_WINDOW_WIDTH) / 2, posy = pa->posy + CUSTOM_ATK_HEIGHT;
        }
        else {
            auto pa = static_cast<Enemy *>(parent);
            hp = pa->hp;
            maxhp = pa->totalhp;
            posx = pa->posx + (CUSTOM_ATK_WIDTH - HP_WINDOW_WIDTH) / 2, posy = pa->posy + CUSTOM_ATK_HEIGHT;
        }
        setPos(posx, posy);
    }
    else assert(0);
}

HP &HP::operator =(const HP &other)
{
    parent = other.parent;
    posx = other.posx;
    posy = other.posy;
    hp = other.hp;
    maxhp = other.maxhp;
    return *this;
}



