#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "VideoCapture.h"
#include "edge.h"
#include <vector>

using namespace std;
using namespace cv;

int main() {

	//init variables
	VideoCapture cap;
	VideoWriter video;

	cap = initCapture();
	video = initWriter(cap);
	Mat frame, gray_f, ret;
	int sgm_max = 0;
	//raw dx, dy, and sgm
	vector<vector<int>> dx, dy, sgm; 		
	//normalized dx, dy, and sgm
	vector<vector<unsigned char>> nsgm; 		
	int threshold = 50;
	int sgm_div = 0;

	while(1) {

		frame = getFrame(cap);
		cvtColor(frame, gray_f, COLOR_BGR2GRAY);
		for(int y = 0; y < gray_f.rows; y++) {
			for(int x = 0; x < gray_f.cols; x++) {
				dx[y][x] = calc_dx(gray_f, x, y);

				dy[y][x] = calc_dy(gray_f, x, y);

				sgm[y][x] = calc_sgm(dx[y][x], dy[y][x]);
				if(sgm[y][x] > sgm_max) { sgm_max = sgm[y][x]; }
			}				
		}

		//normalizing sgm
		sgm_div = sgm_max / 255;

		for(int y = 0; y < gray_f.rows; y++) {
			for(int x = 0; x < gray_f.cols; x++) {
				nsgm[y][x] = sgm[y][x] / sgm_div; 
				gray_f.at<int>(y, x) = nsgm[y][x];
				ret = find_edges(gray_f, x, y, threshold);
			}
		}

		imshow("Edges", ret);
	}

	return 0;
}