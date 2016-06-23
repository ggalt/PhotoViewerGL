#include "photowindow.h"
#include <QDebug>
#include <cstdlib>      // for rand and srand

PhotoWindow::PhotoWindow()
{

}

void PhotoWindow::Init(void)
{
    fullImage[0] = new QImage();
    fullImage[1] = new QImage();
    ReadURLs();
    tick.setInterval(5000);

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    connect(&tick, SIGNAL(timeout()),
            this, SLOT(LoadNextPhoto()));
    tick.start();
}

void PhotoWindow::initializeGL()
{
    // Set up the rendering context, load shaders and other resources, etc.:
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    windowWidth = this->geometry().width();
    windowHeight = this->geometry().height();
}

void PhotoWindow::resizeGL(int w, int h)
{
    windowWidth = w;
    windowHeight= h;
    aspectRatio = (float)windowWidth / (float)windowHeight;
    isWider = aspectRatio > 1 ? true : false;
    this->update();
}

void PhotoWindow::paintGL()
{
    // Draw the scene:
    qDebug() << "paint";
    QPainter p;
    p.begin(this);
    QRect r = QRect(0,0,windowWidth,windowHeight);
    QBrush b(Qt::black);
    p.fillRect(r,b);

    int x = 0;
    int y = 0;
//    if(aspectRatio > imgBGAspectRatio[0])
//        x = (int)(windowWidth-(windowHeight*imgBGAspectRatio[0]))/2;
//    else
//        y = (int)(windowHeight-(windowWidth/imgBGAspectRatio[0]))/2;

//    p.drawImage(x,y,imgBackground[0]->scaled(windowWidth,windowHeight,Qt::KeepAspectRatio));
    if(aspectRatio > fullImgAspectRation[0]) {
        // window is wider than image
        // set image width to window and adjust height using image aspect
        // set y to a negative equal to half the height difference of window and adjusted image
        y = (int)(windowHeight - (float)windowWidth/fullImgAspectRation[0])/2;
        p.drawImage(x,y,fullImage[0]->scaled(windowWidth,(windowWidth / fullImgAspectRation[0]),Qt::KeepAspectRatioByExpanding));
    }
    else {
        // window is taller than image
        // set image height to window and adjust width using image aspect
        // set x to a negative equal to half the width difference between window and adjusted image
        x = (int)(windowWidth - (float)windowHeight*fullImgAspectRation[0])/2;
        p.drawImage(x,y,fullImage[0]->scaled(windowHeight*fullImgAspectRation[0],windowHeight,Qt::KeepAspectRatioByExpanding));
    }

    qDebug() << x << y;
    p.end();
}

void PhotoWindow::ReadURLs(void)
{
    photoUrlList.clear();
#ifdef Q_OS_LINUX
    photoUrlList.append("/home/ggalt/Pictures/DesktopImages/DSC_0004.JPG");
    photoUrlList.append("/home/ggalt/Pictures/DesktopImages/DSC_0686-1.JPG");
    photoUrlList.append("/home/ggalt/Pictures/DesktopImages/DSC_0712-1.JPG");
    photoUrlList.append("/home/ggalt/Pictures/DesktopImages/DSC_0796-1.JPG");

//    photoUrlList.append("/home/ggalt/Pictures/2006-Summer/IMG_0430.JPG");
//    photoUrlList.append("/home/ggalt/Pictures/2006-Summer/IMG_0431.JPG");
//    photoUrlList.append("/home/ggalt/Pictures/2015/Hawaii and California/DSC_0611.JPG");
//    photoUrlList.append("/home/ggalt/Pictures/2015/Hawaii and California/DSC_0633.JPG");
#else
    photoUrlList.append("C:/Users/ggalt66/Pictures/Desktop Images/DSC_0682");
    photoUrlList.append("C:/Users/ggalt66/Pictures/Desktop Images/DSC_0759");
    photoUrlList.append("C:/Users/ggalt66/Pictures/Desktop Images/DSC_1656");
    photoUrlList.append("C:/Users/ggalt66/Pictures/Desktop Images/DSC_0738");
#endif

}

QString PhotoWindow::NextImage(void)
{
    return photoUrlList.at(qrand() % photoUrlList.count());
}


void PhotoWindow::LoadNextPhoto(void)
{
    QImageReader reader;

    #if QT_VERSION < QT_VERSION_CHECK(5, 4, 0)
    reader.autoDetectImageFormat();
    #else
    reader.setAutoTransform(true);
    #endif

    reader.setFileName(NextImage());
    qDebug() << reader.fileName();
    if( !fullImage[1]->isNull() ) {
        delete fullImage[1];
        fullImage[1] = fullImage[0];
    }
    fullImage[0] = new QImage(reader.read());
    if(fullImage[0]->isNull())
        qDebug() << reader.errorString();
    fullImgAspectRation[0] = (float)fullImage[0]->width() / (float)fullImage[0]->height();
    this->update();
}
