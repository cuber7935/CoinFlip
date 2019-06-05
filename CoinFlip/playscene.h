#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QLabel>
#include <QSound>
#include "mycoin.h"
#include "mypushbutton.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int index);

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //窗口初始化
    void initWindows();
    //创建音效
    void createSound();
    //创建赢的图片
    void createWinIcon();
    //显示赢的图片
    void showWinIcon();
    //显示当前关卡
    void showScreen();
    //创建金币的背景图片
    void createGround();
    //初始化金币出现的位置
    void coinPosion();
    //创建金币
    void createCoin();
    //翻周围金币
    void turnOverCoin(MyCoin* coin);

signals:
    void chooseSceneBack();
public slots:

private:
    //记录当前本关的 关卡号
    int leaveIndex ;
    //是否胜利的标志
    bool isWin;

    //退出按钮
    QAction * m_pQuit;
    //返回按钮
    MyPushButton * m_pBackBtn;
    //用来保存胜利的图片
    QLabel * m_pWin;

    //翻金币音效
    QSound *m_pFlipSound;
    //胜利按钮音效
    QSound *m_pWinSound;
    //返回按钮音效
    QSound *m_pBackSound;

    //游戏二维数组 维护里面金币或者银币标志
    int gameArray[4][4];
    //金币按钮数组
    MyCoin * coinBtn[4][4];
};

#endif // PLAYSCENE_H
