#pragma once
#include <mysql.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qwidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QDate>
#include <QDateEdit>

class MainClass :public QWidget
{
public:
	MainClass();
	~MainClass();

private:
	QPushButton* m_AddClass, *m_AlterClass;
	QLabel * label;
	QLineEdit * line;
	QHBoxLayout *hbo;
	QVBoxLayout *vbo1, *vbo2;
	MYSQL  pCmysql;

	void writ(bool);
	void red(bool);
};

MainClass::MainClass()
{
	hbo = new QHBoxLayout(this);
	vbo1 = new QVBoxLayout();
	vbo2 = new QVBoxLayout();
	m_AddClass = new QPushButton(this);
	m_AlterClass = new QPushButton(this);
	line = new QLineEdit(this);
	label = new QLabel(this);

	vbo1->addWidget(m_AddClass);
	vbo1->addWidget(line);
	vbo2->addWidget(m_AlterClass);
	vbo2->addWidget(label);

	hbo->addLayout(vbo1);
	hbo->addLayout(vbo2);

	QObject::connect(m_AlterClass, &QPushButton::clicked, [=](){

		char buf[1024];
		sprintf(buf, "select * from test where age =16");
		if (mysql_query(&pCmysql, buf) != 0)
		{
			int a1;
			a1++;
		}
		MYSQL_ROW  rel_row;
		MYSQL_RES * result1;
		MYSQL_FIELD * result2;

		result1 = mysql_store_result(&pCmysql);
		if (!result1)
		{
			int a;
			int b;
		}
		while ((rel_row = mysql_fetch_row(result1)) != NULL)
		{


			//label->setText(QString::fromLocal8Bit("°¢µÀ·ò"));
			label->setText(QString::fromUtf8(rel_row[0]));
		}

	});

	QObject::connect(m_AddClass, &QPushButton::clicked, [=](){
		char buf[1024];
		sprintf(buf, "insert into test values(\"%s\",16)", line->text().toUtf8().data());

		if (mysql_query(&pCmysql, buf) != 0)
		{
			const char * dd = mysql_error(&pCmysql);
			int a;
			a++;
			dd;
		}

	});


	mysql_init(&pCmysql);
	mysql_real_connect(&pCmysql, "127.0.0.1",
		"dbuser1", "dbuser1",
		"db1", 0, 0, 0);
	mysql_query(&pCmysql, "set names utf8");
}

MainClass::~MainClass()
{
}
void MainClass::writ(bool t)
{
	char buf[1024];
	sprintf("insert into testauto values(1, 10, \"%s\")", line->text().toLatin1().data());
	if (mysql_query(&pCmysql, QString(buf).toUtf8().data()) != 0)
	{
		int a1;
		a1++;
	}
}
void MainClass::red(bool r)
{
	MYSQL_ROW  rel_row;
	MYSQL_RES * result1;
	MYSQL_FIELD * result2;
}