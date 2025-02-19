// WSL All Rights Reserved


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/WarriorAttributeSet.h"
//引入GameplayTag 头文件
#include "WarriorGameplayTags.h"

//引入打印辅助头文件
#include "WarriorDebugHelper.h"

//通过辅助宏的方式快速捕获相应的属性
//先声明一个结构体做媒介
struct FWarriorDamageCapture
{
	//捕获定义的Attribute属性
	DECLARE_ATTRIBUTE_CAPTUREDEF( AttackPower )
	DECLARE_ATTRIBUTE_CAPTUREDEF( DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF( DamageTaken )

	//定义构造函数
	FWarriorDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF( UWarriorAttributeSet, AttackPower , Source , false )
		DEFINE_ATTRIBUTE_CAPTUREDEF( UWarriorAttributeSet, DefensePower, Target , false )
		DEFINE_ATTRIBUTE_CAPTUREDEF( UWarriorAttributeSet, DamageTaken , Target , false )
	}
};

//创建一个获取FWarriorDamageCapture的函数
static const FWarriorDamageCapture& GetWarriorDamageCapture()
{
	static FWarriorDamageCapture WarriorDamageCapture;
	return WarriorDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	//比较慢的捕获属性的方式
	//FProperty*  AttackPowerPro= FindFieldChecked<FProperty>(
	//	UWarriorAttributeSet::StaticClass(),
	//	GET_MEMBER_NAME_CHECKED(UWarriorAttributeSet , AttackPower )
	//);

	////AttackPower GE属性捕获定义
	//FGameplayEffectAttributeCaptureDefinition AttackPowerAttributeCaptureDefinition( AttackPowerPro , EGameplayEffectAttributeCaptureSource::Source , false );

	////添加捕获的属性
	//RelevantAttributesToCapture.Add(AttackPowerAttributeCaptureDefinition);

	//添加捕获的属性
	RelevantAttributesToCapture.Add( GetWarriorDamageCapture().AttackPowerDef );
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DefensePowerDef );
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	//创建GEspec临时变量
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	//因为在HeroCombatGameAbility中设置了相关属性所以在计算类中暂时不用去获取
	////获取SourceObject
	//EffectSpec.GetContext().GetSourceObject();
	////获取ability
	//EffectSpec.GetContext().GetAbility();
	////获取发起者
	//EffectSpec.GetContext().GetInstigator();
	////获取GameEffect制造者
	//EffectSpec.GetContext().GetEffectCauser();

	//创建评估参数局部变量
	FAggregatorEvaluateParameters EvaluateParameters;
	//设置来源和目标
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	//创建一个sourceAttackPower局部float变量
	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude( GetWarriorDamageCapture().AttackPowerDef , EvaluateParameters , SourceAttackPower );
	/*Debug::print(TEXT("SourceAttackPower is "), SourceAttackPower);*/

	//声明一个基础伤害的局部变量
	float BaseDamage = 0.f;
	

	//声明一个局部变量来存储LightAttack的战斗动作索引
	int32 UsedLightAttackComboCount = 0;
	

	//声明一个局部变量来存储HeavyAttack的战斗动作索引
	int32 UsedHeavyAttackComboCount = 0;
	
	

	//检索找到的GameplayTag 
	for ( const TPair< FGameplayTag , float >& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes )
	{
		//判断获取的BaseDamage Key值是否有效
		if ( TagMagnitude.Key.MatchesTagExact( WarriorGameplayTags::Shared_SetByCaller_BaseDamage ) )
		{
			//存储从GameAbility传递过来的BaseDamage数据
			BaseDamage = TagMagnitude.Value;
			/*Debug::print(TEXT("BaseDamage is "), BaseDamage);*/
		}

		//判断获取的LightAttack Key值是否有效
		if ( TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Player_SetByCaller_AttackType_Light ) )
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			/*Debug::print(TEXT("UsedLightAttackComboCount is "), UsedLightAttackComboCount);*/
		}

		if (TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Player_SetByCaller_AttackType_Heavy ) )
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			/*Debug::print(TEXT("UsedHeavyAttackComboCount is "), UsedHeavyAttackComboCount);*/
		}
	}

	//调用Print函数打印初始值
	//Debug::print( TEXT("after search BaseDamage is %f  ,  UsedLightAttackComboCount is %d  , UsedHeavyAttackComboCount is %d "), BaseDamage , UsedLightAttackComboCount, UsedHeavyAttackComboCount,FColor::Cyan );
	

	float TargetDefensePower = 0.f;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);
	//Debug::print(TEXT("TargetDefensePower is "), TargetDefensePower);

	//检查UsedLightAttackComboCount 是否为零
	if ( UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = ( UsedLightAttackComboCount - 1 ) * 0.05 + 1.f ;

		BaseDamage *= DamageIncreasePercentLight;

		//Debug::print(TEXT("ScaledLightAttackBaseDamage is "), BaseDamage);
	}

	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;
		BaseDamage *= DamageIncreasePercentHeavy;
		//Debug::print(TEXT("ScaledHeavyAttackBaseDamage is "), BaseDamage);
	}



	//计算最终的伤害值
	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower ;
	//ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().DamageTakenDef , EvaluateParameters, TargetDefensePower);
	//Debug::print( TEXT("FinalDamageDone is "), FinalDamageDone );

	//若最后伤害大于零
	if ( FinalDamageDone > 0.f )
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetWarriorDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone
			)
		);
	}


}

