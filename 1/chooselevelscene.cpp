#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>

chooselevelscene::chooselevelscene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320,588);

    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡");
    //菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    //开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    //退出 菜单项
    QAction *  quitAction = startMenu->addAction("退出");

    //点击退出
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    MyPushButton *backbtn =new MyPushButton(":/res/BackButton.png" , ":/res/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width() - backbtn->width() , this->height() - backbtn->height());

    //点击返回
    connect(backbtn,&MyPushButton::clicked,[=](){

        //延时返回
        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });

    });
    for(int i=0;i<20;i++){
        MyPushButton *menubtn =new MyPushButton( ":/res/LevelIcon.png");
        menubtn->setParent(this);
        menubtn->move(25+i%4 * 70,130+i/4*70);

        //gao zhi yong hu xuan ze de shi di ji guan
        connect(menubtn,&MyPushButton::clicked,[=](){
            QString str = QString("您选择的是第 %1 关 ").arg( i + 1);
            qDebug() <<str;


            //JINRU
            this->hide();
            play =new Playscene(i+1);
            play->show();//显示游戏场景

            connect(play,&Playscene::chooseSceneBack,[=](){
                this->show();
                delete play;
                play = NULL;
            });

        });
    //label hui 覆盖按钮得设置穿透属性。
        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menubtn->width(),menubtn->height());
        label->setText(QString::number(i+1));
        label->move(25 + i%4 * 70 , 130 + i/4 * 70 );

        //设置 label上的文字对齐方式 水平居中和 垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置让鼠标进行穿透   51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }


}
void chooselevelscene::  paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap( (this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
