#include "graphicsscene.h"

#include <QGraphicsSceneMouseEvent>

#include "command.h"

GraphicsScene::GraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
    , crController(0)
{

}


void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos(event->buttonDownScenePos(Qt::LeftButton).x(),
                         event->buttonDownScenePos(Qt::LeftButton).y());

    if(crController)
    {
        crController->MousePressEvent(pos, this);
    }
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(crController)
    {
        crController->MouseReleaseEvent(this);
    }

    QGraphicsScene::mouseReleaseEvent(event);
}
