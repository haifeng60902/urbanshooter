#ifndef _TRANSPARENCYCALLBACK_H
#define _TRANSPARENCYCALLBACK_H


//TODO : Herite de osg::NodeCallback
class TransparencyCallback {
	public:
    TransparencyCallback(const float & _beginTransparency);


	protected:
    ~TransparencyCallback();


	private:
    float _defaultTransparency;

};
#endif
