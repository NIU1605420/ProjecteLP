#include "pch.h"
#include "CamiSolucio.h"

CamiSolucio::CamiSolucio(CamiSolucio& camiSolucio)
{
	camiSolucio.m_Coordinates.resize(m_Coordinates.size());
	for (int i = 0; i < m_Coordinates.size(); i++)
		m_Coordinates.push_back(camiSolucio.m_Coordinates[i]);
}
