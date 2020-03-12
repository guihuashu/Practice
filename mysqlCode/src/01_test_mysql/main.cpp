#include <iostream>
#include <thread>
#include <chrono>


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
    (const char *)"sys",
    3306
};
static const char *CMDShowDatabases = "show databases";
static const char *CMDShowTables = "show tables";
int main()
{

    MYSQL sql;
    mysql_init(&sql);
    int connectTimeout = 5; //秒
    bool Reconnect = true;
    int ret;

    mysql_options(&sql, MYSQL_OPT_CONNECT_TIMEOUT, &connectTimeout);
    mysql_options(&sql, MYSQL_OPT_RECONNECT, &Reconnect);
    cout << "connect1 "<<endl;

    if (!mysql_real_connect(&sql, 0,
                       localhost.user,localhost.passwd,
                       localhost.db, localhost.port,0,0))
    {
        cout << "connect faile"<<endl;
        return -1;
    }
    cout << "connect ok"<<endl;

    // 查询
    const char *cmd = "select * from sys_config";
    cout << mysql_real_query(&sql, cmd, strlen(cmd))<<endl;
    // 获取结果集
    MYSQL_RES *result = NULL;
    //result = mysql_store_result(&sql);
    result = mysql_use_result(&sql);

    MYSQL_ROW row;
    unsigned long *lengths;
    int fieldsNum = 0;
    MYSQL_FIELD *field;
    fieldsNum = mysql_num_fields(result);

    // 读取结果集中的字段
    while (field = mysql_fetch_field(result)) {
        cout<<field->name<<" ";
    }
    cout<<endl;

    // 遍历结果集中的所有字段信息
    while (row = mysql_fetch_row(result)){      // 一行
        lengths = mysql_fetch_lengths(result);  // 读取该行中的字段信息长度
        for (int i=0; i < fieldsNum; ++i){      // 打印
            if (row[i])
                cout<<row[i]<<flush;            // 字段信息数组
            else
                cout<<"NULL"<<flush;
            cout<<"("<< lengths[i]<< ")" << " "<<flush; // 字段信息长度数组
        }
        cout<<endl;
    }

    mysql_close(&sql);   // 关闭连接
    mysql_library_end(); // 终止使用数据库


    return 0;
}

