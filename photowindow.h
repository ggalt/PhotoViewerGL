#ifndef PHOTOWINDOW_H
#define PHOTOWINDOW_H

#include <QObject>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <QString>
#include <QStringList>

#include <QImage>
#include <QImageReader>
#include <QPixmap>

#include <QBrush>
#include <QColor>

#include <QPainter>

#include <QTimer>

#include "animatedimage.h"

class PhotoWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    PhotoWindow();

    void Init(void);

private slots:
    void NextImage(void);
    void AnimateScreen(void);

signals:

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    void ReadURLs(void);
    QString SelectImage(void);


private:
    QStringList photoUrlList;
    AnimatedImage *backgroundIn;
    AnimatedImage *backgroundOut;
    AnimatedImage *foregroundIn;
    AnimatedImage *foregroundOut;

    AnimationState animationState;

    QTimer tick;
};

#endif // PHOTOWINDOW_H
