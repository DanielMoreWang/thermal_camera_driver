#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <asm/types.h>
#include <linux/videodev2.h>

#include <sys/time.h>
#include <iostream>
#include <chrono>
#include <iomanip>

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

#define CAMERA_DEVICE "/dev/video4"
#define CLEAR(x) memset (&(x), 0, sizeof (x))

#define VIDEO_WIDTH 1280
#define VIDEO_HEIGHT 512
#define VIDEO_FORMAT V4L2_PIX_FMT_YUYV
#define BUFFER_COUNT 4

typedef struct VideoBuffer {
        void *                  start;
        size_t                  length;
} VideoBuffer;

static int width=1280;
static int height=512;

string current_time_filepath(bool bShot, bool bVideo){
    // for current time
    auto now = std::chrono::system_clock::now();
    auto now_c = chrono::system_clock::to_time_t(now);
    //to string
    stringstream ss;
    ss << put_time(localtime(&now_c),"%Y-%m-%d_%H-%M-%S");
    string time_str = ss.str();
    // define extension
    string image_ext = ".jpg";
    string viedo_ext = ".avi";
    // string viedo_ext = ".mp4";

    if(bShot&bVideo){
        cout << "Choice error: you need choose one mode: iamge or video" << endl;
    }
    if(bShot){
        return time_str += image_ext;
    }

    if(bVideo){
        return time_str += viedo_ext;
    }

    return 0;
};


int main(){

    cv::VideoWriter vw;

    int fd_video;
    fd_video = open(CAMERA_DEVICE, O_RDWR);
    if (fd_video < 0){
        printf("Open %s failed \n", CAMERA_DEVICE);
        return -1;
    }

    // access the driver information
    struct v4l2_capability cap;
    int ret = ioctl(fd_video, VIDIOC_QUERYCAP, &cap);
    if (ret < 0){
        printf("VIDIOC_QUERYCAP failed (%d) \n", ret);
        return ret;
    }

    // Print capability informations
    printf("Capability Informations: \n");
    printf("driver: %s\n", cap.driver);
    printf("card: %s\n", cap.card);
    printf("bus_info: %s\n", cap.bus_info);
    printf("version: %08X\n", cap.version);
    printf("capability: %08X\n", cap.capabilities);

    if ((cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == V4L2_CAP_VIDEO_CAPTURE){
        printf("Device %s: supports capture.\n",CAMERA_DEVICE);
    }
    if ((cap.capabilities & V4L2_CAP_STREAMING) == V4L2_CAP_STREAMING){
        printf("Device %s: supports streaming.\n",CAMERA_DEVICE);
    }

    // set the format of video
    struct v4l2_format fmt;
    memset(&fmt , 0, sizeof(fmt));
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = VIDEO_WIDTH;
    fmt.fmt.pix.height = VIDEO_HEIGHT;
    fmt.fmt.pix.pixelformat = V4L2_FIELD_INTERLACED;
    ret = ioctl(fd_video,VIDIOC_S_FMT, &fmt);
    if (ret < 0){
        printf("VIDIOC_S_FMT failed (%d)\n", ret);
        return ret;
    }

    // obtain the format of video
    ret = ioctl(fd_video, VIDIOC_G_FMT, &fmt);
    if(ret < 0){
        printf("VIDIOC_G_FMT failed (%d)\n", ret);
        return ret;
    }

    ret = ioctl(fd_video, VIDIOC_S_FMT, &fmt);
    if(ret < 0){
        printf("VIDIOC_S_FMT failed (%d)\n", ret);
        return ret;
    }

    //Print Stream Format
    printf("Stream Format Informations: \n");
    printf("type: %d\n", fmt.type);
    printf("width: %d\n", fmt.fmt.pix.width);
    printf("height: %d\n", fmt.fmt.pix.height);
    char fmtstr[8];
    memset(fmtstr, 0, 8);
    memcpy(fmtstr,&fmt.fmt.pix.pixelformat, 4 );
    printf("pixelformat: %s\n", fmtstr);
    printf("field: %d\n", fmt.fmt.pix.field);
    printf("bytesperline: %d\n", fmt.fmt.pix.bytesperline);
    printf("sizeimage: %d\n", fmt.fmt.pix.sizeimage);
    printf("colorspace: %d\n", fmt.fmt.pix.colorspace);
    printf(" priv: %d\n", fmt.fmt.pix.priv);
    printf("raw_data: %s\n", fmt.fmt.raw_data);

    //request for memory
    struct v4l2_requestbuffers reqbuf = {};

    // CLEAR(reqbuf);

    reqbuf.count = BUFFER_COUNT;
    reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    reqbuf.memory = V4L2_MEMORY_MMAP;

    ret = ioctl(fd_video, VIDIOC_REQBUFS, &reqbuf);
    if(ret<0){
        printf("VIDIOC_REQBUFS failed (%d)\n", ret);
        return ret;
    }
    printf("request buffer success.\n");

    // obtain for space

    VideoBuffer* buffers = (VideoBuffer*)calloc(reqbuf.count, sizeof(*buffers));
    // void* buffers[BUFFER_COUNT] ;

    for(int i=0; i < reqbuf.count; i++)
    {   
        struct v4l2_buffer buf = {} ;
        buf.index = i;
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        int ret = ioctl(fd_video, VIDIOC_QUERYBUF, &buf);
        if (ret <0){
            printf("VIDIOC_QUERYBUFS (%d) failed (%d)\n", i, ret);
            return ret;
        }
        // // mmap buffer

        buffers[i].length = buf.length;
        buffers[i].start = (char*) mmap(NULL, buf.length, PROT_READ|PROT_WRITE, MAP_SHARED, fd_video, buf.m.offset);
        // buffers[i] = mmap(NULL, buf.length, PROT_READ|PROT_WRITE, MAP_SHARED, fd_video, buf.m.offset);
        if (buffers[i].start == MAP_FAILED){
            close(fd_video);
            printf("mmap (%d) failed (%s)\n", i, strerror(errno));
            return -1;
        }
        //Queen buffer
        ret = ioctl( fd_video, VIDIOC_QBUF, &buf);
        if(ret<0){
            printf("VIDIOC_QBUF (%d) failed (%d)\n", i, ret);
            return -1;            
        }
        printf("Frame buffer %d : address=0x%x, length=%d\n", i, *(unsigned int*)buffers[i].start, (int)buffers[i].length);


    }

    // begin for video stream
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = ioctl(fd_video,VIDIOC_STREAMON, &type);
    if(ret<0){
        printf("VIDIOC_STREAMON failed (%d)\n", ret);
        return ret;
    }
    // loop for capture 1000 frame
    string file_path = current_time_filepath(false, true);
    // vw.open(file_path, cv::VideoWriter::fourcc('M','J','P','G'),25,cv::Size(1280,512),false);
    vw.open(file_path, cv::VideoWriter::fourcc('M','J','P','G'),50,cv::Size(1280,512),false);
    if(!vw.isOpened()){
        cout << "VideoWriter open failed" << endl;
    }
    else{
        cout << "VideoWriter open success!" << endl;
    }

    struct timeval tv;
    gettimeofday(&tv, NULL);

    for (int i=0; i<10000; ++i){

        // get one frame from the queue
        struct v4l2_buffer buf = {} ;
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        ret = ioctl(fd_video,VIDIOC_DQBUF, &buf);
        if(ret<0){
            printf("VIDIOC_DQBUF failed (%d)\n", ret);
            return ret;
        } 
        //process the frame
        unsigned char* data = static_cast<unsigned char*>(buffers[buf.index].start);

        IplImage * pImg = cvCreateImage(cvSize(width,height),8,2);
        memcpy(pImg->imageData, data, width*height*2);
        IplImage * pImgGray2 = cvCreateImage(cvGetSize(pImg),8,3);
        cvCvtColor(pImg, pImgGray2, CV_YUV2BGR_YUYV);

        Mat mat=cvarrToMat(pImgGray2);
        Mat rgb;
        Mat grey_scale;
        Mat gauss_smoothed_grey;

        cvtColor(mat,grey_scale,COLOR_BGR2GRAY);
        cvtColor(mat,rgb, CV_BGR2RGB);

        GaussianBlur(grey_scale, gauss_smoothed_grey, Size(5,5), 0, 0);

        // Re-queen buffer
        ret = ioctl(fd_video, VIDIOC_QBUF, &buf);
        if(ret<0){
            printf("VIDIOC_QBUF failed (%d) \n", ret);
            return ret;
                }
        // display rgb data
        // cv::imshow("GREY", grey_scale);
        cv::imshow("Gauss_smoothed_grey", gauss_smoothed_grey);
        // cv::imshow("BGR", mat);
        // cv::imshow("RGB", rgb);
        // break using Esc on keyboard
        if(cv::waitKey(1) == 27){
            break;
        }
        // cv::waitKey(0);

        // struct timeval tv;
        // gettimeofday(&tv, NULL);
        // cout << "Current time: " << tv.tv_usec  << endl;
        // vw << grey_scale;
        vw << gauss_smoothed_grey;
        // vw << rgb;

        cvReleaseImage(&pImg);
        cvReleaseImage(&pImgGray2);
        //display the processed video, display on window or save to the file
        //display rgb data
        // cv::imshow("RGB", mat);
        // cv::imshow("RGB", rgb);
        // cv::waitKey(0);
        // struct timeval tv;
        // gettimeofday(&tv, NULL);
        // cout << "Current time: " << tv.tv_usec  << endl;
    }

    vw.release();
    cout << "Video is saved at: " << file_path <<endl;

    // stop streaming
    ret = ioctl(fd_video,VIDIOC_STREAMOFF, &type);
    if(ret<0){
        printf("Stop streaming failed (%d)\n", ret);
        return ret;
    }

    //release the resource
    for(int i=0; i<4; i++){
        munmap(buffers[i].start,buffers[i].length);
    }

    close(fd_video);
    printf("Video Captured.\n");
}