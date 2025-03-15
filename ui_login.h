/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QGridLayout *gridLayout;
    QToolBox *toolBox;
    QWidget *page;
    QVBoxLayout *vlayout;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(300, 700);
        gridLayout = new QGridLayout(Login);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        toolBox = new QToolBox(Login);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 300, 670));
        vlayout = new QVBoxLayout(page);
        vlayout->setObjectName(QStringLiteral("vlayout"));
        toolBox->addItem(page, QString::fromUtf8("\347\276\244\346\210\220\345\221\230"));

        gridLayout->addWidget(toolBox, 0, 0, 1, 1);


        retranslateUi(Login);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Form", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("Login", "\347\276\244\346\210\220\345\221\230", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
