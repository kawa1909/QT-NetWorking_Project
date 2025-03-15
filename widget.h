#ifndef WIDGET_H
#define WIDGET_H
#include<QUdpSocket>
#include <QWidget>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    enum msgType{
        Msg,//普通信息
        UserEnter,//用户进入
        UserLeft//用户离开
    };
    explicit Widget(QWidget *parent,QString name);
    //重写关闭事件
    void closeEvent(QCloseEvent *);
    void sendMsg(msgType type);//广播信息
    QString getName();//获取名字
    QString getMsg();//获取聊天信息
    void userEnter(QString username);//处理用户进入
    void userLeft(QString username,QString time);//处理用户离开
    void receiveMessage();//接收udp消息(槽函数)

    ~Widget();
signals:
    //发送关闭信号
    void closeWidget();
private:
    Ui::Widget *ui;
    QString myname;
    quint16 port;//端口
    QUdpSocket *udpSocket;//udp套接字
};

#endif // WIDGET_H
