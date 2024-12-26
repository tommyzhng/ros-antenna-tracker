#ifndef ANTENNA_TRACKER_HPP
#define ANTENNA_TRACKER_HPP

#include <Arduino.h>
#include <ESP32Servo.h>
#undef ESP32
#include <ros.h>
#define ESP32
#include <geometry_msgs/Point.h>

class AntennaTracker {
public:
    AntennaTracker();
    ~AntennaTracker();
    void UpdateAngle();
    static void angleCb(const geometry_msgs::Point &msg);

private:
    static geometry_msgs::Point angleMsg_;
    Servo panServo_;
    Servo tiltServo_;
    int panPin_{15};
    int tiltPin_{16};
};

#endif // ANTENNA_TRACKER_HPP
