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
}
