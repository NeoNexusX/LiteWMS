//
// Created by neo on 12/14/24.
//
#include "../include/database_module.h"

// 构造函数：初始化成员变量
DatabaseModule::DatabaseModule(const DatabaseType base_type, char* base_path)
    : base_type(base_type), base_path(base_path), database(nullptr) {
    // 数据库指针初始化为 nullptr
}

// 静态函数：将状态转换为字符串
std::string DatabaseModule::statusToString(const OperationStatus status) {
    switch (status) {
        case OperationStatus::Success:        return "Success";
        case OperationStatus::Failure:        return "Failure";
        case OperationStatus::NoData:         return "No Data";
        case OperationStatus::DataExists:     return "Data Already Exists";
        case OperationStatus::PermissionError:return "Permission Error";
        case OperationStatus::UnknownError:   return "Unknown Error";
        default:                              return "Unknown Status";
    }
}
