#pragma once
#include <qobject.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qwidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qfile.h>
#include <qobject.h>
#include <MainSysAdd.h>
#include <MainSysRevise.h>

class MainSys:public QWidget
{
public:
	MainSys();
	~MainSys();

	void on_button_AddUser();
	void on_button_AlterPwd();
	void on_button_ReLand();

private:
	QPushButton* m_button_AddUser, *m_button_AlterPwd, *m_button_ReLand;
	
};

MainSys::MainSys()
{
	m_button_AddUser = new QPushButton(QString::fromLocal8Bit("添加用户"), this);
	m_button_AlterPwd = new QPushButton(QString::fromLocal8Bit("修改密码"), this);
	m_button_ReLand = new QPushButton(QString::fromLocal8Bit("重新登陆"), this);

	this->setFixedHeight(370);
	this->setFixedWidth(180);

	QVBoxLayout *VLay = new QVBoxLayout(this);
	VLay->addWidget(m_button_AddUser);
	VLay->addWidget(m_button_AlterPwd);
	VLay->addWidget(m_button_ReLand);

	m_button_AddUser->setFixedHeight(80);
	m_button_AlterPwd->setFixedHeight(80);
	m_button_ReLand->setFixedHeight(80);

	QFile styleSheet(":/new/prefix1/qt_practicemyStyle.qss");
	if (!styleSheet.open(QIODevice::ReadOnly))
	{
		qWarning("Can't open the style sheet file.");
		return;
	}
	this->setStyleSheet(styleSheet.readAll());

	 QObject::connect(m_button_AddUser, &QPushButton::clicked,this,&MainSys::on_button_AddUser);
	 QObject::connect(m_button_AlterPwd, &QPushButton::clicked, this, &MainSys::on_button_AlterPwd);

}

void MainSys::on_button_ReLand()
{
	
}

void MainSys::on_button_AddUser()
{
	MainSysAdd * tmp = new MainSysAdd();
	tmp->show();
}

void MainSys::on_button_AlterPwd()
{
	MainSysRevise * tmp = new MainSysRevise();
	tmp->show();
}

MainSys::~MainSys()
{
}