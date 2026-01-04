// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * c++ 오브젝트를 언리얼 오브젝트에서 사용시 FGCObject를 상속한 다음
 * AddReferencedObjects, GetReferencerName함수 구현
 */
class UNREALMEMORY_API FStudentManager : public FGCObject
{
public:
	FStudentManager(class UStudent* InStudent) : SafeStudent(InStudent) {}

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override
	{
		return TEXT("FStudentManager");
	}


	const class UStudent* GetStudent() const { return SafeStudent; }

private:
	class UStudent* SafeStudent = nullptr;
};
