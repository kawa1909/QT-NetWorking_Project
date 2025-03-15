#include "widget.h"
#include <QApplication>
#include "login.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // Widget w;
  //  w.show();
    Login login;//登陆界面
    login.show();//展示登录界面
    return a.exec();//会话循环
}
