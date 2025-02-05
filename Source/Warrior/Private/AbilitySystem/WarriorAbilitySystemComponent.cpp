// WSL All Rights Reserved


#include "AbilitySystem/WarriorAbilitySystemComponent.h"

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
