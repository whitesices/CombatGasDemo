// WSL All Rights Reserved


#include "Components/Combat/EnemyCombatComponent.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	//若击中对象有效
	if (HitActor)
	{
		UE_LOG( LogTemp , Warning , TEXT("Hitactor is right %s "), *HitActor->GetActorNameOrLabel() );
	}
}
