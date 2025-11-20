#pragma once
class C_Entity
{
public:

	static bool GetIsCamp(EDFMGamePlayMode DFMGamePlayerMode) {
		bool bIsCamp = false;
		switch (DFMGamePlayerMode)
		{
		case EDFMGamePlayMode::None:
			break;
		case EDFMGamePlayMode::GamePlayMode_SOL:
			bIsCamp = false;
			break;
		case EDFMGamePlayMode::GamePlayMode_Raid:
			break;
		case EDFMGamePlayMode::GamePlayMode_IrisDiscovery:
			break;
		case EDFMGamePlayMode::GamePlayMode_Conquest:
			bIsCamp = false;
			break;
		case EDFMGamePlayMode::GamePlayMode_Breakthrough:
			bIsCamp = true;
			break;
		case EDFMGamePlayMode::GamePlayMode_SafeHouse:
			break;
		case EDFMGamePlayMode::GamePlayMode_Intro:
			break;
		case EDFMGamePlayMode::EDFMGamePlayMode_MAX:
			break;
		default:
			break;
		}
		return bIsCamp;
	}

	static void UpData(){
		
		GameData::MyCharacter = GameData::BlueprintFunctionLibrary[(int)BlueprintType::GameplayBlueprintHelper]->GetLocalGPCharacter(GameData::GWorld);
		if (IsBadPtr(GameData::MyCharacter)) return;
	
		if (GameData::BlueprintFunctionLibrary[(int)BlueprintType::GameplayBlueprintHelper]->IsLocalPlayer(GameData::MyCharacter)) {
			
			auto HealthDataComponent = GameData::MyCharacter->GetHealthComp();
			if (IsBadPtr(HealthDataComponent)) return;
			if (HealthDataComponent->GetHealth() > 0 && !GameData::MyCharacter->IsDead()) {
		
				auto TeamComp = GameData::MyCharacter->GetTeamComp();
				if (IsBadPtr(TeamComp)) return;
				if (GameData::bIsCampMode)
					GameData::TeamIndex = TeamComp->GetCamp();
				else
					GameData::TeamIndex = TeamComp->GetTeamID();
			}
		}
	
		TArray<AActor*> ACharacters = {};
		GameData::BlueprintFunctionLibrary[(int)BlueprintType::GameplayStatics]->GetAllActorsOfClass(GameData::GWorld, ADFMCharacter::StaticClass(), &ACharacters);
		for (auto i = 0; i < ACharacters.Num(); i++){
			
			const auto& pCharacter = ACharacters[i]->As<ADFMCharacter*>();
			if (pCharacter == GameData::MyCharacter || !pCharacter->IsAlive()) continue;

			auto TeamComp = pCharacter->GetTeamComp();
			if (IsBadPtr(TeamComp)) continue;

			auto TeamIndex = GameData::bIsCampMode ? TeamComp->GetCamp() : TeamComp->GetTeamID();
			if (TeamIndex == GameData::TeamIndex) continue;

			auto DFMOutLineEffectComponent = Mem::Read<UGPOutLineEffectComponent*>(
				reinterpret_cast<uintptr_t>(pCharacter) + Offsets::DFMOutLineEffectComponent);
			if (IsBadPtr(DFMOutLineEffectComponent)) continue;
			
			auto desiredEffect = EOutLineEffectType::OutLineType_None;
			if (pCharacter->IsAI()) {
				// desiredEffect = EOutLineEffectType::OutLineType_DyingShowTeammateCanRescueSelf;
			}
			else {
				desiredEffect = EOutLineEffectType::OutLineType_ProxSensor;
			}

			auto currentEffect = Mem::Read<EOutLineEffectType>(
				reinterpret_cast<uintptr_t>(DFMOutLineEffectComponent) + 0x1D8);
			if (currentEffect != desiredEffect) {
				DFMOutLineEffectComponent->PlayOutLineEffect(desiredEffect);
			}
		}
		
		if (ACharacters.Data)
			Utils::FastCall(Offsets::FreeFunc, ACharacters.Data);
	}
};