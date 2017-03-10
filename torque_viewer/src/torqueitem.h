#ifndef TORQUEITEM_H
#define TORQUEITEM_H
#include <QObject>
#include <QMetaObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QBrush>
#include "graphicstorqueitem.h"
/**
 * @brief The TorqueItem class is a graphical representation of a single torque
 */
class TorqueItem : public QObject
{
  Q_OBJECT
protected:
  int x,y; // joint position
  int offx,offy; // translation from joint position to where the gauge and text will be shown
  int max_width;
  int height;
  std::string name;
  GraphicsTorqueItem * rect;
  QGraphicsSimpleTextItem * text;
  QGraphicsPixmapItem *alert;
  double torque;
  double min_torque;
  double max_torque;
public:
  TorqueItem(int x,int y,int offx,int offy,const std::string &name,QGraphicsScene *scene,double min_torque=-1.0, double max_torque=1.0);

  ~TorqueItem();

  Q_INVOKABLE void update(double torque);

  void set_torque(double torque);
};

#endif // TORQUEITEM_H
