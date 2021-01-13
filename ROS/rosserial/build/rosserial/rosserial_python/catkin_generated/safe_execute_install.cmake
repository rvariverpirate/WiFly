execute_process(COMMAND "/mnt/c/Users/jcann/Desktop/Projects/WiFly/ROS/rosserial/build/rosserial/rosserial_python/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/mnt/c/Users/jcann/Desktop/Projects/WiFly/ROS/rosserial/build/rosserial/rosserial_python/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
