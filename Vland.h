#pragma once
#include <qobject.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qwidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
class Vland :public QWidget
{
public:
	Vland();
	~Vland();

private:
	QPushButton * m_button_land;
	QLabel *	  m_label_user, *m_label_pwd, *m_label_msg;
	QLineEdit*	  m_LEdit_user, *m_LEdit_pwd;
};

Vland::Vland()
{
	this->setFixedSize(200,150);
	m_button_land = new QPushButton(QString::fromLocal8Bit("µÇÂ½"), this);
	m_label_user = new QLabel(QString::fromLocal8Bit("ÐÕÃû "), this);
	m_label_pwd = new QLabel(QString::fromLocal8Bit("ÃÜÂë "), this);
	m_label_msg = new QLabel(this);
	m_LEdit_pwd = new QLineEdit(this);
	m_LEdit_user = new QLineEdit(this);

	m_LEdit_pwd->setEchoMode(QLineEdit::Password);

	QHBoxLayout * Hlay_user = new QHBoxLayout();
	QHBoxLayout * Hlay_pwd = new QHBoxLayout();
	QVBoxLayout*  Vlay = new QVBoxLayout(this);

	Hlay_user->addWidget(m_label_user);
	Hlay_user->addWidget(m_LEdit_user);
	Hlay_pwd->addWidget(m_label_pwd);
	Hlay_pwd->addWidget(m_LEdit_pwd);

	Vlay->addWidget(new QLabel());
	Vlay->addLayout(Hlay_user);
	Vlay->addLayout(Hlay_pwd);
	Vlay->addWidget(m_button_land);
	Vlay->addWidget(m_label_msg);

	QFile styleSheet(":/new/prefix1/qt_practicemyStyle.qss");
	if (!styleSheet.open(QIODevice::ReadOnly))
	{
		qWarning("Can't open the style sheet file.");
		return;
	}
	this->setStyleSheet(styleSheet.readAll());
}

Vland::~Vland()
{
}
//QString("µÇÂ½").toUtf8().data()