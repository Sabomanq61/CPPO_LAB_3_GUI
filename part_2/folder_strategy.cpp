#include "folder_strategy.h"
#include <QFileInfo>
#include <QDir>
#include <QTextStream>

std::shared_ptr<ExplorerStrategy::FileList> StrategyFolder::Explore(const QString& path) const
{
    using namespace std;

    QFileInfo file(path);

    uint64_t total_size = 0;

    if(file.isDir())// Проверка на то что элемент является директорией
    {
        std::shared_ptr<ExplorerStrategy::FileList> dirInfo (new ExplorerStrategy::FileList);

        QDir dir(path);

        for(QFileInfo it : dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Type))
        {
            uint64_t size = Size(it.absoluteFilePath());
            total_size += size;
            dirInfo->push_back(FileInfo(it.fileName(), (size)));
        }

        for(auto& it : *dirInfo)
        {
            it.percent_ = QString::number(it.size_.toFloat() / total_size);
        }

        return dirInfo;
    }
    return nullptr;
}

int64_t StrategyFolder::Size(const QString &path) const
{
    QFileInfo fileInfo(path);

    if(fileInfo.isDir())
    {
        QDir dir(path);
        int64_t total_size=0;
        //Обход элементов папки
        for (QFileInfo it : dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System | QDir::NoSymLinks,QDir::Name))
        {
            if(it.isDir())
            {
                total_size += Size(it.absoluteFilePath());// Рекурсия для вычисления размера папки содержащей еще папки.
            }
            else total_size+=it.size();
        }
        return total_size;
    }
    return fileInfo.size();
}



