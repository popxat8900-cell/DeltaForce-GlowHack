#pragma once

enum class BlueprintType : int32_t {
	GameplayStatics,
	KismetTextLibrary,
	KismetStringLibrary,
	GameplayBlueprintHelper,
	GPScalabilityBlueprintTools,
	KismetSystemLibrary,
	BlueprintFunctionLibrary,
	Max
};

enum class EDFMGamePlayMode : uint8_t  //Size 9
{
	None = 0,
	GamePlayMode_SOL = 1,
	GamePlayMode_Raid = 2,
	GamePlayMode_IrisDiscovery = 3,
	GamePlayMode_Conquest = 4,
	GamePlayMode_Breakthrough = 5,
	GamePlayMode_SafeHouse = 6,
	GamePlayMode_Intro = 7,
	EDFMGamePlayMode_MAX = 8
};

enum class EOutLineEffectType : int32_t {
	OutLineType_None = 0,
	OutLineType_ProxSensor = 1,
	OutLineType_ArrowMark = 2,
	OutLineType_MedicGun = 4,
	OutLineType_MedicGunHit = 8,
	OutLineType_SupportEffect = 16,
	OutLineType_DyingLockEnemy = 32,
	OutLineType_Breakthrough_Defender = 64,
	OutLineType_DyingShowTeammateCanRescueSelf = 128,
	OutLineType_DyingShowCampMedicCanRescueSelf = 256,
	OutLineType_Locking = 512,
	OutLineType_LockComplete = 1024,
	OutLineType_LockFire = 2048,
	OutLineType_OnlyMarker = 4096,
	OutLineType_SOL_OB_Teammate = 8192,
	OutLineType_SOL_OB_Enemy = 16384,
	OutLineType_SOL_OB_AI = 32768,
	OutLineType_SOL_OB_FreeCamera = 65536,
	OutLineType_Breakthrough_OB_Attacker = 131072,
	OutLineType_OBorReplay = 262144,
	OutLineType_MAX = 262145
};

enum class EMainFlowState : uint8_t {
	Default = 0,
	Lobby = 1,
	Loading = 2,
	SafeHouse = 3,
	InGame = 4,
	LobbyBHD = 5,
	EMainFlowState_MAX = 6
};
