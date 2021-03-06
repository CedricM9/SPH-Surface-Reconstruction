#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SurfaceReconstruction/data/particle_list.h"
#include "SurfaceReconstruction/data/triangle_list.h"
#include "SurfaceReconstruction/in/partio_particle_reader.h"
#include "SurfaceReconstruction/in/vtk_particle_reader.h"
#include "SurfaceReconstruction/in/ply_triangle_reader.h"
#include "SurfaceReconstruction/in/vtk_triangle_reader.h"
#include "SurfaceReconstruction/out/ply_triangle_writer.h"
#include "SurfaceReconstruction/out/vtk_triangle_writer.h"
#include "SurfaceReconstruction/alg/nsearch/spatial_hashing_neighborhood_search.h"
#include "SurfaceReconstruction/alg/kernel/cubic_spline_kernel.h"
#include "SurfaceReconstruction/alg/kernel/spiky_kernel.h"
#include "SurfaceReconstruction/alg/level/dimensionless_level_set_function.h"
#include "SurfaceReconstruction/alg/marching_cubes_reconstructor.h"
#include "SurfaceReconstruction/alg/post/open_mesh_processor.h"
#include "SurfaceReconstruction/create_batch_job_script.h"

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

    //Disable Anti-Aliasing
    QSurfaceFormat format;
    format.setStereo(true);
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

    camera = view->camera();

    //Set up camera
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 3.5f, 3.5f));
    camera->setUpVector(QVector3D(0,1,0));
    camera->setViewCenter(QVector3D(0, 0, 0));

    //Set up light
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(camera->position());
    lightEntity->addComponent(lightTransform);

    //Set up camera controls
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setCamera(camera);
    camController->setLinearSpeed(1.4f);
    camController->setLookSpeed(75.0f);

    //Loading .ply data
    QUrl data = QUrl("qrc:/resources/TestData/cow.ply");
    qDebug() << data << data.isValid();
    surfaceMesh = new Qt3DRender::QMesh();
    surfaceMesh->setMeshName("surfaceMesh");
    surfaceMesh->setSource(data);

    surfaceTransform = new Qt3DCore::QTransform();
    surfaceTransform->setScale3D(QVector3D(1, 1, 1));
    surfaceTransform->setTranslation(QVector3D(0, 0, 0));
    surfaceTransform->setRotationY(270.0f);

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

//When the Button "Generate Batch Job..." is clicked, Messageboxes will ask for specifcs and the batch job is generated to the export directory
void MainWindow::on_batchJobPushButton_clicked()
{
    if(outputFolder.isEmpty()==true) {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Please select an export directory.");
        errorMessage.exec();
    }
    else {
        bool correctFormat = false;
        inputPath = model->fileInfo(selectedIndex).absoluteFilePath();

        //Set correct input format
        std::string inputFormat;
        if (inputPath.back() == "k" && inputPath.at(inputPath.size()-2) == "t" && inputPath.at(inputPath.size()-3) == "v"
                && inputPath.at(inputPath.size()-4) == ".") {
            inputFormat = "vtk";
            correctFormat = true;
        }
        else if (inputPath.back() == "o" && inputPath.at(inputPath.size()-2) == "e" && inputPath.at(inputPath.size()-3) == "g"
                    && inputPath.at(inputPath.size()-4) == "b" && inputPath.at(inputPath.size()-5) == ".") {
            inputFormat = "bgeo";
            correctFormat = true;
        }

        if(correctFormat == false) {
            QErrorMessage errorMessage;
            errorMessage.showMessage("Please select a .vtk or .bgeo file");
            errorMessage.exec();
        } else{
            int batchTime = QInputDialog::getInt(this, "Maximum Time", "State the maximum execution time of the batch script in minutes:", 60, 1);
            int batchMemory = QInputDialog::getInt(this, "Requested Memory", "State the memory the batch script requests for execution in MB", 512, 512, 2147483647, 16);

            std::string inputFolder = model->fileInfo(selectedIndex).absoluteFilePath().toStdString();
            int slash = inputFolder.find_last_of("/");
            inputFolder = inputFolder.substr(0, slash);

            //Set correct output format
            std::string outputFormat;
            if (ui->exportFormatComboBox->currentIndex()==0) {
                outputFormat = "ply";
            } else if (ui->exportFormatComboBox->currentIndex()==1) {
                outputFormat = "vtk";
            }

            // Set correct SPH interpolation kernel.
            std::string kernel;
            if (ui->sphComboBox->currentIndex() == 0) {
                kernel= "cubicSpline";
            }

            //Set correct reconstructor, level-set function and neighborhoodsearch, filename
            std::string reconstructor = "marchingCubes";
            std::string levelFunction = "dimensionless";
            std::string neighborhoodSearch = "spatialHashing";
            std::string filename = outputFolder.first().toStdString();
            filename.append("/Surface_Reconstruction.sh");

            create_script(filename, inputFormat, outputFormat, neighborhoodSearch, kernel,
                          levelFunction, reconstructor, inputFolder,
                          outputFolder.first().toStdString(),
                          ui->smoothingDoubleSpinBox->value(),
                          ui->supportDoubleSpinBox->value(),
                          ui->isoDoubleSpinBox->value(),
                          ui->gridCellsSpinBox->value(),
                          ui->ompNumThreadsSpinBox->value(),
                          batchTime, batchMemory);
        }
    }
}

//When the Button "Reconstruct..." is clicked, a QMessageBox asks for confirmation
void MainWindow::on_reconstructPushButton_clicked()
{
    if(outputFolder.isEmpty()==true) {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Please select an export directory.");
        errorMessage.exec();
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Do you want to start the surface reconstruction"
                       " with the given parameters?");
        QPushButton *yesOneButton = msgBox.addButton(tr("Yes, reconstruct the selected frame."), QMessageBox::YesRole);
        QPushButton *yesWholeButton = msgBox.addButton(tr("Yes, reconstruct all frames in the selected folder."), QMessageBox::YesRole);
        QPushButton *noButton = msgBox.addButton(tr("No, abort."), QMessageBox::NoRole);
        msgBox.setDefaultButton(noButton);
        msgBox.setEscapeButton(noButton);
        msgBox.exec();

        if(msgBox.clickedButton() == yesOneButton) {
            ui->progressBar->setValue(1);
            /*time = 0;
            QTimer *timer = new QTimer(this);
            connect(timer, &QTimer::timeout, this, &MainWindow::updateTimeElapsed);
            timer->start(1000);
            ui->progressBar->setValue(42);*/
            reconstructOneFrame(model->fileInfo(selectedIndex).absoluteFilePath(), outputFolder.first());
            ui->progressBar->setValue(100);
        }
        if(msgBox.clickedButton() == yesWholeButton) {
            reconstructWholeSimulation(model->fileInfo(selectedIndex).absoluteFilePath(), outputFolder.first());
        }
    }
}

void MainWindow::reconstructOneFrame(QString inputPath, QString outputPath)
{
    //Create correct particle reader
    std::shared_ptr<particleReader> particleIn;
    if (inputPath.back() == "k" && inputPath.at(inputPath.size()-2) == "t" && inputPath.at(inputPath.size()-3) == "v"
            && inputPath.at(inputPath.size()-4) == ".") {
        particleIn.reset(new vtkParticleReader);
    }
    else if (inputPath.back() == "o" && inputPath.at(inputPath.size()-2) == "e" && inputPath.at(inputPath.size()-3) == "g"
            && inputPath.at(inputPath.size()-4) == "b" && inputPath.at(inputPath.size()-5) == ".") {
        particleIn.reset(new partioParticleReader);
    }

    //Create correct writer
    std::shared_ptr<triangleWriter> triangleOut;
    if (ui->exportFormatComboBox->currentIndex()==0) {
        triangleOut.reset(new plyTriangleWriter);
    } else if (ui->exportFormatComboBox->currentIndex()==1) {
        triangleOut.reset(new vtkTriangleWriter);
    }

    std::shared_ptr<compactNeighborhoodSearch> nSearchPointer;
    nSearchPointer.reset(new spatialHashingNeighborhoodSearch);

    // Create pointer to the correct SPH interpolation kernel.
    std::shared_ptr<cubicSplineKernel> kernelPointer;
    if (ui->sphComboBox->currentIndex() == 0) {
        kernelPointer.reset(new cubicSplineKernel);
    }

    // Create pointer to the correct level set function.
    std::shared_ptr<levelSetFunction> levelSetPointer;
    levelSetPointer.reset(new dimensionlessLevelSetFunction);

    // Create pointer to the correct reconstructor.
    std::shared_ptr<surfaceReconstructor> reconstructionPointer;
    reconstructionPointer.reset(new marchingCubesReconstructor);

    std::string inputFile = inputPath.toStdString();

    // Read in particles.
    particleList particles = particleIn->read(inputFile);

    std::cout << "jojo" << std::endl;


    // Reconstruct a surface using marching cubes algorithm.
    graph reconstructionGraph(particles, ui->gridCellsSpinBox->value());
    triangleList result = reconstructionPointer->reconstruct(
    reconstructionGraph, particles, ui->smoothingDoubleSpinBox->value(), ui->supportDoubleSpinBox->value(), ui->isoDoubleSpinBox->value(),levelSetPointer, nSearchPointer, kernelPointer);

    std::string outputFile = outputPath.toStdString();
    std::string outputSmoothedFile = outputFile;
    int slash = inputFile.find_last_of("/");
    int dot = inputFile.find_last_of(".");
    if (ui->exportFormatComboBox->currentIndex()==0) {
        outputFile.append(inputFile.substr(slash, dot-slash).append(".ply"));
        outputSmoothedFile.append(inputFile.substr(slash, dot-slash).append("_smoothed.ply"));
    }
    else if (ui->exportFormatComboBox->currentIndex()==1) {
        outputFile.append(inputFile.substr(slash, dot-slash).append(".vtk"));
        outputSmoothedFile.append(inputFile.substr(slash, dot-slash).append("_smoothed.vtk"));
    }



    // Write the output file.
    triangleOut->write(outputFile, result);

    //Smooth and rewrite
    //openMeshProcessor postprocessor;
    //triangleList result2 = postprocessor.smooth(result, 50);
    //triangleOut->write(outputSmoothedFile, result2);

    //Display the output file
    //loadSurfaceData(QString::fromStdString(outputFile));
}

void MainWindow::reconstructWholeSimulation(QString inputPath, QString outputPath)
{
    ui->progressBar->setValue(1);
    int slash = inputPath.lastIndexOf("/");
    inputPath.remove(slash, inputPath.length()-slash);
    QDir directory(inputPath);
    QStringList simStatesList = directory.entryList(QStringList() << "*.vtk" << "*.bgeo",QDir::Files);

    if(simStatesList.isEmpty() == true) {
        QErrorMessage errorMessage;
        errorMessage.showMessage("There are no .vtk or .bgeo files in the current directory.");
        errorMessage.exec();
    }

    else {
        float fraction = 100/simStatesList.length();
        float progress = 0;

        #pragma omp parallel for num_threads(ui->ompNumThreadsSpinBox->value()) shared(progress)
        for(int i=0; i<simStatesList.length(); i++) {
            QString simState = inputPath;
            simState.append("/");
            simState.append(simStatesList.at(i));
            reconstructOneFrame(simState, outputPath);
            progress += fraction;
            int roundedProgress = progress;
            ui->progressBar->setValue(roundedProgress);
        }
        ui->progressBar->setValue(100);
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
    if (dialog.exec()) {
        outputFolder = dialog.selectedFiles();
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
    inputPath = model->fileInfo(selectedIndex).absoluteFilePath();
    if (inputPath.back() == "k" && inputPath.at(inputPath.size()-2) == "t" && inputPath.at(inputPath.size()-3) == "v"
            && inputPath.at(inputPath.size()-4) == ".") {
        loadParticleData(inputPath);
    }
    else if (inputPath.back() == "o" && inputPath.at(inputPath.size()-2) == "e" && inputPath.at(inputPath.size()-3) == "g"
            && inputPath.at(inputPath.size()-4) == "b" && inputPath.at(inputPath.size()-5) == ".") {
        loadParticleData(inputPath);
    }
    else if (inputPath.back() == "y" && inputPath.at(inputPath.size()-2) == "l" && inputPath.at(inputPath.size()-3) == "p"
            && inputPath.at(inputPath.size()-4) == ".") {
        loadSurfaceData(inputPath);
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
    if (numParticles == sphereEntityVector.size() && sphereEntityVector.isEmpty() == false) {
        for (int i=0; i<numParticles; i++) {
            sphereTransVector[i]->setTranslation(QVector3D(particleVector[i](0), particleVector[i](1), particleVector[i](2)));
        }
    }

    //If there were no particles at all before, the particles will be initialized
    else if(sphereEntityVector.isEmpty() == true) {
                sphereEntityVector.resize(numParticles);
                sphereTransVector.resize(numParticles);

                sphereMaterial = new Qt3DExtras::QDiffuseSpecularMaterial();
                sphereMaterial->setAlphaBlendingEnabled(false);
                sphereMaterial->setDiffuse(QColor(0, 255, 0, 255));

                sphereMesh->setRings(2);
                sphereMesh->setSlices(3);
                sphereMesh->setRadius(0.02);

                for (int i=0; i<numParticles; i++) {
                    sphereTransVector[i] = new Qt3DCore::QTransform();
                    sphereTransVector[i]->setTranslation(QVector3D(particleVector[i](0), particleVector[i](1), particleVector[i](2)));
                    sphereEntityVector[i] = new Qt3DCore::QEntity(rootEntity);
                    sphereEntityVector[i]->addComponent(sphereMesh);
                    sphereEntityVector[i]->addComponent(sphereMaterial);
                    sphereEntityVector[i]->addComponent(sphereTransVector[i]);
                }
    }

    //If there are more particles than before, the new ones will be initialized, while the old ones will be moved
    else if (numParticles > sphereEntityVector.size()) {
        int oldNumParticles = sphereEntityVector.size();
        sphereEntityVector.resize(numParticles);
        sphereTransVector.resize(numParticles);
        for (int i = 0; i<oldNumParticles; i++) {
            sphereTransVector[i]->setTranslation(QVector3D(particleVector[i](0), particleVector[i](1), particleVector[i](2)));
        }
        for (int i = oldNumParticles; i<numParticles; i++) {
            sphereTransVector[i] = new Qt3DCore::QTransform();
            sphereTransVector[i]->setTranslation(QVector3D(particleVector[i](0), particleVector[i](1), particleVector[i](2)));
            sphereEntityVector[i] = new Qt3DCore::QEntity(rootEntity);
            sphereEntityVector[i]->addComponent(sphereMesh);
            sphereEntityVector[i]->addComponent(sphereMaterial);
            sphereEntityVector[i]->addComponent(sphereTransVector[i]);
        }
    }

    //If there are less particles than before, the superflous ones will be made invisible, while the others will be moved
    else if (numParticles < sphereEntityVector.size()) {
        for (int i = numParticles; i<sphereEntityVector.size(); i++) {
            sphereEntityVector[i]->setEnabled(false);
        }
        for (int i = 0; i<numParticles; i++) {
            sphereTransVector[i]->setTranslation(QVector3D(particleVector[i](0), particleVector[i](1), particleVector[i](2)));
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
    camera->setPosition(QVector3D(0, 3.5f, 3.5f));
    camera->setViewCenter(QVector3D(0, 0, 0));
    camera->setUpVector(QVector3D(0,1,0));
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

void MainWindow::on_transparencyCheckBox_stateChanged(int arg1)
{
    if (arg1 == 0) {
        surfaceMaterial->setAlphaBlendingEnabled(false);
    }
    if(arg1 == 2) {
        surfaceMaterial->setAlphaBlendingEnabled(true);
    }
}

void MainWindow::on_simplifyPushButton_clicked()
{
    if(outputFolder.isEmpty()==true) {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Please select an export directory.");
        errorMessage.exec();
    }
    else {
        bool correctFormat = false;

        inputPath = model->fileInfo(selectedIndex).absoluteFilePath();

        //Create correct triangle reader and writer
        std::shared_ptr<triangleReader> triangleIn;
        std::shared_ptr<triangleWriter> triangleOut;
        if (inputPath.back() == "k" && inputPath.at(inputPath.size()-2) == "t" && inputPath.at(inputPath.size()-3) == "v"
            && inputPath.at(inputPath.size()-4) == ".") {
            triangleIn.reset(new vtkTriangleReader);
            triangleOut.reset(new vtkTriangleWriter);
            correctFormat = true;
        }
        else if (inputPath.back() == "y" && inputPath.at(inputPath.size()-2) == "l" && inputPath.at(inputPath.size()-3) == "p"
                && inputPath.at(inputPath.size()-4) == ".") {
            triangleIn.reset(new plyTriangleReader);
            triangleOut.reset(new plyTriangleWriter);
            correctFormat = true;
        }

        if(correctFormat == false) {
            QErrorMessage errorMessage;
            errorMessage.showMessage("Please select a .vtk or .ply surface");
            errorMessage.exec();
        }
        else {
            std::string inputFile = inputPath.toStdString();

            //Read the selected surface
            triangleList rawSurface = triangleIn->read(inputFile);

            //Create Post Processor and smooth the mesh
            openMeshProcessor postprocessor;
            triangleList result = postprocessor.simplify(rawSurface);

            std::string outputFile = outputFolder.first().toStdString();
            int slash = inputFile.find_last_of("/");
            int dot = inputFile.find_last_of(".");
            if (inputPath.back() == "k" && inputPath.at(inputPath.size()-2) == "t" && inputPath.at(inputPath.size()-3) == "v"
                && inputPath.at(inputPath.size()-4) == ".") {
                outputFile.append(inputFile.substr(slash, dot-slash).append("_simplified.vtk"));
            }
            else if (inputPath.back() == "y" && inputPath.at(inputPath.size()-2) == "l" && inputPath.at(inputPath.size()-3) == "p"
                     && inputPath.at(inputPath.size()-4) == ".") {
                outputFile.append(inputFile.substr(slash, dot-slash).append("_simplified.ply"));
            }

            //Write the result
            triangleOut->write(outputFile, result);
        }
    }
}

void MainWindow::on_postSmoothingPushButton_clicked()
{
    if(outputFolder.isEmpty()==true) {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Please select an export directory.");
        errorMessage.exec();
    }
    else {
        bool correctFormat = false;
        inputPath = model->fileInfo(selectedIndex).absoluteFilePath();

        //Create correct triangle reader and writer
        std::shared_ptr<triangleReader> triangleIn;
        std::shared_ptr<triangleWriter> triangleOut;
        if (inputPath.back() == "k" && inputPath.at(inputPath.size()-2) == "t" && inputPath.at(inputPath.size()-3) == "v"
                && inputPath.at(inputPath.size()-4) == ".") {
            triangleIn.reset(new vtkTriangleReader);
            triangleOut.reset(new vtkTriangleWriter);
            correctFormat = true;
        }
        else if (inputPath.back() == "y" && inputPath.at(inputPath.size()-2) == "l" && inputPath.at(inputPath.size()-3) == "p"
                    && inputPath.at(inputPath.size()-4) == ".") {
            triangleIn.reset(new plyTriangleReader);
            triangleOut.reset(new plyTriangleWriter);
            correctFormat = true;
        }

        if(correctFormat == false) {
            QErrorMessage errorMessage;
            errorMessage.showMessage("Please select a .vtk or .ply surface");
            errorMessage.exec();
        }
        else {

            std::string inputFile = inputPath.toStdString();


            //Read the selected surface
            triangleList rawSurface = triangleIn->read(inputFile);

            std::cout << inputFile << std::endl;

            //Create Post Processor and smooth the mesh
            openMeshProcessor postprocessor;
            triangleList result = postprocessor.smooth(rawSurface, ui->postSmoothingSpinBox->value());

            std::string outputFile = outputFolder.first().toStdString();
            int slash = inputFile.find_last_of("/");
            int dot = inputFile.find_last_of(".");
            if (inputPath.back() == "k" && inputPath.at(inputPath.size()-2) == "t" && inputPath.at(inputPath.size()-3) == "v"
                    && inputPath.at(inputPath.size()-4) == ".") {
                outputFile.append(inputFile.substr(slash, dot-slash).append("_smoothed.vtk"));
            }
            else if (inputPath.back() == "y" && inputPath.at(inputPath.size()-2) == "l" && inputPath.at(inputPath.size()-3) == "p"
                        && inputPath.at(inputPath.size()-4) == ".") {
                outputFile.append(inputFile.substr(slash, dot-slash).append("_smoothed.ply"));
            }

            //Write the result
            triangleOut->write(outputFile, result);
        }
    }
}

void MainWindow::on_surfaceCheckBox_stateChanged(int arg1)
{
    if (arg1 == 0) {
        surfaceMaterial->setEnabled(false);
    }
    if(arg1 == 2) {
        surfaceMaterial->setEnabled(true);
    }
}

void MainWindow::on_testPushButton_clicked()
{
    if(outputFolder.isEmpty()==true) {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Please select an export directory.");
        errorMessage.exec();
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Do you really want to start the test reconstruction? This will reset the reconstruction parameters.");
        QPushButton *yesButton = msgBox.addButton(tr("Yes"), QMessageBox::YesRole);
        QPushButton *noButton = msgBox.addButton(tr("No"), QMessageBox::NoRole);
        msgBox.setDefaultButton(noButton);
        msgBox.setEscapeButton(noButton);
        msgBox.exec();
        ui->smoothingDoubleSpinBox->setValue(0.028);
        ui->isoDoubleSpinBox->setValue(0.355);
        ui->supportDoubleSpinBox->setValue(0.056);
        ui->gridCellsSpinBox->setValue(21);
        ui->exportFormatComboBox->setCurrentIndex(0);
        ui->sphComboBox->setCurrentIndex(0);

        if(msgBox.clickedButton() == yesButton) {

            QTemporaryDir tempDir(outputFolder.first());
            if (tempDir.isValid()) {
                QString tempFile = tempDir.path() + "/Test_Surface.bgeo";
                if (QFile::copy(":/resources/TestData/Test_Surface.bgeo", tempFile)) {
                    reconstructOneFrame(tempFile, outputFolder.first());
                }
            }
        }
    }
}

