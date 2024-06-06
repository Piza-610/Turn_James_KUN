#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argh, char* argv[])
{
    cv::VideoCapture cap(0);    //デバイスのオープン

    if(!cap.isOpened())     //カメラデバイスが正常にオープンしたか確認
        return -1;

    cv::Mat frame;  //取得したフレーム
    while (cap.read(frame))
    {
        //取得したフレーム画像に対し、クレースケール変換や2値化などの処理を書き込む

        cv::imshow("win",frame);
        const int key = cv::waitKey(1);
        if(key == 'q')
            break;
        else if(key == 's')
            cv::imwrite("img.jpg", frame);
    }
    cv::destroyAllWindows();

    return 0;
}