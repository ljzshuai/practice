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

class MainSys:public QWidget
{
public:
	MainSys();
	~MainSys();

private:
	QPushButton* m_AddUser, *m_AlterPwd, *m_ReLand;
	
};

MainSys::MainSys()
{
	m_AddUser   = new QPushButton(QString::fromLocal8Bit("添加用户"),this);
	m_AlterPwd = new QPushButton(QString::fromLocal8Bit("修改密码"),this);
	m_ReLand = new QPushButton(QString::fromLocal8Bit("重新登陆"),this);

	this->setFixedHeight(370);
	this->setFixedWidth(180);

	QVBoxLayout *VLay = new QVBoxLayout(this);
	VLay->addWidget(m_AddUser);
	VLay->addWidget(m_AlterPwd);
	VLay->addWidget(m_ReLand);

	m_AddUser->setFixedHeight(80);
	m_AlterPwd->setFixedHeight(80);
	m_ReLand->setFixedHeight(80);

	QFile styleSheet(":/new/prefix1/qt_practicemyStyle.qss");
	if (!styleSheet.open(QIODevice::ReadOnly))
	{
		qWarning("Can't open the style sheet file.");
		return;
	}
	this->setStyleSheet(styleSheet.readAll());

}

MainSys::~MainSys()
{
}