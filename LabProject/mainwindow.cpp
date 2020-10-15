#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"
using Vector3f = Eigen::Matrix<float, 3, 1, Eigen::DontAlign>;

/*Constructor: Sets up the UI and the QTreeView on the left to show files on the local
machine starting in C:/ */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QFileSystemModel;
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

    cameraEntity = view->camera();

    //Set up camera
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(-3.5f, 3.5f, 0));
    cameraEntity->setUpVector(QVector3D(0,1,0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

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
    camController->setLinearSpeed(1.4f);
    camController->setLookSpeed(75.0f);

    //Loading .ply data
    QUrl data = QUrl("qrc:/resources/airplane.ply");
    qDebug() << data << data.isValid();
    Qt3DRender::QMesh *sceneLoader = new Qt3DRender::QMesh();
    sceneLoader->setMeshName("bodyMesh");
    sceneLoader->setSource(data);

    Qt3DCore::QTransform *bodyTransform = new Qt3DCore::QTransform();
    bodyTransform->setScale3D(QVector3D(0.2, 0.2, 0.2));
    bodyTransform->setTranslation(QVector3D(0, 0, 0));

    bodyMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    bodyMaterial->setDiffuse(QColor(255, 0, 0, 127));

    plyEntity = new Qt3DCore::QEntity(rootEntity);
    plyEntity->addComponent(sceneLoader);
    plyEntity->addComponent(bodyMaterial);
    plyEntity->addComponent(bodyTransform);

    //Set root Object of the scene
    view->setRootEntity(rootEntity);

    sphereMesh = new Qt3DExtras::QSphereMesh();
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

void MainWindow::on_fileSelectTreeView_clicked(const QModelIndex &index)
{
    selectedIndex = index;
}

void MainWindow::on_loadPushButton_clicked()
{
    QString filePath = model->fileInfo(selectedIndex).absoluteFilePath();
    if (filePath.back() == "k" && filePath.at(filePath.size()-2) == "t" && filePath.at(filePath.size()-3) == "v" && filePath.at(filePath.size()-4) == ".") {
        std::string stringFilePath = filePath.toStdString();
        std::vector<Vector3f> particleVector = io::read_particles_from_vtk(stringFilePath);
        int numParticles = particleVector.size();
        ui->numberParticlesLabel_2->setNum(numParticles);

        QVector<Qt3DCore::QEntity*> sphereVector(numParticles);
        QVector<Qt3DCore::QTransform*> sphereTransVector(numParticles);

        sphereMaterial = new Qt3DExtras::QDiffuseSpecularMaterial();
        sphereMaterial->setAlphaBlendingEnabled(false);
        sphereMaterial->setDiffuse(QColor(0, 255, 0, 255));

        sphereMesh->setRings(3);
        sphereMesh->setSlices(3);
        sphereMesh->setRadius(0.02);

        for (int i=0; i<numParticles; i++) {
            sphereTransVector[i] = new Qt3DCore::QTransform();
            sphereTransVector[i]->setTranslation(QVector3D(particleVector[i](2), particleVector[i](1), particleVector[i](0)));
            sphereVector[i] = new Qt3DCore::QEntity(rootEntity);
            sphereVector[i]->addComponent(sphereMesh);
            sphereVector[i]->addComponent(sphereMaterial);
            sphereVector[i]->addComponent(sphereTransVector[i]);
        }
    }
    else if (filePath.back() == "o" && filePath.at(filePath.size()-2) == "e" && filePath.at(filePath.size()-3) == "g"
            && filePath.at(filePath.size()-4) == "b" && filePath.at(filePath.size()-5) == ".") {
        std::string stringFilePath = filePath.toStdString();
        std::vector<Vector3f> particleVector = io::read_particles_from_bgeo(stringFilePath);
        int numParticles = particleVector.size();
        ui->numberParticlesLabel_2->setNum(numParticles);

        QVector<Qt3DCore::QEntity*> sphereVector(numParticles);
        QVector<Qt3DCore::QTransform*> sphereTransVector(numParticles);

        sphereMaterial = new Qt3DExtras::QDiffuseSpecularMaterial();
        sphereMaterial->setAlphaBlendingEnabled(false);
        sphereMaterial->setDiffuse(QColor(0, 255, 0, 255));

        sphereMesh->setRings(3);
        sphereMesh->setSlices(3);
        sphereMesh->setRadius(0.02);

        for (int i=0; i<numParticles; i++) {
            sphereTransVector[i] = new Qt3DCore::QTransform();
            sphereTransVector[i]->setTranslation(QVector3D(particleVector[i](2), particleVector[i](1), particleVector[i](0)));
            sphereVector[i] = new Qt3DCore::QEntity(rootEntity);
            sphereVector[i]->addComponent(sphereMesh);
            sphereVector[i]->addComponent(sphereMaterial);
            sphereVector[i]->addComponent(sphereTransVector[i]);
        }
    }
    else {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Please select a .vtk, .bgeo or .ply file");
        errorMessage.exec();
    }

}



void MainWindow::on_resetCamPushButton_clicked()
{
    cameraEntity->setPosition(QVector3D(-3.5f, 3.5f, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));
    cameraEntity->setUpVector(QVector3D(0,1,0));
}

void MainWindow::on_particlesCheckBox_stateChanged(int arg1)
{
    if (arg1 == 0) {
        sphereMesh->setEnabled(false);
    }
    if(arg1 == 2) {
        sphereMesh->setEnabled(true);
    }
}
