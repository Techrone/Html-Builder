#include <iostream>
#include <fstream>
#include "src/HtmlContainer.h"
using namespace std;

std::string containersToString(vector<HtmlContainer*> containers);
void clearContainers(vector<HtmlContainer*> containers);

void performParseTest(std::string);

#define TEST_WITH_STRING 1
#if TEST_WITH_STRING

void main()
{
	performParseTest("<div onclick='alert(\"Hello World\")'><p></p></div>");

}


void performParseTest(std::string html)
{
	vector<HtmlContainer*> containers = HtmlContainer::parse(html);
	cout << "successfull: ";
	if (html == containersToString(containers))
	{
		cout << "true";
	}
	else
	{
		cout << "false";
	}

	clearContainers(containers);
}
#else

void fileTest();

void main()
{
	performParseTest();
}
void fileTest()
{

}
#endif // TEST_WITH_STRING


std::string containersToString(vector<HtmlContainer*> containers)
{
	std::string html = "";
	for (size_t i = 0; i < containers.size(); i++)
	{
		html += containers[i]->buildHtml();
	}

	return html;
}

void clearContainers(vector<HtmlContainer*> containers)
{
	for (size_t i = 0; i < containers.size(); i++)
	{
		delete containers[i];
	}
	containers.clear();
}

