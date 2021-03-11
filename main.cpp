#include <iostream>
#include <stdlib.h>
#include "VideoCapture.hpp"
#include "edge.hpp"

using namespace std;
using namespace cv;

int main() {

	//init video class
	video vid;
	Mat frame, ret;

	for(;;) {

		frame = vid.getFrame();
		edge ed(frame);
		ed.update_sgm();
		ed.update_normalized_sgm();
		ret = ed.find_edges();
		vid.writeFrame(ret);
		imshow("Edges", ret);

		if(waitKey(10) == 27) {
			break;
		}
	}

	return 0;
}