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
#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DInput>
#include <Qt3DLogic>
#include <Qt3DExtras>
#include <Qt3DAnimation>
#include "surfrec_io/code/io.h"


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

    void on_transparencySlider_valueChanged(int value);

    void on_loadPushButton_clicked();

    void on_fileSelectTreeView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    int time;
    Qt3DCore::QEntity *rootEntity;
    Qt3DCore::QEntity *plyEntity;
    Qt3DCore::QEntity *sphereEntity;
    Qt3DExtras::QPhongAlphaMaterial *bodyMaterial;
    Qt3DExtras::QPhongAlphaMaterial *sphereMaterial;
    QFileSystemModel *model;
    QModelIndex selectedIndex;
};
#endif // MAINWINDOW_H
