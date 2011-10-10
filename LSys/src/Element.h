#ifndef LSYS_ELEMENT_H
#define LSYS_ELEMENT_H

#include <vector>


//One letter
class Element
{
public:

	Element(char elem) :
	  _elem( elem )
	  {}

	  ~Element(){};

	inline void set(char elem){ _elem = elem; };
	inline char get() const { return _elem; }

	//For the map sort
	bool operator<(const Element e) const
	{
		return (_elem < e.get());
	}


private:

	char _elem;
};

typedef std::vector<Element> Elements;




#endif //LSYS_ELEMENT_H
