# Html-Builder
This is a single threaded, will be updated to multi thread, HTML parser and builder in a single set. It is developed in C++ and it is cross platform. Currently it is single threaded but will be updated to become multi-threaded algorithm.
This would be used to generate more dynamic html pages and finalizing the html content before sending it back to the client. The library makes
use of a specific coding standard on how to access/create or handle html properties such as elements and attributes.

## Coding Example

### Creating HTML elements
HTML_Create can only take in the following types:
* string - name of the tag
* HTML_Element
```
// Creating HTML elements
HTML_Element element  = HTML_Create("div");
HTML_Element element2 = HTML_Create(element);
```

### Using HTML elements setting and getting HTML content
```
HTML_Element element  = HTML_Create("p");

element->setHtmlText("Hello World");                  // Result: <p>Hello World</p>
element->clearHtmlText();                             // Result: <p></p>                  

element->setHtml("<div><p>Big potato</p></div>");     // Result: <div><p>Big potato</p></div>
element->clearHtmlText();                             // Result: <div><p>Big potato</p></div>
element->clearChildren();                             // Result: <div></div>

element->addAttribute("id","5");                      // Result: <div id=5></div>
element->addAttribute("id","6");                      // Result: <div id=5></div>
element->addAttribute("id","6",true);                 // Result: <div id=6></div>
element->addAttribute("id","5", false);               // Result: <div id=6></div>
element->addAttribute("data-key","'string'", false);  // Result: <div id=6 data-key='string'></div>

element->removeAttribute("id");                       // Result: <div data-key='string'></div>

element->clearAttributes();                           // Result: <div></div>

// Creating proper HTML: <input type="text" id="foo" />
// Step:
element->setHtmlTag("input")
element->addAttribute("input")
element->addAttribute("input")
element->setEmptyTag(true);
string inputHtml = HTML_ToString(element);  // HTML_ToString does nullpointer checks
inputHtml == element->toString();           // returns true
                                          

```


### Using HTML elements with attributes
```
// Creating HTML elements
HTML_Element element  = HTML_Create("div");

// Adding Html Attributes
// Method 1
element->addAttribute("id","foo");

// Method 2
HTML_Attribute id = HTML_CREATE("id","foo");
element->addAttribute(id);


// Validating Html Attributes
// Attributes has to be initialized to null
id = null;
HTML_AttributeIsValid(id) // returns false

id = HTML_CREATE("","foo")
HTML_AttributeIsValid(id) // returns false
// Attribute always has to have a key
```
### Using HTML element: Access child elements
```
// Creating HTML elements
HTML_Element element  = HTML_Create("div");
element->add(HTML_Create("p"));
element->add(HTML_Create("input"));

element->hasChildren();             // Return true
element->numberOfChildElements();   // Return 2
element->getChildElements();        // Return std::vector<HTML_Element>

```

```
// Creating HTML elements
HTML_Element fooEl  = HTML_Create("div");
HTML_Element barEl = HTML_Create(fooEl);

fooEl->add(barEl);
```
Adds barEl as a child element at fooEl
It will look as <div

```
// Perform HTML parsing
HTML_Element element = HTML_Parse("<p></p>")
```
