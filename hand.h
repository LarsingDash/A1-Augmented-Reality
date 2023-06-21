#ifndef HAND
#define HAND

//windows has to be above opencv for std:: to work
#include <Windows.h>
#include <opencv2/opencv.hpp>

//Init - Update - Teardown
int HandInit(int windowWidth, int windowHeight);
void HandUpdate();
void HandTeardown();

//Variables
static cv::VideoCapture cap;
static cv::Mat frame;
 
static cv::CascadeClassifier handCascadePalm;
static cv::CascadeClassifier handCascadeFist;
 
static bool handInArea = false;
static cv::Rect currentArea;

static int screenWidth;
static int screenHeight;

static int cursorX;
static int cursorY;

constexpr float CURSOR_SPEED = 0.25f;
static bool lastIsClicked = false;

#endif