#include "../../header/enemy/enemy.h"
#include "../../header/agent/agent.h"
#include "../../header/agent/agentcard.h"

Enemy::Enemy(qreal width, qreal height, qreal block_width, qreal block_height, EnemyPath enemypath, qreal x_block, qreal y_block)
    : width(width), height(height), block_width(block_width), block_height(block_height), enemypath(enemypath), x_block(x_block), y_block(y_block)
{
    posx = block_width * x_block, posy = block_height * y_block;
    name = "new enemy";
    hp =  totalhp = 0;
    phydefence = 0;
    magdefence = 0.0;
    attack = 0;
    atktype = AttackType_None;
    atkradius = atkspeed = atkInterval = atkTimeCounter = 0.0;
    state = EnemyState_None;
    fly = false;
    longDistanceAtk = false;
    speed = 0;
    movie = nullptr;
    setX(posx);
    setY(posy);
    this->setFlag(ItemIsSelectable);
}

QRectF Enemy::boundingRect() const {
    return QRectF(0, 0, width, height);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if (movie) {
        QImage tmp = movie->currentImage();
        if (not left2right) tmp = tmp.mirrored(true, false);
        painter->drawImage(boundingRect(), tmp.scaled((int) width, (int) height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        painter->drawRect(boundingRect());
        painter->drawRect(QRectF(0, CUSTOM_ATK_HEIGHT - HP_WINDOW_HEIGHT, HP_WINDOW_WIDTH, HP_WINDOW_HEIGHT));
        painter->fillRect(QRectF(0, CUSTOM_ATK_HEIGHT - HP_WINDOW_HEIGHT, fmax(HP_WINDOW_WIDTH * hp / totalhp, 0), HP_WINDOW_HEIGHT), Qt::darkRed);
    }
    else {
        qDebug() << "No matching movie to " + name;
    }
}

QPainterPath Enemy::shape() const
{
    QPainterPath ret;
    ret.addRect(boundingRect());
    return ret;
}

void Enemy::setMovie(QString path) {
    if (movie) delete movie;
    movie = new QMovie(path);
    movie->start();
    movieFrameCount = movie->frameCount();
}

void Enemy::setStateNone() {
    if (state != EnemyState_None) state = EnemyState_None;
    setMovie(":/enemy/" + name + "/None");
}

void Enemy::setStateMove() {
    state = EnemyState_Move;
    setMovie(":/enemy/" + name + "/Move");
}

void Enemy::setStateAtk() {
    state = EnemyState_Attack;
    setMovie(":/enemy/" + name + "/None");
    atkTimeCounter = atkInterval * 1000;
    atkMovieCounter = 0;
}

void Enemy::setStateDead() {
    state = EnemyState_Dead;
    setMovie(":/enemy/" + name + "/Dead");
}

void Enemy::setStateMoveAtk()
{
    state = EnemyState_MoveAttack;
    setMovie(":/enemy/" + name + "/Move");
}

void Enemy::setDirect(bool lefttoright)
{
    left2right = lefttoright;
}

void Enemy::setPath(EnemyPath path)
{
    enemypath = path;
}

void Enemy::move()
{
    if (enemypath.empty()) {
        if (state != EnemyState_None) setStateNone();
        //setX(-width);
        //setY(-height);
        delete this;
        return;
    }
    if (state == EnemyState_Move or state == EnemyState_MoveAttack) {
        qreal movedx = posx - x_block * block_width, movedy = posy - y_block * block_height;
        if (enemypath.front() == MoveLeft) left2right = false;
        if (enemypath.front() == MoveRight) left2right = true;
        if (abs(movedx) >= block_width or abs(movedy) >= block_height) {
            //setStateNone();
            x_block += dx[enemypath.front()];
            y_block += dy[enemypath.front()];
            posx = x_block * block_width, posy =  y_block * block_height;
            enemypath.dequeue();
            //setStateMove();
        }
        else {
            posx += dx[enemypath.front()] * speed;
            posy += dy[enemypath.front()] * speed;
        }
        setX(posx);
        setY(posy);
    }
}

void Enemy::notResist()
{
}

void Enemy::attackOther()   //defualt model is find the blocked agent
{
    if (atkTimeCounter < atkInterval * 1000)  {
        atkTimeCounter += TOTALNEWMSEC;
        atkMovieCounter = 0;
    }
    else {
        if (atkMovieCounter == 0) {
            setMovie(":/enemy/" + name + "/Atk");
        }
        atkMovieCounter++;
        if (atkMovieCounter > movieFrameCount * 2) {
            atkTimeCounter -= atkInterval * 1000;
            atkMovieCounter = 0;
            setMovie(":/enemy/" + name + "/None");
            if (not atkAgent.empty()) {
                Agent * agent = qgraphicsitem_cast<Agent *>(atkAgent[0]);
                agent->attackedByOther(attack, atktype);
            }
            else assert(0);
            return;
        }
    }
}

void Enemy::moveAtk()
{
    if (atkTimeCounter <= atkInterval * 1000)  {
        atkTimeCounter += TOTALNEWMSEC;
        move();
        atkMovieCounter = 0;
    }
    else {
        if (atkAgent.empty()) {
            move();
            return;
        }
        if (atkMovieCounter == 0) setMovie(":/enemy/" + name + "/Atk");
        atkMovieCounter++;
        if (atkMovieCounter >= movieFrameCount * 2) {
            atkTimeCounter -= atkInterval * 1000;
            atkMovieCounter = 0;
            setMovie(":/enemy/" + name + "/Move");
            if (not atkAgent.empty()) {
                Agent * agent = qgraphicsitem_cast<Agent *>(atkAgent[0]);
                agent->attackedByOther(attack, atktype);
            }
            else assert(0);
            return;
        }
    }
}

void Enemy::attackedByOther(qreal dmg, AttackType typ)
{
    if (typ == AttackType_Physical) hp -= fmax(30, dmg - phydefence);
    else if (typ == AttackType_Magic) hp -= dmg * fmax(0.01, 1 - magdefence);
    else {
        assert(atktype = AttackType_Real);
        hp -= dmg;
    }
}

bool Enemy::canAttackItem(QGraphicsItem *other)
{
    return other->type() == Agent::Type;
}

bool Enemy::canBeAttacked()
{
    if (state == EnemyState_Dead or state == EnemyState_None) return false;
    else return true;
}

void Enemy::addAttackItem(QGraphicsItem *item)
{
    if (atkAgent.indexOf(item) == -1) atkAgent.push_back(item);
}

void Enemy::addAttackedItem(QGraphicsItem *item)
{
    if (atkedAgent.indexOf(item) == -1) atkedAgent.push_back(item);
}

void Enemy::deleteAttackItem(QGraphicsItem *item)
{
    if (atkAgent.indexOf(item) != -1) atkAgent.erase(atkAgent.begin() + atkAgent.indexOf(item));
    else assert(0);
}

void Enemy::deleteAttackedItem(QGraphicsItem *item)
{
    if (atkedAgent.indexOf(item) != -1) atkedAgent.erase(atkedAgent.begin() + atkedAgent.indexOf(item));
    else assert(0);
}

void Enemy::deleteResistItem(QGraphicsItem *item)
{
    if (resistAgent.indexOf(item) != -1) resistAgent.erase(resistAgent.begin() + resistAgent.indexOf(item));
    else assert(0);
}

void Enemy::selectResistItem()
{
     QList<QGraphicsItem *> items = this->collidingItems(Qt::IntersectsItemBoundingRect);
     foreach(QGraphicsItem * item, items) {
         if (resistAgent.indexOf(item) != -1) continue;
         if (canResistItem(item)) {
             assert(item->type() == Agent::Type);
             Agent* tmp = static_cast<Agent*>(item);
             if (tmp->canResistItem(this, resistNum)) {
                tmp->addResistItem(this, resistNum);
                resistAgent.push_back(item);
             }
         }
     }
}

void Enemy::selectAtkItem()             //default model is select the blocked agent as the attacking aim
{
    if (longDistanceAtk and resistAgent.empty()) {              //if can attack from distance then select one agent appear last
        atkAgent.clear();
        foreach(QGraphicsItem * item, scene()->items()) {
            if (item->type() == Agent::Type and canAttackItem(item)) {
                Agent * tmp = static_cast<Agent *>(item);
                if (not tmp->canBeAttacked()) continue;
                qreal agtPosx = item->x() + item->boundingRect().width() / 2;
                qreal agtPosy = item->y() + item->boundingRect().height() / 2;
                qreal selfPosx = posx + width / 2;
                qreal selfPosy = posy + width / 2;
                qreal distance = sqrt(pow(agtPosx - selfPosx, 2) + pow(agtPosy - selfPosy, 2));
                if (distance <= atkradius * width) {
                    this->addAttackItem(item);
                    tmp->addAttackedItem(this);
                    break;
                }
            }
            /*if (item->type() == Enemy::Type and canAttackItem(item)) {
                Enemy * tmp = static_cast<Enemy *>(item);
                if (not tmp->canBeAttacked()) continue;
                qreal agtPosx = item->x() + item->boundingRect().width() / 2;
                qreal agtPosy = item->y() + item->boundingRect().height() / 2;
                qreal selfPosx = posx + width / 2;
                qreal selfPosy = posy + width / 2;
                qreal distance = sqrt(pow(agtPosx - selfPosx, 2) + pow(agtPosy - selfPosy, 2));
                if (distance <= atkradius * width) {
                    this->addAttackItem(item);
                    tmp->addAttackedItem(this);
                    break;
                }
            }*/
        }
    }
    else {                      //otherwise, select one item from blocked
                                //default module is the only blocked agent
        foreach(QGraphicsItem * item, resistAgent) {
            if (atkAgent.indexOf(item) != -1) continue;
            if (item->type() == Agent::Type) {
                Agent * tmp = static_cast<Agent *>(item);
                if (not tmp->canBeAttacked()) continue;
                this->addAttackItem(item);
                tmp->addAttackedItem(this);
            }
            else if (item->type() == Enemy::Type) {
                Enemy * tmp = static_cast<Enemy *>(item);
                if (not tmp->canBeAttacked()) continue;
                this->addAttackItem(item);
                tmp->addAttackedItem(this);
            }
            else assert(0);
        }
    }
}

bool Enemy::canResistItem(QGraphicsItem *item)
{
    return item->type() == Agent::Type;
}



int Enemy::type() const
{
    return Type;
}

void Enemy::advance(int phase)
{
    if (!phase) return;
    update();
    if (hp <= 0 and state != EnemyState_Dead) {
        //delete the resist agent
        foreach(QGraphicsItem *item , resistAgent) {
            Agent * agent = qgraphicsitem_cast<Agent *>(item);
            agent->deleteResistItem(this, resistNum);
        }
        resistAgent.clear();
        //delete the attack item
        foreach(QGraphicsItem* item, atkAgent) {
            if (item->type() == Agent::Type) {
                Agent* tmp = static_cast<Agent*>(item);
                tmp->deleteAttackedItem(this);
            }
            else if (item->type() == Enemy::Type) {
                Enemy* tmp = static_cast<Enemy*>(item);
                tmp->deleteAttackedItem(this);
            }
            else assert(0);
        }
        atkAgent.clear();
        //delete the attacked item
        foreach(QGraphicsItem * item, atkedAgent) {
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
        atkedAgent.clear();
        setStateDead();
        update();
        return;
    }
    if (state == EnemyState_Dead) {
        if (movieFrameCount > 0) {
            movieFrameCount --;
            update();
            return;
        }
        else {
            update();
            delete this;
            return;
        }
    }
    selectResistItem();
    selectAtkItem();
    if (resistAgent.empty()) {
        if (state != EnemyState_Move and not longDistanceAtk) setStateMove();
        if (state != EnemyState_MoveAttack and longDistanceAtk) setStateMoveAtk();
    }
    else {
        if (not atkAgent.empty() and state != EnemyState_Attack) setStateAtk();
        else if (atkAgent.empty() and state != EnemyState_None) setStateNone();
    }
    if (state == EnemyState_Attack) attackOther();
    else if (state == EnemyState_Move) move();
    else if (state == EnemyState_MoveAttack) moveAtk();
    else if (state == EnemyState_None) assert(0);
    else assert(0);
}

