#include "hand.h"
#include "glm/glm.hpp"

const int camHeight = 342;
const int camWidth = 607;

int HandInit(const int windowWidth, const int windowHeight) {
    screenWidth = windowWidth;
    screenHeight = windowHeight;
    cursorX = screenWidth / 2;
    cursorY = screenHeight / 2;

    cap = cv::VideoCapture(0);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, camWidth); // valueX = your wanted width
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, camHeight); // valueY = your wanted height

    if (!cap.isOpened()) {
        std::cerr << "Failed to open camera." << std::endl;
        return -1;
    }

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

    return 0;
}

void HandUpdate()
{
    cap >> frame;
    if (frame.empty()) {
        throw "Failed to capture frame.";
    }

    cv::Mat frameGray;
    cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(frameGray, frameGray);

    std::vector<cv::Rect> hands;
    std::vector<cv::Rect> fist;
    std::vector<cv::Rect> total;

    handcascade_palm.detectMultiScale(frameGray, hands, 1.1, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
    handcascade_fist.detectMultiScale(frameGray, fist, 1.1, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    total.reserve(hands.size() + fist.size());
    total.insert(total.end(), hands.begin(), hands.end());
    total.insert(total.end(), fist.begin(), fist.end());

    handInArea = false;

    for (const auto& hand : total) {
	    constexpr int thickness = 2;
	    const cv::Point center(hand.x + hand.width / 2, hand.y + hand.height / 2);
        cv::circle(frame, center, hand.width / 2, cv::Scalar(255, 0, 255), 2);

	    const float length = static_cast<float>(center.x) - static_cast<float>(frame.cols) / 2.f;
	    const float height = static_cast<float>(center.y) - static_cast<float>(frame.rows) / 2.f;
	    const float distance = sqrt(pow(abs(length), 2.f) + pow(abs(height), 2.f));

	    if (distance > 100)
	    {
		    glm::vec2 direction(length, height);
		    direction = glm::normalize(direction);

            constexpr glm::vec2 invert(-1, 1);
            direction *= invert;

            cursorX += static_cast<int>(direction.x * (distance * CURSOR_SPEED));
            cursorY += static_cast<int>(direction.y * (distance * CURSOR_SPEED));

            cv::line(frame, cv::Point(frame.cols / 2, frame.rows / 2), center, cv::Scalar(0, 255, 0), 2);
            SetCursorPos(cursorX, cursorY);
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
