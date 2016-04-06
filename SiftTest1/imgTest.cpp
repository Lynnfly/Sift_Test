#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <vector>
#include "SiftTest.h"

using namespace cv;
using namespace std;  

int siftTest::one_Img_Sift(Mat img)
{
	//---------------------------------------------------
	//  ��Ⲣ��ʾһ��ͼƬ��SIFT������
	//---------------------------------------------------

	SIFT sift;    //ʵ����SIFT��  
//	SIFT sift(40);    //ֻ���40��������

	vector<KeyPoint> key_points;    //������  
	Mat descriptors, mascara;    // descriptorsΪ��������mascaraΪ�������  
	Mat output_img;    //���ͼ�����  

	sift(img, mascara, key_points, descriptors);    //ִ��SIFT���㣬�����ͼ���л���������  
	drawKeypoints(img,     //����ͼ��  
		key_points,      //������ʸ��  
		output_img,      //���ͼ��  
		Scalar::all(-1),      //�������������ɫ��Ϊ���  
		//��������Ϊ���Ļ�Բ��Բ�İ뾶��ʾ������Ĵ�С��ֱ�߱�ʾ������ķ���  
		DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	namedWindow("SIFT");
	imshow("SIFT", output_img);
	waitKey(0);

	return 0;
}

int siftTest::two_Img_Sift(Mat img1, Mat img2)
{
	//---------------------------------------------------
	//    �ֱ�������ͼƬ��SIFT�����㣬��ƥ��
	//---------------------------------------------------

	//sift�������
	SiftFeatureDetector  siftdtc;
	vector<KeyPoint>kp1, kp2;
    siftdtc.detect(img1, kp1);
	siftdtc.detect(img2, kp2);
	
	//����sift������
	Mat outimg1;
	drawKeypoints(img1, kp1, outimg1);
//	imshow("image1 keypoints", outimg1);
	waitKey();

    Mat outimg2;
	drawKeypoints(img2, kp2, outimg2);
//	imshow("image2 keypoints", outimg2);
	waitKey();

	//��ȡ����������������������
	SiftDescriptorExtractor extractor;    //SIFT����̽����
	Mat descriptor1, descriptor2;    //�����������Ӧ����������
	extractor.compute(img1, kp1, descriptor1);
	extractor.compute(img2, kp2, descriptor2);
	// keypointֻ������sift��⵽���������һЩ������Ϣ��
	// ��sift����ȡ����������������ʵ������������棬
	// ��������ͨ��SiftDescriptorExtractor ��ȡ���������һ��Mat�����ݽṹ��

	//*****************************************
	//����������ȡ����һ�ֱ�﷽ʽ
	//SIFT sift1,sift2;
	//vector<KeyPoint>kp1, kp2;
	//Mat descriptor1, descriptor2,mascara;
	//sift1(img1,mascara,kp1,descriptor1);
	//sift2(img2,mascara,kp2,descriptor2);
	//*****************************************

	//��������ƥ��
	BruteForceMatcher<L2<float>> matcher;    //����ƥ����
	vector<DMatch> matches;    //����ƥ��������ƥ��������
	matcher.match(descriptor1, descriptor2, matches);

	//������ȡ��ǰ30�����ƥ��������������С  
	std::nth_element(matches.begin(),     //ƥ�������ӵĳ�ʼλ��  
		matches.begin() + 29,     // ���������  
		matches.end());       // ����λ��  
	matches.erase(matches.begin() + 30, matches.end());    //�޳��������ƥ���� 

	//����ƥ��ͼ
    Mat img_matches;
	drawMatches(img1, kp1, img2, kp2, matches, img_matches);
	imshow("matches", img_matches);

//	waitKey();
	return 0;
}
