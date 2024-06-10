// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DSCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DSCharacterControlData.h"
#include "Item/DSItemWeaponData.h"
#include "Bullet/DSBullet.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Engine/DamageEvents.h"

ADSCharacterPlayer::ADSCharacterPlayer()
{
	// 메시
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/IsaacClarke/IsaacClarke.IsaacClarke'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	/*static ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnimInstanceRef(TEXT("/Game/Blueprints/ABP_IsaacClarke.ABP_IsaacClarke_C"));
	if (CharacterAnimInstanceRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(CharacterAnimInstanceRef.Class);
	}*/	

	// 애니메이션
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ShotActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animations/IsaacClarke/AM_Shot.AM_Shot'"));
	if (ShotActionMontageRef.Object)
	{
		ShotActionMontage = ShotActionMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ReloadActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animations/IsaacClarke/AM_Reload.AM_Reload'"));
	if (ReloadActionMontageRef.Object)
	{
		ReloadActionMontage = ReloadActionMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> StasisActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animations/IsaacClarke/AM_Stasis.AM_Stasis'"));
	if (StasisActionMontageRef.Object)
	{
		StasisActionMontage = StasisActionMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> StompActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animations/IsaacClarke/AM_Stomp.AM_Stomp'"));
	if (StompActionMontageRef.Object)
	{
		StompActionMontage = StompActionMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> HitReactionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animations/IsaacClarke/HitAnimMontage.HitAnimMontage'"));
	if(HitReactionMontageRef.Object)
	{
		HitReactionMontage = HitReactionMontageRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadctionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animations/IsaacClarke/AM_Death.AM_Death'"));
	if (DeadctionMontageRef.Object)
	{
		DeadActionMontage = DeadctionMontageRef.Object;
	}

	// 카메라
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	// 입력
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Default.IMC_Default'"));
	if (InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Move.IA_Move'"));
	if (InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Look.IA_Look'"));
	if (InputActionLookRef.Object)
	{
		LookAction = InputActionLookRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionZoomRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Zoom.IA_Zoom'"));
	if (InputActionZoomRef.Object)
	{
		ZoomAction = InputActionZoomRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionWheelRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Wheel.IA_Wheel'"));
	if (InputActionWheelRef.Object)
	{
		WheelAction = InputActionWheelRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionShotRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Shot.IA_Shot'"));
	if (InputActionShotRef.Object)
	{
		ShotAction = InputActionShotRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionReloadRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Reload.IA_Reload'"));
	if (InputActionReloadRef.Object)
	{
		ReloadAction = InputActionReloadRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionStasisRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Stasis.IA_Stasis'"));
	if (InputActionStasisRef.Object)
	{
		StasisAction = InputActionStasisRef.Object;
	}
		
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionStompRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Stomp.IA_Stomp'"));
	if (InputActionStompRef.Object)
	{
		StompAction = InputActionStompRef.Object;
	}

	CurrentCharacterControlType = ECharacterControlType::Default;

	// 무기
	/*Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("RightHandSocket"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Item/Weapon/PlasmaCutter/PlasmaCutter.PlasmaCutter'"));
	if (WeaponMeshRef.Object)
	{
		Weapon->SetSkeletalMesh(WeaponMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> WeaponAnimInstanceRef(TEXT("/Game/Blueprints/ABP_PlasmaCutter.ABP_PlasmaCutter_C"));
	if (WeaponAnimInstanceRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(WeaponAnimInstanceRef.Class);
	}*/

	// 아이템
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &ADSCharacterPlayer::EquipWeapon)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &ADSCharacterPlayer::DrinkPotion)));
}

void ADSCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		EnableInput(PlayerController);
	}

	SetCharacterControl(CurrentCharacterControlType);
}

void ADSCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADSCharacterPlayer::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADSCharacterPlayer::Look);
	EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ADSCharacterPlayer::Zoom);
	EnhancedInputComponent->BindAction(WheelAction, ETriggerEvent::Triggered, this, &ADSCharacterPlayer::Wheel);
	EnhancedInputComponent->BindAction(ShotAction, ETriggerEvent::Triggered, this, &ADSCharacterPlayer::Shot);
	EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &ADSCharacterPlayer::Reload);
	EnhancedInputComponent->BindAction(StompAction, ETriggerEvent::Triggered, this, &ADSCharacterPlayer::Stomp);
	EnhancedInputComponent->BindAction(StasisAction, ETriggerEvent::Triggered, this, &ADSCharacterPlayer::Stasis);
}

void ADSCharacterPlayer::SetCharacterControlData(const UDSCharacterControlData* CharacterControlData)
{
	Super::SetCharacterControlData(CharacterControlData);

	//SpringArm->TargetArmLength = CharacterControlData->TargetArmLength;
	SpringArm->SetRelativeRotation(CharacterControlData->RelativeRotation);
	SpringArm->bUsePawnControlRotation = CharacterControlData->bUsePawnControlRotation;
	SpringArm->bInheritPitch = CharacterControlData->bInheritPitch;
	SpringArm->bInheritYaw = CharacterControlData->bInheritYaw;
	SpringArm->bInheritRoll = CharacterControlData->bInheritRoll;
	SpringArm->bDoCollisionTest = CharacterControlData->bDoCollisionTest;
}

void ADSCharacterPlayer::SetCharacterControl(ECharacterControlType NewCharacterControlType)
{
	UDSCharacterControlData* NewCharacterControl = CharacterControlManager[NewCharacterControlType];
	check(NewCharacterControl);

	SetCharacterControlData(NewCharacterControl);

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();

		UInputMappingContext* NewMappingContext = NewCharacterControl->InputMappingContext;
		if (NewMappingContext)
		{
			Subsystem->AddMappingContext(NewMappingContext, 0);
		}
	}

	CurrentCharacterControlType = NewCharacterControlType;
}

void ADSCharacterPlayer::SetCharacterControlType(ECharacterControlType NewCharacterControlType)
{
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ADSCharacterPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void ADSCharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void ADSCharacterPlayer::Zoom()
{
	if (bPressedReload)
	{
		return;
	}

	if (bPressedStomp)
	{
		return;
	}

	if (!bPressedZoom)
	{
		UE_LOG(LogDSCharacter, Log, TEXT("Zoom Start"));
		bPressedZoom = true;
	}
	else
	{
		UE_LOG(LogDSCharacter, Log, TEXT("Zoom End"));
		bPressedZoom = false;
	}
}

void ADSCharacterPlayer::Wheel()
{
	if (bPressedShot)
	{
		return;
	}

	if (bPressedReload)
	{
		return;
	}

	if (bPressedStomp)
	{
		return;
	}

	if (!bPressedWheel)
	{
		UE_LOG(LogDSCharacter, Log, TEXT("Wheel Start"));
		bPressedWheel = true;
	}
	else
	{
		UE_LOG(LogDSCharacter, Log, TEXT("Wheel End"));
		bPressedWheel = false;
	}
}

void ADSCharacterPlayer::Shot()
{
	if (bPressedStomp)
	{
		return;
	}

	if (bPressedReload)
	{
		return;
	}

	if (!bPressedZoom)
	{
		return;
	}

	if (!bPressedShot)
	{
		UE_LOG(LogDSCharacter, Log, TEXT("Shot Start"));
		bPressedShot = true;
		bAttack = false;
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->Montage_Play(ShotActionMontage);

		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &ADSCharacterPlayer::ShotActionEnd);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, ShotActionMontage);
	}
}

void ADSCharacterPlayer::ShotActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	UE_LOG(LogDSCharacter, Log, TEXT("Shot End"));
	bPressedShot = false;
}

void ADSCharacterPlayer:: OverReload()
{
	UE_LOG(LogDSCharacter, Log, TEXT("Reload Start"));
	bPressedReload = true;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(ReloadActionMontage);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ADSCharacterPlayer::ReloadActionEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ReloadActionMontage);
}

void ADSCharacterPlayer::Reload()
{
	if (bPressedStomp)
	{
		return;
	}

	if (bPressedShot)
	{
		return;
	}

	if (!bPressedReload)
	{
		UE_LOG(LogDSCharacter, Log, TEXT("Reload Start"));
		bPressedReload = true;
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->StopAllMontages(0.0f);
		AnimInstance->Montage_Play(ReloadActionMontage);

		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &ADSCharacterPlayer::ReloadActionEnd);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, ReloadActionMontage);
	}
}

void ADSCharacterPlayer::ReloadActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	UE_LOG(LogDSCharacter, Log, TEXT("Reload End"));
	bPressedReload = false;
}

void ADSCharacterPlayer::Stasis()
{
	if (bPressedReload)
	{
		return;
	}

	if (bPressedStomp)
	{
		return;
	}

	if (!bPressedStasis)
	{
		UE_LOG(LogDSCharacter, Log, TEXT("Stasis Start"));
		bPressedStasis = true;
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->Montage_Play(StasisActionMontage);

		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &ADSCharacterPlayer::StasisActionEnd);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, StasisActionMontage);
	}
}

void ADSCharacterPlayer::StasisActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	UE_LOG(LogDSCharacter, Log, TEXT("Stasis End"));
	bPressedStasis = false;
}

void ADSCharacterPlayer::Stomp()
{
	if (bPressedShot)
	{
		return;
	}

	if (bPressedReload)
	{
		return;
	}

	if (bPressedStasis)
	{
		return;
	}

	if (!bPressedStomp)
	{
		UE_LOG(LogDSCharacter, Log, TEXT("Stomp Start"));
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		bPressedStomp = true;
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->Montage_Play(StompActionMontage);

		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &ADSCharacterPlayer::StompActionEnd);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, StompActionMontage);
	}
}

void ADSCharacterPlayer::StompActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	UE_LOG(LogDSCharacter, Log, TEXT("Stomp End"));
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	bPressedStomp = false;
}

float ADSCharacterPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if(CurrentHP > 0)
	{
		UE_LOG(LogDSCharacter, Log, TEXT("TakeDamage"));
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->Montage_Play(HitReactionMontage);
	}
	return DamageAmount;
}

void ADSCharacterPlayer::TakeItem(UDSItemData* InItemData)
{
	if (InItemData)
	{
		TakeItemActions[(uint8)InItemData->ItemType].ItemDelegate.ExecuteIfBound(InItemData);
	}
}

void ADSCharacterPlayer::DrinkPotion(UDSItemData* InItemData)
{
	UE_LOG(LogDSCharacter, Log, TEXT("Drink Potion"));
}

void ADSCharacterPlayer::EquipWeapon(UDSItemData* InItemData)
{
	UE_LOG(LogDSCharacter, Log, TEXT("Equip Weapon"));

	UDSItemWeaponData* ItemWeaponData = Cast<UDSItemWeaponData>(InItemData);
	if (InItemData)
	{
		if (ItemWeaponData->WeaponMesh.IsPending())
		{
			ItemWeaponData->WeaponMesh.LoadSynchronous();
		}

		bEquippedWeapon = true;
	}
}

void ADSCharacterPlayer::Dead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(DeadActionMontage);

	SetActorEnableCollision(false);
}

void ADSCharacterPlayer::Finish()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	//AnimInstance->Montage_Play(EndingActionMontage);
}
