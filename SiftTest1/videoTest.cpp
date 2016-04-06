#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <iostream>
#include "SiftTest.h"

using namespace std;
using namespace cv;

int siftTest::video_Input()
{	
	//-------------------------------------------------------
	//    使用opencv中的方法打开摄像头读取视频
	//-------------------------------------------------------

	CvCapture* capture = cvCreateCameraCapture(0);   
	//0为外部摄像头的ID，1为笔记本内置摄像头的ID
	//cvCreateFileCapture(char*name) 表示解码视频得到图像
	//CvCapture是一个结构体，用来保存图像捕获所需的信息，如文件名、每一帧状态

	char c;
	IplImage* src;
	cvNamedWindow("camera");
	while (1)
	{
		src = cvQueryFrame(capture);  
		//cvQueryFrame(capture)参数为CvCapture结构的指针，从摄像头或文件中抓取并返回一帧
		//将下一帧加载到内存，返回一个对当前帧的指针.ps.不重新分配内存
		if (! src) break;
		cvShowImage("camera", src);
		c = waitKey(10);    //当前帧被显示后等待10毫秒，控制帧率
		if (c == 27) break;
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("camera");
	return 0;
}

int siftTest::save_Video_to_Img()
{
	//---------------------------------------------------
	//    将摄像头读取的视频保存成图片
	//    练习单帧处理
	//---------------------------------------------------

	CvCapture* capture = cvCreateCameraCapture(0);    //初始化视频捕捉器
	cvQueryFrame(capture);    //获取视频信息
	int frameH = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
	int frameW = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
	int fps = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
	int numFrames = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
	
	int i = 0;
	char img_name[13];
	char c;
	IplImage* img = 0;
	cvNamedWindow("camera");
	while (1)
	{
		img = cvQueryFrame(capture);    //获取一帧图片
		if (!img) break;
		cvShowImage("camera", img);    //显示图片
		c = cvWaitKey(20);
		sprintf(img_name, "%s%d%s", "img", ++i, ".jpg"); 
		cvSaveImage(img_name, img);    //保存图片
//		if (i == NUM_Frame) break;    //读视频文件需要加截止条件
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("camera");
	return 0;
}

int siftTest::video_Sift(Mat g_img)
{
	//----------------------------------------------------------------------------------
	//    给定一张目标图像，在摄像头捕捉的视频中寻找SIFT特征点匹配
	//----------------------------------------------------------------------------------

	cvNamedWindow("match_result");

	//SIFT特征检测初始化
	SiftFeatureDetector siftdtc;
	SiftDescriptorExtractor extractor;
	vector<KeyPoint> kp1, kp2;
	Mat descriptor1, descriptor2, img_matches;
	siftdtc.detect(g_img, kp1);
	extractor.compute(g_img, kp1, descriptor1);

	//视频捕捉器初始化
	CvCapture* capture = cvCreateCameraCapture(0);    
	cvQueryFrame(capture);    
	int frameH = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
	int frameW = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
	int fps = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
	int numFrames = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);

	int i = 0;
	char c;
	IplImage* img = 0;
	while (1)
	{
		//获取一帧图片
		img = cvQueryFrame(capture);    
		if (!img) break;

//		two_Img_Sift(g_img, img2);		

		//视频图像的特征点检测
		Mat img2(img, true);    //将IplImage转换成Mat
		siftdtc.detect(img2, kp2);
		extractor.compute(img2, kp2, descriptor2);
		//匹配
		BruteForceMatcher<L2<float>> matcher;   
		vector<DMatch> matches;    
		matcher.match(descriptor1, descriptor2, matches);
		//排序取前30个最佳匹配结果  
		std::nth_element(matches.begin(), matches.begin() + 29, matches.end());  
		matches.erase(matches.begin() + 30, matches.end()); 
		//画图
		drawMatches(g_img, kp1, img2, kp2, matches, img_matches);
		imshow("match_result", img_matches);

		c = cvWaitKey(5);
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("match_result");
	return 0;
}
