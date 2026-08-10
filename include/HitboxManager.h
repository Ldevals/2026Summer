#include "common.h"

class HitboxComponent;
class HitboxManager
{
public:
	static void CreateInstance();
	static HitboxManager* GetInstance();
	void AddHitbox(HitboxComponent* _hitbox);
	void RemoveHitbox(HitboxComponent* _hitbox);
	void Update();

private:
	HitboxManager(){}

	void ResolveBodyToBody(HitboxComponent* _hitboxA, HitboxComponent* _hitboxB);
	void ResolveProjectileToBody(HitboxComponent* _hitboxA, HitboxComponent* _hitboxB);
	void ResolveCollision(HitboxComponent* _hitboxA, HitboxComponent* _hitboxB);
	std::vector<HitboxComponent*> hitbox;
	static HitboxManager* instance;
};
