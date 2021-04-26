#pragma once
#include "entityPool.h"


class BulletPool : public EntityPool<BulletPool>
{
protected:

public:
	static unsigned char poolPointer;
	static std::shared_ptr<Entity> pool[256];
};

