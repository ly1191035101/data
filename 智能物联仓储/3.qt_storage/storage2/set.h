#ifndef SET_H
#define SET_H

#include <QDialog>
#include <QPainter>

#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QButtonGroup>
#include <QDebug>
#include "sqldriver.h"

namespace Ui {
class set;
}

class set : public QDialog
{
    Q_OBJECT

public:
    explicit set(QWidget *parent = 0);
    ~set();
public:
    void paintEvent(QPaintEvent *);
struct conver_env_info {
        int snum;		 //仓库编号
        float temperature;	 //温度
        float humidity;		 //湿度
        float ill;		 //光照
        float bet;		 //电池电量
        float adc; 		 //电位器信息

        signed char x;			 //三轴信息
        signed char y;
        signed char z;
 }conver;
private slots:
    //MO 控制器槽函数
    void on_M0contButton_clicked();
    //M0 环境变量槽函数
    void on_evButton_clicked();
    //用户信息槽函数
    void on_msgButton_clicked();
    //注册用户槽函数
    void on_registerButton_clicked();
    //M0状态槽函数
    void on_M0stateButton_clicked();
    //M0led灯确认提交槽函数
    void on_M0led_confirmButton_clicked();

    //M0蜂鸣器确认提交槽函数
    void on_M0buzzer_confirmButton_clicked();

    //M0风扇确认提交数据槽函数
    void on_fan_confirmButton_clicked();

    //M0数码管确认提交数据槽函数
    void on_tube_confirmButton_clicked();

    //A9led灯确认提交数据槽函数
    void on_A9led_confirmButton_3_clicked();

    //A9蜂鸣器确认提交数据槽函数
    void on_A9buzzer_confirmButton_clicked();
    //注册账号槽函数
    void on_logonButton_clicked();
    //退出槽函数
    void on_exitButton_clicked();
    //寻找WiFi槽函数
    void on_wifiButton_clicked();
    //连接服务器槽函数
    void on_connect_pushButton_clicked();
    //读取数据
    void on_readyRead_slots();
    //提交环境变量
    void on_setdataButton_clicked();
private:
    Ui::set *ui;
    // 判断客户端连接服务起的状态
    // 客户端的套接字
    QTcpSocket *clientSocket;
    QByteArray msg;
};

#endif // SET_H
