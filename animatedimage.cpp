#include "animatedimage.h"

AnimatedImage::AnimatedImage(QSize myParentSize, QWidget *parent) : QWidget(parent)
{
    setScreenSize(myParentSize.width(), myParentSize.height());
    isBackground = false;       // assumed
}


AnimatedImage::~AnimatedImage()
{
}

void AnimatedImage::setMyImage(QImage image)
{
    myImage = image;
    setImageAspect(myImage.width(), myImage.height());

    if(screenAspect > imageAspect) {    // screen is wider than image
        myScaledImage = myImage.scaledToHeight(screenSize.height(), Qt::SmoothTransformation);   // option: Qt::FastTransformation
    } else {                            // image is wider than screen
        myScaledImage = myImage.scaledToWidth(screenSize.width(), Qt::SmoothTransformation);
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

void AnimatedImage::resizeEvent(QResizeEvent *e)
{
    setImageAspect(e->size().width(),e->size().height());
    imageRect.setHeight(e->size().height());
    imageRect.setWidth(e->size().width());
}
