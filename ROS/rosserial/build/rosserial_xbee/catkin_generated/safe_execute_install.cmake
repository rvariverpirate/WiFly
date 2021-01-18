execute_process(COMMAND "/home/tripp/Workspaces/src/rosserial/build/rosserial_xbee/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/tripp/Workspaces/src/rosserial/build/rosserial_xbee/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
