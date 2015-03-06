#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include "playthread.h"

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
    void menuVideoOpen();
    void playVideo();
    void getNewFrame(QImage, int);
    void on_horizontalSlider_sliderMoved(int position);
    void on_horizontalSlider_sliderPressed();

signals:
    void stopTheThread();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture cap;
    void fileOpened();
    QThread *thread;
    PlayThread *playThread;
    cv::Mat currFrame;
    void updateSliderMaxValue(int);
};

#endif // MAINWINDOW_H
