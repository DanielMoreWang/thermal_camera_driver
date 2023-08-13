### There are three folders:
    Img_transport_ws is a ROS workspace to store the ROS package learn_img_transport, which contain ROS node-- Image_publisher
    IR_02 is a folder to store the code to control the thermal camera via Qt
    IR_back is a folder to store the code to control the thermal camera directly, which is easy to intergrate with other code.

### Steps to use camera via ROS1:
    1. Check the file that driver use to receive the video information by v4l2:  v4l2-ctl --list-devices
    2. run command: roscore           just for ROS1
    3. rosrun learning_img_transport image_publisher
    4. run rostopic to check whether the ros node publish the video information




