// WSL All Rights Reserved


#include "DataAssets/Input/DataAsset_InputConfig.h"
//引入GamePlayTag容器
#include "InputAction.h"
#include "InputMappingContext.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InputTag) const
{
	//返回数据资产内的Inputaction
	for (const FWarriorInputActionConfig& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.InputTag == InputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}

	return nullptr;
}
