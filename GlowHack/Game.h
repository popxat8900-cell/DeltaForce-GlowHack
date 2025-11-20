#pragma once

namespace GameData {

	UWorld* GWorld = nullptr;
	UObject* Engine;
	UBlueprintFunctionLibrary* BlueprintFunctionLibrary[10] = { nullptr };
	AGPCharacter* MyCharacter = nullptr;

	bool bIsInGame = false;
	bool bIsCampMode = false;
	uint32_t TeamIndex = NULL;
}

