#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QStringList>
#include <QCheckBox>
#include <QPoint>


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void addd(QStringList);
    void change(int);
    void change1(int);
    void small();
    void cloose();

    void paintEvent1(QPaintEvent *event);

    QPoint move_point; //移动的距离
     bool mouse_press; //鼠标按下
     //鼠标按下事件
     void mousePressEvent(QMouseEvent *event);
    //鼠标释放事件
     void mouseReleaseEvent(QMouseEvent *event);
    //鼠标移动事件
     void mouseMoveEvent(QMouseEvent *event);

private:
    QComboBox  *combox;
    QLineEdit  *linedt;
    QCheckBox  *checkone,*checktwo;

};

#endif // WIDGET_H
