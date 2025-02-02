// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
//引入Gameplaytagcontainertou头文件
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

//struct FGameplayTag;
class AWarriorWeaponBase;
/**
 * 
 */
UCLASS()
class WARRIOR_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable , Category = "Warrior|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister , bool bResgisterAsEquippedWeapon = false);

	UFUNCTION( BlueprintCallable , Category = "Warrior|Combat")
	AWarriorWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UPROPERTY( BlueprintReadWrite , Category = "Warrior|Combat" )
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION( BlueprintCallable , Category = "Warrior|Combat")
	AWarriorWeaponBase* GetCharacterCurrentEquippedWeapon() const;



private:
	TMap<FGameplayTag, AWarriorWeaponBase*> CharacterCarriedWeaponMap;
};
