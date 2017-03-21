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

using QPLabel = QLabel *;
using QPLineEdit = QLineEdit *;
class MainGradeAdd : public QWidget
{
public:
	MainGradeAdd();
	~MainGradeAdd();

private:
	QPLabel 		m_label_ID,m_label_term, m_label_name,
					m_label_subject, m_label_grade, m_label_Rgrade, m_label_msg_revise;
	QPLineEdit 		m_LineEdt_ID, m_LineEdt_grade, m_LineEdt_Rgrade,m_LineEdt_name;
	QPushButton *	m_button_add;
	QComboBox*		m_combox_term, *m_combox_subject;
	QGridLayout*    m_gboxlay;
};

MainGradeAdd::MainGradeAdd()
{
	m_label_ID			= new QLabel(QString::fromLocal8Bit("      ѧ��"), this);
	m_label_name		= new QLabel(QString::fromLocal8Bit("      ����"), this);
	m_label_term		= new QLabel(QString::fromLocal8Bit("      ѧ��"), this);
	m_label_subject		= new QLabel(QString::fromLocal8Bit("      ��Ŀ"), this);
	m_label_grade		= new QLabel(QString::fromLocal8Bit("      �ɼ�"), this);
	m_label_Rgrade		= new QLabel(QString::fromLocal8Bit("      �����ɼ�"), this);
	m_label_msg_revise	= new QLabel(this);

	m_LineEdt_ID		= new QLineEdit(this);
	m_LineEdt_grade		= new QLineEdit(this);
	m_LineEdt_Rgrade	= new QLineEdit(this);
	m_LineEdt_name		= new QLineEdit(this);

	m_gboxlay			= new QGridLayout(this);

	m_button_add		= new QPushButton(QString::fromLocal8Bit("���"), this);

	m_combox_subject	= new QComboBox(this);
	m_combox_term		= new QComboBox(this);

	m_gboxlay->addWidget(m_label_ID, 0, 0, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_ID, 0, 1, 1, 1);
	m_gboxlay->addWidget(m_label_name, 0, 2, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_name, 0, 3, 1, 1);
	//m_gboxlay->addWidget(new QLabel(this), 0, 4, 1, 2);

	m_gboxlay->addWidget(m_label_term, 1, 0, 1, 1);
	m_gboxlay->addWidget(m_combox_term, 1, 1, 1, 2);

	m_gboxlay->addWidget(m_label_subject, 2, 0, 1, 1);
	m_gboxlay->addWidget(m_combox_subject, 2, 1, 1, 2);

	m_gboxlay->addWidget(m_label_grade, 3, 0, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_grade, 3, 1, 1, 1);
	m_gboxlay->addWidget(m_label_Rgrade, 3, 2, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_Rgrade, 3, 3, 1, 1);
	//m_gboxlay->addWidget(new QLabel(this), 3, 4, 1, 2);

	m_gboxlay->addWidget(m_button_add, 4, 1, 1, 1);
	m_gboxlay->addWidget(m_label_msg_revise, 4, 2, 1, 1);


    QString("select distinct term from grade").toUtf8();
    //use first
    QString("select * from grade where term = '%1'").arg(m_combox_college->currentText());
    QStringList *tmp;

	m_combox_subject->addItem("12345");
	m_combox_subject->addItem("qwerrt");

	QFile styleSheet(":/new/prefix1/qt_practicemyStyle.qss");
	if (!styleSheet.open(QIODevice::ReadOnly))
	{
		qWarning("Can't open the style sheet file.");
		return;
	}
	this->setStyleSheet(styleSheet.readAll());
	//this->resize(540, 450);
}

MainGradeAdd::~MainGradeAdd()
{
}
