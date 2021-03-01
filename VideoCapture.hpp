#ifndef CAPTURE_H
#define CAPTURE_H

#include <opencv.hpp>
#include <highgui/highgui.hpp>
#include <videoio.hpp>

using namespace cv;

VideoCapture initCapture();
Mat getFrame(VideoCapture cap);
VideoWriter initWriter(VideoCapture cap);
void closeVideo(VideoCapture cap, VideoWriter video);

#endif 
