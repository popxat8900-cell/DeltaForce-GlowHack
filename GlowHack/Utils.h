#pragma once

#define IsBadPtr(_x_) (Mem::ValidPtr((void*)(_x_)))

namespace Mem{

	bool ValidPtr(PVOID Ptr)
	{
		auto v1 = (ULONG64)Ptr;
		return (bool)(v1 < 0x1000000 || v1 > 0x7FFFFFF00000 || v1 % sizeof(uint64_t));
	}
	BOOL IsBadReadPtr_(void* lp, UINT_PTR ucb)
	{

		if (ValidPtr(lp))
			return TRUE;

		MEMORY_BASIC_INFORMATION mbi;

		if (VirtualQuery(lp, &mbi, sizeof(mbi)) == 0)
		{
			return TRUE;
		}

		// 检查内存保护标志
		if (mbi.Protect == PAGE_NOACCESS || mbi.Protect == PAGE_EXECUTE)
		{
			return TRUE;
		}
		if (mbi.State == MEM_FREE || mbi.State == MEM_RESERVE) {
			return TRUE;
		}

		if (ucb > mbi.RegionSize)
		{
			return TRUE;
		}

		return FALSE;
	}

	template <typename T>
	T Read(uintptr_t Address)
	{
		return *(T*)Address;
	}

	template<typename T>
	void Write(uintptr_t dwAddress, T Values)
	{
		*(T*)dwAddress = Values;
	}

	bool ReadBytes(uintptr_t address, void* buffer, size_t size)
	{
		if (!address || !buffer || size == 0) return false;

		auto src = reinterpret_cast<const uint8_t*>(address);
		auto dst = reinterpret_cast<uint8_t*>(buffer);

		for (size_t i = 0; i < size; i++)
		{
			dst[i] = src[i];
		}
		return true;
	}

	bool WriteBytes(uintptr_t address, void* buffer, size_t size)
	{
		if (!address || !buffer || size == 0) return false;
		auto src = reinterpret_cast<uint8_t*>(address);
		auto dst = reinterpret_cast<uint8_t*>(buffer);
		DWORD OldProtect = NULL;
		if (VirtualProtect(src, size, PAGE_EXECUTE_READWRITE, &OldProtect)) {
			for (size_t i = 0; i < size; i++)
			{
				src[i] = dst[i];
			}
			VirtualProtect(src, size, OldProtect, &OldProtect);
		}
		return true;
	}

	uintptr_t ABS(uintptr_t address, int offset, int size)
	{
		if (address)
		{
			uintptr_t addrs = address + size + Read<int>(address + offset);
			return addrs;
		}
		return NULL;
	}
}

namespace Utils{

	template<typename Ret = void, typename... Args>
	__forceinline Ret FastCall(void* pFunc, Args... args) {
		typedef Ret(__fastcall* FuncType)(Args...);
		return reinterpret_cast<FuncType>(pFunc)(args...);
	}

	template<typename Ret = void, typename... Args>
	__forceinline Ret FastCall(uint64_t pFunc, Args... args) {
		typedef Ret(__fastcall* FuncType)(Args...);
		return FastCall<Ret>((void*)pFunc, args...);
	}

	std::string WCHAR2String(const std::wstring& wstrSrc)
	{
		if (wstrSrc.empty()) return "";

		int nLen = WideCharToMultiByte(CP_ACP, 0,
			wstrSrc.c_str(), -1,
			nullptr, 0, nullptr, nullptr);
		if (nLen <= 0) return "";

		std::string strDest(nLen - 1, '\0');
		WideCharToMultiByte(CP_ACP, 0,
			wstrSrc.c_str(), -1,
			strDest.data(), nLen, nullptr, nullptr);

		return strDest;
	}
}
