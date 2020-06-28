#pragma once

#include <QString>
#include <vector>
#include "file_info.h"
#include <memory>

class ExplorerStrategy // Интерфейс стратегии
{
public:
    // Создаем синоним
    // Сохраняем
    using FileList = std::vector<FileInfo>;

    ExplorerStrategy() = default; //Дефолтный деструктор

    // Рекурсивный анализ директории
    // param [in] path путь к директории
    // return указатель на vector<FileInfo>
    virtual std::shared_ptr<FileList> Explore(const QString& path)const = 0;

    virtual ~ExplorerStrategy() = default; // Виртуальный дефолтный деструктор для правильного освобождения памяти
};

