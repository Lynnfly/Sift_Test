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
	int one_Img_Sift(Mat img);    //��Ⲣ����һ��ͼƬ��sift������
	int two_Img_Sift(Mat img1, Mat img2);    //�������ͼƬ�������㣬������ƥ��ͼ
	int video_Input();    //������ͷ������Ƶ
	int save_Video_to_Img();    //������ͷ�����ͼ�񱣴��ͼƬ����֡����
	int video_Sift(Mat g_img);    //����Ŀ��ͼ��������ͷ��׽����Ƶ��Ѱ��SIFT������ƥ��
};