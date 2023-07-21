#include <iostream>
#include <vector>
// #include <opencv2/opencv.hpp>

#include "DbscanMethod.h"

int main(int argc, char** argv)
{
	std::vector<DbscanPoint> vec_dbscan_point;
	double eps = 2;
	int min_pts = 2;

	std::vector<double> x0{2, 10};
	std::vector<double> x1{2, 5};
	std::vector<double> x2{8, 4};
	std::vector<double> x3{5, 8};
	std::vector<double> x4{7, 5};
	std::vector<double> x5{6, 4};
	std::vector<double> x6{1, 2};
	std::vector<double> x7{4, 9};

	DbscanPoint point0(x0);
	vec_dbscan_point.push_back(point0);
	DbscanPoint point1(x1);
	vec_dbscan_point.push_back(point1);
	DbscanPoint point2(x2);
	vec_dbscan_point.push_back(point2);
	DbscanPoint point3(x3);
	vec_dbscan_point.push_back(point3);
	DbscanPoint point4(x4);
	vec_dbscan_point.push_back(point4);
	DbscanPoint point5(x5);
	vec_dbscan_point.push_back(point5);
	DbscanPoint point6(x6);
	vec_dbscan_point.push_back(point6);
	DbscanPoint point7(x7);
	vec_dbscan_point.push_back(point7);

	// //导入图片
	// cv::Mat src = cv::imread("ali.jpg", cv::IMREAD_UNCHANGED);
	// ////调整图像大小
	// //cv::Size dsize = cv::Size(135, 100);
	// //cv::Mat src;
	// //cv::resize(img, src, dsize, 0, 0, cv::INTER_AREA);
	// //创建画布
	// cv::Mat dst = cv::Mat::zeros(src.size(), CV_8UC1);

	// int h = src.rows;
	// int w = src.cols;

	// int temp = 0;

	// for (int row = 0; row < h; ++row)
	// 	for (int col = 0; col < w; ++col)
	// 	{
	// 		std::vector<double> x_temp{ (double)src.at<cv::Vec3b>(row, col)[0] ,(double)src.at<cv::Vec3b>(row, col)[1] ,(double)src.at<cv::Vec3b>(row, col)[2] };
	// 		DbscanPoint point_temp(x_temp);
	// 		vec_dbscan_point.push_back(point_temp);


	// 		temp++;
	// 		std::cout << "初始化了" << temp << "个点" << std::endl;
	// 	}

	DbscanMethod(vec_dbscan_point, eps, min_pts);

	// auto iter = vec_dbscan_point.begin();

	// for (int row = 0; row < h; ++row)
	// 	for (int col = 0; col < w; ++col)
	// 	{
	// 		if (iter != vec_dbscan_point.end())
	// 			dst.at<uchar>(row, col) = (uchar)iter->cluster * 20;
	// 		iter++;
	// 	}

	// cv::imshow("src", src);
	// cv::imshow("dst", dst);

	// cv::imwrite("dst.jpg", dst);

	// cv::waitKey(0);//等待

	return 0;
}
