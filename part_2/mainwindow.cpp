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

    //Инициализаця модели для представления дерикторий
    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
    fileModel->setRootPath(QDir::currentPath());

    ui_window->treeView->setModel(fileModel);

    // Устанавливаем автоматический расчет секции в зависимости от длины названия элемента
    ui_window->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui_window->treeView->expandAll();
    //По умолчанию отоброжаем сведения о текущей директории с
    ui_window->tableView->setModel(new InfoModel(nullptr, Explore(0, QDir::currentPath())));
    //Соединение слотов
    connect(ui_window->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::on_selectionChangedSlot);

    // Соединение сигнала выбора группировки с его обработкой
    connect(ui_window->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_group_bottom);
}

void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    // Вызов слота для стратегий с заданной стратегией
    on_group_bottom(ui_window->comboBox->currentIndex());
}

void MainWindow::on_group_bottom(const int& type)
{
    // Получаем индекс выбранной директории
    QModelIndexList list = ui_window->treeView->selectionModel()->selectedIndexes();
    //Проверка на то, что в дереве выбрана директория
    if(!list.empty())
    {
        // Получаем путь к директории
        auto index = list[0];
        QString path =  fileModel->filePath(index);

        // Выбор стратегий
        switch (type)
        {
        case 0:
        {
            // Удаляем старую модель и выставляем новую
            QItemSelectionModel *m = ui_window->tableView->selectionModel();

            ui_window->tableView->setModel(new InfoModel(nullptr, Explore(0, path)));
            delete m;
            break;
        }
        case 1:
        {
            // Удаляем старую модель и выставляем новую
            QItemSelectionModel *m = ui_window->tableView->selectionModel();
            ui_window->tableView->setModel(new InfoModel(nullptr, Explore(1, path)));
            delete m;
            break;
        }
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
