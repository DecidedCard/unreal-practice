// Fill out your copyright notice in the Description page of Project Settings.


#include "Teacher.h"
#include "Card.h"

UTeacher::UTeacher()
{
	Name = TEXT("선생님");
	Card->SetCardType(ECardType::Teacher);

}

void UTeacher::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("%s 이(가) 수업을 가르치고 있습니다."), *Name);
}
