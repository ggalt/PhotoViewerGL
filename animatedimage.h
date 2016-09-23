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
public:
    explicit AnimatedImage(QSize myParentSize, QWidget *parent = 0);
    ~AnimatedImage();


    void setMyImage(QImage image);
    void setImageRect(QRect r) { imageRect = r; }
    void setBlurValue(int b) { blurValue = b; }
    void setImageAspect(int width, int height) { fullImageSize = QSize(width,height); imageAspect = (width*1000)/height; }
    void setScreenSize(int width,int height); // { screenSize = QSize(width, height); screenAspect = (width*1000)/height; }
    void setAnimationDuration(int d) { animationDuration = d; }
    void setIsBackground(bool is) { isBackground = is; }

    QImage getMyImage(void) { return myImage; }
    QImage getMyScaledImage(void) { return myScaledImage; }
    QRect getImageRect(void) { return imageRect; }
    QSize getScaledImageSize(void) { return scaledImageSize; }
    int getBlurValue(void) { return blurValue; }
    int getImageAspect(void) { return imageAspect; }
    int getAnimationDuration(void) { return animationDuration; }
    bool getIsBackground(void) { return isBackground; }

signals:

public slots:
    void AnimationStart(AnimationState s = PreFadeIn);
    void AnimationStop(void);

protected:
    void resizeEvent(QResizeEvent *e);

private:

private:
    QImage myImage;
    QImage myScaledImage;
    QSize fullImageSize;
    QSize scaledImageSize;
    QSize screenSize;
    QRect imageRect;
    int blurValue;
    int imageAspect;
    int screenAspect;
    AnimationState myState;
    int animationDuration;
    bool isBackground;
    QPropertyAnimation *anim;
    QGraphicsBlurEffect *blur;
    QGraphicsOpacityEffect *opacity;
};

#endif // ANIMATEDIMAGE_H
