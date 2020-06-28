#pragma once

#include "strategy.h"
//Стратегия группировка по элементам

class StrategyFolder : public ExplorerStrategy
{
public:
    ///@brief Конструктор по умолчанию
    StrategyFolder() = default;


    /// parh путь к директории
    /// return умный указатель на vector<FileInfo> = FileList
    std::shared_ptr<FileList> Explore(const QString& path) const override;

    //Подсчет размера объекта
    //return размер объекта
    int64_t Size(const QString& path) const;

    ~StrategyFolder() = default;
};
