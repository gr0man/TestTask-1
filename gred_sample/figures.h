#ifndef FIGURES_H
#define FIGURES_H

/* Перегруженные классы прямоугольника и эллипса (QGraphicsRectItem и QGraphicsEllipseItem)
   (для коррекции отрисовки)
*/

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

class Rect : public QGraphicsRectItem
{
public:
    Rect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = Q_NULLPTR)
        : QGraphicsRectItem(x, y, width, height, parent)
        , brush(Qt::gray)
        , pen(QBrush(Qt::black), 2)
    {
        setFlag(QGraphicsItem::ItemIsSelectable);
        setBrush(brush);
        setPen(pen);
    }



    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR)
    {
        if(isSelected())
        {
            setSelected(false);
            QGraphicsRectItem::paint(painter, option, widget);
            setSelected(true);

            QRectF boundRect = rect();

            painter->setPen(QPen(QBrush(Qt::blue),2));
            painter->drawRect(boundRect);
        }
        else
            QGraphicsRectItem::paint(painter, option, widget);
    }

private:
    QBrush brush;
    QPen pen;

};


class Ellipse : public QGraphicsEllipseItem
{
public:
    Ellipse(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = Q_NULLPTR)
        : QGraphicsEllipseItem(x, y, width, height, parent)
        , brush(Qt::gray)
        , pen(QBrush(Qt::black), 2)
    {
        setFlag(QGraphicsItem::ItemIsSelectable);
        setBrush(brush);
        setPen(pen);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR)
    {
        QGraphicsEllipseItem::paint(painter, option, widget);

        if(isSelected())
        {
            QRectF boundRect = rect();

            painter->setPen(QPen(QBrush(Qt::blue),2));
            painter->drawRect(boundRect);
        }
    }

private:
    QBrush brush;
    QPen pen;

};
#endif // FIGURES_H
