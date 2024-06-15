#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

using namespace cv;
using namespace std;

int main(void) {
	//カメラデバイスが正常にオープンしたか確認．
	VideoCapture cap(0);
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

	//顔の検知範囲
	Mat detection_frame;	//顔の検出範囲
	Rect roi;
	int detection_flag = 0;	//直前に顔を検知しているか(0:No, 1:Yes)

	int x = 0;	//左上
	int y = 0;	//右上
	int x_end = 0;	//左下
	int y_end = 0;	//右下

	int basic_flag = 0;	//顔を連続で検知しているか(0:No, 1:Yes)
	int x_basic = 0;
	int y_basic = 0;

	int roi_x, roi_y, roi_width, roi_height;

	//無限ループ
	while (1){
		//USBカメラが得た動画の１フレームを格納
		cap >> frame;

		if(detection_flag == 0){
			//検知範囲を全体
			detection_frame = frame;

			//基準をリセット
			basic_flag = 0;
			x_basic = 0;
			y_basic = 0;
		}else{
			//直前の顔検出の範囲より一回り大きい範囲を検出する
			Rect roi(Point(x - 50, y - 50), Point(x_end + 50, y_end + 50));
			detection_frame = frame(roi);

			//連続検索フラグを1
			basic_flag = 1;
		}

		detection_flag = 0;
		

		//格納されたフレームに対してカスケードファイルに基づいて顔を検知
		cascade.detectMultiScale(detection_frame, faces, 1.2, 5, 0, Size(20, 20));

		//顔を検出した場合
		if(faces.size() > 0){
			//顔検出フラグを立てる(1)
			detection_flag = 1;

			//左上の顔座標を求める
			if(basic_flag == 0){	//初期検知の場合
				x = faces[0].x;
				y = faces[0].y;
			}else if(basic_flag == 1){	//連続検知の場合
				x = (x_basic - 50) + faces[0].x;
				y = (y_basic - 50) + faces[0].y;
			}

			x_end = x + faces[0].width;
			y_end = y + faces[0].height;

			x_basic = x;
			y_basic = y;

			//検知した顔回りに赤い線
			rectangle(frame, Point(x, y), Point(x_end, y_end), Scalar(0, 0, 255), 3);
		}


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