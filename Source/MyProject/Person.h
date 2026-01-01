// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Person.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UPerson : public UObject
{
	GENERATED_BODY()

public:
	UPerson();

	UFUNCTION()
	virtual void DoLesson();

	const FString& GetName() const;
	void SetName(const FString& InName);

protected:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Year;

private:
	
};
