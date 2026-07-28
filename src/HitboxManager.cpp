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

void HitboxManager::Update()
{
	if (hitbox.size() > 0)
	{
		for (size_t i = 0; i < hitbox.size(); ++i)
		{
			for (size_t j = i + 1; j < hitbox.size(); ++j)
			{
				sf::FloatRect a = hitbox[i]->GetHitbox();
				sf::FloatRect b = hitbox[j]->GetHitbox();

				if (hitbox[i]->GetStatic() && hitbox[j]->GetStatic())
					continue;

				if (a.findIntersection(b))
				{
					if (hitbox[i]->GetType() == hitbox[j]->GetType())
					{
						if (hitbox[i]->GetFriendlyColliding() && hitbox[j]->GetFriendlyColliding())
						{
							//fonction de calcul de collision
						}
					}
					if (hitbox[i]->GetType() == HitboxType::Neutral || hitbox[j]->GetType() == HitboxType::Neutral)
					{

					}
					{
						switch (hitbox[i]->GetType())
						{
						case HitboxType::Ally:
							switch (hitbox[j]->GetType())
							{
							case HitboxType::Ally:
								if (hitbox[i]->GetFriendlyColliding() && hitbox[j]->GetFriendlyColliding())
								{
									//fonction de calcul de collision
								}
								break;
							case HitboxType::Enemy:

								break;
							}
							break;
						}
					}

					float moveLeft = a.position.x + a.size.x - b.position.x;
					float moveRight = b.position.x + b.size.x - a.position.x;

					float moveUp = a.position.y + a.size.y - b.position.y;
					float moveDown = b.position.y + b.size.y - a.position.y;

					float overlapX = (moveLeft < moveRight) ? moveLeft : -moveRight;
					float overlapY = (moveUp < moveDown) ? moveUp : -moveDown;

					if (std::abs(overlapX) < std::abs(overlapY))
					{
						hitbox[i]->Move({ -overlapX * 0.5f, 0.f });
						hitbox[j]->Move({ overlapX * 0.5f, 0.f });
					}
					else
					{
						hitbox[i]->Move({ 0.f, -overlapY * 0.5f });
						hitbox[j]->Move({ 0.f, overlapY * 0.5f });
					}
				}
			}
		}

	}
}
