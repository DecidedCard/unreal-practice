// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "JsonObjectConverter.h"

void PrintStudentInfo(const UStudent* InStudent, const FString& InTag)
{
	UE_LOG(LogTemp, Log, TEXT("[%s] 이름 %s 순번 %d"), *InTag, *InStudent->GetName(), InStudent->GetOrder());
}

UMyGameInstance::UMyGameInstance()
{
}

void UMyGameInstance::Init()
{
	Super::Init();

	FStudentData RawDataSrc(16, TEXT("테스트"));

	const FString SavedDir = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved")); // 저장할 파일 디렉토리, ProjectDir은 현재 프로젝트 폴더 위치
	UE_LOG(LogTemp, Log, TEXT("파일 저장 디렉토리: %s"), *SavedDir);

	{
		const FString RawDataFileName(TEXT("RawData.bin"));
		FString RawDataAbsolutePath = FPaths::Combine(SavedDir, *RawDataFileName);
		UE_LOG(LogTemp, Log, TEXT("저장할 파일 전체 경로: %s"), *RawDataAbsolutePath);
		FPaths::MakeStandardFilename(RawDataAbsolutePath);
		UE_LOG(LogTemp, Log, TEXT("변경할 파일 전체 경로: %s"), *RawDataAbsolutePath);

		FArchive* RawFileWriterAr = IFileManager::Get().CreateFileWriter(*RawDataAbsolutePath); // FArchive를 상속받은 RawFileWriterAr 생성
		if (nullptr != RawFileWriterAr)
		{
			*RawFileWriterAr << RawDataSrc;
			RawFileWriterAr->Close();
			delete RawFileWriterAr;
			RawFileWriterAr = nullptr;
		}

		FStudentData RawDataDest;
		FArchive* RawFileReaderAr = IFileManager::Get().CreateFileReader(*RawDataAbsolutePath);
		if (nullptr != RawFileReaderAr)
		{
			*RawFileReaderAr << RawDataDest;
			RawFileReaderAr->Close();
			delete RawFileReaderAr;
			RawFileReaderAr = nullptr;

			UE_LOG(LogTemp, Log, TEXT("[RawData] 이름 %s 순번 %d"), *RawDataDest.Name, RawDataDest.Order);
		}
	}

	StudentSrc = NewObject<UStudent>();
	StudentSrc->SetName(TEXT("정해준"));
	StudentSrc->SetOrder(59);

	{
		const FString ObjectDataFileName(TEXT("ObjectData.bin")); // 저장할 파일 이름
		FString ObjectDataAbsolutePath = FPaths::Combine(*SavedDir, *ObjectDataFileName); // 저장할 파일 경로
		FPaths::MakeStandardFilename(ObjectDataAbsolutePath); // 파일을 ../을 없애고 드라이브부터 표시되게 변경

		TArray<uint8> BufferArray;
		FMemoryWriter MemoryWriterAr(BufferArray);
		StudentSrc->Serialize(MemoryWriterAr);

		if (TUniquePtr<FArchive> FIleWriterAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*ObjectDataAbsolutePath)))
		{
			*FIleWriterAr << BufferArray;
			FIleWriterAr->Close(); // close후 언리얼 오브젝트라 delete및 nullptr로 바꿀 필요 없음
		}

		TArray<uint8> BufferArrayFromFile;
		if (TUniquePtr<FArchive> FIleReaderAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*ObjectDataAbsolutePath)))
		{
			*FIleReaderAr << BufferArrayFromFile;
			FIleReaderAr->Close();
		}

		FMemoryReader MemoryReaderAr(BufferArrayFromFile);
		UStudent* StudentDest = NewObject<UStudent>();
		StudentDest->Serialize(MemoryReaderAr);
		PrintStudentInfo(StudentDest, TEXT("ObjectData"));
	}

	{
		const FString JsonDataFileName(TEXT("StudentJsonData.txt"));
		FString JsonDataAbsolutePath = FPaths::Combine(*SavedDir, *JsonDataFileName);
		FPaths::MakeStandardFilename(JsonDataAbsolutePath);

		TSharedRef<FJsonObject> JsonObjectSrc = MakeShared<FJsonObject>();
		FJsonObjectConverter::UStructToJsonObject(StudentSrc->GetClass(), StudentSrc, JsonObjectSrc);

		FString JsonOutString;
		TSharedRef<TJsonWriter<TCHAR>> JsonWriterAr = TJsonWriterFactory<TCHAR>::Create(&JsonOutString);
		if (FJsonSerializer::Serialize(JsonObjectSrc, JsonWriterAr))
		{
			FFileHelper::SaveStringToFile(JsonOutString, *JsonDataAbsolutePath);
		}

		FString JsonInString;
		FFileHelper::LoadFileToString(JsonInString, *JsonDataAbsolutePath);

		TSharedRef<TJsonReader<TCHAR>> JsonReaderAr = TJsonReaderFactory<TCHAR>::Create(JsonInString);

		TSharedPtr<FJsonObject> JsonObjectDest;
		if (FJsonSerializer::Deserialize(JsonReaderAr, JsonObjectDest))
		{
			UStudent* JsonStudentDest = NewObject<UStudent>();
			if (FJsonObjectConverter::JsonObjectToUStruct(JsonObjectDest.ToSharedRef(), JsonStudentDest->GetClass(), JsonStudentDest))
			{
				PrintStudentInfo(JsonStudentDest, TEXT("JsonData"));
			}
		}
	}
}
