#include <iostream>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <cpr/cpr.h>
#include <cstring>

int main() {
    cpr::Response r = cpr::Get(
            cpr::Url{"http://localhost:8000/ticket.html"});
    const char *html = r.text.c_str();

    // Parse the HTML document
    htmlDocPtr doc = htmlReadMemory(html, strlen(html), "noname.html", nullptr,
                                    HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    if (doc == nullptr) {
        std::cerr << "Failed to parse document" << std::endl;
        return 1;
    }

    // Create XPath evaluation context
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == nullptr) {
        std::cerr << "Error: unable to create new XPath context" << std::endl;
        xmlFreeDoc(doc);
        return 1;
    }

    // Search for all 'a' nodes with specified attribute
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) "//a[@data-testid='listing']", xpathCtx);
    if (xpathObj == nullptr) {
        std::cerr << "Error: unable to evaluate xpath expression" << std::endl;
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return 1;
    }

    // Get the href attribute of the first 'a' node with specified attribute
    std::string href;
    if (xpathObj->nodesetval && xpathObj->nodesetval->nodeNr > 0) {
        xmlNodePtr node = xpathObj->nodesetval->nodeTab[0];
        xmlChar *hrefChar = xmlGetProp(node, (const xmlChar *) "href");
        if (hrefChar) {
            href = std::string((char *) hrefChar);
            xmlFree(hrefChar);
        }
    }

    // Cleanup
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    // Shutdown libxml
    xmlCleanupParser();

    // Print the href
    std::cout << "Href: " << href << std::endl;

    return 0;
}
