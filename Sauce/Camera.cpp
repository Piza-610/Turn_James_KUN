#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <vector>

#include "Camera.h"

using namespace cv;
using namespace std;

typedef struct Face_Position{
	int x_st = 0, y_st = 0, x_ed = 0,  y_ed = 0;
}Face_Position;


int main() {
	struct Face_Position Fpos;

    /* 初期設定 */
	cv::VideoCapture cap(0);    //open the device
	if (!cap.isOpened())
		return -1;
	cv::Mat frame; 	//取得したフレーム

    /* 顔認識の土台作り */
    //カスケード分類気格納場所
    CascadeClassifier cascade;
    //正面顔情報が入っているカスケードをロード
    cascade.load("~~~/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml");
	
    vector<Rect> faces;    //輪郭情報を格納場所
    Mat detection_frame;    //指定範囲
    Rect roi;
    int detection_flag = 0; //既に顔検出しているか(0:no, 1,yes)

    int basic_flag = 0;//連続で顔を検知しているかフラグ(0:no(fst_load)　1:yes)
	int x_basic = 0;//基準点のX座標
	int y_basic = 0;//基準点のY座標

    /*カメラ起動中処理*/
	while (1){
		cap >> frame;

        /*カメラ検出範囲処理*/
        if (detection_flag == 0) {  //直前のフレームで顔が検出されていない場合

			//検出範囲はカメラ映像全体とする
			detection_frame = frame;

			//基準点をリセット
			basic_flag = 0;
			x_basic = 0;
			y_basic = 0;

		} else {  //直前のフレームで顔が検出された場合

			//検出範囲として、直前のフレームの顔検出の範囲より一回り(上下左右50pixel)大きい範囲とする
			Rect roi(Point(Fpos.x_st - 50, Fpos.y_st - 50), 
				Point(Fpos.x_ed + 50, Fpos.y_ed + 50));
			detection_frame = frame(roi);

			//検出範囲をピンク枠で囲う
			rectangle(frame, Point(Fpos.x_st - 50, Fpos.y_st - 50), 	
				Point(Fpos.x_ed + 50, Fpos.y_ed + 50), Scalar(200, 0, 255), 3);

			//連続検索フラグを1(2連続以上の)
			basic_flag = 1;
		}

		detection_flag = 0;

        //カードスケープファイルに基づいてフレームから顔を検知
        cascade.detectMultiScale(frame, faces, 1.1, 3, 0, Size(20, 20));

		if (faces.size() > 0) {//顔を検出した場合
			detection_flag = 1; 			//顔の検出フラグを1(発見)にする

			//顔座標の左上の座標を求める
			if (basic_flag == 0) {//初検知の場合
				//初検知の場合は検出された値をそのまま使う
				Fpos.x_st = faces[0].x;
				Fpos.y_st = faces[0].y;

			} else if (basic_flag == 1) {//連続検知の場合
				//連続検知の場合は、検出座標と直前の基準点を使って顔座標を検出する
				Fpos.x_st = (x_basic - 50) + faces[0].x ;
				Fpos.y_st = (y_basic - 50) + faces[0].y ;

			}

			//顔座標の右下の座標を求める
			Fpos.x_ed = Fpos.x_st + faces[0].width;
			Fpos.y_ed = Fpos.y_st + faces[0].height;

			//基準点を今算出した顔座標に更新する
			x_basic = Fpos.x_st;
			y_basic = Fpos.y_st;

			rectangle(frame, Point(Fpos.x_st, Fpos.y_st),
				Point(Fpos.x_end, Fpos.y_end), Scalar(0, 0, 255), 3);
		}

		//画像を表示．
		imshow("win", frame);

        const int key = cv::waitKey(1);
		if (key == 'q')	    
			break;          
	}
	//すべてのウィンドウを閉じる
	cv::destroyAllWindows();
	return 0;
}


//    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
//    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);