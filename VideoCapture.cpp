#include "VideoCapture.hpp"

using namespace cv;

VideoCapture video::initCapture()
{
	//initialize capture properties
	VideoCapture cap(0, cv::CAP_V4L2);
	cap.set(CAP_PROP_FRAME_WIDTH, 800);
 	cap.set(CAP_PROP_FRAME_HEIGHT, 600);
 	cap.set(CAP_PROP_FPS, 30);
	cap.set(CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));

	if(!cap.isOpened())
	{
		std::cout << "Could not open video or camera\n";
		exit(EXIT_FAILURE); //end the program	
	}
	return cap;
}

VideoWriter video::initWriter()
{
	VideoWriter wri("akoutput.mp4", cv::CAP_FFMPEG, cap.get(CAP_PROP_FOURCC), cap.get(CAP_PROP_FPS), 
		Size(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT)), false);
	return wri;
}

void video::closeVideo()
{
	cap.release();
	wri.release();
}

Mat video::getFrame() {
	cap >> frame;
	return frame; 
}

void video::writeFrame(Mat frame) {
	wri << frame;
}