#ifndef MYVIDEOCAPTURE_H
#define MYVIDEOCAPTURE_H

#include <QPixmap>
#include <QImage>
#include <QThread>
#include <opencv2/opencv.hpp>

#define ID_Camera 0
class MyVideoCapture : public QThread
{
    Q_OBJECT
public:
    MyVideoCapture(QObject *parent = nullptr);

    QPixmap pixmap()const
    {
        return mPixmap;
    }
    cv::Mat frame()const
    {
        return mFrame;
    }
protected:
    void run() override;
signals:
    void newPixmpapCaptured();


private:
    QPixmap mPixmap;
    cv::Mat mFrame;
    cv::VideoCapture mVideoCap;

    QPixmap cvMatToQPixmap( const cv::Mat &inMat );
    QImage cvMatToQImage( const cv::Mat &inMat );
};

#endif // MYVIDEOCAPTURE_H
