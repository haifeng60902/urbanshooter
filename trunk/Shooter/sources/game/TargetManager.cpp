#include <game/TargetManager.h>

#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>

#include <animation/CallbackManager.h>
#include <animation/RotationCallback.h>
#include <animation/ReliveCallback.h>

TargetManager::TargetManager()
{}

TargetManager::~TargetManager()
{
}


TargetManager::ShootResult TargetManager::Intersect(osgUtil::LineSegmentIntersector::Intersection intersection)
{
	std::string pattern = "Target_";

	//get the intersection nodepath and get the group
	osg::Group * target = NULL;

	int i = intersection.nodePath.size()-1;
	while(!target && i>=0)
	{
		target = intersection.nodePath.at(i)->asGroup();
		
		if(target)
			if(target->getName().find(pattern) == std::string::npos) //contains the pattern mean it is a target
				target = NULL; //no pattern, not a valid target
		
		i--;
	}
	

	//no valid intersection
	if(i<0)
		return TARGET_MISSED;
	
	if(!target)
		return TARGET_MISSED;
	

	//if the node is a MT, replace it by a PAT to manage animations
	if(!dynamic_cast<osg::PositionAttitudeTransform*>(target))
	{
		osg::MatrixTransform * mat = dynamic_cast<osg::MatrixTransform*>(target);
		if(!mat)
		{
			return TARGET_MISSED;
		}
		else
		{
			osg::PositionAttitudeTransform * pat = new osg::PositionAttitudeTransform();
			osg::Vec3d trans, scale;
			osg::Quat rot, so;
			mat->getMatrix().decompose(trans, rot, scale, so);

			pat->setAttitude(rot);
			pat->setPosition(trans);
			pat->setScale(scale);
			pat->setName(mat->getName());

			//replace the node
				//children
			for(unsigned int i=0; i < mat->getNumChildren() ; ++i)
			{
				pat->addChild(mat->getChild(i));
				mat->removeChild(i);
			}

				//parents
			osg::Node::ParentList pl = mat->getParents();
			for(unsigned int i=0; i < pl.size() ; ++i)
				pl.at(i)->replaceChild(mat, pat);

			target = pat;
		}
	}



	//rotate the target when hit
	CallbackManager::addNodeCallback(target, new RotationCallback(osg::Y_AXIS, osg::PI_2, 0.3));

	//add relive callback too
	CallbackManager::addNodeCallback(target, new ReliveCallback());


	return TARGET_REACHED;

}