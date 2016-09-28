#include "photoframe.h"

PhotoFrame::PhotoFrame(QSize myParentSize, bool isBackground, QWidget *parent) : QWidget(parent)
{
    m_blurValue = 0;
    m_opacity = 0.0;

    in = new ScaledImage(!isBackground);
    out = new ScaledImage(!isBackground);

    m_ParentSize = myParentSize;

    in->setScreenSize(myParentSize);
    out->setScreenSize(myParentSize);
}

void PhotoFrame::LoadImage(QImage image)
{
    out->setImage(in->getFullScaleImage());
    in->setImage(image);
}

void PhotoFrame::resizeEvent(QResizeEvent *e)
{
    in->setScreenSize(e->size());
}
