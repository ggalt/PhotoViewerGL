#ifndef PHOTOFRAME_H
#define PHOTOFRAME_H

#include <QWidget>

#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsOpacityEffect>
#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QPainter>

#include <QRect>
#include <QSize>
#include <QResizeEvent>

#include "scaledimage.h"

class PhotoFrame : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(int blurValue READ blurValue WRITE setblurValue NOTIFY blurValueChanged)

public:
    explicit PhotoFrame(QSize myParentSize, bool isBackground, QWidget *parent = 0);

    void setblurValue(int b) { m_blurValue = b; in->setblurValue(b); out->setblurValue(b); emit blurValueChanged(); }
    void setOpacity(qreal o) { m_opacity = o; in->setOpacity(o); out->setOpacity(o); emit opacityChanged(); }
    int blurValue(void) { return m_blurValue; }
    qreal opacity(void) { return m_opacity; }

    void LoadImage(QImage image);

    ScaledImage *getInboundImage(void) {return in;}
    ScaledImage *getOutboundImage(void) {return out;}

signals:
    void opacityChanged(void);
    void blurValueChanged(void);


public slots:

protected:
    void resizeEvent(QResizeEvent *e);

private:
//    QImage applyEffectToImage(QPixmap src, QGraphicsEffect *effect, int extent=0);

private:
    int m_blurValue;
    qreal m_opacity;
    bool m_isBackground;
    QSize m_ParentSize;

    ScaledImage *in;
    ScaledImage *out;
};

#endif // PHOTOFRAME_H
