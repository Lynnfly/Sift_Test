#include "SiftTest.h"

int main()
{
	siftTest s;
	//------------------------img_Test------------------------
	//Mat img1 = imread("3.jpg");
	//Mat img2 = imread("4.jpg");
	////Èç¹û¶ÁÈëÍ¼ÏñÊ§°Ü
	//if (img1.empty())
	//{
	//	fprintf(stderr, "Can not load image1 \n");
	//	return -1;
	//}
	//if (img2.empty())
	//{
	//	fprintf(stderr, "Can not load image2\n");
	//	return -1;
	//}

	//s.one_Img_Sift(img1);
	//s.two_Img_Sift(img1, img2);

	//------------------------video_Test------------------------
//	s.video_Input();
//	s.save_Video_to_Img();

	Mat g_img = imread("g.jpg");
	if (g_img.empty())
	{
		fprintf(stderr, "Can not load goal_image \n");
		return -1;
	}
	s.video_Sift(g_img);

	return 0;
}