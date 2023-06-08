#include <iostream>
#include <Windows.h>
#include <opencv2/opencv.hpp>

// Constants for cursor control
const int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);
const int camHeight = 342;
const int camWidth = 607;
int lastX;
int lastY;

// Cursor movement speed
const int CURSOR_SPEED = 10;

// Function to move the cursor in a specific direction
void moveCursor(int dx, int dy) {
    int newX = lastX + dx;
    int newY = lastY + dy;

    // Clamp the cursor position within the screen boundaries
    newX = std::max(0, std::min(newX, SCREEN_WIDTH));
    newY = std::max(0, std::min(newY, SCREEN_HEIGHT));

    // Update the cursor position and set it
    lastX = newX;
    lastY = newY;

    SetCursorPos(newX, newY);
}

int hand() {
    cv::VideoCapture cap(1);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, camWidth); // valueX = your wanted width
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, camHeight); // valueY = your wanted height

    if (!cap.isOpened()) {
        std::cerr << "Failed to open camera." << std::endl;
        return -1;
    }

    cv::CascadeClassifier handcascade_palm;
    cv::CascadeClassifier handcascade_fist;
    handcascade_fist.load("fist.xml");  // Path to the hand cascade XML file
    handcascade_palm.load("rpalm.xml");  // Path to the hand cascade XML file

    if (handcascade_palm.empty()) {
        std::cerr << "Failed to load hand cascade file." << std::endl;
        return -1;
    }
    if (handcascade_fist.empty()) {
        std::cerr << "Failed to load hand cascade file." << std::endl;
        return -1;
    }

    cv::Mat frame;
    bool handInArea = false;
    cv::Rect currentArea;

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Failed to capture frame." << std::endl;
            break;
        }

        cv::Mat frameGray;
        cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(frameGray, frameGray);

        std::vector<cv::Rect> hands;
        std::vector<cv::Rect> fist;
        handcascade_palm.detectMultiScale(frameGray, hands, 1.1, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
        handcascade_fist.detectMultiScale(frameGray, fist, 1.1, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

        // Rectangles for areas
        cv::Rect leftArea(camWidth / 10, camHeight / 2.5, 100, 100);
        cv::Rect rightArea(camWidth / 2, camHeight / 2.5, 100, 100);
        cv::Rect upArea(camWidth / 3.33, camHeight / 10, 100, 100);
        cv::Rect downArea(camWidth / 3.33, camHeight / 1.4, 100, 100);
        cv::Rect clickArea(camWidth - 100, camHeight / 2.5, 100, 100);

        handInArea = false;

        for (const auto& hand : hands) {
            cv::Point center(hand.x + hand.width / 2, hand.y + hand.height / 2);
            cv::circle(frame, center, hand.width / 2, cv::Scalar(255, 0, 255), 2);

            if (leftArea.contains(center)) {
                moveCursor(-CURSOR_SPEED, 0);
                handInArea = true;
                currentArea = leftArea;
            }
            else if (rightArea.contains(center)) {
                moveCursor(CURSOR_SPEED, 0);
                handInArea = true;
                currentArea = rightArea;
            }
            else if (upArea.contains(center)) {
                moveCursor(0, -CURSOR_SPEED);
                handInArea = true;
                currentArea = upArea;
            }
            else if (downArea.contains(center)) {
                moveCursor(0, CURSOR_SPEED);
                handInArea = true;
                currentArea = downArea;
            }
            
        }

        for (const auto& hand : fist) {
            cv::Point center(hand.x + hand.width / 2, hand.y + hand.height / 2);
            cv::circle(frame, center, hand.width / 2, cv::Scalar(255, 0, 255), 2);

            if (leftArea.contains(center)) {
                moveCursor(-CURSOR_SPEED, 0);
                handInArea = true;
                currentArea = leftArea;
            }
            else if (rightArea.contains(center)) {
                moveCursor(CURSOR_SPEED, 0);
                handInArea = true;
                currentArea = rightArea;
            }
            else if (upArea.contains(center)) {
                moveCursor(0, -CURSOR_SPEED);
                handInArea = true;
                currentArea = upArea;
            }
            else if (downArea.contains(center)) {
                moveCursor(0, CURSOR_SPEED);
                handInArea = true;
                currentArea = downArea;
            }
            else if (clickArea.contains(center)) {
                moveCursor(0, 0);
                handInArea = true;
                currentArea = clickArea;

                // Perform left mouse click
                INPUT input;
                input.type = INPUT_MOUSE;
                input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
                SendInput(1, &input, sizeof(INPUT));
            }
        }

        if (!handInArea) {
            // If hand is not in any area, stop the cursor
            currentArea = cv::Rect(0, 0, 0, 0);
        }

        // Draw areas
        cv::Scalar areaColor = cv::Scalar(0, 0, 255); // Red color
        int thickness = 2;
        cv::rectangle(frame, leftArea, (currentArea == leftArea) ? cv::Scalar(0, 255, 0) : areaColor, thickness);
        cv::putText(frame, "Left", cv::Point(10, frame.rows / 2), cv::FONT_HERSHEY_SIMPLEX, 1.0, (currentArea == leftArea) ? cv::Scalar(0, 255, 0) : areaColor, thickness);

        cv::rectangle(frame, rightArea, (currentArea == rightArea) ? cv::Scalar(0, 255, 0) : areaColor, thickness);
        cv::putText(frame, "Right", cv::Point(frame.cols - 100, frame.rows / 2), cv::FONT_HERSHEY_SIMPLEX, 1.0, (currentArea == rightArea) ? cv::Scalar(0, 255, 0) : areaColor, thickness);

        cv::rectangle(frame, upArea, (currentArea == upArea) ? cv::Scalar(0, 255, 0) : areaColor, thickness);
        cv::putText(frame, "Up", cv::Point(frame.cols / 3, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0, (currentArea == upArea) ? cv::Scalar(0, 255, 0) : areaColor, thickness);

        cv::rectangle(frame, downArea, (currentArea == downArea) ? cv::Scalar(0, 255, 0) : areaColor, thickness);
        cv::putText(frame, "Down", cv::Point(frame.cols / 3, frame.rows - 20), cv::FONT_HERSHEY_SIMPLEX, 1.0, (currentArea == downArea) ? cv::Scalar(0, 255, 0) : areaColor, thickness);

        cv::rectangle(frame, clickArea, (currentArea == clickArea) ? cv::Scalar(0, 255, 0) : areaColor, thickness);
        cv::putText(frame, "Click", cv::Point(frame.cols / 2, frame.rows / 2), cv::FONT_HERSHEY_SIMPLEX, 1.0, (currentArea == clickArea) ? cv::Scalar(0, 255, 0) : areaColor, thickness);

        cv::imshow("Hand Gesture Recognition", frame);

        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    cv::destroyAllWindows();
    cap.release();

    return 0;
}
