#include "set.h"
#include "ui_set.h"

set::set(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::set)
{
    ui->setupUi(this);
    clientSocket = new QTcpSocket(this);

}

set::~set()
{
    delete ui;
}
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
struct environment_variable{
    float MAX_temperature;
    float MAX_ill;
    float MAX_humidity;
    float MIN_temperature;
    float MIN_ill;
    float MIN_humidity;

}variable;
//M0控制界面
void set::on_M0contButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
//M0环境变量
void set::on_evButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
//查看监控
void set::on_msgButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

}
//注册用户
void set::on_registerButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
//M0状态
void set::on_M0stateButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//M0led灯确认提交数据槽函数
void set::on_M0led_confirmButton_clicked()
{
    char buf[4] = {0};
    if( ui->M0led_offButton->isChecked()== true)
    {
        strcpy(buf,"30");
        clientSocket->write((char *)buf,sizeof(buf));
        qDebug() << "M0LED灯关闭";
    }
    if(ui->M0led_onButton->isChecked() == true)
    {
        strcpy(buf,"31");
        clientSocket->write((char *)buf,sizeof(buf));
        qDebug() << "M0LED灯开";
    }
}


//M0蜂鸣器确认提交槽函数
void set::on_M0buzzer_confirmButton_clicked()
{
    char buf[4] = {0};
    if( ui->M0buzzer_offButton->isChecked()== true)
    {
        strcpy(buf,"40");
        clientSocket->write((char *)buf,sizeof(buf));
        qDebug() << "M0蜂鸣器关闭";
    }
    if(ui->M0buzzer_onButton->isChecked() == true)
    {
        strcpy(buf,"41");
        clientSocket->write((char *)buf,sizeof(buf));
        qDebug()   << "M0蜂鸣器打开";
    }
}

//M0风扇确认提交数据槽函数
void set::on_fan_confirmButton_clicked()
{
    char buf[4] = {0};
    if( ui->fan_offButton->isChecked()== true)
    {
        strcpy(buf,"50");
        clientSocket->write((char *)buf,sizeof(buf));
        qDebug() << "风扇关闭";
    }
    if(ui->fan_1Button->isChecked() == true)
    {
        strcpy(buf,"51");
        clientSocket->write((char *)buf,sizeof(buf));
        qDebug()   << "风扇一档";
    }
    if(ui->fan_2Button->isChecked() == true)
    {
        strcpy(buf,"52");
        clientSocket->write((char *)buf,sizeof(buf));
        qDebug()   << "风扇二档";
    }if(ui->fan_3Button->isChecked() == true)
    {
        strcpy(buf,"53");
        clientSocket->write((char *)buf,sizeof(buf));
        qDebug()   << "风扇三档";
    }
}


//M0数码管确认提交数据槽函数
void set::on_tube_confirmButton_clicked()
{
   char buf[4] = {0};
   QString tube = QString ("%1%2").arg("6").arg(ui->tube_spinBox->text());
   QByteArray tu = tube.toLatin1();
   strcpy(buf,tu.data());
 //  qDebug() << buf;
   if(ui->tube_offButton->isChecked() == true)
   {
        strcpy(buf,"6f");
        clientSocket->write((char *)buf,sizeof(buf));
        qDebug() << "M0数码管灯关闭";
   }
   if(ui->tube_onButton->isChecked() == true)
   {
         clientSocket->write((char *)buf,sizeof(buf));
          qDebug() << "M0数码管灯开启";
   }
}

//A9led灯确认提交数据槽函数
void set::on_A9led_confirmButton_3_clicked()
{
    char buf[4] = {0};
    if( ui->A9led_offButton->isChecked()== true)
    {
        strcpy(buf,"10");
        clientSocket->write((char *)buf,sizeof(buf));
        qDebug() << "A53LED灯关闭";
    }
    if(ui->A9led_onButton->isChecked() == true)
    {
        strcpy(buf,"11");
        clientSocket->write((char *)buf,sizeof(buf));
        qDebug() << "A53LED灯开";
    }
}

//A9蜂鸣器确认提交数据槽函数
void set::on_A9buzzer_confirmButton_clicked()
{
    char buf[4] = {0};
    if( ui->A9buzzer_offButton->isChecked()== true)
    {
        strcpy(buf,"20");
        clientSocket->write((char *)buf,sizeof(buf));
        qDebug() << "A53蜂鸣器关闭";
    }
    if(ui->A9buzzer_onButton->isChecked() == true)
    {
        strcpy(buf,"21");
        clientSocket->write((char *)buf,sizeof(buf));
        qDebug() << "A53蜂鸣器打开";
    }
}
//注册账号的槽函数
void set::on_logonButton_clicked()
{

}
//退出槽函数
void set::on_exitButton_clicked()
{
    close();
}
//寻找WiFi槽函数
void set::on_wifiButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}
void set::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QRect rect = this->rect();
    QImage image(":/uImage/1.jpg");
    p.drawImage(rect,image);
}
//连接服务器槽函数
void set::on_connect_pushButton_clicked()
{
    clientSocket = new QTcpSocket();
    QString ip = ui->ipEdit->text();
    int port = ui->portEdit->text().toInt();
    clientSocket->connectToHost(ip,port);
    if(ui->connect_pushButton->text() == "连接服务器"){
    connect(clientSocket,SIGNAL(readyRead()),this,SLOT(on_readyRead_slots()));
            ui->connect_pushButton->setText("断开服务器");
    }else{
        ui->connect_pushButton->setText("连接服务器");

    }
}
//接收数据槽函数
void set::on_readyRead_slots()
{

   msg.resize(clientSocket->bytesAvailable());
   clientSocket->read((char *)&conver,sizeof(conver));
    QString snum = QString ("%1").arg(conver.snum);		 //仓库编号
    QString temperature = QString ("%1").arg(conver.temperature);	 //温度
    QString humidity = QString ("%1").arg(conver.humidity);		 //湿度
    QString ill = QString ("%1").arg(conver.ill);		 //光照
    QString  bet = QString ("%1").arg(conver.bet);		 //电池电量
    QString adc = QString ("%1").arg(conver.adc); 		 //电位器信息

    QString x = QString ("%1").arg(conver.x);			 //三轴信息
    QString y = QString ("%1").arg(conver.y);
    QString z = QString ("%1").arg(conver.z);

    ui->dtEdit->setText(snum);
    ui->lightEdit->setText(ill);
    ui->tempEdit->setText(temperature);
    ui->humEdit->setText(humidity);
    ui->XaxisEdit->setText(x);
    ui->YaxisEdit->setText(y);
    ui->ZaxisEdit->setText(z);
    ui->elementEdit->setText(bet);
    ui->potentiometerEdit->setText(adc);

}
//提交环境变量槽函数
void set::on_setdataButton_clicked()
{
    char buf[4] = {0};
    variable.MAX_temperature = ui->htempEdit->text().toFloat();
    variable.MAX_ill = ui->hlightEdit->text().toFloat();
    variable.MAX_humidity = ui->hhumEdit->text().toFloat();
    variable.MIN_temperature = ui->ltempEdit->text().toFloat();
    variable.MIN_ill = ui->llightlineEdit->text().toFloat();
    variable.MIN_humidity = ui->lhumEdit->text().toFloat();
    strcpy(buf,"70");
    clientSocket->write((char *)buf,sizeof(buf));
    clientSocket->write((char *)&variable,sizeof(variable));
}
