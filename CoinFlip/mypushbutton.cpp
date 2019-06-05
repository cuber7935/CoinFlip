#include "mypushbutton.h"
#include <QPropertyAnimation>
MyPushButton::MyPushButton( QString normalImg,QString pressImg)
{
    //保存住 正常显示路径 和 选中后显示的路径
    this->normalImgPath = normalImg;
    this->pressedImgPath = pressImg;

    QPixmap pix;
    if(! pix.load( this->normalImgPath ) )
    {
        QString str = QString("%1 图片加载失败").arg( this->normalImgPath);
        qDebug () <<  str;
        return;
    }

    //设定图片大小
    this->setFixedSize(pix.width(),pix.height());

    //设置不规则图片样式
    this->setStyleSheet( "QPushButton{border:0px;}" );

    //设置图片
    this->setIcon(pix);

    //设置图片大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}


//向下跳跃
void MyPushButton::Zoom1()
{
    QPropertyAnimation * animation  = new QPropertyAnimation (this,"geometry");

    //设定时间间隔
    animation->setDuration(200);
    //设置动画对象起始位置
    animation->setStartValue(QRect( this->x(),this->y(),this->width(),this->height() ));
    //设置动画对象结束位置
    animation->setEndValue(QRect( this->x(),this->y() + 10,this->width(),this->height() ) );
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();

}
//向上跳跃
void MyPushButton::Zoom2()
{
    QPropertyAnimation * animation  = new QPropertyAnimation (this,"geometry");

    //设定时间间隔
    animation->setDuration(200);
    //设置动画对象起始位置
    animation->setStartValue(QRect( this->x(),this->y()+10,this->width(),this->height() ));
    //设置动画对象结束位置
    animation->setEndValue(QRect( this->x(),this->y(),this->width(),this->height() ) );
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();

}

//鼠标按下事件
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressedImgPath != "") //传入选中后的图片路径不为空，需要选中后来进行图片的切换
    {
        QPixmap pix;
        if( ! pix.load(this->pressedImgPath) )
        {
            qDebug() << "图片加载失败" ;
            return;
        }

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet( "QPushButton{border:0px;}" );
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //其他事情 交给父类处理
    QPushButton::mousePressEvent(e);

}
//鼠标释放事件
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressedImgPath != "") //传入选中后的图片路径不为空，需要选中后来进行图片的切换
    {
        QPixmap pix;
        if( ! pix.load(this->normalImgPath) )
        {
            qDebug() << "图片加载失败" ;
            return;
        }

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet( "QPushButton{border:0px;}" );
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //其他事情 交给父类处理
    QPushButton::mouseReleaseEvent(e);
}


