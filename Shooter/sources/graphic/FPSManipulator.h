#ifndef _FPS_MANIPULATOR_H_
#define _FPS_MANIPULATOR_H_

#include <osgGA/MatrixManipulator>

#include <osgViewer/GraphicsWindow>

class FPSManipulator : public osgGA::MatrixManipulator
{

public:
	FPSManipulator();
	~FPSManipulator();


	
    /** set the position of the matrix manipulator using a 4x4 Matrix.*/
    virtual void setByMatrix(const osg::Matrixd& matrix);

    /** set the position of the matrix manipulator using a 4x4 Matrix.*/
    virtual void setByInverseMatrix(const osg::Matrixd& matrix) { setByMatrix(osg::Matrixd::inverse(matrix)); }

    /** get the position of the manipulator as 4x4 Matrix.*/
    virtual osg::Matrixd getMatrix() const;

    /** get the position of the manipulator as a inverse matrix of the manipulator, typically used as a model view matrix.*/
    virtual osg::Matrixd getInverseMatrix() const;

	void home(double currentTime);

	void addMouseEvent(const osgGA::GUIEventAdapter& ea);
	void flushMouseEventStack();


    /** Start/restart the manipulator.*/
    virtual void init(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us);

    /** handle events, return true if handled, false otherwise.*/
    virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us);

	bool calcMovement();

void computePosition(const osg::Vec3& eye,const osg::Vec3& center,const osg::Vec3& up);


void setGW(osgViewer::GraphicsWindow* gw){ _gw = gw; }


private:

	        // Internal event stack comprising last two mouse events.
        osg::ref_ptr<const osgGA::GUIEventAdapter> _ga_t1;
        osg::ref_ptr<const osgGA::GUIEventAdapter> _ga_t0;


        osg::Vec3d   _center;
        osg::Quat    _rotation;

	osgViewer::GraphicsWindow* _gw;

	
};

#endif //_FPS_MANIPULATOR_H_
