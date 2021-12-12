#pragma once
#include "Ball.h"
#include <math.h>
#include <list>

using namespace std;

class BallTree
{
public:
	BallTree();
	BallTree(Ball ball);
	~BallTree();

	double maxDistance(vector<Coordinate> coordinates, Coordinate point, int index);
	double CalculateDistance(Coordinate point_A, Coordinate point_B);
	Ball* construirBalls(vector<Coordinate> coordinates);

	void inOrdre(vector<list<Coordinate>>& out);
	void postOrdre(vector<list<Coordinate>>& out);
	void preOrdre(vector<list<Coordinate>>& out);

private:
	Ball* m_pepe;
};

void BallTree::inOrdre(vector<list<Coordinate>>& out)
{
	if (this != nullptr)
	{
		if (m_pepe == nullptr)
			return;

		Ball* left_Ball = m_pepe->getEsquerre();
		if (left_Ball != nullptr)
			(*left_Ball).inOrdre(out);

		list<Coordinate> list_Coordinates;
		vector<Coordinate> vector_Coordinates = (*m_pepe).getCoordenades();
		for (int it_root = 0; it_root < vector_Coordinates.size(); it_root++)
			list_Coordinates.emplace_back(vector_Coordinates[it_root]);
		out.push_back(list_Coordinates);

		Ball* right_Ball = m_pepe->getDreta();
		if (right_Ball != nullptr)
			(*right_Ball).inOrdre(out);
	}
}

void BallTree::postOrdre(vector<list<Coordinate>>& out)
{
	if (this != nullptr)
	{
		if (m_pepe == nullptr)
			return;

		Ball* left_Ball = m_pepe->getEsquerre();
		if (left_Ball != nullptr)
			(*left_Ball).inOrdre(out);

		Ball* right_Ball = m_pepe->getDreta();
		if (right_Ball != nullptr)
			(*right_Ball).inOrdre(out);

		list<Coordinate> list_Coordinates;
		vector<Coordinate> vector_Coordinates = (*m_pepe).getCoordenades();
		for (int it_root = 0; it_root < vector_Coordinates.size(); it_root++)
			list_Coordinates.emplace_back(vector_Coordinates[it_root]);
		out.push_back(list_Coordinates);

	}
}

void BallTree::preOrdre(vector<list<Coordinate>>& out)
{
	if (this != nullptr)
	{
		if (m_pepe == nullptr)
			return;

		list<Coordinate> list_Coordinates;
		vector<Coordinate> vector_Coordinates = (*m_pepe).getCoordenades();
		for (int it_root = 0; it_root < vector_Coordinates.size(); it_root++)
			list_Coordinates.emplace_back(vector_Coordinates[it_root]);
		out.push_back(list_Coordinates);

		Ball* left_Ball = m_pepe->getEsquerre();
		if (left_Ball != nullptr)
			(*left_Ball).inOrdre(out);

		Ball* right_Ball = m_pepe->getDreta();
		if (right_Ball != nullptr)
			(*right_Ball).inOrdre(out);
	}
}

double maxDistance(vector<Coordinate> coordinates, Coordinate point, int index)
{
	double max_Distances = CalculateDistance(coordinates[0], point);
	index = 0;

	for (int it_vector = 1; it_vector < coordinates.size(); it_vector++)
	{
		auto aux_distance = CalculateDistance(coordinates[it_vector], point);
		if (max_Distances < aux_distance)
		{ 
			max_Distances = aux_distance;
			index = it_vector;
		}
	}

	return max_Distances;
}

double CalculateDistance(Coordinate point_A, Coordinate point_B)
{
	double lat_Increment = Util::deg2Rad(point_B.lat - point_A.lat);
	double lon_Increment = Util::deg2Rad(point_B.lon - point_A.lon);
	double radical = pow(sin(lat_Increment / 2), 2) + pow(sin(lon_Increment / 2), 2) * cos(Util::deg2Rad(point_A.lat)) * cos(Util::deg2Rad(point_B.lat));
	double distance = atan2(sqrt(radical), sqrt(1 - radical));
	return distance;
}

BallTree::BallTree(Ball ball)
{
	m_pepe = construirBalls(ball.getCoordenades());
}

Ball* BallTree::construirBalls(vector<Coordinate> coordinates)
{
	if (coordinates.size() > 1)
	{
		Ball* newBall = new Ball;
		Coordinate point_C = Util::calcularPuntCentral(coordinates);
		(*newBall).setPivot(point_C);

		int index_Point_A;
		double distance_point_A = maxDistance(coordinates, point_C, index_Point_A);
		(*newBall).setRadius(distance_point_A);

		int index_Point_B;
		double distance_point_B = maxDistance(coordinates, coordinates[index_Point_A], index_Point_B);

		vector<Coordinate> left_Vector, right_Vector;

		for (int it_vector = 0; it_vector < coordinates.size(); it_vector++)
		{
			double first_Distance = CalculateDistance(coordinates[it_vector], coordinates[index_Point_B]);
			double second_Distance = CalculateDistance(coordinates[it_vector], point_C);

			if (first_Distance < second_Distance)
				left_Vector.emplace_back(coordinates[it_vector]);
			else
				right_Vector.emplace_back(coordinates[it_vector]);
		}

		(*newBall).setEsquerre(construirBalls(left_Vector));
		(*newBall).setDreta(construirBalls(right_Vector));

	}
	return nullptr;
}

BallTree::BallTree()
{
	m_pepe = nullptr;
}

BallTree::~BallTree()
{
	delete m_pepe;
}