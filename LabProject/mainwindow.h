#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QFile>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QTreeView>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateTimeElapsed();

private slots:

    void on_batchJobPushButton_clicked();

    void on_reconstructPushButton_clicked();

    void on_exportPushButton_clicked();

private:
    Ui::MainWindow *ui;
    int time;
};
#endif // MAINWINDOW_H
