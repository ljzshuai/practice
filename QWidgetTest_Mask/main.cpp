#include <D:\qt\5.8\mingw53_32\include\QtWidgets\QApplication>

#include "shapedwidget.h"
#include <QPoint>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ShapedWidget *widget = new ShapedWidget;
    widget->show();

    return a.exec();
}
