#pragma once

//声明一个命名空间
namespace Debug
{
	static void print( const FString& Msg , const FColor& Color = FColor::MakeRandomColor() , int32 InKey = -1 )
	{
		//将信息打印到屏幕上
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage( InKey , 7.f , Color , Msg);

			//将消息打印到日志上
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
		}

	}

	//建议一个新的打印函数去打印数值
	static void print( const FString& FloatTitle , float FloatValueToPrint , int32 InKey = -1 , const FColor& Color = FColor::MakeRandomColor() )
	{
		//将信息打印到屏幕上
		if (GEngine)
		{
			const FString FinalMsg = FloatTitle + TEXT(": ") + FString::SanitizeFloat(FloatValueToPrint);

			GEngine->AddOnScreenDebugMessage( InKey , 7.f , Color , FinalMsg);

			//将消息打印到日志上
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMsg);
		}

	}
}