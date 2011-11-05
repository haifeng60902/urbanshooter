#include <graphic/HudWeapon.h>

#include <osg/LightModel>

HudWeapon::HudWeapon()
{
	_weaponRoot = new osg::Group;

	// set the projection matrix
    setProjectionMatrix(osg::Matrix::ortho2D(0,1280,0,1024));
	
    // set the view matrix    
    setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    setViewMatrix(osg::Matrix::identity());

    // only clear the depth buffer
    setClearMask(GL_DEPTH_BUFFER_BIT);

    // draw subgraph after main camera view.
    setRenderOrder(osg::Camera::POST_RENDER);

    // we don't want the camera to grab event focus from the viewers main camera(s).
    setAllowEventFocus(false);

	addChild( _weaponRoot );
	
	//render two sided, no cullface, no ligghtning
	osg::LightModel * lm = new osg::LightModel;
	lm->setTwoSided (true);
	_weaponRoot->getOrCreateStateSet()->setAttributeAndModes(lm, osg::StateAttribute::ON);
	_weaponRoot->getOrCreateStateSet()->setMode(GL_CULL_FACE, osg::StateAttribute::OFF);
//	_weaponRoot->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF|osg::StateAttribute::PROTECTED|osg::StateAttribute::OVERRIDE);

}

HudWeapon::~HudWeapon()
{}

void HudWeapon::setWeaponRoot( osg::PositionAttitudeTransform * pat )
{
	//remove all children and add the new one
	_weaponRoot->removeChildren(0, _weaponRoot->getNumChildren());
	_weaponRoot->addChild(pat);
}