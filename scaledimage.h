#ifndef SCALEDIMAGE_H
#define SCALEDIMAGE_H

#include <QObject>

#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsOpacityEffect>
#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QPainter>

#include <QRect>
#include <QSize>


class ScaledImage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(int blurValue READ blurValue WRITE setblurValue NOTIFY blurValueChanged)
    Q_PROPERTY(bool isScaled READ isScaled WRITE setIsScaled NOTIFY isScaledChanged)

public:
    explicit ScaledImage(bool isScaled = true, QObject *parent = 0);

    void setblurValue(int b) { m_blurValue = b; emit blurValueChanged(); }
    void setOpacity(qreal o) { m_opacity = o; emit opacityChanged(); }
    void setIsScaled(bool b) { m_isScaled = b; emit isScaledChanged(); }
    int blurValue(void) { return m_blurValue; }
    qreal opacity(void) { return m_opacity; }
    bool isScaled(void) { return m_isScaled; }

    void setImage(QImage image);
    QImage getFullScaleImage(void) { return fullScaleImage; }
    QImage getScaledImage(void) { return scaledImage; }

    void setScreenSize(QSize screen);
    int getImageAspectRatio(void) { return m_imageAspect; }

signals:
    void opacityChanged(void);
    void blurValueChanged(void);
    void isScaledChanged(void);


public slots:

private:
    QImage applyEffectToImage(QPixmap src, QGraphicsEffect *effect, int extent=0);

private:
    QImage fullScaleImage;
    QImage scaledImage;

    int m_blurValue;
    qreal m_opacity;
    bool m_isScaled;

    int m_imageAspect;
    int m_screenAspect;
    QSize m_screenSize;
};

#endif // SCALEDIMAGE_H
