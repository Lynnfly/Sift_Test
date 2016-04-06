#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <iostream>
#include "SiftTest.h"

using namespace std;
using namespace cv;

int siftTest::video_Input()
{	
	//-------------------------------------------------------
	//    ʹ��opencv�еķ���������ͷ��ȡ��Ƶ
	//-------------------------------------------------------

	CvCapture* capture = cvCreateCameraCapture(0);   
	//0Ϊ�ⲿ����ͷ��ID��1Ϊ�ʼǱ���������ͷ��ID
	//cvCreateFileCapture(char*name) ��ʾ������Ƶ�õ�ͼ��
	//CvCapture��һ���ṹ�壬��������ͼ�񲶻��������Ϣ�����ļ�����ÿһ֡״̬

	char c;
	IplImage* src;
	cvNamedWindow("camera");
	while (1)
	{
		src = cvQueryFrame(capture);  
		//cvQueryFrame(capture)����ΪCvCapture�ṹ��ָ�룬������ͷ���ļ���ץȡ������һ֡
		//����һ֡���ص��ڴ棬����һ���Ե�ǰ֡��ָ��.ps.�����·����ڴ�
		if (! src) break;
		cvShowImage("camera", src);
		c = waitKey(10);    //��ǰ֡����ʾ��ȴ�10���룬����֡��
		if (c == 27) break;
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("camera");
	return 0;
}

int siftTest::save_Video_to_Img()
{
	//---------------------------------------------------
	//    ������ͷ��ȡ����Ƶ�����ͼƬ
	//    ��ϰ��֡����
	//---------------------------------------------------

	CvCapture* capture = cvCreateCameraCapture(0);    //��ʼ����Ƶ��׽��
	cvQueryFrame(capture);    //��ȡ��Ƶ��Ϣ
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
		img = cvQueryFrame(capture);    //��ȡһ֡ͼƬ
		if (!img) break;
		cvShowImage("camera", img);    //��ʾͼƬ
		c = cvWaitKey(20);
		sprintf(img_name, "%s%d%s", "img", ++i, ".jpg"); 
		cvSaveImage(img_name, img);    //����ͼƬ
//		if (i == NUM_Frame) break;    //����Ƶ�ļ���Ҫ�ӽ�ֹ����
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("camera");
	return 0;
}

int siftTest::video_Sift(Mat g_img)
{
	//----------------------------------------------------------------------------------
	//    ����һ��Ŀ��ͼ��������ͷ��׽����Ƶ��Ѱ��SIFT������ƥ��
	//----------------------------------------------------------------------------------

	cvNamedWindow("match_result");

	//SIFT��������ʼ��
	SiftFeatureDetector siftdtc;
	SiftDescriptorExtractor extractor;
	vector<KeyPoint> kp1, kp2;
	Mat descriptor1, descriptor2, img_matches;
	siftdtc.detect(g_img, kp1);
	extractor.compute(g_img, kp1, descriptor1);

	//��Ƶ��׽����ʼ��
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
		//��ȡһ֡ͼƬ
		img = cvQueryFrame(capture);    
		if (!img) break;

//		two_Img_Sift(g_img, img2);		

		//��Ƶͼ�����������
		Mat img2(img, true);    //��IplImageת����Mat
		siftdtc.detect(img2, kp2);
		extractor.compute(img2, kp2, descriptor2);
		//ƥ��
		BruteForceMatcher<L2<float>> matcher;   
		vector<DMatch> matches;    
		matcher.match(descriptor1, descriptor2, matches);
		//����ȡǰ30�����ƥ����  
		std::nth_element(matches.begin(), matches.begin() + 29, matches.end());  
		matches.erase(matches.begin() + 30, matches.end()); 
		//��ͼ
		drawMatches(g_img, kp1, img2, kp2, matches, img_matches);
		imshow("match_result", img_matches);

		c = cvWaitKey(5);
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("match_result");
	return 0;
}
