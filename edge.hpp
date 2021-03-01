#ifndef EDGE_H
#define EDGE_H

#include <opencv.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <iostream>
#include <math.h>

using namespace cv;

bool assert_gray(Mat img);
float calc_dx(Mat img, int x, int y);
float calc_dy(Mat img, int x, int y);
int calc_sgm(int dx, int dy);
Mat find_edges(Mat img, int x, int y, unsigned char threshold);

#endif