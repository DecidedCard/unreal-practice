// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Algo/Accumulate.h"

void UMyGameInstance::Init()
{
	Super::Init();

	const int32 ArrayNum = 10;
	TArray<int32> Int32Array;

	for (int32 ix = 1; ix <= ArrayNum; ++ix)
	{
		Int32Array.Add(ix); // Adds numbers 1 to 10
	}

	Int32Array.RemoveAll(
		[](int32 Val)
		{
			return Val % 2 == 0;
		}
	); // Removes all even numbers

	Int32Array += {2, 4, 6, 8, 10}; // Adds even numbers back

	TArray<int32> Int32ArrayCompare;
	int32 CArray[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
	Int32ArrayCompare.AddUninitialized(ArrayNum);
	FMemory::Memcpy(Int32ArrayCompare.GetData(), CArray, sizeof(int32) * ArrayNum);

	ensure(Int32Array == Int32ArrayCompare);

	int32 Sum = 0;
	for (const int32& Int32Elem : Int32Array)
	{
		Sum += Int32Elem;
	}

	ensure(Sum == 55);

	int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);
	ensure(SumByAlgo == Sum);

	TSet<int32> Int32Set;
	for (int32 ix = 1; ix <= ArrayNum; ++ix)
	{
		Int32Set.Add(ix); // Adds numbers 1 to 10
	}

	Int32Set.Remove(2); // Removes number 2
	Int32Set.Remove(4); // Removes number 4
	Int32Set.Remove(6); // Removes number 6
	Int32Set.Remove(8); // Removes number 8
	Int32Set.Remove(10); // Removes number 10

	Int32Set.Add(2); // Adds number 2 back
	Int32Set.Add(4); // Adds number 4 back
	Int32Set.Add(6); // Adds number 6 back
	Int32Set.Add(8); // Adds number 8 back
	Int32Set.Add(10); // Adds number 10 back
}
