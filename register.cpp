#include "register.h"
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QPainter>
#include <QColor>
#include <qmath.h>
#include <QMouseEvent>
#include <QToolButton>
#include <QGridLayout>
#include <QPixmap>
#include <QStyle>
#include <QGroupBox>
#include <QPalette>
#include <QColor>
#include <QFormLayout>

Register::Register(QWidget *parent) :
    QWidget(parent),mouse_press(false)
{
    this->resize(400,300);

    QFormLayout * flay = new QFormLayout();
    flay->setRowWrapPolicy(QFormLayout::WrapAllRows);

    QGridLayout * glay = new QGridLayout();
    glay->setMargin(30);

    button = new QPushButton(QString::fromLocal8Bit("确定"),this);
    linedt_name_ = new QLineEdit(this);
    linedt_pwd_  = new QLineEdit(this);
    linedt_rpwd_ = new QLineEdit(this);
    label_msg_   = new QLabel(this);

    QLabel * label_name = new QLabel(QString::fromLocal8Bit("用户名"),this);
    QLabel * label_pwd = new QLabel(QString::fromLocal8Bit("密码"),this);
    QLabel * label_rpwd = new QLabel(QString::fromLocal8Bit("确认密码"),this);


    linedt_name_->setPlaceholderText(QString::fromLocal8Bit("中文/英文/数字"));
    linedt_pwd_->setPlaceholderText(QString::fromLocal8Bit("英文/数字/特殊符号"));
    linedt_rpwd_->setPlaceholderText(QString::fromLocal8Bit("英文/数字/特殊符号"));

    linedt_pwd_->setContextMenuPolicy(Qt::NoContextMenu);
    linedt_name_->setContextMenuPolicy(Qt::NoContextMenu);

    linedt_pwd_->setEchoMode(QLineEdit::Password);
    linedt_rpwd_->setEchoMode(QLineEdit::Password);

    glay->addWidget(label_name,1,0);
    glay->addWidget(linedt_name_,2,0);
    glay->addWidget(label_pwd,3,0);
    glay->addWidget(linedt_pwd_,4,0);
    glay->addWidget(label_rpwd,5,0);
    glay->addWidget(linedt_rpwd_,6,0);
    glay->addWidget(new QLabel(),7,0);
    glay->addWidget(button,8,0);
    glay->addWidget(label_msg_,9,0);

    QGroupBox * gbox = new QGroupBox(QString::fromLocal8Bit("用户注册"));
    gbox->setLayout(glay);
    QGridLayout * gg = new QGridLayout(this);
    gg->addWidget(gbox);

    QPalette pal(this->palette());
    QPixmap pixmap("D:\\boost\\bei.jpg");
    pal.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette(pal);
    this->show();

    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(-5, 5);
    shadow_effect->setColor(Qt::white);//QColor(126,118,168));
    shadow_effect->setBlurRadius(8);
    gbox->setGraphicsEffect(shadow_effect);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

     //无窗口可移动
    setMouseTracking(true);

    QToolButton *minButton = new QToolButton(this);
    QToolButton *closeButton= new QToolButton(this);

    QObject::connect(minButton,&QToolButton::clicked,this,&Register::Msmall);
    QObject::connect(closeButton,&QToolButton::clicked,this,&Register::Mclose);

     //获取最小化、关闭按钮图标
    QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);

     //设置最小化、关闭按钮图标
    minButton->setIcon(minPix);
    closeButton->setIcon(closePix);
     //设置最小化、关闭按钮在界面的位置
    minButton->setGeometry(400-46,1,20,20);
    closeButton->setGeometry(400-25,2,20,20);

     //设置最小化、关闭按钮的样式
    minButton->setStyleSheet("background-color:transparent;");
    closeButton->setStyleSheet("background-color:transparent;");

    QObject::connect(button,&QPushButton::clicked,this,&Register::OnButtonDown);
}

void Register::OnButtonDown()
{
    if(linedt_pwd_->text().size()<1)
    {
        label_msg_->setText(QString::fromLocal8Bit("请输入密码"));
        return;
    }

    if(linedt_pwd_->text() != linedt_rpwd_->text())
    {
        label_msg_->setText(QString::fromLocal8Bit("两次密码不同，请重新输入"));
        return;
    }

    linedt_name_->clear();
    linedt_pwd_->clear();
    linedt_rpwd_->clear();
}

void Register::Mclose()
{
    this->close();
}
void Register::Msmall()
{
    this->showMinimized();
}

void Register::mousePressEvent(QMouseEvent *event)
{
 if(event->button() == Qt::LeftButton)
 {
      mouse_press = true;
      //鼠标相对于窗体的位置（或者使用event->globalPos() - this->pos()）
      move_point = event->pos();;
 }
}

void Register::mouseMoveEvent(QMouseEvent *event)
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

void Register::mouseReleaseEvent(QMouseEvent *event)
{
    //设置鼠标为未被按下
    mouse_press = false;
}

Register::~Register()
{

}
