#include "ImageMarkWindow.h"
#include "ui_ImageMarkWindow.h"

ImageMarkWindow::ImageMarkWindow(DarknetHelper *helper,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageMarkWindow),
    m_helper(helper)
{
    ui->setupUi(this);
    QObject::connect(ui->listView,&ImageMarkListView::currentFilename,ui->openGLWidget,&ImageMarkWidget::currentFilename);
    auto path = m_helper->objPath();
    m_model = new QFileSystemModel(this);
    m_model->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    m_model->setNameFilters({"*.png","*.jpg","*.bmp"});
    m_model->setNameFilterDisables(false);

    m_model->setRootPath(path);

    ui->listView->setFlow(QListView::LeftToRight);
    ui->listView->setItemDelegate(new ItemDelegate(m_helper,ui->listView));

    ui->listView->setModel(m_model);
    ui->listView->setRootIndex(m_model->index(path));
    ui->openGLWidget->setDarknetHelper(m_helper);
    ui->openGLWidget->setLabels(ui->listView_label);
    QObject::connect(this,&ImageMarkWindow::clearMark,ui->openGLWidget,&ImageMarkWidget::clearMark);
    QObject::connect(this,&ImageMarkWindow::switchLabel,ui->openGLWidget,&ImageMarkWidget::switchLabel);

    // 添加标签
    // 哈希颜色
    QStringList labels;
    QFile data(m_helper->objNamesFilename());
    if (data.open(QFile::ReadOnly)) {
        QTextStream in(&data);
        QString line;
        while (in.readLineInto(&line)) {
            labels.append(line);
        }
    }

    auto model = new QStringListModel(labels,this);
    ui->listView_label->setModel(model);
    if(model->index(0).isValid()){
        ui->listView_label->setCurrentIndex(model->index(0));
    }
    ui->groupBox_image_info->hide();
}

ImageMarkWindow::~ImageMarkWindow()
{
    // 存储标签
    auto model = qobject_cast<QStringListModel*>(ui->listView_label->model());
    if(model){
        QStringList labels = model->stringList();
        QFile data(m_helper->objNamesFilename());
        if (data.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
            QTextStream out(&data);
            for(auto &s:labels){
                out << s << "\n";
            }
        }
    }
    delete ui;
}
