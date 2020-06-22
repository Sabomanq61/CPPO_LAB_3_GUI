#pragma once

#include <QString>
#include <vector>
#include "dir_info.h"
#include <memory>

class ExplorerStrategy // Интерфейс стратегии
{
public:
    using FileList = std::vector<FileInfo>;

    ExplorerStrategy() = default; //Дефолтный деструктор

    // param [in] path путь к директории
    // return указатель на FileInfo
    virtual std::shared_ptr<FileList> Explore(const QString& path)const = 0;

    virtual ~ExplorerStrategy() = default; // Виртуальный дефолтный деструктор для правильного освобождения памяти
};

