#include "MainGradeNew.h"

MainGradeNew::MainGradeNew()
{
    m_button_add       = new QPushButton(QString::fromLocal8Bit("添加"),this);

    m_label_subject    = new QLabel(QString::fromLocal8Bit("学科"),this);
    m_label_term       = new QLabel(QString::fromLocal8Bit("学期"),this);
    m_label_msg        = new QLabel(this);

    m_combox_term      = new QComboBox(this);
    //

    m_lineEdt_subject  = new QLineEdit(this);

    m_grid = new QGridLayout(this);
    m_grid->addWidget(m_label_term,0,0,1,1);
    m_grid->addWidget(m_combox_term,0,1,1,2);

    m_grid->addWidget(m_label_subject,1,0,1,1);
    m_grid->addWidget(m_lineEdt_subject,1,1,1,2);

    m_grid->addWidget(m_button_add,2,0,1,1);
    m_grid->addWidget(m_label_msg,2,1,1,2);

    QObject::connect(m_button_add,&QPushButton::clicked,this,&MainGradeNew::on_button_add);

    this->setWindowModality(Qt::ApplicationModal);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void MainGradeNew::on_button_add()
{
    if(m_lineEdt_subject->text().size() < 1){
        m_label_msg->setText(QString::fromLocal8Bit("请输入学科"));
        return;
    }

    QString tmp = QString("insert into college values ('%1','%2')")
            .arg(m_lineEdt_college->text())
            .arg(m_lineEdt_major->text());
    //
    m_label_msg->setText(QString::fromLocal8Bit("添加成功"));
    m_lineEdt_subject->clear();

}
