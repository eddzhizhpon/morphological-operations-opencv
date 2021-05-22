#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cmath>
#include <string>

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
#include <QFileDialog>
#include <QScrollArea>
#include <QLayout>
#include <QMessageBox>

using namespace std;
using namespace cv;

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

class Image {
    public:
        Image();
        Image(cv::Mat, string, int, int);
        cv::Mat image;
        string title;
        int r;
        int c;
};

class MainImageGUI : public QMainWindow {

    protected:
        void resizeEvent(QResizeEvent *event) override;

    private slots:
        void handleButton();
        void handleImageChooserButton();
    
    private:
        vector<Image> processedImages;

        MorphologicalOperation mo;
        cv::Mat original;

        QGridLayout *layout;
        QGridLayout *imageLayout;
        QWidget *widget;
        QWidget *imageWidget;
        QLineEdit *kernelSize;
        QLineEdit *imagePath;
        QGroupBox *imageBox;

        QPushButton *kernelButton;
        QPushButton *imageChooserButton;

    public:
        int w;
        MainImageGUI();
        int init();

        void addImageToWidget(cv::Mat, QString, int, int);

        cv::Mat readImage(string);
        void displayImage(string, cv::Mat);
        void applyAll();

        void showImages();
        void clearLayout(QLayout *layout);
};