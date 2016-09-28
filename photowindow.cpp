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
//    backgroundIn = new AnimatedImage(this->size(), this);
//    backgroundOut = new AnimatedImage(this->size(), this);
//    foregroundIn = new AnimatedImage(this->size(), this);
//    foregroundOut = new AnimatedImage(this->size(), this);
//    backgroundIn->setOpacity(0.0);
//    backgroundOut->setOpacity(1.0);
//    foregroundIn->setOpacity(0.0);
//    foregroundOut->setOpacity(0.0);
//    backgroundIn->setblurValue(50);
//    backgroundOut->setblurValue(50);
    foreground = new PhotoFrame(this->size(),false,this);
    background = new PhotoFrame(this->size(),true,this);
    animationState = PreFadeIn;

//    foregroundIn->setMyImage(QImage(":/Images/blankimage.jpeg"));
//    backgroundIn->setMyImage(QImage(":/Images/blankimage.jpeg"));
//    foregroundOut->setMyImage(QImage(":/Images/blankimage.jpeg"));
//    backgroundOut->setMyImage(QImage(":/Images/blankimage.jpeg"));

//    anim = new QPropertyAnimation(foregroundIn,"opacity");

    ReadURLs();
    NextImage();

    connect(&tick, SIGNAL(timeout()), this, SLOT(NextImage()));
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
//    backgroundIn->setImageRect(QRect(0,0,w,h));
//    backgroundOut->setImageRect(QRect(0,0,w,h));
//    foregroundIn->setScreenSize(w,h);
//    foregroundOut->setImageRect(QRect(0,0,w,h));
    background->resize(w,h);
    foreground->resize(w,h);
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

//    if( animationState != View ) {    // we will need to draw the "out" images too
//        p.setOpacity(backgroundOut->opacity());

//        if( animationState == FadeIn || animationState == FadeOut ) {   // we need to outgoing foreground image even less
//            p.setOpacity(foregroundOut->opacity());
//        }
//    }

////    p.setOpacity(backgroundIn->opacity());
//    p.setOpacity(1.0);
//    p.drawImage((this->width()-backgroundIn->getScaledImageSize().width())/2,
//                (this->height()-backgroundIn->getScaledImageSize().height())/2,
//                backgroundIn->getMyScaledImage());


//    /// EUREKA!! YOU CAN SET THE OPACITY OF THE PAINTER!!

////    p.setOpacity(foregroundIn->opacity());
//    p.setOpacity(1.0);
//    p.drawImage((this->width()-foregroundIn->getScaledImageSize().width())/2,
//                (this->height()-foregroundIn->getScaledImageSize().height())/2,
//                foregroundIn->getMyScaledImage());

    p.drawImage((this->width()-background->getInboundImage()->getScaledImage().width())/2,
                (this->height()-background->getInboundImage()->getScaledImage().height())/2,
                 background->getInboundImage()->getScaledImage());
    p.drawImage((this->width()-foreground->getInboundImage()->getScaledImage().width())/2,
                (this->height()-foreground->getInboundImage()->getScaledImage().height()/2),
                foreground->getInboundImage()->getScaledImage());
    p.end();
}

void PhotoWindow::ReadURLs(void)
{
    photoUrlList.clear();
#ifdef Q_OS_LINUX
//    photoUrlList.append("/home/ggalt/Pictures/2014-summer/DSC_3264.jpg");
//    photoUrlList.append("/home/ggalt/Pictures/2014-summer/DSC_3325.jpg");
//    photoUrlList.append("/home/ggalt/Pictures/2014-summer/P1000417.JPG");
//    photoUrlList.append("/home/ggalt/Pictures/2014-summer/P1000504.JPG");

//    photoUrlList.append("/home/ggalt/Pictures/2006-Summer/IMG_0430.JPG");
//    photoUrlList.append("/home/ggalt/Pictures/2006-Summer/IMG_0431.JPG");
//    photoUrlList.append("/home/ggalt/Pictures/2015/Hawaii and California/DSC_0611.JPG");
//    photoUrlList.append("/home/ggalt/Pictures/2015/Hawaii and California/DSC_0633.JPG");

    photoUrlList.append("/home/ggalt/Pictures/2013_07_Hawaii/G0010093ww.JPG");
//    photoUrlList.append("/home/ggalt/Pictures/2013_07_Hawaii/G0010093.JPG");
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
    // first swap "in" images for "out" images
//    foregroundOut->setMyImage(foregroundIn->getMyImage());
//    backgroundOut->setMyImage(backgroundIn->getMyImage(),true);

    QImageReader reader;

    #if QT_VERSION < QT_VERSION_CHECK(5, 4, 0)
      reader.autoDetectImageFormat();
    #else
      reader.setAutoTransform(true);
    #endif

    reader.setFileName(SelectImage());
    qDebug() << reader.fileName();
//    foregroundIn->setMyImage(reader.read());
//    backgroundIn->setMyImage(foregroundIn->getMyImage(),true);

//    if(foregroundIn->getMyImage().isNull())
//        qDebug() << "Null Image";

    foreground->LoadImage(reader.read());
    background->LoadImage(reader.read());
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

