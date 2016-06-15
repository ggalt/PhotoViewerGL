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
    photoUrlList.append("C:\Users\ggalt66\Pictures\Desktop Images\DSC_0682");
    photoUrlList.append("C:\Users\ggalt66\Pictures\Desktop Images\DSC_0759");
    photoUrlList.append("C:\Users\ggalt66\Pictures\Desktop Images\DSC_1656");
    photoUrlList.append("C:\Users\ggalt66\Pictures\Desktop Images\DSC_0738");
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
