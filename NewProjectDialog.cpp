#include "NewProjectDialog.h"
#include "ui_NewProjectDialog.h"
#include <QFileDialog>
#include <QSettings>
#include <QDir>
#include <QDebug>
#include "DarknetHelper.h"

NewProjectDialog::NewProjectDialog(DarknetHelper * helper,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog),
    m_helper(helper)
{
    ui->setupUi(this);

    QSettings s;
    auto path = s.value("newProjectPath","/").toString();
    ui->lineEdit_create_path->setText(path);
    ui->lineEdit_name->setText("untitled");

    QString program = QSettings().value("DarknetConfig","./DarknetConfig.exe").toString();
    if(!program.contains("DarknetConfig.exe")){
        ui->label_darknetConfig->show();
    }else{
        ui->label_darknetConfig->hide();
    }

}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}

void NewProjectDialog::on_pushButton_finish_clicked()
{
    auto path = ui->lineEdit_create_path->text();
    auto filename = ui->lineEdit_name->text();

    if(QDir(path).exists(filename)){
        return;
    }

    QString program = QSettings().value("DarknetConfig","./DarknetConfig.exe").toString();
    if(!program.contains("DarknetConfig.exe")){
        return;
    }

    if(!path.isEmpty() || !filename.isEmpty()){
        // 运行 DarknetConfig.exe 脚手架
        m_helper->setPath(path + "/" + filename);
        m_helper->setBatch(ui->lineEdit_batch->text().toInt());
        m_helper->setSubdivision(ui->lineEdit_subdivision->text().toInt());
        m_helper->setClasses(ui->lineEdit_classes->text().toInt());
        m_helper->setType(ui->comboBox_type->currentIndex());
        m_helper->setWidth(ui->lineEdit_width->text().toInt());
        m_helper->setHeight(ui->lineEdit_height->text().toInt());
        m_helper->run();
        m_helper->setInit(true);

        emit newProject(m_helper->path());
    }
    close();
}

void NewProjectDialog::on_pushButton_cancel_clicked()
{
    close();
}

void NewProjectDialog::on_pushButton_browse_clicked()
{
    QSettings s;
    auto path = s.value("newProjectPath","/").toString();
    auto str = QFileDialog::getExistingDirectory(this,QStringLiteral("选择文件"),path);
    ui->lineEdit_create_path->setText(str);
    s.setValue("newProjectPath",str);
}

void NewProjectDialog::on_lineEdit_name_textChanged(const QString &arg1)
{
    auto path = ui->lineEdit_create_path->text();
    if(QDir(path).exists(arg1)){
        ui->label_exists->show();
    }else{
        ui->label_exists->hide();
    }
}
