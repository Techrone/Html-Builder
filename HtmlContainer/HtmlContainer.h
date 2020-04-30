#include <string>
#include <vector>

#define null 0

template<typename Base, typename T>
inline bool instanceof(const T*) {
	return std::is_base_of<Base, T>::value;
}

struct Property {
	std::string key;
	std::string value;

	Property(std::string attributeProperty, std::string attributeValue);
	bool operator==(const Property& attribute) const;
	bool operator==(const std::string & attributeKey) const;
	bool operator!=(const Property& attribute) const;
	bool operator!=(const std::string& attributeKey) const;

	/*
		Returns true if it is not valid
	*/
	bool operator!() const;
	operator bool() const;
};

class HtmlSpecialCharacter {
public:

	static std::string getEntityCode(std::string character);
	static bool isEntityCode(std::string entity);

private: 
	static std::vector<std::vector<std::string>> specialCharacters;
};

class HtmlContainer {
public:

	~HtmlContainer();

	/*
		Overwrites all containers, attributes and htmlText
	*/
	HtmlContainer& setHtml(std::string html);
	
	/*
		Sets the html text values. All special characters will be replaced by the appropriate characters
		Example: "Adam & Eve" -> "Adam &amp; Eve"
	*/
	HtmlContainer& setHtmlText(std::string html);

	/*
		Append the child container
	*/
	HtmlContainer& add(HtmlContainer* html);

	/*
		Adds the child container in the specific index order between the paren'ts children
	*/
	HtmlContainer& add(HtmlContainer* html, int index);

	/*
		Adds the list attribute to the list if the attribute is not found. Existing attribute values  will be overwritten if overwritten set to true, otherwise it appends
	*/
	HtmlContainer& addAttributes(const std::vector<Property> attributes, bool overwrite = false);

	/*
		Adds the attribute to the list if the attribute is not found otherwise it ignores it
		Makes it own reference that will be stored
	*/
	HtmlContainer& addAttribute(Property& attr, bool overwrite = false);
	HtmlContainer& addAttribute(std::string& key, std::string& value, bool overwrite = false);
	HtmlContainer& addAttribute(const char* key, const char* value, bool overwrite = false);

	/*
		Adds the attribute to the list if the attribute is not found otherwise it overwrites the attribute's value
	*/
	HtmlContainer& setAttribute(Property& attr);

	/*
		Gets the value of the attribute as a string
	*/
	std::string getAttributeValue(const std::string& attributeKey) const;
	
	/*
		Removes an attributes from the attribute list, if the attribute does exist
	*/
	void removeAttribute(const std::string& attributeKey);

	/*
		Removes a list of attributes from the attribute list, if the attributes exists in the attribute list
	*/
	void removeAttributes(const std::vector<Property> attributes);

	/*
		Generates a HtmlContainer(s) based on the value. Default value is the name of a tag "div" of the container, but it can also be HTML text that can be parsed to an HtmlContainer(s)
		@param value - String that would be converted to a HtmlContainer - "p" or "<p></p>"
		@return Returns a new reference of an HtmlContainer (needs manual deletion);
	*/
	static HtmlContainer* generate(std::string text = "div");
	
	/*
		Generates a HtmlContainer that will contain all the html content that is send through. The tagValue has to be the name of the html tag that will be the name of container that will encapsulate the other containers
		@param htmlTag - Name of the container or tag - "div" or "p"
		@param containers - Created containers that will be linked
		@return Returns a new reference of an HtmlContainer (needs manual deletion);
	*/
	static HtmlContainer* generate(std::vector<HtmlContainer*> containers, std::string htmlTag = "div");

	/*
		Indicates if it is an empty tag or not
		Example: <img/> -> true | <p></p> -> false
	*/
	bool isEmptyTag() const;

	/*
		Returns the html tag value.
		Example: "p" or "div" or else
	*/
	std::string getHtmlTag() const;

	/*
		Converts the entire HtmlContainer, and what it is linked to, into HTML string/text
	*/
	std::string buildHtml();

	/*
		Clears all the attributes assigned to this container
	*/
	void clearAttributes();

	/*
		Set the element tag of the html Container
	*/
	HtmlContainer& setHtmlTag(std::string tag);

	/*
		Set whether this html container should be an empty tag or not.
	*/
	HtmlContainer& setEmptyTag(bool emptyTag);

	HtmlContainer* clone() const;

	/*
		Clears all inner text assigned to the container
	*/
	void clearHtmlText();

	/*
		Clears all child containers/elements linked to this container
	*/
	void clearContainers();
	
	/*
		Clears all inner text, attributes and child containers linked to this container
	*/
	void clearAll();

	/*
		Overload delete to allow deletion only when it has no reference to any parent container
	*/
	void operator delete(void* p);

	/*
		Checks if container has any references to any parent containers
	*/
	HtmlContainer* getParent() const;

	static std::vector<HtmlContainer*> parse(std::string html);
	static bool parseAutoFix;

protected:
	HtmlContainer(const HtmlContainer& container);
	HtmlContainer(std::string htmlTag);
	HtmlContainer(std::vector<HtmlContainer*> containers);

private:
	HtmlContainer();
	static bool isValidHtml(std::string html);
	void linkChildToParent(HtmlContainer* parentContainer);
	void unlinkChildFromParent(HtmlContainer* child);

	void forceDelete();

	HtmlContainer* m_parent;
	std::vector<HtmlContainer*> m_childContainers;
	std::vector<Property*> m_attributeList;
	bool m_emptyTag;
	std::string m_htmlTag;
	std::string m_htmlText;

};

bool validateTagCharacter(const char c, bool inQuotes, std::string attrKey);