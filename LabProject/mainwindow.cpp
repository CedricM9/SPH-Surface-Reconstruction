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

    QSurfaceFormat format;
    format.setStereo(true); // Disables anti-aliasing, but is definitely weird
    QSurfaceFormat::setDefaultFormat(format);

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
    QUrl data = QUrl("qrc:/resources/cow.ply");
    qDebug() << data << data.isValid();
    surfaceMesh = new Qt3DRender::QMesh();
    surfaceMesh->setMeshName("surfaceMesh");
    surfaceMesh->setSource(data);

    surfaceTransform = new Qt3DCore::QTransform();
    surfaceTransform->setScale3D(QVector3D(1, 1, 1));
    surfaceTransform->setTranslation(QVector3D(0, 0, 0));
    surfaceTransform->setRotationY(180.0f);

    surfaceMaterial = new Qt3DExtras::QDiffuseSpecularMaterial();
    surfaceMaterial->setAlphaBlendingEnabled(false);
    surfaceMaterial->setDiffuse(QColor(255, 0, 0, 255));

    surfaceEntity = new Qt3DCore::QEntity(rootEntity);
    surfaceEntity->addComponent(surfaceMesh);
    surfaceEntity->addComponent(surfaceMaterial);
    surfaceEntity->addComponent(surfaceTransform);

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
    surfaceMaterial->setDiffuse(QColor(255, 0, 0, (100-value)*2.55f));
    surfaceMaterial->setSpecular(QColor(255, 0, 0, (100-value)*2.55f));
}

void MainWindow::on_fileSelectTreeView_clicked(const QModelIndex &index)
{
    selectedIndex = index;
}

void MainWindow::on_loadPushButton_clicked()
{
    QString filePath = model->fileInfo(selectedIndex).absoluteFilePath();
    if (filePath.back() == "k" && filePath.at(filePath.size()-2) == "t" && filePath.at(filePath.size()-3) == "v"
            && filePath.at(filePath.size()-4) == ".") {
        loadParticleData(filePath);
    }
    else if (filePath.back() == "o" && filePath.at(filePath.size()-2) == "e" && filePath.at(filePath.size()-3) == "g"
            && filePath.at(filePath.size()-4) == "b" && filePath.at(filePath.size()-5) == ".") {
        loadParticleData(filePath);
    }
    else if (filePath.back() == "y" && filePath.at(filePath.size()-2) == "l" && filePath.at(filePath.size()-3) == "p"
            && filePath.at(filePath.size()-4) == ".") {
        loadSurfaceData(filePath);
    }
    else {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Please select a .vtk, .bgeo or .ply file");
        errorMessage.exec();
    }

}

//Loads and displays particles from .bgeo or .vtk file format
void MainWindow::loadParticleData(QString filePath)
{
    int numParticles = 0;
    std::vector<Vector3f> particleVector;
    if (filePath.back() == "k" && filePath.at(filePath.size()-2) == "t" && filePath.at(filePath.size()-3) == "v"
            && filePath.at(filePath.size()-4) == ".") {
        std::string stringFilePath = filePath.toStdString();
        particleVector = io::read_particles_from_vtk(stringFilePath);
    }
    else if (filePath.back() == "o" && filePath.at(filePath.size()-2) == "e" && filePath.at(filePath.size()-3) == "g"
            && filePath.at(filePath.size()-4) == "b" && filePath.at(filePath.size()-5) == ".") {
        std::string stringFilePath = filePath.toStdString();
        particleVector = io::read_particles_from_bgeo(stringFilePath);
    }

    numParticles = particleVector.size();
    ui->numberParticlesLabel_2->setNum(numParticles);

    //If the number of particles did not change, the particles will only be moved
    if (numParticles == sphereVector.size() && sphereVector.isEmpty() == false) {
        for (int i=0; i<numParticles; i++) {
            sphereTransVector[i]->setTranslation(QVector3D(particleVector[i](2), particleVector[i](1), particleVector[i](0)));
        }
    }

    //If there were no particles at all before, the particles will be initialized
    else if(sphereVector.isEmpty() == true) {
                sphereVector.resize(numParticles);
                sphereTransVector.resize(numParticles);

                sphereMaterial = new Qt3DExtras::QDiffuseSpecularMaterial();
                sphereMaterial->setAlphaBlendingEnabled(false);
                sphereMaterial->setDiffuse(QColor(0, 255, 0, 255));

                sphereMesh->setRings(2);
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

    //If there are more particles than before, the new ones will be initialized, while the old ones will be moved
    else if (numParticles > sphereVector.size()) {
        int oldNumParticles = sphereVector.size();
        sphereVector.resize(numParticles);
        sphereTransVector.resize(numParticles);
        for (int i = 0; i<oldNumParticles; i++) {
            sphereTransVector[i]->setTranslation(QVector3D(particleVector[i](2), particleVector[i](1), particleVector[i](0)));
        }
        for (int i = oldNumParticles; i<numParticles; i++) {
            sphereTransVector[i] = new Qt3DCore::QTransform();
            sphereTransVector[i]->setTranslation(QVector3D(particleVector[i](2), particleVector[i](1), particleVector[i](0)));
            sphereVector[i] = new Qt3DCore::QEntity(rootEntity);
            sphereVector[i]->addComponent(sphereMesh);
            sphereVector[i]->addComponent(sphereMaterial);
            sphereVector[i]->addComponent(sphereTransVector[i]);
        }
    }

    //If there are less particles than before, the superflous ones will be made invisible, while the others will be moved
    else if (numParticles < sphereVector.size()) {
        for (int i = numParticles; i<sphereVector.size(); i++) {
            sphereVector[i]->setEnabled(false);
        }
        for (int i = 0; i<numParticles; i++) {
            sphereTransVector[i]->setTranslation(QVector3D(particleVector[i](2), particleVector[i](1), particleVector[i](0)));
        }
    }
}

//Loads and displays surface mesh from .ply file format
void MainWindow::loadSurfaceData(QString filePath)
{
    QUrl fileUrl = QUrl::fromLocalFile(QFileInfo(filePath).absoluteFilePath());
    surfaceMesh->setSource(fileUrl);
    surfaceTransform->setRotationY(0.0f);
}

//PushButton resets the camera to default position and angle
void MainWindow::on_resetCamPushButton_clicked()
{
    cameraEntity->setPosition(QVector3D(-3.5f, 3.5f, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));
    cameraEntity->setUpVector(QVector3D(0,1,0));
}

//Checkbox makes particles visible/invisible
void MainWindow::on_particlesCheckBox_stateChanged(int arg1)
{
    if (arg1 == 0) {
        sphereMesh->setEnabled(false);
    }
    if(arg1 == 2) {
        sphereMesh->setEnabled(true);
    }
}

void MainWindow::on_prevFramePushButton_clicked()
{
    selectedIndex = ui->fileSelectTreeView->indexAbove(selectedIndex);
    on_loadPushButton_clicked();
}

void MainWindow::on_nextFramePushButton_clicked()
{
    selectedIndex = ui->fileSelectTreeView->indexBelow(selectedIndex);
    on_loadPushButton_clicked();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (arg1 == 0) {
        surfaceMaterial->setAlphaBlendingEnabled(false);
    }
    if(arg1 == 2) {
        surfaceMaterial->setAlphaBlendingEnabled(true);
    }
}
