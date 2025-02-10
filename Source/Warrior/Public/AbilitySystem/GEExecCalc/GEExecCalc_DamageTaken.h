// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEExecCalc_DamageTaken.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UGEExecCalc_DamageTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	//伤害计算的构造函数
	UGEExecCalc_DamageTaken();


	//实现Execute函数
	virtual void Execute_Implementation( const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput ) const override;
	
};
