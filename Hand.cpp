#include <iostream>
#include <Windows.h>
#include <opencv2/opencv.hpp>

// Constants for cursor control
const int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);
int lastX;
int lastY;

// Function to move the cursor
void moveCursor(int x, int y) {
    int newX = SCREEN_WIDTH - ((x * SCREEN_WIDTH) / 607);  // Map the x-coordinate to the screen width
    int newY = (y * SCREEN_HEIGHT) / 342;  // Map the y-coordinate to the screen height

    newX = std::max(0, std::min(newX, SCREEN_WIDTH));
    newY = std::max(0, std::min(newY, SCREEN_HEIGHT));

    lastX = newX;
    lastY = newY;

    SetCursorPos(newX, newY);
}

// Function to simulate a mouse button press
void mouseButtonDown() {
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
}

void mouseButtonUp() {
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

int hand() {
    cv::VideoCapture cap(1);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 607); // valueX = your wanted width
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 342); // valueY = your wanted height

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

        for (const auto& hand : hands) {
            cv::Point center(hand.x + hand.width / 2, hand.y + hand.height / 2);
            cv::circle(frame, center, hand.width / 2, cv::Scalar(255, 0, 255), 2);

            // Determine hand status based on hand area
            std::string handStatus = (hand.width * hand.height < 6000) ? "Closed" : "Open";
            cv::putText(frame, "Open", cv::Point(hand.x, hand.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.9, cv::Scalar(255, 0, 255), 2);

            // Move the cursor based on hand position
            moveCursor(hand.x + hand.width / 2, hand.y + hand.height / 2);
            // mouseButtonUp();
        }
        for (const auto& hand : fist) {
            cv::Point center(hand.x + hand.width / 2, hand.y + hand.height / 2);
            cv::circle(frame, center, hand.width / 2, cv::Scalar(255, 0, 255), 2);

            // Determine hand status based on hand area
            std::string handStatus = (hand.width * hand.height < 6000) ? "Closed" : "Open";
            cv::putText(frame, "Closed", cv::Point(hand.x, hand.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.9, cv::Scalar(255, 0, 255), 2);

            // Move the cursor based on hand position
            moveCursor(hand.x + hand.width / 2, hand.y + hand.height / 2);
            // mouseButtonDown();
        }

        cv::imshow("Hand Recognition", frame);

        if (cv::waitKey(1) == 27) {
            break;  // Exit if ESC is pressed
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
