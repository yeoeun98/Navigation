#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "map5");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot to move 1 meter forward
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = 3.4;
  goal.target_pose.pose.position.y = 2.16;
  goal.target_pose.pose.orientation.z = 0.71;
  goal.target_pose.pose.orientation.w = 0.71;

  // goal2
  // goal.target_pose.pose.position.x = 6.0;
  // goal.target_pose.pose.orientation.w = 1.0;

  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the base moved 1 meter forward");
    
    // ac.sleep();
  }
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");

  move_base_msgs::MoveBaseGoal goal2;

  goal2.target_pose.header.frame_id = "map";
  goal2.target_pose.header.stamp = ros::Time::now();

  goal2.target_pose.pose.position.x = 7.01;
  goal2.target_pose.pose.position.y = 0.76;
  goal2.target_pose.pose.orientation.w = 1.0;

  if(abs(goal2.target_pose.pose.position.x-goal.target_pose.pose.position.x)>1.0){
    ac.sendGoal(goal2);
    ac.waitForResult();
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
      ROS_INFO("Hooray, the base moved 1 meter forward");
    }
    else
      ROS_INFO("The base failed to move forward 1 meter for some reason");
  }

  return 0;
}

