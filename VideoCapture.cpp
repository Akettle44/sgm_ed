#include "VideoCapture.h"

using namespace cv;

VideoCapture initCapture()
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

VideoWriter initWriter(VideoCapture cap)
{
	VideoWriter video("akoutput.mp4", cv::CAP_FFMPEG, cv::VideoWriter::fourcc('H', '2', '6', '4'), cap.get(5), Size(cap.get(3), cap.get(4)),true);
	return video;
}

void closeVideo(VideoCapture cap, VideoWriter video)
{
	cap.release();
	video.release();
}

Mat getFrame(VideoCapture cap) {
	Mat frame;
	cap >> frame;
	return frame; 
}
