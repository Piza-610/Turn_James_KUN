#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <wiringPi.h> 
#include "Camera.h"
#include "Motor.h"

using namespace cv;
using namespace std;

int main(void) {
    wiringPiSetupGpio();        // Clear WiringPi
	VideoCapture cap(0);        // Open camera & check
	if (!cap.isOpened()){
		return -1;	// Processing when reading fails
	}

    Motor motor1;

    Motor_construct(&motor1);

    int pin = Motor_getPin(&motor1);

    Motor_setting(&motor1 , pin, 400, 1024);

	Mat frame;	        // Create frame
	CascadeClassifier cascade; 	// Create a cascade box.
	cascade.load("/usr/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml"); 	// Load face Cascade
	vector<Rect> faces; 	    // Create a face contour box

    Face_Coordinate FC;
	Basic_Coordinate_Infomation BCI;

	Mat detection_frame;	// Create face detection range
	Rect roi;
	int detection_flag = 0;	// Is the face detected just before(0:No, 1:Yes)
	int not_found_flag = 1;// 連続して顔を見つけられなかったか(0:No, 1:Yes)

	// Endless loop
	while (1){
		// Stores a single frame of video obtained by the USB camera
		cap >> frame;

		detection_frame = range_of_detection(detection_flag, FC, BCI, frame);	

		// Face detection based on cascade file for stored frames
		cascade.detectMultiScale(detection_frame, faces, 1.2, 5, 0, Size(20, 20)); 

		detection_flag = faces_detection(FC, BCI, frame, faces);

        if(BCI.basic_flag == 1) Motor_moving(&motor1 , pin);

		// Show Image
		imshow("window", frame);

		// Waiting for keyboard input
		int key = waitKey(1);
		// If you press 'q',
		if (key == 'q'){
			break;  // The loop is end
		}

	}
	// Close all windows
	destroyAllWindows();

	return 0;
}
