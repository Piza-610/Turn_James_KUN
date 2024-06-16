#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <wiringPi.h> 
#include "Camera.h"
#include "Motor.h"

using namespace cv;
using namespace std;

int main(void) {
    wiringPiSetupGpio();        // clear WiringPi

    Motor motor1;

    Motor_construct(&motor1);

    int pin = Motor_getPin(&motor1);

    Motor_setting(&motor1 , pin, 400, 1024);
    Motor_moving(&motor1 , pin);

	VideoCapture cap(0);    //open camera & check
	if (!cap.isOpened()){
		return -1;	//読み込みに失敗したときの処理
	}

	//取得したフレーム
	Mat frame;
	//カスケード分類器格納場所
	CascadeClassifier cascade; 
	//正面顔情報が入っているカスケード
	cascade.load("/usr/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml"); 
	//輪郭情報を格納場所
	vector<Rect> faces;

    Face_Coordinate FC;
	Basic_Coordinate_Infomation BCI;

	Mat detection_frame;	//顔の検出範囲
	Rect roi;
	int detection_flag = 0;	//直前に顔を検知しているか(0:No, 1:Yes)
	int not_found_flag = 1;//連続顔を見つけられなかった(0:No, 1:Yes)

	//無限ループ
	while (1){
		//USBカメラが得た動画の１フレームを格納
		cap >> frame;

		detection_frame = range_of_detection(detection_flag, FC, BCI, frame);	

		//格納されたフレームに対してカスケードファイルに基づいて顔を検知
		cascade.detectMultiScale(detection_frame, faces, 1.2, 5, 0, Size(20, 20)); 

		detection_flag = faces_detection(FC, BCI, frame, faces);

		//画像を表示．
		imshow("window", frame);

		//キーボード入力を受け付ける
		int key = waitKey(1);
		//qボタンが押されたとき
		if (key == 'q'){
			break;
		}

	}
	//すべてのウィンドウを閉じる
	destroyAllWindows();

	return 0;
}
