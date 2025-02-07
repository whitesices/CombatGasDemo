// WSL All Rights Reserved

#pragma once
//引入GameplayTagContainer
#include "GameplayTagContainer.h"

#include "WarriorStructTypes.generated.h"

//引入相应的前置声明
class UWarriorHeroLinkedAnimLayer;
class UWarriorGameplayAbility;
class UWarriorAbilitySystemComponent;
class UInputMappingContext;
class UWarriorHeroGameplayAbility;
//class UWarriorEnemyGameplayAbility;

USTRUCT(BlueprintType)
struct FWarriorHeroAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	//声明自定义的AbilitySystemComponent
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWarriorHeroGameplayAbility> AbilityToGrant;

	//创建有效性函数
	bool IsValid() const;
};

//声明敌人属性集合
//USTRUCT(BlueprintType)
//struct FWarriorEnemyAbilitySet
//{
//	GENERATED_BODY()
//
//	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , meta = ( Categories = "InputTag") )
//	FGameplayTag InputTag;
//
//	//声明自定义的AbilitySystemComponent
//	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly )
//	TSubclassOf<UWarriorEnemyGameplayAbility> AbilityToGrant;
//
//	//创建有效性函数
//	bool IsValid() const;
//};

USTRUCT(BlueprintType)
struct FWarriorHeroWeaponData
{
	GENERATED_BODY()

	//声明一个属性
	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly)
	TSubclassOf<UWarriorHeroLinkedAnimLayer> WeaponAnimLayerToLink;

	//声明英雄属性集
	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , meta = (TitleProperty="InputTag") )
	TArray<FWarriorHeroAbilitySet> DefaultWeaponAbilities;

	//声明InputMappingContext
	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly)
	UInputMappingContext* WInputMappingContext;
};
