
#include <iostream>
#include <mysql.h>
int main()
{
    MYSQL sql;
    mysql_init(&sql);
    std::cout << "Hello World!\n";
    return 0;
}
