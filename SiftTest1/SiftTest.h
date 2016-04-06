#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

class siftTest
{
public:
	int one_Img_Sift(Mat img);    //检测并画出一张图片的sift特征点
	int two_Img_Sift(Mat img1, Mat img2);    //检测两张图片的特征点，并画出匹配图
	int video_Input();    //从摄像头读入视频
	int save_Video_to_Img();    //将摄像头捕获的图像保存成图片，单帧处理
	int video_Sift(Mat g_img);    //给定目标图像，在摄像头捕捉的视频中寻找SIFT特征点匹配
};