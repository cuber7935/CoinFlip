#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QDebug>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = 0);

    MyPushButton( QString normalImg,QString pressImg = "" );

    QString normalImgPath;  //默认显示图片路径
    QString pressedImgPath; //按下后显示图片路径

    //向下跳跃
    void Zoom1();
    //向上跳跃
    void Zoom2();

    //鼠标按下事件
    void mousePressEvent(QMouseEvent *e);
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
