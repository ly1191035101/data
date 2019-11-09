/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *loginButton;
    QLineEdit *passwdEdit;
    QLineEdit *nameEdit;
    QLabel *label_3;
    QPushButton *exitButton;
    QLabel *label_2;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QStringLiteral("login"));
        login->resize(570, 422);
        login->setMinimumSize(QSize(570, 422));
        login->setMaximumSize(QSize(570, 422));
        login->setStyleSheet(QStringLiteral(""));
        layoutWidget = new QWidget(login);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(260, 230, 301, 133));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        loginButton = new QPushButton(layoutWidget);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        QFont font;
        font.setPointSize(19);
        font.setBold(true);
        font.setWeight(75);
        loginButton->setFont(font);

        gridLayout->addWidget(loginButton, 2, 1, 1, 1);

        passwdEdit = new QLineEdit(layoutWidget);
        passwdEdit->setObjectName(QStringLiteral("passwdEdit"));
        QFont font1;
        font1.setPointSize(15);
        passwdEdit->setFont(font1);
        passwdEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(passwdEdit, 1, 1, 1, 2);

        nameEdit = new QLineEdit(layoutWidget);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));
        nameEdit->setFont(font1);

        gridLayout->addWidget(nameEdit, 0, 1, 1, 2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);
        label_3->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        exitButton = new QPushButton(layoutWidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setFont(font);

        gridLayout->addWidget(exitButton, 2, 2, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);


        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QApplication::translate("login", "login", 0));
        loginButton->setText(QApplication::translate("login", "\347\231\273\345\275\225", 0));
        passwdEdit->setText(QApplication::translate("login", "admin", 0));
        nameEdit->setText(QApplication::translate("login", "admin", 0));
        label_3->setText(QApplication::translate("login", "\345\257\206\347\240\201\357\274\232", 0));
        exitButton->setText(QApplication::translate("login", "\351\200\200\345\207\272", 0));
        label_2->setText(QApplication::translate("login", "\350\264\246\345\217\267\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
