/*******************************************************************************
* Copyright 2020 Jose Manuel Fajardo
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include <ros/ros.h>
#include <mobile_robot_unal_description/MobileOdom.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>

int main(int argc,char** argv)
{
    ros::init(argc, argv, "robotino_odometry");
    ros::NodeHandle nodeHandle("~");

    mobile_odometry::MobileOdom odometry(nodeHandle);
    return 0;
}

