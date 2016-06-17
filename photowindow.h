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

class PhotoWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    PhotoWindow();

    void Init(void);

private slots:
    void LoadNextPhoto(void);

signals:

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    void ReadURLs(void);
    QString NextImage(void);


private:
    QStringList photoUrlList;

    QImage *imgBackground[2];
    QImage *imgForeground[2];
    float imgBGAspectRatio[2];


    int windowWidth;
    int windowHeight;
    float aspectRatio;
    bool isWider;

    QTimer tick;
};

#endif // PHOTOWINDOW_H
