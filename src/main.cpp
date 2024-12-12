#include <iostream>
#include <sqlite3.h> // SQLite3 的头文件

int main(int argc, char* argv[]) {
    sqlite3* db = nullptr;  // 初始化数据库连接指针为 nullptr

    // 尝试打开数据库文件
    if (const int rc = sqlite3_open("./results/test.db", &db); rc != SQLITE_OK) {  // 检查返回值，确保数据库成功打开
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);  // 如果打开失败，也需要确保清理资源
        return 1;           // 返回非零值表示程序失败
    }

    std::cout << "Opened database successfully" << std::endl;

    // 关闭数据库连接
    sqlite3_close(db);
    return 0;  // 返回 0 表示程序成功
}
