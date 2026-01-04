// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMEMORY_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;

	virtual void Shutdown() override;

private:

	TObjectPtr<class UStudent> NonPropStudent; // UPROPERTY 없는 오브젝트 선언

	UPROPERTY()
	TObjectPtr<class UStudent> PropStudent; // UPROPERTY 있는 오브젝트 선언

	TArray<TObjectPtr<class UStudent>> NonPropStudents;

	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> PropStudents;

	class FStudentManager* StudentManager = nullptr;
};
