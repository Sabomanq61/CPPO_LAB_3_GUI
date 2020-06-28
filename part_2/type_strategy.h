#pragma once
#include "strategy.h"
#include <map>

class StrategyType : public ExplorerStrategy
{
public:
    StrategyType() = default;

    /// @brief
    /// parh путь к директории
    /// return
    std::shared_ptr<FileList> Explore(const QString& path) const override;

    //Подсчет размера объекта
    //return размер объекта
    int64_t Size(const QString& path, std::map<QString, int64_t>& hash) const;

    ~StrategyType() = default;
};


