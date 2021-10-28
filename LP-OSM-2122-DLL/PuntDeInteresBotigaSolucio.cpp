#include "PuntDeInteresBotigaSolucio.h"
#include "pch.h"

using namespace std;

unsigned int  PuntDeInteresBotigaSolucio::getColor()
{
	switch (m_typeOfShop)
	{
	case Shops::SuperMarket:
	{
		return 0xA5BE00;
		break;
	}
	case Shops::Tobacco:
	{
		return 0xFFAD69;
		break;
	}
	case Shops::Bakery:
	{
		return 0xE85D75;
		break;
	}
	default:
	{
		return 0xEFD6AC;
		break;
	}
	}
}