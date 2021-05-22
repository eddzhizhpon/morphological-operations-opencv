#include "../header_files/header.hpp"

Image::Image(){}

Image::Image(cv::Mat image, string title, int r, int c){
    this->image = image;
    this->title = title;
    this->r = r;
    this->c = c;
}