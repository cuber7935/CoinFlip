#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "chooselevelscene.h"
namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();

    //绘图事件
    void paintEvent(QPaintEvent *);

    ChooseLevelScene * chooseScene;

private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
