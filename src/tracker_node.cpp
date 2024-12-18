#include "tracker.hpp"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "tracker_node");
    ros::NodeHandle nh("~");
    ros::Rate rate(30);

    Tracker tracker(nh);

    while (ros::ok())
    {
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
