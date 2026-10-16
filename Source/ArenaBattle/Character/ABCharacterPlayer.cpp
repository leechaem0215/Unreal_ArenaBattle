// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterPlayer.h"
#include <EnhancedInputComponent.h>

#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Camera/CameraComponent.h>

#include <InputMappingContext.h>
#include <InputAction.h>

#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

AABCharacterPlayer::AABCharacterPlayer()
{
}

void AABCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	// 사용할 입력 매핑 컨텍스트 설정.
	// 플레이어 컨트롤러 가져오기.
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (IsValid(PlayerController))
	{
		// 향상된 입력 서브 시스템 가져오기.
		UEnhancedInputLocalPlayerSubsystem* InputSystem
			= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
				PlayerController->GetLocalPlayer()
			);

		if (InputSystem)
		{
			InputSystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AABCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 바인딩 - 입력 액션을 통해서 입력이 전달될 때 실행함 함수 연동.
	// 향상된 입력 컴포넌트로 변환.
	UEnhancedInputComponent* EnhancedInputComponent
		= Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(
			MoveAction,
			ETriggerEvent::Triggered,
			this,
			&AABCharacterPlayer::Move
		);

		EnhancedInputComponent->BindAction(
			LookAction,
			ETriggerEvent::Triggered,
			this,
			&AABCharacterPlayer::Look
		);

		EnhancedInputComponent->BindAction(
			JumpAction,
			ETriggerEvent::Started,
			this,
			&ACharacter::Jump
		);

		EnhancedInputComponent->BindAction(
			JumpAction,
			ETriggerEvent::Completed,
			this,
			&ACharacter::StopJumping
		);
	}
}

void AABCharacterPlayer::Move(const FInputActionValue& Value)
{
}

void AABCharacterPlayer::Look(const FInputActionValue& Value)
{
}
