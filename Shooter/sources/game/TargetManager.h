#ifndef _TARGET_MANAGER_H_
#define _TARGET_MANAGER_H_


#include <osgUtil/LineSegmentIntersector>


//manage target intersection and results
class TargetManager
{
public:
	TargetManager();
	~TargetManager();

	void Intersect(osgUtil::LineSegmentIntersector::Intersection intersection);

private:


};

#endif //_TARGET_MANAGER_H_
