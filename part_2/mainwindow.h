#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>
#include "infomodel.h"

// Forward declaration на класс сгенерированный на основе ui представления
// mainwindow
namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    // Слот для обработки выбора директории
    void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);

    // Слот для обработки выбора стратегий
    void on_group_bottom(const int& type);

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    // Указатель на объект формы пользовательского интерфейса
    Ui::MainWindow* ui_window;
    // Указатель
    QFileSystemModel *fileModel;
};

