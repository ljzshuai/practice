#pragma once
#include <qobject.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qwidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qfile.h>
#include <qgridlayout.h>
class MainSysRevise :public QWidget
{
public:
	MainSysRevise();
	~MainSysRevise();

private:
	QPushButton*  m_button_add;
	QLineEdit *   m_lineEdt_pwd, *m_lineEdt_Rpwd;
	QLabel*       m_label_pwd,   *m_label_Rpwd, *m_label_msg;
	QGridLayout * m_gboxlay;
};

MainSysRevise::MainSysRevise()
{
	m_button_add = new QPushButton(QString::fromLocal8Bit("ÐÞ¸ÄÃÜÂë"), this);

	m_label_pwd = new QLabel(QString::fromLocal8Bit(" ÐÂÃÜÂë"), this);
	m_label_Rpwd = new QLabel(QString::fromLocal8Bit(" È·ÈÏÃÜÂë"), this);
	m_label_msg = new QLabel(this);


	m_lineEdt_pwd = new QLineEdit(this);
	m_lineEdt_Rpwd = new QLineEdit(this);

	m_gboxlay = new QGridLayout(this);

	m_lineEdt_pwd->setEchoMode(QLineEdit::Password);
	m_lineEdt_Rpwd->setEchoMode(QLineEdit::Password);


	m_gboxlay->addWidget(m_label_pwd, 1, 0, 1, 1);
	m_gboxlay->addWidget(m_lineEdt_pwd, 1, 1, 1, 1);
	m_gboxlay->addWidget(m_label_Rpwd, 2, 0, 1, 1);
	m_gboxlay->addWidget(m_lineEdt_Rpwd, 2, 1, 1, 1);
	m_gboxlay->addWidget(m_button_add, 3, 0, 1, 1);
	m_gboxlay->addWidget(m_label_msg, 3, 1, 1, 1);

	QFile styleSheet(":/new/prefix1/qt_practicemyStyle.qss");
	if (!styleSheet.open(QIODevice::ReadOnly))
	{
		qWarning("Can't open the style sheet file.");
		return;
	}
	this->setStyleSheet(styleSheet.readAll());

	this->setWindowModality(Qt::ApplicationModal);
	this->setAttribute(Qt::WA_DeleteOnClose);

}

MainSysRevise::~MainSysRevise()
{
}