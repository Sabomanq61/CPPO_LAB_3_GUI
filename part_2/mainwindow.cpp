#include "mainwindow.h"
#include <QFileSystemModel>
#include "ui_mainwindow.h"
#include "type_strategy.h"
#include "folder_strategy.h"

#include <QDebug>

std::shared_ptr<ExplorerStrategy::FileList> Explore(const int& type, const QString& path)
{
    if(type == 0)
    {
        QTextStream(stdout) <<"Group by type " << path << endl << flush;
        StrategyType explorer;
        auto result = explorer.Explore(path);
        for(auto it: *result)
        {
            QTextStream(stdout) << it.name_ <<' ' << it.size_ << ' ' << it.percent_ << endl <<flush;
        }
        return result;
    }
    else
    {
        QTextStream(stdout) <<"Group by folder " << path << endl << flush;
        StrategyFolder explorer;
        auto result = explorer.Explore(path);
        for(auto it: *result)
        {
            QTextStream(stdout) << it.name_ <<' ' << it.size_ << ' ' << it.percent_ << endl <<flush;
        }
        return result;
    }
    return nullptr;
}

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

    ui_window->treeView->setModel(fileModel);
    ui_window->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(ui_window->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::on_selectionChangedSlot);

    connect(ui_window->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_group_bottom);
}

void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    on_group_bottom(ui_window->comboBox->currentIndex());
}

void MainWindow::on_group_bottom(const int& type)
{
    QModelIndexList list = ui_window->treeView->selectionModel()->selectedIndexes();
    if(!list.empty())
    {
        auto index = list[0];

        QString path =  fileModel->filePath(index);

        switch (type)
        {
        case 0:
            ui_window->tableView->setModel(new InfoModel(nullptr, Explore(0, path)));
            break;
        case 1:
            ui_window->tableView->setModel(new InfoModel(nullptr, Explore(1, path)));
            break;
        default:
            break;
        }
    }
}

MainWindow::~MainWindow()
{
    delete fileModel;
    delete ui_window;
}
