#pragma once

#include "Util.h"
#include <vector>
#include <list>

class Ball {

	public:
		Ball() {
			m_left = nullptr;
			m_right = nullptr;
			m_radi = 0.001;
			m_pivot = Coordinate{ 0.0, 0.0 };
		}

		Coordinate getPivot() {
			return m_pivot;
		}

		double getRadi() {
			return m_radi;
		}

		Ball* getEsquerre() {
			return m_right;
		}

		Ball* getDreta() {
			return m_left;
		}

		std::vector<Coordinate>& getCoordenades() {
			return m_coordenades;
		}

		void setPivot(Coordinate pivot) {
			m_pivot = pivot;
		}

		void setRadius(double radi) {
			m_radi = radi;
		}

		void setEsquerre(Ball* right) {
			m_right = right;
		}

		void setDreta(Ball* left) {
			m_left = left;
		}

		void setCoordenades(std::vector<Coordinate>& coordenades) {
			m_coordenades = coordenades;
		}

		void inOrdre(vector<list<Coordinate>>& out)
		{
			if (this != nullptr)
			{
				if (m_left != nullptr)
					(*m_left).inOrdre(out);

				list<Coordinate> list_Coordinates;
				for (int it_root = 0; it_root < m_coordenades.size(); it_root++)
					list_Coordinates.emplace_back(m_coordenades[it_root]);
				out.push_back(list_Coordinates);

				if (m_right != nullptr)
					(*m_right).inOrdre(out);
			}
		}

		void postOrdre(vector<list<Coordinate>>& out)
		{
			if (this != nullptr)
			{
				if (m_left != nullptr)
					(*m_left).inOrdre(out);

				if (m_right != nullptr)
					(*m_right).inOrdre(out);

				list<Coordinate> list_Coordinates;
				for (int it_root = 0; it_root < m_coordenades.size(); it_root++)
					list_Coordinates.emplace_back(m_coordenades[it_root]);
				out.push_back(list_Coordinates);
			}
		}

		void preOrdre(vector<list<Coordinate>>& out)
		{
			if (this != nullptr)
			{
				list<Coordinate> list_Coordinates;
				for (int it_root = 0; it_root < m_coordenades.size(); it_root++)
					list_Coordinates.emplace_back(m_coordenades[it_root]);
				out.push_back(list_Coordinates);

				if (m_left != nullptr)
					(*m_left).inOrdre(out);

				if (m_right != nullptr)
					(*m_right).inOrdre(out);
			}
		}
		

	private:
		Ball* m_left = nullptr;
		Ball* m_right = nullptr;
		double m_radi;
		Coordinate m_pivot;
		std::vector<Coordinate> m_coordenades;

};

