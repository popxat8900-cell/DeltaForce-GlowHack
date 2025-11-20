
template<class T>
struct TArray
{

public:
	T* Data;

	int32_t Count;
	int32_t Max;

	TArray()
	{
		Data = nullptr;
		Max = 0;
		Count = 0;
	}

	int Num() const
	{
		return Count;
	}

	T& operator[](int i)
	{
		return Data[i];
	}

	const T& operator[](int i) const
	{
		return Data[i];
	}

	bool IsValidIndex(int i) const
	{
		return i < Num();
	}

	void Free()
	{
		delete[] Data;
		Count = 0;
		Max = 0;
		Data = nullptr;
	}

	void Add(const T& Element)
	{
		if (GetSlack() <= 3) Reserve(3);

		Data[Count] = Element;
		Count++;
	}

	int32_t GetSlack() const { return Max - Count; }

	void Reserve(int32_t Count)
	{
		Max += Count;
		T* NewData = new T[Max];

		if (Data)
		{
			std::copy(Data, Data + Count, NewData);
			delete[] Data;
		}

		Data = NewData;
	}
};

struct FString
{
	wchar_t* Data;
	uint32_t Count;
	uint32_t Max;
	FString() {
		RtlZeroMemory(this, sizeof FString);
	};


	FString(wchar_t* X, uint32_t Y, uint32_t Max) : Data(X), Count(Y), Max(Max) {};

	FString(const wchar_t* other) { Max = Count = *other ? static_cast<uint32_t>(wcslen(other)) + 1 : 0; if (Count) Data = const_cast<wchar_t*>(other); }

};
class FTextData
{
public:
	char pad[0x28];
	struct FString DisplayString;
};
class FText
{
public:
	FTextData* TextData;
	char Pad_8[0x10];
};
struct FVector
{
public:
	float                                              X;                                                         // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                              Y;                                                         // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                              Z;                                                         // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)

	FVector() : X(0), Y(0), Z(0) {}

	FVector(float x, float y, float z) : X(x), Y(y), Z(z) {}

	FVector operator + (const FVector& other) const { return FVector(X + other.X, Y + other.Y, Z + other.Z); }

	FVector operator - (const FVector& other) const { return FVector(X - other.X, Y - other.Y, Z - other.Z); }

	FVector operator * (float scalar) const { return FVector(X * scalar, Y * scalar, Z * scalar); }

	FVector operator * (const FVector& other) const { return FVector(X * other.X, Y * other.Y, Z * other.Z); }

	FVector operator / (float scalar) const { return FVector(X / scalar, Y / scalar, Z / scalar); }
	FVector operator^(const FVector& V) const { return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X); }

	FVector operator / (const FVector& other) const { return FVector(X / other.X, Y / other.Y, Z / other.Z); }

	FVector& operator=  (const FVector& other) { X = other.X; Y = other.Y; Z = other.Z; return *this; }

	FVector& operator+= (const FVector& other) { X += other.X; Y += other.Y; Z += other.Z; return *this; }

	FVector& operator-= (const FVector& other) { X -= other.X; Y -= other.Y; Z -= other.Z; return *this; }

	FVector& operator*= (const float other) { X *= other; Y *= other; Z *= other; return *this; }

	float Dot(const FVector& b) const { return (X * b.X) + (Y * b.Y) + (Z * b.Z); }

	float Distance(FVector v) { return float(sqrt(pow(v.X - X, 2.0) + pow(v.Y - Y, 2.0) + pow(v.Z - Z, 2.0))); }
	float MagnitudeSqr() const { return Dot(*this); }

	float Magnitude() const { return sqrt(MagnitudeSqr()); }

	FVector Unit() const
	{
		const float fMagnitude = Magnitude();
		return FVector(X / fMagnitude, Y / fMagnitude, Z / fMagnitude);
	}

	friend bool operator==(const FVector& first, const FVector& second) { return first.X == second.X && first.Y == second.Y && first.Z == second.Z; }

	friend bool operator!=(const FVector& first, const FVector& second) { return !(first == second); }
};

struct FVector2D
{
public:

	float                                              X;                                                         // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                              Y;                                                         // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)

	FVector2D() : X(0), Y(0) {}

	FVector2D(float x, float y) : X(x), Y(y) {}
	bool Zero() const
	{
		return (X > -0.1f && X < 0.1f && Y > -0.1f && Y < 0.1f);
	}
	float ScreenDis(float GameX, float GameY) {
		FVector2D Vec;
		Vec.X = GameX - X;
		Vec.Y = GameY - Y;
		float dis = sqrt(Vec.X * Vec.X + Vec.Y * Vec.Y);
		return dis;
	}
	FVector2D operator + (const FVector2D& other) const { return FVector2D(X + other.X, Y + other.Y); }

	FVector2D operator - (const FVector2D& other) const { return FVector2D(X - other.X, Y - other.Y); }

	FVector2D operator * (float scalar) const { return FVector2D(X * scalar, Y * scalar); }

	FVector2D operator * (const FVector2D& other) const { return FVector2D(X * other.X, Y * other.Y); }

	FVector2D operator / (float scalar) const { return FVector2D(X / scalar, Y / scalar); }

	FVector2D operator / (const FVector2D& other) const { return FVector2D(X / other.X, Y / other.Y); }

	FVector2D& operator=  (const FVector2D& other) { X = other.X; Y = other.Y; return *this; }

	FVector2D& operator+= (const FVector2D& other) { X += other.X; Y += other.Y; return *this; }

	FVector2D& operator-= (const FVector2D& other) { X -= other.X; Y -= other.Y; return *this; }

	FVector2D& operator*= (const float other) { X *= other; Y *= other; return *this; }
};

struct FLinearColor
{
	float r;
	float g;
	float b;
	float a;

	FLinearColor() {
		RtlZeroMemory(this, sizeof FLinearColor);
	}

	FLinearColor(float R, float G, float B, float A = 255.f)
	{
		r = R;
		g = G;
		b = B;
		a = A;
	}
};



struct FName {
	int32_t Index;
	int32_t Number;

	std::string GetName()
	{
		wchar_t Unicode[1024];
		auto _Len = Utils::FastCall<int>(Offsets::GetName, this, Unicode);
		std::string name = Utils::WCHAR2String(Unicode);
		auto pos = name.rfind('/');
		if (pos != std::string::npos)
		{
			name = name.substr(pos + 1);
		}
		return name;
	}
	std::wstring GetNameW()
	{
		wchar_t Unicode[1024];
		auto _Len = Utils::FastCall<int>(Offsets::GetName, this, Unicode);
		auto Name = std::wstring(Unicode);
		auto pos = Name.rfind('/');
		if (pos != std::wstring::npos)
		{
			Name = Name.substr(pos + 1);
		}
		return Name;
	}

	static std::string GetName(int id) {
		wchar_t Unicode[1024];
		FName NameID = { id ,0 };
		auto _Len = Utils::FastCall<int>(Offsets::GetName, &NameID, Unicode);
		if (_Len <= 0 || _Len > 1024) {
			return "";
		}
		std::string name = Utils::WCHAR2String(Unicode);
		auto pos = name.rfind('/');
		if (pos != std::string::npos)
		{
			name = name.substr(pos + 1);
		}
		return name;
	}
};

class UField
{
public:
	uint8_t                                        Pad_00[0x18];
	class UField* Next;
	uint8_t                                        Pad_20[0x08];
	FName										   Name;
	uint8_t                                        Pad_30[0x24];
	uint32_t									   Offset;
	uint8_t                                        Pad_58[0x38];
};

class UObject
{
public:
	void**				VFTable;		
	class UClass*		ClassPrivate;	
	class UObject*		OuterPrivate;	
	int32_t				InternalIndex;	
	FName				NamePrivate;	

	bool IsA(void* cmp)
	{
		for (auto super = ClassPrivate; super; super = Mem::Read<UClass*>((ULONG64)super + 0x48))
		{
			if (super == cmp) {
				return true;
			}
		}
		return false;
	}
	void ProcessEvent(void* fn, void* parms)
	{
		auto vtable = *reinterpret_cast<void***>(this);
		auto call = vtable[0x44];
		if (*(BYTE*)call == 0xE9 || *(BYTE*)call == 0xE8)
			return;
		Utils::FastCall<bool>(call, this, fn, parms);
	}
	std::string GetName()
	{
		return  NamePrivate.GetName();
	}
	std::wstring GetNameW()
	{
		return  NamePrivate.GetNameW();
	}
	static UObject* FindObject(const wchar_t* name)
	{
		return Utils::FastCall<UObject*>(Offsets::StaticFindObject, (uintptr_t)0, (uintptr_t)-1, name, false);
	}

};

class UStruct : public UObject
{
public:
	uint8_t			Pad_20[0x28];		// (0x20[0x38]) 
	class UStruct* SuperStruct;		// (0x48[0x08]) 
	uint8_t			Pad_50[0x20];		// (0x50[0x20]) 
	class UField* ChildProperties;	// (0x70[0x08]) 
};

class UClass : public UStruct
{
public:

};


class USceneComponent : public UObject
{
public:
	FVector Pos;
	FVector GetRelativeLocation()
	{
		static UObject* fn = nullptr;
		if (!fn) {
			fn = FindObject((L"USceneComponent.RelativeLocation"));
		}
		struct
		{
			FVector ReturnValue;
		}Params{};
		if (fn)
			ProcessEvent(fn, &Params);
		return Params.ReturnValue;
	}
};
class ItemComponent : public UObject
{
public:
	int32_t GetQuality() {
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"DFMCommonItemRow.Quality"));
		struct {

			int32_t ReturnValue;

		} Params{};
		if (fn)
			ProcessEvent(fn, &Params);

		return Params.ReturnValue;

	}
	int32_t GetValue() {
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"DFMCommonItemRow.InitialGuidePrice"));
		struct {

			int32_t ReturnValue;

		} Params{};
		if (fn)
			ProcessEvent(fn, &Params);

		return Params.ReturnValue;

	}
};
class AActor : public UObject
{
public:
	USceneComponent* RootComponent;
	ItemComponent* ItemData;

	static UClass* StaticClass()
	{
		static UClass* Class;

		if (!Class) Class = (UClass*)FindObject((L"Engine.Actor"));

		return Class;
	}

	FText GetItemName()
	{
		static void* Function = NULL;
		if (!Function) {
			Function = FindObject(L"PickupBase.GetItemName");
		}

		struct {
			FText ReturnValue;
		} Params = {};
		if (Function)
			ProcessEvent(Function, &Params);

		return Params.ReturnValue;
	}

	template<typename T>
	inline T As()
	{
		if (!this)
			return nullptr;

		return static_cast<T>(this);
	}
};

class APawn : public AActor
{
public:
	
};

class UWorld : public UObject
{
public:
	
};

class UGameViewportClient : public UObject
{
public:

};

class UGPHealthDataComponent : public AActor
{
public:

	float GetHealth() {
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"GPGameplay.GPHealthDataComponent.GetHealth"));
		struct {

			float ReturnValue;

		} Params{};
		if (fn)
			ProcessEvent(fn, &Params);

		return Params.ReturnValue;

	}
};

class UCanvas : public UObject
{
public:

	void* GetRoboto()
	{
		static void* Font;
		if (!Font) Font = (void*)FindObject((L"/Game/UI/Fonts/FZLTZHJW_ZH_Font.FZLTZHJW_ZH_Font"));
		return Font;
	}

	void K2_StrokeText(FString RenderText, FLinearColor Color, const FVector2D& Pos)
	{
		const FLinearColor OutlineColor = FLinearColor(0.12f, 0.12f, 0.12f, 0.5f);
		const FLinearColor SoftShadowColor = FLinearColor(0.05f, 0.05f, 0.05f, 0.25f);
		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {
				if (x == 0 && y == 0) continue;
				K2_DrawText(GetRoboto(), RenderText, { Pos.X + x * 0.5f, Pos.Y + y * 0.5f }, // X
					{ 1.f,1.f }, OutlineColor, 1.f, FLinearColor(), FVector2D(), true, true, false, FLinearColor());
			}
		}
		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {
				if (x == 0 && y == 0) continue;
				K2_DrawText(GetRoboto(), RenderText, { Pos.X + x * 0.8f, Pos.Y + y * 0.8f }, // X
					{ 1.f,1.f }, SoftShadowColor, 1.f, FLinearColor(), FVector2D(), true, true, false, FLinearColor());
			}
		}
		FLinearColor AdjustedColor = FLinearColor(std::clamp(Color.r * 1.3f, 0.0f, 1.0f), std::clamp(Color.g * 1.3f, 0.0f, 1.0f), std::clamp(Color.b * 1.3f, 0.0f, 1.0f), Color.a);
		K2_DrawText(GetRoboto(), RenderText, Pos, { 1.f,1.f }, AdjustedColor,
			1.f, FLinearColor(), FVector2D(), true, true, false, FLinearColor());
	}

	void K2_DrawText(void* RenderFont, FString RenderText, FVector2D ScreenPosition, FVector2D Scale, FLinearColor RenderColor, float Kerning, FLinearColor ShadowColor, FVector2D ShadowOffset, bool bCentreX, bool bCentreY, bool bOutlined, FLinearColor OutlineColor) {
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"Canvas.K2_DrawText"));
		struct {
			void* RenderFont;
			FString RenderText;
			FVector2D ScreenPosition;
			FVector2D Scale;
			FLinearColor RenderColor;
			float Kerning;
			FLinearColor ShadowColor;
			FVector2D ShadowOffset;
			bool bCentreX;
			bool bCentreY;
			bool bOutlined;
			FLinearColor OutlineColor;
		}Params{ RenderFont,RenderText,ScreenPosition,Scale,RenderColor,Kerning,ShadowColor,ShadowOffset,bCentreX,bCentreY,bOutlined,OutlineColor };

		if (fn)
			ProcessEvent(fn, &Params);
		return;
	}


};

class UGPTeamComponent : public AActor
{
public:
	int32_t GetTeamID() {
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"GPGameplay.GPTeamComponent.GetTeamID"));
		struct {

			int32_t ReturnValue;

		} Params{};
		if (fn)
			ProcessEvent(fn, &Params);

		return Params.ReturnValue;

	}
	int32_t GetCamp() {
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"GPGameplay.GPTeamComponent.GetCamp"));
		struct {

			int32_t ReturnValue;

		} Params{};
		if (fn)
			ProcessEvent(fn, &Params);

		return Params.ReturnValue;

	}
};

class ACharacter : public APawn
{
public:

	static UClass* StaticClass()
	{
		static UClass* Class;

		if (!Class) Class = (UClass*)FindObject((L"Engine.CHARACTER"));

		return Class;
	}
};

class AIntCharacter : public ACharacter {
public:
	static UClass* StaticClass()
	{
		static UClass* Class;

		if (!Class) Class = (UClass*)FindObject((L"GPGameplay.IntCharacter"));

		return Class;
	}

};

class APlayerCameraManager : public UObject
{
public:
	FVector GetCameraLocation()
	{
		static UObject* fn = nullptr;
		if (!fn) {
			fn = FindObject((L"PlayerCameraManager.GetCameraLocation"));
		}
		struct
		{
			FVector ReturnValue;
		}Params{};
		if (fn)
			ProcessEvent(fn, &Params);
		return Params.ReturnValue;
	}

};
class APlayerController : public UObject
{
public:
	APlayerCameraManager* PlayerCameraManager;
	bool WorldToScreen(FVector WorldLocation, FVector2D& ScreenLocation)
	{
		static UObject* fn = NULL;

		if (!fn)
		{
			fn = FindObject(L"PlayerController.ProjectWorldLocationToScreen");
		}

		struct
		{
			FVector WorldLocation;
			FVector2D ScreenLocation;
			bool bPlayerViewportRelative;
			bool ReturnValue;
		}Params{ WorldLocation,FVector2D(),false };
		if (fn)
			ProcessEvent(fn, &Params);
		ScreenLocation = Params.ScreenLocation;
		return Params.ReturnValue;
	}
};


class ACharacterBase : public AIntCharacter {
public:

	static UClass* StaticClass()
	{
		static UClass* Class;

		if (!Class) Class = (UClass*)FindObject((L"GPGameplay.CharacterBase"));

		return Class;
	}

	bool IsDead() {
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"GPGameplay.CharacterBase.IsDead"));
		struct {

			bool ReturnValue;

		} Params{};
		if (fn)
			ProcessEvent(fn, &Params);

		return Params.ReturnValue;

	}
};

class AGPCharacterBase : public ACharacterBase {
public:

	static UClass* StaticClass()
	{
		static UClass* Class;

		if (!Class) Class = (UClass*)FindObject((L"GPGameplay.GPCharacterBase"));

		return Class;
	}

	char IsAlive() {
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"GPGameplay.GPCharacterBase.IsAlive"));
		struct {

			char ReturnValue;

		} Params{};
		if (fn)
			ProcessEvent(fn, &Params);

		return Params.ReturnValue;
	}

	bool IsAI() {
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"GPGameplay.GPCharacterBase.IsAI"));
		struct {

			bool ReturnValue;

		} Params{};
		if (fn)
			ProcessEvent(fn, &Params);

		return Params.ReturnValue;

	}
	bool IsPlayer() {
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"GPGameplay.GPCharacterBase.IsPlayer"));
		struct {

			bool ReturnValue;

		} Params{};
		if (fn)
			ProcessEvent(fn, &Params);

		return Params.ReturnValue;

	}
	UGPTeamComponent* GetTeamComp() {
		UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"GPGameplay.GPCharacterBase.GetTeamComp"));
		struct {

			UGPTeamComponent* ReturnValue;

		} Params{};
		if (fn)
			ProcessEvent(fn, &Params);

		return Params.ReturnValue;

	}
	UGPHealthDataComponent* GetHealthComp() {
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"GPGameplay.GPCharacterBase.GetHealthComp"));
		struct {

			UGPHealthDataComponent* ReturnValue;

		} Params{};
		if (fn)
			ProcessEvent(fn, &Params);

		return Params.ReturnValue;

	}
};

class AGPCharacter : public AGPCharacterBase {
public:

	static UClass* StaticClass()
	{
		static UClass* Class;

		if (!Class) Class = (UClass*)FindObject((L"GPGameplay.GPCharacter"));

		return Class;
	}
};

class ADFMCharacter : public AGPCharacter {
public:

	static UClass* StaticClass()
	{
		static UClass* Class;

		if (!Class) Class = (UClass*)FindObject((L"DFMGameplay.DFMCharacter"));

		return Class;
	}
};

class ADFMInventoryPickup : public AActor {
public:

	static UClass* StaticClass()
	{
		static UClass* Class;

		if (!Class) Class = (UClass*)FindObject((L"DFMGameplay.InventoryPickup"));

		return Class;
	}
};

class UBlueprintFunctionLibrary : public UObject
{
public:
	
	void GetAllActorsOfClass(UObject* WorldContextObject, UClass* ActorClass, TArray<AActor*>* OutActors)
	{
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"Engine.GameplayStatics.GetAllActorsOfClass"));
		struct
		{
			UObject* WorldContextObject;             // (ConstParm, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
			UClass* ActorClass;                     // (Parm, ZeroConstructor, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
			TArray<AActor*> OutActors;             // (Parm, OutParm, ZeroConstructor, NativeAccessSpecifierPublic)
		} params{};
		params.WorldContextObject = WorldContextObject;
		params.ActorClass = ActorClass;
		if (fn)
			ProcessEvent(fn, &params);
		if (OutActors != nullptr)
			*OutActors = params.OutActors;

	}

	APlayerController* GetPlayerController(UObject* WorldContextObject)
	{
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"GPGameplay.GameplayBlueprintHelper.GetPlayerController"));
		struct {
			UObject* WorldContextObject;
			APlayerController* ReturnValue;
		} Params{};
		Params.WorldContextObject = WorldContextObject;
		if (fn)
			ProcessEvent(fn, &Params);
		return Params.ReturnValue;
	}

	bool IsLocalPlayer(UObject* WorldContextObject)
	{
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"GPGameplay.GameplayBlueprintHelper.IsLocalPlayer"));
		struct {
			UObject* WorldContextObject;
			bool ReturnValue;
		} Params{};
		Params.WorldContextObject = WorldContextObject;
		if (fn)
			ProcessEvent(fn, &Params);
		return Params.ReturnValue;
	}
	uintptr_t GetGPGameState(UObject* WorldContextObject)
	{
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"GPGameplay.GameplayBlueprintHelper.GetGPGameState"));
		struct {
			UObject* WorldContextObject;
			uintptr_t ReturnValue;
		} Params{};
		Params.WorldContextObject = WorldContextObject;
		if (fn)
			ProcessEvent(fn, &Params);
		return Params.ReturnValue;
	}
	AGPCharacter* GetLocalGPCharacter(UObject* WorldContextObject)
	{
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"GPGameplay.GameplayBlueprintHelper.GetLocalGPCharacter"));
		struct {
			UObject* WorldContextObject;
			AGPCharacter* ReturnValue;
		} Params{};
		Params.WorldContextObject = WorldContextObject;
		if (fn)
			ProcessEvent(fn, &Params);
		return Params.ReturnValue;
	}
	enum  EMainFlowState GetMainFlowState()
	{
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"GPSettings.GPScalabilityBlueprintTools.GetMainFlowState"));
		struct {
			enum  EMainFlowState ReturnValue;
		} Params{};
		if (fn)
			ProcessEvent(fn, &Params);
		return Params.ReturnValue;
	}
	int32_t GetGameMode()
	{
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"GPSettings.GPScalabilityBlueprintTools.GetGameMode"));
		struct {
			int32_t ReturnValue;
		} Params{};
		if (fn)
			ProcessEvent(fn, &Params);
		return Params.ReturnValue;
	}
};

class UGPOutLineEffectComponent : public UObject {
public:
	void PlayOutLineEffect(enum class EOutLineEffectType OutLineType) {
		static UObject* fn = nullptr;
		if (fn == nullptr)
			fn = FindObject((L"GPGameplay.GPOutLineEffectComponent.PlayOutLineEffect"));
		struct
		{
			enum class EOutLineEffectType OutLineType;
		} params{};
		params.OutLineType = OutLineType;
		if (fn)
			ProcessEvent(fn, &params);
	}

};
