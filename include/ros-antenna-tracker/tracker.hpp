#ifndef ROS_ANTENNA_TRACKER_TRACKER_HPP
#define ROS_ANTENNA_TRACKER_TRACKER_HPP

#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.msg>
#include <eigen3/Eigen/Dense>

class Tracker
{
public:
    Tracker(ros::NodeHandle &nh);
    ~Tracker();
private:
    void RecieveDronePositionCb();
    void ConvertEf2Bf();
    void CalculateError();
    void PublishAngles();

    Eigen::Vector3f curLLA_;  // current global position of the drone
    Eigen::Vector3f initLLA_; // initial global position of the drone at boot
    Eigen::Vector3f localError_;
};

#endif