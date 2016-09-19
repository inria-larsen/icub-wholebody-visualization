#ifndef GRAPHICSTORQUEITEM_H
#define GRAPHICSTORQUEITEM_H
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QObject>
#include <QPainter>
class GraphicsTorqueItem : public QGraphicsRectItem
{
private:
    int r,g,b;
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        QRectF rect = boundingRect();
        QPen pen(Qt::NoPen);
        QBrush brush(QColor(r,g,b));

        painter->setPen(pen);
        painter->setBrush(brush);
        painter->drawRect(rect);
    }
    void setColor(int r,int g, int b)
    {
        this->r=r;
        this->g=g;
        this->b=b;
    }
};

#endif // GRAPHICSTORQUEITEM_H
