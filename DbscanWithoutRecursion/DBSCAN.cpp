#include "DBSCAN.h"

double CalculateDistance(DbscanPoint* point1, DbscanPoint* point2)
{
	if (point1->xn.size() != point2->xn.size())
	{
		std::cout << "数据点异常" << std::endl;
		return 0;
	}
	double distance = 0;

	double sum = 0;
	for (size_t i = 0; i != point1->xn.size(); ++i)
		sum += (point1->xn[i] - point2->xn[i]) * (point1->xn[i] - point2->xn[i]);

	distance = sqrt(sum);

	return distance;
}


void DbscanMethod(std::vector<DbscanPoint>& vec_dbscan_point, const double& Eps, const int& MinPts)
{
	std::vector<DbscanPoint*> vec_dbscan_point_ptr;//先转化为指针，保证后面迭代的一致性
	for (auto &i : vec_dbscan_point)
		vec_dbscan_point_ptr.push_back(&i);

	//第1步
	//计算所有两点间的距离
	//确定每个点的类型
	//存每个点后面的邻域内的点
	for (auto m : vec_dbscan_point_ptr)
	{
		for (auto n : vec_dbscan_point_ptr)
			if (n->calculated == CALCULATE_NO && m != n)
			{
				double distance = CalculateDistance(m, n);

				if (distance <= Eps)
				{
					//密度增加
					m->num_pts++;
					n->num_pts++;
					//将点记录到自己的邻域内
					m->vec_dbscan_point_ptr.push_back(n);
					n->vec_dbscan_point_ptr.push_back(m);
				}
			}
		m->calculated = CALCULATE_YES;

		if (m->num_pts >= MinPts)			//密度大于一定值就是核心点
			m->point_type = POINT_CORE;
		else
			m->point_type = POINT_NOISE;	//其它的暂时记为噪声
	}

	int cluster_current = 0;
	for (auto m : vec_dbscan_point_ptr)
	{
		std::stack<DbscanPoint*> ps;

		if (m->visited == VISIT_YES || m->point_type != POINT_CORE)
			continue;
		++cluster_current;//进入一个新的簇
		m->cluster = cluster_current;

		ps.push(m);
		DbscanPoint* current_ptr;

		while (!ps.empty())
		{
			current_ptr = ps.top();
			ps.pop();
			if (current_ptr->visited == VISIT_YES)
				continue;
			current_ptr->visited = VISIT_YES;
			if (current_ptr->point_type == POINT_CORE)
			{
				for (auto n : current_ptr->vec_dbscan_point_ptr)
				{
					if (n->visited == VISIT_YES)
						continue;
					ps.push(n);					
				}
				current_ptr->cluster = cluster_current;
			}
			else
			{
				current_ptr->point_type == POINT_BOUNDARY;
				current_ptr->cluster = cluster_current;
			}

			++S_temp;
			std::cout << "处理了" << S_temp << "个点" << std::endl;
		}
	}
}