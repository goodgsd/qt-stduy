#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
Playscene::Playscene(int levelNum)
{
    QString str = QString("进入了第 %1 关 ").arg(levelNum);
    qDebug() << str;
    this->levelIndex = levelNum;


    //初始化场景
    this->setFixedSize(320,588);
    this->setWindowTitle("游戏场景");
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    QMenu * startMenu = bar->addMenu("开始");

    //创建退出 菜单项
    QAction *  quitAction = startMenu->addAction("退出");

    //点击退出 实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    //返回按钮
    MyPushButton * backbtn = new MyPushButton(":/res/BackButton.png" , ":/res/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width() - backbtn->width() , this->height() - backbtn->height());

    //点击返回
    connect(backbtn,&MyPushButton::clicked,[=](){
        qDebug() << "翻金币场景中：点击了返回按钮";

        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });

    });
    //显示level
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(21);
    QString str1 = QString("Level: %1").arg(this->levelIndex);
    //将字体设置到标签控件
    label->setFont(font);
    label->setText( str1);
    label->setGeometry(30, this->height() - 50,120, 50);




    //初始化二维数组
    dataConfig config;
     for(int i =0;i<4;i++){
         for(int j=0;j<4;j++){
            this->gameArray [i][j]=config.mData[this->levelIndex][i][j];

         }
    }
     QLabel* winLabel = new QLabel;
         QPixmap tmpPix;
         tmpPix.load(":/res/LevelCompletedDialogBg.png");
         winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
         winLabel->setPixmap(tmpPix);
         winLabel->setParent(this);
         winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());



    //游戏金币实现
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            QLabel * label =new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);
            label->move(57+i*50,200+j*50);

            QString str;
            if(this->gameArray[i][j]==1){
                str=":/res/Coin0001.png";
            }
            else{
                str=":/res/Coin0008.png";
            }


            mycoin *coin = new mycoin(str);
            coin->setParent(this);
            coin->move(57+i*50,204+j*50);

            coin->posX=i;
            coin->posY=j;
            coin->flag=this->gameArray[i][j];

            //把金币放进数组方便维护
            coinBtn[i][j]=coin;


            connect(coin,&mycoin::clicked,[=](){
                coin->changeflag();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0; //数组内部记录的标志同步修改
                QTimer::singleShot(300, this,[=](){
                    if(coin->posX+1 <=3)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeflag();
                        gameArray[coin->posX+1][coin->posY] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posX-1>=0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeflag();
                        gameArray[coin->posX-1][coin->posY] = gameArray[coin->posX-1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posY+1<=3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeflag();
                        gameArray[coin->posX][coin->posY+1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posY-1>=0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeflag();
                        gameArray[coin->posX][coin->posY-1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                    }

                    this->isWin = true;
                    for(int i = 0 ; i < 4;i++)
                    {
                        for(int j = 0 ; j < 4; j++)
                        {
                            //qDebug() << coinBtn[i][j]->flag ;
                            if( coinBtn[i][j]->flag == false)
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin==true)
                    {
                        qDebug() << "胜利";
                        for(int i = 0 ; i < 4;i++)
                        {
                            for(int j = 0 ; j < 4; j++)
                            {
                                coinBtn[i][j]->isWin=true;
                            }
                        }
                        if(this->isWin)
                        {
                            qDebug() << "胜利";
                            QPropertyAnimation * animation1 =  new QPropertyAnimation(winLabel,"geometry");
                            animation1->setDuration(1000);
                            animation1->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                            animation1->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                            animation1->setEasingCurve(QEasingCurve::OutBounce);
                            animation1->start();
                        }

                    }



                });



             });
        }

    }
}
void Playscene:: paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);
}
