#ifndef MAINGRADENEW_H
#define MAINGRADENEW_H

#include <QWidget>
#include <qpushbutton.h>
#include <qlabel.h>
#include <QLineEdit>
//#include "NMysql.h"
#include <qgridlayout.h>
#include <QComboBox>

class MainGradeNew : QWidget
{
    Q_OBJECT
public:
    MainGradeNew();

    void on_button_add();

    //NMysql * mysql;
private:
    QPushButton *  m_button_add;
    QLabel*        m_label_term,*m_label_subject,*m_label_msg;
    QLineEdit*     m_lineEdt_subject;
    QComboBox*     m_combox_term;
    QGridLayout*   m_grid;
};

#endif // MAINGRADENEW_H
