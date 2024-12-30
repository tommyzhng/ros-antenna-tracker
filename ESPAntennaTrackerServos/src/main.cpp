#include "AntennaTracker.hpp"
AntennaTracker::AntennaTracker()
{
    panServo_.attach(panPin_);
    tiltServo_.attach(tiltPin_);
    panServo_.write(90);
    tiltServo_.write(90);
}
AntennaTracker::~AntennaTracker()
{
    panServo_.detach();
    tiltServo_.detach();
}
void AntennaTracker::angleCb(const geometry_msgs::Point &msg)
{
    angleMsg_ = msg;
}
void AntennaTracker::UpdateAngle()
{
    panServo_.write(int(90+angleMsg_.x));
    tiltServo_.write(int(angleMsg_.y));
}

// Outside the class
ros::NodeHandle nh;
AntennaTracker tracker;
geometry_msgs::Point AntennaTracker::angleMsg_;
ros::Subscriber<geometry_msgs::Point>angleSub_("/antenna_tracker/angles", AntennaTracker::angleCb);
const unsigned int FPS = 60;

void setup()
{
    nh.getHardware()->setBaud(115200);
    nh.initNode();
    nh.subscribe(angleSub_);
}
void loop() {
    static unsigned long last_time = 0;
    unsigned long current_time = millis();
    if (current_time - last_time >= (1000/FPS))
    {
        last_time = current_time;
        tracker.UpdateAngle();
        nh.spinOnce();
    }
}