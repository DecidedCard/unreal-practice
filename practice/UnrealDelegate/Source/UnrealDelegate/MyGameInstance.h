// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALDELEGATE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();  // 생성자 선언

	virtual void Init() override;

private:

	UPROPERTY()
	TObjectPtr<class UCourseInfo> CourseInfo;  // UCourseInfo 객체에 대한 포인터

	UPROPERTY()  // UPROPERTY 매크로 사용
	FString SchoolName;  // 학교 이름을 저장하는 FString 변수

};
