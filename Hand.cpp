#include <iostream>
#include <>
int main()
{
    // Step 1: Create video capture object
    cv::VideoCapture cap(0);

    // Check if video capture is successful
    if (!cap.isOpened())
    {
        std::cout << "Failed to open the camera." << std::endl;
        return -1;
    }

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

        // Step 8: Draw a contour around the hand
        cv::Mat hand_mask = cv::Mat::zeros(frame.size(), CV_8UC3);
        if (max_contour_index != -1)
        {
            cv::drawContours(hand_mask, contours, max_contour_index, cv::Scalar(0, 255, 0), 2);
        }

        // Step 9: Display the hand mask
        cv::imshow("Hand Detection", hand_mask);
        cv::imshow(" test", frame);

        // Step 10: Finish when the Esc key is pressed
        if (cv::waitKey(1) == 27)
        {
            break;
        }
    }

    // Release the video capture object and close the windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
