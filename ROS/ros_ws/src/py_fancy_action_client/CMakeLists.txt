cmake_minimum_required(VERSION 2.8.3)
project(py_fancy_action_client)


find_package(catkin REQUIRED COMPONENTS
  actionlib_msgs
  message_generation
)

add_action_files(
  DIRECTORY action
  FILES Timer.action
)

generate_messages(
  DEPENDENCIES
  actionlib_msgs
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS
  actionlib_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)
