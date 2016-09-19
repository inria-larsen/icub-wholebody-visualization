export YARP_ROBOT_NAME=icubGazeboSim
gzserver ~/icub.world &
sleep 1
wholeBodyDynamicsTree --autoconnect


