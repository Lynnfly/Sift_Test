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
	//  检测并显示一张图片的SIFT特征点
	//---------------------------------------------------

	SIFT sift;    //实例化SIFT类  
//	SIFT sift(40);    //只检测40个特征点

	vector<KeyPoint> key_points;    //特征点  
	Mat descriptors, mascara;    // descriptors为描述符，mascara为掩码矩阵  
	Mat output_img;    //输出图像矩阵  

	sift(img, mascara, key_points, descriptors);    //执行SIFT运算，在输出图像中绘制特征点  
	drawKeypoints(img,     //输入图像  
		key_points,      //特征点矢量  
		output_img,      //输出图像  
		Scalar::all(-1),      //绘制特征点的颜色，为随机  
		//以特征点为中心画圆，圆的半径表示特征点的大小，直线表示特征点的方向  
		DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	namedWindow("SIFT");
	imshow("SIFT", output_img);
	waitKey(0);

	return 0;
}

int siftTest::two_Img_Sift(Mat img1, Mat img2)
{
	//---------------------------------------------------
	//    分别检测两张图片的SIFT特征点，并匹配
	//---------------------------------------------------

	//sift特征检测
	SiftFeatureDetector  siftdtc;
	vector<KeyPoint>kp1, kp2;
    siftdtc.detect(img1, kp1);
	siftdtc.detect(img2, kp2);
	
	//画出sift特征点
	Mat outimg1;
	drawKeypoints(img1, kp1, outimg1);
//	imshow("image1 keypoints", outimg1);
	waitKey();

    Mat outimg2;
	drawKeypoints(img2, kp2, outimg2);
//	imshow("image2 keypoints", outimg2);
	waitKey();

	//提取特征点描述，即特征向量
	SiftDescriptorExtractor extractor;    //SIFT特征探测器
	Mat descriptor1, descriptor2;    //保存特征点对应的特征向量
	extractor.compute(img1, kp1, descriptor1);
	extractor.compute(img2, kp2, descriptor2);
	// keypoint只保存了sift检测到的特征点的一些基本信息，
	// 但sift所提取出来的特征向量其实不是在这个里面，
	// 特征向量通过SiftDescriptorExtractor 提取，结果放在一个Mat的数据结构中

	//*****************************************
	//特征向量提取的另一种表达方式
	//SIFT sift1,sift2;
	//vector<KeyPoint>kp1, kp2;
	//Mat descriptor1, descriptor2,mascara;
	//sift1(img1,mascara,kp1,descriptor1);
	//sift2(img2,mascara,kp2,descriptor2);
	//*****************************************

	//特征向量匹配
	BruteForceMatcher<L2<float>> matcher;    //暴力匹配器
	vector<DMatch> matches;    //保存匹配结果，即匹配器算子
	matcher.match(descriptor1, descriptor2, matches);

	//排序，提取出前30个最佳匹配结果，即距离最小  
	std::nth_element(matches.begin(),     //匹配器算子的初始位置  
		matches.begin() + 29,     // 排序的数量  
		matches.end());       // 结束位置  
	matches.erase(matches.begin() + 30, matches.end());    //剔除掉其余的匹配结果 

	//画出匹配图
    Mat img_matches;
	drawMatches(img1, kp1, img2, kp2, matches, img_matches);
	imshow("matches", img_matches);

//	waitKey();
	return 0;
}
