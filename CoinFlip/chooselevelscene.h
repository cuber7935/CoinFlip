#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = 0);

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //维护游戏场景的指针
    PlayScene * playScene;


signals:
    //自定义信号 只需要声明，不需要实现
    void chooseSceneBack();
public slots:
};

#endif // CHOOSELEVELSCENE_H
