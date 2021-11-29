#include "pch.h"
#include <iostream>
#include "XML4OSMUtil.h"


XML4OSMUtil::XML4OSMUtil() {
    xercesc::XMLPlatformUtils::Initialize();
    this->m_parser = new xercesc::XercesDOMParser();
    this->m_xmlDoc = nullptr;
}


std::vector<XmlElement> XML4OSMUtil::parseXML(const char* file) {

    std::vector<XmlElement> result = {};

    this->m_parser->parse(file);

    m_xmlDoc = m_parser->getDocument();

    if (m_xmlDoc != nullptr) {
        xercesc::DOMNodeList* nodeList = m_xmlDoc->getDocumentElement()->getChildNodes();

        std::vector<PAIR_ATTR_VALUE> attributes;
        std::vector<CHILD_NODE> children;

        for (int i = 0; i < nodeList->getLength(); i++) {
            xercesc::DOMNode* currentNode = nodeList->item(i);
            if (currentNode->getNodeType() == xercesc::DOMNode::ELEMENT_NODE) {
                std::string name = xercesc::XMLString::transcode(currentNode->getNodeName());
                std::cout << xercesc::XMLString::transcode(currentNode->getNodeName()) << std::endl;
                xercesc::DOMElement *currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
                xercesc::DOMNamedNodeMap* attr = currentElement->getAttributes();

                for (int j = 0; j < attr->getLength(); j++) {
                    std::string nodeName = xercesc::XMLString::transcode(attr->item(j)->getNodeName());
                    std::string nodeValue = xercesc::XMLString::transcode(attr->item(j)->getNodeValue());

                    attributes.push_back(std::make_pair(nodeName, nodeValue));
                }
            
                if (currentElement->hasChildNodes()) {
                    xercesc::DOMNodeList* childNodes = currentElement->getChildNodes();

                    for (int j = 0; j < childNodes->getLength(); j++) {
                        xercesc::DOMNode* node = childNodes->item(j);
                        std::string nodeChildName = xercesc::XMLString::transcode(node->getNodeName());

                        std::vector<PAIR_ATTR_VALUE> childAttributes;

                        xercesc::DOMNamedNodeMap* attr_child = node->getAttributes();
                        if (attr_child != nullptr) {
                            for (int k = 0; k < attr_child->getLength(); k++) {
                                std::string nodeName = xercesc::XMLString::transcode(attr_child->item(k)->getNodeName());
                                std::string nodeValue = xercesc::XMLString::transcode(attr_child->item(k)->getNodeValue());

                                childAttributes.push_back(std::make_pair(nodeName, nodeValue));
                            }   
                        }

                        children.push_back(std::make_pair(nodeChildName, childAttributes));
                    }
                }

                result.push_back(XmlElement{ name, attributes, children });

                attributes.clear();
                children.clear();
            }
        }
    }

    return result;
}

XML4OSMUtil::~XML4OSMUtil() {
    delete this->m_parser;
}
