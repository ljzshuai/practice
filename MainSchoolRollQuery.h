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
class MainSchoolRollQuery : public QWidget
{
public:
	MainSchoolRollQuery();
	~MainSchoolRollQuery();

private:
	QPLabel 		m_label_ID, m_label_college, m_label_name,
					m_label_major, m_label_sex, m_label_year, m_label_msg_revise,
					m_label_edu, m_label_xz, m_label_perID, m_label_birth;

	QPLineEdit 		m_LineEdt_ID, m_LineEdt_perID, m_LineEdt_year, m_LineEdt_name;
	QPushButton *	m_button_query;
	QPComboBox		m_combox_college, m_combox_major, m_combox_edu, m_combox_xz, m_combox_sex;
	QGridLayout*    m_gboxlay;
	QDate *			m_date;
	QDateEdit*		m_dateEdit;
};

MainSchoolRollQuery::MainSchoolRollQuery()
{
	m_date = new QDate(1990, 1, 1);
	m_dateEdit = new QDateEdit(this);
	m_dateEdit->setDate(*m_date);

	m_label_ID = new QLabel(QString::fromLocal8Bit("      ѧ��"), this);
	m_label_name = new QLabel(QString::fromLocal8Bit("      ����"), this);
	m_label_college = new QLabel(QString::fromLocal8Bit("      ѧԺ"), this);//
	m_label_major = new QLabel(QString::fromLocal8Bit("      רҵ"), this);//
	m_label_sex = new QLabel(QString::fromLocal8Bit("      �Ա�"), this);//
	m_label_year = new QLabel(QString::fromLocal8Bit("      ��ѧ���"), this);
	m_label_edu = new QLabel(QString::fromLocal8Bit("      ѧ��"), this);//
	m_label_xz = new QLabel(QString::fromLocal8Bit("      ѧ��"), this);//
	m_label_perID = new QLabel(QString::fromLocal8Bit("      ���֤"), this);
	m_label_birth = new QLabel(QString::fromLocal8Bit("      ����"));//
	m_label_msg_revise = new QLabel(this);

	m_LineEdt_ID = new QLineEdit(this);
	m_LineEdt_perID = new QLineEdit(this);
	m_LineEdt_year = new QLineEdit(this);
	m_LineEdt_name = new QLineEdit(this);

	m_gboxlay = new QGridLayout(this);

	m_button_query = new QPushButton(QString::fromLocal8Bit("��ѯ"), this);

	m_combox_xz = new QComboBox(this);//ѧ��
	m_combox_edu = new QComboBox(this);//ѧ��
	m_combox_major = new QComboBox(this);//רҵ
	m_combox_college = new QComboBox(this);//ѧԺ
	m_combox_sex = new QComboBox(this);

	m_combox_sex->addItem(QString::fromLocal8Bit("��"));
	m_combox_sex->addItem(QString::fromLocal8Bit("Ů"));

	m_combox_xz->addItem(QString::fromLocal8Bit("һ��"));
	m_combox_xz->addItem(QString::fromLocal8Bit("����"));
	m_combox_xz->addItem(QString::fromLocal8Bit("����"));
	m_combox_xz->addItem(QString::fromLocal8Bit("����"));
	m_combox_xz->addItem(QString::fromLocal8Bit("����"));

	m_combox_edu->addItem(QString::fromLocal8Bit("ר��"));
	m_combox_edu->addItem(QString::fromLocal8Bit("����"));
	m_combox_edu->addItem(QString::fromLocal8Bit("˶ʿ"));
	m_combox_edu->addItem(QString::fromLocal8Bit("��ʿ"));
	m_combox_edu->addItem(QString::fromLocal8Bit("��ʿ��"));


	m_gboxlay->addWidget(m_label_ID, 0, 0, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_ID, 0,1, 1, 1);
	m_gboxlay->addWidget(m_button_query, 0,2,1, 1);
	m_gboxlay->addWidget(m_label_msg_revise, 0, 3, 1, 2);

	m_gboxlay->addWidget(m_label_name, 1, 0, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_name, 1, 1, 1, 1);

	m_gboxlay->addWidget(m_label_college, 2, 0, 1, 1);
	m_gboxlay->addWidget(m_combox_college, 2, 1, 1, 2);

	m_gboxlay->addWidget(m_label_major, 3, 0, 1, 1);
	m_gboxlay->addWidget(m_combox_major, 3, 1, 1, 2);

	m_gboxlay->addWidget(m_label_xz, 4, 0, 1, 1);
	m_gboxlay->addWidget(m_combox_xz, 4, 1, 1, 2);

	m_gboxlay->addWidget(m_label_edu, 5, 0, 1, 1);
	m_gboxlay->addWidget(m_combox_edu, 5, 1, 1, 2);

	m_gboxlay->addWidget(m_label_year, 6, 0, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_year,6, 1, 1, 1);
	m_gboxlay->addWidget(m_label_sex, 6, 2, 1, 1);
	m_gboxlay->addWidget(m_combox_sex, 6, 3, 1, 1);

	m_gboxlay->addWidget(m_label_birth, 7, 0, 1, 1);
	m_gboxlay->addWidget(m_dateEdit, 7, 1, 1, 1);
	m_gboxlay->addWidget(m_label_perID, 7, 2, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_perID, 7, 3, 1, 1);


	QFile styleSheet(":/new/prefix1/qt_practicemyStyle.qss");
	if (!styleSheet.open(QIODevice::ReadOnly))
	{
		qWarning("Can't open the style sheet file.");
		return;
	}
	this->setStyleSheet(styleSheet.readAll());
	this->resize(540, 350);
}

MainSchoolRollQuery::~MainSchoolRollQuery()
{
}