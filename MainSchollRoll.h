#include <qobject.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qwidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
class MainSchoolRoll:public QWidget
{
public:
	MainSchoolRoll();
	~MainSchoolRoll();

private:
	QPushButton* m_AddSchoolRoll, *m_AlterSchoolRoll, *m_QuerySchoolRoll;
	
};

MainSchoolRoll::MainSchoolRoll()
{
	m_AddSchoolRoll   = new QPushButton("���ѧ��",this);
	m_AlterSchoolRoll = new QPushButton("�޸�ѧ��",this);
	m_QuerySchoolRoll = new QPushButton("��ѯѧ��",this);

	this->setFixedHeight(370);
	this->setFixedWidth(180);

	QVBoxLayout *VLay = new QVBoxLayout(this);
	VLay->addWidget(m_AddSchoolRoll);
	VLay->addWidget(m_AlterSchoolRoll);
	VLay->addWidget(m_QuerySchoolRoll);

	m_AddSchoolRoll->setFixedHeight(80);
	m_AlterSchoolRoll->setFixedHeight(80);
	m_QuerySchoolRoll->setFixedHeight(80);


}

MainSchoolRoll::~MainSchoolRoll()
{
}