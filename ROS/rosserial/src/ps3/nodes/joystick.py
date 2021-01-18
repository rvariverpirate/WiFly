#!/usr/bin/env python
import pygame, sys
from time import sleep
import rospy
from sensor_msgs.msg import Joy
from rosserial_msgs.msg import RPY
from enum import Enum





# setup the pygame window
pygame.init()
pygame.mixer.quit() # Fixes runaway CPU usabe
#window = pygame.display.set_mode((200, 200), 0, 32)

# how many joysticks connected to computer?
joystick_count = pygame.joystick.get_count()
print "There is " + str(joystick_count) + " joystick/s"


# Create joystick message
joy_msg = Joy()

# Create Joy publishers
joy_pub = rospy.Publisher('sensors/joystick/ps3', Joy, queue_size=1)

# Start ps3_node
rospy.init_node('ps3_node')


if joystick_count == 0:
    # if no joysticks, quit program safely
    print ("Error, I did not find any joysticks")
    pygame.quit()
    sys.exit()
else:
    # initialise joystick
    joystick = pygame.joystick.Joystick(0)
    joystick.init()

axes = joystick.get_numaxes()
buttons = joystick.get_numbuttons()
hats = joystick.get_numhats()

print "There is " + str(axes) + " axes"
print "There is " + str(buttons) + " button/s"
print "There is " + str(hats) + " hat/s"

def getAxis(number):
    # when nothing is moved on an axis, the VALUE IS NOT EXACTLY ZERO
    # so this is used not "if joystick value not zero"
    if joystick.get_axis(number) < -0.1 or joystick.get_axis(number) > 0.1:
      # value between 1.0 and -1.0
      print "Axis value is %s" %(joystick.get_axis(number))
      print "Axis ID is %s" %(number)
      joy_msg.axes[number] = joystick.get_axis(number)

def getButton(number):
    # returns 1 or 0 - pressed or not
    if joystick.get_button(number):
      # just prints id of button
      print "Button ID is %s" %(number)
      joy_msg.buttons[number] = joystick.get_button(number)

def getHat(number):
    if joystick.get_hat(number) != (0,0):
      # returns tuple with values either 1, 0 or -1
      print "Hat value is %s, %s" %(joystick.get_hat(number)[0],joystick.get_hat(number)[1])
      print "Hat ID is %s" %(number)

while True:

    # Add timestamp and frame ID to joytick message
    joy_msg.header.stamp = rospy.Time.now()
    joy_msg.header.frame_id = "PS3"

    # Initialize all axes to default values
    joy_msg.axes = [0, 0, -1, 0, 0, -1] # ther are six axis

    # Initialize all buttons to zero
    joy_msg.buttons = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,] # 13 buttons


    for event in pygame.event.get():
      # loop through events, if window shut down, quit program
      if event.type == pygame.QUIT:
        pygame.quit()
        sys.exit()
    if axes != 0:
      for i in range(axes):
        getAxis(i)
    if buttons != 0:
      for i in range(buttons):
        getButton(i)
    if hats != 0:
      for i in range(hats):
        getHat(i)

    # Publish the PS3 Joystick Message
    joy_pub.publish(joy_msg)

    # Throttle the loop at 100 Hz
    sleep(0.01)
