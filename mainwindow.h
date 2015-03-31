#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videoclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonStart_clicked();
    void updateFrame();

private:
    Ui::MainWindow *ui;
    VideoClient videoClient;
};

#endif // MAINWINDOW_H
