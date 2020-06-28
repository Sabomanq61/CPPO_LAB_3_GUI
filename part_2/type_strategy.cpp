#include "type_strategy.h"
#include <QFileInfo>
#include <QDir>
#include <vector>
#include <QTextStream>


std::shared_ptr<ExplorerStrategy::FileList> StrategyType::Explore(const QString& path ) const
{
    using namespace std;
    QFileInfo fileInfo(path);

    if(fileInfo.isDir())
    {
        shared_ptr<ExplorerStrategy::FileList> result(new ExplorerStrategy::FileList);
        std::map<QString, int64_t> hash;
        QDir dir(path);

        int64_t totalSize = 0;

        for(QFileInfo it : dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System | QDir::NoSymLinks,QDir::Name))
        {
            totalSize += Size(it.absoluteFilePath(), hash);
        }

        for(const auto& it : hash)
        {
            result->push_back(FileInfo(it.first, it.second, float(it.second) / totalSize));
        }
        return result;
    }
    return nullptr;
}

int64_t StrategyType::Size(const QString& path, std::map<QString,int64_t>& hash) const
{
    QFileInfo fileInfo(path);
    if(fileInfo.isDir())
    {
        QDir dir(path);
        uint64_t totalSize=0;
        //Обход элементов папки
        for (QFileInfo it : dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System | QDir::NoSymLinks,QDir::Name)) {
            if(it.isDir())
            {
                totalSize += Size(it.absoluteFilePath(),hash);
            }
            else
            {
                hash[it.suffix()]+=it.size();
                totalSize += it.size();
            }
        }
        return totalSize;
    }
    hash[fileInfo.suffix()] += fileInfo.size();
    return fileInfo.size();
}
