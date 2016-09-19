#include <yarp/os/all.h>
#include <yarp/os/ResourceFinder.h>
#include <yarp/os/Property.h>

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
  BufferedPort<Bottle> inPort, outPort;
  
  rf.setVerbose(true);
  rf.configure(argc,argv);

  if (rf.check("help"))
  {
      usage();
      return 0;
  }

  bool autoconnect=true;

  if(rf.check("autoconnect") )
  {
      yInfo() << "autoconnect enabled.";
      autoconnect=true;
  }
  
  bool ok=inPort.open("/com2gui/COM:i");
  ok=ok && outPort.open("/com2gui/objects:o");
  
  if (!ok) 
  {
    std::cerr << "Could not open yarp ports - is yarpserver alive ?" << std::endl;
    return EXIT_FAILURE;
  }
  if (autoconnect)
  {
    yarp.connect(outPort.getName(),"/iCubGui/objects");
    yarp.connect("/wholeBodyDynamicsTree/com:o",inPort.getName());
  }
  int i=0;
  while (true)
  {
    Bottle *in = inPort.read();                                                                                  
    if (in==NULL) {
      fprintf(stderr, "Failed to read message\n");
      return EXIT_FAILURE;
    }
    double x=in->get(0).asDouble();
    double y=in->get(1).asDouble();
    double z=in->get(2).asDouble();
    
    Bottle &obj=outPort.prepare();
    obj.clear();
    
    obj.addString("object"); // command to add/update an object
    obj.addString("COM");
    // object dimensions in millimiters
    // (it will be displayed as an ellipsoid with the tag "my_object_name")
    obj.addDouble(100);
    obj.addDouble(100);
    obj.addDouble(100);
    // object position in millimiters
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
    
    printf("Sending %s\n", obj.toString().c_str());
    outPort.write(true);
  }
  //Bottle *in = inPort.read();                                                                                  
  //if (in==NULL) {
  //  fprintf(stderr, "Failed to read message\n");
  //}
  return EXIT_SUCCESS;
}
