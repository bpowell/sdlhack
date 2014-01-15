#ifndef _COMPONENTS_H_
#define _COMPONENTS_H_

#include "Component.h"

class PositionComponent : public Component{
	public:
		float x;
		float y;

		PositionComponent(float x, float y);
};

#endif
