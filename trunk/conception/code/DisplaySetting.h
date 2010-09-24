#ifndef _DISPLAYSETTING_H
#define _DISPLAYSETTING_H


class DisplayGeometry;

//// Doit gerer l'instance unique de la geometry
class DisplaySetting {
  private:
    float _visibleTime;


  public:
     setDisplayGeometry(DisplayGeometry * dispGeom);


  private:
    float _backgroundTransparency;

    DisplayGeometry * _displayGeometry;

};
#endif
