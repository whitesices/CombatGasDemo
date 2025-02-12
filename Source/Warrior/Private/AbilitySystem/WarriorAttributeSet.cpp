// WSL All Rights Reserved


#include "AbilitySystem/WarriorAttributeSet.h"

//引入FGameplayEffectModCallbackData的头文件
#include "GameplayEffectExtension.h"

#include "WFunctionLibrary.h"
#include "WarriorGameplayTags.h"

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
	//判断传入数据中是否有当前健康属性
	if ( Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		//声明一个局部变量存储获得的当前健康值
		const float NewCurrentHealth = FMath::Clamp( GetCurrentHealth() , 0.f , GetMaxHealth() );

		//设置当前的健康属性值
		SetCurrentHealth(NewCurrentHealth);
	}

	//修改当前范围
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		//声明一个局部变量存储当前的范围值
		const float NewCurrentRage = FMath::Clamp( GetCurrentRage(), 0.f , GetMaxRage() );

		//设置当前范围值
		SetCurrentRage(NewCurrentRage);
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
		const FString DebugString = FString::Printf( TEXT("Old Health is %f , Damage Done is %f , NewCurrentHealth is %f"), OldHealth , DamageDone , NewCurrentHealth );
		//调用屏幕打印函数
		Debug::print(DebugString, FColor::Green);

		//TODO::Notify the UI

		//TODO::Handle character death
		if ( NewCurrentHealth == 0.f )
		{
			//调用自定义蓝图函数库中的给目标actor添加gameplaytag
			UWFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), WarriorGameplayTags::Shared_Status_Dead );
		}
	}
}
