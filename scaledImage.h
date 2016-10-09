#ifndef SCALEDIMAGE_H
#define SCALEDIMAGE_H

#include <QWidget>
#include <QResizeEvent>

#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsOpacityEffect>
#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>

#include <QSize>


class ScaledImage : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(int blurValue READ blurValue WRITE setblurValue NOTIFY blurValueChanged)


public:
    explicit ScaledImage(QSize myParentSize, QWidget *parent = 0);
    ~ScaledImage();


    void setMyImage(QImage image, bool isBack=false, int blurVal=0);
    void setMyFrameSize(QImage image, QSize s);
    void setblurValue(int b) { m_blurValue = b; emit blurValueChanged(); }
    void setOpacity(qreal o) { m_opacity = o; emit opacityChanged(); }

    QImage getMyImage(void) { return myImage; }
    int blurValue(void) { return m_blurValue; }
    qreal opacity(void) { return m_opacity; }
    int getAspectRatio(void) { return m_AspectRatio; }

signals:
    void opacityChanged(void);
    void blurValueChanged(void);

private:
    QImage applyEffectToImage(QPixmap src, QGraphicsEffect *effect, int extent=0);

private:
    QImage myImage;
    QSize myFrameSize;
    int myFrameAspectRatio;
    int m_blurValue;
    qreal m_opacity;
    bool isBackground;
    int m_AspectRatio;
};

#endif // SCALEDIMAGE_H
