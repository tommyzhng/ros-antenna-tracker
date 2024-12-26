#ifndef ROS_ANTENNA_TRACKER_TRACKER_HPP
#define ROS_ANTENNA_TRACKER_TRACKER_HPP

#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>
#include <geometry_msgs/Point.h>
#include <eigen3/Eigen/Dense>
#include <cmath>

#define DEG_TO_RAD (M_PI/180)
#define SCALING_FACTOR 1e7

class Tracker
{
public:
    Tracker(ros::NodeHandle &nh);
    ~Tracker();
    void Update();
private:
    void RecieveDronePositionCb(sensor_msgs::NavSatFix msg);
    void CalculateDroneAngle();
    void CalculateServoCommand();
    void PublishAngles();


    bool altitudeInitialized_{false};

    // error calculations
    double servoDelta_{0};
    double droneAngle_{0};
    double antAngle_{0}; // this is in NED from the compass

    ros::Subscriber dronePositionSub_;
    ros::Publisher anglesPub_;

    Eigen::Vector3d droneRadLLA_{0, 0, 0};  // current global position of the drone
    Eigen::Vector3d antennaRadLLA_{0, 0, 0}; // initial global position of the drone at boot
    Eigen::Vector3d globalError_{0, 0, 0};
};

#endif