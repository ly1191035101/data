#include "login.h"
#include "set.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 实例化登录框的对象
    login login1;
    login1.show();
    // exec()函数返回值，如果为QDialog::accepted(1)表示成功
    // 如果返回QDialog::rejected(0)表示失败
    // 要想返回Accepted值，在登录的槽函数中调用accept()
    if(login1.exec() == QDialog::Accepted)
    {
        set w;
        w.show();

        return a.exec();
    }
    else {
        return -1;
    }
}

