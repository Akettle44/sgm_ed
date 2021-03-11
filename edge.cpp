#include "edge.hpp"

//make sure the image is grayscale
bool edge::assert_gray() {
	if(img.channels() > 1) {
		std::cout << "not grayscale";
		return false;
	} 
	return true;
}

//calculate raw horizontal sobel mask
float edge::calc_dx(int x, int y) {
	float dx = -1*(img.at<unsigned char>(y-1, x-1)) + -2*(img.at<unsigned char>(y, x-1)) + 
		-1*(img.at<unsigned char>(y+1, x-1)) + 1*(img.at<unsigned char>(y-1, x+1)) +
		2*(img.at<unsigned char>(y, x+1)) + 1*(img.at<unsigned char>(y+1, x+1));
		
	return abs(dx);
}

//calculate raw vertical sobel mask
float edge::calc_dy(int x, int y) {
	float dy = -1*(img.at<unsigned char>(y+1, x-1)) + -2*(img.at<unsigned char>(y+1, x)) + 
		-1*(img.at<unsigned char>(y+1, x+1)) + 1*(img.at<unsigned char>(y-1, x-1)) +
		2*(img.at<unsigned char>(y-1, x)) + 1*(img.at<unsigned char>(y-1, x+1));

	return abs(dy);
}

//calculate sgm
int edge::calc_sgm(int dx, int dy) {
	return pow(dx, 2) + pow(dy, 2);
}

//calculate the normalized sgm
void edge::update_sgm() {

	int dx = 0;
	int dy = 0;

	for(int y = 1; y < img.rows - 1; y++) {
		for(int x = 1; x < img.cols - 1; x++) {
			dx = calc_dx(x, y);

			dy = calc_dy(x, y);

			sgm[y][x] = calc_sgm(dx, dy);
			if(sgm[y][x] > sgm_max) { sgm_max = sgm[y][x]; }
		}				
	}
	update_sgm_div();
}

void edge::update_normalized_sgm() {
	for(int y = 1; y < img.rows - 1; y++) {
		for(int x = 1; x < img.cols - 1; x++) {
			nsgm[y][x] = (unsigned char)(sgm[y][x] / sgm_div); 
			img.at<unsigned char>(y, x) = nsgm[y][x];
		}
	}
}

void edge::update_sgm_div() {
	sgm_div = sgm_max / 255;
}

//create binary image
Mat edge::find_edges() {
	for(int y = 0; y < img.rows; y++) {
		for(int x = 0; x < img.cols; x++) {
			if(img.at<unsigned char>(y, x) > threshold) {
				img.at<unsigned char>(y, x) = 255;
			} else {
				img.at<unsigned char>(y, x) = 0;
			}
		}
	}
	return img;
}