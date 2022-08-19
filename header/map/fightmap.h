#ifndef FIGHTMAP_H
#define FIGHTMAP_H

#include "../../header/common.h"

#include "../../header/map/mapblock.h"
#include "../../header/agent/agent.h"
#include "../../header/agent/agentcard.h"
#include "../../header/map/coster.h"
#include "../../header/agent/placeagent.h"

class FightMap : public QGraphicsItem
{
public:
    FightMap(int startx, int starty, int x_num, int y_num, int width, int height, QVector<QPixmap *> appear, QVector<QVector<QPair<int, int> > >block2fig);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
public:
    enum {Type = UserType + 4};
    int startx, starty;
    int x_num, y_num;
    int width, height;
    bool dragOver;
    QVector<QPixmap *> appear;
    QVector<QVector<MapBlock> > fightmap;
    QVector<QString> AgentCardName;
    QVector<AgentCard *> AgentCardSet;
    QVector<Agent *> AgentSet;
    Coster *coster;
    bool placingBlock;
    QPointF placingPos;
    QString placingName;
    PlaceAgent* placingTmpAgent;
    void addAgent(QString name, QPointF pos, int block_x, int block_y, AgentTowards toward);
    void addPlaceAgent(QString name, QPointF pos, int block_x, int block_y);
    void transAgentCard();
    void setAgentCard(QVector<QString> tmp);
    void addAgentCard(QString name);
    void addAgentSet(Agent* tmp);
    void deleteAgentSet(Agent * tmp);
    bool deleteAgentCard(QString name);
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;
    qreal getCost();
};

#endif // FIGHTMAP_H
