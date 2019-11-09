#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}
//登录的槽函数
void login::on_loginButton_clicked()
{
    QString name,password;
        name = ui->nameEdit->text();
        password = ui->passwdEdit->text();
        if(name =="" || password == ""){
            QMessageBox::critical(this,"温馨提示：","用户名和密码不能为空");
            }else{
                if(name == "admin" && password == "admin"){
                    accept();
              }else{
                   QMessageBox::critical(this,"温馨提示：","用户名或密码错误");
                }
          }
}
//退出登录的槽函数
void login::on_exitButton_clicked()
{
    close();
}
void login::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QRect rect = this->rect();
    QImage image(":/uImage/timg.jpg");
    p.drawImage(rect,image);
}
