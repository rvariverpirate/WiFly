#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from rosserial_msgs.msg import RPY

# Because of transformations
import tf_conversions
import tf2_ros
import geometry_msgs.msg

# Get params from launch file


def callback(orient):
    # Create a TF2 Broadcaster
    br = tf2_ros.TransformBroadcaster()
    t = geometry_msgs.msg.TransformStamped()

    # Create the TF Message
    t.header.stamp = rospy.Time.now()
    t.header.frame_id = frame_id
    t.child_frame_id = "map"
    t.transform.translation.x = 0.0
    t.transform.translation.y = 0.0
    t.transform.translation.z = 0.0
    q = tf_conversions.transformations.quaternion_from_euler(orient.roll, orient.pitch, orient.yaw)
    t.transform.rotation.x = q[0]
    t.transform.rotation.y = q[1]
    t.transform.rotation.z = q[2]
    t.transform.rotation.w = q[3]

    # Broadcast the TF2 Message
    br.sendTransform(t)

def listener():
    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.Subscriber(subs_name, RPY, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    rospy.init_node('euler_to_tf', anonymous=True)
    frame_id = rospy.get_param("~frame_id") # works with /Joy_3D/frame_id  
    subs_name = rospy.get_param("~subs_name")
    listener()
