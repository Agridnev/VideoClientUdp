#include "videoclient.h"

VideoClient::VideoClient() : resendTime(1000)
{

}

VideoClient::~VideoClient()
{
    if (isOpened())
        close();
}

int VideoClient::open(QString host, int port)
{
    socket.connectToHost(host, port);
    return socket.isOpen();
}

bool VideoClient::isOpened() const
{
    return socket.isOpen();
}

void VideoClient::close()
{
    socket.close();
}

QPixmap VideoClient::getFrame()
{
    QPixmap frame;
    if (!isOpened())
        return frame;
    while (true)
    {
        int parts = 0;
        while (!parts)
        {
            QByteArray requestParts((int) 1, (char) 0);
            socket.write(requestParts);
            socket.waitForBytesWritten();
            socket.waitForReadyRead(resendTime);
            QByteArray responseParts = socket.read(65536);
            if (responseParts.size() == sizeof(int))
                parts = *((int *)responseParts.constData());
        }
        QByteArray frameCompressed;
        for (int i = 0; i < parts; ++i)
        {
            QByteArray responsePart;
            while (!responsePart.size())
            {
                QByteArray requestPart((int) 1, (char) 1);
                requestPart.append((char *) &i, sizeof(int));
                socket.write(requestPart);
                socket.waitForBytesWritten();
                socket.waitForReadyRead(resendTime);
                responsePart = socket.read(65536);
            }
            frameCompressed.append(responsePart);
        }
        if (frame.loadFromData(frameCompressed, "JPG"))
            break;
    }
    return frame;
}

int VideoClient::getResendTime() const
{
    return resendTime;
}

void VideoClient::setResendTime(int resendTime)
{
    if (resendTime > 0)
        this->resendTime = resendTime;
}
