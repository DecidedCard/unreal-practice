// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	TCHAR LogCharArray[] = TEXT("Hello Unreal");  // TCHAR 배열 선언 및 초기화
	UE_LOG(LogTemp, Log, TEXT("%s"), LogCharArray);

	FString LogCharString = LogCharArray;  // TCHAR 배열을 FString으로 변환
	UE_LOG(LogTemp, Log, TEXT("%s"), *LogCharString);

	const TCHAR* LongCharPtr = *LogCharString;  // 포인터 연산자를 사용해서 FString에서 TCHAR*로 변환
	TCHAR* LogCharDataPtr = LogCharString.GetCharArray().GetData();  // GetCharArray()와 GetData()를 사용해서 TCHAR*로 변환

	TCHAR LogCharArrayWithSize[100];
	FCString::Strcpy(LogCharArrayWithSize, LogCharString.Len(), *LogCharString); // FCString::Strcpy 사용, 저수준의 복사

	if (LogCharString.Contains(TEXT("unreal"), ESearchCase::IgnoreCase))  // 대소문자 무시하고 포함 여부
	{
		int32 Index = LogCharString.Find(TEXT("unreal"), ESearchCase::IgnoreCase);  // 대소문자 무시하고 위치 찾기
		FString EndString = LogCharString.Mid(Index);  // Mid() 함수로 부분 문자열 추출
		UE_LOG(LogTemp, Log, TEXT("Find Test: %s"), *EndString);  // 결과 출력
	}

	FString Left, Right; // 분할된 문자열을 저장할 변수
	if (LogCharString.Split(TEXT(" "), &Left, &Right)) // Split() 함수로 문자열 분할
	{
		UE_LOG(LogTemp, Log, TEXT("Split Test: %s 와 %s"), *Left, *Right);
	}
}
 