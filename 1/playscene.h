#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mycoin.h"
class Playscene : public QMainWindow
{
    Q_OBJECT
public:
   // explicit Playscene(QWidget *parent = nullptr);
       Playscene(int levelNum);
     int levelIndex ; //内部成员属性 记录所选的关卡
     void paintEvent(QPaintEvent *);
     //设计数组维护关卡数据
     int gameArray[4][4];
    mycoin * coinBtn [4][4];
    bool isWin;
signals:
    void chooseSceneBack();
public slots:
};

#endif // PLAYSCENE_H
