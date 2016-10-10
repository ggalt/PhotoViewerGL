#include "photowindow.h"
#include <QDebug>
#include <cstdlib>      // for rand and srand
#include <stdio.h>

PhotoWindow::PhotoWindow()
{

}

void PhotoWindow::Init(void)
{
    qDebug() << "This size is:" << this->size();

    backgroundFrame = new ImageFrame(this->size(), this);
    foregroundFrame = new ImageFrame(this->size(), this);
    backgroundFrame->setOpacity(0);
    backgroundFrame->setblurValue(50);
    foregroundFrame->setOpacity(0);
    animationState = PreFadeIn;

//    anim = new QPropertyAnimation(foregroundIn,"opacity");

    ReadURLs();
    NextImage();

    connect(&tick, SIGNAL(timeout()), this, SLOT(NextImage()));
    connect(backgroundFrame,SIGNAL(opacityChanged()),this, SLOT(repaint()));
    connect(foregroundFrame,SIGNAL(opacityChanged()),this,SLOT(repaint()));
    tick.setInterval(5000);
    tick.start();
}

void PhotoWindow::SetupSteps(void)
{
}


void PhotoWindow::initializeGL()
{
    // Set up the rendering context, load shaders and other resources, etc.:
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void PhotoWindow::resizeGL(int w, int h)
{
    backgroundFrame->setScreenSize(w,h);
    foregroundFrame->setScreenSize(w,h);
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

//    if( animationState != View ) {    // we will need to draw the "out" images too
//        p.setOpacity(backgroundOut->opacity());

//        if( animationState == FadeIn || animationState == FadeOut ) {   // we need to outgoing foreground image even less
//            p.setOpacity(foregroundOut->opacity());
//        }
//    }

//    p.setOpacity(backgroundIn->opacity());

    p.setOpacity(1.0);
    p.drawImage((this->width() - backgroundFrame->getInboundImage()->getMyImage().width())/2,
                (this->height()- backgroundFrame->getInboundImage()->getMyImage().height())/2,
                backgroundFrame->getInboundImage()->getMyImage());

//    p.setOpacity(foregroundIn->opacity());
    p.setOpacity(1.0);
    p.drawImage((this->width() - foregroundFrame->getInboundImage()->getMyImage().width())/2,
                (this->height()- foregroundFrame->getInboundImage()->getMyImage().height())/2,
                foregroundFrame->getInboundImage()->getMyImage());

//    p.drawImage((this->width()-background->getInboundImage()->getScaledImage().width())/2,
//                (this->height()-background->getInboundImage()->getScaledImage().height())/2,
//                 background->getInboundImage()->getScaledImage());
//    p.drawImage((this->width()-foreground->getInboundImage()->getScaledImage().width())/2,
//                (this->height()-foreground->getInboundImage()->getScaledImage().height()/2),
//                foreground->getInboundImage()->getScaledImage());
    p.end();
}

void PhotoWindow::ReadURLs(void)
{
    photoUrlList.clear();
#ifdef Q_OS_LINUX
    //// Lenovo
//    photoUrlList.append("/home/ggalt/Pictures/2014-summer/DSC_3264.jpg");
//    photoUrlList.append("/home/ggalt/Pictures/2014-summer/DSC_3325.jpg");
//    photoUrlList.append("/home/ggalt/Pictures/2014-summer/P1000417.JPG");
//    photoUrlList.append("/home/ggalt/Pictures/2014-summer/P1000504.JPG");

    //// Main
    photoUrlList.append("/home/ggalt/Pictures/2006-Summer/IMG_0430.JPG");
    photoUrlList.append("/home/ggalt/Pictures/2006-Summer/IMG_0431.JPG");
    photoUrlList.append("/home/ggalt/Pictures/2015/Hawaii and California/DSC_0611.JPG");
    photoUrlList.append("/home/ggalt/Pictures/2015/Hawaii and California/DSC_0633.JPG");

//    photoUrlList.append("/home/ggalt/Pictures/2013_07_Hawaii/G0010093ww.JPG");
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
    QImage i(reader.read());
    backgroundFrame->setInboundImage(i,true);
    foregroundFrame->setInboundImage(i,false);

    this->update();
}

void PhotoWindow::AnimateScreen(void)
{
    switch(animationState) {
    case PreFadeIn:
        break;
    case FadeIn:
        break;
    case View:
        break;
    case FadeOut:
        break;
    case PostFadeOut:
        break;
    }
}

