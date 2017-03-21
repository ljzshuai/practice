#pragma once
#include <qlineedit.h>
#include <qstring.h>
#include <qwidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qtablewidget.h>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QGridLayout>
#include <QComboBox>
#include <qfile.h>
#include <QDate>
#include <QDateEdit>

using QPLabel = QLabel *;
using QPLineEdit = QLineEdit *;
using QPComboBox = QComboBox *;
class MainSchoolRollAdd : public QWidget
{
public:
	MainSchoolRollAdd();
	~MainSchoolRollAdd();

	void on_button_add();
    void on_combox_college_change();

private:
	QPLabel 		m_label_ID,    m_label_college, m_label_name,
					m_label_major, m_label_sex,     m_label_year,  m_label_msg_revise,
					m_label_edu,   m_label_xz,      m_label_perID, m_label_birth;
	 
	QPLineEdit 		m_LineEdt_ID,  m_LineEdt_perID, m_LineEdt_year, m_LineEdt_name;
	QPushButton *	m_button_add;
	QPComboBox		m_combox_college, m_combox_major,m_combox_edu,m_combox_xz,m_combox_sex;
	QGridLayout*    m_gboxlay;
	QDate *			m_date;
	QDateEdit*		m_dateEdit;
    QStringList*    m_StrList_college,*m_StrList_majr;
};

MainSchoolRollAdd::MainSchoolRollAdd()
{
	m_date = new QDate(1990, 1, 1);
	m_dateEdit = new QDateEdit(this);
	m_dateEdit->setDate(*m_date);

	m_label_ID			= new QLabel(QString::fromLocal8Bit("      学号"), this);
	m_label_name		= new QLabel(QString::fromLocal8Bit("      姓名"), this);
	m_label_college		= new QLabel(QString::fromLocal8Bit("      学院"), this);//
	m_label_major		= new QLabel(QString::fromLocal8Bit("      专业"), this);//
	m_label_sex			= new QLabel(QString::fromLocal8Bit("      性别"), this);//
	m_label_year		= new QLabel(QString::fromLocal8Bit("      入学年份"), this);
	m_label_edu			= new QLabel(QString::fromLocal8Bit("      学历"), this);//
	m_label_xz			= new QLabel(QString::fromLocal8Bit("      学制"), this);//
	m_label_perID		= new QLabel(QString::fromLocal8Bit("      身份证"),this);
	m_label_birth		= new QLabel(QString::fromLocal8Bit("      生日"));//
	m_label_msg_revise	= new QLabel(this);

	m_LineEdt_ID		= new QLineEdit(this);
	m_LineEdt_perID		= new QLineEdit(this);
	m_LineEdt_year		= new QLineEdit(this);
	m_LineEdt_name		= new QLineEdit(this);

	m_gboxlay			= new QGridLayout(this);

	m_button_add		= new QPushButton(QString::fromLocal8Bit("添加"), this);

	m_combox_xz			= new QComboBox(this);//学制
	m_combox_edu		= new QComboBox(this);//学历
	m_combox_major		= new QComboBox(this);//专业
	m_combox_college	= new QComboBox(this);//学院
	m_combox_sex		= new QComboBox(this);

    QString("select distinct college from college").toUtf8();
    //use first
    QString("select * from college where college = '%1'").arg(m_combox_college->currentText());
    QStringList *tmp;

    //m_StrList_college = mysql->xxxx();
    m_combox_college->addItems(*m_StrList_college);

	m_combox_sex->addItem(QString::fromLocal8Bit("男"));
	m_combox_sex->addItem(QString::fromLocal8Bit("女"));

	m_combox_xz->addItem(QString::fromLocal8Bit("一年"));
	m_combox_xz->addItem(QString::fromLocal8Bit("两年"));
	m_combox_xz->addItem(QString::fromLocal8Bit("三年"));
	m_combox_xz->addItem(QString::fromLocal8Bit("四年"));
	m_combox_xz->addItem(QString::fromLocal8Bit("五年"));

	m_combox_edu->addItem(QString::fromLocal8Bit("专科"));
	m_combox_edu->addItem(QString::fromLocal8Bit("本科"));
	m_combox_edu->addItem(QString::fromLocal8Bit("硕士"));
	m_combox_edu->addItem(QString::fromLocal8Bit("博士"));
	m_combox_edu->addItem(QString::fromLocal8Bit("博士后"));

	m_gboxlay->addWidget(m_label_name, 0, 0, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_name, 0, 1, 1, 1);
	m_gboxlay->addWidget(m_label_ID, 0, 2, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_ID, 0, 3, 1, 1);

	m_gboxlay->addWidget(m_label_college, 1, 0, 1, 1);
	m_gboxlay->addWidget(m_combox_college, 1, 1, 1, 2);

	m_gboxlay->addWidget(m_label_major, 2, 0, 1, 1);
	m_gboxlay->addWidget(m_combox_major, 2, 1, 1, 2);

	m_gboxlay->addWidget(m_label_xz, 3, 0, 1, 1);
	m_gboxlay->addWidget(m_combox_xz, 3, 1, 1, 2);

	m_gboxlay->addWidget(m_label_edu, 4, 0, 1, 1);
	m_gboxlay->addWidget(m_combox_edu, 4, 1, 1, 2);

	m_gboxlay->addWidget(m_label_year, 5, 0, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_year, 5, 1, 1, 1);
	m_gboxlay->addWidget(m_label_sex, 5, 2, 1, 1);
	m_gboxlay->addWidget(m_combox_sex, 5, 3, 1, 1);

	m_gboxlay->addWidget(m_label_birth, 6, 0, 1, 1);
	m_gboxlay->addWidget(m_dateEdit, 6, 1, 1, 1);
	m_gboxlay->addWidget(m_label_perID, 6, 2, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_perID, 6, 3, 1, 1);

	m_gboxlay->addWidget(m_button_add, 7, 1, 1, 1);
	m_gboxlay->addWidget(m_label_msg_revise, 7, 2, 1, 2);

	QFile styleSheet(":/new/prefix1/qt_practicemyStyle.qss");
	if (!styleSheet.open(QIODevice::ReadOnly))
	{
		qWarning("Can't open the style sheet file.");
		return;
	}
	this->setStyleSheet(styleSheet.readAll());

	this->resize(540, 350);

	QObject::connect(m_button_add, &QPushButton::clicked, this, &MainSchoolRollAdd::on_button_add);
    QObject::connect(m_combox_college,&QComboBox::currentIndexChanged,this,&MainSchoolRollAdd::on_combox_college_change());

	this->setWindowModality(Qt::ApplicationModal);
	this->setAttribute(Qt::WA_DeleteOnClose);
}

void MainSchoolRollAdd::on_button_add()
{
	if (m_LineEdt_ID->text().size() == 0)
		m_label_msg_revise->setText(QString::fromLocal8Bit("请输入学号"));
	if (m_LineEdt_name->text().size() == 0)
		m_label_msg_revise->setText(QString::fromLocal8Bit("请输入姓名"));
	if (m_LineEdt_perID->text().size() == 0)
		m_label_msg_revise->setText(QString::fromLocal8Bit("请输入身份证号"));
	if (m_LineEdt_year->text().size() == 0)
		m_label_msg_revise->setText(QString::fromLocal8Bit("请输入入学年份"));


    QString("insert into schoolroll values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10')")
            .arg(m_LineEdt_ID->text())
            .arg(m_LineEdt_name->text())
            .arg(m_combox_college->currentText())
            .arg(m_combox_major->currentText())
            .arg(m_combox_sex->currentText())
            .arg(m_LineEdt_year->text())
            .arg(m_combox_edu->currentText())
            .arg(m_combox_xz->currentText())
            .arg(m_LineEdt_perID->text())
            .arg(m_dateEdit->date().toString(Qt::ISODate));
    //mysql-> tian jia
    m_label_msg_revise->setText(QString::fromLocal8Bit("shi bai qing chong shi"));



}

MainSchoolRollAdd::on_combox_college_change()
{
   QString tmp =  QString("select major from college where college = '%1'").arg(m_combox_college->currentText());
   //mysql->input_sql

   //fail
    m_label_msg_revise->setText(QString::fromLocal8Bit("shi bai qing chong shi"));
    //success
    m_combox_major->clear();
   delete m_StrList_majr;
    m_StrList_majr;//=mysql->xxx();
    m_combox_major->addActions(*m_StrList_majr);
}

MainSchoolRollAdd::~MainSchoolRollAdd()
{
}
