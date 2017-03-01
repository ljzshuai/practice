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
#include <QGridLayout>
#include <qfile.h>

class MainGradeQuery : public QWidget
{
public:
	MainGradeQuery();
	~MainGradeQuery();

private:
	QLabel *		m_label_ID,*m_label_msg;
	QLineEdit *		m_LineEdt_ID;
	QPushButton *	m_button_query;
	QTableWidget *  m_TableWidget;
	QHBoxLayout*    m_hboxlay;
	QGridLayout*    m_gboxlay;
};

MainGradeQuery::MainGradeQuery()
{

	m_TableWidget = new QTableWidget(this);
	m_TableWidget->setFrameShape(QFrame::NoFrame);//û����߿�
	m_TableWidget->setColumnCount(5); //��������
	m_TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//���ɸ��ı������
	m_TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//����ѡ��
	
	QStringList header;
	header << QString::fromLocal8Bit("����") << QString::fromLocal8Bit("ѧ��")
		<< QString::fromLocal8Bit("��Ŀ") << QString::fromLocal8Bit("�ɼ�")
		<< QString::fromLocal8Bit("�����ɼ�");
	m_TableWidget->setHorizontalHeaderLabels(header);	//���ñ�ͷ


	m_label_ID =	 new QLabel(QString::fromLocal8Bit("ѧ��"),this);
	m_button_query = new QPushButton(QString::fromLocal8Bit("��ѯ"), this);
	m_label_msg =	 new QLabel(this);
	m_LineEdt_ID =	 new QLineEdit(this);
	m_hboxlay =		 new QHBoxLayout();
	m_gboxlay =		 new QGridLayout(this);

	m_hboxlay->addWidget(m_label_ID);
	m_hboxlay->addWidget(m_LineEdt_ID);
	m_hboxlay->addWidget(m_button_query);
	m_hboxlay->addWidget(m_label_msg);

	m_gboxlay->addLayout(m_hboxlay, 0, 0, 1, 4);
	m_gboxlay->addWidget(m_TableWidget, 1, 0, 10, 10);


	QFile styleSheet(":/new/prefix1/qt_practicemyStyle.qss");
	if (!styleSheet.open(QIODevice::ReadOnly))
	{
		qWarning("Can't open the style sheet file.");
		return;
	}
	this->setStyleSheet(styleSheet.readAll());
	this->resize(540, 450);
}

MainGradeQuery::~MainGradeQuery()
{
}