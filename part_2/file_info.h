#pragma once

#include <QString>

///Структура для хранения информации о файле или типе файла.
struct FileInfo
{
public:
    //Констуктор
    //Принимает имя объекта, размер и процент. соотн-ие
    //Преоб-ем численные типы данных к QString
    FileInfo(const QString& name = "", const int64_t& size = 0, const float& percent = 0)
        : name_(name), size_(QString::number(size)), percent_(QString::number(percent, 'g', 4) + '%')
    {}

    // имя объекта
    QString name_;
    // размер объекта
    QString size_;
    // процент. содер-ие.
    QString percent_;
};








