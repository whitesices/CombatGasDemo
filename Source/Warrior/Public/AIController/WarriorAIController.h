// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WarriorAIController.generated.h"


class UAIPerceptionComponent;
class UAISenseConfig_Sight;
/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	//建立新的构造函数
	AWarriorAIController( const FObjectInitializer& ObjectInitializer);

	//重写获取团队成员的ID方法
	//begin IGenericTeamAgentInterface
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	//end IGenericTeamAgentInterface

protected:
	//重写Beginplay函数
	virtual void BeginPlay() override;

	//声明EnemyAI感知组件变量
	UPROPERTY( VisibleAnywhere,BlueprintReadOnly )
	UAIPerceptionComponent* EnemyPerceptionComonent;

	//声明视觉感知配置文件
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	UAISenseConfig_Sight* AISenseConfig_Sight;

	//新建一个函数来更新感知数据
	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

private:
	//声明避让策略信息值
	UPROPERTY( EditDefaultsOnly , Category = "Detour Crowd Avoidance Config")
	bool bEnableDetourCrowdAvoidance = true;

	//声明避让策略
	UPROPERTY( EditDefaultsOnly , Category = "Detour Crowd Avoidance Config" , meta = ( EditCondition = "bEnableDetourCrowdAvoidance",UIMin = "1",UIMax="4") )
	int32 DetourCrowdAvoiddanceQuality = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourCrowdAvoidance"))
	float CollisionQueryRange = 600.f;
};
