#include <Hud/HudTextRoot.h>


HudTest::HudTextRoot::HudTextRoot()
{
	_nextPos = osg::Vec2(10,5);
}

HudTest::HudTextRoot::~HudTextRoot()
{

	//empty the queue
	for(unsigned int i = 0 ; i<_texts.size() ; ++i)
		_texts.pop();

}

void HudTest::HudTextRoot::addText(const std::string &text)
{

	int sizeX = 150;
	int sizeY = 40;

	osg::ref_ptr<HudText> ht = new HudText(sizeX, sizeY);
	ht->setText(text);

	osg::PositionAttitudeTransform* pat = new osg::PositionAttitudeTransform();
	pat->addChild(ht);
	pat->setPosition(osg::Vec3(_nextPos.x(), _nextPos.y(), 0. ));

	//_nextPos[0] += sizeX;
	_nextPos[1] += sizeY+1;

	addChild(pat);

	_texts.push(ht);

}

