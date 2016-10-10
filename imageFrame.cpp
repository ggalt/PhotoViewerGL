#include <QDebug>
#include "imageFrame.h"
#include <stdio.h>

ImageFrame::ImageFrame(QSize myParentSize, QWidget *parent) : QWidget(parent)
{
    qDebug() << "Establshing Frame";
    screenSize = myParentSize;
    isBackground = false;       // assumed
    inbound_FullSize = QImage(":/images/blankimage.jpeg");
    outbound_FullSize = QImage(":/images/blankimage.jpeg");
    inbound = new ScaledImage(myParentSize, parent);
    outbound = new ScaledImage(myParentSize, parent);
}


ImageFrame::~ImageFrame()
{
    inbound->deleteLater();
    outbound->deleteLater();
}

void ImageFrame::setInboundImage(QImage image, bool isBack)
{
    qDebug() << "setting inbound image";
    outbound_FullSize = QImage(inbound_FullSize);
    inbound_FullSize = image;
    m_opacity = 0.0;
    isBackground = isBack;
    outbound->setMyImage(outbound_FullSize,isBackground,m_blurValue);
    inbound->setMyImage(inbound_FullSize,isBackground,m_blurValue);
}


void ImageFrame::AnimationStart(AnimationState s)
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

void ImageFrame::AnimationStop(void)
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

void ImageFrame::setScreenSize(int width,int height)
{
    setScreenSize(QSize(width,height));
}

void ImageFrame::setScreenSize(QSize s)
{
    qDebug() << "setting screen size to:" << s;
    inbound->setMyFrameSize(inbound_FullSize, s);
    outbound->setMyFrameSize(outbound_FullSize, s);
}

void ImageFrame::resizeEvent(QResizeEvent *e)
{
    setScreenSize(e->size());
}

