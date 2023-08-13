#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QThread>
#include <QMutex>
#include <QDateTime>
#include <QQueue>
#include <QList>
#include <QMap>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "uvc/ircammanager.h"
// #include "ircammanager.h"


//image data sync thread

static int mDeviceWidth;
static int mDeviceHeight;
static unsigned short *m_temp;
static unsigned char *m_img;



//main
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void log(QString str);
private slots:
    void on_pushButton_link_clicked();
    
    void on_pushButton_distance_get_clicked();

    void on_pushButton_clicked();

// private:
public:
    Ui::MainWindow *ui;
    bool uvc_open(const char* devname);
    void uvc_close();
    IrCamManager* pCamManager;

};

#endif // MAINWINDOW_H
