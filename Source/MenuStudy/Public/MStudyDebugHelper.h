﻿#pragma once

namespace Debug
{
	static void Print(const FString& Msg, int32 InKey = -1, const FColor& InFColor = FColor::MakeRandomColor())
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 5.f, InFColor, Msg);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
		}
	}
}
