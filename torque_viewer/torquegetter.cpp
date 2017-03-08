#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <yarp/os/all.h>
#include <yarp/os/Property.h>
#include "torquegetter.h"
#include "torqueitem.h"

using namespace yarp::os;

TorqueGetter::TorqueGetter(QGraphicsScene *scene, const std::string &name, const std::string &prefix, yarp::os::Property &prop) : BufferedPort<Bottle>(), scene(scene) , name(name), prefix(prefix)
{   
  const yarp::os::Value &v=prop.findGroup("TORQUE_PORTS").find(name);
  if (!v.isNull())
  {
    const yarp::os::Bottle *joint_list=v.asList()->get(1).asList();
    nb_items=joint_list->size();
    items=new TorqueItem*[nb_items];
    
    for (int i=0;i<nb_items;i++)
    {
      std::string joint_name=joint_list->get(i).asString();
      const yarp::os::Value &joint_xy=prop.findGroup("TORQUE_XY").find(joint_name);
      const yarp::os::Value &joint_limits=prop.findGroup("TORQUE_LIMITS").find(joint_name);
      
      if (joint_xy.isList() && joint_limits.isList())
      {
        // TODO check if valid
        int x=joint_xy.asList()->get(0).asInt();
        int y=joint_xy.asList()->get(1).asInt();
        int offx=joint_xy.asList()->get(2).asInt();
        int offy=joint_xy.asList()->get(3).asInt();
        
        double min_torque=joint_limits.asList()->get(0).asDouble();
        double max_torque=joint_limits.asList()->get(1).asDouble();
        
        items[i]=new TorqueItem(x,y,offx,offy,joint_name,scene,min_torque,max_torque);
      }
      else
      { 
        items[i]=NULL;
        std::cerr << "cannot find joint position or limits for " << joint_name << std::endl;
      }
    }
    this->useCallback();
    this->open("/torqueviewer/"+name+"/torques:i");
  }
  else
  {
    items=NULL;
    std::cerr << "warning: "+name+" not found in config file" << std::endl;
  }
}

TorqueGetter::~TorqueGetter()
{
  for (int i=0;i<nb_items;i++)
  {
    delete items[i];
  }
  delete[] items;
}

void TorqueGetter::autoconnect()
{
    Network::connect("/"+prefix+"/"+name+"/Torques:o","/torqueviewer/"+name+"/torques:i");
}

void TorqueGetter::onRead(yarp::os::Bottle& b)
{
  if (b.size()-1==nb_items)
  {
    for (int i=0;i<nb_items;i++)
    {
      double torque=b.get(1+i).asDouble();
      if (items[i])
      {
        items[i]->set_torque(torque);
      }        
    }    
  }
  else
  {
    std::cerr << "*** error: bottle of size " << b.size() << " instead of "<< nb_items+1 << std::endl;
  }
}
