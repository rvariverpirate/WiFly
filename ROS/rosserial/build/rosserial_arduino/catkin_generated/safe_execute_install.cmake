execute_process(COMMAND "/home/tripp/Desktop/WiFly/ROS/rosserial/build/rosserial_arduino/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/tripp/Desktop/WiFly/ROS/rosserial/build/rosserial_arduino/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
