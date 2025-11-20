#pragma once

class VTableHook
{
public:

	void Initialize(void* pTarget)
	{
		Target = pTarget;
		oVTable = *(void***)pTarget;

		uint32_t Size = CalcVTableSize();
		VTable = new void* [Size];

		memcpy(VTable, oVTable, Size * sizeof(void*));
		*(void***)pTarget = VTable;
	}
	void Bind(uint32_t Index, void* Function)
	{

		VTable[Index] = Function;


	}
	void UnBind(uint32_t Index)
	{
		VTable[Index] = oVTable[Index];
	}
	void UnAllBind()
	{
		delete[] VTable;
		*(void***)Target = oVTable;
	}

	template <typename T>
	T GetOriginal(uint32_t Index)
	{
		return (T)oVTable[Index];
	}

private:
	uint32_t CalcVTableSize()
	{
		uint32_t i = 0;
		while (oVTable[i] != NULL) {
			i++;
		}

		return i;
	}
	void* Target = NULL;
	void** VTable = NULL;
	void** oVTable = NULL;
};

inline namespace Hook { 
	VTableHook RenderHook;
};
