#ifndef HAND
#define HAND

//windows has to be above opencv for std:: to work
#include <Windows.h>
#include <opencv2/opencv.hpp>

void moveCursor(int x, int y);

int HandInit();
void HandUpdate();
void HandTeardown();
 
static cv::VideoCapture cap;
static cv::Mat frame;
 
static cv::CascadeClassifier handcascade_palm;
static cv::CascadeClassifier handcascade_fist;
 
static bool handInArea = false;
static cv::Rect currentArea;

#endif