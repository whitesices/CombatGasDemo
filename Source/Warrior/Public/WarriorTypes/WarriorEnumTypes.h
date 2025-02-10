#pragma once

//创建一个枚举类型
UENUM()
enum class EWarriorConfirmType : uint8
{
	Yes,
	No
};

//创建一个有效性的枚举类型
UENUM()
enum class EWarriorValidType : uint8
{
	Valid,
	InValid
};

//创建一个判断是否成功应用GE的枚举类型
UENUM()
enum class EWarriorSuccessType : uint8
{
	Successful,
	Failed
};