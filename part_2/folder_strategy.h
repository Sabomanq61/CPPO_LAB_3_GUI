#pragma once

#include "strategy.h"
//Стратегия группировка по элементам

class StrategyFolder : public ExplorerStrategy
{
public:
    StrategyFolder() = default;

    /// @brief
    /// parh путь к директории
    /// return
    std::shared_ptr<FileList> Explore(const QString& path) const override;

    //Подсчет размера объекта
    //return размер объекта
    int64_t Size(const QString& path) const;

    ~StrategyFolder() = default;
};
