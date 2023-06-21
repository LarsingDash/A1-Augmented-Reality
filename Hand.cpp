#include "hand.h"
#include "glm/glm.hpp"

//Camera image variables
constexpr int CAM_HEIGHT = 342;
constexpr int CAM_WIDTH = 607;

//Init
int HandInit(const int windowWidth, const int windowHeight) {
    screenWidth = windowWidth;
    screenHeight = windowHeight;
    cursorX = screenWidth / 2;
    cursorY = screenHeight / 2;

    //Camera input
    cap = cv::VideoCapture(0);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);

    if (!cap.isOpened()) {
        std::cerr << "Failed to open camera." << std::endl;
        return -1;
    }

    //Open and closed hand cascades.
    handCascadeFist.load("fist.xml");  // Path to the hand cascade XML file
    handCascadePalm.load("rpalm.xml");  // Path to the hand cascade XML file

    if (handCascadePalm.empty()) {
        std::cerr << "Failed to load hand cascade file." << std::endl;
        return -1;
    }
    if (handCascadeFist.empty()) {
        std::cerr << "Failed to load hand cascade file." << std::endl;
        return -1;
    }

    return 0;
}

//Update method
void HandUpdate()
{
    cap >> frame;
    if (frame.empty()) {
        throw "Failed to capture frame.";
    }

    cv::Mat frameGray;
    cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(frameGray, frameGray);

    //Lists of detected objects.
    std::vector<cv::Rect> hands;
    std::vector<cv::Rect> fists;
    std::vector<cv::Rect> total;

    handCascadePalm.detectMultiScale(frameGray, hands, 1.1, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
    handCascadeFist.detectMultiScale(frameGray, fists, 1.1, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    total.reserve(hands.size() + fists.size());
    total.insert(total.end(), hands.begin(), hands.end());
    total.insert(total.end(), fists.begin(), fists.end());

    handInArea = false;

    for (const auto& hand : total) {

        //Detect hand and draw circle
        constexpr int thickness = 2;
        const cv::Point center(hand.x + hand.width / 2, hand.y + hand.height / 2);
        cv::Scalar color(255, 0, 255);  // Purple color for hand circle

        cv::circle(frame, center, hand.width / 2, color, thickness);

        //Smoothing
        const float length = static_cast<float>(center.x) - static_cast<float>(frame.cols) / 2.f;
        const float height = static_cast<float>(center.y) - static_cast<float>(frame.rows) / 2.f;
        const float distance = sqrt(pow(abs(length), 2.f) + pow(abs(height), 2.f));

        if (distance > 50)
        {
            //Move the cursor
            glm::vec2 direction(length, height);
            direction = glm::normalize(direction);

            constexpr glm::vec2 invert(-1, 1);
            direction *= invert;

            cursorX += static_cast<int>(direction.x * (distance * CURSOR_SPEED));
            cursorY += static_cast<int>(direction.y * (distance * CURSOR_SPEED));

            cv::line(frame, cv::Point(frame.cols / 2, frame.rows / 2), center, cv::Scalar(0, 255, 0), thickness);
            SetCursorPos(cursorX, cursorY);
        }

        //Left mouse click logic
        const bool isClicked = !fists.empty();
        if (isClicked != lastIsClicked)
        {
            lastIsClicked = isClicked;
            INPUT buffer[1];

            if (isClicked)
            {
                cv::circle(frame, cv::Point(0, 0), 10, cv::Scalar(255, 0, 0), 2);

                buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
                SendInput(1, buffer, sizeof(INPUT));
            }
            else
            {
                buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
                SendInput(1, buffer, sizeof(INPUT));
            }
        }
    }

    cv::Mat flipped;
    cv::flip(frame, flipped, 1);
    cv::imshow("Hand Gesture Recognition", flipped);
}

void HandTeardown()
{
    cv::destroyAllWindows();
    cap.release();
}
