#include "VideoCapture.hpp"

using namespace cv;

VideoCapture video::initCapture()
{
	//initialize capture properties
	VideoCapture cap(0, cv::CAP_V4L2);
	cap.set(CAP_PROP_FRAME_WIDTH, 1920);
 	cap.set(CAP_PROP_FRAME_HEIGHT, 1080);
 	cap.set(CAP_PROP_FPS, 30);
	cap.set(CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));

	if(!cap.isOpened())
	{
	#ifdef DEBUG
		std::cout << "Could not open video or camera\n";
	#endif
		exit(EXIT_FAILURE); //end the program	
	}
	return cap;
}

VideoWriter video::initWriter()
{
	VideoWriter wri("akoutput.mp4", cv::CAP_FFMPEG, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), cap.get(5), Size(cap.get(3), cap.get(4)),true);
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