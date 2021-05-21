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

        void setKernel(cv::Mat);

};

class MainImageGUI {

    private:
        MorphologicalOperation mo;
        cv::Mat original;
        void init(int argc, char *argv[]);

    public:
        MainImageGUI(string, int argc, char *argv[]);

        cv::Mat readImage(string);
        void displayImage(string, cv::Mat);
        void applyAll();
};