#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "VideoCapture.hpp"
#include "edge.hpp"
#include <vector>
#include <videoio.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <unistd.h>

using namespace std;
using namespace cv;

int main() {

	//init video class
	video vid = video();
	Mat frame, ret;

	while(1) {

		frame = vid.getFrame();
		edge_detection ed = edge_detection(frame);
		ed.update_sgm();
		//ed.update_normalized_sgm();
		//ret = ed.find_edges();
		imshow("Edges", frame);
		waitKey(10);
	}
	return 0;
}