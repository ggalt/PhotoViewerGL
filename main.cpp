#include "photowindow.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    PhotoWindow *p = new PhotoWindow();
//    p->resize(1000,1000);
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    p->setFormat(format);
    p->Init();
    p->show();

    return a.exec();
}
