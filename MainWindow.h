#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>
#include "DarknetHelper.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_newProject_triggered();

    void on_action_imageMark_triggered();

    void on_action_setting_triggered();

    void newPorject(const QString &path);
private:
    Ui::MainWindow *ui;

    DarknetHelper m_helper;
    QFileSystemModel *m_model;
};
#endif // MAINWINDOW_H
