#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QPainter>
#include <QColor>
#include <qmath.h>
#include <QMouseEvent>
#include <QToolButton>
#include <QVBoxLayout>
#include <QPixmap>

Widget::Widget(QWidget *parent) :
    QWidget(parent),mouse_press(false)
{
    this->resize(500,500);

    combox = new QComboBox(this);
    linedt = new QLineEdit(this);
    checkone = new QCheckBox("save pass",this);
    checktwo = new QCheckBox("save all",this);
    QPushButton * button1 = new QPushButton(this);
     QPushButton * button = new QPushButton(this);

     QVBoxLayout * verticalLayout = new QVBoxLayout(this);

   verticalLayout->setMargin(30);
   verticalLayout->addWidget(combox);
   verticalLayout->addWidget(linedt);
   verticalLayout->addWidget(checkone);
   verticalLayout->addWidget(checktwo);
   verticalLayout->addWidget(button1);
   verticalLayout->addWidget(button);

    QObject::connect(checktwo,&QCheckBox::stateChanged,this,&Widget::change);
    QObject::connect(checkone,&QCheckBox::stateChanged,this,&Widget::change1);

    combox->setEditable(true);

    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(-5, 5);
    shadow_effect->setColor(Qt::gray);
    shadow_effect->setOffset(0,0);
    shadow_effect->setBlurRadius(8);
   // button1->setGraphicsEffect(shadow_effect);
   this->setGraphicsEffect(shadow_effect);

    //设置窗体标题栏隐藏并设置位于顶层
    // setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    // setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);//任务栏使程序最小化
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);//任务栏使程序最小化

     //可获取鼠标跟踪效果
     setMouseTracking(true);

     QToolButton *minButton = new QToolButton(this);
     QToolButton *closeButton= new QToolButton(this);

     QObject::connect(minButton,&QToolButton::clicked,this,&Widget::small);
     QObject::connect(closeButton,&QToolButton::clicked,this,&Widget::cloose);

     //获取最小化、关闭按钮图标
     QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
     QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);

     //设置最小化、关闭按钮图标
     minButton->setIcon(minPix);
     closeButton->setIcon(closePix);
     //设置最小化、关闭按钮在界面的位置
     minButton->setGeometry(500-66,13,20,20);
     closeButton->setGeometry(500-45,14,20,20);

     //设置最小化、关闭按钮的样式
     minButton->setStyleSheet("background-color:transparent;");
     closeButton->setStyleSheet("background-color:transparent;");
}

void Widget::paintEvent1(QPaintEvent *event)
{
    QPainterPath path;
    path.setFillRule(Qt::OddEvenFill);
    path.addRect(10, 10, this->width()-20, this->height()-20);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0, 0, 0, 50);
    for(int i=0; i<10; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}

void Widget::cloose()
{
    this->close();
}
void Widget::small()
{
    this->showMinimized();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
 if(event->button() == Qt::LeftButton)
 {
      mouse_press = true;
      //鼠标相对于窗体的位置（或者使用event->globalPos() - this->pos()）
      move_point = event->pos();;
 }
}
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    //若鼠标左键被按下
    if(mouse_press)
    {
        //鼠标相对于屏幕的位置
        QPoint move_pos = event->globalPos();

       //移动主窗体位置
       this->move(move_pos - move_point);
    }
}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    //设置鼠标为未被按下
    mouse_press = false;
}

void Widget::change1(int state)
{
    if(checktwo->isChecked())
    {
        checkone->setChecked(true);
    }
}

void Widget::change(int state)
{
        qDebug()<<combox->currentText();

    if(state == Qt::Checked)
    {
        checkone->setChecked(true);
        return;
    }
    checkone->setChecked(false);

}

void Widget::addd(QStringList name)
{
    combox->addItems(name);
}


Widget::~Widget()
{

}
