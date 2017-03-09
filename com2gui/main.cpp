#include <yarp/os/all.h>
#include <yarp/os/ResourceFinder.h>
#include <yarp/os/Property.h>

using namespace yarp::os;

void usage(void)
{    
    yInfo()<< "Parameters";
    yInfo()<< "    --name      : default is com2gui";
    yInfo()<< "    --wholebody : default is wholeBodyDynamicsTree";
}

int main(int argc, char *argv[])
{ 
  Network yarp;
  ResourceFinder rf;
  BufferedPort<Bottle> inPort, outPort;
  
  rf.setVerbose(true);
  rf.configure(argc,argv);

  if (rf.check("help"))
  {
      usage();
      return 0;
  }
  
  std::string name=rf.check("name",Value("com2gui")).asString();
  std::string wholebody=rf.check("wholebody",Value("wholeBodyDynamicsTree")).asString();
  
  bool ok=inPort.open("/"+name+"/COM:i");
  ok=ok && outPort.open("/"+name+"/objects:o");
  
  if (!ok) 
  {
    yError() << "Could not open yarp ports - is yarpserver running happily ?";
    return EXIT_FAILURE;
  }
  
  yarp.connect(outPort.getName(),"/iCubGui/objects","udp");
  yarp.connect("/"+wholebody+"/com:o",inPort.getName(),"udp");
  
  yInfo() << "Configured: ";
  yInfo() << "  name= " << name;
  yInfo() << "  wholebody= " <<  wholebody << " (reading from /"+wholebody+"/com:o)";
  yInfo() << "  writing to /iCubGui/objects";
  
  int i=0;
  while (true)
  {
    Bottle *in = inPort.read();                                                                                  
    if (in==NULL) {
      yError() << "Failed to read message";
      return EXIT_FAILURE;
    }
    double x=in->get(0).asDouble();
    double y=in->get(1).asDouble();
    double z=in->get(2).asDouble();
    
    Bottle &obj=outPort.prepare();
    obj.clear();
    
    obj.addString("object"); // command to add/update an object
    obj.addString("COM");
    // object dimensions in mm
    // (it will be displayed as an ellipsoid with the tag "COM")
    obj.addDouble(100);
    obj.addDouble(100);
    obj.addDouble(100);
    // object position in mm
    // reference frame: X=fwd, Y=left, Z=up
    obj.addDouble(x);
    obj.addDouble(y);
    obj.addDouble(z);
    // object orientation (roll, pitch, yaw) in degrees
    obj.addDouble(0);
    obj.addDouble(0);
    obj.addDouble(0);
    // object color (0-255)
    obj.addInt(255);
    obj.addInt(128);        
    obj.addInt(128);
    // transparency (0.0=invisible 1.0=solid)
    obj.addDouble(1.0);
    outPort.write(true);
  }
  return EXIT_SUCCESS;
}
