#ifndef _HUDTEXT_H
#define _HUDTEXT_H


////Herite de osg::PAT
class HudText {
	public:
    HudText();

    ~HudText();


	private:
    ////ref_ptr, an should be created in contructor
    osg::Text * _text;

};
#endif
