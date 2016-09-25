#include "animatedimage.h"
#include <stdio.h>

AnimatedImage::AnimatedImage(QSize myParentSize, QWidget *parent) : QWidget(parent)
{
    setScreenSize(myParentSize.width(), myParentSize.height());
    isBackground = false;       // assumed
}


AnimatedImage::~AnimatedImage()
{
}

void AnimatedImage::setMyImage(QImage image, bool isBack)
{
    myImage = image;
    setImageAspect(myImage.width(), myImage.height());

    isBackground = isBack;

    if( isBackground ) {
        QGraphicsBlurEffect *blur = new QGraphicsBlurEffect();
        blur->setBlurRadius(getBlurValue());
        myScaledImage = applyEffectToImage(QPixmap::fromImage(image), blur, 0);
    } else {
        if(screenAspect > imageAspect) {    // screen is wider than image
            myScaledImage = myImage.scaledToHeight(screenSize.height(), Qt::SmoothTransformation);   // option: Qt::FastTransformation
        } else {                            // image is wider than screen
            myScaledImage = myImage.scaledToWidth(screenSize.width(), Qt::SmoothTransformation);
        }
    }
    scaledImageSize = myScaledImage.size();
}


void AnimatedImage::AnimationStart(AnimationState s)
{
    myState = s;
    switch(myState) {
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

void AnimatedImage::AnimationStop(void)
{
    switch(myState) {
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


void AnimatedImage::setScreenSize(int width,int height)
{
    screenSize = QSize(width, height);
    screenAspect = (width*1000)/height;

    if(screenAspect > imageAspect) {    // screen is wider than image
        myScaledImage = myImage.scaledToHeight(screenSize.height(), Qt::SmoothTransformation);   // option: Qt::FastTransformation
    } else {                            // image is wider than screen
        myScaledImage = myImage.scaledToWidth(screenSize.width(), Qt::SmoothTransformation);
    }
    scaledImageSize = myScaledImage.size();
}

void AnimatedImage::setImageAspect(int width, int height)
{
    if( height < 1)
        height = 1;
    if( width < 1 )
        width = 1;
    fullImageSize = QSize(width,height);
    imageAspect = (width*1000)/height;
}


void AnimatedImage::resizeEvent(QResizeEvent *e)
{
    setImageAspect(e->size().width(),e->size().height());
    imageRect.setHeight(e->size().height());
    imageRect.setWidth(e->size().width());
}

QImage AnimatedImage::applyEffectToImage(QPixmap src, QGraphicsEffect *effect, int extent)
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
