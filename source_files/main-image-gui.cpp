#include "../header_files/header.hpp"

MainImageGUI::MainImageGUI(string imagePath){
    this->original = readImage(imagePath);
}

cv::Mat MainImageGUI::readImage(string imagePath){
    cv::Mat image = cv::imread(imagePath, IMREAD_GRAYSCALE);
    return image;
}

int MainImageGUI::init(){
    
    widget = new QWidget(this);
    layout = new QGridLayout(widget);

    this->setCentralWidget(widget);
    widget->setLayout(layout);

    QGroupBox *box = new QGroupBox("Kernel", widget);
    layout->addWidget(box, 0, 0);
    QVBoxLayout *boxLayout = new QVBoxLayout(box);
    QWidget* kernelWidget = new QWidget(box);
    boxLayout->addWidget(kernelWidget);

    QHBoxLayout *kernelLayout = new QHBoxLayout(kernelWidget);

    kernelLayout->addWidget(new QLabel("Cantidad:"));
    kernelSize = new QLineEdit(kernelWidget);
    kernelLayout->addWidget(kernelSize);
    
    kernelButton = new QPushButton("Validate", kernelWidget);
    connect(kernelButton, &QPushButton::released,this, &MainImageGUI::handleButton);
    kernelLayout->addWidget(kernelButton);

    imageBox = new QGroupBox("Imágenes", widget);
    layout->addWidget(imageBox, 1, 0);
    imageLayout = new QGridLayout(imageBox);
    imageWidget = new QWidget(imageBox);
    imageLayout->addWidget(imageWidget);

    this->show();
    
    return 0;
}

void MainImageGUI::addImageToWidget(cv::Mat image, QString title, int r, int c){
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

void MainImageGUI::displayImage(string title, cv::Mat image){
    cv::namedWindow(title, WINDOW_AUTOSIZE);
    cv::imshow(title, image);
}

void MainImageGUI::applyAll(){
    mo.createKernel(kernelSize->text().toInt());
    addImageToWidget(original, "ORIGINAL", 0, 0);
    addImageToWidget(mo.applyErosion(original), "Erosion", 0, 1);
    addImageToWidget(mo.applyDilatation(original), "Dilatation", 0, 2);
    addImageToWidget(mo.applyTopHat(original), "Top Hat", 1, 0);
    addImageToWidget(mo.applyBlackHat(original), "Black Hat", 1, 1);
    addImageToWidget(mo.applyEquation(original), "Equation", 1, 2);
}

void MainImageGUI::handleButton(){
    applyAll();
}