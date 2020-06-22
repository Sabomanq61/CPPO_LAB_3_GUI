#include "mainwindow.h"
#include <QFileSystemModel>
#include "ui_mainwindow.h"
#include "type_strategy.h"
#include "folder_strategy.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui_window(new Ui::MainWindow)
{
    ui_window->setupUi(this);
    //Устанавливаем размер главного окна
    this->setGeometry(100, 100, 1500, 500);
    this->setStatusBar(new QStatusBar(this));
    this->statusBar()->showMessage("Choosen Path: ");

    //
    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
    fileModel->setRootPath(QDir::currentPath());

    //
    tableModel = new InfoModel(this, nullptr);


    ui_window->treeView->setModel(fileModel);
    ui_window->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui_window->tableView->setModel(tableModel);
    //connect(ui_window->treeView->selectionModel(),)
    connect(ui_window->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_group_bottom);
}

void MainWindow::on_group_bottom(const int& type)
{
    switch (type)
    {
    case 0:
    {
        explore = new StrategyFolder;
        tableModel->SetInfo(explore->Explore());
    }
    case 1:
        tableModel->SetInfo(nullptr);
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete fileModel;
    delete ui_window;
}
