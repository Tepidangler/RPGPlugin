// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameInstance.h"

URPGGameInstance::URPGGameInstance()
{
	Party = NewObject<UPartySystem>();
}

void URPGGameInstance::Init()
{
	Super::Init();

}