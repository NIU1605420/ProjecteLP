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
	Coordinate nodeMesProper(Coordinate pdi, Coordinate& Q, Ball* bola);

private:
	Ball* m_pepe;
};

Coordinate nodeMesProper(Coordinate pdi, Coordinate& Q, Ball* bola)
{
	Coordinate point_Central = (*bola).getPivot();
	double distance_point_1 = Util::DistanciaHaversine(pdi, point_Central);
	double distance_point_2 = Util::DistanciaHaversine(Q, point_Central);

	if (distance_point_1 - bola->getRadi() >= distance_point_2)
		return Q;
	if(((*bola).getEsquerre() == nullptr && (*bola).getDreta() == nullptr))
	{
		vector<Coordinate> vector_Coordinates = (*bola).getCoordenades();
		double distance_point_i = Util::DistanciaHaversine(pdi, vector_Coordinates[0]);
		double distance_point_Q = Util::DistanciaHaversine(pdi, Q);
		if (distance_point_Q > distance_point_i)
			Q = vector_Coordinates[0];
	}
	else
	{
		double distance_right_ball = Util::DistanciaHaversine(pdi, (*bola).getDreta()->getPivot());
		double distance_left_ball = Util::DistanciaHaversine(pdi, (*bola).getEsquerre()->getPivot());

		if (distance_right_ball < distance_left_ball) //Cerca de la bola x la derta i despres x l'esquerra
		{
			Q = nodeMesProper(pdi, Q, bola->getDreta());
			Q = nodeMesProper(pdi, Q, bola->getEsquerre());
		}
		else // Cerca x la bola esquerra i despres x la dreta.
		{
			Q = nodeMesProper(pdi, Q, bola->getEsquerre());
			Q = nodeMesProper(pdi, Q, bola->getDreta());
		}
	}
	
	return Q;
}

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
	double max_Distances = Util::DistanciaHaversine(coordinates[0], point);
	index = 0;

	for (int it_vector = 1; it_vector < coordinates.size(); it_vector++)
	{
		auto aux_distance = Util::DistanciaHaversine(coordinates[it_vector], point);
		if (max_Distances < aux_distance)
		{ 
			max_Distances = aux_distance;
			index = it_vector;
		}
	}

	return max_Distances;
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
		(*newBall).setCoordenades(coordinates);
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
			double first_Distance = CalculateDistance(coordinates[it_vector], coordinates[index_Point_A]);
			double second_Distance = CalculateDistance(coordinates[it_vector], coordinates[index_Point_B]);

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