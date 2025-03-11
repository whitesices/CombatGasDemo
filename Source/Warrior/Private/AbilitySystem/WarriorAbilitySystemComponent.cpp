// WSL All Rights Reserved


#include "AbilitySystem/WarriorAbilitySystemComponent.h"
//引入自定义的GameplayAbility
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
//引入HeroAbilitySystem
#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"

void UWarriorAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	//判断InInputTag 的有效性
	if (!InInputTag.IsValid()) return;

	//获取对应的ability并激活
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		//检验技能句柄是否有效以及Tag是否匹配
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;

		TryActivateAbility(AbilitySpec.Handle);

	}
}

void UWarriorAbilitySystemComponent::OnAbilityInputRelease(const FGameplayTag& InInputTag)
{
	//判断InInputTag的有效性
	if (!InInputTag.IsValid()) return;

	//获取对应的Ability并激活
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		//检验技能句柄是否有效
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;
		//激活匹配tag的ability
		TryActivateAbility(AbilitySpec.Handle);
	}
	
}

void UWarriorAbilitySystemComponent::GrantHeroWEaponAbilities(const TArray<FWarriorHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel , TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	//判断武器技能是否为空
	if (InDefaultWeaponAbilities.IsEmpty())
	{
		return;
	}

	//读取每一个英雄属性参数集
	for (const FWarriorHeroAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		//判断读取的AbilitySet是否有效
		if (!AbilitySet.IsValid()) continue;

		//声明SpecHandle
		FGameplayAbilitySpec AbilitySpec( AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		//GiveAbility(AbilitySpec);
		//技能在一个数组内进行管理
		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UWarriorAbilitySystemComponent::RemoveHeroWEaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandleToRemove)
{
	//判断武器技能是否为空
	if (InSpecHandleToRemove.IsEmpty())
	{
		return;
	}

	//遍历传过来的句柄
	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandleToRemove)
	{
		if (SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}
	InSpecHandleToRemove.Empty();
}

bool UWarriorAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagByActivate)
{
	/*return false;*/
	//检查Tag是否有效
	if ( !AbilityTagByActivate.IsValid() )
	{
		return false;
	}

	//声明一个GameplayTag数组来存储
	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;

	//通过激活的技能匹配相应的Tag
	GetActivatableGameplayAbilitySpecsByAllMatchingTags( AbilityTagByActivate.GetSingleTagContainer() , FoundAbilitySpecs );

	//检查这种技能是否有效
	if ( !FoundAbilitySpecs.IsEmpty() )
	{
		const int32 RandomAbilityIndex = FMath::RandRange( 0 , FoundAbilitySpecs.Num() - 1 );

		FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];

		//检查SpecToActivate有效性
		check( SpecToActivate );

		//检查是否被激活
		if ( !SpecToActivate->IsActive() )
		{
			//返回是否激活技能
			return TryActivateAbility( SpecToActivate->Handle );
		}

	}

	return false;
}
