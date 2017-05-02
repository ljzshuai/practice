#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QStringList>
#include <QCheckBox>
#include <QPoint>


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void addd(QStringList);
    void change(int);
    void change1(int);
    void small();
    void cloose();

    void paintEvent1(QPaintEvent *event);

    QPoint move_point; //�ƶ��ľ���
     bool mouse_press; //��갴��
     //��갴���¼�
     void mousePressEvent(QMouseEvent *event);
    //����ͷ��¼�
     void mouseReleaseEvent(QMouseEvent *event);
    //����ƶ��¼�
     void mouseMoveEvent(QMouseEvent *event);

private:
    QComboBox  *combox;
    QLineEdit  *linedt;
    QCheckBox  *checkone,*checktwo;

};

#endif // WIDGET_H
