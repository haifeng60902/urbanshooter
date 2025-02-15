#ifndef _TARGET_MANAGER_H_
#define _TARGET_MANAGER_H_


#include <osgUtil/LineSegmentIntersector>

//manage target intersection and results
class TargetManager
{
public:
	TargetManager();
	~TargetManager();

	enum ShootResult{ TARGET_REACHED, TARGET_MISSED, TARGET_WRONG };

	ShootResult Intersect(osgUtil::LineSegmentIntersector::Intersection intersection);

	typedef std::set< osg::PositionAttitudeTransform* > TargetMap;

private:

};

#endif //_TARGET_MANAGER_H_
