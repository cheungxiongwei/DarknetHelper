#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include <QFileDialog>
#include <QSettings>

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    QSettings s;
    auto filename = s.value("DarknetConfig","").toString();
    ui->lineEdit_darknet_helper_filename->setText(filename);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButton_brower_clicked()
{
    QSettings s;
    auto path = s.value("newProjectPath","/").toString();
    auto str = QFileDialog::getOpenFileName(this,QStringLiteral("选择 DarknetConfig 文件"),path);
    ui->lineEdit_darknet_helper_filename->setText(str);
    s.setValue("DarknetConfig",str);
}
