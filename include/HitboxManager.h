#include "common.h"

class HitboxComponent;
class HitboxManager
{
public:
	static void CreateInstance();
	static HitboxManager* GetInstance();
	void AddHitbox(HitboxComponent* _hitbox);
	void Update();

private:
	HitboxManager(){}

	std::vector<HitboxComponent*> hitbox;
	static HitboxManager* instance;
};
