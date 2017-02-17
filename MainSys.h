#include <qobject.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qwidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
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
	m_AddUser   = new QPushButton("����û�",this);
	m_AlterPwd = new QPushButton("�޸�����",this);
	m_ReLand = new QPushButton("���µ�½",this);

	this->setFixedHeight(370);
	this->setFixedWidth(180);

	QVBoxLayout *VLay = new QVBoxLayout(this);
	VLay->addWidget(m_AddUser);
	VLay->addWidget(m_AlterPwd);
	VLay->addWidget(m_ReLand);

	m_AddUser->setFixedHeight(80);
	m_AlterPwd->setFixedHeight(80);
	m_ReLand->setFixedHeight(80);


}

MainSys::~MainSys()
{
}