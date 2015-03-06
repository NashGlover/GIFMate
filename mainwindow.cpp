#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <opencv/cv.h>
#include <QFileDialog>
#include <QStringList>
#include <QMessageBox>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    thread = new QThread();
    playThread = new PlayThread();

    playThread->moveToThread(thread);

    connect(ui->openVideo, SIGNAL(triggered()), this, SLOT(menuVideoOpen()));
    connect(ui->actionPlay, SIGNAL(triggered()), this, SLOT(playVideo()));
    connect(thread, SIGNAL(started()), playThread,  SLOT(startPlaying()));
    connect(this, SIGNAL(stopTheThread()), playThread, SLOT(stoppingTheThread()));
    connect(playThread, SIGNAL(newFrame(QImage, int)), this, SLOT(getNewFrame(QImage, int)), Qt::BlockingQueuedConnection);
    //connect(playThread, SIGNAL(updateSlider))
    //connect(this, )
    ui->actionPlay->setDisabled(true);
    //ui->horizontalSlider->setMaximum(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileOpened()
{
    ui->actionPlay->setEnabled(true);
    playThread->setCapture(cap);
    updateSliderMaxValue(cap.get(CV_CAP_PROP_FRAME_COUNT));
    cap >> currFrame;
    cv::cvtColor(currFrame, currFrame, CV_BGR2RGB);
    QImage currImage = QImage((unsigned char*)currFrame.data, currFrame.cols, currFrame.rows, currFrame.step, QImage::Format_RGB888);
    ui->frameDisplay->setPixmap(QPixmap::fromImage(currImage));
}

void MainWindow::playVideo()
{
    thread->start();
}

void MainWindow::getNewFrame(QImage newImage, int current_frame_num)
{
    QPainter* painter = new QPainter(&newImage);
    painter->setPen(Qt::blue);
    painter->setFont(QFont("Arial", 30));
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->drawText(newImage.rect(), Qt::AlignCenter, "Text on Image");
    painter->end();
    ui->horizontalSlider->setValue(current_frame_num);
    ui->frameDisplay->setPixmap(QPixmap::fromImage(newImage));
}

void MainWindow::menuVideoOpen()
{
    QStringList validTypes;
    validTypes << ".mp4" << ".avi";
    //qDebug() << "Opened video?";
    bool validFile = false;
    QString fileName;
    while (!validFile)
    {
        fileName = QFileDialog::getOpenFileName(this, tr("Open a Video"), NULL);
        if (fileName.isNull())
        {
            return;
        }
        validFile = false;
        qDebug() << fileName;
        foreach (QString validType, validTypes){
            if (!fileName.endsWith(validType, Qt::CaseInsensitive))
            {
                validFile = false || validFile;
            }
            else {
                validFile = true;
            }
        }
        if (!validFile)
        {
            int ret = QMessageBox::critical(this, tr("Error"),
                                            tr("Please choose an appropriate file type (.mp4, .avi)."),
                                            QMessageBox::Ok | QMessageBox::Cancel);
            if (ret == QMessageBox::Cancel) return;
        }
    }
    cap.open(fileName.toStdString());
    if (!cap.isOpened())
    {
        QMessageBox::critical(this, tr("Error"),
                              tr("Could not open the file."),
                              QMessageBox::Ok);
        return;
    }
    fileOpened();
}

void MainWindow::updateSliderMaxValue(int value) {
    ui->horizontalSlider->setMaximum(value);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{

}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    qDebug() << "I DID IT";
}
