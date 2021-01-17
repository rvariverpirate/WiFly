### A WiFi enabled ROS drone for research purposes... and for fun...

## WSL Port Forwarding (abandonded WSL approach due to inherient inacessibility to bluetooth)
If running ROS in WSL, you will need to forward the ROS master ports to your computers local host. Becasue WSL doesn't have a static IP, you'll want to run the 'network.ps1' PoserShell script in an elevated Power Shell to set this up.

Additionally, you may have to create Inbound and Outbound rules or ports 11311 and 11411 in Windows Defender Firewall to allow ROS messages to be sent and received by ROS Master and your ROS Nodes.

# Test ROS Serial
roscore
roslaunch rosserial_server socket.launch
rostopic echo chatter

# Test WiFly ROS
source_wifly
roslaunch rosserial_server socket.launch

source_wifly
rosrun view3D  euler_to_tf.py 0 0 0 0 0 0 1 map IMU 10

source_wifly
rviz
Add tf

source_wifly
rostopic echo /tf

Refferences:
WSL Port Forwarding
https://dev.to/vishnumohanrk/wsl-port-forwarding-2e22
netsh interface portproxy reset
netsh interface portproxy show v4tov4

Stream Server Test:
http://192.168.1.244:81/stream
