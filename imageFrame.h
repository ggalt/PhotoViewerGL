#ifndef IMAGEFRAME_H
#define IMAGEFRAME_H

#include <QWidget>
#include <QResizeEvent>

#include <QPropertyAnimation>
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

#include "scaledImage.h"

typedef enum {
    PreFadeIn,
    FadeIn,
    View,
    FadeOut,
    PostFadeOut } AnimationState;



class ImageFrame : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(int blurValue READ blurValue WRITE setblurValue NOTIFY blurValueChanged)


public:
    explicit ImageFrame(QSize myParentSize, QWidget *parent = 0);
    ~ImageFrame();

    void setInboundImage(QImage image, bool isBack);
    void setblurValue(int b) { m_blurValue = b; emit blurValueChanged(); }
    void setOpacity(qreal o) { m_opacity = o; inbound->setOpacity(o); outbound->setOpacity(1.0 - o); emit opacityChanged(); }
    void setScreenSize(int width,int height); // { screenSize = QSize(width, height); screenAspect = (width*1000)/height; }
    void setAnimationDuration(int d) { animationDuration = d; }
    void setIsBackground(bool is) { isBackground = is; }

    int blurValue(void) { return m_blurValue; }
    qreal opacity(void) { return m_opacity; }

signals:
    void opacityChanged(void);
    void blurValueChanged(void);

public slots:
    void AnimationStart(AnimationState s = PreFadeIn);
    void AnimationStop(void);

protected:
    void resizeEvent(QResizeEvent *e);

private:
    QImage inbound_FullSize;
    QImage outbound_FullSize;
    ScaledImage *inbound;
    ScaledImage *outbound;
    QSize screenSize;
    int m_blurValue;
    qreal m_opacity;
    int screenAspect;
    AnimationState myState;
    int animationDuration;
    bool isBackground;
};

#endif // IMAGEFRAME_H
