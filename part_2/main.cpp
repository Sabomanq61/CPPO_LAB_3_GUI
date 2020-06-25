#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "dir_info.h"
#include "folder_strategy.h"
#include "type_strategy.h"
#include <QTextStream>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

    //QFileInfo t("D:\dev\CPPO\CPPO_LAB_3_GUI\part_2\test\test3");

    //StrategyFolder explore;
    //std::shared_ptr<ExplorerStrategy::FileList> pointer = explore.Explore("../part_2/test/test3");
    /*StrategyType expType;
    std::shared_ptr<ExplorerStrategy::FileList> pointer = expType.Explore("../part_2/test/test3");
*/
    //for(auto& it : *pointer)
    //{
    //    QTextStream(stdout) << it.name_ << ' ' << it.size_ << ' ' << it.percent_ << endl <<flush;
    //}
/*
    QString t = QString::number(float(456)/10);
    QTextStream(stdout) << t;*/
    return 0;
}
