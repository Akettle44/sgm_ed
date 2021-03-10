#ifndef CAPTURE_H
#define CAPTURE_H

#include <opencv.hpp>
#include <highgui/highgui.hpp>
#include <videoio.hpp>

using namespace cv;

class video {

	public:
		//default constructor
		video() {
			cap = initCapture();
		//	wri = initWriter();
		}

		//parameterized constructor
		video(VideoCapture capture, VideoWriter writer) {
			cap = capture;
			wri = writer;
		}

		//destructor
		~video() {
			closeVideo();
		}

		//functions
		VideoCapture initCapture();
		Mat getFrame();
		VideoWriter initWriter();
		void closeVideo();

	private:
		VideoCapture cap;
		VideoWriter wri;
		Mat frame;
};
#endif 
