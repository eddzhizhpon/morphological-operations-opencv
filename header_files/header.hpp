#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cmath>
#include <sstream>
#include <fstream>
#include <string>
#include <experimental/filesystem>

#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp> 
#include <opencv2/video/video.hpp> 
#include <opencv2/videoio/videoio.hpp>

#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGraphicsScene>


using namespace std;
using namespace cv;

namespace fs =  std::experimental::filesystem;

class MorphologicalOperation {

    private:
        cv::Mat kernel;

    public:
        MorphologicalOperation(int = 37, int = 37);
        
        cv::Mat applyErosion(cv::Mat);
        cv::Mat applyDilatation(cv::Mat);
        cv::Mat applyTopHat(cv::Mat);
        cv::Mat applyBlackHat(cv::Mat);
        cv::Mat applyEquation(cv::Mat);

        void createKernel(int);

};

class MainImageGUI : public QMainWindow {
    private slots:
        void handleButton();
    private:
        MorphologicalOperation mo;
        cv::Mat original;

        QGridLayout *layout;
        QGridLayout *imageLayout;
        QWidget *widget;
        QWidget *imageWidget;
        QPushButton *kernelButton;
        QLineEdit *kernelSize;
        QGroupBox *imageBox;

    public:
        MainImageGUI(string);
        int init();

        void addImageToWidget(cv::Mat, QString, int, int);

        cv::Mat readImage(string);
        void displayImage(string, cv::Mat);
        void applyAll();
};