#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include"playscene.h"
class chooselevelscene : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooselevelscene(QWidget *parent = nullptr);

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    Playscene *play =NULL;

signals:
    //写一个自定义信号，告诉主场景  点击了返回
    void chooseSceneBack();
public slots:
};

#endif // CHOOSELEVELSCENE_H
