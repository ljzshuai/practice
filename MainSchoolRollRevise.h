#pragma once
#include <qlineedit.h>
#include <qstring.h>
#include <qwidget.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qtablewidget.h>
#include <QTableWidgetItem>
#include <QHeaderView>
//#include <vector>
#include <QGridLayout>
#include <QComboBox>
#include <qfile.h>
#include <QDate>
#include <QDateEdit>

using QPLabel = QLabel *;
using QPLineEdit = QLineEdit *;
using QPComboBox = QComboBox *;
class MainSchoolRollRevise : public QWidget
{
public:
	MainSchoolRollRevise();
	~MainSchoolRollRevise();

    void on_button_query();
    void on_button_revise();

private:
	QPLabel 		m_label_ID, m_label_college, m_label_name,m_label_msg_revise,
		            m_label_major, m_label_sex, m_label_year, m_label_msg_ch,
		            m_label_edu, m_label_xz, m_label_perID, m_label_birth;

    QPLineEdit 		m_LineEdt_ID, m_LineEdt_perID, m_LineEdt_year, m_LineEdt_name,
                    m_LineEdt_college, m_LineEdt_major, m_LineEdt_edu, m_LineEdt_xz, m_LineEdt_sex;
	QPushButton *	m_button_query,*m_button_revise;
	QGridLayout*    m_gboxlay;
	QDate *			m_date;
	QDateEdit*		m_dateEdit;
};

MainSchoolRollRevise::MainSchoolRollRevise()
{
	m_date = new QDate(1990, 1, 1);
	m_dateEdit = new QDateEdit(this);
	m_dateEdit->setDate(*m_date);

	m_label_ID      = new QLabel(QString::fromLocal8Bit("      学号"), this);
	m_label_name    = new QLabel(QString::fromLocal8Bit("      姓名"), this);
	m_label_college = new QLabel(QString::fromLocal8Bit("      学院"), this);//
	m_label_major   = new QLabel(QString::fromLocal8Bit("      专业"), this);//
	m_label_sex     = new QLabel(QString::fromLocal8Bit("      性别"), this);//
	m_label_year    = new QLabel(QString::fromLocal8Bit("      入学年份"), this);
	m_label_edu     = new QLabel(QString::fromLocal8Bit("      学历"), this);//
	m_label_xz      = new QLabel(QString::fromLocal8Bit("      学制"), this);//
	m_label_perID   = new QLabel(QString::fromLocal8Bit("      身份证"), this);
	m_label_birth   = new QLabel(QString::fromLocal8Bit("      生日"));//
	m_label_msg_revise = new QLabel(this);
    m_label_msg_ch     = new QLabel(this);

    m_LineEdt_ID      = new QLineEdit(this);
    m_LineEdt_name    = new QLineEdit(this);
    m_LineEdt_perID   = new QLineEdit(this);
    m_LineEdt_year    = new QLineEdit(this);
    m_LineEdt_xz      = new QLineEdit(this);//学制
    m_LineEdt_edu     = new QLineEdit(this);//学历
    m_LineEdt_major   = new QLineEdit(this);//专业
    m_LineEdt_college = new QLineEdit(this);//学院
    m_LineEdt_sex     = new QLineEdit(this);

	m_gboxlay = new QGridLayout(this);

	m_button_query  = new QPushButton(QString::fromLocal8Bit("查询"), this);
	m_button_revise = new QPushButton(QString::fromLocal8Bit("修改"), this);


	m_gboxlay->addWidget(m_label_ID, 0, 0, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_ID, 0, 1, 1, 1);
	m_gboxlay->addWidget(m_button_query, 0, 2, 1, 1);
	m_gboxlay->addWidget(m_label_msg_revise, 0, 3, 1, 2);

	m_gboxlay->addWidget(m_label_name, 1, 0, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_name, 1, 1, 1, 1);

	m_gboxlay->addWidget(m_label_college, 2, 0, 1, 1);
    m_gboxlay->addWidget(m_LineEdt_college, 2, 1, 1, 2);

	m_gboxlay->addWidget(m_label_major, 3, 0, 1, 1);
    m_gboxlay->addWidget(m_LineEdt_major, 3, 1, 1, 2);

	m_gboxlay->addWidget(m_label_xz, 4, 0, 1, 1);
    m_gboxlay->addWidget(m_LineEdt_xz, 4, 1, 1, 2);

	m_gboxlay->addWidget(m_label_edu, 5, 0, 1, 1);
    m_gboxlay->addWidget(m_LineEdt_edu, 5, 1, 1, 2);

	m_gboxlay->addWidget(m_label_year, 6, 0, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_year, 6, 1, 1, 1);
	m_gboxlay->addWidget(m_label_sex, 6, 2, 1, 1);
    m_gboxlay->addWidget(m_LineEdt_sex, 6, 3, 1, 1);

	m_gboxlay->addWidget(m_label_birth, 7, 0, 1, 1);
	m_gboxlay->addWidget(m_dateEdit, 7, 1, 1, 1);
	m_gboxlay->addWidget(m_label_perID, 7, 2, 1, 1);
	m_gboxlay->addWidget(m_LineEdt_perID, 7, 3, 1, 1);

	m_gboxlay->addWidget(m_button_revise, 8, 1, 1, 1);
	m_gboxlay->addWidget(m_label_msg_ch, 8, 2, 1, 1);

	QFile styleSheet(":/new/prefix1/qt_practicemyStyle.qss");
	if (!styleSheet.open(QIODevice::ReadOnly))
	{
		qWarning("Can't open the style sheet file.");
		return;
	}
	this->setStyleSheet(styleSheet.readAll());

	this->resize(540, 350);

	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowModality(Qt::ApplicationModal);
}
void MainSchoolRollRevise::on_button_revise()
{
    QString query1 = QString("update schoolroll set ID = '%1',name = '%2',college = '%3'"
                                                         ",major = '%4',sex = '%5',year = '%6',edu = '%7'"
                                                         ",xz = '%8',perID = '%9',birth = '%10'")
            .arg(m_LineEdt_ID->text())
            .arg(m_LineEdt_name->text())
            .arg(m_LineEdt_college->text())
            .arg(m_LineEdt_major->->text())
            .arg(m_LineEdt_sex->->text())
            .arg(m_LineEdt_year->text())
            .arg(m_LineEdt_edu->text())
            .arg(m_LineEdt_xz->text())
            .arg(m_LineEdt_perID->text())
            .arg(m_dateEdit->date().toString(Qt::ISODate));
       //
}

void MainSchoolRollRevise::on_button_query()
{
    QString query1 = QString("select * from schoolroll where ID = '%1").arg(m_LineEdt_ID);
    char tmp[1024];
   // std::vector<QString> tmp =
    m_LineEdt_ID->setText(tmp[0]);
    m_LineEdt_name->setText(tmp[1]);
    m_LineEdt_college->setText(tmp[2]);
    m_LineEdt_major->setText(tmp[3]);
    m_LineEdt_sex->setText(tmp[4]);
    m_LineEdt_year->setText(tmp[5]);
    m_LineEdt_edu->setText(tmp[6]);
    m_LineEdt_xz->setText(tmp[7]);
    m_LineEdt_perID->setText(tmp[8]);
    *m_date = QDate::fromString(tmp[9],"yyyy-MM-dd");
    m_dateEdit->setDate(m_date);




}


MainSchoolRollRevise::~MainSchoolRollRevise()
{
}
