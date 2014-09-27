// -------------------------
#include <tinyxml2.h>
// -------------------
void WriteDream(ostream& output, vector<pair<string,string> >& methods)
{
  for(auto& name : methods)
    output << name.first << " " << name.second << "{ }" << endl;
}
// ------------------------------------
// ParseDream is the xml parsing function intended to output c++ declarations.
// It will also output the functions defined in the xml will code bodies
// so that the IRFile output can be read for the functions 'mangled' name.
// ---------------------------------
// ParseDream is recursive. It re-enters when a container type structure
// is involved such as a class or namespace. To iterate over a set of siblings
// is iterative : P however.
// -------------------------------------
// ParseDream is not a good name for a function in this program however, thats
// its name in the test bed i made to produce this function, and the name of
// the example xml on the tinyxml website is dream.xml
// ----------------------------------------
void ParseDream(tinyxml2::XMLNode* root, ostream& output, vector<string> names, vector<pair<string,string> >& methods)
{
  for(auto child = root->FirstChildElement();
      child;
      child=child->NextSiblingElement())
  {
    cout << child->Value() << endl;
    string type = child->Value();
    // -----------------------
    if(type=="Include")
    {
      if(child->GetText()!=nullptr)
      {
        string file = child->GetText();
        string inctype = "\"\"";
        if(auto attr = child->FirstAttribute())
        {
          string inp =attr->Value();
          if(inp=="remote")
            inctype="<>";
        }
        output << "#include " << inctype[0] << file << inctype[1] << endl;
      }
      else
        cerr << "Empty include tag ommited" << endl;
    }// END IF TYPE==INCLUDE
    else if(type=="Namespace")
    {
      string name;
      if(child->GetText()!=nullptr)
      {
        name = child->GetText();
        output << "namespace " << name;
      }
      else
      {
        output << "namespace\n";
        cerr << "Anonymous namepace defined\n";
      }
      if(child->FirstChildElement()!=nullptr)
      {
        names.push_back(name+"::");
        output << "{" << endl;
        ParseDream(child, output, names, methods);
        output << "};" << endl;
        names.pop_back();
      }
      else
        cerr << "Empty namespace created" << endl;
    }// END IF TYPE==NAMESPCE
    else if(type=="Class")
    {
      string name;
      if(child->GetText()!=nullptr)
      {
        name = child->GetText();
        output << "class " << name;
      }
      else
        cerr << "Empty class ommited" << endl;
      if(child->FirstChildElement()!=nullptr)
      {
        names.push_back(name+"::");
        output << "{" << endl;
        ParseDream(child, output, names, methods);
        output << "};"<< endl;
        names.pop_back();
      }
      else
      {
        output << ";" << endl;
        fprintf(stderr, "class %s declared, but not interface made\n", child->GetText());
      }
    } // END IF TYPE==CLASS
    else if(type=="Function")
    {
      string ret_type = "";
      // -------------------------------
      // Here we check for modifier prefixes and return type
      // -------------------------------
      for(auto attrib = child->FirstAttribute();
          attrib;
          attrib = attrib->Next())
      {
        string attr = attrib->Name();
        if(attr == "mod") // modifiers are only included in class definitions
        {
          output << attrib->Value() << " ";
        }
        else if(attr == "ret")
        {
          ret_type = attrib->Value();
        }
      }
      if(child->GetText()!=nullptr)
      {
        output << ret_type << " " << child->GetText() << ";" << endl;
        string fullname = "";
        for(auto& s : names)
          fullname += s;
        fullname+=child->GetText();
        methods.push_back(pair<string,string>(ret_type, fullname));
      }
      else cerr << "No named included for function tag. ommited" << endl;
      // ------------------------------
    }
  } // END FOR LOOP
}
