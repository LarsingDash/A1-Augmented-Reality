#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void hand();
Mat detectAndDisplay(cv::Mat frame, cv::CascadeClassifier& hand_cascade_classifier);
Mat addFilter(Mat frame);
