#pragma once
#ifndef DBSCAN_H
#define DBSCAN_H

#include <iostream>
#include <math.h>
#include <vector>
#include <stack>

static int S_temp = 0;

enum  POINT_TYPE
{
	POINT_DEFAULT,		// 未定义
	POINT_CORE,			// 核心对象
	POINT_BOUNDARY,		// 边界对象
	POINT_NOISE			// 噪声
};
enum POINT_CALCULATE
{
	CALCULATE_NO,		//未被计算
	CALCULATE_YES		//已被计算
};
enum POINT_VISIT
{
	VISIT_NO,			// 未被遍历
	VISIT_YES			// 已被遍历
};


/*
DbscanPoint初始化需要传入一个std::vector<double>类型的数据
这里考虑的Point并不局限于一个二维的点，可以是任意维度
一个点所有维度的坐标按照一定顺序存放在std::vector<double>中
*/
class DbscanPoint
{
	//friend double CalculateDistance(DbscanPoint* point1, DbscanPoint* point2);
	//friend void Dbscan(DbscanPoint* dbscan_point_ptr, int cluster_current);
	//friend void DBSCAN(std::vector<DbscanPoint>& vec_dbscan_point, double Eps, int MinPts);

public:
	DbscanPoint() = default;
	DbscanPoint(std::vector<double> xn) :xn(xn) { }

public:
	std::vector<double> xn;//坐标（不仅限于二维）
	int cluster = 0;//第几个簇
	int num_pts = 1;//记录邻域内有多少个点（包括自己，所以初始值为1）
	int point_type = POINT_DEFAULT;//点的类型
	int calculated = CALCULATE_NO;//点是否被计算
	int  visited = VISIT_NO;//点是否被遍历
	std::vector<DbscanPoint*> vec_dbscan_point_ptr;//用于存放邻域内的点
};


double CalculateDistance(DbscanPoint* point1, DbscanPoint* point2);


/*
参数：
vec_dbscan_point	需要输入一个DbscanPoint类型的vector，这个vector里的所有DbscanPoint应该是已经初始化过点坐标的
Eps					给定的邻域的范围Eps
MinPts				在邻域至少有MinPts个点（包括自己）才能叫做核心点
*/
void DbscanMethod(std::vector<DbscanPoint>& vec_dbscan_point, const double& Eps, const int& MinPts);

#endif