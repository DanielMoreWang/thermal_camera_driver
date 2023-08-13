#include "ros/ros.h"
#include "image_transport/image_transport.h"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"

#include <sys/time.h>
// #include <iostream>
#include <chrono>
#include <iomanip>


#include <iostream>

#define VIDEO_SOURCE 6

using namespace std;

int main(int argc, char** argv){

    ros::init(argc, argv, "image_publisher"); //node name :image_publisher
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("IR/image", 1);

    int video_source = VIDEO_SOURCE;
    cv::VideoCapture cap(video_source);
    if(!cap.isOpened()){
        return -1;}
    // std::string file_path = "/home/labsun/IR_practice_ws/src/my.jpg";
    // cv::Mat image = cv::imread(file_path, cv::IMREAD_ANYCOLOR);
    // if(image.empty()){
    //     std::cout << "Could not read the image" << "2023-04-13_15-46-44.jpg" << std::endl;
    //     return 1;
    // }
    // cv::imshow("Grab image", image);
    // cv::waitKey(100);
    // sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "mono8" , image).toImageMsg();

    ros::Rate loop_rate(40);

    cv::Mat intrinsic = (cv::Mat_<double>(3,3) <<587.49580772,0,320.04506661, 0,583.95342145,245.19773092, 0,0,1);
    cv::Mat distCoeffics=  (cv::Mat_<double>(1,5) << -0.28615155, -0.03261748, 0.00420999, -0.00111174, 0.45364076);

    int count = 0;
    while(nh.ok()){
        cv::Mat frame;
        cap >> frame;

        ros::Time capture_time = ros::Time::now();

        cv::Mat gray;
        cv::Mat gauss_smoothed_grey;
        cv::Mat after;
        cv::Mat img_undistort;


        struct timeval tv1;
        gettimeofday(&tv1, NULL);
        cout << "start time: " << tv1.tv_usec << "  ";

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(gray, gauss_smoothed_grey, cv::Size(5,5), 0, 0);
        cv::resize(gauss_smoothed_grey, after, cv::Size(640,512),cv::INTER_AREA);
        cv::undistort(after, img_undistort, intrinsic, distCoeffics, cv::noArray());

        struct timeval tv;
        gettimeofday(&tv, NULL);
        cout << "stop time: " << tv.tv_usec  << endl;

        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "mono8" , img_undistort).toImageMsg();

        // msg-> header.stamp = ros::Time::now();
        msg-> header.stamp = capture_time;
        msg-> header.frame_id = "IR_frame";

        pub.publish(msg);

        // std::cout << "I publish " << count << "image" <<endl;
        ROS_INFO("I publish %d", count);

        ros::spinOnce();
        loop_rate.sleep();

        count = count +1;
    }

    return 0;
}
