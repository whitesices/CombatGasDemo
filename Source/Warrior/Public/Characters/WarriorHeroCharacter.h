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
#pragma endregion

#pragma region Input
	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly , Category = "CharacterData" , meta=(AllowPrivateAccess = "true") )
	UDataAsset_InputConfig* InputConfigDataAsset;

	void W_Move(const FInputActionValue& InputActionValue);

	void W_Look(const FInputActionValue& InputActionValue);
#pragma endregion

public:
	//内联函数获取combatComponent
	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const
	{
		return HeroCombatComponent;
	}
};
