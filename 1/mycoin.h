#ifndef MYCOIN_H
#define MYCOIN_H


#include<QPushButton>
#include<QTimer>
class mycoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit mycoin(QWidget *parent = nullptr);
    //参数表示传入的是什么图片
    mycoin(QString btnimg);
    //金币属性
    int posX;
    int posY;
    bool flag;

    //改变金币
    void changeflag();
    QTimer * timer1;
    QTimer * timer2;
    int min =1;
    int max =8;
    bool isAnimation  = false;
    void mousePressEvent(QMouseEvent *e);
    bool isWin =false;

signals:

public slots:
};

#endif // MYCOIN_H
