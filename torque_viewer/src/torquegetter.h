#ifndef TORQUEGETTER_H
#define TORQUEGETTER_H

#include <string>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <yarp/os/all.h>
#include <yarp/os/ResourceFinder.h>
#include "torqueitem.h"

/**
 * @brief The TorqueGetter class is in charge of representing all torques from a single port
 */
class TorqueGetter : public yarp::os::BufferedPort<yarp::os::Bottle>
{    
protected:
  QGraphicsScene *scene;
  int nb_items;
  TorqueItem **items;
  std::string name;
  std::string prefix;
public:
    explicit TorqueGetter(QGraphicsScene *scene, const std::string &name, const std::string &prefix, yarp::os::ResourceFinder &rf);    
    ~TorqueGetter();

    using yarp::os::BufferedPort<yarp::os::Bottle>::onRead;
  virtual void onRead(yarp::os::Bottle& b);
  void autoconnect();
};

#endif
