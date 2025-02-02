// WSL All Rights Reserved


#include "Components/Combat/PawnCombatComponent.h"


void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister, bool bResgisterAsEquippedWeapon)
{
	//检查有效性
	checkf( !CharacterCarriedWeaponMap.Contains( InWeaponTagToRegister ) , TEXT("A named %s has already been added as carried weapon") , *InWeaponTagToRegister.ToString() );
	//检查有效性
	check(InWeaponToRegister);

	CharacterCarriedWeaponMap.Emplace( InWeaponTagToRegister , InWeaponToRegister );

	//如果装备了
	if (bResgisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	//判断Gameplaytag的有效性
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (AWarriorWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *FoundWeapon;
		}
	}


	return nullptr;
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	//判断当前装备武器的Tag是否有效
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}
