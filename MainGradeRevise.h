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
class MainGradeRevise : public QWidget
{
public:
	MainGradeRevise();
	~MainGradeRevise();

private:
	QPLabel 		m_label_ID, m_label_msg_query,m_label_term,
					m_label_subject,m_label_grade,m_label_Rgrade,m_label_msg_revise;
	QPLineEdit 		m_LineEdt_ID,m_LineEdt_grade,m_LineEdt_Rgrade;
	QPushButton *	m_button_query,*m_button_revise;
	QComboBox*		m_combox_term,*m_combox_subject;
	QGridLayout*    m_gboxlay;
};

MainGradeRevise::MainGradeRevise()
{
	m_label_ID			= new QLabel(QString::fromLocal8Bit("      学号"), this);
	m_label_term		= new QLabel(QString::fromLocal8Bit("      学期"), this);
	m_label_subject		= new QLabel(QString::fromLocal8Bit("      科目"), this);
	m_label_grade		= new QLabel(QString::fromLocal8Bit("      成绩"), this);
	m_label_Rgrade		= new QLabel(QString::fromLocal8Bit("      补考成绩"), this);
	m_label_msg_query	= new QLabel(this);
	m_label_msg_revise  = new QLabel(this);

	m_LineEdt_ID		= new QLineEdit(this);
	m_LineEdt_grade		= new QLineEdit(this);
	m_LineEdt_Rgrade	= new QLineEdit(this);

	m_gboxlay			= new QGridLayout(this);

	m_button_query		= new QPushButton(QString::fromLocal8Bit("查询"), this);
	m_button_revise		= new QPushButton(QString::fromLocal8Bit("修改"), this);

	m_combox_subject	= new QComboBox(this);
	m_combox_term		= new QComboBox(this);

	m_gboxlay->addWidget(m_label_ID, 0, 0, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_ID, 0, 1, 1, 2);
	m_gboxlay->addWidget(m_button_query, 0, 4, 1, 2);
	m_gboxlay->addWidget(m_label_msg_query, 0, 3, 1, 1);
	m_gboxlay->addWidget(m_label_term, 1, 0, 1, 1);
	m_gboxlay->addWidget(m_combox_term, 1, 1, 1, 2);
	m_gboxlay->addWidget(m_label_subject, 2, 0, 1, 1);
	m_gboxlay->addWidget(m_combox_subject, 2, 1, 1, 2);
	m_gboxlay->addWidget(m_label_grade, 3, 0, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_grade,3, 1, 1, 1);
	m_gboxlay->addWidget(m_label_Rgrade, 3, 2, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_Rgrade, 3, 3, 1, 1);
	m_gboxlay->addWidget(new QLabel(this), 3, 4, 1, 2);
	m_gboxlay->addWidget(m_button_revise, 4, 1, 1, 1);
	m_gboxlay->addWidget(m_label_msg_revise, 4, 2, 1, 1);

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

MainGradeRevise::~MainGradeRevise()
{
}