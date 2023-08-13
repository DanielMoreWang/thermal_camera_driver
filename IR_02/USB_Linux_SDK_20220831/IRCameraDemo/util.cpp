#include "util.h"
#include <QTime>
#include <QCoreApplication>
#include <sys/statvfs.h>
#include<QTextCodec>
util::util()
{

}

void util::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void util:: getSDCardSize(int &total, int &free)
{
    struct statvfs sdinfo;
    memset(&sdinfo, 0x00, sizeof(struct statvfs));
    if(0 == statvfs("/run/media/mmcblk0p1", &sdinfo))
    {
        unsigned int block_size = sdinfo.f_bsize;
        total = sdinfo.f_blocks/1024 * block_size;
        free = sdinfo.f_bfree/1024 * block_size;
//        qDebug("block_size=%d,total_size=%d,free_size=%d",block_size,total,free);

    }

}


