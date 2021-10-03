#ifndef LP_OSM_2122_XML4OSMUTIL_H
#define LP_OSM_2122_XML4OSMUTIL_H

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

#include <string>
#include <vector>
#include "Common.h"

class XML4OSMUtil {

public:
    XML4OSMUtil();
    ~XML4OSMUtil();

    std::vector<XmlElement> parseXML(const char* file);

private:
    xercesc::XercesDOMParser* m_parser;
    xercesc::DOMDocument* m_xmlDoc;
};

#endif //LP_OSM_2122_XML4OSMUTIL_H
