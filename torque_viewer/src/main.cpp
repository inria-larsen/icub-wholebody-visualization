#include <vector>
#include <QApplication>
#include <yarp/os/all.h>
#include <yarp/os/ResourceFinder.h>
#include "dialog.h"
#include "torquegetter.h"


// TODO: separate ui/yarp comm (eg. Dialog, ...)

using namespace yarp::os;

void usage(void)
{
    yInfo()<< "Parameters";
    yInfo()<< "    --robot            : Robot name.";
    yInfo()<< "    --autoconnect      : Autoconnect torque ports.";
}

int main(int argc, char *argv[])
{ 
  Network yarp;
  ResourceFinder rf;
  rf.setVerbose(true);
  rf.configure(argc,argv);

  if (rf.check("help"))
  {
      usage();
      return 0;
  }

  bool autoconnect=false;

  if(rf.check("autoconnect") )
  {
      yInfo() << "autoconnect enabled.";
      autoconnect=true;
  }

  QApplication a(argc, argv);
  Dialog w;

  std::vector<TorqueGetter*> torque_getters;
//   yarp::os::Property prop;
//   prop.fromConfigFile("torqueviewer.ini");
  
  ResourceFinder prop;
  prop.setVerbose(); //logs searched directories
  prop.setDefaultConfigFile("torqueviewer.ini"); //specifies a default configuration file
  prop.configure(argc, argv);
  
  std::string prefix=prop.findGroup("MAIN").find("prefix").asString();   
  const yarp::os::Bottle & torques=prop.findGroup("TORQUE_PORTS");
  int size=torques.size()-1;
  torque_getters.resize(size);

  QGraphicsScene * scene=w.getView()->getScene();
  for(int i=0;i<size;i++)
  {
      std::string name=torques.get(i+1).asList()->get(0).asString();
      torque_getters[i]=new TorqueGetter(scene,name,prefix,prop);
  }
  if (autoconnect)
  {
      for (int i=0;i<torque_getters.size();i++)
      {
          torque_getters[i]->autoconnect();
      }
  }
  w.show();

  int r=a.exec();
  for (int i=0;i<torque_getters.size();i++)
  {
      delete torque_getters[i];
  }
  return r;
}
