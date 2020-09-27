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

    //Set up viewport
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x607B8B)));
    QWidget *container = QWidget::createWindowContainer(view);
    QSize screenSize = view->screen()->size();
    container->setMinimumSize(QSize(200, 100));
    container->setMaximumSize(screenSize);

    ui->viewportLayout->addWidget(container);

    Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
    view->registerAspect(input);

    //Root entity
    rootEntity = new Qt3DCore::QEntity();

    Qt3DRender::QCamera *cameraEntity = view->camera();

    //Set up camera
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(-500, 0, 500.f));
    cameraEntity->setUpVector(QVector3D(0,0,1));
    cameraEntity->setViewCenter(QVector3D(0, -200, 200));

    //Set up light
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);

    //Set up camera controls
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setCamera(cameraEntity);
    camController->setLinearSpeed(200);
    camController->setLookSpeed(180.0f);

    //Loading .ply data
    QUrl data = QUrl("qrc:/resources/airplane.ply");
    qDebug() << data << data.isValid();
    Qt3DRender::QMesh *bodyMesh = new Qt3DRender::QMesh();
    bodyMesh->setMeshName("bodyMesh");
    bodyMesh->setSource(data);

    Qt3DCore::QTransform *bodyTransform = new Qt3DCore::QTransform;
    bodyTransform->setScale3D(QVector3D(0.2, 0.2, 0.2));

    bodyMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    bodyMaterial->setDiffuse(QColor(255, 0, 0, 127));

    plyEntity = new Qt3DCore::QEntity(rootEntity);
    plyEntity->addComponent(bodyMesh);
    plyEntity->addComponent(bodyMaterial);
    plyEntity->addComponent(bodyTransform);

    //Set root Object of the scene
    view->setRootEntity(rootEntity);
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

void MainWindow::on_transparencySlider_valueChanged(int value)
{
    bodyMaterial->setAlpha(value/100.0f);
}
