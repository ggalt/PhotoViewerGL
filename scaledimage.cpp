#include "scaledimage.h"

#include <QDebug>

ScaledImage::ScaledImage(bool isScaled, QObject *parent) : QObject(parent)
{
    m_isScaled = isScaled;
    m_opacity = 1.0;    // assumed values
    m_blurValue = 0;
    fullScaleImage = QImage(":/Images/blankimage.jpeg");
    m_imageAspect = fullScaleImage.width()*1000/fullScaleImage.height();
}


void ScaledImage::setImage(QImage image)
{
    if( image.isNull() ) {
        image = QImage(":/Image/blankimage.jpeg");
        qDebug() << "loading default image";
    }

    m_imageAspect = (image.width()*1000)/image.height();

    // if there is a blur apply it to the fullscale image (so if we resize, we don't lose the blur)
    if( m_blurValue > 0 ) {
        QGraphicsBlurEffect *blur = new QGraphicsBlurEffect();
        blur->setBlurRadius(blurValue());
        fullScaleImage = applyEffectToImage(QPixmap::fromImage(image), blur, 0);
    } else {
        fullScaleImage = image;
    }

    // if we want a scaled image, scale it
    if( m_isScaled ) {
        if(m_screenAspect > m_imageAspect) {    // screen is wider than image
            scaledImage = fullScaleImage.scaledToHeight(m_screenSize.height(), Qt::SmoothTransformation);   // option: Qt::FastTransformation
        } else {                            // image is wider than screen
            scaledImage = fullScaleImage.scaledToWidth(m_screenSize.width(), Qt::SmoothTransformation);
        }
    }
}

void ScaledImage::setScreenSize(QSize screen)
{
    if(screen.height() < 1) {
        screen = QSize(100,100);
        qDebug() << "Error, screen size is zero";
    }

    m_screenSize = screen;
    m_screenAspect = (screen.width()*1000)/screen.height();

    if(m_isScaled) {
        if(m_screenAspect > m_imageAspect) {    // screen is wider than image
            scaledImage = scaledImage.scaledToHeight(m_screenSize.height(), Qt::SmoothTransformation);   // option: Qt::FastTransformation
        } else {                            // image is wider than screen
            scaledImage = scaledImage.scaledToWidth(m_screenSize.width(), Qt::SmoothTransformation);
        }
    } else {
        scaledImage = fullScaleImage;
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
