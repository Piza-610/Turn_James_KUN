#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include "Camera.h"

using namespace cv;
using namespace std;

//顔の検出範囲を決定
Mat range_of_detection(int dflag, Face_Coordinate &FC, Basic_Coordinate_Infomation &BCI, Mat &frame){
	if(dflag == 0){
		//基準をリセット
		BCI.basic_flag = 0;
		BCI.x_basic = 0;
		BCI.y_basic = 0;

		//検知範囲を全体
		return frame;
	}else{
		//検出範囲がキャプチャフレーム内に収まるように変換する
		if (FC.x_srt - 50 < 1) FC.x_srt = 51;
		if (FC.y_srt - 50 < 1) FC.y_srt = 51;
		if (FC.x_end + 50 > frame.cols - 1)	FC.x_end = frame.cols - 51;
		if (FC.y_end + 50 > frame.rows - 1)	FC.y_end = frame.rows - 51;

		//連続検索フラグを1
		BCI.basic_flag = 1;

		//検出範囲として、直前のフレームの顔検出の範囲より一回り(上下左右50pixel)大きい範囲とする
		Rect roi(Point(FC.x_srt - 50, FC.y_srt - 50), Point(FC.x_end + 50, FC.y_end + 50));
		return  frame(roi);
	}
}

int faces_detection(Face_Coordinate &FC, Basic_Coordinate_Infomation &BCI, Mat &frame, vector<Rect> &faces){
	//顔を検出した場合
	if(faces.size() > 0){
		//左上の顔座標を求める
		if(BCI.basic_flag == 0){	//初期検知の場合
			FC.x_srt = faces[0].x;
			FC.y_srt = faces[0].y;
		}else if(BCI.basic_flag == 1){	//連続検知の場合
			FC.x_end = (BCI.x_basic - 50) + faces[0].x;
			FC.y_end = (BCI.y_basic - 50) + faces[0].y;
		}

		FC.x_end = FC.x_srt + faces[0].width;
		FC.y_end = FC.y_srt + faces[0].height;

		BCI.x_basic = FC.x_srt;
		BCI.y_basic = FC.y_srt;

		//検知した顔回りに赤い線
		rectangle(frame, Point(FC.x_srt, FC.y_srt), Point(FC.x_end, FC.y_end), Scalar(0, 0, 255), 3);

		//顔検出フラグを立てる(1)
		return 1;
	}
	return 0;
}

/*
//連続顔検出フラグが0のとき顔を斜めにする
<!>ここの処理は重たくなるから今は排除<!>

//(直前に顔を検出していた時だけ斜めの検出を行う)
if (not_found_flag == 0) {
	not_found_flag = 1;
	if (faces.size() == 0) {
		//右に15度傾けるアフィン行列を求める
		Mat trans = getRotationMatrix2D(Point(detection_frame.cols / 2, detection_frame.rows / 2), 30, 1);
		//求めたアフィン行列を使って画像を回転
		warpAffine(detection_frame, detection_frame, trans, detection_frame.size());
		//傾けた画像で顔を検出
		cascade.detectMultiScale(detection_frame, faces, 1.2, 5, 0, Size(20, 20));
	}
	if (faces.size() == 0) {
		//左に15度傾けるアフィン行列を求める(右に15度傾けていたので-30度右に傾けることで実質左に15度傾く)
		Mat trans = getRotationMatrix2D(Point(detection_frame.cols / 2, detection_frame.rows / 2), -60, 1);
		//求めたアフィン行列を使って画像を回転
		warpAffine(detection_frame, detection_frame, trans, detection_frame.size());
		//傾けた画像で顔を検出
		cascade.detectMultiScale(detection_frame, faces, 1.2, 5, 0, Size(20, 20));
	}
}
*/