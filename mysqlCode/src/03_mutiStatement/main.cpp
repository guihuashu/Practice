#include <iostream>
#include <thread>
#include <chrono>
#include <string>


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

    // 1.连接时,启用多语句执行支持和多结果处理支持
    if (!mysql_real_connect(&mysql, 0,
                       localhost.user,localhost.passwd,
                       localhost.db, localhost.port,0,CLIENT_MULTI_STATEMENTS))
    {
        cout << "connect faile"<<endl;
        return -1;
    }
    cout << "connect ok"<<endl;

    const char *mutiStatement =
                "drop table if exists testTable; \
                 create table  testTable(id INT AUTO_INCREMENT, val INT, PRIMARY KEY(id)); \
                 insert into  testTable values(1,10); \
                 update testTable SET val = 20 where id=1; \
                 select * from testTable;\
                 drop table testTable";

    // 2.一次执行多条sql语句
    if (mysql_query(&mysql, mutiStatement)) {
        cout<< mysql_error(&mysql)<<endl;
        return -1;
    }
    cout << "mysql_query(&mysql, mutiStatement) ok"<<endl;

    // 3.获取返回的多个结果集
    do {    // 执行sql语句后马上就会有结果集返回,所以要先获取结果集,再判断是否有下一个结果集
        MYSQL_RES *result = mysql_store_result(&mysql);
        if (result) {   /* 成功执行了查询类语句,有结果集返回 */
            cout<<"[result set] mysql_num_fields:"<<mysql_num_fields(result)<<endl;

        }
        else {  /* 没有结果集 */
            if (mysql_field_count(&mysql) >0) { // 执行select错误,有结果集
                cout<<"[result set] select err:"<<mysql_error(&mysql);
            }
            else { /* 执行了非查询语句,没有结果集返回 */
                ret = mysql_affected_rows(&mysql);  // 上一条sql语句影响的行数
                cout<<"[no result set] mysql_num_fields:"<<ret<<endl;
            }
        }

    }while(!mysql_next_result(&mysql));

    mysql_close(&mysql);   // 关闭连接
    mysql_library_end(); // 终止使用数据库


    return 0;
}

