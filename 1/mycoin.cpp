#include "mycoin.h"
#include<QDebug>
mycoin::mycoin(QString btnimg){
    QPixmap pix;
    bool ret =pix.load(btnimg);
    if(!ret){
        QString str = QString("图片%1加载失败").arg(btnimg);
        qDebug()<<str;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton(border:Opx;)");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));


    timer1 = new QTimer(this);
    timer2 =new QTimer(this);
    connect(timer1,&QTimer::timeout,[=](){
            QPixmap pixmap;
            QString str = QString(":/res/Coin000%1.png").arg(this->min++);
            pixmap.load(str);
            this->setFixedSize(pixmap.width(),pixmap.height() );
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(pixmap);
            this->setIconSize(QSize(pixmap.width(),pixmap.height()));
            if(this->min > this->max)


            {
                this->min = 1;
                isAnimation=false;
                timer1->stop();
            }
        });
    connect(timer2,&QTimer::timeout,[=](){
            QPixmap pixmap;
            QString str = QString(":/res/Coin000%1.png").arg(this->max-- );
            pixmap.load(str);
            this->setFixedSize(pixmap.width(),pixmap.height() );
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(pixmap);
            this->setIconSize(QSize(pixmap.width(),pixmap.height()));
            if(this->max < this->min) //如果小于最小值，重置最大值，并停止定时器
            {
                this->max = 8;
                isAnimation=false;
                timer2->stop();
            }
        });



}
void mycoin::mousePressEvent(QMouseEvent *e){
    if(this->isAnimation||this->isWin )
        {
            return;
        }
        else
        {
            return QPushButton::mousePressEvent(e);
        }

}
void mycoin::  changeflag(){
    if(this->flag){
        timer1->start(30);
        this->isAnimation=true;
        this->flag=false;
    }
    else //反面执行下列代码
        {
            timer2->start(30);
            this->isAnimation=true;
            this->flag = true;
        }


}
