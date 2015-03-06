#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QObject>
#include <QThread>
#include <QImage>
#include <QTime>
//#include <libavcodec/avcodec.h>
#include <opencv2/highgui/highgui.hpp>

class PlayThread : public QObject
{
    Q_OBJECT
public:
    explicit PlayThread();
    void setCapture(cv::VideoCapture);

signals:
    void newFrame(QImage, int);

public slots:
    void startPlaying();
    void stoppingTheThread();
    void updateCurrentFrame(int);

private:
    int currPos;
    cv::VideoCapture cap;
    cv::Mat currFrame;
    QTime *timer;
    bool playing;

};

#endif // PLAYTHREAD_H
