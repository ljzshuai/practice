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

    //���ô�����������ز�����λ�ڶ���
    // setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    // setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);//������ʹ������С��
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);//������ʹ������С��

     //�ɻ�ȡ������Ч��
     setMouseTracking(true);

     QToolButton *minButton = new QToolButton(this);
     QToolButton *closeButton= new QToolButton(this);

     QObject::connect(minButton,&QToolButton::clicked,this,&Widget::small);
     QObject::connect(closeButton,&QToolButton::clicked,this,&Widget::cloose);

     //��ȡ��С�����رհ�ťͼ��
     QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
     QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);

     //������С�����رհ�ťͼ��
     minButton->setIcon(minPix);
     closeButton->setIcon(closePix);
     //������С�����رհ�ť�ڽ����λ��
     minButton->setGeometry(500-66,13,20,20);
     closeButton->setGeometry(500-45,14,20,20);

     //������С�����رհ�ť����ʽ
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
      //�������ڴ����λ�ã�����ʹ��event->globalPos() - this->pos()��
      move_point = event->pos();;
 }
}
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    //��������������
    if(mouse_press)
    {
        //����������Ļ��λ��
        QPoint move_pos = event->globalPos();

       //�ƶ�������λ��
       this->move(move_pos - move_point);
    }
}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    //�������Ϊδ������
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
