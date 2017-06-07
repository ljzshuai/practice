#ifndef SHAPEDWIDGET_H
#define SHAPEDWIDGET_H

#include <D:\qt\5.8\mingw53_32\include\QtWidgets\QWidget>
class QPoint;
class QPixmap;
class ShapedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShapedWidget(QWidget *parent = 0);    
    ~ShapedWidget();

private slots:
    void changeSkin();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private:
    void initData();
    void initVisualComponents();
    void setupContextMenu();

    QPoint*     dragPos_;
    QPixmap*    backgroundPixmap_;
};

#endif // SHAPEDWIDGET_H
