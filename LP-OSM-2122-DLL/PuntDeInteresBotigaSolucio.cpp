#include "PuntDeInteresBotigaSolucio.h"
#include "pch.h"

using namespace std;

unsigned int  PuntDeInteresBotigaSolucio::getColor()
{
	if (m_typeOfShop == "supermarket")
		return 0xA5BE00;
	else if (m_typeOfShop == "tobacco")
		return 0xFFAD69;
	else if (m_typeOfShop == "bakery")
		return 0xE85D75;
	else 
		return 0xEFD6AC;
}