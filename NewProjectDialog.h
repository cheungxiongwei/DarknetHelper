#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class NewProjectDialog;
}

class DarknetHelper;
class NewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewProjectDialog(DarknetHelper * helper,QWidget *parent = nullptr);
    ~NewProjectDialog();
signals:
    void newProject(const QString &path);
private slots:
    void on_pushButton_finish_clicked();
    void on_pushButton_cancel_clicked();
    void on_pushButton_browse_clicked();
    void on_lineEdit_name_textChanged(const QString &arg1);

private:
    Ui::NewProjectDialog *ui;
    DarknetHelper *m_helper;
};

#endif // NEWPROJECTDIALOG_H
