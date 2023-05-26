#include "hand.h"

CascadeClassifier hand_cascade; // Declare the hand cascade classifier

void hand()
{
    // Step 1: Create video capture object
    cv::VideoCapture cap(0);

    // Check if video capture is successful
    if (!cap.isOpened())
    {
        std::cout << "Failed to open the camera." << std::endl;
    }
    hand_cascade.load("rpalm.xml"); // Path to palm cascade XML file

    // Create a window to display the camera feed
    cv::namedWindow("Hand Detection", cv::WINDOW_NORMAL);

    cv::Mat frame;

    while (true)
    {
        // Step 1: Read a frame from the video capture
        cap.read(frame);

        // Step 2: Convert the frame to HSV color space
        cv::Mat hsv_frame;
        cv::cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);

        // Step 3: Define skin color range in HSV
        cv::Scalar lower_skin_color(0, 10, 60);
        cv::Scalar upper_skin_color(20, 150, 255);

        // Step 4: Create a binary mask to detect skin color regions
        cv::Mat skin_mask;
        cv::inRange(hsv_frame, lower_skin_color, upper_skin_color, skin_mask);

        // Step 5: Apply morphological operations to reduce noise
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
        cv::morphologyEx(skin_mask, skin_mask, cv::MORPH_OPEN, kernel);
        cv::morphologyEx(skin_mask, skin_mask, cv::MORPH_CLOSE, kernel);

        // Step 6: Find contours of skin regions
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(skin_mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        // Step 7: Find the largest contour (assumed to be the hand)
        int max_contour_index = -1;
        double max_contour_area = 0.0;
        for (size_t i = 0; i < contours.size(); i++)
        {
            double contour_area = cv::contourArea(contours[i]);
            if (contour_area > max_contour_area)
            {
                max_contour_area = contour_area;
                max_contour_index = i;
            }
        }

        // Step 8: Create a black frame
        cv::Mat black_frame = cv::Mat::zeros(frame.size(), CV_8UC3);

        // Step 9: Draw the hand contour on the black frame
        if (max_contour_index != -1)
        {
            cv::drawContours(black_frame, contours, max_contour_index, cv::Scalar(255, 255, 255), cv::FILLED);
        }

        // Step 10: Display the output frame
        cv::imshow("Hand Detection", black_frame);
        detectAndDisplay(frame, hand_cascade);

        // Step 11: Finish when the Esc key is pressed
        if (cv::waitKey(1) == 27)
        {
            break;
        }
    }

    // Release the video capture object and close the windows
    cap.release();
    cv::destroyAllWindows();
}

void detectAndDisplay(cv::Mat frame, cv::CascadeClassifier& hand_cascade_classifier)
{
    cv::Mat frame_gray;
    cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(frame_gray, frame_gray);

    //-- Detect hands
    std::vector<cv::Rect> hands;
    hand_cascade_classifier.detectMultiScale(frame_gray, hands);
    for (size_t i = 0; i < hands.size(); i++)
    {
        cv::Point center(hands[i].x + hands[i].width / 2, hands[i].y + hands[i].height / 2);
        cv::ellipse(frame, center, cv::Size(hands[i].width / 2, hands[i].height / 2), 0, 0, 360, cv::Scalar(255, 0, 255), 4);
    }

    //-- Show what you got
    cv::imshow("Capture - Hand detection", frame);
}
