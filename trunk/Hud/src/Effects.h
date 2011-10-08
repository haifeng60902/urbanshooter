#ifndef _EFFECTS_H_
#define _EFFECTS_H_

#include <NodeCollector.h>
#include <osg/Material>
#include <osg/Geometry>
#include <osg/Geode>

class Effects
{

	//static void hide();


public:

	static void setTransparency(osg::Node * node, double alpha)
	{
		if(!node) return;


		std::vector< osg::Geode *> geodes = NodeCollector::collect<osg::Geode>(node);

		for(unsigned int i=0 ; i < geodes.size() ; ++i)
			for(unsigned int j=0 ; j < geodes.at(i)->getNumDrawables() ; ++j)
				setTransparency(dynamic_cast<osg::Geometry*>(geodes.at(i)->getDrawable(j)), alpha);
		
	}

private:

	static void setTransparency(osg::Geometry * node, double alpha)
	{
		if(!node) return;

		osg::ref_ptr<osg::StateSet> state = node->getOrCreateStateSet();

		//If no material, add a new one

		osg::ref_ptr<osg::Material> mat = dynamic_cast<osg::Material*>( state->getAttribute(osg::StateAttribute::MATERIAL) );

		if(!mat.valid())
			mat = new osg::Material();

		mat->setAlpha(osg::Material::FRONT_AND_BACK,alpha);

		state->setAttributeAndModes(mat.get(), osg::StateAttribute::ON);


		if(alpha < 1.0f) 
		{
			state->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
			state->setMode(GL_BLEND,osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
			mat->setColorMode(osg::Material::AMBIENT);//_AND_DIFFUSE); //avoid replacing the vertex color array (important)
		}
		else 
		{
			state->setRenderingHint(osg::StateSet::DEFAULT_BIN);
			state->setMode(GL_BLEND,osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
			mat->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE); //avoid replacing the vertex color array (important)
		}
	}


};

#endif //_EFFECTS_H_
