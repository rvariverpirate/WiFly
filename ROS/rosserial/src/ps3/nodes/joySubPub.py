#!/usr/bin/env python

import rospy
from sensor_msgs.msg import Joy
from rosserial_msgs.msg import RPY
from enum import Enum

# Define mathematical Pi
pi_math = 3.141592653589793

# Create Enumeration Class for Relevant Axis
class RPY_enum():
    roll = 0
    pitch = 1
    yaw = 3
    altitude = 4

rospy.init_node('joy_pub_sub')

# Create a Roll, Pitch, Yaw Command Message
rpy_command_msg = RPY()

# Create the RPY Command Publisher
rpy_command_pub = rospy.Publisher('commands/rpy_command', RPY, queue_size=1)

# Need to check if Joystick Axes have changed (use this)
joy_axes_prev = [0, 0, -1, 0, 0, -1]

def scaleRPY(axisValue):
    #Convert from -1:1 joy scale to -pi/2:pi/2 rpy scale
    return axisValue*pi_math/2.0

def joystickCallback(joyMsg):
  global joy_axes_prev
  # If the joystick axes have changed
  print("joystickCallback occured")
  if(joyMsg.axes!=joy_axes_prev):

    # Add timestamp and frame ID to RPY Command Message
    rpy_command_msg.header.frame_id = "rpy_command"
    rpy_command_msg.header.stamp = rospy.Time.now()

    # Initialize RPY Command Message to all zero
    rpy_command_msg.roll = scaleRPY(joyMsg.axes[RPY_enum.roll])
    rpy_command_msg.pitch = scaleRPY(joyMsg.axes[RPY_enum.pitch])
    rpy_command_msg.yaw = scaleRPY(joyMsg.axes[RPY_enum.yaw])
    # Publish the RPY Command Message
    rpy_command_pub.publish(rpy_command_msg)
  joy_axes_prev = joyMsg.axes

# Subscribe to the Joystick Raw Message
rospy.Subscriber('sensors/joystick/ps3', Joy, joystickCallback)
rospy.spin()
