#include <QDebug>
#include "scaledImage.h"
#include <stdio.h>

ScaledImage::ScaledImage(QSize myParentSize, QWidget *parent) : QWidget(parent)
{
    myFrameSize = myParentSize;
    myFrameAspectRatio (myParentSize.width() * 1000) / myParentSize.height();
    isBackground = false;       // assumed
    setMyImage(QImage(":/Images/blankimage.jpeg"));
}


ScaledImage::~ScaledImage()
{
}

void ScaledImage::setMyImage(QImage image, bool isBack, int blurVal)
{
    m_AspectRatio = (image.width() * 1000) /  image.height();
    isBackground = isBack;

    if( image.isNull() ) {
        myImage = QImage(":/Images/blankimage.jpeg");
        qDebug() << "loading default image";
    }
    else if(!isBackground){
        if(myFrameAspectRatio > m_AspectRatio) {    // Frame is wider than image
            myImage = image.scaledToHeight(myFrameSize.height());
        } else {
            myImage = image.scaledToWidth(myFrameSize.width());
        }
    } else {
        m_blurValue = blurVal;
        QGraphicsBlurEffect *blur = new QGraphicsBlurEffect();
        blur->setBlurRadius(blurValue());
        myImage = applyEffectToImage(QPixmap::fromImage(image), blur, 0);       // remember, background images remain full size
    }
}

void ScaledImage::setMyFrameSize(QImage image, QSize s)
{
    m_AspectRatio = (image.width() * 1000) /  image.height();
    myFrameSize = s;

    if(myFrameAspectRatio > m_AspectRatio) {    // Frame is wider than image
        myImage = image.scaledToHeight(myFrameSize.height());
    } else {
        myImage = image.scaledToWidth(myFrameSize.width());
    }
}


QImage ScaledImage::applyEffectToImage(QPixmap src, QGraphicsEffect *effect, int extent)
{
    if(src.isNull())
        return QImage();   //No need to do anything else!

    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(src);
    item.setGraphicsEffect(effect);
    scene.addItem(&item);
    QImage res(src.size()+QSize(extent*2, extent*2), QImage::Format_ARGB32);
    res.fill(Qt::transparent);
    QPainter ptr(&res);
    scene.render(&ptr, QRectF(), QRectF( -extent, -extent, src.width()+extent*2, src.height()+extent*2 ) );
    return res;
}
