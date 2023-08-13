#ifndef UTIL_H
#define UTIL_H

#include<QString>

class util
{
public:
    util();
    static void Sleep(int msec);
    static void getSDCardSize(int &total, int &free);
    static QByteArray GBK2UTF8(const QString &inStr);
    static QByteArray UTF82GBK(const QString &inStr);
};

#endif // UTIL_H
