#ifndef _MACROS_H_
#define _MACROS_H_

/** Needs to be used in all callback to be able to be managed by the callbackManager */
#define METADATA(name) virtual const char* className() const { return #name; }

#endif //_MACROS_H_

