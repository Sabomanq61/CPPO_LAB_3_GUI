#pragma once

#include <QString>

struct FileInfo
{
public:
    //
    FileInfo(const QString& name = "", const int64_t& size = 0, const float& percent = 0)
        : name_(name), size_(QString::number(size)), percent_(QString::number(percent))
    {}

    QString name_;
    QString size_;
    QString percent_;
};








