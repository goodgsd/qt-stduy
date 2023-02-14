 #include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QPushButton>
#include"mypushbutton.h"
#include<QTimer>
#include"mycoin.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //主场景

    //固定大小
    setFixedSize(320,588);
    //图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("翻金币主场景");
    //tuichu
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    choosScene =new chooselevelscene;
   MyPushButton *startbtn =new MyPushButton(":/res/MenuSceneStartButton.png");
   startbtn->setParent(this);
   startbtn->move(this->width()*0.5-startbtn->width()*0.5,this->height()*0.7);
    //实例化选择关卡的场景
   choosScene =new chooselevelscene;

   //监听选择关卡的返回按钮的信号
   connect(choosScene,&chooselevelscene::chooseSceneBack,this,[=](){
       choosScene->hide(); //将选择关卡场景 隐藏掉
       this->show(); //重新显示主场景
   });


   connect(startbtn,&MyPushButton::clicked,[=](){

       //做弹起特效
       startbtn->zoom1();
       startbtn->zoom2();

       //延时进入到选择关卡场景中
       QTimer::singleShot(500,this,[=](){
           //自身隐藏
           this->hide();
           //显示选择关卡场景
           choosScene->show();
       });



   });
}
void MainWindow:: paintEvent(QPaintEvent *)
 {
    //创建画家，指定绘图设备
        QPainter painter(this);
        //创建QPixmap对象
        QPixmap pix;
        //加载图片
        pix.load(":/res/PlayLevelSceneBg.png");
        //绘制背景图
       painter.drawPixmap(0,0,this->width(),this->height(),pix);

       //背景图图标
       pix.load(":/res/Title.png");
       pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
       painter.drawPixmap(10,30,pix);





}
MainWindow::~MainWindow()
{
    delete ui;
}
