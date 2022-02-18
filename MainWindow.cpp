#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "NewProjectDialog.h"
#include "ImageMarkWindow.h"
#include "SettingDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_model = new QFileSystemModel(this);
    ui->treeView->setModel(m_model);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);

    QSettings s;
    auto init = s.value("darknethelper_init",false).toBool();
    if(init){
        auto path = s.value("darknethelper_path","./").toString();
        m_model->setRootPath(path);
        ui->treeView->setRootIndex(m_model->index(path));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_newProject_triggered()
{
    NewProjectDialog w(&m_helper);
    QObject::connect(&w,&NewProjectDialog::newProject,this,&MainWindow::newPorject);
    w.exec();
}

void MainWindow::on_action_imageMark_triggered()
{
    QEventLoop e;
    auto w = new ImageMarkWindow(&m_helper,this);
    QObject::connect(w,&ImageMarkWindow::destroyed,&e,&QEventLoop::quit);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
    e.exec();
}

void MainWindow::on_action_setting_triggered()
{
    SettingDialog w;
    w.exec();
}

void MainWindow::newPorject(const QString &path)
{
    m_model->setRootPath(path);
    ui->treeView->setRootIndex(m_model->index(path));
}

