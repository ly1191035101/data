#include "sqldriver.h"
sqlDriver::sqlDriver(QWidget *parent):db(new QSqlDatabase),
    model(new QSqlQueryModel(parent))
{

}
sqlDriver::~sqlDriver()
{
    delete db;
    delete model;
}
// 连接数据库和创建数据库文件的函数
void sqlDriver::createDB()
{
    // 连接sqlite数据库的驱动文件
    *db = QSqlDatabase::addDatabase("QSQLITE");
    // 设置数据库文件，如果文件不存在，创建数据库文件
    db->setDatabaseName("user.db");
    // 打开数据库文件
    db->open();
}
// 执行sql语句的函数
void sqlDriver::ExecSqlQuery(const QString& sql_str)
{
    // 准备sql语句
    QSqlQuery query;
    query.prepare(sql_str);
    qDebug() << sql_str;
    // 执行sql语句
    query.exec();
}
// 查询sql语句的函数，并返回结果
QSqlQueryModel* sqlDriver::selectData(const QString& select_sql)
{
    // 准备sql语句 ,并且执行sql语句
    model->setQuery(select_sql);
    return model;
}
