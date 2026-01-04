// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "StudentManager.h"

void CheckUObjectIsValid(const UObject* InObject, const FString& InTag) // 유효한 오브젝트인지 확인하는 함수
{
	if (InObject->IsValidLowLevel()) // ::IsValid함수도 있지만 지금은 더 깊숙히 작동하는걸 보기위해 IsValidLowLevel을 사용
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효한 언리얼 오브젝트"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효하지 않은 언리얼 오브젝트"), *InTag);
	}
}

void CheckUObjectIsNull(const UObject* InObject, const FString& InTag) // 널 포인터인지 체크하는 함수
{
	if (nullptr == InObject)
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 널 포인터 언리얼 오브젝트"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 널 포인터가 아닌 언리얼 오브젝트"), *InTag);
	}
}

void UMyGameInstance::Init()
{
	Super::Init();

	NonPropStudent = NewObject<UStudent>();
	PropStudent = NewObject<UStudent>();

	NonPropStudents.Add(NewObject<UStudent>());
	PropStudents.Add(NewObject<UStudent>());

	StudentManager = new FStudentManager(NewObject<UStudent>());
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();

	const UStudent* StudentInManager = StudentManager->GetStudent();

	delete StudentManager; // delete StudentManager
	StudentManager = nullptr; // nullptr로 초기화

	// StudentInManager check
	CheckUObjectIsNull(StudentInManager, TEXT("StudentInManager"));
	CheckUObjectIsValid(StudentInManager, TEXT("StudentInManager"));

	// NonPropStudent check
	CheckUObjectIsNull(NonPropStudent, TEXT("NonPropStudent"));
	CheckUObjectIsValid(NonPropStudent, TEXT("NonPropStudent"));

	// PropStudent check
	CheckUObjectIsNull(PropStudent, TEXT("PropStudent"));
	CheckUObjectIsValid(PropStudent, TEXT("PropStudent"));

	// NonPropStudents check
	CheckUObjectIsNull(NonPropStudents[0], TEXT("NonPropStudents"));
	CheckUObjectIsValid(NonPropStudents[0], TEXT("NonPropStudents"));

	// PropStudents check
	CheckUObjectIsNull(PropStudents[0], TEXT("PropStudents"));
	CheckUObjectIsValid(PropStudents[0], TEXT("PropStudents"));

}
