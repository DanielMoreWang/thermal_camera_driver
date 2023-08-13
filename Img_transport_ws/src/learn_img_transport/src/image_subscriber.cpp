#include "ros/ros.h"
#include "image_transport/image_transport.h"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace std;
using namespace cv;

void imageCallback(const  sensor_msgs::ImageConstPtr& msg){
    // try{
        // cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
        // cv::waitKey(1000);
        ROS_INFO("I heard image whose width is %d, height is %d", msg->width, msg->height);
        std::cout << "The sequence is " << msg->header.seq;
        std::cout << " The current time is :" << msg->header.stamp <<std::endl;
        // std::cout << " The frame id is :" << msg->header.frame_id <<std::endl;
    // }
    // catch (cv_bridge::Exception& e){
    //     ROS_ERROR("Could not convert from '%s' to 'bgr8'. ", msg->encoding.c_str() );
    // }
}

int main(int argc, char** argv){
    ros::init(argc, argv, "image_listener");
    ros::NodeHandle nh;
    // cv::namedWindow("view");

    image_transport::ImageTransport it(nh);

    image_transport::Subscriber sub = it.subscribe("IR/image",1, imageCallback);

    ros::spin();
    // cv::destroyWindow("view");

}