#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QLabel>
#include <QMetaType>
#include <QPainter>
#include <QMutex>
#include <QFileDialog>
#include <qfiledialog.h>
#include <qfile.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "opencv2/opencv.hpp"
// #include "/usr/local/include/opencv4/opencv2/opencv_modules.hpp"
// #include "/usr/local/include/opencv4/opencv2/imgproc/imgproc_c.h"
// #include "/usr/local/include/opencv4/opencv2/videoio.hpp"
// #include "/usr/local/include/opencv4/opencv2/highgui.hpp"

#include "udevhelper.h"
#include <QImageReader>
#include <QMessageBox>
#include "util.h"
#include "uvc/ircammanager.h"

using namespace cv;
#define WDTTIME 3

QTextStream sout;
QFile file;

//video window title info
int w_width,w_height;
int w_fcount;

MainWindow *pMain = NULL;

QLabel* lable_preview = NULL;
QLabel* label_temp=NULL;
int draw_count = 0;
bool breg = false;
static int point_x,point_y=0;
static int coreType=0; //0-M3 1-LT 2-ELF 3-M Handheld
static int measureType=0; //0-工业测温 1-人体测温
static bool isTImage=0; //0-温度成像关 1-温度成像开
static bool isTempMeasure=true;
static int count=0;

cv::VideoWriter vw;
bool bShot=false;
bool bVideo=false;
unsigned char* data2 = new unsigned char[1280*512];

void onReciveFrameData(unsigned char* data,int size)
{
    if(size<mDeviceWidth*mDeviceHeight*2)
    {
        return;
    }
    memset(data2,0,1280*512);
    for(int i=0;i<size/2;i++)
    {
        data2[i]=data[i*2];
    }
  //  cv::Mat myuv(mDeviceHeight, mDeviceWidth, CV_8UC3, (unsigned char *)data2);
  //  Mat rgb;

  //  cvtColor(myuv,rgb,CV_GRAY2BGR);
  //  cvtColor(myuv,rgb,CV_YUV2BGR);

//    QImage img;

//    img = QImage((const uchar*)(rgb.data),rgb.cols,rgb.rows,rgb.cols*rgb.channels(),QImage::Format_RGB888);


    IplImage * pImg = cvCreateImage(cvSize(mDeviceWidth, mDeviceHeight), 8, 2);
    memcpy(pImg->imageData,data2,mDeviceWidth*mDeviceHeight*2);
    IplImage * pImgGray2 = cvCreateImage(cvGetSize(pImg), 8, 3);
    if(coreType==2)
    {
        cvCvtColor(pImg, pImgGray2, CV_YUV2BGR_YUYV);
    }
    else
    {
        cvCvtColor(pImg, pImgGray2, CV_YUV2BGR_UYVY);
    }
    Mat mat=cvarrToMat(pImgGray2);
    Mat rgb;
    QImage img;

    if(mat.channels()==3)
    {
        cvtColor(mat,rgb,CV_BGR2RGB);
        img = QImage((const uchar*)(rgb.data),rgb.cols,rgb.rows,rgb.cols*rgb.channels(),QImage::Format_RGB888);
    }
    else
    {
        img = QImage((const uchar*)(mat.data),mat.cols,mat.rows,mat.cols*mat.channels(),QImage::Format_RGB888);

    }

       lable_preview->setAlignment(Qt::AlignCenter);
       QSize m_lableshowSize;
       m_lableshowSize.setWidth(mDeviceWidth);
       m_lableshowSize.setHeight(mDeviceHeight);
       lable_preview->setPixmap(QPixmap::fromImage(img).scaled(
                                      m_lableshowSize,
                                      Qt::IgnoreAspectRatio,
                                      Qt::SmoothTransformation));
       //保存当前mat
       if(bShot)
       {
           QString filepath=QDateTime::currentDateTime().toString("ddhhmmss")+".jpg";
           bool res=cv::imwrite(filepath.toStdString(),mat);
           qDebug()<<"take photo success!filepath="+filepath;
           bShot=false;
       }
       //创建视频文件
       if(bVideo)
       {
           vw<<rgb;
       }

       cvReleaseImage(&pImg);
       cvReleaseImage(&pImgGray2);

  //   rgb.release();
 //    myuv.release();
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<QByteArray> simglist = QImageReader::supportedImageFormats();
    QByteArray jpeg_name("jpeg");
    if(!simglist.contains(jpeg_name))
    {
        qDebug("No jpeg plugin to support jpeg format.");
        log(tr("No jpeg plugin to support jpeg format."));
    }
    pCamManager = new IrCamManager();
    pMain = this;
    lable_preview = ui->label_preview;
}


MainWindow::~MainWindow()
{
    delete ui;
    if(pCamManager)
    {
        delete pCamManager;
    }
    delete[] data2;
}



void MainWindow::log(QString str)
{
    ui->textEdit_log->append(str);
}


void MainWindow::on_pushButton_link_clicked()
{
    if(ui->pushButton_link->text()=="Link")
    {
        if(ui->lineEdit_uvcdevname->text().isEmpty())
        {
            log("No device name");
            return;
        }
        char* seldev = ui->lineEdit_uvcdevname->text().toLatin1().data();
        size_t devname_len=ui->lineEdit_uvcdevname->text().length();
        char* devname =new char[devname_len+1];
        strncpy(devname, seldev, devname_len);
        devname[devname_len]='\0';

        if(uvc_open(devname)){
            ui->pushButton_link->setText(QString("Close"));
        }
    }
    else if(ui->pushButton_link->text()=="Close")
    {
        usleep(500*1000);
        uvc_close();
        //viewForm.close();
        ui->pushButton_link->setText(QString("Link"));
    }
}

//****************************************************************************
//uvc device open function
//****************************************************************************
bool MainWindow::uvc_open(const char* devname)
{
    bool bok = false;
    int res_w = 0,res_h = 0;
    QStringList sres = ui->comboBox_capture_res->currentText().split('x');
    if(sres.size()!=2){
        res_w=1280;
        res_h=512;
        coreType=3;
    }
    else
    {
        res_w = sres.at(0).toInt(&bok);
        if(!bok){
            ui->textEdit_log->append("invalid width value");
            return false;
        }
        res_h = sres.at(1).toInt(&bok);
        if(!bok){
            ui->textEdit_log->append("invalid height value");
            return false;
        }
    }
    qDebug()<<"capture parameter:res="<<res_w<<"x"<<res_h;
    int fps=25;
    int ret = pCamManager->OpenDevice(devname,res_w,res_h,fps);
    if(ret<0)
    {
        log(QString("Can not link video device (%1) error=%2").arg(tr(devname)).arg(ret));
        return false;
    }
    log(QString("Link video device (%1) successful").arg(tr(devname)));

    pCamManager->SetDataCallback(&onReciveFrameData);
    mDeviceWidth=res_w;
    mDeviceHeight=res_h;
    m_temp=new unsigned short[mDeviceWidth*mDeviceHeight*2];
    m_img=new unsigned char[mDeviceWidth*mDeviceHeight*4];
    return true;
}

//****************************************************************************
//uvc device close function
//****************************************************************************
void MainWindow::uvc_close()
{
    pCamManager->CloseDevice();
    log("Close the video device");
}


void MainWindow::on_pushButton_distance_get_clicked()
{
    bShot=true;
}
QString filepath;
void MainWindow::on_pushButton_clicked()
{
    if(bVideo)
    {
        bVideo=false;
        log("save success!filePath="+filepath);
        vw.release();
    }
    else
    {
        bVideo=true;
        filepath=QDateTime::currentDateTime().toString("ddhhmmss")+".avi";

    //    vw.open(filepath.toStdString(),CV_FOURCC_DEFAULT, 25,cv::Size(640,512));
        vw.open(filepath.toStdString(),cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 25,cv::Size(640,512));

        if (!vw.isOpened())
        {
            log("VideoWriter open failed!");
            return;
        }
        log("VideoWriter open success!");
    }
}
