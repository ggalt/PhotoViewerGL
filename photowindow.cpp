#include "photowindow.h"
#include <cstdlib>      // for rand and srand

PhotoWindow::PhotoWindow()
{

}

void PhotoWindow::Init(void)
{
}

void PhotoWindow::initializeGL()
{

}

void PhotoWindow::resizeGL(int w, int h)
{

}

void PhotoWindow::paintGL()
{

}

void PhotoWindow::ReadURLs(void)
{
    photoUrlList.clear();
#ifdef Q_OS_LINUX
    photoUrlList.append("/home/ggalt/Pictures/2006-Summer/IMG_0430.JPG");
    photoUrlList.append("/home/ggalt/Pictures/2006-Summer/IMG_0431.JPG");
    photoUrlList.append("/home/ggalt/Pictures/2015/Hawaii and California/DSC_0611.JPG");
    photoUrlList.append("/home/ggalt/Pictures/2015/Hawaii and California/DSC_0633.JPG");
#else
    photoUrlList.append("C:\Users\ggalt66\Pictures\Desktop Images\DSC_0682");
    photoUrlList.append("C:\Users\ggalt66\Pictures\Desktop Images\DSC_0759");
    photoUrlList.append("C:\Users\ggalt66\Pictures\Desktop Images\DSC_1656");
    photoUrlList.append("C:\Users\ggalt66\Pictures\Desktop Images\DSC_0738");
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
    if( !imgBackground[1]->isNull() )
        delete imgBackground[1];

    imgBackground[1] = imgBackground[0];
    imgBackground[0] = new QImage(reader.read());
}
