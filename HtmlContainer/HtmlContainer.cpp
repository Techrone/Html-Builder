#include "HtmlContainer.h"

std::vector<std::vector<std::string>> HtmlSpecialCharacter::specialCharacters;
bool HtmlContainer::parseAutoFix = false;

Property::Property(std::string attributeProperty, std::string attributeValue)
{
	this->key = attributeProperty;
	this->value = attributeValue;
}

bool Property::operator==(const Property& attribute) const
{
	return attribute.key == this->key;
}

bool Property::operator==(const std::string& attributeKey) const
{
	return this->key == attributeKey;
}

bool Property::operator!=(const Property& attribute) const
{
	return !(*this == attribute);
}

bool Property::operator!=(const std::string& attributeKey) const
{
	return this->key != attributeKey;
}

bool Property::operator!() const
{
	return this->key == "";
}

Property::operator bool() const
{
	return this->key != "";
}

std::string HtmlSpecialCharacter::getEntityCode(std::string character)
{
	std::vector<std::vector<std::string>>& specialCharacters = HtmlSpecialCharacter::specialCharacters;

	for (size_t i = 0; i < specialCharacters.size(); i++)
	{
		if (specialCharacters[i][0] == character) {
			return specialCharacters[i][1];
		}
	}

	return "";
}

bool HtmlSpecialCharacter::isEntityCode(std::string entity)
{
	std::vector<std::vector<std::string>>& specialCharacters = HtmlSpecialCharacter::specialCharacters;

	for (size_t i = 0; i < specialCharacters.size(); i++)
	{
		if (specialCharacters[i][1] == entity) {
			return true;
		}
	}

	return false;
}

HtmlContainer& HtmlContainer::setHtml(std::string html)
{
	// Outer html
	// Todo: Parse html to HtmlContainer

	return *this;
}

HtmlContainer& HtmlContainer::setHtmlText(std::string html)
{
	m_htmlText = html;

	// TODO:Create another thread that swaps out all the special character with entity characters

	return *this;
}

HtmlContainer& HtmlContainer::add(HtmlContainer* html)
{
	if (html != null)
	{
		html->linkChildToParent(this);
		m_childContainers.push_back(html);
	}
	return *this;
}

HtmlContainer& HtmlContainer::add(HtmlContainer* html, int index)
{
	if (html != null)
	{
		html->linkChildToParent(this);
		std::vector<HtmlContainer*> container(m_childContainers.size() + 1);

		bool hasCopiedHtml = false;
		for (size_t i = 0; i < m_childContainers.size(); i++)
		{
			if (!hasCopiedHtml && i == index)
			{
				i--;
				container.push_back(html);
				hasCopiedHtml = true;
				continue;
			}
			container.push_back(m_childContainers[i]);
		}
	}
	return *this;
}

HtmlContainer& HtmlContainer::addAttributes(std::vector<Property> attributes, bool overwrite)
{
	bool doesExist;
	std::vector<size_t> nullIndices;
	for (size_t i = 0; i < attributes.size(); i++)
	{
		if (!attributes[i])
		{
			continue;
		}
		doesExist = false;
		nullIndices.clear();
		for (size_t j = 0; j < m_attributeList.size(); j++)
		{
			if (m_attributeList[j] == null)
			{
				nullIndices.push_back(j);
			}
			else if((*m_attributeList[j]) == attributes[i])
			{
				doesExist = true;
				if (overwrite)
				{
					(*m_attributeList[j]).value = attributes[i].value;
				}
				else
				{
					(*m_attributeList[j]).value += attributes[i].value;

				}
				break;
			}
		}

		if (!doesExist)
		{
			if (nullIndices.size() > 0)
			{
				m_attributeList[nullIndices[0]] = new Property(attributes[i]);
			}
			else
			{
				m_attributeList.push_back(new Property(attributes[i]));
			}
		}
	}

	return *this;
}

HtmlContainer& HtmlContainer::addAttribute(Property& attr, bool overwrite)
{
	if (!attr) 
	{
		return *this;
	}
	bool doesExist = false;
	std::vector<size_t> nullIndices;

	for (size_t j = 0; j < m_attributeList.size(); j++)
	{
		if (m_attributeList[j] == null)
		{
			nullIndices.push_back(j);
		}
		else if ((*m_attributeList[j]) == attr)
		{
			doesExist = true;
			if (!overwrite)
			{
				m_attributeList[j]->value += attr.value;
			}
			else
			{
				m_attributeList[j]->value = attr.value;
			}
			return *this;

		}
	}

	if (!doesExist)
	{
		if (nullIndices.size() > 0)
		{
			m_attributeList[nullIndices[0]] = new Property(attr);
		}
		else
		{
			m_attributeList.push_back(new Property(attr));
		}
	}

	return *this;
}

HtmlContainer& HtmlContainer::addAttribute(std::string& key, std::string& value, bool overwrite)
{
	Property attr = Property(key, value);
	addAttribute(attr, overwrite);
	return *this;
}

HtmlContainer& HtmlContainer::addAttribute(const char* key, const char* value, bool overwrite)
{
	Property attr = Property(key, value);
	addAttribute(attr, overwrite);
	return *this;
}

HtmlContainer& HtmlContainer::setAttribute(Property& attr)
{
	if (!attr)
	{
		return *this;
	}
	bool doesExist = false;
	std::vector<size_t> nullIndices;
	for (size_t j = 0; j < m_attributeList.size(); j++)
	{
		if (m_attributeList[j] == null)
		{
			nullIndices.push_back(j);
		}
		else if ((*m_attributeList[j]) == attr)
		{
			doesExist = true;
			(*m_attributeList[j]).value = attr.key;
			return *this;
		}
	}

	if (!doesExist)
	{
		if (nullIndices.size() > 0)
		{
			m_attributeList[nullIndices[0]] = new Property(attr);
		}
		else
		{
			m_attributeList.push_back(new Property(attr));
		}
	}

	return *this;
}

std::string HtmlContainer::getAttributeValue(const std::string& attributeKey) const
{
	for (size_t i = 0; i < m_attributeList.size(); i++)
	{
		if (m_attributeList[i] != null && (*m_attributeList[i]) == attributeKey)
		{
			return m_attributeList[i]->value;
		}
	}
	return "";
}

void HtmlContainer::removeAttribute(const std::string& attributeKey)
{
	for (size_t i = 0; i < m_attributeList.size(); i++)
	{
		if (m_attributeList[i] != null && (*m_attributeList[i]) == attributeKey)
		{
			delete m_attributeList[i];
			m_attributeList[i] = null;
			return;
		}
	}
}

void HtmlContainer::removeAttributes(const std::vector<Property> attributes)
{
	for (size_t j = 0; j < attributes.size(); j++)
	{
		for (size_t i = 0; i < m_attributeList.size(); i++)
		{
			if (m_attributeList[i] != null && (*m_attributeList[i]) == attributes[i])
			{
				delete m_attributeList[i];
				m_attributeList[i] = null;
				break;
			}
		}
	}
}

HtmlContainer* HtmlContainer::generate(std::string text)
{
	//TODO: Parse htmlText to HtmlContainer or create html container with tag
	std::vector<HtmlContainer*> result = HtmlContainer::parse(text);
	HtmlContainer* container = null;

	if (result.size() > 1)
	{
		for (size_t i = 0; i < result.size(); i++)
		{
			if (result[i] != null)
			{
				result[i]->forceDelete();
			}
		}
	}
	else if (result.size() == 1)
	{
		container = result[0];
	}
	else 
	{
		container = new HtmlContainer(text);
	}

	return container;
}

HtmlContainer* HtmlContainer::generate(std::vector<HtmlContainer *> containers, std::string htmlTag)
{
	HtmlContainer* container = null;
	if (!HtmlContainer::isValidHtml(htmlTag))
	{
		container = new HtmlContainer(htmlTag);
		for (size_t i = 0; i < containers.size(); i++)
		{
			if(containers[i] != null)
				container->add(containers[i]);
		}
	}
	return container;
}

bool HtmlContainer::isEmptyTag() const
{
	return m_emptyTag;
}

std::string HtmlContainer::getHtmlTag() const
{
	return m_htmlTag;
}

std::string HtmlContainer::buildHtml()
{
	std::string html = "<" + m_htmlTag + (m_attributeList.size() > 0 ? " " : "");

	// Traverse through attributes
	size_t max = (m_attributeList.size() == 0 ? 0 : m_attributeList.size() - 1);
	for (size_t i = 0; i < max; i++)
	{
		html += m_attributeList[i]->key + "=\"" + m_attributeList[i]->value + "\" ";
	}
	if(max >= 0 && m_attributeList.size() != 0)
		html += m_attributeList[max]->key + "=" + m_attributeList[max]->value + "";

	if (!isEmptyTag())
	{
		html += ">" + m_htmlText;
		for (size_t i = 0; i < m_childContainers.size(); i++)
		{
			html += m_childContainers[i]->buildHtml();
		}

		html += "</" + m_htmlTag + ">";
	} 
	else
	{
		html += "/>";
	}

	return html;
}

void HtmlContainer::clearAttributes()
{
	for (size_t i = 0; i < m_attributeList.size(); i++)
	{
		if (m_attributeList[i] != null)
		{
			delete m_attributeList[i];
		}
	}

	m_attributeList.clear();
}

HtmlContainer& HtmlContainer::setHtmlTag(std::string tag)
{
	m_htmlTag = tag;
	return *this;
}

HtmlContainer& HtmlContainer::setEmptyTag(bool emptyTag)
{
	m_emptyTag = emptyTag;

	return *this;
}

void HtmlContainer::clearHtmlText()
{
	m_htmlText = "";
}

HtmlContainer* HtmlContainer::clone() const
{
	return new HtmlContainer(*this);
}

void HtmlContainer::clearContainers()
{
	for (size_t i = 0; i < m_childContainers.size(); i++)
	{
		if (m_childContainers[i] != null) 
		{
			delete m_childContainers[i];
		}
	}
}

void HtmlContainer::clearAll()
{
	clearContainers();
	clearAttributes();
	clearHtmlText();
}

void HtmlContainer::operator delete(void* p)
{
	if (p != null)
	{
		if (instanceof<HtmlContainer>(p))
		{
			HtmlContainer* container = (HtmlContainer*)p;
			if (container->getParent() != null)
				return;
		}
		free(p);
	}
}

HtmlContainer* HtmlContainer::getParent() const
{
	return m_parent;
}

bool HtmlContainer::isValidHtml(std::string html)
{
	return false;
}

void HtmlContainer::linkChildToParent(HtmlContainer* parentContainer)
{
	m_parent = parentContainer;
}

void HtmlContainer::unlinkChildFromParent(HtmlContainer* childContainer)
{
	if (childContainer == null) return;
	childContainer->m_parent = null;
}

std::vector<HtmlContainer*> HtmlContainer::parse(std::string html)
{
	bool autoFix = parseAutoFix;
	std::vector<HtmlContainer*> stack;
	std::vector<HtmlContainer*> created;
	std::vector<HtmlContainer*> result;

	HtmlContainer* parent = null;

	std::vector<HtmlContainer*> onStack;
	bool tagEncounter = false;
	bool tagOpeningTriggered = false;
	std::string input = "";
	std::string innerText = "";


	try 
	{
		for (size_t i = 0, size = html.length(); i < size; i++)
		{
			switch (html[i])
			{
			case '<':
			{
				HtmlContainer* tag = new HtmlContainer();
				std::string input = "";
				bool isAttribute = false;
				bool isAssigning = false;
				bool isClosingTag = false;
				bool hasTriggeredTag = true;
				std::vector<char> openedQuotes;
				std::vector<std::string> attributeKeys;
				std::vector<std::string> attributeValues;
				tagOpeningTriggered = true;

				// Parse open or empty tag
				for (i++; i < size; i++)
				{
					if (html[i] == ' ')
					{
						// Check if the tag name has been captured
						if (input == "" && hasTriggeredTag)
						{
							// Tag name was not captured
							continue;
						}
						
						// Input has been captured but check if it is tag name 
						if (hasTriggeredTag)
						{
							tag->setHtmlTag(input);
							hasTriggeredTag = false;
							isAttribute = true;
							input = "";
							continue;
						}

						// Check if nothing is being assigned
						if (isAssigning && openedQuotes.empty())
						{
							isAttribute = false;
							isAssigning = false;
							attributeValues.push_back("");
							continue;
						}

						// If not in quotes don't add space to attribute
						if (openedQuotes.empty() && !hasTriggeredTag)
						{
							// Check for: <p id=    5></p> 
							if (!input.empty())
							{
								attributeValues.push_back(input);
								isAttribute = false;
							}
							continue;
						}

					}
					// Check if it is assigning a value to an attribute
					else if (html[i] == '=')
					{
						if (!isAssigning)
						{
							isAttribute = false;
							isAssigning = true;
							if(!input.empty())
								attributeKeys.push_back(input);
							input = "";
							continue;
						}
						else if (openedQuotes.empty())
						{
							// TODO: Throw error or ignore
							delete tag; // Delete tag if error throw
							throw "Parsing error case: <div =\"demo\">";
						}
					}
					// Check if attribute is in quotes with level of quotes
					else if (html[i] == '\'' || html[i] == '\"')
					{
						// Check if quotes exist without any assignement
						if (!isAssigning || attributeKeys.size() != attributeValues.size() + 1)
						{
							// Try implement auto fix or throw error
							if (autoFix) continue;
							delete tag; // Delete tag if error throw
							throw "Parse error: <p \" \"></p>";
						}

						// check if still in quotes and if it is closing quotes
						if (!openedQuotes.empty() && openedQuotes.back() == html[i])
						{
							openedQuotes.pop_back();
							// Check if the quotes is finished
							if (openedQuotes.empty())
							{
								// Add attribute to the list
								isAssigning = false;
								attributeValues.push_back(input + html[i]);
								input = "";
							}
						} else if (openedQuotes.empty())
						{
							// Add new quote level
							openedQuotes.push_back(html[i]);
						}

					}
					// Check if reached the end of the tag
					else if (html[i] == '>')
					{

						// Todo: Add JavaScript cases here
						//	Test case<script> /*>*/ </script>
						if(openedQuotes.empty())
						{
							if (hasTriggeredTag)
							{
								tag->setHtmlTag(input);
							}
							break;
						}
					}
					// Check if it is a closing tag
					else if (html[i] == '/' && openedQuotes.empty())
					{
						if (tag->getHtmlTag() == "")
						{
							delete tag;
							tag = null;
							i--; // Forcing the outer loop to perform closing tag check
							break;
						}
						continue;
					}
					
					if(validateTagCharacter(html[i], !openedQuotes.empty(), (attributeKeys.empty() ? "" :attributeKeys.back())))
						input += html[i];

				}
				
				i;
				if (tag != null)
				{
					// Adding last attributes to html tag
					for (size_t j = 0; j < attributeKeys.size(); j++)
					{
						tag->addAttribute(attributeKeys[j], attributeValues[j]);
					}
					tagOpeningTriggered = false;
					if (!stack.empty()) 
					{
						stack.back()->add(tag);
					}
					stack.push_back(tag);
					created.push_back(tag);
				}

				break;
			}
			case '/':
			{
				if (tagOpeningTriggered)
				{
					innerText = input;
					input = "";
				}

				break;
			}
			case '>':
			{
				if (tagOpeningTriggered)
				{
					tagOpeningTriggered = false;
					std::string tag = input;
					if (!stack.empty())
					{
						// Check if same html tag is closing
						if (stack.back()->getHtmlTag() == tag)
						{
							stack.pop_back();
							input = "";
							break;
						}

						if (!autoFix)
						{
							throw "Parse error: Invalid closing tag. \n<div></p>";
						}

						/*
							Replace: <div></p>
							With:	<div></div><p></p>

							OR

							Replace: </div>
							With:	<div></div>
						*/
						HtmlContainer* fixContainer = new HtmlContainer(tag);
						if (stack.back()->getParent() != null)
						{
							stack.back()->getParent()->add(fixContainer);
							stack.pop_back();
						}

						created.push_back(fixContainer);
					}
				}
				break;
			}
			default:
				input += html[i];
				break;
			}

		}
	}
	catch (const char* e)
	{
		for (size_t i = 0; i < created.size(); i++)
		{
			delete created[i];
		}
		created.clear();
	}

	for (size_t i = 0; i < created.size(); i++)
	{
		if (created[i]->getParent() == null)
		{
			result.push_back(created[i]);
		}
	}

	return result;

}


bool validateTagCharacter(const char c, bool inQuotes, std::string attrKey)
{
	switch (c)
	{
	case 'A': return true;
	case 'B': return true;
	case 'C': return true;
	case 'D': return true;
	case 'E': return true;
	case 'F': return true;
	case 'G': return true;
	case 'H': return true;
	case 'I': return true;
	case 'J': return true;
	case 'K': return true;
	case 'L': return true;
	case 'M': return true;
	case 'N': return true;
	case 'O': return true;
	case 'P': return true;
	case 'Q': return true;
	case 'R': return true;
	case 'S': return true;
	case 'T': return true;
	case 'U': return true;
	case 'V': return true;
	case 'W': return true;
	case 'X': return true;
	case 'Y': return true;
	case 'Z': return true;
	case 'a': return true;
	case 'b': return true;
	case 'c': return true;
	case 'd': return true;
	case 'e': return true;
	case 'f': return true;
	case 'g': return true;
	case 'h': return true;
	case 'i': return true;
	case 'j': return true;
	case 'k': return true;
	case 'l': return true;
	case 'm': return true;
	case 'n': return true;
	case 'o': return true;
	case 'p': return true;
	case 'q': return true;
	case 'r': return true;
	case 's': return true;
	case 't': return true;
	case 'u': return true;
	case 'v': return true;
	case 'x': return true;
	case 'y': return true;
	case 'z': return true;
	case '0': return true;
	case '1': return true;
	case '2': return true;
	case '3': return true;
	case '4': return true;
	case '5': return true;
	case '6': return true;
	case '7': return true;
	case '8': return true;
	case '9': return true;
	case '\n': return true;
	case '\t': return true;
	case ' ': return true;
	case '&': return true && (inQuotes || attrKey.find("on") == -1);
	case '!': return true && (inQuotes || attrKey.find("on") == -1);
	case '@': return true && (inQuotes || attrKey.find("on") == -1);
	case '#': return true && (inQuotes || attrKey.find("on") == -1);
	case '$': return true && (inQuotes || attrKey.find("on") == -1);
	case '%': return true && (inQuotes || attrKey.find("on") == -1);
	case '^': return true && (inQuotes || attrKey.find("on") == -1);
	case '*': return true && (inQuotes || attrKey.find("on") == -1);
	case '(': return true && (inQuotes || attrKey.find("on") == -1);
	case ')': return true && (inQuotes || attrKey.find("on") == -1);
	case '[': return true && (inQuotes || attrKey.find("on") == -1);
	case ']': return true && (inQuotes || attrKey.find("on") == -1);
	case '{': return true && (inQuotes || attrKey.find("on") == -1);
	case '}': return true && (inQuotes || attrKey.find("on") == -1);
	case '\\': return true && (inQuotes || attrKey.find("on") == -1);
	case '-': return true && (inQuotes || attrKey.find("on") == -1);
	default:
		break;
	}
}

void HtmlContainer::forceDelete()
{
}


HtmlContainer::HtmlContainer()
{
	m_parent = null;
	m_emptyTag = false;
	m_htmlTag = "";
	m_htmlText = "";
}

HtmlContainer::HtmlContainer(const HtmlContainer& container)
{
	m_parent = container.m_parent;
	m_emptyTag = container.m_emptyTag;
	m_htmlTag = container.m_htmlTag;
	m_htmlText = container.m_htmlText;

	for (size_t i = 0; i < container.m_childContainers.size(); i++)
	{
		m_childContainers.push_back(new HtmlContainer(*container.m_childContainers[i]));
	}

	for (size_t i = 0; i < container.m_attributeList.size(); i++)
	{
		m_attributeList.push_back(new Property(*container.m_attributeList[i]));
	}
}

HtmlContainer::HtmlContainer(std::string htmlTag)
{
	m_parent = null;
	m_emptyTag = false;
	m_htmlTag = htmlTag;
	m_htmlText = "";
}


HtmlContainer::HtmlContainer(std::vector<HtmlContainer*> containers) : HtmlContainer()
{
	m_childContainers = containers;
}

HtmlContainer::~HtmlContainer()
{
	if (m_parent != null)
		m_parent->unlinkChildFromParent(this);

	for (size_t i = 0; i < m_childContainers.size(); i++)
	{
		delete m_childContainers[i];
	}
	m_childContainers.clear();

	for (size_t i = 0; i < m_attributeList.size(); i++)
	{
		delete m_attributeList[i];
	}
	m_attributeList.clear();


}