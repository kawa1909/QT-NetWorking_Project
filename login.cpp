#include "login.h"
#include "ui_login.h"
#include<QToolButton>
#include<QPixmap>
#include "widget.h"
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    QVector<QToolButton*> vector;
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/qq.png"));//图标
    this->setWindowTitle("QQ");//窗口名称
    //用户名列表
    QStringList list;
    list<<"吕蒙"<<"诸葛亮"<<"曹操"<<"关羽"<<"刘禅"<<"许诸"<<"孟获"<<"周瑜"<<"小乔";
    //图片资源列表
    QStringList listIcon;//和用户名列表一一对应
    listIcon<<"spqy"<<"ymrl"<<"qq"<<"Cherry"<<"dr"<<"jj"<<"lswh"<<"qmnn"<<"spqy";

    for(int i=0;i<9;i++){//将用户显示在login界面
       QToolButton *btn=new QToolButton(this);//定义按钮指针
       btn->setIcon(QPixmap(QString(":/images/%1.png").arg(listIcon[i])));//%1对应着listIcon[i]
       btn->setIconSize(QPixmap(QString(":/images/%1.png").arg(listIcon[i])).size());//图片大小
       //设置按钮为透明
       btn->setAutoRaise(true);
       //设置网名
       btn->setText(QString("%1").arg(list[i]));
       //设置显示格式
       btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//图片和用户名一起显示
       ui->vlayout->addWidget(btn);
       vector.push_back(btn);//把指针添加到数组中循环
       isShow.push_back(false);
    }
    for(int i=0;i<9;i++){
        connect(vector[i],&QToolButton::clicked,[=](){
            if(true==isShow[i]){
                QMessageBox::warning(this,"警告","该聊天框已被打开");
                return;
            }
            isShow[i]=true;//标记该用户的聊天窗的已经打开
            Widget *widget=new Widget(0,vector[i]->text());//放到堆区
            widget->setWindowIcon(vector[i]->icon());//
            widget->setWindowTitle(vector[i]->text());//
            widget->show();//打开该用户的聊天窗口
            //关闭聊天框时将对于的isShow跟改为false
            connect(widget,&Widget::closeWidget,[=](){//信号槽连接
                isShow[i]=false;
            });
         });
    }
}

Login::~Login()
{
    delete ui;
}
