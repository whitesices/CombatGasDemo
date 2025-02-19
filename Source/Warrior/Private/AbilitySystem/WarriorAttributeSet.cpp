// WSL All Rights Reserved


#include "AbilitySystem/WarriorAttributeSet.h"

//引入FGameplayEffectModCallbackData的头文件
#include "GameplayEffectExtension.h"

#include "WFunctionLibrary.h"
#include "WarriorGameplayTags.h"

//引入PawnUI接口
#include "Interfaces/PawnUIInterface.h"
//引入PawnUI组件头文件
#include "Components/UI/PawnUIComponent.h"
//引入HeroUI组件头文件
#include "Components/UI/HeroUIComponent.h"

//引入打印信息到屏幕的头文件
#include "WarriorDebugHelper.h"


UWarriorAttributeSet::UWarriorAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);

	
}

void UWarriorAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	//判断缓存UI接口的有效性,这样避免频繁的进行接口变量拷贝赋值
	if (!CachedPawnInterface.IsValid())
	{
		//通过传递的数据获取发起者
		CachedPawnInterface = TWeakInterfacePtr<IPawnUIInterface>( Data.Target.GetAvatarActor() );

		//与上文实现的功能是一致的
		/*CachedPawnInterface = Cast<IPawnUIInterface>(Data.Target.GetAvatarActor());*/
	}

	//通过断言判断UI接口是否有效
	checkf( CachedPawnInterface.IsValid() , TEXT("%s didn't implement IPawnUIInterface "),*Data.Target.GetAvatarActor()->GetActorNameOrLabel() );

	//声明一个PawnUI的局部变量来存储
	UPawnUIComponent* PawnUIComponent = CachedPawnInterface->GetPawnUIComponent();

	//声明一个HeroUI的局部变量来存储
	//UHeroUIComponent* HeroUIComponent = CachedPawnInterface->GetCurrentHeroUIComponent();

	//通过断言判断PawnUI组件是否有效
	checkf( PawnUIComponent , TEXT(" Coundn't extrac a PawnUIComponent from %s "), *Data.Target.GetAvatarActor()->GetActorNameOrLabel() );

	//通过断言判断HeroUI组件是否有效
	//checkf(HeroUIComponent, TEXT(" Coundn't extrac a HeroUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	////调用获取UI的接口函数，
	//UPawnUIComponent* PawnUIComponent = Cast<UPawnUIComponent>( CachedPawnInterface->GetPawnUIComponent() );
	
	//判断传入数据中是否有当前健康属性
	if ( Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		//声明一个局部变量存储获得的当前健康值
		const float NewCurrentHealth = FMath::Clamp( GetCurrentHealth() , 0.f , GetMaxHealth() );

		//设置当前的健康属性值
		SetCurrentHealth(NewCurrentHealth);

		//通过PawnUI的委托广播传递相应健康百分值 数据
		PawnUIComponent->OnCurrentHealthChanged.Broadcast((GetCurrentHealth() / GetMaxHealth()));
	}

	//修改当前范围
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		//声明一个局部变量存储当前的范围值
		const float NewCurrentRage = FMath::Clamp( GetCurrentRage(), 0.f , GetMaxRage() );

		//设置当前范围值
		SetCurrentRage(NewCurrentRage);

		////通过PawnUI的委托广播传递相应健康百分值 数据
		//PawnUIComponent->OnCurrentHealthChanged.Broadcast((GetCurrentHealth() / GetMaxHealth()));
		//通过HeroUI的委托广播传递相应的愤怒百分值的数据
		//HeroUIComponent->OnCurrentRageChanged.Broadcast( ( GetCurrentRage()/ GetMaxRage()) );
		//判断获取的HeroUI是否有效
		if( UHeroUIComponent * HeroUIComponent = CachedPawnInterface->GetCurrentHeroUIComponent() )
		{
			HeroUIComponent->OnCurrentRageChanged.Broadcast((GetCurrentRage() / GetMaxRage()));
		 }
	}

	//计算受到伤害后的健康值并修改当前健康值
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		//声明过去健康值局部变量
		const float OldHealth = GetCurrentHealth();
		//声明受到伤害值的局部变量
		const float DamageDone = GetDamageTaken();

		//声明一个局部变量存储计算受到伤害后的健康值
		const float NewCurrentHealth = FMath::Clamp( OldHealth - DamageDone , 0.f , GetMaxHealth() );

		//设置当前的健康值
		SetCurrentHealth(NewCurrentHealth);

		//声明一个调试信息字符串局部变量
		//const FString DebugString = FString::Printf( TEXT("Old Health is %f , Damage Done is %f , NewCurrentHealth is %f"), OldHealth , DamageDone , NewCurrentHealth );
		//调用屏幕打印函数
		//Debug::print(DebugString, FColor::Green);

		/************************************ Notify the UI *******************************************/
		//TODO::Notify the UI
		//通过PawnUI的委托广播传递相应健康百分值 数据
		PawnUIComponent->OnCurrentHealthChanged.Broadcast( ( GetCurrentHealth() / GetMaxHealth() ) );

		//打印当前值的变化
		//FString DebugText = FString:;printf(TEXT("About CurentHealthPercent is %f"), (GetCurrentHealth() / GetMaxHealth()));
		Debug::print( TEXT("About CurentHealthPercent is ") , ( GetCurrentHealth() / GetMaxHealth() ) );

		/************************************ Notify the UI *******************************************/

		//TODO::Handle character death
		if ( GetCurrentHealth() == 0.f )
		{
			//调用自定义蓝图函数库中的给目标actor添加gameplaytag
			UWFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), WarriorGameplayTags::Shared_Status_Dead );
		}
	}
}
