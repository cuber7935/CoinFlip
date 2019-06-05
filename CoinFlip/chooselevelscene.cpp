#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <mypushbutton.h>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //设置固定大小
    this->setFixedSize(320,588);

    //设置标题
    this->setWindowTitle("选择关卡场景");

    //设置图片
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //创建菜单栏
    QMenuBar * bar = menuBar();
    this->setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    //创建菜单项
    QAction * quitAction = startMenu->addAction("退出");

    //点击退出按钮 实现退游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //选择关卡按钮音效
    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);

    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);


    //返回按钮创建
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png" , ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move( this->width() - backBtn->width() , this->height() - backBtn->height()  );

    connect(backBtn,&MyPushButton::clicked,[=](){
       //qDebug() << "返回到主场景";
        //隐藏自身
        //延时发送出返回按钮信号
        //播放返回按钮音效
        backSound->play();

        QTimer::singleShot(500,this,[=](){
             emit this->chooseSceneBack();
        });
    });


    playScene = NULL;



    //选择关卡按钮
    for(int i = 0 ; i< 20;i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move( 25 + (i%4)*70 ,130+(i/4)*70 );

        connect(menuBtn,&MyPushButton::clicked,[=](){
//            QString str = QString("您选择的是 %1 关").arg(i+1);
//            qDebug() <<str;

            //播放点击选择关卡按钮音效
            chooseSound->play();

            //隐藏自身
            this->hide();

            //进入到具体游戏场景
            playScene = new PlayScene(i+1);

            //将游戏场景的位置 同步为 选择关卡场景的位置
            playScene->setGeometry( this->geometry() );

            playScene->show();

            connect(playScene,&PlayScene::chooseSceneBack,[=](){
                //具体翻金币游戏场景 隐藏掉

                //设置选择关卡场景位置  为 游戏场景返回时候的位置
                this->setGeometry(playScene->geometry());

                playScene->close();
                delete playScene;
                playScene = NULL;

                //选择关卡场景 显示
                this->show();
            });

        });

        QLabel  * label = new QLabel(this);
        //设置标签大小
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        //设置显示内容
        label->setText( QString::number(i+1));
        label->move( 25 + (i%4)*70 ,130+(i/4)*70 );
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置鼠标穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents); // 51鼠标穿透属性
    }
}


//重写绘图事件
void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

     //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap( (this->width() - pix.width())/2, 30, pix.width(), pix.height(),pix);
}
