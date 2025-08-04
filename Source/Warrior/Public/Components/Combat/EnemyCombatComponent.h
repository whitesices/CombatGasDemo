// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "EnemyCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UEnemyCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	//重写相应函数
	virtual void OnHitTargetActor(AActor* HitActor) override;
	//重写BodyCollision
	virtual void ToggleBodyCollisionBoxCollision(bool bShouldEnbale, EToggleDamageType ToggleDamageType) override;

	
};
