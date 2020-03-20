#include <iostream>
#include <vector>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

class SortVisualization
{
 public:
  // Initializes the size of the window.
  SortVisualization(int w = 1000, int h = 700) : width(w), height(h)
  {
    img = Mat::zeros(height, width, CV_8UC3);
  }

  void generate_random_nums()
  {
    int sz = width / 10;
    srand(time(nullptr));
    for (int i = 0; i < sz; ++i)
      nums.push_back(rand() % height);
  }

  void set_nums(vector<int>& nums)
  {
    for (int i = 0; i < width / 10; ++i)
      this->nums.push_back(nums[i]);
  }

  // The data is drawn as a bar graph, with each column having a width of 10px.
  void show()
  {
    int sz = 0;
    for (int i = 0; i < nums.size(); ++i)
    {
      sz = i * 10;
      rectangle(img, Rect(Point(sz+2, nums[i]), Point(sz+10, height)), Scalar(255, 0, 0));
    }
    imshow("Window", img);
    waitKey(1000); // Show 1S.
  }

  // Bubble Sort
  // Time complexity: O(n^2)
  // Space complexity: O(1)
  void bubble_sort()
  {
    bool sorted = false;
    for (int i = 0; i < nums.size() && !sorted; ++i)
    {
      sorted = true;
      for (int j = 1; j < nums.size() - i; ++j)
      {
        if (nums[j] > nums[j - 1])
        {
          swap(nums[j], nums[j - 1]);
          sorted = false;
        }
        update();
      }
    }
    sorted_show();
  }

  // Shell Sort
  // Time complexity: O(n^2)
  // Space complexity: O(1)
  void shell_sort()
  {
    int h = 1;

    while (h < nums.size() / 3)
      h = (h * 3) + 1; // step: 1 4 13 43 ...

    while (h >= 1)
    {
      for (int i = h; i < nums.size(); ++i)
      {
        for (int j = i; j >= h; j -= h)
        {
          if (nums[j] < nums[j - h])
            swap(nums[j], nums[j - h]);
          
          update();
        }
      }
      h /= 3;
    }

    sorted_show();
  }


 private:
  void update()
  {
    img.setTo(0); // clear the window.
    int sz = 0;
    for (int i = 0; i < nums.size(); ++i)
    {
      sz = i * 10;
      rectangle(img, Rect(Point(sz+2, nums[i]), Point(sz+10, height)), Scalar(255, 0, 0));
    }

    imshow("Window", img);
    waitKey(10); // delay 10 ms.
  }

  void sorted_show()
  {
    int sz = 0;
    for (int i = 0; i < nums.size(); ++i)
    {
      sz = i * 10;
      rectangle(img, Rect(Point(sz+2, nums[i]), Point(sz+10, height)), Scalar(0, 255, 0));
      imshow("Window", img);
      waitKey(20);
    }
    waitKey(0); // Press any key to continue.
  }

 private:
  int width;
  int height;
  Mat img;
  vector<int> nums;
};


// You can customize your own data in this function.
void generate_order_nums(vector<int>& nums, int sz = 100)
{
  srand(time(nullptr));
  for (int i = 0; i < sz; ++i)
    nums.push_back(i);
}

int main()
{
  // 0. Input the window size you need.
  char ch = 'Y';
  cout << "Input Window width and height. Use defauls: 1000x700 (Y/N) ";
  cin >> ch;
  int width = 1000, height = 700;
  if (ch != 'Y')
    cin >> width >> height;

  // 1. Initializes Window size.
  SortVisualization* sort = new SortVisualization(width, height);
  
  // 2.1 Initializes the data to be sorted. Use default data.
  sort->generate_random_nums();
  
  // 2.2 Initializes the data to be sorted. Use your own data.
  // vector<int> nums;
  // generate_order_nums(nums);
  // sort->set_nums(nums);

  // 3. Show Window.
  sort->show();

  // 4. Test sort algorithm.
  sort->bubble_sort();
  // sort->shell_sort();

  return 0;
}
