#include "playscene.h"
#include "mypushbutton.h"
#include "dataconfig.h"
#include <QTimer>
#include <QMenuBar>
#include <QPainter>
#include <QPropertyAnimation>

PlayScene::PlayScene(int index)
{
    //保存本关 关卡号
    this->leaveIndex = index;
    //默认未胜利
    isWin = false;
    //初始化窗口
    initWindows();
    //创建音效
    createSound();
    //创建胜利的图片
    createWinIcon();
    //显示关卡
    showScreen();
    //初始化金币
    coinPosion();
    //创建金币的背景图片
    createGround();
    //创建金币
    createCoin();

    //点击退出按钮 实现退游戏
    connect(m_pQuit,&QAction::triggered,[=](){
        this->close();
    });
    //监听返回发出的信号
    connect(m_pBackBtn,&MyPushButton::clicked,[=](){
        //延时发送出返回按钮信号
        //播放返回音效
        m_pBackSound->play();
        QTimer::singleShot(500,this,[=](){
             emit this->chooseSceneBack();
        });
    });
}

void PlayScene::initWindows()
{
    //设置固定大小
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle(QString("Level: %1").arg(this->leaveIndex));
    //设置图片
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //创建菜单栏
    QMenuBar * bar = menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    //创建菜单项
    m_pQuit = startMenu->addAction("退出");

    //返回按钮
    m_pBackBtn = new MyPushButton(":/res/BackButton.png" , ":/res/BackButtonSelected.png");
    m_pBackBtn->setParent(this);
    m_pBackBtn->move( this->width() - m_pBackBtn->width() , this->height() - m_pBackBtn->height()  );
}

//创建音效
void PlayScene::createSound()
{
    //翻金币音效
    m_pFlipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利按钮音效
    m_pWinSound = new QSound(":/res/LevelWinSound.wav",this);
    //返回按钮音效
    m_pBackSound = new QSound(":/res/BackButtonSound.wav",this);
}

//创建胜利的图片
void PlayScene::createWinIcon()
{
    m_pWin= new QLabel;
    QPixmap pix(":/res/LevelCompletedDialogBg.png");
    m_pWin->setGeometry( QRect(0,0,pix.width(),pix.height()) );
    m_pWin->setParent(this);
    m_pWin->setPixmap(pix);
    m_pWin->move(  (this->width() - pix.width())/2, -pix.height() );
}

//显示赢了
void PlayScene::showWinIcon()
{
    QPropertyAnimation * animation = new QPropertyAnimation(m_pWin,"geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect( m_pWin->x(),m_pWin->y(),m_pWin->width(),m_pWin->height()));
    animation->setEndValue(QRect( m_pWin->x(),m_pWin->y()+114,m_pWin->width(),m_pWin->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

//显示当前关卡
void PlayScene::showScreen()
{
    //显示具体关卡号
    QLabel * label = new QLabel;
    label->setParent(this);
    QString str = QString("Level: %1").arg(this->leaveIndex);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(18);

    //让label使用上面创建的字体
    label->setFont(font);
    label->setText(str);
    label->setGeometry(QRect(30, this->height() - 50,130, 50)); //设置大小和位置
}

 //创建金币的背景图片
void PlayScene::createGround()
{
    for( int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4;j++)
        {
            //QLabel显示图片 金币背景
            QLabel * bg = new QLabel(this);
            QPixmap pix;
            pix.load(":/res/BoardNode.png");
            bg->setGeometry(0,0,pix.width(),pix.height());
            bg->setPixmap(pix);
            bg->move( 57 + i*50,200+j*50 );
        }
    }
}

//初始化 金币出现的位置
void PlayScene::coinPosion()
{
    dataConfig data;
    //初始化游戏中的二维数组
    for(int i = 0 ; i <4;i++)
    {
        for(int j = 0 ; j < 4;j++)
        {
            this->gameArray[i][j] =data.mData[this->leaveIndex][i][j];
        }
    }
}

//创建金币
void PlayScene::createCoin()
{
    for( int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4;j++)
        {
            QString str;
            if(this->gameArray[i][j] == 1 )
                str = ":/res/Coin0001.png";  //金币
            else
                str = ":/res/Coin0008.png";   //银币

            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);

            coin->posX = i; //记录x位置
            coin->posY = j; //记录y位置
            coin->flag = this->gameArray[i][j]; //记录硬币正反标志
            coin->move( 59 + i*50,204+j*50 );

            //将coin放入到维护的金币的二维数组中
            coinBtn[i][j] = coin;

            connect(coin,&MyCoin::clicked,[=](){
                //播放翻金币音效
                m_pFlipSound->play();

                //!!!点击后，将所有的按钮先禁用
                for(int i = 0 ; i < 4;i++)
                {
                    for(int j = 0 ; j < 4;j ++)
                    {
                        this->coinBtn[i][j]->isWin = true;
                    }
                }

                coin->changeFlag();
                //同步内部维护二维数组中的数据
                gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0;

                //延时 继续翻动 周围的硬币
                QTimer::singleShot(300,this,[=](){
                        this->turnOverCoin(coin);
                });
            });
        }
    }
}

void PlayScene::turnOverCoin(MyCoin *coin)
{
    //检测 翻右侧硬币,并且翻转
    if(coin->posX + 1 <= 3)
    {
        coinBtn[coin->posX+1][coin->posY]->changeFlag();
        gameArray[coin->posX+1][coin->posY] =  gameArray[coin->posX+1][coin->posY] == 0 ? 1 : 0;
    }
    //检测 左侧硬币
    if(coin->posX - 1 >= 0)
    {
        coinBtn[coin->posX-1][coin->posY]->changeFlag();
        gameArray[coin->posX-1][coin->posY] =  gameArray[coin->posX-1][coin->posY] == 0 ? 1 : 0;
    }
    // 检测 翻下侧硬币
    if(coin->posY + 1 <=3 )
    {
        coinBtn[coin->posX][coin->posY + 1]->changeFlag();
        gameArray[coin->posX][coin->posY + 1] =  gameArray[coin->posX][coin->posY+1] == 0 ? 1 : 0;
    }
    // 检测 翻上侧硬币
    if(coin->posY - 1 >= 0 )
    {
        coinBtn[coin->posX][coin->posY - 1]->changeFlag();
        gameArray[coin->posX][coin->posY - 1] =  gameArray[coin->posX][coin->posY-1] == 0 ? 1 : 0;
    }


    //!!!翻完所有硬币后 将所有的按钮解禁
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4;j ++)
        {
            this->coinBtn[i][j]->isWin = false;
        }
    }

    //在翻完周围硬币后，判断是否全都是金币，如果是，那么游戏胜利了
    this->isWin = true;
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4;j ++)
        {
            if(coinBtn[i][j]->flag == false)
            {
                this->isWin = false;
                break;
            }
        }
    }
    if(this->isWin == true)
    {
        //播放胜利音效
        m_pWinSound->play();

        //将所有硬币的胜利标志 都设置为true
        for(int i = 0 ;i < 4;i++)
        {
            for(int j =  0  ; j < 4;j++)
            {
                coinBtn[i][j]->isWin = true;
            }
        }
        //将胜利的图片 显示出来
        showWinIcon();
    }
}

//重写绘图事件
void PlayScene::paintEvent(QPaintEvent *)
{
    //绘制背景图片
    QPainter painter (this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //绘制标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()/2, pix.height()/2 );
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
