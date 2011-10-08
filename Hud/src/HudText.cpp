#include <HudText.h>

#include <DisplaySetting.h>
#include <DisplayGeometry.h>
#include <Effects.h>

HudText::HudText(const std::string & text, DisplaySetting * ds) {

	_text = new osgText::Text();

	osg::Geode * geode = new osg::Geode;
	addChild(geode);

	geode->addDrawable(_text);

	//get and attach the background
	osg::Geode * bg = ds->getDisplayGeometry()->createBackground();
	addChild(bg);

	//set its transparency
	Effects::setTransparency(bg, ds->getBackgroundTransparency());

	//set text position and size
	_text->setFont(ds->getFont());
	_text->setCharacterSize(ds->getCharSize());
	_text->setText(text);
	_text->setColor(ds->getTextColor());

	//initialize position
	_text->setPosition(osg::Vec3d(10. ,10. , 0.));

	//no lighting
    getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
}



HudText::~HudText() {
	//nothing to delete
}

