#ifndef LSYS_REGLE_H
#define LSYS_REGLE_H

#include <map>

#include <Element.h>

class Regle
{
public: 
	Regle(){}
	~Regle(){}

	typedef std::map< Element, Elements > RegleListe;

	inline void add(Element e, Elements ve)
	{
		_r[e] = ve;
	}

	inline void addToElement(Element key, Element e)
	{
		_r[key].push_back(e);
	}

	void clear()
	{
		_r.clear();
	}

	inline Elements get(const Element & key)
	{
		Elements res ;

		RegleListe::iterator it = _r.find(key);
		if(it!= _r.end())
			res = it->second;

		return res;
	}

	static Elements fromString(std::string elems)
	{
		Elements e;
		for(unsigned int i = 0 ; i < elems.size() ; ++i)
			e.push_back(Element(elems.at(i)));
		return e;
	}


private:

	RegleListe _r;

};

#endif //LSYS_REGLE_H

