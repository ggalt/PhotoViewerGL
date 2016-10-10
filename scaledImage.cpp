#include <QDebug>
#include <QPainter>
#include <stdio.h>

#include "scaledImage.h"


ScaledImage::ScaledImage(QSize myParentSize, QWidget *parent) : QWidget(parent)
{
    myFrameSize = myParentSize;
    myFrameAspectRatio = (myParentSize.width() * 1000) / myParentSize.height();
    isBackground = false;       // assumed
    setMyImage(QImage(":/images/blankimage.jpeg"));
}


ScaledImage::~ScaledImage()
{
}

void ScaledImage::setMyImage(QImage image, bool isBack, int blurVal)
{
    isBackground = isBack;

    if( image.isNull() ) {
        image = QImage(":/images/blankimage.jpeg");
        qDebug() << "loading default image";
    }

    m_AspectRatio = (image.width() * 1000) /  image.height();
    qDebug() << "Frame size is:" << myFrameSize << "Image size is:" << image.size();

    if(!isBackground){
        qDebug() << "Not background image";
        if(myFrameAspectRatio >= m_AspectRatio) {    // Frame is wider than image
            qDebug() << "frame is WIDER than image";
            myImage = image.scaledToHeight(myFrameSize.height());
        } else {
            qDebug() << "frame is NARROWER than image";
            myImage = image.scaledToWidth(myFrameSize.width());
        }
    } else {
        qDebug() << "background image with blur of:" << blurVal;
        m_blurValue = blurVal;
        QGraphicsBlurEffect *blur = new QGraphicsBlurEffect();
        blur->setBlurRadius(blurValue());
        myImage = applyEffectToImage(QPixmap::fromImage(image), blur, 0);       // remember, background images remain full size
    }
}

void ScaledImage::setMyFrameSize(QImage image, QSize s)
{
    qDebug() << "scaled image getting frame size of" << s;
    m_AspectRatio = (image.width() * 1000) /  image.height();
    myFrameSize = s;

    if(myFrameAspectRatio >= m_AspectRatio) {    // Frame is wider than image
        qDebug() << "frame is WIDER than image";
        myImage = image.scaledToHeight(myFrameSize.height());
    } else {
        qDebug() << "frame is NARROWER than image";
        myImage = image.scaledToWidth(myFrameSize.width());
    }
}


QImage ScaledImage::applyEffectToImage(QPixmap src, QGraphicsEffect *effect, int extent)
{
    if(src.isNull())
        return QImage(":/images/blankimage.jpeg");   //No need to do anything else!

    qDebug() << "applying blur effect";
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
