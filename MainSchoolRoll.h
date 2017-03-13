#pragma once
#include <qobject.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qwidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "MainSchoolRollAdd.h"
#include "MainSchoolRollQuery.h"
#include "MainSchoolRollRevise.h"
class MainSchoolRoll:public QWidget
{
	//Q_OBJECT
public:
	MainSchoolRoll();
	~MainSchoolRoll();

	void on_button_AddSchoolRoll();
	void on_button_AlterSchoolRoll();
	void on_button_QuerySchoolRoll();

private:
	QPushButton* m_button_AddSchoolRoll, *m_button_AlterSchoolRoll, *m_button_QuerySchoolRoll;
	
};

MainSchoolRoll::MainSchoolRoll()
{
	m_button_AddSchoolRoll   = new QPushButton(QString::fromLocal8Bit("添加学籍"), this);
	m_button_AlterSchoolRoll = new QPushButton(QString::fromLocal8Bit("修改学籍"), this);
	m_button_QuerySchoolRoll = new QPushButton(QString::fromLocal8Bit("查询学籍"), this);

	this->setFixedHeight(370);
	this->setFixedWidth(180);

	QVBoxLayout *VLay = new QVBoxLayout(this);
	VLay->addWidget(m_button_AddSchoolRoll);
	VLay->addWidget(m_button_AlterSchoolRoll);
	VLay->addWidget(m_button_QuerySchoolRoll);

	m_button_AddSchoolRoll->setFixedHeight(80);
	m_button_AlterSchoolRoll->setFixedHeight(80);
	m_button_QuerySchoolRoll->setFixedHeight(80);
	

	QFile styleSheet(":/new/prefix1/qt_practicemyStyle.qss");
	if (!styleSheet.open(QIODevice::ReadOnly))
	{
		qWarning("Can't open the style sheet file.");
		return;
	}
	this->setStyleSheet(styleSheet.readAll());

	QObject::connect(m_button_AddSchoolRoll, &QPushButton::clicked, this, &MainSchoolRoll::on_button_AddSchoolRoll);
	QObject::connect(m_button_AlterSchoolRoll, &QPushButton::clicked, this, &MainSchoolRoll::on_button_AlterSchoolRoll);
	QObject::connect(m_button_QuerySchoolRoll, &QPushButton::clicked, this, &MainSchoolRoll::on_button_QuerySchoolRoll);

	//this->setWindowFlags(Qt::FramelessWindowHint);
}

void MainSchoolRoll::on_button_AddSchoolRoll()
{
	MainSchoolRollAdd * tmp = new MainSchoolRollAdd();
	tmp->show();
}

void MainSchoolRoll::on_button_AlterSchoolRoll()
{
	MainSchoolRollRevise * tmp = new MainSchoolRollRevise();
	tmp->show();
}

void MainSchoolRoll::on_button_QuerySchoolRoll()
{
	MainSchoolRollQuery * tmp = new MainSchoolRollQuery();
	tmp->show();
}

MainSchoolRoll::~MainSchoolRoll()
{

}