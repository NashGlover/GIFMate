#include "playthread.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv/cv.h>
#include <QDebug>
#include <QImage>
#include <QTime>
#include <QThread>
//#include <libavcodec/avcodec.h>
//#include <

PlayThread::PlayThread() : currPos(0)
{
    timer = new QTime();
    qDebug() << currPos;
}

void PlayThread::stoppingTheThread()
{
    qDebug() << "In stoppingTheThread()";
}

void PlayThread::startPlaying()
{

    qDebug() << "Start the thread";
    double FPS = cap.get(CV_CAP_PROP_FPS);
    int frame_count = cap.get(CV_CAP_PROP_FRAME_COUNT);
    qDebug() << FPS << " " << frame_count;
    int current_frame_count = 0;
    QTime clock;
    playing = true;
    while (playing)
    {
     /*   cap >> currFrame;*/
        //cap.set(CV_CAP_PROP_POS_FRAMES,frame_count-100);
        //cap.read(currFrame);
        cap >> currFrame;
        cv::cvtColor(currFrame, currFrame, CV_BGR2RGB);
        QImage Image = QImage((unsigned char*)currFrame.data, currFrame.cols, currFrame.rows, currFrame.step, QImage::Format_RGB888);
        if (current_frame_count != 0) {
            int elapsed_time = clock.elapsed();
            QThread::msleep(33.3 - elapsed_time);
        }
        emit newFrame(Image, current_frame_count);
        if (current_frame_count == 0) clock.start();
        else clock.restart();
        current_frame_count++;
    }
}

void PlayThread::updateCurrentFrame(int frame_value) {
    cap.set(CV_CAP_PROP_POS_FRAMES, (double)frame_value);
}

void PlayThread::setCapture(cv::VideoCapture inCap)
{
    this->cap = inCap;
}
