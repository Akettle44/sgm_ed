#include "edge.hpp"

//make sure the image is grayscale
bool edge_detection::assert_gray() {
	if(img.channels() > 1) {
		std::cout << "not grayscale";
		return false;
	} 
	return true;
}

//calculate raw horizontal sobel mask
float edge_detection::calc_dx(int x, int y) {
	float dx = -1*(img.at<unsigned char>(y-1, x-1)) + -2*(img.at<unsigned char>(y, x-1)) + 
		-1*(img.at<unsigned char>(y+1, x-1)) + 1*(img.at<unsigned char>(y-1, x+1)) +
		2*(img.at<unsigned char>(y, x+1)) + 1*(img.at<unsigned char>(y+1, x+1));
		
	return abs(dx);
}

//calculate raw vertical sobel mask
float edge_detection::calc_dy(int x, int y) {
	float dy = -1*(img.at<unsigned char>(y+1, x-1)) + -2*(img.at<unsigned char>(y+1, x)) + 
		-1*(img.at<unsigned char>(y+1, x+1)) + 1*(img.at<unsigned char>(y-1, x-1)) +
		2*(img.at<unsigned char>(y-1, x)) + 1*(img.at<unsigned char>(y-1, x+1));

	return abs(dy);
}

//calculate sgm
int edge_detection::calc_sgm(int dx, int dy) {
	return pow(dx, 2) + pow(dy, 2);
}

//calculate the normalized sgm
void edge_detection::update_sgm() {
	for(int y = 1; y < img.rows - 1; y++) {
		for(int x = 1; x < img.cols - 1; x++) {
			dx[y][x] = calc_dx(x, y);

			dy[y][x] = calc_dy(x, y);

			sgm[y][x] = calc_sgm(dx[y][x], dy[y][x]);
			if(sgm[y][x] > sgm_max) { sgm_max = sgm[y][x]; }
		}				
	}
	update_sgm_div();
}

void edge_detection::update_normalized_sgm() {
	for(int y = 1; y < img.rows - 1; y++) {
		for(int x = 1; x < img.cols - 1; x++) {
			nsgm[y][x] = sgm[y][x] / sgm_div; 
			img.at<int>(y, x) = nsgm[y][x];
		}
	}
}

void edge_detection::update_sgm_div() {
	sgm_div = sgm_max / 255;
}

//create binary image
Mat edge_detection::find_edges() {
	for(int y = 0; y < img.cols; y++) {
		for(int x = 0; x < img.rows; x++) {
			if(img.at<int>(y, x) > threshold) {
				ret.at<unsigned char>(y, x) = 255;
			} else {
				ret.at<unsigned char>(y, x) = 0;
			}
		}
	}
	return ret;
}
