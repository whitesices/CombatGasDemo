// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/WarriorBaseCharacter.h"

#include "WarriorHeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;
class UHeroCombatComponent;
struct FGameplayTag;
class UHeroUIComponent;

/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorHeroCharacter : public AWarriorBaseCharacter
{
	GENERATED_BODY()
public:
	//定义一个构造函数
	AWarriorHeroCharacter();

	//重写GetPawnCombatComponent ~ Begin IPawnCombatInterface 
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//end IPawnCombatInterface

	//重写GetPawnUIComponent ~Begin IPawnUIInterface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	//end IPawnUIInterface

	//重写GetHeroUIComponent ~Begin IPawnUIInterface
	virtual UHeroUIComponent* GetCurrentHeroUIComponent() const override;
	//end IPawnUIInterface

protected:
	//重写PossessedBy ， ~Begin APawn Inetrface
	virtual void PossessedBy(AController* NewController) override;
	//~End APawn Inetrface

	//重写BeginPlay函数
	virtual void BeginPlay() override;

	//重写输入操作的函数
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	//创建所需的组件
#pragma region Components
	//定义相机所需的弹簧臂组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "Camera" , meta = (AllowPrivateAccess = "true") )
	USpringArmComponent* CameraBoom;
	//定义相机组件变量
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = "Camera" , meta = (AllowPrivateAccess = "true") )
	UCameraComponent* FllowCamera;

	//声明战斗系统组件变量
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UHeroCombatComponent* HeroCombatComponent;

	//声明UIComponent
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "UI" , meta = (AllowPrivateAccess = "true"))
	UHeroUIComponent* HeroUIComponent;

#pragma endregion

#pragma region Input
	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly , Category = "CharacterData" , meta=(AllowPrivateAccess = "true") )
	UDataAsset_InputConfig* InputConfigDataAsset;

	void W_Move(const FInputActionValue& InputActionValue);

	void W_Look(const FInputActionValue& InputActionValue);

	//定义装备武器技能按下的方法
	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	//定义装备武器技能释放的方法
	void Input_AbilityInputRelease(FGameplayTag InInputTag);
#pragma endregion

public:
	//内联函数获取combatComponent
	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const
	{
		return HeroCombatComponent;
	}

	//内联函数获取UIComponent
	FORCEINLINE UHeroUIComponent* GetHeroUIComponent() const
	{
		return HeroUIComponent;
	}
};
