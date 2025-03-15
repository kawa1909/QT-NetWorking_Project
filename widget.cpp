#include "widget.h"
#include "ui_widget.h"
#include<QDataStream>
#include<QMessageBox>
#include<QDateTime>
#include<QTableWidget>
#include<QComboBox>
#include<QFont>
#include<QColorDialog>
#include<QFileDialog>
#include<QDebug>
Widget::Widget(QWidget *parent,QString name) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->myname=name;
    port=9999;
    udpSocket=new QUdpSocket(this);
    //允许其他服务器连接相同端口和地址|重新连接服务器
    udpSocket->bind(port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);


    //发送按钮
    connect(ui->sendBtn,&QPushButton::clicked,this,[=](){
        sendMsg(Msg);
    });
    //监听别人发送的数据
    connect(udpSocket,&QUdpSocket::readyRead,this,&Widget::receiveMessage);

    //新用户进入
   sendMsg(UserEnter);
   connect(ui->exitBtn,&QPushButton::clicked,this,[=](){
       this->close();
   });

   //字体
   connect(ui->fontCbx,&QFontComboBox::currentFontChanged,this,[=](const QFont &font){
       //设置全局字体
       ui->msgTxtEdit->setFontFamily(font.toString());
       ui->msgTxtEdit->setFocus();
   });

   //字体大小
   void (QComboBox:: *sizeBtn)(const QString &text)=&QComboBox::currentTextChanged;
   connect(ui->sizeCbx,sizeBtn,this,[=](const QString &text){
       ui->msgTxtEdit->setFontPointSize(text.toDouble());
        ui->msgTxtEdit->setFocus();
   });

   //加粗
   connect(ui->boldBtn,&QToolButton::clicked,this,[=](bool checked){
       //是否按下
       if(checked){
          ui->msgTxtEdit->setFontWeight(QFont::Bold);
       }else{
           ui->msgTxtEdit->setFontWeight(QFont::Normal);
       }
   });

   //倾斜
   connect(ui->italicTbtn,&QToolButton::clicked,this,[=](bool checked){
       ui->msgTxtEdit->setFontItalic(checked);
       ui->msgTxtEdit->setFocus();
   });

   //下划线
   connect(ui->underlineTbtn,&QToolButton::clicked,this,[=](bool checked){
       ui->msgTxtEdit->setFontUnderline(checked);
       ui->msgTxtEdit->setFocus();
   });

    //清空
   connect(ui->clearTbtn,&QToolButton::clicked,this,[=](){
       ui->msgBrowser->clear();
   });

   //字体颜色
   connect(ui->colorTbtn,&QToolButton::clicked,this,[=](){
       QColor color=QColorDialog::getColor(color,this);
        ui->msgTxtEdit->setTextColor(color);
   });

   //保存聊天记录
   connect(ui->saveTbtn,&QToolButton::clicked,this,[=](){
       if(ui->msgBrowser->toPlainText().isEmpty()){
           QMessageBox::warning(this,"警告","保存内容不能为空");
           return;
       }
       //获取保存文件绝对路径/文件名(窗口标题,文件名,类型)
       QString fileName=QFileDialog::getSaveFileName(this,"保存聊天记录","聊天记录","(*.txt)");
       if(!fileName.isEmpty()){
           QFile file(fileName);
           file.open(QIODevice::WriteOnly|QFile::Text);
           QTextStream stream(&file);
           stream<<ui->msgBrowser->toPlainText();
           file.close();
       }
   });
}

void Widget::closeEvent(QCloseEvent *)
{
    emit closeWidget();
    sendMsg(UserLeft);
    udpSocket->close();
    udpSocket->destroyed();
}

void Widget::sendMsg(Widget::msgType type)
{
        QByteArray array;
        QDataStream stream(&array,QIODevice::WriteOnly);
        stream<<type<<this->getName();
        switch (type)
        {
        case Msg:
            if(ui->msgTxtEdit->toPlainText()=="")
            {
                QMessageBox::warning(this,"警告","发送的聊天内容不能为空!");
                return;
            }
            stream<<this->getMsg();
            break;
        case UserEnter:
            break;
        case UserLeft:
            break;
        }
        //书写报文
        udpSocket->writeDatagram(array.data(),array.size(),QHostAddress::Broadcast,this->port);
}

QString Widget::getName()
{
    return myname;
}

QString Widget::getMsg()
{
    QString msg=ui->msgTxtEdit->toHtml();
    ui->msgTxtEdit->clear();
    ui->msgTxtEdit->setFocus();
    return msg;
}

void Widget::userEnter(QString username)
{
    bool IsEmpty=ui->tableWidget->findItems(username,Qt::MatchExactly).isEmpty();
       if(IsEmpty)
       {
           QTableWidgetItem *table=new QTableWidgetItem(username);
           ui->tableWidget->insertRow(0);
           ui->tableWidget->setItem(0,0,table);
           ui->msgBrowser->setTextColor(QColor(Qt::gray));
           ui->msgBrowser->append(username+"已上线");
           ui->userNumLbl->setText(QString("在线人数:%1").arg(ui->tableWidget->rowCount()));
           sendMsg(UserEnter);
       }
}

void Widget::userLeft(QString username, QString time)
{
    bool isEmpty=ui->tableWidget->findItems(username,Qt::MatchExactly).isEmpty();
    if(!isEmpty){
        int row=ui->tableWidget->findItems(username,Qt::MatchExactly).first()->row();
        ui->tableWidget->removeRow(row);
        ui->msgBrowser->append(username+"用户于"+time+"离开");
         ui->userNumLbl->setText(QString("在线人数:%1").arg(ui->tableWidget->rowCount()));
    }
}

void Widget::receiveMessage()
{
    qint64 size=udpSocket->pendingDatagramSize();
        //int mysize= static_cast<int>(size);
        QByteArray array=QByteArray(size,0);
        udpSocket->readDatagram(array.data(),size);
        QDataStream stream(&array,QIODevice::ReadOnly);
        int mytype;
        QString name,msg;//用户名 聊天内容
        QString time=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        stream>>mytype;
        switch (mytype) {
        case Msg:
            stream>>name>>msg;
            ui->msgBrowser->setTextColor(QColor(Qt::blue));
            ui->msgBrowser->append("["+name+"]"+time);
            ui->msgBrowser->append(msg);
            break;
        case UserLeft:
            stream>>name;
            userLeft(name,time);
            break;
        case UserEnter:
            stream>>name;
            userEnter(name);
            break;
        }
}

Widget::~Widget()
{
    delete ui;
}
