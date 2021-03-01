#include "edge.h"

//make sure the image is grayscale
bool assert_gray(Mat img) {
	if(img.channels() > 1) {
		std::cout << "not grayscale";
		return false;
	} 
	return true;
}

//calculate raw horizontal sobel mask
float calc_dx(Mat img, int x, int y) {
	float dx = -1*(img.at<unsigned char>(y-1, x-1)) + -2*(img.at<unsigned char>(y, x-1)) + 
		-1*(img.at<unsigned char>(y+1, x-1)) + 1*(img.at<unsigned char>(y-1, x+1)) +
		2*(img.at<unsigned char>(y, x+1)) + 1*(img.at<unsigned char>(y+1, x+1));
		
	return abs(dx);
}

//calculate raw vertical sobel mask
float calc_dy(Mat img, int x, int y) {
	float dy = -1*(img.at<unsigned char>(y+1, x-1)) + -2*(img.at<unsigned char>(y+1, x)) + 
		-1*(img.at<unsigned char>(y+1, x+1)) + 1*(img.at<unsigned char>(y-1, x-1)) +
		2*(img.at<unsigned char>(y-1, x)) + 1*(img.at<unsigned char>(y-1, x+1));

	return abs(dy);
}

int calc_sgm(float dx, float dy) {
	return pow(dx, 2) + pow(dy, 2);
}

Mat find_edges(Mat img, int x, int y, unsigned char threshold) {
	for(int y = 0; y < img.cols; y++) {
		for(int x = 0; x < img.rows; x++) {
		if(img.at<unsigned char>(y, x) > threshold) {
			img.at<unsigned char>(y, x) = 255;
		} else {
			img.at<unsigned char>(y, x) = 0;
		}
	}
	return img;
}
