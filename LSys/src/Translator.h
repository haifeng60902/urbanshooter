#ifndef LSYS_TRANSLATOR_H
#define LSYS_TRANSLATOR_H

#include <Generator.h>

#include <osg/Group>

//Class used to translate from Generator output to graphical datas
class Translator
{
public:
	Translator(Elements generation);
	~Translator();

	void translate();

private:

	Elements _generation;
	osg::ref_ptr< osg:Group > _root;
};

#endif //LSYS_TRANSLATOR_H
