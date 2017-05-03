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

    button = new QPushButton(QString::fromLocal8Bit("ȷ��"),this);
    linedt_name_ = new QLineEdit(this);
    linedt_pwd_  = new QLineEdit(this);
    linedt_rpwd_ = new QLineEdit(this);
    label_msg_   = new QLabel(this);

    QLabel * label_name = new QLabel(QString::fromLocal8Bit("�û���"),this);
    QLabel * label_pwd = new QLabel(QString::fromLocal8Bit("����"),this);
    QLabel * label_rpwd = new QLabel(QString::fromLocal8Bit("ȷ������"),this);


    linedt_name_->setPlaceholderText(QString::fromLocal8Bit("����/Ӣ��/����"));
    linedt_pwd_->setPlaceholderText(QString::fromLocal8Bit("Ӣ��/����/�������"));
    linedt_rpwd_->setPlaceholderText(QString::fromLocal8Bit("Ӣ��/����/�������"));

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

    QGroupBox * gbox = new QGroupBox(QString::fromLocal8Bit("�û�ע��"));
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

     //�޴��ڿ��ƶ�
    setMouseTracking(true);

    QToolButton *minButton = new QToolButton(this);
    QToolButton *closeButton= new QToolButton(this);

    QObject::connect(minButton,&QToolButton::clicked,this,&Register::Msmall);
    QObject::connect(closeButton,&QToolButton::clicked,this,&Register::Mclose);

     //��ȡ��С�����رհ�ťͼ��
    QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);

     //������С�����رհ�ťͼ��
    minButton->setIcon(minPix);
    closeButton->setIcon(closePix);
     //������С�����رհ�ť�ڽ����λ��
    minButton->setGeometry(400-46,1,20,20);
    closeButton->setGeometry(400-25,2,20,20);

     //������С�����رհ�ť����ʽ
    minButton->setStyleSheet("background-color:transparent;");
    closeButton->setStyleSheet("background-color:transparent;");

    QObject::connect(button,&QPushButton::clicked,this,&Register::OnButtonDown);
}

void Register::OnButtonDown()
{
    if(linedt_pwd_->text().size()<1)
    {
        label_msg_->setText(QString::fromLocal8Bit("����������"));
        return;
    }

    if(linedt_pwd_->text() != linedt_rpwd_->text())
    {
        label_msg_->setText(QString::fromLocal8Bit("�������벻ͬ������������"));
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
      //�������ڴ����λ�ã�����ʹ��event->globalPos() - this->pos()��
      move_point = event->pos();;
 }
}

void Register::mouseMoveEvent(QMouseEvent *event)
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

void Register::mouseReleaseEvent(QMouseEvent *event)
{
    //�������Ϊδ������
    mouse_press = false;
}

Register::~Register()
{

}
