#ifndef ANIMATEDIMAGE_H
#define ANIMATEDIMAGE_H

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

typedef enum {
    PreFadeIn,
    FadeIn,
    View,
    FadeOut,
    PostFadeOut } AnimationState;



class AnimatedImage : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(int blurValue READ blurValue WRITE setblurValue NOTIFY blurValueChanged)


public:
    explicit AnimatedImage(QSize myParentSize, QWidget *parent = 0);
    ~AnimatedImage();


    void setMyImage(QImage image, bool isBack=false);
    void setImageRect(QRect r) { imageRect = r; }
    void setblurValue(int b) { m_blurValue = b; emit blurValueChanged(); }
    void setOpacity(qreal o) { m_opacity = o; emit opacityChanged(); }
    void setImageAspect(int width, int height);
    void setScreenSize(int width,int height); // { screenSize = QSize(width, height); screenAspect = (width*1000)/height; }
    void setAnimationDuration(int d) { animationDuration = d; }
    void setIsBackground(bool is) { isBackground = is; }

    QImage getMyImage(void) { return myImage; }
    QImage getMyScaledImage(void) { return myScaledImage; }
    QRect getImageRect(void) { return imageRect; }
    QSize getScaledImageSize(void) { return scaledImageSize; }
    int blurValue(void) { return m_blurValue; }
    qreal opacity(void) { return m_opacity; }
    int getImageAspect(void) { return imageAspect; }
    int getAnimationDuration(void) { return animationDuration; }
    bool getIsBackground(void) { return isBackground; }

signals:
    void opacityChanged(void);
    void blurValueChanged(void);

public slots:
    void AnimationStart(AnimationState s = PreFadeIn);
    void AnimationStop(void);

protected:
    void resizeEvent(QResizeEvent *e);

private:
    QImage applyEffectToImage(QPixmap src, QGraphicsEffect *effect, int extent=0);

private:
    QImage myImage;
    QImage myScaledImage;
    QSize fullImageSize;
    QSize scaledImageSize;
    QSize screenSize;
    QRect imageRect;
    int m_blurValue;
    qreal m_opacity;
    int imageAspect;
    int screenAspect;
    AnimationState myState;
    int animationDuration;
    bool isBackground;
//    QPropertyAnimation *anim;
//    QGraphicsBlurEffect *blur;
//    QGraphicsOpacityEffect *opacity;
};

#endif // ANIMATEDIMAGE_H
