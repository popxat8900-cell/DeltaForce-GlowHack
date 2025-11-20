#pragma once
class C_Hack
{
public:

	static void hkPostRender(void* GameViewport, UCanvas* Canvas)
	{
		// update game data
		auto MainFlowState = GameData::BlueprintFunctionLibrary[(int)BlueprintType::GPScalabilityBlueprintTools]->GetMainFlowState();
		GameData::bIsInGame = MainFlowState == EMainFlowState::InGame || MainFlowState == EMainFlowState::SafeHouse;
		if (!GameData::bIsInGame) return;

		auto GameViewportClient = Mem::Read<UGameViewportClient*>((uintptr_t)GameData::Engine + Offsets::GameViewport);
		if (IsBadPtr(GameViewportClient)) return;

		GameData::GWorld = Mem::Read<UWorld*>((uintptr_t)GameViewportClient + Offsets::World);
		if (IsBadPtr(GameData::GWorld)) return;

		auto GameState = GameData::BlueprintFunctionLibrary[(int)BlueprintType::GameplayBlueprintHelper]->GetGPGameState(GameData::GWorld);
		if (IsBadPtr(GameState)) return;
		auto DFMGamePlayerMode = Mem::Read<EDFMGamePlayMode>(GameState + Offsets::DFMGamePlayerMode);

		GameData::bIsCampMode = C_Entity::GetIsCamp(DFMGamePlayerMode);

		C_Entity::UpData(); // entity update
		// C_Items::UpData(Canvas);  // items update

		return Utils::FastCall<void>(RenderHook.GetOriginal<void*>(95), GameViewport, Canvas);
	}

	static int FindOffset(const wchar_t* Class, const char* varName) {

		auto CurrentObject = (UStruct*)UObject::FindObject(Class);
		if (IsBadPtr(CurrentObject)) return NULL;

		for (auto Property = CurrentObject->ChildProperties; !IsBadPtr(Property); Property = Property->Next) {

			auto Offset = Property->Offset;
			if (Offset > 0 && Offset < 0xFFFF) {
				if (strcmp(Property->Name.GetName().c_str(), varName) == 0) {
					return Offset;
				}
			}
		}
		return NULL;
	}
	
	static void InitOffsets() {

		Offsets::StaticFindObject = 0x14B2145A0;
		Offsets::GetName = 0x14AEB4AD0;
		Offsets::FreeFunc = 0x14AD7B320;
		Offsets::GEngine = 0x154164CD8;

		Offsets::GameViewport = FindOffset((L"Engine.Engine"), xorstr("GameViewport"));

		Offsets::World = FindOffset((L"Engine.GameViewportClient"), xorstr("World"));

		// Offsets::Levels = FindOffset((L"Engine.World"), xorstr("Levels"));

		Offsets::GameState = FindOffset((L"Engine.World"), xorstr("GameState"));

		Offsets::DFMGamePlayerMode = FindOffset((L"DFMGameplay.DFMGameState"), xorstr("DFMGamePlayerMode"));

		// Offsets::PlayerController = FindOffset((L"Engine.Player"), xorstr("PlayerController"));

		// Offsets::PlayerCameraManager = FindOffset((L"Engine.PlayerController"), xorstr("PlayerCameraManager"));

		Offsets::PlayerState = FindOffset((L"Engine.Pawn"), xorstr("PlayerState"));

		// Offsets::PlayerNamePrivate = FindOffset((L"Engine.PlayerState"), xorstr("PlayerNamePrivate"));

		// Offsets::RootComponent = FindOffset((L"Engine.Actor"), xorstr("RootComponent"));
		
		Offsets::DFMOutLineEffectComponent = FindOffset((L"DFMGameplay.DFMCharacter"), xorstr("DFMOutLineEffectComponent"));

		GameData::BlueprintFunctionLibrary[(int)BlueprintType::GameplayStatics] = (UBlueprintFunctionLibrary*)UObject::FindObject((L"Engine.GameplayStatics"));

		GameData::BlueprintFunctionLibrary[(int)BlueprintType::KismetTextLibrary] = (UBlueprintFunctionLibrary*)UObject::FindObject((L"Engine.KismetTextLibrary"));

		GameData::BlueprintFunctionLibrary[(int)BlueprintType::KismetStringLibrary] = (UBlueprintFunctionLibrary*)UObject::FindObject((L"Engine.KismetStringLibrary"));

		GameData::BlueprintFunctionLibrary[(int)BlueprintType::GameplayBlueprintHelper] = (UBlueprintFunctionLibrary*)UObject::FindObject((L"GPGameplay.GameplayBlueprintHelper"));

		GameData::BlueprintFunctionLibrary[(int)BlueprintType::GPScalabilityBlueprintTools] = (UBlueprintFunctionLibrary*)UObject::FindObject((L"GPSettings.GPScalabilityBlueprintTools"));

		GameData::BlueprintFunctionLibrary[(int)BlueprintType::KismetSystemLibrary] = (UBlueprintFunctionLibrary*)UObject::FindObject((L"Engine.KismetSystemLibrary"));

		GameData::BlueprintFunctionLibrary[(int)BlueprintType::BlueprintFunctionLibrary] = (UBlueprintFunctionLibrary*)UObject::FindObject((L"Engine.BlueprintFunctionLibrary"));

		GameData::Engine = Mem::Read<UObject*>(Offsets::GEngine);
	}
	
	static void InitHooks() {

		if (!IsBadPtr(GameData::Engine)) {
			auto GameViewportClient = *(UGameViewportClient**)((uintptr_t)GameData::Engine + Offsets::GameViewport);
			if (!IsBadPtr(GameViewportClient)) {

				RenderHook.Initialize(GameViewportClient);
				RenderHook.Bind(95, hkPostRender);
			}
		}
	}

	static void Init(HMODULE hModule) {
		while (!(GetAsyncKeyState(VK_HOME) & 0x8000)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		Beep(800, 500);

		InitOffsets();
		InitHooks();
	}
};

