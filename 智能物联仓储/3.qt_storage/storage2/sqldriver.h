#ifndef SQLDRIVER_H
#define SQLDRIVER_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

class sqlDriver
{
public:
    sqlDriver(QWidget *parent = nullptr);
    ~sqlDriver();
    // 连接数据库和创建数据库文件的函数
    void createDB();
    // 执行sql语句的函数
    void ExecSqlQuery(const QString& sql_str);
    // 查询sql语句的函数，并返回结果
    QSqlQueryModel* selectData(const QString& select_sql);
 private:
    QSqlDatabase *db;
    QSqlQueryModel *model;
};

#endif // SQLDRIVER_H
