#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"

/*Constructor: Sets up the UI and the QTreeView on the left to show files on the local
machine starting in C:/ */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath("C:/");
    ui->fileSelectTreeView->setModel(model);
}

//Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

//When the Button "Generate Batch Job..." is clicked, a QMessageBox asks for confirmation
void MainWindow::on_batchJobPushButton_clicked()
{    
    QMessageBox msgBox;
    msgBox.setText("Do you want to create a batch job for the surface reconstruction of the "
                   "selected simulation with the given parameters?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    if(ret==QMessageBox::Yes) {
        ui->progressBar->setValue(84);
    }
}

//When the Button "Reconstruct..." is clicked, a QMessageBox asks for confirmation
void MainWindow::on_reconstructPushButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Do you want to start the surface reconstruction of the selected simulation"
                   "with the given parameters?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    //If "Yes" is clicked, a QTimer calls updateTimeElapsed() every second
    if(ret==QMessageBox::Yes) {
        time = 0;
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MainWindow::updateTimeElapsed);
        timer->start(1000);
        ui->progressBar->setValue(42);

    }
}

//Increases time by 1 and sets timeLabel_2 to time
void MainWindow::updateTimeElapsed() {
    ui->timeLabel_2->setText(QString::number(++time));
}

//When the Button "Export Directory..." is clicked, a QFileDialog pops up and the user may choose a directory
void MainWindow::on_exportPushButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setViewMode(QFileDialog::List);
    QStringList fileNames;
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
    }
}
