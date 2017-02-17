#include <qobject.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qwidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
class MainClass:public QWidget
{
public:
	MainClass();
	~MainClass();

private:
	QPushButton* m_AddClass, *m_AlterClass;
	
};

MainClass::MainClass()
{
	m_AddClass   = new QPushButton("添加班级",this);
	m_AlterClass  = new QPushButton("修改班级信息",this);

	this->setFixedHeight(370);
	this->setFixedWidth(180);

	QVBoxLayout *VLay = new QVBoxLayout(this);
	VLay->addWidget(m_AddClass);
	VLay->addWidget(m_AlterClass);

	m_AddClass->setFixedHeight(80);
	m_AlterClass->setFixedHeight(80);


}

MainClass::~MainClass()
{
}