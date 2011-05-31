#pragma once
#include "Node.h"


class AnimationNode : public Node
{
public:
	AnimationNode(void);
	~AnimationNode(void);

	void render(void);
};

