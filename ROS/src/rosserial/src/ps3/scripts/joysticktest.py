#!/usr/bin/env python
import pygame, sys
from time import sleep
import rospy
from sensor_msgs.msg import Joy


# setup the pygame window
pygame.init()
pygame.mixer.quit()
#window = pygame.display.set_mode((200, 200), 0, 32)

# how many joysticks connected to computer?
joystick_count = pygame.joystick.get_count()
print "There is " + str(joystick_count) + " joystick/s"

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
 
def getButton(number):
    # returns 1 or 0 - pressed or not
    if joystick.get_button(number):
      # just prints id of button
      print "Button ID is %s" %(number)

def getHat(number):
    if joystick.get_hat(number) != (0,0):
      # returns tuple with values either 1, 0 or -1
      print "Hat value is %s, %s" %(joystick.get_hat(number)[0],joystick.get_hat(number)[1])
      print "Hat ID is %s" %(number)

while True:
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
    sleep(0.01)
