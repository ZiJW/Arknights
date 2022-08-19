#ifndef ENEMY_H
#define ENEMY_H

#include "../../header/common.h"

class Enemy : public QGraphicsItem
{
public:
    explicit Enemy(qreal width, qreal height, qreal block_width, qreal block_height, EnemyPath enemypath, qreal x_block, qreal y_block);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const override;
    void setMovie(QString path);
    void setStateNone();
    void setStateMove();
    void setStateAtk();
    void setStateDead();
    void setStateMoveAtk();
    void setDirect(bool lefttoright);
    void setPath(EnemyPath path);
    void move();

    void notResist();
    void attackOther();
    virtual void moveAtk();
    int moveAtkCounter;
    int atkMovieCounter;
    void attackedByOther(qreal dmg, AttackType typ);
    virtual bool canAttackItem(QGraphicsItem* other);
    virtual bool canBeAttacked();
    void addAttackItem(QGraphicsItem* item);
    void deleteAttackItem(QGraphicsItem* item);
    void addAttackedItem(QGraphicsItem* item);
    void deleteAttackedItem(QGraphicsItem* item);
    void deleteResistItem(QGraphicsItem* item);


    virtual void selectResistItem();
    virtual void selectAtkItem();
    virtual bool canResistItem(QGraphicsItem * item);
    int type() const override;
    void advance(int phase) override;
public:
    enum {Type = UserType + 2};
    QString name;

    qreal hp;
    qreal totalhp;
    qreal phydefence;
    qreal magdefence;

    qreal attack;
    AttackType atktype;
    qreal atkradius;
    qreal atkspeed;
    qreal atkInterval;
    qreal atkTimeCounter;


    EnemyState state;
    bool fly;
    bool longDistanceAtk;
    int resistNum;
    qreal speed;

    qreal posx, posy;

    qreal width, height;
    bool left2right;

    EnemyPath enemypath;
    qreal block_width, block_height;
    qreal x_block, y_block;

    QVector<QGraphicsItem *> resistAgent;
    QVector<QGraphicsItem *> atkAgent;
    QVector<QGraphicsItem *> atkedAgent;

protected:
    QMovie *movie;
    int movieFrameCount;

};

const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

#endif // ENEMY_H
