cmake_minimum_required(VERSION 2.8.3)
project(rosserial_msgs)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  std_msgs
  #geometry_msgs
)

add_message_files(FILES
  Log.msg
  TopicInfo.msg
  myTest.msg
  RPY.msg
)

add_service_files(FILES
  RequestMessageInfo.srv
  RequestParam.srv
  RequestServiceInfo.srv
)

generate_messages( DEPENDENCIES
   std_msgs
   #geometry_msgs
)

catkin_package(CATKIN_DEPENDS
  message_runtime
)
