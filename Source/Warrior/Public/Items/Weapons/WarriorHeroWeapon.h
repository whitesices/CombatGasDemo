// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/WarriorWeaponBase.h"

//引入自定义的武器类型
#include "WarriorTypes/WarriorStructTypes.h"
#include "WarriorHeroWeapon.generated.h"

struct FGameplayAbilitySpecHandle;

/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorHeroWeapon : public AWarriorWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly , Category="WeaponData")
	FWarriorHeroWeaponData HeroWeaponData;

	//定义set和Get来处理私有变量
	UFUNCTION( BlueprintCallable )
	void AssignGrantedAbilitySpecHanle( const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION( BlueprintPure )
	TArray<FGameplayAbilitySpecHandle> GetGrantAbilitySpecHandle() const;
	
private:
	//声明变量存储技能句柄
	TArray<FGameplayAbilitySpecHandle> GrantAbilitySpecHandles;
};
