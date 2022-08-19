#include "../../header/agent/agent.h"
#include "../../header/enemy/enemy.h"
#include "../../header/agent/agentcard.h"
#include "../../header/map/fightmap.h"

Agent::Agent(QGraphicsItem * parent, QString name, int x_block, int y_block, qreal x, qreal y, AgentTowards towards)
    : parent(parent), name(name), x_block(x_block), y_block(y_block), posx(x), posy(y), towards(towards)
{
    movie = nullptr;
    portrait = nullptr;
    painting = nullptr;
    setStateStart();
    setPos(posx, posy);
    atkTimeCounter = 0;
    selected = false;
}

Agent::~Agent()
{
    if (movie) delete movie;
    return;
}

QRectF Agent::boundingRect() const
{
    return QRectF(0, 0, CUSTOM_ATK_WIDTH, CUSTOM_ATK_HEIGHT);
}

void Agent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawImage(boundingRect(), movie->currentImage().scaled(CUSTOM_ATK_WIDTH, CUSTOM_ATK_WIDTH, Qt::KeepAspectRatio));
    painter->drawRect(boundingRect());
    painter->drawRect(QRectF(0, CUSTOM_ATK_HEIGHT - HP_WINDOW_HEIGHT, HP_WINDOW_WIDTH, HP_WINDOW_HEIGHT));
    painter->fillRect(QRectF(0, CUSTOM_ATK_HEIGHT - HP_WINDOW_HEIGHT, fmax(HP_WINDOW_WIDTH * hp / totalhp, 0), HP_WINDOW_HEIGHT), Qt::darkGreen);
}

void Agent::setMovie(QString path)
{
    if (movie) delete movie;
    movie = new QMovie(path);
    MovieCount = movie->frameCount();
    movie->start();
    movieFrameCount = movie->frameCount();
}

void Agent::advance(int phase)
{
    if (!phase) return;
    update();
    assert(state != AgentState_None and state != AgentState_None2);
    if (state == AgentState_Start) {
        if (MovieCount > 0) MovieCount--;
        else {
            setStateWait();
            update();
            return;
        }
    }
    if (hp <= 0 and state != AgentState_Dead) {
        clearResAtkObject();
        //set self dead
        setStateDead();
        return;
    }
    //display the dead movie
    if (state == AgentState_Dead) {
        if (MovieCount > 0) {
            MovieCount --;
            return;
        }
        else {
            FightMap * tmp = static_cast<FightMap *>(parent);
            tmp->deleteAgentSet(this);
            //TODO
            //if exit with no reason, try delete next line
            tmp->addAgentCard(name);
            delete this;
            return;
        }
    }
    selectAttackItem();
    if (atkEnemy.empty()) {
        if (state != AgentState_Wait) setStateWait();
    }
    else if (state != AgentState_Atk) setStateAtk();
    if (state == AgentState_Atk) attackOther();
}

int Agent::type() const
{
    return Type;
}

bool Agent::pressed()
{
    return selected;
}

void Agent::setStateAtk()
{
    state = AgentState_Atk;
    setMovie(":/agent/" + name + "/Atk");
    atkTimeCounter = atkInterval * 1000;
    atkMovieCounter = 0;
}

void Agent::setStateNone()
{
    state = AgentState_None;
    setMovie(":/agent/" + name + "/None");
}

void Agent::setStateDead()
{
    state = AgentState_Dead;
    setMovie(":/agent/" + name + "/Dead");
}

void Agent::setStateStart()
{
    state = AgentState_Start;
    setMovie(":/agent/" + name + "/Start");
}

void Agent::setStateWait()
{
    state = AgentState_Wait;
    setMovie(":/agent/" + name + "/Wait");
}

void Agent::attackOther()
{
    assert(state == AgentState_Atk);
    if (atkTimeCounter < atkInterval * 1000)  {
        atkTimeCounter += TOTALNEWMSEC;
        atkMovieCounter = 0;
    }
    else {
        if (atkMovieCounter == 0) {
            setMovie(":/agent/" + name + "/Atk");
        }
        atkMovieCounter++;
        if (atkMovieCounter > movieFrameCount * 2) {
            atkTimeCounter -= atkInterval * 1000;
            atkMovieCounter = 0;
            setMovie(":/agent/" + name + "/Wait");
            if (not atkEnemy.empty()) {
                Enemy * enemy = qgraphicsitem_cast<Enemy *>(atkEnemy[0]);
                enemy->attackedByOther(attack, atktype);
            }
            else assert(0);
            return;
        }
    }
}

void Agent::attackedByOther(qreal dmg, AttackType typ)
{
    if (typ == AttackType_Physical) hp -= fmax(30, dmg - phydefence);
    else if (typ == AttackType_Magic) hp -= dmg * fmax(0.01, 1 - magdefence);
    else {
        assert(atktype = AttackType_Real);
        hp -= dmg;
    }
}

bool Agent::canAttackItem(QGraphicsItem *other)
{
    if (other == this) return false;
    return other->type() == Enemy::Type;
}

void Agent::selectAttackItem()
{
    QList<QGraphicsItem *> items = this->atkArea.collidingItems(Qt::IntersectsItemShape);
    auto record = atkEnemy;
    foreach(QGraphicsItem *item, atkEnemy) {
        if (items.indexOf(item) == -1) {
            assert(item->type() == Enemy::Type or item->type() == Agent::Type);
            if (item->type() == Enemy::Type) {
                Enemy* tmp = static_cast<Enemy*>(item);
                tmp->deleteAttackedItem(this);
            }
            else if (item->type() == Agent::Type) {
                Agent * tmp = static_cast<Agent *>(item);
                tmp->deleteAttackedItem(this);
            }
            record.erase(record.begin() + record.indexOf(item));
        }
    }
    atkEnemy = record;
    foreach(QGraphicsItem *item, items) {
        if (canAttackItem(item)) {
            assert(item->type() == Enemy::Type or item->type() == Agent::Type);
            if (atkEnemy.indexOf(item) == -1) {
                if (item->type() == Enemy::Type) {
                    Enemy* tmp = static_cast<Enemy*>(item);
                    if (not tmp->canBeAttacked()) continue;
                    tmp->addAttackedItem(this);
                    atkEnemy.push_back(item);
                }
                if (item->type() == Agent::Type) {
                    Agent* tmp = static_cast<Agent*>(item);
                    if (not tmp->canBeAttacked()) continue;
                    tmp->addAttackedItem(this);
                    atkEnemy.push_back(item);
                }
            }
        }
    }
}

bool Agent::canBeAttacked()
{
    if (state == AgentState_None or state == AgentState_Dead or state == AgentState_None2 or state ==  AgentState_Start)
        return false;
    else return true;
}

void Agent::addAttackedItem(QGraphicsItem *item)
{
    if (atkedEnemy.indexOf(item) == -1) atkedEnemy.push_back(item);
}

void Agent::deleteAttackItem(QGraphicsItem *item)
{
    if (atkEnemy.indexOf(item) != -1) atkEnemy.erase(atkEnemy.begin() + atkEnemy.indexOf(item));
    else assert(0);
}

void Agent::deleteAttackedItem(QGraphicsItem *item)
{
    if (atkedEnemy.indexOf(item) != -1) atkedEnemy.erase(atkedEnemy.begin() + atkedEnemy.indexOf(item));
    else assert(0);
}

void Agent::deleteResistItem(QGraphicsItem *item, int resnum)
{
    if (resistEnemy.indexOf(item) != -1) {
        resistEnemy.erase(resistEnemy.begin() + resistEnemy.indexOf(item));
        resistnum -= resnum;
        assert(resistnum >= 0);
    }
    else assert(0);
}

void Agent::addResistItem(QGraphicsItem *item, int resnum)
{
    if (resistEnemy.indexOf(item) == -1) {
        resistEnemy.push_back(item);
        resistnum += resnum;
    }
}

bool Agent::canResistItem(QGraphicsItem *item, int resnum)
{
    if (state == AgentState_Dead or state == AgentState_None or state == AgentState_None2) return false;
    if (resistEnemy.indexOf(item) != -1) return false;
    if (resistnum + resnum <= maxresistnum) return true;
    else return false;
}

void Agent::clearResAtkObject()
{
    //delete self from other blocked enemy
    foreach(QGraphicsItem *item , resistEnemy) {
        Enemy *enemy = qgraphicsitem_cast<Enemy*>(item);
        enemy->deleteResistItem(this);
    }
    resistEnemy.clear();
    //delete self from other enemy atkedobject
    foreach(QGraphicsItem* item, atkEnemy) {
        if (item->type() == Enemy::Type) {
            Enemy* tmp = static_cast<Enemy*>(item);
            tmp->deleteAttackedItem(this);
        }
        else if (item->type() == Agent::Type) {
            Agent* tmp = static_cast<Agent*>(item);
            tmp->deleteAttackedItem(this);
        }
        else assert(0);
    }
    atkEnemy.clear();
    //delete self from other enemy atkobject
    foreach(QGraphicsItem* item, atkedEnemy) {
        if (item->type() == Enemy::Type) {
            Enemy* tmp = static_cast<Enemy*>(item);
            tmp->deleteAttackItem(this);
        }
        else if (item->type() == Agent::Type) {
            Agent* tmp = static_cast<Agent*>(item);
            tmp->deleteAttackItem(this);
        }
        else assert(0);
    }
    atkedEnemy.clear();
}

void Agent::handleInfo(QString path)
{
    QFile info(path);
    QVector<double> data;
    QString s;
    std::string transs;
    if (info.open(QFile::ReadOnly)) {
        QTextStream in(&info);
        for (int i = 0; i < basicAttrNum * 3; i++) {
            in >> s;
            transs = s.toStdString();
            double tmp;
            if (std::sscanf(transs.c_str(), "%lf", &tmp) == 1) {
                data.push_back(tmp);
            }
        }

        elite = data[0];
        level = data[1];
        RedeployTime = data[2];
        cost = data[3];
        maxresistnum = data[4];
        resistnum = 0;
        trust = data[5];
        rarity = data[6];

        hp = totalhp = data[8];
        phydefence = data[9];
        magdefence = data[10];
        attack = data[11];
        atktype = data[12];
        atkradius = data[13];
        atkspeed = data[14];
        atkInterval = data[15];

        int k = data[16];
        QVector<std::complex<qreal> > tmparea;
        while (k --) {
            qreal tmpx, tmpy;
            in >> tmpx >> tmpy;
            tmparea.push_back(std::complex<qreal>(tmpx, tmpy));
        }
        atkArea = AgentAtkArea(this, towards, CUSTOM_ATK_HEIGHT, CUSTOM_ATK_WIDTH, std::complex<qreal>(x_block, y_block), tmparea);
        parent->scene()->addItem(&atkArea);
        info.close();
    }
    else {
        qDebug() << "fail to find or open the file" + path;
        assert(0);
    }
}

void Agent::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    selected = not selected;
}

void Agent::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
}

void Agent::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    FightMap *tmp = (FightMap *) parent;
    tmp->coster->cost += cost / 2;
    clearResAtkObject();
    setStateNone();
    tmp->deleteAgentSet(this);
    tmp->addAgentCard(name);
    delete this;
}

