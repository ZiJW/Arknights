#include "../../header/agent/agentcard.h"
#include "../../header/agent/melantha.h"
#include "../../header/agent/skadi.h"
#include "../../header/agent/eyjafjalla.h"
#include "../../header/agent/silverash.h"
#include "../../header/agent/exusiai.h"
#include "../../header/map/fightmap.h"

#define helper(x) if(name == #x) placed = x::Placed;

AgentCard::AgentCard(QGraphicsItem* parent, QString name, int posx, int posy, int width, int height)
    : parent(parent), name(name), posx(posx), posy(posy), width(width), height(height)
{
    CannotPlaceEffect = new QGraphicsOpacityEffect();
    CannotPlaceEffect->setOpacity(0.7);
    CanPlaceEffect = new QGraphicsOpacityEffect();
    CanPlaceEffect->setOpacity(1.0);
    placed = false;
    timeCounter = 0;
    canPlace = false;
    QFile info(":/agent/" + name + "/info");
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
        needTime = data[2];
        cost = data[3];
        place = data[7];
        info.close();
    }
    else {
        qDebug() << "fail to find or open the file /agent/" + name + "/info";
        assert(0);
    }
    bool placed = false;
    helper(Melantha)
    helper(Skadi)
    helper(Exusiai)
    helper(Eyjafjalla)
    helper(SilverAsh)
    //TODO
    //Add more agent
    if (not placed) {
        timeCounter = needTime * 1000;
    }
}

QRectF AgentCard::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

void AgentCard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    setX(posx);
    setY(posy);
    painter->drawPixmap(QRect(0, 0, width, height), QPixmap(":/agent/" + name + "/Portrait").scaled(width, height, Qt::KeepAspectRatio));
    painter->setPen(Qt::black);
    QFont font;
    font.setPixelSize(15);
    painter->setFont(font);
    painter->drawText(QRectF(width / 4, 0, width / 2, height / 6), Qt::AlignCenter, QString::number((int) cost));
    painter->setPen(Qt::white);
    QString tmp;
    if (fmax(0, needTime - timeCounter / 1000) != 0)
        painter->drawText(QRectF(0, 0, width, height), Qt::AlignCenter, tmp.setNum(fmax(0, needTime - timeCounter / 1000), 'f', 1));
}

void AgentCard::advance(int phase)
{
    if (!phase) return;
    update();
    timeCounter += TOTALNEWMSEC;
    qreal tmpcost = ((FightMap *) (parent))->getCost();                                                                 //parent must be a fightmap
    if (timeCounter > needTime * 1000 and tmpcost >= cost) canPlace = true;
    else canPlace = false;
    if (canPlace) this->setGraphicsEffect(CanPlaceEffect);
    else this->setGraphicsEffect(CannotPlaceEffect);
    if (placed) delete this;
}

void AgentCard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor);
}

void AgentCard::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (not canPlace) return;
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    QImage image(":/agent/" + name + "/Placing");
    image = image.scaled(CUSTOM_ATK_WIDTH, CUSTOM_ATK_HEIGHT, Qt::KeepAspectRatio);
    mime->setText("Timenow:" + QString::number(timeCounter) + " Timeneed:" + QString::number(needTime) + " Cost:" + QString::number(cost) + " Name:" + name + " PlaceType:" + QString::number(place));
    mime->setImageData(image);
    drag->setMimeData(mime);
    drag->setPixmap(QPixmap::fromImage(image));
    drag->setHotSpot(QPoint(CUSTOM_ATK_WIDTH / 2, CUSTOM_ATK_HEIGHT / 2));
    drag->exec();
}

void AgentCard::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    setCursor(Qt::ArrowCursor);
}




