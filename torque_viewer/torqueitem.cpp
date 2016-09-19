#include <sstream>
#include <iomanip>
#include <iostream>
#include <QBrush>
#include <QPen>
#include <QObject>
#include "graphicstorqueitem.h"
#include "torqueitem.h"

TorqueItem::TorqueItem(int x,int y,int offx,int offy,const std::string &name,QGraphicsScene *scene,double min_torque,double max_torque)
    : x(x), y(y), offx(offx), offy(offy),name(name),
      torque(0), min_torque(min_torque),max_torque(max_torque),
      max_width(16),height(18)
{
  int datax=x+offx+max_width;
  int datay=y+offy;

  rect=new GraphicsTorqueItem();
  rect->setRect(datax,datay-height/2,0,height);
  text=new QGraphicsSimpleTextItem("???");
  // TODO proper pos, knowing size etc.
  text->setPos(datax+max_width+8,datay-12);
  scene->addItem(rect);
  scene->addItem(text);
  scene->addRect(datax-max_width-2,datay-height/2-2,max_width*2+4,height+4);
  alert=scene->addPixmap(QPixmap(":/images/images/warning.png"));
  double scale=0.2;
  alert->setScale(scale);
  QRectF r=alert->boundingRect();
  alert->setPos(x-r.width()/2.0*scale,y-r.height()/2.0*scale);
  alert->hide();
}

TorqueItem::~TorqueItem()
{
}

void TorqueItem::update(double torque)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << torque;
    text->setText(QString::fromStdString(stream.str()));
    if (torque>=0)
    {
        double norm_torque=torque/max_torque;
        if (norm_torque>1.0)
        {
            norm_torque=1.0;
            alert->show();
        }
        else
        {
            alert->hide();
        }

        int w=norm_torque*255;
        rect->setColor(w,255-w,128);
        rect->setRect(x+offx+max_width,y+offy-height/2,norm_torque*max_width,height);
    }
    else
    {
        double norm_torque=torque/min_torque;
        if (norm_torque>1.0)
        {
            norm_torque=1.0;
            alert->show();
        }
        else
        {
            alert->hide();
        }

        int w=norm_torque*255;
        rect->setColor(w,255-w,128);
        rect->setRect(x+offx+max_width-norm_torque*max_width,y+offy-height/2,norm_torque*max_width,height);

    }
}

void TorqueItem::set_torque(double torque)
{
    QMetaObject::invokeMethod(this,"update",Q_ARG(double,torque));
}
