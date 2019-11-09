#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <Qpainter>
#include <QMessageBox>
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
public:
    void paintEvent(QPaintEvent *);
private slots:
    //登录的槽函数
    void on_loginButton_clicked();
    //退出登录的槽函数
    void on_exitButton_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
