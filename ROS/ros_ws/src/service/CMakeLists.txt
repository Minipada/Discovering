cmake_minimum_required(VERSION 2.8.3)
project(service)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  tf
  rosbag
  message_generation
  std_msgs
  genmsg
)

add_service_files(FILES AddTwoInts.srv)

generate_messages(DEPENDENCIES std_msgs)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_executable(service_server src/service_server.cpp)
target_link_libraries(service_server ${catkin_LIBRARIES})

add_executable(service_client src/service_client.cpp)
target_link_libraries(service_client ${catkin_LIBRARIES})

