#include <iostream>
#include <yarp/os/all.h>
#include "torqueview.h"
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

using namespace yarp::os;

TorqueView::TorqueView() : QGraphicsView()
{
    scene = new QGraphicsScene();
    QPixmap pixmap(":/images/images/icub.png");
    width=pixmap.size().width();
    height=pixmap.size().height();
    setProperty("verticalScrollBarPolicy",Qt::ScrollBarAlwaysOff);
    setProperty("horizontalScrollBarPolicy",Qt::ScrollBarAlwaysOff);
    QGraphicsPixmapItem *pixmap_item=scene->addPixmap(pixmap);
    setScene(scene);
}

void TorqueView::resizeEvent(QResizeEvent *event)
{
  fitInView(0,0,width,height,Qt::KeepAspectRatio);
  QGraphicsView::resizeEvent(event);
}

QGraphicsScene *TorqueView::getScene()
{
    return scene;
}
