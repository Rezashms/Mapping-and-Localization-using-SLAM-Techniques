#include "ros/ros.h"
#include "std_msgs/String.h"
#include "nav_msgs/Odometry.h"
#include <tf2_ros/transform_broadcaster.h>

class odomTf {

public:

  odomTf() {
  	odomSub = n.subscribe("/odom", 1000, &odomTf::transformCallback, this);
  }

  void transformCallback(const nav_msgs::Odometry::ConstPtr &msg){

    //Transformation from odometry frame to base_footprint
    transformStamped.header.stamp = ros::Time::now();
    transformStamped.header.frame_id = "odom";
    transformStamped.child_frame_id = "base_footprint";
    transformStamped.transform.translation.x = msg->pose.pose.position.x;
    transformStamped.transform.translation.y = msg->pose.pose.position.y;
    transformStamped.transform.translation.z = msg->pose.pose.position.z;
    transformStamped.transform.rotation.x = msg->pose.pose.orientation.x;
    transformStamped.transform.rotation.y = msg->pose.pose.orientation.y;
    transformStamped.transform.rotation.z = msg->pose.pose.orientation.z;
    transformStamped.transform.rotation.w = msg->pose.pose.orientation.w;

    toBase.sendTransform(transformStamped);

  }


private:
  ros::NodeHandle n;
  ros::Subscriber odomSub;

  tf2_ros::TransformBroadcaster toBase;
  geometry_msgs::TransformStamped transformStamped;
   
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "odomTf");
  odomTf tfBroadcaster;
  ros::spin();
  return 0;
}