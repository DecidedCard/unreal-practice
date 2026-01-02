// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Teacher.h"
#include "Student.h"
#include "Staff.h"

UMyGameInstance::UMyGameInstance()  // 생성자 정의
{
	SchoolName = TEXT("기본 학교");  // 학교 이름 초기화
}

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("===================================="))
	TArray<UPerson*> Persons = {NewObject<UStudent>(),
		NewObject<UTeacher>(),
		NewObject<UStaff>()
	};

	for (const auto Person : Persons)
	{
		UE_LOG(LogTemp, Log, TEXT("구성원 이름: %s"), *Person->GetName());
	}

	UE_LOG(LogTemp, Log, TEXT("===================================="))

	for (const auto Person : Persons)
	{
		ILessonInterface* LessonInterface = Cast<ILessonInterface>(Person);
		if (LessonInterface)
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 있습니다."), *Person->GetName());
			LessonInterface->DoLesson();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 없습니다."), *Person->GetName());
		}
	}

	UE_LOG(LogTemp, Log, TEXT("===================================="))
}
 