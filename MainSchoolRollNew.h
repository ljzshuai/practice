#ifndef MAINSCHOOLROLLNEW_H
#define MAINSCHOOLROLLNEW_H

#include <QWidget>
#include <qpushbutton.h>
#include <qlabel.h>
#include <QLineEdit>
//#include "NMysql.h"
#include <qgridlayout.h>

class MainSchoolRollNew : public QWidget
{
    Q_OBJECT
public:
     MainSchoolRollNew();

     void on_button_add();

     //NMysql * mysql;
private:
     QPushButton * m_button_add;
     QLabel*        m_label_college,*m_label_major,*m_label_msg;
     QLineEdit*     m_lineEdt_college,*m_lineEdt_major;
     QGridLayout*  m_grid;


};

#endif // MAINSCHOOLROLLNEW_H
