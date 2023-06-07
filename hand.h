#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <Windows.h>

using namespace std;
using namespace cv;

int hand();
void moveCursor(int x, int y);
// Mat detectAndDisplay(cv::Mat frame, cv::CascadeClassifier& hand_cascade_classifier);
// Mat addFilter(Mat frame);
