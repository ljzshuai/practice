#include <qobject.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qwidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
class MainGrade:public QWidget
{
public:
	MainGrade();
	~MainGrade();

private:
	QPushButton* m_AddGrade, *m_AlterGrade, *m_QueryGrade;
	
};

MainGrade::MainGrade()
{
	m_AddGrade   = new QPushButton("��ӳɼ�",this);
	m_AlterGrade = new QPushButton("�޸ĳɼ�",this);
	m_QueryGrade = new QPushButton("��ѯ�ɼ�",this);

	this->setFixedHeight(370);
	this->setFixedWidth(180);

	QVBoxLayout *VLay = new QVBoxLayout(this);
	VLay->addWidget(m_AddGrade);
	VLay->addWidget(m_AlterGrade);
	VLay->addWidget(m_QueryGrade);

	m_AddGrade->setFixedHeight(80);
	m_AlterGrade->setFixedHeight(80);
	m_QueryGrade->setFixedHeight(80);
}

MainGrade::~MainGrade()
{
}