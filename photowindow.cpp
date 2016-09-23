#include "photowindow.h"
#include <QDebug>
#include <cstdlib>      // for rand and srand

PhotoWindow::PhotoWindow()
{

}

void PhotoWindow::Init(void)
{
    qDebug() << "This size is:" << this->size();
    backgroundIn = new AnimatedImage(this->size(), this);
    backgroundOut = new AnimatedImage(this->size(), this);
    foregroundIn = new AnimatedImage(this->size(), this);
    foregroundOut = new AnimatedImage(this->size(), this);

//    QPixmap blank(this->width(),this->height());
//    blank.fill(Qt::black);

//    backgroundIn->setMyImage(blank.toImage());
//    backgroundIn->setIsBackground(true);
//    backgroundOut->setMyImage(blank.toImage());
//    backgroundOut->setIsBackground(true);
//    foregroundIn->setMyImage(blank.toImage());
//    foregroundOut->setMyImage(blank.toImage());

    ReadURLs();
    NextImage();

    connect(&tick, SIGNAL(timeout()), this, SLOT(NextImage()));
    tick.setInterval(5000);
    tick.start();
}

void PhotoWindow::initializeGL()
{
    // Set up the rendering context, load shaders and other resources, etc.:
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void PhotoWindow::resizeGL(int w, int h)
{
//    backgroundIn->setImageRect(QRect(0,0,w,h));
//    backgroundOut->setImageRect(QRect(0,0,w,h));
    foregroundIn->setScreenSize(w,h);
//    foregroundOut->setImageRect(QRect(0,0,w,h));
    this->update();
}

void PhotoWindow::paintGL()
{
    // Draw the scene:
    qDebug() << "paint";
    QPainter p;
    p.begin(this);
    QRect r = QRect(0,0,this->width(),this->height());
    QBrush b(Qt::black);
    p.fillRect(r,b);
//    p.drawImage(0,0,backgroundIn->getMyImage());
    p.drawImage((this->width()-foregroundIn->getScaledImageSize().width())/2,
                (this->height()-foregroundIn->getScaledImageSize().height())/2,
                foregroundIn->getMyScaledImage());
    p.end();
}

void PhotoWindow::ReadURLs(void)
{
    photoUrlList.clear();
#ifdef Q_OS_LINUX
//    photoUrlList.append("/home/ggalt/Pictures/2006-Summer/IMG_0430.JPG");
//    photoUrlList.append("/home/ggalt/Pictures/2006-Summer/IMG_0431.JPG");
//    photoUrlList.append("/home/ggalt/Pictures/2015/Hawaii and California/DSC_0611.JPG");
//    photoUrlList.append("/home/ggalt/Pictures/2015/Hawaii and California/DSC_0633.JPG");

    photoUrlList.append("/home/ggalt/Pictures/2013_07_Hawaii/G0010093.JPG");
    photoUrlList.append("/home/ggalt/Pictures/2013_07_Hawaii/GOPR0116.JPG");
    photoUrlList.append("/home/ggalt/Pictures/2013_07_Hawaii/GOPR0137.JPG");
    photoUrlList.append("/home/ggalt/Pictures/2013_07_Hawaii/GOPR0170.JPG");

#else
    photoUrlList.append("C:/Users/ggalt66/Pictures/Desktop Images/DSC_0682");
    photoUrlList.append("C:/Users/ggalt66/Pictures/Desktop Images/DSC_0759");
    photoUrlList.append("C:/Users/ggalt66/Pictures/Desktop Images/DSC_1656");
    photoUrlList.append("C:/Users/ggalt66/Pictures/Desktop Images/DSC_0738");
#endif

}

QString PhotoWindow::SelectImage(void)
{
    return photoUrlList.at(qrand() % photoUrlList.count());
}


void PhotoWindow::NextImage(void)
{
    QImageReader reader;

    #if QT_VERSION < QT_VERSION_CHECK(5, 4, 0)
      reader.autoDetectImageFormat();
    #else
      reader.setAutoTransform(true);
    #endif

    reader.setFileName(SelectImage());
    qDebug() << reader.fileName();
    foregroundIn->setMyImage(reader.read());
    this->update();
}
