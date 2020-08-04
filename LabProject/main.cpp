#pragma once
#include <QApplication>
#include <QFileSystemModel>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

     // Create a container window
     MainWindow window;
     window.show();
    return app.exec();
}
