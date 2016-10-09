#include <QDebug>
#include "imageFrame.h"
#include <stdio.h>

ImageFrame::ImageFrame(QSize myParentSize, QWidget *parent) : QWidget(parent)
{
    screenSize = myParentSize;
    isBackground = false;       // assumed
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

void ImageFrame::resizeEvent(QResizeEvent *e)
{
    inbound->setMyFrameSize(inbound_FullSize, e->size());
    outbound->setMyFrameSize(outbound_FullSize, e->size());
}

