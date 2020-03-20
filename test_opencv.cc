#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

// Define the window.
const int kHeight = 400;
const int kWidth = 400;
Mat img = Mat::zeros(kWidth, kHeight, CV_8UC3);

int main()
{
  namedWindow("Window", 1);
  imshow("Window", img);
  waitKey(0);
  return 0;
}
