#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include <tf/tf.h>
#include <math.h>

float odom_x = 0.0, odom_y = 0.0;

void odomCallback(const nav_msgs::Odometry::ConstPtr &msg)
{
  ::odom_x = msg->pose.pose.position.x;
  ::odom_y = msg->pose.pose.position.y;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "robert_add_markers");
  ros::NodeHandle n;
  ros::Rate r(20);
  ros::Subscriber obom_sub = n.subscribe("/odom", 1000, odomCallback);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::SPHERE;
  float goals[2][3] = {{-2.0, -9.0, -1.57}, {-6.0, -1.5, -1.57}};

  bool have_thing = false;
  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "robert_add_markers";
  marker.id = 0;

  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  marker.action = visualization_msgs::Marker::ADD;

  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  marker.pose.position.x = goals[0][0];
  marker.pose.position.y = goals[0][1];
  marker.pose.position.z = 0.5;
  marker.pose.orientation = tf::createQuaternionMsgFromYaw(goals[0][2]);

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.30;
  marker.scale.y = 0.30;
  marker.scale.z = 0.30;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 1.0f;
  marker.color.g = 0.647f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();

  while (ros::ok())
  {

    float x_distance, y_distance;

    float tolerance = 0.15;
    //ROS_INFO("Odom data: %f, %f", odom_x, odom_y);

    if (!have_thing)
    {
      marker_pub.publish(marker);
      x_distance = fabs(marker.pose.position.x - odom_x);
      y_distance = fabs(marker.pose.position.y - odom_y);

      if ((x_distance < tolerance) && (y_distance < tolerance))
      {
        marker.action = visualization_msgs::Marker::DELETE;
        marker_pub.publish(marker);
        have_thing = true;
      }
    }
    else
    {
      x_distance = fabs(goals[1][0] - odom_x);
      y_distance = fabs(goals[1][1] - odom_y);

      if ((x_distance < tolerance) && (y_distance < tolerance))
      {
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.position.x = goals[1][0];
        marker.pose.position.y = goals[1][1];
        marker.pose.position.z = 0.5;
        marker.pose.orientation = tf::createQuaternionMsgFromYaw(goals[1][2]);
        marker_pub.publish(marker);
      }
    }

    ros::spinOnce();

    r.sleep();
  }
  return 0;
}
