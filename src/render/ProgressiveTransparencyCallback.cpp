#include <ProgressiveTransparencyCallback.h>

#include <osg/Node>
#include <osg/StateSet>
#include <osg/Notify>

ProgressiveTransparencyCallback::ProgressiveTransparencyCallback(double durationVisible , double duration_blur)
{
	_duration_visible = durationVisible;
	_duration_blur = duration_blur;

	_first_traverse = false;
	_material = NULL;
}

ProgressiveTransparencyCallback::~ProgressiveTransparencyCallback()
{

}


void ProgressiveTransparencyCallback::operator ()(osg::Node *node, osg::NodeVisitor *nv)
{
	osg::Timer_t actual_tick = osg::Timer::instance()->tick();


	//first traverse : init start_tick
	if(!_first_traverse)
	{
		_start_tick = actual_tick;
		_first_traverse = true;

		osg::ref_ptr<osg::StateSet> stateset = node->getOrCreateStateSet();
		stateset->setMode(GL_BLEND, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE );
        stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	//	stateset->setDataVariance(osg::Object::DYNAMIC);
		stateset->setRenderBinDetails(11, "DepthSortedBin");

		_material = new osg::Material;
		_material->setColorMode(osg::Material::AMBIENT);
		/*_material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(1, 1, 1, 1));
		_material->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(1, 1, 1, 1));
		_material->setShininess(osg::Material::FRONT_AND_BACK, 64.0f);*/
		_material->setAlpha(osg::Material::FRONT_AND_BACK, 0.2);
		stateset->setAttributeAndModes(_material.get(), osg::StateAttribute::ON);

			osg::notify(osg::NOTICE) << "BEGIN of transparency" << std::endl;

	}
	else
	{
		//when duration visible is done : start
		double duration = osg::Timer::instance()->delta_s(_start_tick , actual_tick);
		osg::notify(osg::NOTICE) << "Duration : " << duration << std::endl;

		
		if(duration >= (_duration_visible + _duration_blur))
		{
			osg::ref_ptr<osg::StateSet> stateset = node->getOrCreateStateSet();
			stateset->setMode(GL_BLEND, osg::StateAttribute::OFF);
			stateset->setRenderingHint(osg::StateSet::DEFAULT_BIN);
			stateset->removeAttribute(_material.get());

			osg::notify(osg::NOTICE) << "END of transparency" << std::endl;

			//auto-destruction
			traverse(node,nv);
			node->setUpdateCallback(NULL);
			return;
		}
		else if(duration >= _duration_visible)
		{
			//start blur
			double transparency = 1 - ( duration - _duration_visible ) / _duration_blur;

			_material->setAlpha(osg::Material::FRONT_AND_BACK, transparency);
			osg::notify(osg::NOTICE) << "transparency : "<<transparency << std::endl;
			
		}
		//else do nothing : let it be displayed

	}

	


    
	traverse(node,nv);
	
}