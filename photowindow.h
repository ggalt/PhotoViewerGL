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
#include <QPropertyAnimation>
#include <QTimer>

//#include "animatedimage.h"
#include "photoframe.h"

typedef enum {
    PreFadeIn,
    FadeIn,
    View,
    FadeOut,
    PostFadeOut } AnimationState;



class PhotoWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    PhotoWindow();

    void Init(void);

    void SetFadeSeconds(int s) { fadeSeconds = s; }
    void SetBackgroundFadeSeconds(int s) { backgroundFadeSeconds = s; }

    int GetFadeSeconds(void) { return fadeSeconds; }
    int GetBackgroundFadeSeconds(void) { return backgroundFadeSeconds; }

    qreal GetFadeStep(void) { return fadeStep; }
    qreal GetBackgroundFadeStep(void) { return backgroundFadeStep; }

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
    void SetupSteps(void);


private:
    QStringList photoUrlList;
//    AnimatedImage *backgroundIn;
//    AnimatedImage *backgroundOut;
//    AnimatedImage *foregroundIn;
//    AnimatedImage *foregroundOut;
    PhotoFrame *foreground;
    PhotoFrame *background;


    AnimationState animationState;

    int fadeSeconds;
    int backgroundFadeSeconds;

    qreal fadeStep;
    qreal backgroundFadeStep;

    QTimer tick;
    QPropertyAnimation *anim;

};

#endif // PHOTOWINDOW_H
