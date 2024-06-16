#ifndef CLASS_CAMERA_H
#define CLASS_CAMERA_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

using namespace cv;

//基準となる値
typedef struct Basic_Coordinate_Infomation{
	int basic_flag = 0;	//顔を連続で検知しているか(0:No, 1:Yes)
	int x_basic = 0;
	int y_basic = 0;
}Basic_Coordinate_Infomation;

//顔の座標の位置
typedef struct Face_Coordinate{
	int x_srt = 0;	//左上 x
	int y_srt = 0;	//右上 y
	int x_end = 0;	//左下
	int y_end = 0;	//右下
}Face_Coordinate;

Mat range_of_detection(int dflag, Face_Coordinate &FC, Basic_Coordinate_Infomation &BCI, Mat &frame);
int faces_detection(Face_Coordinate &FC, Basic_Coordinate_Infomation &BCI, Mat &frame, vector<Rect> &faces);

#endif
