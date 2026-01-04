// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

USTRUCT()
struct FStudentData // Example struct to hold student data
{
	GENERATED_BODY()

	FStudentData()
	{
		Name = TEXT("홍길동");
		Order = 1;
	}

	FStudentData(FString InName, int32 InOrder) : Name(InName), Order(InOrder) {}

	bool operator == (const FStudentData& InOther) const
	{
		return Order == InOther.Order;
	}

	friend FORCEINLINE uint32 GetTypeHash(const FStudentData& InStudentData)
	{
		return GetTypeHash(InStudentData.Order);
	}

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Order;
};

/**
 * 
 */
UCLASS()
class UNREALCONTAINER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

	public:
		virtual void Init() override;

private:
	TArray<FStudentData> StudentsData;

	UPROPERTY() // 필수
	TArray<TObjectPtr<class UStudent>>Students; // 언리얼 오브젝트를 TArray로 관리 시

	TMap<int32, FString> StudentsMap; // 키, 밸류로 생성. 키나 밸류에 언리얼 오브젝트가 들어갈 시 UPROPERTY필수 그외는 선택사항.
	
};
