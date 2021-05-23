#include "../header_files/header.hpp"

MainImageGUI::MainImageGUI(){}

cv::Mat MainImageGUI::readImage(string imagePath){
    cv::Mat image = cv::imread(imagePath, IMREAD_GRAYSCALE);
    return image;
}

int MainImageGUI::init(){
    this->resize(1000, 700);
    widget = new QWidget(this);
    layout = new QGridLayout(widget);

    this->setCentralWidget(widget);
    widget->setLayout(layout);

    // --- ROW 0

    QGroupBox *boxImage = new QGroupBox("Imagen", widget);
    layout->addWidget(boxImage, 0, 0);
    QVBoxLayout *boxLayoutImage = new QVBoxLayout(boxImage);
    QWidget* imageChooserWidget = new QWidget(boxImage);
    boxLayoutImage->addWidget(imageChooserWidget);

    QHBoxLayout *imageChooserLayout = new QHBoxLayout(imageChooserWidget);
    QLabel *dirLabel = new QLabel("Directorio:");
    imageChooserLayout->addWidget(dirLabel);
    imagePath = new QLineEdit();
    imageChooserLayout->addWidget(imagePath);
    
    imageChooserButton = new QPushButton("Escoger Imagen", imageChooserWidget);
    connect(imageChooserButton, &QPushButton::released,this, &MainImageGUI::handleImageChooserButton);
    imageChooserLayout->addWidget(imageChooserButton);

    // --- ROW 1

    QGroupBox *box = new QGroupBox("Kernel", widget);
    layout->addWidget(box, 1, 0);
    QVBoxLayout *boxLayout = new QVBoxLayout(box);
    QWidget* kernelWidget = new QWidget(box);
    boxLayout->addWidget(kernelWidget);

    QHBoxLayout *kernelLayout = new QHBoxLayout(kernelWidget);
    kernelLayout->addWidget(new QLabel("Cantidad:"));
    kernelSize = new QLineEdit(kernelWidget);
    kernelLayout->addWidget(kernelSize);
    
    kernelButton = new QPushButton("Aplicar Operaciones", kernelWidget);
    connect(kernelButton, &QPushButton::released,this, &MainImageGUI::handleButton);
    kernelLayout->addWidget(kernelButton);

    // ROW 2

    imageBox = new QGroupBox("Imágenes", widget);
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(imageBox);
    layout->addWidget(scrollArea, 2, 0);

    imageLayout = new QGridLayout(imageBox);
    imageWidget = new QWidget(imageBox);

    
    imageLayout->addWidget(imageWidget);

    this->show();
    return 0;
}

void MainImageGUI::addImageToWidget(cv::Mat image, QString title, int r, int c){

    double ws = ((double)w * 0.3);
    double hs = (ws / image.cols) * image.rows;

    cv::resize(image, image, Size(abs(ws), abs(hs)));

    Mat dest;
    QWidget *widgetT = new QWidget(imageWidget);
    QVBoxLayout *layoutT = new QVBoxLayout(widgetT);

    QLabel *myLabel = new QLabel(widgetT);
    QLabel *titleLabel = new QLabel(title);
    
    cvtColor(image, dest, COLOR_GRAY2RGB);
    QImage image1 = QImage((uchar*) dest.data, dest.cols, dest.rows, dest.step, QImage::Format_RGB888);
    myLabel->setPixmap(QPixmap::fromImage(image1));

    layoutT->addWidget(titleLabel);
    layoutT->addWidget(myLabel);

    imageLayout->addWidget(widgetT, r, c);
}

void MainImageGUI::applyAll(){
    processedImages.clear();
    processedImages.push_back(Image(original, "Original", 0, 0));
    processedImages.push_back(Image(mo.applyErosion(original), "Erosion", 0, 1));
    processedImages.push_back(Image(mo.applyDilatation(original), "Dilatation", 0, 2));
    processedImages.push_back(Image(mo.applyTopHat(original), "Top Hat", 1, 0));
    processedImages.push_back(Image(mo.applyBlackHat(original), "Black Hat", 1, 1));
    processedImages.push_back(Image(mo.applyEquation(original), "Equation", 1, 2));
    showImages();
}

void MainImageGUI::showImages(){
    QRect geometry = imageLayout->geometry();
    w = geometry.width();
    clearLayout(imageLayout);
    imageWidget = new QWidget(imageBox);
    imageLayout->addWidget(imageWidget);
    for (int i = 0; i < processedImages.size(); i++){
        addImageToWidget(processedImages[i].image, QString::fromStdString(processedImages[i].title), 
            processedImages[i].r, processedImages[i].c);
    }
}

void MainImageGUI::handleButton(){
    try {
        if (imagePath->text().toStdString().empty()) {
            throw(20);
        }
        mo.createKernel(kernelSize->text().toInt());
        this->original = readImage(imagePath->text().toStdString());
        applyAll();
    }catch (int e) {
        if (e == 20) {
            QMessageBox messageBox;
            messageBox.critical(0,"Error", "Seleccione una imagen");
            messageBox.setFixedSize(500,200);
        } else {
            QMessageBox messageBox;
            messageBox.critical(0,"Error", "El valor del Kernel tiene que ser impar y mayor a cero");
            messageBox.setFixedSize(500,200);
        }
    }catch (exception& e){
        QMessageBox messageBox;
        messageBox.critical(0,"Error", "Error al procesar la imagen");
        messageBox.setFixedSize(500,200);
    }
}

void MainImageGUI::handleImageChooserButton(){
    imagePath->setText(QFileDialog::getOpenFileName(this,
        tr("Seleccione una Imagen"), "../", tr("Image Files (*.png *.jpg *.jpeg *.bmp)")));
}

void MainImageGUI::clearLayout(QLayout *layout) {
    QLayoutItem* child;
    while (layout->count() != 0) {
        child = layout->takeAt ( 0 );
        if (child->layout() != 0) {
            clearLayout ( child->layout() );
        } else if ( child->widget() != 0 ) {
            delete child->widget();
        }
        delete child;
    }
}

void MainImageGUI::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    showImages();
}