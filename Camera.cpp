#include <iostream>
#include <opencv2/opencv.hpp>
#include "Camera.h"

int main() {
    cv::Mat img;
    cv::VideoCapture cap;
    cap.open("/dev/video0", cv::CAP_V4L2); 

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return -1;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    while (true) {
        // カメラの画像をimgに代入
        cap.read(img);

        // imgの表示
        cv::imshow("VideoCapture", img);

        // escで終了
        unsigned char key = cv::waitKey(2);
        if (key == '\x1b') break;
    }

    return 0;
}