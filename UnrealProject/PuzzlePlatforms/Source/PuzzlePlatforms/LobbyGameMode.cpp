// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"

#include "Public/TimerManager.h"

#include "PuzzlePlatformsGameInstance.h"



void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	++NumberOfPlayers;
	if (NumberOfPlayers >= 2)
	{
		GetWorldTimerManager().SetTimer(GetStartTimer, this, &ALobbyGameMode::StartGame, 30);
		
	}
}

void ALobbyGameMode::Logout(APlayerController* Exiting)
{
	Super::Logout(Exiting);
	--NumberOfPlayers;
}

void ALobbyGameMode::StartGame()
{
	auto GameInstance = Cast <UPuzzlePlatformsGameInstance>(GetGameInstance());

	if (GameInstance == nullptr) return;

	GameInstance->StartSession();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	bUseSeamlessTravel = true;

	World->ServerTravel("/Game/PuzzlePlatforms/Maps/Game?listen");
}