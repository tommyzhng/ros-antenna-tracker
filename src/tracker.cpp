#include "tracker.hpp"

Tracker::Tracker(ros::NodeHandle &nh)
{
    double antenna_longitude, antenna_latitude;
    nh.getParam("antenna_latitude", antenna_latitude);
    nh.getParam("antenna_longitude", antenna_longitude);
    nh.getParam("antenna_initial_heading", antAngle_);

    antAngle_ = std::fmod((450 - antAngle_), 360);  // convert from NED to ENU yaw
    antennaRadLLA_ << antenna_latitude * DEG_TO_RAD, antenna_longitude * DEG_TO_RAD, 0;

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
        antennaRadLLA_.z() = msg.altitude;
        altitudeInitialized_ = true;
    }
    droneRadLLA_ << msg.latitude * DEG_TO_RAD, msg.longitude * DEG_TO_RAD, msg.altitude;
    Tracker::CalculateDroneAngle();
}

void Tracker::CalculateDroneAngle()
{
    // Earth radius in meters
    constexpr double EARTH_RADIUS = 6371000.0;

    // Compute differences in latitude and longitude
    double deltaLat = droneRadLLA_.x() - antennaRadLLA_.x();
    double deltaLon = droneRadLLA_.y() - antennaRadLLA_.y();

    // Calculate the delta in meters for x (East-West) and y (North-South)
    double deltaX = EARTH_RADIUS * cos(antennaRadLLA_.x()) * deltaLon; // East-West distance
    double deltaY = EARTH_RADIUS * deltaLat;                           // North-South distance

    droneAngle_ = atan2(deltaY, deltaX) * (180 / M_PI);   
    droneAngle_ = std::fmod((droneAngle_ + 360), 360); // convert to 0-360
    Tracker::CalculateServoCommand();
}

void Tracker::CalculateServoCommand()
{
    servoDelta_ = droneAngle_ - antAngle_; // calculate the error
}

void Tracker::PublishAngles()
{
    geometry_msgs::Point angleMsg;
    angleMsg.x = servoDelta_;
    angleMsg.y = droneAngle_;
    angleMsg.z = 0.0;
    anglesPub_.publish(angleMsg);
}
void Tracker::Update()
{
    Tracker::PublishAngles();
}

