// WSL All Rights Reserved


#include "AIController/WarriorAIController.h"
#include "Navigation/CrowdFollowingComponent.h"

//引入感知组件头文件
#include "Perception/AIPerceptionComponent.h"
//引入AI视觉感知配置头文件
#include "Perception/AISenseConfig_Sight.h"
//引入行为树组件头文件
#include "BehaviorTree/BlackboardComponent.h"

//引入打印日志头文件
#include "WarriorDebugHelper.h"

AWarriorAIController::AWarriorAIController(const FObjectInitializer& ObjectInitializer):Super( ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	//判断CrowdComp的有效性
	/*if (UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		Debug::print(  TEXT("CrowdFollowingComponent valid"),FColor::Green );
	}*/

	//创建视觉感知组件
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("EnemySenseConfig_Sight");
	//设置感知Enemy为true
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	//设置感知Friendly为False
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	//设置感知范围
	AISenseConfig_Sight->SightRadius = 5000.f;
	//设置寻路侧边,设置为零使其不会丢失玩家视野
	AISenseConfig_Sight->LoseSightRadius = 0.f;
	//设置周边视野,设置为360 让Enemy一直看到玩家
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;

	//创建感知组件
	EnemyPerceptionComonent = CreateDefaultSubobject<UAIPerceptionComponent>("EnemyAIPerceptionComponent");
	//感知组件配置感知配置的相关参数
	EnemyPerceptionComonent->ConfigureSense(*AISenseConfig_Sight);
	//设置感知类
	EnemyPerceptionComonent->SetDominantSense( UAISenseConfig_Sight::StaticClass() );
	//更新感知参数
	EnemyPerceptionComonent->OnTargetPerceptionUpdated.AddUniqueDynamic(this,&AWarriorAIController::OnEnemyPerceptionUpdated);
	//写入自己定义所添加的团队值
	SetGenericTeamId( FGenericTeamId(1) );
}

ETeamAttitude::Type AWarriorAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	//获取相应的对象
	const APawn* PawnToCheck = Cast<const APawn>(&Other);

	//获取相应接口
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>( PawnToCheck->GetController() );

	//判断获取Id的有效性
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() != GetGenericTeamId())
	{
		return ETeamAttitude::Hostile;
	}

	return ETeamAttitude::Friendly;
}

void AWarriorAIController::BeginPlay()
{
	Super::BeginPlay();

	//判断CrowdComp的有效性
	if (UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		Debug::print(TEXT("CrowdFollowingComponent valid"), FColor::Green);
		CrowdComp->SetCrowdSimulationState( bEnableDetourCrowdAvoidance ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled );

		//选择路由质量
		switch ( DetourCrowdAvoiddanceQuality )
		{
			case 1: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);break;
			case 2: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);break;
			case 3: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);break;
			case 4: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);break;
			default:
				break;
		}

		//设置CrowdComp 的相应参数
		CrowdComp->SetAvoidanceGroup(1);
		CrowdComp->SetGroupsToAvoid(1);
		CrowdComp->SetCrowdCollisionQueryRange( CollisionQueryRange );
	}
}

void AWarriorAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	//更新感知信息
	if (Stimulus.WasSuccessfullySensed() && Actor)
	{
		//Debug::print( Actor->GetActorNameOrLabel() + TEXT(" was sensd"),FColor::Green );
		//判断黑板组件的有效性来存储TargetActor
		if (UBlackboardComponent* BlackboradComponent = GetBlackboardComponent())
		{
			//传递相应的数据,添加所要传递数据的键值名
			BlackboradComponent->SetValueAsObject(FName("TargetActor"), Actor);
		}
	}
}
