//
// Created by neo on 12/14/24.
//
#ifndef DATABASE_MODULE_H
#define DATABASE_MODULE_H
#include <cstdint>
#include <string>

enum class DatabaseType : uint8_t {
     GIT ,
     SQLITE,
     SQL,
     OTHER,
};

enum class OperationStatus {
     Success,           // 操作成功
     Failure,           // 操作失败
     NoData,            // 查询无数据
     DataExists,        // 数据已存在
     PermissionError,   // 权限错误
     UnknownError       // 未知错误
 };

class DatabaseModule {
    protected:
        DatabaseType base_type;      // 数据库类型
        char* base_path;             // 数据库路径
        void* database;              // 数据库指针

    public:
        // 构造函数：初始化数据库类型和路径
        DatabaseModule( DatabaseType base_type, char* base_path);

        // 析构函数：虚拟析构函数
        virtual ~DatabaseModule() = default;

    protected:
        // 将状态转换为字符串（用于日志）
        static std::string statusToString( OperationStatus status);

        // 创建数据库
        virtual void* CreateDatabase() = 0;

        // 打开数据库
        virtual void* OpenDatabase() = 0;

        // 关闭数据库
        virtual void CloseDatabase() = 0;

    public:
        // 获取数据库实例（）
        virtual void* GetDatabase() = 0;

        // 获取数据
        virtual void* GetData(char* data) = 0;

        // 删除数据
        virtual void DeleteData(char* data) = 0;

        // 添加数据
        virtual void AddData(char* data) = 0;

        // 修改数据
        virtual void ChangeData(char* data) = 0;
};

std::string statusToString(OperationStatus status);
#endif //DATABASE_MODULE_H