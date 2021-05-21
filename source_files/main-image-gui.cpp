#include "../header_files/header.hpp"
#include <QApplication>
#include <QLabel>
#include <QWidget>

MainImageGUI::MainImageGUI(string imagePath, int argc, char *argv[]){
    this->original = readImage(imagePath);
    init(argc, argv);
}

cv::Mat MainImageGUI::readImage(string imagePath){
    cv::Mat image = cv::imread(imagePath, IMREAD_GRAYSCALE);
    return image;
}

void MainImageGUI::init(int argc, char *argv[]){
    QApplication app(argc, argv);
    QLabel hello("<center>Welcome to my first Qt program</center>");
    hello.setWindowTitle("My First Qt Program");
    hello.resize(400, 400);
    hello.show();
    app.exec();
}

void MainImageGUI::displayImage(string title, cv::Mat image){
    cv::namedWindow(title, WINDOW_AUTOSIZE);
    cv::imshow(title, image);
}

void MainImageGUI::applyAll(){
    displayImage("Original", original);
    displayImage("Erosion", mo.applyErosion(original));
    displayImage("Dilatation", mo.applyDilatation(original));
    displayImage("Top Hat", mo.applyTopHat(original));
    displayImage("Black Hat", mo.applyBlackHat(original));
    displayImage("Equation", mo.applyEquation(original));
}