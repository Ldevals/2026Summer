#include "HitboxManager.h"
#include "Components.h"
#include "Entity.h"

HitboxManager* HitboxManager::instance = nullptr;
void HitboxManager::CreateInstance()
{
	if (!instance)
	{
		instance = new HitboxManager();
	}
}

HitboxManager* HitboxManager::GetInstance()
{
	return instance;
}

void HitboxManager::AddHitbox(HitboxComponent* _hitbox)
{
	hitbox.push_back(_hitbox);
}

void HitboxManager::RemoveHitbox(HitboxComponent* _hitbox)
{
	auto it = std::find(hitbox.begin(), hitbox.end(), _hitbox);
	if (it != hitbox.end())
		hitbox.erase(it);
}

void HitboxManager::Update()
{
	if (hitbox.size() > 0)
	{
		for (size_t i = 0; i < hitbox.size(); ++i)
		{
			for (size_t j = i + 1; j < hitbox.size(); ++j)
			{

				if (hitbox[i]->GetStatic() && hitbox[j]->GetStatic())
					continue;

				sf::FloatRect a = hitbox[i]->GetHitbox();
				sf::FloatRect b = hitbox[j]->GetHitbox();
				if (a.findIntersection(b))
				{
					//	if (hitbox[i]->GetType() == hitbox[j]->GetType())
					//	{
					//		if (hitbox[i]->GetFriendlyColliding() && hitbox[j]->GetFriendlyColliding())
					//		{
					//			//fonction de calcul de collision
					//		}
					//	}
					//	if (hitbox[i]->GetType() == HitboxType::AllyProjectile || hitbox[i]->GetType() == HitboxType::EnemyProjectile)
					//	{
					if (hitbox[i]->GetType() == HitboxType::Body && hitbox[j]->GetType() == HitboxType::Body)
					{
						ResolveBodyToBody(hitbox[i], hitbox[j]);
					}
					else
					{
						ResolveProjectileToBody(hitbox[i], hitbox[j]);
					}
					//ResolveCollision(hitbox[i], hitbox[j]);
				}
			}
		}
	}
}

void HitboxManager::ResolveBodyToBody(HitboxComponent* _hitboxA, HitboxComponent* _hitboxB)
{
	if (_hitboxA->GetTeam() == _hitboxB->GetTeam())
	{
		if (_hitboxA->GetFriendlyColliding() && _hitboxB->GetFriendlyColliding())
			ResolveCollision(_hitboxA, _hitboxB);

	}
	else
	{
		//faire les degats vers le joueur
		std::cout << _hitboxA->GetEntity().name << "  " << _hitboxB->GetEntity().name << std::endl;
		if (_hitboxA->GetTeam() == Team::Enemy)
		{
			_hitboxB->GetEntity().GetComponent<HealthComponent>()->Damage
			(_hitboxA->GetEntity().GetComponent<DamageComponent>()->GetDamage());
		}
		else
		{
			_hitboxA->GetEntity().GetComponent<HealthComponent>()->Damage
			(_hitboxB->GetEntity().GetComponent<DamageComponent>()->GetDamage());
		}

		ResolveCollision(_hitboxA, _hitboxB);
	}

	//voir pour rajouter une catégorie de collision pour les degats de mélee du joueur et des ennemies
}

void HitboxManager::ResolveProjectileToBody(HitboxComponent* _hitboxA, HitboxComponent* _hitboxB)
{
	if (_hitboxA->GetTeam() != _hitboxB->GetTeam())
	{
		//faire degats a l'entity qui contient la hitbox body

		if (_hitboxA->GetType() == HitboxType::Projectile)
		{
			_hitboxB->GetEntity().GetComponent<HealthComponent>()->Damage
			(_hitboxA->GetEntity().GetComponent<DamageComponent>()->GetDamage());
			_hitboxA->GetEntity().isDead = true;
		}
		else
		{
			_hitboxA->GetEntity().GetComponent<HealthComponent>()->Damage
			(_hitboxB->GetEntity().GetComponent<DamageComponent>()->GetDamage());
			_hitboxB->GetEntity().isDead = true;
		}
	}
}

void HitboxManager::ResolveCollision(HitboxComponent* _hitboxA, HitboxComponent* _hitboxB)
{

	sf::FloatRect a = _hitboxA->GetHitbox();
	sf::FloatRect b = _hitboxB->GetHitbox();

	float moveLeft = a.position.x + a.size.x - b.position.x;
	float moveRight = b.position.x + b.size.x - a.position.x;

	float moveUp = a.position.y + a.size.y - b.position.y;
	float moveDown = b.position.y + b.size.y - a.position.y;

	float overlapX = (moveLeft < moveRight) ? moveLeft : -moveRight;
	float overlapY = (moveUp < moveDown) ? moveUp : -moveDown;

	if (std::abs(overlapX) < std::abs(overlapY))
	{
		_hitboxA->Move({ -overlapX * 0.5f, 0.f });
		_hitboxB->Move({ overlapX * 0.5f, 0.f });
	}
	else
	{
		_hitboxA->Move({ 0.f, -overlapY * 0.5f });
		_hitboxB->Move({ 0.f, overlapY * 0.5f });
	}
}
