#ifndef VIDEOCLIENT_H
#define VIDEOCLIENT_H

#include <QUdpSocket>
#include <QPixmap>

class VideoClient
{
public:
    VideoClient();
    ~VideoClient();
    int open(QString host, int port);
    bool isOpened() const;
    void close();
    QPixmap getFrame();
    int getResendTime() const;
    void setResendTime(int resendTime);

private:
    int resendTime;
    QUdpSocket socket;
};

#endif // VIDEOCLIENT_H
