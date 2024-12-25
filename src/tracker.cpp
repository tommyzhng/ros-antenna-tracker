#include "tracker.hpp"

Tracker::Tracker(ros::NodeHandle &nh)
{
    float antenna_longitude, antenna_lattitude;
    nh.param("antenna_longitude", antenna_longitude);
    nh.param("antenna_lattitude", antenna_lattitude);
    antennaLLA_ << antenna_longitude, antenna_lattitude, 0;

    dronePositionSub_ = nh.subscribe("/mavros/global_position/global", 1, &Tracker::RecieveDronePositionCb, this);
    anglesPub_ = nh.advertise<geometry_msgs::Point>("/antenna_tracker/angles", 1);
}
Tracker::~Tracker()
{ 

}
void Tracker::RecieveDronePositionCb(sensor_msgs::NavSatFix msg)
{
    // initialize the altitude of the antenna
    if (!altitudeInitialized_){
        antennaLLA_.z() = msg.altitude;
        altitudeInitialized_ = true;
    }
    droneLLA_ << msg.longitude, msg.latitude, msg.altitude;
}