#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonStart_clicked()
{
    if (videoClient.isOpened())
        return;
    QString host = ui->lineEditHost->text();
    int port = ui->lineEditPort->text().toInt();
    int delayTime = ui->lineEditDelayTime->text().toInt();
    int resendTime = ui->lineEditResendTime->text().toInt();
    if (port < 1 || port > 65535)
    {
        QMessageBox::critical(this, "Error", "Wrong port number (1 <= port <= 65535)");
        return;
    }
    if (delayTime < 1)
    {
        QMessageBox::critical(this, "Title", "Wrong delay time (> 0)");
        return;
    }
    if (resendTime < 1)
    {
        QMessageBox::critical(this, "Title", "Wrong reset time (> 0)");
        return;
    }
    if (videoClient.open(host, port))
    {
        videoClient.setResendTime(resendTime);
        ui->lineEditHost->setEnabled(false);
        ui->lineEditPort->setEnabled(false);
        ui->lineEditDelayTime->setEnabled(false);
        ui->lineEditResendTime->setEnabled(false);
        ui->pushButtonStart->setEnabled(false);
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
        timer->start(delayTime);
    }
    else
    {
        QMessageBox::critical(this, "Error", "Socked was not opened");
    }
}

void MainWindow::updateFrame()
{
    ui->labelImage->setPixmap(videoClient.getFrame());
}
