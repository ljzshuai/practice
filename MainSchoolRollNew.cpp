#include "MainSchoolRollNew.h"

MainSchoolRollNew::MainSchoolRollNew()

{
    m_button_add      = new QPushButton(QString::fromLocal8Bit("添加"),this);

    m_label_major     = new QLabel(QString::fromLocal8Bit("专业"),this);
    m_label_college   = new QLabel(QString::fromLocal8Bit("学院"),this);
    m_label_msg       = new QLabel(this);

    m_lineEdt_college = new QLineEdit(this);
    m_lineEdt_major   = new QLineEdit(this);

    m_grid = new QGridLayout(this);
    m_grid->addWidget(m_label_college,0,0,1,1);
    m_grid->addWidget(m_lineEdt_college,0,1,1,2);

    m_grid->addWidget(m_label_major,1,0,1,1);
    m_grid->addWidget(m_lineEdt_major,1,1,1,2);

    m_grid->addWidget(m_button_add,2,0,1,1);
    m_grid->addWidget(m_label_msg,2,1,1,2);

    QObject::connect(m_button_add,&QPushButton::clicked,this,&MainSchoolRollNew::on_button_add);

    this->setWindowModality(Qt::ApplicationModal);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void MainSchoolRollNew::objectName()
{
    if(m_lineEdt_college->text().size() < 1){
        m_label_msg->setText(QString::fromLocal8Bit("请输入学院"));
        return;
    }
    if(m_lineEdt_major->text().size() < 1){
        m_label_msg->setText(QString::fromLocal8Bit("请输入专业"));
    }
    QString tmp = QString("insert into college values ('%1','%2')")
            .arg(m_lineEdt_college->text())
            .arg(m_lineEdt_major->text());
    //
    m_label_msg->setText(QString::fromLocal8Bit("添加成功"));
    m_lineEdt_college->clear();
    m_lineEdt_major->clear();
}
