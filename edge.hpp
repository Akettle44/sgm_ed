#ifndef EDGE_H
#define EDGE_H

#include <opencv.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <iostream>
#include <math.h>
#include <vector>

#define ROWS 1080
#define COLS 1920

using namespace std;
using namespace cv;

class edge_detection {

	public: 
		edge_detection(Mat color_image) {
			cvtColor(color_image, img, COLOR_BGR2GRAY);
			//make sure conversion happened
			if(!assert_gray()) {
				exit(EXIT_FAILURE); 
			}
			for(int y = 0; y < ROWS; y++) {
				for(int x = 0; x < COLS; x++) {
					nsgm[y][x] = 0;
					dx[y][x] = 0;
					dy[y][x] = 0;
					sgm[y][x] = 0;
				}
			}
		}

		//member functions
		bool assert_gray();
		float calc_dx(int x, int y);
		float calc_dy(int x, int y);
		int calc_sgm(int dx, int dy);
		Mat find_edges();
		void update_sgm();
		void update_normalized_sgm();
		void update_sgm_div(); 

	private:
		Mat img;
		Mat ret;
		unsigned char nsgm[ROWS][COLS]; 		
		int dx[ROWS][COLS], dy[ROWS][COLS], sgm[ROWS][COLS]; 		
		int sgm_max = 0;
		int threshold = 50;
		int sgm_div = 0;

};

#endif