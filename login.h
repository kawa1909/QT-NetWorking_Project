#ifndef LOGIN_H
#define LOGIN_H
#include<QVector>
#include <QWidget>
#include<QMessageBox>
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private:
    Ui::Login *ui;
    //初始状态为未打开登录后的界面
    QVector<bool> isShow;
};

#endif // LOGIN_H
