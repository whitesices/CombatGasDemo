// WSL All Rights Reserved


#include "Items/Weapons/WarriorHeroWeapon.h"

#include "GameplayAbilitySpecHandle.h"

void AWarriorHeroWeapon::AssignGrantedAbilitySpecHanle(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AWarriorHeroWeapon::GetGrantAbilitySpecHandle() const
{
	return GrantAbilitySpecHandles;
}
