﻿#pragma once
#include <qobject.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qwidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qfile.h>
class VMAIN: public QWidget
{
public:
	VMAIN();
	~VMAIN();

private:
	QPushButton *m_button_class, *m_button_sys, *m_button_SchollRoll;
	QPushButton *m_button_course, *m_button_grade;
};

VMAIN::VMAIN()
{
	m_button_sys		= new QPushButton(QString::fromLocal8Bit("系统管理"),this);
	m_button_SchollRoll = new QPushButton(QString::fromLocal8Bit("学籍管理"),this);
	m_button_grade		= new QPushButton(QString::fromLocal8Bit("成绩管理"),this);

	this->setFixedHeight(370);
	this->setFixedWidth(180);

	m_button_sys->setFixedHeight(60);
	m_button_SchollRoll->setFixedHeight(60);
	m_button_grade->setFixedHeight(60);

	QVBoxLayout *VLay = new QVBoxLayout(this);
	VLay->addWidget(m_button_grade);
	VLay->addWidget(m_button_SchollRoll);
	VLay->addWidget(m_button_sys);

	QFile styleSheet(":/new/prefix1/qt_practicemyStyle.qss");
	if (!styleSheet.open(QIODevice::ReadOnly))
	{
		qWarning("Can't open the style sheet file.");
		return;
	}
	this->setStyleSheet(styleSheet.readAll());
}

VMAIN::~VMAIN()
{
}