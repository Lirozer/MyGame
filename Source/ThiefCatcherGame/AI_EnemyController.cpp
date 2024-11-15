// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_EnemyController.h"
#include "NavigationSystem.h"

void AAI_EnemyController::BeginPlay()
{
	Super::BeginPlay();

	NavigationMesh = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

	RandomPatrol();
	RunAwayFromPlayer();
}

void AAI_EnemyController::RandomPatrol()
{
	GetWorld()->GetTimerManager().SetTimer(PointDelay, this, &AAI_EnemyController::RandomPatrol, 3.f, true, -1.f);

	if (NavigationMesh)
	{
		NavigationMesh->K2_GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(), RandomLocation, 1500.0f);

		MoveToLocation(RandomLocation);
	}
}

void AAI_EnemyController::RunAwayFromPlayer()
{
	GetWorld()->GetTimerManager().SetTimer(RunAway, this, &AAI_EnemyController::RunAwayFromPlayer, 1.f, true, -1.f);

	FVector PawnLocation = GetPawn()->GetActorLocation();
	AThiefCatcher* PlayerCharacter = Cast<AThiefCatcher>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	FVector ForwardVector = PlayerCharacter->GetActorForwardVector();
	FVector RightVector = PlayerCharacter->GetActorRightVector();

	FVector WhereToMove = PawnLocation + ForwardVector + 700.f + RightVector + 700.f;
	float Distance = GetPawn()->GetDistanceTo(PlayerCharacter);

	if (Distance < 700.f && NavigationMesh)
	{
		NavigationMesh->K2_GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(), WhereToMove, 1200.0f);
		ClearTimer();
	}
}

void AAI_EnemyController::ClearTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(PointDelay);
	RandomPatrol();
}
