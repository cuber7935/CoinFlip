#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //点击开始 - 退出 退出游戏
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });

    //设置固定大小
    this->setFixedSize(320,588);

    //设置标题
    this->setWindowTitle("翻金币游戏");

    //设置图片
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //开始按钮创建
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()/2 - startBtn->width()/2 , this->height()*3/4);

    //准备开始按钮 音效
    QSound * startSound = new QSound(":/res/TapButtonSound.wav",this);

    //startSound->setLoops(-1); 设置循环次数，如果是-1 代表无限循环

    //创建出 第二个选择关卡场景
    chooseScene = new ChooseLevelScene;

    //监听第二个选择关卡场景中的返回按钮的信号
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
        //选择关卡场景隐藏
        chooseScene->hide();

        //自身的位置同步为 选择关卡场景的位置
        this->setGeometry( chooseScene->geometry() );

        //自身显示
        this->show();
    });

    connect(startBtn,&MyPushButton::clicked,[=](){
        //qDebug() << "点击了开始按钮";
        //播放开始音效
        startSound->play();

        //点击开始按钮 执行弹跳效果
        startBtn->Zoom1();
        startBtn->Zoom2();

        //延时 进入到第二个场景
        QTimer::singleShot(500,this,[=](){
            //将自身隐藏调用
            this->hide();

            //设置选中关卡场景的位置
            chooseScene->setGeometry( this->geometry());

            //进入到第二个 选择关卡场景中
            chooseScene->show();
        });
    });
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter (this);

    //画背景图片
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画标题图片
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()/2,pix.height()/2);
    painter.drawPixmap(10,30,pix);
}

MainScene::~MainScene()
{
    delete ui;
}
