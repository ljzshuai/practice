#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QPoint>
#include <QLabel>

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

    void Msmall();
    void Mclose();
    void OnButtonDown();

    //void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
     QPoint move_point;
     bool   mouse_press;

     QPushButton * button;
     QLineEdit *   linedt_name_,*linedt_pwd_,*linedt_rpwd_;
     QLabel *      label_msg_;
};

#endif // WIDGET_H
