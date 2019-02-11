// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "EndMenu.h"

void UEndMenu::Retry()
{
	UGameplayStatics::OpenLevel(GetWorld(), "scene");
}

void UEndMenu::Quit()
{
	FGenericPlatformMisc::RequestExit(false);
}