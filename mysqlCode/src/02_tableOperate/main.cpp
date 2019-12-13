#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>

using namespace std;
#include <mysql.h>

struct LocalhostInfo
{
    const char *user;
    const char *passwd;
    const char *db;
    const int port;
};
static LocalhostInfo localhost = {
    (const char *)"root",
    (const char *)"060198",
    (const char *)"lxkt",
    3306
};
static const char *CMDShowDatabases = "show databases";
static const char *CMDShowTables = "show tables";
int main()
{

    MYSQL mysql;
    mysql_init(&mysql);
    int connectTimeout = 5; //秒
    bool Reconnect = true;
    int ret;

    mysql_options(&mysql, MYSQL_OPT_CONNECT_TIMEOUT, &connectTimeout);
    mysql_options(&mysql, MYSQL_OPT_RECONNECT, &Reconnect);
    cout << "connect1 "<<endl;

    // 连接到mysql数据库
    if (!mysql_real_connect(&mysql, 0,
                       localhost.user,localhost.passwd,
                       localhost.db, localhost.port,0,0)){
        cout << "connect faile"<<endl;
        return -1;
    }
    cout << "connect ok"<<endl;

    // 1. 如果表t_image不存在,就在数据库中创建该表
    const char *CmdCrateTable = "create table IF NOT EXISTS `t_image` ( \
                                `id` int AUTO_INCREMENT, \
                                `name` varchar(1024), \
                                `path` varchar(2046), \
                                `size` int, \
                                PRIMARY KEY(`id`)\
                                )";
    if (mysql_query(&mysql, CmdCrateTable)) {
        cout<< mysql_error(&mysql)<<endl;
        return -1;
    }
    cout << "create table ok"<<endl;

    // 2.向表中插入数据
    const char *CmdInsertRow = "insert into `t_image` \
                               (`name`, `path`, `size`) \
                               values('2.jpg', 'g:/2.jpg',2048) \
                               ";
    if (mysql_query(&mysql, CmdInsertRow)) {
        cout<< mysql_error(&mysql)<<endl;
        return -1;
    }
    ret = mysql_affected_rows(&mysql);
    cout<< "mysql_affected_rows: "<<ret<<endl;

    // 插入5条数据
    for (int i=0; i< 1000; i++){
        stringstream ss;
        ss<<"insert into `t_image` (`name`, `path`, `size`) values('";
        ss<<i<< ".jpg', 'g:/img/',1024)";
        //cout<<ss.str()<<endl;
        cout<<"mysql_insert_id: "<<mysql_insert_id(&mysql)<<endl;
        if (mysql_query(&mysql, ss.str().c_str()))
            cout<<mysql_error(&mysql);
    }

    // 3.修改表中的数据
    if (mysql_query(&mysql, "update t_image set name='LiSi',size=88 where id=4"))
        cout<<mysql_error(&mysql);

    // 4.删除表中的数据
    if (mysql_query(&mysql, "delete from t_image where id=9"))
        cout<<mysql_error(&mysql);
    // 从存储器中删除内容
    if (mysql_query(&mysql, "optimize table t_image"))
        cout<<mysql_error(&mysql);



    mysql_close(&mysql);   // 关闭连接
    mysql_library_end(); // 终止使用数据库


    return 0;
}

