#ifndef ROS_ANTENNA_TRACKER_TRACKER_HPP
#define ROS_ANTENNA_TRACKER_TRACKER_HPP

#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>
#include <geometry_msgs/Point.h>
#include <eigen3/Eigen/Dense>

class Tracker
{
public:
    Tracker(ros::NodeHandle &nh);
    ~Tracker();
private:
    void RecieveDronePositionCb(sensor_msgs::NavSatFix msg);
    void ConvertEf2Lf();
    void CalculateError();
    void PublishAngles();

    bool altitudeInitialized_{false};

    ros::Subscriber dronePositionSub_;
    ros::Publisher anglesPub_;

    Eigen::Vector3f droneLLA_;  // current global position of the drone
    Eigen::Vector3f antennaLLA_{0, 0, 0}; // initial global position of the drone at boot
    Eigen::Vector3f localError_;
};

#endif