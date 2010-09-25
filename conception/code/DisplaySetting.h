#ifndef _DISPLAYSETTING_H
#define _DISPLAYSETTING_H


#include <string>
using namespace std;

class DisplayGeometry;

//Doit gerer l'instance unique de la geometry
class DisplaySetting {
	private:
    float _visibleTime;

    float _backgroundTransparency;

    DisplayGeometry * _displayGeometry;


	public:
    inline const DisplayGeometry * get__displayGeometry() const;

    void set__displayGeometry(DisplayGeometry * value);


	private:
    int _charSize;

    string _font;

};
inline const DisplayGeometry * DisplaySetting::get__displayGeometry() const {
  return _displayGeometry;
}

#endif
