#ifndef AGENT_H
#define AGENT_H

#include "../../header/common.h"
#include "../../header/agent/agentatkarea.h"

class Agent : public QGraphicsItem
{
public:
    Agent(QGraphicsItem * parent, QString name, int x_block, int y_block, qreal x, qreal y, AgentTowards towards);
    ~Agent();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setMovie(QString path);
    //void setPortrait(QString path);
    //void setPainting(QString path);
    void advance(int phase) override;
    int type() const override;
    bool pressed();

    //set self state
    void setStateAtk();
    void setStateNone();
    void setStateDead();
    void setStateStart();
    void setStateWait();

    //attack other;
    virtual void attackOther();
    void attackedByOther(qreal dmg, AttackType typ);
    virtual bool canAttackItem(QGraphicsItem * other);
    void selectAttackItem();
    bool canBeAttacked();
    void addAttackedItem(QGraphicsItem *item);
    void deleteAttackItem(QGraphicsItem *item);
    void deleteAttackedItem(QGraphicsItem *item);
    void deleteResistItem(QGraphicsItem * item, int resnum);
    void addResistItem(QGraphicsItem * item, int resnum);
    virtual bool canResistItem(QGraphicsItem * item, int resnum);
    void clearResAtkObject();


    void handleInfo(QString path);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
public:
    enum {Type = UserType + 1};
    QGraphicsItem *parent;

    QString name;
    EliteLevel elite;
    Level level;
    int RedeployTime;
    int cost;
    int maxresistnum;
    int resistnum;
    int trust;
    int rarity;

    qreal hp;
    qreal totalhp;
    qreal phydefence;
    qreal magdefence;

    qreal attack;
    AttackType atktype;
    qreal atkradius;
    qreal atkspeed;
    qreal atkInterval;
    AttackRange range;
    qreal atkTimeCounter;
    AgentTowards towards;
    AgentAtkArea atkArea;

    AgentState state;
    QVector<QGraphicsItem *> resistEnemy;
    QVector<QGraphicsItem *> atkEnemy;
    QVector<QGraphicsItem *> atkedEnemy;

    qreal x_block, y_block;
    qreal posx, posy;
protected:
    QMovie *movie;
    QPixmap *portrait;
    QPixmap *painting;
    int MovieCount;
    int atkMovieCounter;
    int movieFrameCount;
    bool selected;
};

#endif // AGENT_H
