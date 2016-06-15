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

class PhotoWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    PhotoWindow();

    Init(void);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    void ReadURLs(void);
    QString NextImage(void);
    void LoadNextPhoto(void);


private:
    QStringList photoUrlList;

    QImage *imgBackground[2];
    QImage *imgForeground[2];
};

#endif // PHOTOWINDOW_H
