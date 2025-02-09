// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//引入AbilitySystemInterface头文件
#include "AbilitySystemInterface.h   "
//引入自定义的PawnCombatInterface（中介者模式)
#include "Interfaces/PawnCombatInterface.h"

#include "WarriorBaseCharacter.generated.h"

class UWarriorAbilitySystemComponent;
class UWarriorAttributeSet;
class UAbilitySystemComponent;
class UDataAsset_StartUpDataBase;

UCLASS()
class WARRIOR_API AWarriorBaseCharacter : public ACharacter , public IAbilitySystemInterface , public IPawnCombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWarriorBaseCharacter();

	//重写UAbilitySystemComponent ， ~Begin IAbilitySystemInterface Inetrface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~End IAbilitySystemInterface Inetrface

	//重写GetPawnCombatComponent ~ Begin IPawnCombatInterface 
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//end IPawnCombatInterface

protected:
	//重写PossessedBy ， ~Begin APawn Inetrface
	virtual void PossessedBy( AController* NewController) override;
	//~End APawn Inetrface

	//引入AbilitySystemComponent
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = "AbilitySystem" )
	UWarriorAbilitySystemComponent* WAbilitySystemComponent;
	//声明创建AttributeSet
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = "AttributeSet")
	UWarriorAttributeSet* WAttributeSet;

	//声明一个DataAsset
	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase>  CharcaterStartUpData;

public:
	//定义一个内联函数获取AbilitySystemComponent
	FORCEINLINE UWarriorAbilitySystemComponent* GetWarriorAbilitySystemComponent() const { return WAbilitySystemComponent; }
	//定义一个内联函数获取AttributeSet
	FORCEINLINE UWarriorAttributeSet* GetWarriorAttributeSet() const { return WAttributeSet; }
};
