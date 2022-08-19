#include "../../header/map/fightmap.h"
#include "../../header/agent/agentcard.h"
#include "../../header/agent/melantha.h"
#include "../../header/agent/skadi.h"
#include "../../header/agent/silverash.h"
#include "../../header/agent/exusiai.h"
#include "../../header/agent/eyjafjalla.h"
#include "../../header/agent/placeagent.h"

FightMap::FightMap(int startx, int starty, int x_num, int y_num, int width, int height, QVector<QPixmap *> appear, QVector<QVector<QPair<int, int> > >block2fig)
    : startx(startx), starty(starty), x_num(x_num), y_num(y_num), width(width), height(height), appear(appear)
{
    assert(width == height);
    QVector<MapBlock> emp;
    for (int i = 0; i < y_num; i++) {
        fightmap.push_back(emp);
        for (int j = 0; j < x_num; j++) {
            //MapBlock *tmp = new MapBlock(height, width, startx + j * width, starty + i * height, appear[block2fig[i][j].first], block2fig[i][j].second);
            fightmap[i].push_back(MapBlock(height, width, startx + j * width, starty + i * height, appear[block2fig[i][j].first], block2fig[i][j].second));
            //scene()->addItem(tmp);
        }
    }
    dragOver = false;
    placingBlock = false;
    setAcceptDrops(true);
}

QRectF FightMap::boundingRect() const {
    return QRectF(startx, starty, x_num * width, y_num * height);
}

void FightMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    for (int i = 0; i < y_num; i++) {
        for (int j = 0; j < x_num; j++) {
            fightmap[i][j].paint(painter, nullptr, nullptr);
        }
    }
    return;
}

void FightMap::advance(int phase)
{
}

void FightMap::addAgent(QString name, QPointF pos, int block_x, int block_y, AgentTowards toward)
{
    Agent *test;
    if (name == "Melantha") {
        test = new Melantha(this, block_x, block_y, pos.x(), pos.y(), toward);
    }
    else if (name == "Skadi") {
        test = new Skadi(this, block_x, block_y, pos.x(), pos.y(), toward);
    }
    else if (name == "Exusiai") {
        test = new Exusiai(this, block_x, block_y, pos.x(), pos.y(), toward);
    }
    else if (name == "Eyjafjalla") {
        test = new Eyjafjalla(this, block_x, block_y, pos.x(), pos.y(), toward);
    }
    else if (name == "SilverAsh") {
        test = new SilverAsh(this, block_x, block_y, pos.x(), pos.y(), toward);
    }
    else assert(0);

    //TODO
    //Add more agent
    scene()->addItem(test);
    addAgentSet(test);
}

void FightMap::addPlaceAgent(QString name, QPointF pos, int block_x, int block_y)
{
    placingTmpAgent = new PlaceAgent(this, name, pos, block_x, block_y);
    scene()->addItem(placingTmpAgent);
}

void FightMap::transAgentCard()
{
    for (int i = 0; i < AgentCardSet.size(); i++) {
        delete AgentCardSet[i];
    }
    AgentCardSet.clear();
    for (int i = 0; i < AgentCardName.size(); i++) {
        AgentCard * tmp = new AgentCard(this, AgentCardName[i], width * x_num - CUSTOM_AGTCARD_WIDTH * (i + 1), height* y_num, CUSTOM_AGTCARD_WIDTH, CUSTOM_AGTCARD_HEIGHT);
        AgentCardSet.push_back(tmp);
        scene()->addItem(tmp);
    }
}

void FightMap::setAgentCard(QVector<QString> tmp)
{
    assert(tmp.size() <= 12);
    AgentCardName = tmp;
}

void FightMap::addAgentCard(QString name)
{
    assert(AgentCardName.size() <= 11);
    if (AgentCardName.indexOf(name) == -1) AgentCardName.push_back(name);
    transAgentCard();
}

void FightMap::addAgentSet(Agent *tmp)
{
    AgentSet.push_back(tmp);
    assert(AgentSet.size() <= 12);
}

void FightMap::deleteAgentSet(Agent *tmp)
{
    if (AgentSet.indexOf(tmp) != -1) {
        AgentSet.erase((AgentSet.begin() + AgentSet.indexOf(tmp)));
    }
    else assert(0);
}

bool FightMap::deleteAgentCard(QString name)
{
    if (AgentCardName.indexOf(name) == -1) return false;
    else {
        AgentCardName.erase(AgentCardName.begin() + AgentCardName.indexOf(name));
        transAgentCard();
        return true;
    }
}

void FightMap::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText()) {
        if (event->mimeData()->hasImage()){
            if (placingBlock) return;
            QString s = event->mimeData()->text();
            char name[30];
            qreal timenow, timeneed;
            int cost;
            AgentPlaceType placetype;
            std::string tmp = s.toStdString();
            std::sscanf(tmp.c_str(), "Timenow:%lf Timeneed:%lf Cost:%d Name:%s PlaceType:%d",&timenow, &timeneed, &cost, name, &placetype);
            placingName = QString::fromStdString(std::string(name));
            if (timeneed * 1000 < timenow and coster->cost >= cost) {
                placingPos = mapToScene(event->pos());
                int posx = placingPos.x(), posy = placingPos.y();
                posx = (posx / width) * width, posy = (posy / height) * height;
                int block_x = posx / width, block_y = posy / height;

                //handle the wrong placing of agent
                //高台干员放在了地面上或者地面干员放在了高台上都直接返回
                if (fightmap[block_y][block_x].state == BlockState_End) return;
                if (fightmap[block_y][block_x].state == BlockState_Start) return;
                if (fightmap[block_y][block_x].state == BlockState_None) return;
                if (fightmap[block_y][block_x].state == BlockState_None2) return;
                if (fightmap[block_y][block_x].state == BlockState_Ground) if (placetype == AgentPlaceType_PlotOnly) return;
                if (fightmap[block_y][block_x].state == BlockState_Plat) if (placetype == AgentPlaceType_GroundOnly) return;

                placingPos.setX(posx), placingPos.setY(posy);
                addPlaceAgent(placingName, placingPos, posx / width, posy / height);
                coster->cost -= cost;
                placingBlock = true;
            }
        }
        else {
            assert(placingBlock);
            QPointF pos = mapToScene(event->pos());
            int posx = pos.x(), posy = pos.y();
            qreal cx = placingPos.x() + CUSTOM_ATK_WIDTH / 2;
            qreal cy = placingPos.y() + CUSTOM_ATK_HEIGHT / 2;
            qreal dx = posx - cx;
            qreal dy = posy - cy;
            if (abs(dx) > abs(dy)) addAgent(placingName, placingPos, placingPos.x() / width, placingPos.y() / width, {dx / abs(dx), 0});
            else addAgent(placingName, placingPos, placingPos.x() / width, placingPos.y() / width, {0, dy / abs(dy)});
            assert(deleteAgentCard(placingName));
            placingBlock = false;
            delete placingTmpAgent;
        }
    }
    update();
}

void FightMap::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText())
    {
        event->setAccepted(true);
        dragOver = true;
        update();
    }
    else
        event->setAccepted(false);
}

void FightMap::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    dragOver = false;
    update();
}

void FightMap::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event->key();
}

qreal FightMap::getCost()
{
    return coster->cost;
}


