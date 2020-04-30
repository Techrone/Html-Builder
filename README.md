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
element->setHtmlTag("input");
element->addAttribute("type","\"text\"");
element->addAttribute("id", "\"foo\");
element->setEmptyTag(true);
string inputHtml = HTML_ToString(element);  // HTML_ToString does additional checks                                          

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
                          // Attribute always has to have a valid key
```
### Using HTML element: Access child elements
```
// Creating HTML elements
HTML_Element element  = HTML_Create("div");
element->add(HTML_Create("p"));
element->add(HTML_Create("p"));

element->hasChildren();             // Return true
element->numberOfChildElements();   // Return 2
element->getChildElements();        // Return std::vector<HTML_Element>
string html = HTML_ToString(element);

/*
  Result of html string:
  -------------------
  html -> "<div>
              <p></p>
              <p></p>
            </div>"
*/
```
### Using HTML element: With Parsing

```
// Perform HTML parsing
// HTML_Parse(htmlCode)             returns <div>htmlCode</div>
// HTML_Parse(masterTag, htmlCode)  returns <masterTag>htmlCode</masterTag>

HTML_Element element = HTML_Parse("html","\n"
  + "<head>"
  + "   <style>"
  + "       p {"
  + "           border-radius: 25px;"
  + "           background-color: #ededed;"
  + "       }"
  + "   </style>"
  + "</head>"
  + "<body>"
  + "   <p>Hello World!</p>"
  + "</body>");
string html = HTML_ToString(element);


/*
  Result of html string:
  -------------------
  html -> "
  <html>
    <head>
      <style>"
        p {
            border-radius: 25px;
            background-color: #ededed;
        }
      </style>
    </head>"
    <body>"
      <p>Hello World!</p>
    </body>
  </html> "
*/

//  Accessing parsed HTML:
//  --------------------------
  
  element->getHtmlTag();             // html
  element->getChildElements()[0];    // head
  element->getChildElements()[0]     // head ->
    ->getChildElements()[0];         // style
  element->getChildElements()[1];    // body
  element->getChildElements()[1]     // body ->
    ->getChildElements()[0];         // p
  
  
```
