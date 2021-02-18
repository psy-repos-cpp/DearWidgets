#include <dear_widgets.h>

//#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

#include <string>
#include <chrono>

namespace ImWidgets {
	//////////////////////////////////////////////////////////////////////////
	// Helpers
	//////////////////////////////////////////////////////////////////////////
	void	ScaleData(ImGuiDataType data_type, void* p_data, double value)
	{
		switch (data_type)
		{
		case ImGuiDataType_S8:
			*reinterpret_cast<ImS8*>(p_data) *= static_cast<ImS8>(value);
			break;
		case ImGuiDataType_U8:
			*reinterpret_cast<ImU8*>(p_data) *= static_cast<ImU8>(value);
			break;
		case ImGuiDataType_S16:
			*reinterpret_cast<ImS16*>(p_data) *= static_cast<ImS16>(value);
			break;
		case ImGuiDataType_U16:
			*reinterpret_cast<ImU16*>(p_data) *= static_cast<ImU16>(value);
			break;
		case ImGuiDataType_S32:
			*reinterpret_cast<ImS32*>(p_data) *= static_cast<ImS32>(value);
			break;
		case ImGuiDataType_U32:
			*reinterpret_cast<ImU32*>(p_data) *= static_cast<ImU32>(value);
			break;
		case ImGuiDataType_S64:
			*reinterpret_cast<ImS64*>(p_data) *= static_cast<ImS64>(value);
			break;
		case ImGuiDataType_U64:
			*reinterpret_cast<ImU64*>(p_data) *= static_cast<ImU64>(value);
			break;
		case ImGuiDataType_Float:
			*reinterpret_cast<float*>(p_data) *= static_cast<float>(value);
			break;
		case ImGuiDataType_Double:
			*reinterpret_cast<double*>(p_data) *= value;
			break;
		}
	}

	bool	IsNegativeScalar(ImGuiDataType data_type, ImU64* src)
	{
		switch (data_type)
		{
		case ImGuiDataType_S8:
		{
			ImS8 value = *reinterpret_cast<ImS8*>(src);
			return value < 0;
		}
		break;
		case ImGuiDataType_S16:
		{
			ImS16 value = *reinterpret_cast<ImS16*>(src);
			return value < 0;
		}
		break;
		case ImGuiDataType_S32:
		{
			ImS32 value = *reinterpret_cast<ImS32*>(src);
			return value < 0l;
		}
		break;
		case ImGuiDataType_S64:
		{
			ImS64 value = *reinterpret_cast<ImS64*>(src);
			return value < 0ll;
		}
		break;
		case ImGuiDataType_U8:
		case ImGuiDataType_U16:
		case ImGuiDataType_U32:
		case ImGuiDataType_U64:
		{
			return false;
		}
		break;
		case ImGuiDataType_Float:
		{
			float value = *reinterpret_cast<float*>(src);
			return value < 0.0f;
		}
		break;
		case ImGuiDataType_Double:
		{
			double value = *reinterpret_cast<double*>(src);
			return value < 0.0f;
		}
		break;
		}

		return false;
	}

	bool	IsPositiveScalar(ImGuiDataType data_type, ImU64* src)
	{
		return !IsNegativeScalar(data_type, src);
	}

	template <typename TypeSrc>
	ImU64	SetScalar(ImGuiDataType data_type, TypeSrc src)
	{
		ImU64 result;
		switch (data_type)
		{
		case ImGuiDataType_S8:
		{
			ImS8 value = static_cast<ImS8>(src);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U8:
		{
			ImU8 value = static_cast<ImU8>(src);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S16:
		{
			ImS16 value = static_cast<ImS16>(src);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U16:
		{
			ImU16 value = static_cast<ImU16>(src);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S32:
		{
			ImS32 value = static_cast<ImS32>(src);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U32:
		{
			ImU32 value = static_cast<ImU32>(src);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S64:
		{
			ImS64 value = static_cast<ImS64>(src);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U64:
		{
			ImU64 value = static_cast<ImU64>(src);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_Float:
		{
			float value = static_cast<float>(src);
			result = *reinterpret_cast<ImU64*>(&value);
		}
		break;
		case ImGuiDataType_Double:
		{
			double value = static_cast<double>(src);
			result = *reinterpret_cast<ImU64*>(&value);
		}
		break;
		}

		return result;
	}

	void	EqualScalar(ImGuiDataType data_type, ImU64* p_target, ImU64* p_source)
	{
		switch (data_type)
		{
		case ImGuiDataType_S8:
			*reinterpret_cast<ImS8*>(p_target) = *reinterpret_cast<ImS8*>(p_source);
			break;
		case ImGuiDataType_U8:
			*reinterpret_cast<ImU8*>(p_target) = *reinterpret_cast<ImU8*>(p_source);
			break;
		case ImGuiDataType_S16:
			*reinterpret_cast<ImS16*>(p_target) = *reinterpret_cast<ImS16*>(p_source);
			break;
		case ImGuiDataType_U16:
			*reinterpret_cast<ImU16*>(p_target) = *reinterpret_cast<ImU16*>(p_source);
			break;
		case ImGuiDataType_S32:
			*reinterpret_cast<ImS32*>(p_target) = *reinterpret_cast<ImS32*>(p_source);
			break;
		case ImGuiDataType_U32:
			*reinterpret_cast<ImU64*>(p_target) = *reinterpret_cast<ImU32*>(p_source);
			break;
		case ImGuiDataType_S64:
			*reinterpret_cast<ImS64*>(p_target) = *reinterpret_cast<ImS64*>(p_source);
			break;
		case ImGuiDataType_U64:
			*reinterpret_cast<ImU64*>(p_target) = *reinterpret_cast<ImU64*>(p_source);
			break;
		case ImGuiDataType_Float:
			*reinterpret_cast<float*>(p_target) = *reinterpret_cast<float*>(p_source);
			break;
		case ImGuiDataType_Double:
			*reinterpret_cast<double*>(p_target) = *reinterpret_cast<double*>(p_source);
			break;
		}
	}

	float	ScalarToFloat(ImGuiDataType data_type, ImU64* p_source)
	{
		switch (data_type)
		{
		case ImGuiDataType_S8:
			return static_cast<float>(*reinterpret_cast<ImS8*>(p_source));
		case ImGuiDataType_U8:
			return static_cast<float>(*reinterpret_cast<ImU8*>(p_source));
		case ImGuiDataType_S16:
			return static_cast<float>(*reinterpret_cast<ImS16*>(p_source));
		case ImGuiDataType_U16:
			return static_cast<float>(*reinterpret_cast<ImU16*>(p_source));
		case ImGuiDataType_S32:
			return static_cast<float>(*reinterpret_cast<ImS32*>(p_source));
		case ImGuiDataType_U32:
			return static_cast<float>(*reinterpret_cast<ImU32*>(p_source));
		case ImGuiDataType_S64:
			return static_cast<float>(*reinterpret_cast<ImS64*>(p_source));
		case ImGuiDataType_U64:
			return static_cast<float>(*reinterpret_cast<ImU64*>(p_source));
		case ImGuiDataType_Float:
			return static_cast<float>(*reinterpret_cast<float*>(p_source));
		case ImGuiDataType_Double:
			return static_cast<float>(*reinterpret_cast<double*>(p_source));
		}

		return 0.0f;
	}

	ImU64	FloatToScalar(ImGuiDataType data_type, float f_value)
	{
		switch (data_type)
		{
		case ImGuiDataType_S8:
		{
			ImS8 value = static_cast<ImS8>(f_value);
			return static_cast<ImU64>(value);
		}
		case ImGuiDataType_U8:
		{
			ImU8 value = static_cast<ImU8>(f_value);
			return static_cast<ImU64>(value);
		}
		case ImGuiDataType_S16:
		{
			ImS16 value = static_cast<ImS16>(f_value);
			return static_cast<ImU64>(value);
		}
		case ImGuiDataType_U16:
		{
			ImU16 value = static_cast<ImU16>(f_value);
			return static_cast<ImU64>(value);
		}
		case ImGuiDataType_S32:
		{
			ImS32 value = static_cast<ImS32>(f_value);
			return static_cast<ImU64>(value);
		}
		case ImGuiDataType_U32:
		{
			ImU32 value = static_cast<ImU32>(f_value);
			return static_cast<ImU64>(value);
		}
		case ImGuiDataType_S64:
		{
			ImS64 value = static_cast<ImS64>(f_value);
			return static_cast<ImU64>(value);
		}
		case ImGuiDataType_U64:
		{
			ImU64 value = static_cast<ImU64>(f_value);
			return static_cast<ImU64>(value);
		}
		case ImGuiDataType_Float:
		{
			float value = f_value;
			return *reinterpret_cast<ImU64*>(&value);
		}
		case ImGuiDataType_Double:
		{
			double value = static_cast<double>(f_value);
			return *reinterpret_cast<ImU64*>(&value);
		}
		}

		return ImU64();
	}

	ImU64	AddScalar(ImGuiDataType data_type, void* p_a, void* p_b)
	{
		ImU64 result;
		switch (data_type)
		{
		case ImGuiDataType_S8:
		{
			ImS8 value = *reinterpret_cast<ImS8*>(p_a) + *static_cast<ImS8*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U8:
		{
			ImU8 value = *reinterpret_cast<ImU8*>(p_a) + *static_cast<ImU8*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S16:
		{
			ImS16 value = *reinterpret_cast<ImS16*>(p_a) + *static_cast<ImS16*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U16:
		{
			ImU16 value = *reinterpret_cast<ImU16*>(p_a) + *static_cast<ImU16*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S32:
		{
			ImS32 value = *reinterpret_cast<ImS32*>(p_a) + *static_cast<ImS32*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U32:
		{
			ImU32 value = *reinterpret_cast<ImU32*>(p_a) + *static_cast<ImU32*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S64:
		{
			ImS64 value = *reinterpret_cast<ImS64*>(p_a) + *static_cast<ImS64*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U64:
		{
			ImU64 value = *reinterpret_cast<ImU64*>(p_a) + *static_cast<ImU64*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_Float:
		{
			float value = *reinterpret_cast<float*>(p_a) + *static_cast<float*>(p_b);
			result = *reinterpret_cast<ImU64*>(&value);
		}
		break;
		case ImGuiDataType_Double:
		{
			double value = *reinterpret_cast<double*>(p_a) + *static_cast<double*>(p_b);
			result = *reinterpret_cast<ImU64*>(&value);
		}
		break;
		}

		return result;
	}

#pragma optimize( "", off )
	ImU64	SubScalar(ImGuiDataType data_type, void* p_a, void* p_b)
	{
		ImU64 result = 0;
		switch (data_type)
		{
		case ImGuiDataType_S8:
		{
			ImS8 value = *reinterpret_cast<ImS8*>(p_a) - *static_cast<ImS8*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U8:
		{
			ImU8 value = *reinterpret_cast<ImU8*>(p_a) - *static_cast<ImU8*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S16:
		{
			ImS16 value = *reinterpret_cast<ImS16*>(p_a) - *static_cast<ImS16*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U16:
		{
			ImU16 value = *reinterpret_cast<ImU16*>(p_a) - *static_cast<ImU16*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S32:
		{
			ImS32 value = *reinterpret_cast<ImS32*>(p_a) - *static_cast<ImS32*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U32:
		{
			ImU32 value = *reinterpret_cast<ImU32*>(p_a) - *static_cast<ImU32*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S64:
		{
			ImS64 value = *reinterpret_cast<ImS64*>(p_a) - *static_cast<ImS64*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U64:
		{
			ImU64 value = *reinterpret_cast<ImU64*>(p_a) - *static_cast<ImU64*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_Float:
		{
			float value = *reinterpret_cast<float*>(p_a) - *static_cast<float*>(p_b);
			result = *reinterpret_cast<ImU64*>(&value);
		}
		break;
		case ImGuiDataType_Double:
		{
			double value = *reinterpret_cast<double*>(p_a) - *static_cast<double*>(p_b);
			result = *reinterpret_cast<ImU64*>(&value);
		}
		break;
		}

		return result;
	}

	ImU64	MulScalar(ImGuiDataType data_type, void* p_a, void* p_b)
	{
		ImU64 result;
		switch (data_type)
		{
		case ImGuiDataType_S8:
		{
			ImS8 value = *reinterpret_cast<ImS8*>(p_a) * *static_cast<ImS8*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U8:
		{
			ImU8 value = *reinterpret_cast<ImU8*>(p_a) * *static_cast<ImU8*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S16:
		{
			ImS16 value = *reinterpret_cast<ImS16*>(p_a) * *static_cast<ImS16*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U16:
		{
			ImU16 value = *reinterpret_cast<ImU16*>(p_a) * *static_cast<ImU16*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S32:
		{
			ImS32 value = *reinterpret_cast<ImS32*>(p_a) * *static_cast<ImS32*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U32:
		{
			ImU32 value = *reinterpret_cast<ImU32*>(p_a) * *static_cast<ImU32*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S64:
		{
			ImS64 value = *reinterpret_cast<ImS64*>(p_a) * *static_cast<ImS64*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U64:
		{
			ImU64 value = *reinterpret_cast<ImU64*>(p_a) * *static_cast<ImU64*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_Float:
		{
			float value = *reinterpret_cast<float*>(p_a) * *static_cast<float*>(p_b);
			result = *reinterpret_cast<ImU64*>(&value);
		}
		break;
		case ImGuiDataType_Double:
		{
			double value = *reinterpret_cast<double*>(p_a) * *static_cast<double*>(p_b);
			result = *reinterpret_cast<ImU64*>(&value);
		}
		break;
		}

		return result;
	}

	ImU64	DivScalar(ImGuiDataType data_type, void* p_a, void* p_b)
	{
		ImU64 result;
		switch (data_type)
		{
		case ImGuiDataType_S8:
		{
			ImS8 value = *reinterpret_cast<ImS8*>(p_a) / *static_cast<ImS8*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U8:
		{
			ImU8 value = *reinterpret_cast<ImU8*>(p_a) / *static_cast<ImU8*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S16:
		{
			ImS16 value = *reinterpret_cast<ImS16*>(p_a) / *static_cast<ImS16*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U16:
		{
			ImU16 value = *reinterpret_cast<ImU16*>(p_a) / *static_cast<ImU16*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S32:
		{
			ImS32 value = *reinterpret_cast<ImS32*>(p_a) / *static_cast<ImS32*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U32:
		{
			ImU32 value = *reinterpret_cast<ImU32*>(p_a) / *static_cast<ImU32*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S64:
		{
			ImS64 value = *reinterpret_cast<ImS64*>(p_a) / *static_cast<ImS64*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U64:
		{
			ImU64 value = *reinterpret_cast<ImU64*>(p_a) / *static_cast<ImU64*>(p_b);
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_Float:
		{
			float value = *reinterpret_cast<float*>(p_a) / *static_cast<float*>(p_b);
			result = *reinterpret_cast<ImU64*>(&value);
		}
		break;
		case ImGuiDataType_Double:
		{
			double value = *reinterpret_cast<double*>(p_a) / *static_cast<double*>(p_b);
			result = *reinterpret_cast<ImU64*>(&value);
		}
		break;
		}

		return result;
	}

	ImU64	ClampScalar(ImGuiDataType data_type, void* p_value, void* p_min, void* p_max)
	{
		ImU64 result = 0;
		switch (data_type)
		{
		case ImGuiDataType_S8:
		{
			ImS8 value = ImClamp(*reinterpret_cast<ImS8*>(p_value), *static_cast<ImS8*>(p_min), *static_cast<ImS8*>(p_max));
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U8:
		{
			ImU8 value = ImClamp(*reinterpret_cast<ImU8*>(p_value), *static_cast<ImU8*>(p_min), *static_cast<ImU8*>(p_max));
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S16:
		{
			ImS16 value = ImClamp(*reinterpret_cast<ImS16*>(p_value), *static_cast<ImS16*>(p_min), *static_cast<ImS16*>(p_max));
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U16:
		{
			ImU16 value = ImClamp(*reinterpret_cast<ImU16*>(p_value), *static_cast<ImU16*>(p_min), *static_cast<ImU16*>(p_max));
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S32:
		{
			ImS32 value = ImClamp(*reinterpret_cast<ImS32*>(p_value), *static_cast<ImS32*>(p_min), *static_cast<ImS32*>(p_max));
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U32:
		{
			ImU32 value = ImClamp(*reinterpret_cast<ImU32*>(p_value), *static_cast<ImU32*>(p_min), *static_cast<ImU32*>(p_max));
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_S64:
		{
			ImS64 value = ImClamp(*reinterpret_cast<ImS64*>(p_value), *static_cast<ImS64*>(p_min), *static_cast<ImS64*>(p_max));
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_U64:
		{
			ImU64 value = ImClamp(*reinterpret_cast<ImU64*>(p_value), *static_cast<ImU64*>(p_min), *static_cast<ImU64*>(p_max));
			result = static_cast<ImU64>(value);
		}
		break;
		case ImGuiDataType_Float:
		{
			float value = ImClamp(*reinterpret_cast<float*>(p_value), *static_cast<float*>(p_min), *static_cast<float*>(p_max));
			result = *reinterpret_cast<ImU64*>(&value);
		}
		break;
		case ImGuiDataType_Double:
		{
			double value = ImClamp(*reinterpret_cast<double*>(p_value), *static_cast<double*>(p_min), *static_cast<double*>(p_max));
			result = *reinterpret_cast<ImU64*>(&value);
		}
		break;
		}

		return result;
	}

	void		MemoryString(std::string& sResult, ImU64 const uMemoryByte)
	{
		if (uMemoryByte < ImWidget_Kibi)
		{
			sResult = std::to_string(static_cast<float>(uMemoryByte)) + " B";
		}
		else if (uMemoryByte < ImWidget_Mibi)
		{
			sResult = std::to_string(static_cast<float>(uMemoryByte) / static_cast<float>(ImWidget_Kibi)) + " KiB";
		}
		else if (uMemoryByte < ImWidget_Gibi)
		{
			sResult = std::to_string(static_cast<float>(uMemoryByte) / static_cast<float>(ImWidget_Mibi)) + " MiB";
		}
		else if (uMemoryByte < ImWidget_Tebi)
		{
			sResult = std::to_string(static_cast<float>(uMemoryByte) / static_cast<float>(ImWidget_Gibi)) + " GiB";
		}
		else if (uMemoryByte < ImWidget_Pebi)
		{
			sResult = std::to_string(static_cast<float>(uMemoryByte) / static_cast<float>(ImWidget_Tebi)) + " TiB";
		}
	}

	void		TimeString(std::string& sResult, ImU64 const uNanoseconds)
	{
		std::chrono::nanoseconds oDuration( uNanoseconds );

		typedef std::chrono::duration< ImU64, std::ratio_multiply< std::chrono::hours::period, std::ratio< 8 > >::type > Days; // UTC: +8:00

		Days oDays			= std::chrono::duration_cast< Days >( oDuration );
		oDuration -= oDays;
		auto oHours			= std::chrono::duration_cast< std::chrono::hours >( oDuration );
		oDuration -= oHours;
		auto oMinutes		= std::chrono::duration_cast< std::chrono::minutes >( oDuration );
		oDuration -= oMinutes;
		auto oSeconds		= std::chrono::duration_cast< std::chrono::seconds >( oDuration );
		oDuration -= oSeconds;
		auto oMilliseconds	= std::chrono::duration_cast< std::chrono::milliseconds >( oDuration );
		oDuration -= oMilliseconds;
		auto oMicroseconds	= std::chrono::duration_cast< std::chrono::microseconds >( oDuration );
		oDuration -= oMicroseconds;
		auto oNanoseconds	= std::chrono::duration_cast< std::chrono::nanoseconds >( oDuration );

		ImU64 const uNanoSecondsCountRaw	= oNanoseconds.count();
		ImU64 const uNanoSecondsCount		= uNanoSecondsCountRaw <= 100ull ? 0ull : uNanoSecondsCountRaw;

		sResult.clear();
		if ( oDays.count() > 0 )
		{
			sResult =	std::to_string( oDays.count() )			+ " d : " +
						std::to_string( oHours.count() )		+ " h : " +
						std::to_string( oMinutes.count() )		+ " min : " +
						std::to_string( oSeconds.count() )		+ " s : " +
						std::to_string( oMilliseconds.count() )	+ " ms : " +
						//std::to_string( oMicroseconds.count() ) + " \u00B5s : " +
						std::to_string( oMicroseconds.count() ) + " us";//: " +
						//std::to_string( uNanoSecondsCount )		+ " ns";
		}
		else if ( oHours.count() > 0 )
		{
			sResult =	std::to_string( oHours.count() )		+ " h : " +
						std::to_string( oMinutes.count() )		+ " min : " +
						std::to_string( oSeconds.count() )		+ " s : " +
						std::to_string( oMilliseconds.count() )	+ " ms : " +
						//std::to_string( oMicroseconds.count() ) + " \u00B5s : " +
						std::to_string( oMicroseconds.count() ) + " us";//: " +
						//std::to_string( uNanoSecondsCount )		+ " ns";
		}
		else if ( oMinutes.count() > 0 )
		{
			sResult =	std::to_string( oMinutes.count() )		+ " min : " +
						std::to_string( oSeconds.count() )		+ " s : " +
						std::to_string( oMilliseconds.count() )	+ " ms : " +
						//std::to_string( oMicroseconds.count() ) + " \u00B5s : " +
						std::to_string( oMicroseconds.count() ) + " us";//: " +
						//std::to_string( uNanoSecondsCount )		+ " ns";
		}
		else if ( oSeconds.count() > 0 )
		{
			sResult =	std::to_string( oSeconds.count() )		+ " s : " +
						std::to_string( oMilliseconds.count() )	+ " ms : " +
						//std::to_string( oMicroseconds.count() ) + " \u00B5s : " +
						std::to_string( oMicroseconds.count() ) + " us";//: " +
						//std::to_string( uNanoSecondsCount )		+ " ns";
		}
		else if ( oMilliseconds.count() > 0 )
		{
			sResult =	std::to_string( oMilliseconds.count() )	+ " ms : " +
						//std::to_string( oMicroseconds.count() ) + " \u00B5s : " +
						std::to_string( oMicroseconds.count() ) + " us";//: " +
						//std::to_string( uNanoSecondsCount )		+ " ns";
		}
		else if ( oMicroseconds.count() > 0 )
		{
			sResult =	//std::to_string( oMicroseconds.count() ) + " \u00B5s : " +
						std::to_string( oMicroseconds.count() ) + " us";//: " +
						//std::to_string( uNanoSecondsCount )		+ " ns";
		}
		else //if ( oNanoseconds.count() > 0 )
		{
			sResult =	std::to_string( uNanoSecondsCount )		+ " ns";
		}
	}

	float Dist2(ImVec2 const v, ImVec2 const w)
	{
		//return Sqr(v.x - w.x) + Sqr(v.y - w.y);
		return ImLengthSqr(v - w);
	}
	float DistOnSegmentSqr(ImVec2 const p, ImVec2 const v, ImVec2 const w)
	{
		float l2 = Dist2(v, w);
		if (l2 == 0.0f)
			return 0.0f;

		float t = ((p.x - v.x) * (w.x - v.x) + (p.y - v.y) * (w.y - v.y)) / l2;

		return ImSaturate(t) * Dist2(w, v);
	}
	float DistToSegmentSqr(ImVec2 const p, ImVec2 const v, ImVec2 const w)
	{
		float l2 = Dist2(v, w);
		if (l2 == 0.0f)
			return Dist2(p, v);

		float t = ((p.x - v.x) * (w.x - v.x) + (p.y - v.y) * (w.y - v.y)) / l2;
		t = ImSaturate(t);

		return Dist2(p, ImVec2(v.x + t * (w.x - v.x),
							   v.y + t * (w.y - v.y)));
	}
	float Side(ImVec2 const src, ImVec2 const tgt, ImVec2 const pts)
	{
		ImVec2 vDir = tgt - src;
		ImVec2 vVec = pts - src;

		float zCross = vDir.x * vVec.y - vDir.y * vVec.x;

		return zCross >= 0.0f ? 1.0f : -1.0f;
	}
	ImVec2 Saturatev(ImVec2 const v)
	{
		return ImVec2(ImSaturate(v.x), ImSaturate(v.y));
	}
	ImVec2 Clampv(ImVec2 const v, ImVec2 const min, ImVec2 const max)
	{
		return ImVec2(ImClamp(v.x, min.x, max.x), ImClamp(v.y, min.y, max.y));
	}
	float Rescale01(float const x, float const min, float const max)
	{
		return (x - min) / (max - min);
	}
	ImVec2 Rescale01v(ImVec2 const v, ImVec2 const min, ImVec2 const max)
	{
		return ImVec2(Rescale01(v.x, min.x, max.x), Rescale01(v.y, min.y, max.y));
	}
	float Rescale(float const x, float const min, float const max, float const newMin, float const newMax)
	{
		return Rescale01(x, min, max) * (newMax - newMin) + newMin;
	}
	ImVec2 Rescalev(ImVec2 const x, ImVec2 const min, ImVec2 const max, ImVec2 const newMin, ImVec2 const newMax)
	{
		ImVec2 const vNorm = Rescale01v(x, min, max);
		return ImVec2(vNorm.x * (newMax.x - newMin.x) + newMin.x, vNorm.y * (newMax.y - newMin.y) + newMin.y);
	}
	float Sign(float x)
	{
		return x < 0.0f ? -1.0f : 1.0f;
	}

	//////////////////////////////////////////////////////////////////////////
	// Widgets
	//////////////////////////////////////////////////////////////////////////
	void CenterNextItem(ImVec2 nextItemSize)
	{
		float const width = ImGui::GetContentRegionAvailWidth();
		ImGui::Dummy(ImVec2((width - nextItemSize.x) * 0.5f, nextItemSize.y));
		ImGui::SameLine();
	}

	bool DragFloatLog(const char* label, float* data, float v_speed, float log_basis, const void* p_min, const void* p_max, ImGuiSliderFlags flags)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const float w = ImGui::CalcItemWidth();
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
		const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w, label_size.y + style.FramePadding.y * 2.0f));
		const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));

		ImGui::ItemSize(total_bb, style.FramePadding.y);
		if (!ImGui::ItemAdd(total_bb, id, &frame_bb))
			return false;

		//// Default format string when passing NULL
		//if (format == NULL)
		//	format = ImGui::DataTypeGetInfo(data_type)->PrintFmt;
		//else if (data_type == ImGuiDataType_S32 && strcmp(format, "%d") != 0) // (FIXME-LEGACY: Patch old "%.0f" format string to use "%d", read function more details.)
		//	format = ImGui::PatchFormatStringFloatToInt(format);

		// Tabbing or CTRL-clicking on Drag turns it into an InputText
		const bool hovered = ImGui::ItemHoverable(frame_bb, id);
		const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;
		bool temp_input_is_active = temp_input_allowed && ImGui::TempInputIsActive(id);
		if (!temp_input_is_active)
		{
			const bool focus_requested = temp_input_allowed && ImGui::FocusableItemRegister(window, id);
			const bool clicked = (hovered && g.IO.MouseClicked[0]);
			const bool double_clicked = (hovered && g.IO.MouseDoubleClicked[0]);
			if (focus_requested || clicked || double_clicked || g.NavActivateId == id || g.NavInputId == id)
			{
				ImGui::SetActiveID(id, window);
				ImGui::SetFocusID(id, window);
				ImGui::FocusWindow(window);
				g.ActiveIdUsingNavDirMask = (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
				if (temp_input_allowed && (focus_requested || (clicked && g.IO.KeyCtrl) || double_clicked || g.NavInputId == id))
				{
					temp_input_is_active = true;
					ImGui::FocusableItemUnregister(window);
				}
			}
			// Experimental: simple click (without moving) turns Drag into an InputText
			// FIXME: Currently polling ImGuiConfigFlags_IsTouchScreen, may either poll an hypothetical ImGuiBackendFlags_HasKeyboard and/or an explicit drag settings.
			if (g.IO.ConfigDragClickToInputText && temp_input_allowed && !temp_input_is_active)
				if (g.ActiveId == id && hovered && g.IO.MouseReleased[0] && !ImGui::IsMouseDragPastThreshold(0, g.IO.MouseDragThreshold * 0.5f/*DRAG_MOUSE_THRESHOLD_FACTOR*/))
				{
					g.NavInputId = id;
					temp_input_is_active = true;
					ImGui::FocusableItemUnregister(window);
				}
		}

		if (temp_input_is_active)
		{
			// Only clamp CTRL+Click input when ImGuiSliderFlags_AlwaysClamp is set
			const bool is_clamp_input = (flags & ImGuiSliderFlags_AlwaysClamp) != 0 && (p_min == NULL || p_max == NULL || ImGui::DataTypeCompare(ImGuiDataType_Float, p_min, p_max) < 0);
			return ImGui::TempInputScalar(frame_bb, id, label, ImGuiDataType_Float, data, "%f", is_clamp_input ? p_min : NULL, is_clamp_input ? p_max : NULL);
		}

		// Draw frame
		const ImU32 frame_col = ImGui::GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : g.HoveredId == id ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
		ImGui::RenderNavHighlight(frame_bb, id);
		ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, frame_col, true, style.FrameRounding);

		// Drag behavior
		const bool value_changed = ImGui::DragBehavior(id, ImGuiDataType_Float, data, v_speed, p_min, p_max, "%f", flags);
		if (value_changed)
			ImGui::MarkItemEdited(id);

		// Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
		char value_buf[64];
		const char* value_buf_end = value_buf + ImGui::DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), ImGuiDataType_Float, data, "%f");
		if (g.LogEnabled)
			ImGui::LogSetNextTextDecoration("{", "}");
		ImGui::RenderTextClipped(frame_bb.Min, frame_bb.Max, value_buf, value_buf_end, NULL, ImVec2(0.5f, 0.5f));

		if (label_size.x > 0.0f)
			ImGui::RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

		IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags);
		return value_changed;
	}

	bool DragLengthScalar(const char* label, ImGuiDataType data_type, void* p_data, ImWidgetsLengthUnit* p_defaultUnit, float v_speed, const void* p_min, const void* p_max, ImGuiSliderFlags flags)
	{
		bool modified = false;

		ImWidgetsLengthUnit& defaultUnit = *p_defaultUnit;

		std::string format = std::string(ImGui::DataTypeGetInfo(data_type)->PrintFmt);
		if (ImGui::Button("<", ImVec2(16.0f, 0.0f)))
		{
			--defaultUnit;
			if (defaultUnit < 0)
				defaultUnit = ImWidgetsLengthUnit_COUNT - 1;
		}
		ImGui::SameLine();
		if (defaultUnit == ImWidgetsLengthUnit_Imperial)
		{
			ScaleData(data_type, p_data, 0.28084);
			format += " ft";
		}
		else
		{
			format += " m";
		}
		float const width = ImGui::GetContentRegionAvailWidth();
		ImGui::SetNextItemWidth(width * 0.5f - 32.0f);
		modified |= ImGui::DragScalar(label, data_type, p_data, v_speed, p_min, p_max, format.c_str(), flags);
		if (defaultUnit == ImWidgetsLengthUnit_Imperial)
		{
			ScaleData(data_type, p_data, 1.0 / 0.28084);
		}
		ImGui::SameLine();
		if (ImGui::Button(">", ImVec2(16.0f, 0.0f)))
		{
			++defaultUnit;
			defaultUnit %= ImWidgetsLengthUnit_COUNT;
		}
		ImGui::SetWindowFontScale(1.0f);
		ImVec2 const vTextSize = ImGui::CalcTextSize(defaultUnit == ImWidgetsLengthUnit_Metric ? "meter" : "feet");
		CenterNextItem(vTextSize);
		ImGui::Text(defaultUnit == ImWidgetsLengthUnit_Metric ? "meter" : "feet");
		ImGui::SetWindowFontScale(1.0f);

		return modified;
	}

	bool InputVec2(char const* pLabel, ImVec2* pValue, ImVec2* p_vMinValue, ImVec2* p_vMaxValue, float const fScale /*= 1.0f*/)
	{
		return Slider2DScalar(pLabel, ImGuiDataType_Float, &pValue->x, &pValue->y, &p_vMinValue->x, &p_vMaxValue->x, &p_vMinValue->y, &p_vMaxValue->y, fScale);
	}

	bool InputVec3(char const* pLabel, ImVec4* pValue, ImVec4 const vMinValue, ImVec4 const vMaxValue, float const fScale /*= 1.0f*/)
	{
		return SliderScalar3D(pLabel, &pValue->x, &pValue->y, &pValue->z, vMinValue.x, vMaxValue.x, vMinValue.y, vMaxValue.y, vMinValue.z, vMaxValue.z, fScale);
	}

	bool Slider2DScalar(char const* pLabel, ImGuiDataType data_type, void* p_valueX, void* p_valueY, void* p_minX, void* p_maxX, void* p_minY, void* p_maxY, float const fScale /*= 1.0f*/)
	{
		assert(ScalarToFloat(data_type, p_minX) < ScalarToFloat(data_type, p_maxX));
		assert(ScalarToFloat(data_type, p_minY) < ScalarToFloat(data_type, p_maxY));

		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		//ImGuiContext& g = *GImGui;
		//const ImGuiStyle& style = g.Style;
		//const ImGuiID id = window->GetID(pLabel);

		ImGuiID const iID = ImGui::GetID(pLabel);

		ImVec2 const vSizeSubstract = ImGui::CalcTextSize(std::to_string(1.0f).c_str()) * 1.1f;

		float const vSizeFull = (ImGui::GetWindowContentRegionWidth() - vSizeSubstract.x) * fScale;
		ImVec2 const vSize(vSizeFull, vSizeFull);

		float const fHeightOffset = ImGui::GetTextLineHeight();
		ImVec2 const vHeightOffset(0.0f, fHeightOffset);

		ImVec2 vPos = ImGui::GetCursorScreenPos();
		ImRect oRect(vPos + vHeightOffset, vPos + vSize + vHeightOffset);

		ImGui::Text(pLabel);

		ImGui::PushID(iID);

		ImU32 const uFrameCol = ImGui::GetColorU32(ImGuiCol_FrameBg);

		ImVec2 const vOriginPos = ImGui::GetCursorScreenPos();
		ImGui::RenderFrame(oRect.Min, oRect.Max, uFrameCol, false, 0.0f);

		ImU64 s_delta_x = SubScalar(data_type, p_maxX, p_minX);
		ImU64 s_delta_y = SubScalar(data_type, p_maxY, p_minY);

		bool bModified = false;
		ImVec2 const vSecurity(15.0f, 15.0f);
		ImRect frame_bb = ImRect(oRect.Min - vSecurity, oRect.Max + vSecurity);
		//ImGui::PushItemFlag(ImGuiItemFlags_NoNav, true);
		bool hovered;
		bool held;
		bool pressed = ImGui::ButtonBehavior(frame_bb, ImGui::GetID("##Zone"), &hovered, &held);
		if (hovered && held)
		{
			ImVec2 const vCursorPos = ImGui::GetMousePos() - oRect.Min;

			float fValueX = vCursorPos.x / (oRect.Max.x - oRect.Min.x) * ScalarToFloat(data_type, &s_delta_x) + ScalarToFloat(data_type, (ImU64*)p_minX);
			float fValueY = ScalarToFloat(data_type, &s_delta_y) - vCursorPos.y / (oRect.Max.y - oRect.Min.y) * ScalarToFloat(data_type, &s_delta_y) + ScalarToFloat(data_type, (ImU64*)p_minY);

			ImU64 s_value_x = FloatToScalar(data_type, fValueX);
			ImU64 s_value_y = FloatToScalar(data_type, fValueY);

			EqualScalar(data_type, (ImU64*)p_valueX, &s_value_x);
			EqualScalar(data_type, (ImU64*)p_valueY, &s_value_y);

			bModified = true;
		}
		//ImGui::PopItemFlag();

		ImU64 s_clamped_x = ClampScalar(data_type, p_valueX, p_minX, p_maxX);
		ImU64 s_clamped_y = ClampScalar(data_type, p_valueY, p_minY, p_maxY);
		EqualScalar(data_type, (ImU64*)p_valueX, &s_clamped_x);
		EqualScalar(data_type, (ImU64*)p_valueY, &s_clamped_y);

		float const fScaleX = (ScalarToFloat(data_type, (ImU64*)p_valueX) - ScalarToFloat(data_type, (ImU64*)p_minX)) / ScalarToFloat(data_type, &s_delta_x);
		float const fScaleY = 1.0f - (ScalarToFloat(data_type, (ImU64*)p_valueY) - ScalarToFloat(data_type, (ImU64*)p_minY)) / ScalarToFloat(data_type, &s_delta_y);

		constexpr float fCursorOff = 10.0f;
		float const fXLimit = fCursorOff / oRect.GetWidth();
		float const fYLimit = fCursorOff / oRect.GetHeight();

		ImVec2 const vCursorPos((oRect.Max.x - oRect.Min.x) * fScaleX + oRect.Min.x, (oRect.Max.y - oRect.Min.y) * fScaleY + oRect.Min.y);

		ImDrawList* pDrawList = ImGui::GetWindowDrawList();

		ImVec4 const vBlue(70.0f / 255.0f, 102.0f / 255.0f, 230.0f / 255.0f, 1.0f); // TODO: choose from style
		ImVec4 const vOrange(255.0f / 255.0f, 128.0f / 255.0f, 64.0f / 255.0f, 1.0f); // TODO: choose from style

		ImS32 const uBlue = ImGui::GetColorU32(vBlue);
		ImS32 const uOrange = ImGui::GetColorU32(vOrange);

		constexpr float fBorderThickness	= 2.0f;
		constexpr float fLineThickness		= 3.0f;
		constexpr float fHandleRadius		= 7.0f;
		constexpr float fHandleOffsetCoef	= 2.0f;

		// Cursor
		pDrawList->AddCircleFilled(vCursorPos, 5.0f, uBlue, 16);

		// Vertical Line
		if (fScaleY > 2.0f * fYLimit)
			pDrawList->AddLine(ImVec2(vCursorPos.x, oRect.Min.y + fCursorOff), ImVec2(vCursorPos.x, vCursorPos.y - fCursorOff), uOrange, fLineThickness);
		if (fScaleY < 1.0f - 2.0f * fYLimit)
			pDrawList->AddLine(ImVec2(vCursorPos.x, oRect.Max.y - fCursorOff), ImVec2(vCursorPos.x, vCursorPos.y + fCursorOff), uOrange, fLineThickness);

		// Horizontal Line
		if (fScaleX > 2.0f * fXLimit)
			pDrawList->AddLine(ImVec2(oRect.Min.x + fCursorOff, vCursorPos.y), ImVec2(vCursorPos.x - fCursorOff, vCursorPos.y), uOrange, fLineThickness);
		if (fScaleX < 1.0f - 2.0f * fYLimit)
			pDrawList->AddLine(ImVec2(oRect.Max.x - fCursorOff, vCursorPos.y), ImVec2(vCursorPos.x + fCursorOff, vCursorPos.y), uOrange, fLineThickness);

		std::string formatX = ImGui::DataTypeGetInfo(data_type)->PrintFmt;
		std::string formatY = ImGui::DataTypeGetInfo(data_type)->PrintFmt;

		if (IsPositiveScalar(data_type, (ImU64*)p_valueX))
		{
			formatX = " " + formatX;
		}
		if (IsPositiveScalar(data_type, (ImU64*)p_valueY))
		{
			formatY = " " + formatY;
		}

		char pBufferX[64];
		char pBufferY[64];
		/*const char* value_buf_end_x = pBufferX + */ImGui::DataTypeFormatString(pBufferX, IM_ARRAYSIZE(pBufferX), data_type, p_valueX, formatX.c_str());
		/*const char* value_buf_end_y = pBufferX + */ImGui::DataTypeFormatString(pBufferY, IM_ARRAYSIZE(pBufferY), data_type, p_valueY, formatY.c_str());

		ImU32 const uTextCol = ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]);

		ImGui::SetWindowFontScale(0.75f);

		ImVec2 const vXSize = ImGui::CalcTextSize(pBufferX);
		ImVec2 const vYSize = ImGui::CalcTextSize(pBufferY);

		ImVec2 const vHandlePosX = ImVec2(vCursorPos.x, oRect.Max.y + vYSize.x * 0.5f);
		ImVec2 const vHandlePosY = ImVec2(oRect.Max.x + fHandleOffsetCoef * fCursorOff + vYSize.x, vCursorPos.y);

		ImRect handle_x_bb = ImRect(vHandlePosX - ImVec2(fHandleRadius, fHandleRadius) - vSecurity, vHandlePosX + ImVec2(fHandleRadius, fHandleRadius) + vSecurity);
		ImRect handle_y_bb = ImRect(vHandlePosY - ImVec2(fHandleRadius, fHandleRadius) - vSecurity, vHandlePosY + ImVec2(fHandleRadius, fHandleRadius) + vSecurity);
		pressed = ImGui::ButtonBehavior(handle_x_bb, ImGui::GetID("##HandleX"), &hovered, &held);
		if (hovered && held)
		{
			ImVec2 const vCursorPosLocal = ImGui::GetMousePos() - oRect.Min;

			//*fValueX = vCursorPos.x / (oRect.Max.x - oRect.Min.x) * fDeltaX + fMinX;
			float fValueX = vCursorPosLocal.x / (oRect.Max.x - oRect.Min.x) * ScalarToFloat(data_type, &s_delta_x) + ScalarToFloat(data_type, (ImU64*)p_minX);
			ImU64 s_value_x = FloatToScalar(data_type, fValueX);
			EqualScalar(data_type, (ImU64*)p_valueX, &s_value_x);

			bModified = true;
		}
		pressed = ImGui::ButtonBehavior(handle_y_bb, ImGui::GetID("##HandleX"), &hovered, &held);
		if (hovered && held)
		{
			ImVec2 const vCursorPosLocal = ImGui::GetMousePos() - oRect.Min;

			//*fValueY = fDeltaY - vCursorPos.y / (oRect.Max.y - oRect.Min.y) * fDeltaY + fMinY;
			float fValueY = ScalarToFloat(data_type, &s_delta_y) - vCursorPosLocal.y / (oRect.Max.y - oRect.Min.y) * ScalarToFloat(data_type, &s_delta_y) + ScalarToFloat(data_type, (ImU64*)p_minY);
			ImU64 s_value_y = FloatToScalar(data_type, fValueY);
			EqualScalar(data_type, (ImU64*)p_valueY, &s_value_y);

			bModified = true;
		}

		pDrawList->AddText(
			ImVec2(
				ImMin(ImMax(vCursorPos.x - vXSize.x * 0.5f, oRect.Min.x), oRect.Min.x + vSize.x - vXSize.x),
				oRect.Max.y + fCursorOff),
			uTextCol,
			pBufferX);
		pDrawList->AddText(
			ImVec2(oRect.Max.x + fCursorOff, ImMin(ImMax(vCursorPos.y - vYSize.y * 0.5f, oRect.Min.y),
				oRect.Min.y + vSize.y - vYSize.y)),
			uTextCol,
			pBufferY);
		ImGui::SetWindowFontScale(1.0f);

		// Borders::Right
		pDrawList->AddCircleFilled(ImVec2(oRect.Max.x, vCursorPos.y), 2.0f, uOrange, 3);
		// Handle Right::Y
		pDrawList->AddNgonFilled(ImVec2(oRect.Max.x + fHandleOffsetCoef * fCursorOff + vYSize.x, vCursorPos.y), fHandleRadius, uBlue, 4);
		if (fScaleY > fYLimit)
			pDrawList->AddLine(ImVec2(oRect.Max.x, oRect.Min.y), ImVec2(oRect.Max.x, vCursorPos.y - fCursorOff), uBlue, fBorderThickness);
		if (fScaleY < 1.0f - fYLimit)
			pDrawList->AddLine(ImVec2(oRect.Max.x, oRect.Max.y), ImVec2(oRect.Max.x, vCursorPos.y + fCursorOff), uBlue, fBorderThickness);
		// Borders::Top
		pDrawList->AddCircleFilled(ImVec2(vCursorPos.x, oRect.Min.y), 2.0f, uOrange, 3);
		if (fScaleX > fXLimit)
			pDrawList->AddLine(ImVec2(oRect.Min.x, oRect.Min.y), ImVec2(vCursorPos.x - fCursorOff, oRect.Min.y), uBlue, fBorderThickness);
		if (fScaleX < 1.0f - fXLimit)
			pDrawList->AddLine(ImVec2(oRect.Max.x, oRect.Min.y), ImVec2(vCursorPos.x + fCursorOff, oRect.Min.y), uBlue, fBorderThickness);
		// Borders::Left
		pDrawList->AddCircleFilled(ImVec2(oRect.Min.x, vCursorPos.y), 2.0f, uOrange, 3);
		if (fScaleY > fYLimit)
			pDrawList->AddLine(ImVec2(oRect.Min.x, oRect.Min.y), ImVec2(oRect.Min.x, vCursorPos.y - fCursorOff), uBlue, fBorderThickness);
		if (fScaleY < 1.0f - fYLimit)
			pDrawList->AddLine(ImVec2(oRect.Min.x, oRect.Max.y), ImVec2(oRect.Min.x, vCursorPos.y + fCursorOff), uBlue, fBorderThickness);
		// Borders::Bottom
		pDrawList->AddCircleFilled(ImVec2(vCursorPos.x, oRect.Max.y), 2.0f, uOrange, 3);
		// Handle Bottom::X
		pDrawList->AddNgonFilled(ImVec2(vCursorPos.x, oRect.Max.y + vXSize.y * 2.0f), fHandleRadius, uBlue, 4);
		if (fScaleX > fXLimit)
			pDrawList->AddLine(ImVec2(oRect.Min.x, oRect.Max.y), ImVec2(vCursorPos.x - fCursorOff, oRect.Max.y), uBlue, fBorderThickness);
		if (fScaleX < 1.0f - fXLimit)
			pDrawList->AddLine(ImVec2(oRect.Max.x, oRect.Max.y), ImVec2(vCursorPos.x + fCursorOff, oRect.Max.y), uBlue, fBorderThickness);

		ImGui::PopID();

		ImGui::Dummy(vHeightOffset);
		ImGui::Dummy(vHeightOffset);
		ImGui::Dummy(vSize);

		return bModified;
	}

	bool Slider2DInt(char const* pLabel, int* pValueX, int* pValueY, int* p_minX, int* p_maxX, int* p_minY, int* p_maxY, float const fScale)
	{
		return Slider2DScalar(pLabel, ImGuiDataType_S32, pValueX, pValueY, p_minX, p_maxX, p_minY, p_maxY, fScale);
	}

	bool Slider2DFloat(char const* pLabel, float* pValueX, float* pValueY, float* p_minX, float* p_maxX, float* p_minY, float* p_maxY, float const fScale)
	{
		return Slider2DScalar(pLabel, ImGuiDataType_Float, pValueX, pValueY, p_minX, p_maxX, p_minY, p_maxY, fScale);
	}

	bool Slider2DDouble(char const* pLabel, double* pValueX, double* pValueY, double* p_minX, double* p_maxX, double* p_minY, double* p_maxY, float const fScale)
	{
		return Slider2DScalar(pLabel, ImGuiDataType_Double, pValueX, pValueY, p_minX, p_maxX, p_minY, p_maxY, fScale);
	}

	bool SliderScalar3D(char const* pLabel, float* pValueX, float* pValueY, float* pValueZ, float const fMinX, float const fMaxX, float const fMinY, float const fMaxY, float const fMinZ, float const fMaxZ, float const fScale /*= 1.0f*/)
	{
		assert(fMinX < fMaxX);
		assert(fMinY < fMaxY);
		assert(fMinZ < fMaxZ);

		ImGuiID const iID = ImGui::GetID(pLabel);

		ImVec2 const vSizeSubstract = ImGui::CalcTextSize(std::to_string(1.0f).c_str()) * 1.1f;

		float const vSizeFull = ImGui::GetWindowContentRegionWidth();
		float const fMinSize = (vSizeFull - vSizeSubstract.x * 0.5f) * fScale * 0.75f;
		ImVec2 const vSize(fMinSize, fMinSize);

		float const fHeightOffset = ImGui::GetTextLineHeight();
		ImVec2 const vHeightOffset(0.0f, fHeightOffset);

		ImVec2 vPos = ImGui::GetCursorScreenPos();
		ImRect oRect(vPos + vHeightOffset, vPos + vSize + vHeightOffset);

		ImGui::Text(pLabel);

		ImGui::PushID(iID);

		ImU32 const uFrameCol = ImGui::GetColorU32(ImGuiCol_FrameBg) | 0xFF000000;
		ImU32 const uFrameCol2 = ImGui::GetColorU32(ImGuiCol_FrameBgActive);

		float& fX = *pValueX;
		float& fY = *pValueY;
		float& fZ = *pValueZ;

		float const fDeltaX = fMaxX - fMinX;
		float const fDeltaY = fMaxY - fMinY;
		float const fDeltaZ = fMaxZ - fMinZ;

		ImVec2 const vOriginPos = ImGui::GetCursorScreenPos();

		ImDrawList* pDrawList = ImGui::GetWindowDrawList();

		float const fX3 = vSize.x / 3.0f;
		float const fY3 = vSize.y / 3.0f;

		ImVec2 const vStart = oRect.Min;

		ImVec2 aPositions[] = {
			ImVec2(vStart.x,			vStart.y + fX3),
			ImVec2(vStart.x,			vStart.y + vSize.y),
			ImVec2(vStart.x + 2.0f * fX3,	vStart.y + vSize.y),
			ImVec2(vStart.x + vSize.x,	vStart.y + 2.0f * fY3),
			ImVec2(vStart.x + vSize.x,	vStart.y),
			ImVec2(vStart.x + fX3,		vStart.y)
		};

		pDrawList->AddPolyline(&aPositions[0], 6, uFrameCol2, true, 1.0f);

		// Cube Shape
		pDrawList->AddLine(
			oRect.Min + ImVec2(0.0f, vSize.y),
			oRect.Min + ImVec2(fX3, 2.0f * fY3), uFrameCol2, 1.0f);
		pDrawList->AddLine(
			oRect.Min + ImVec2(fX3, 2.0f * fY3),
			oRect.Min + ImVec2(vSize.x, 2.0f * fY3), uFrameCol2, 1.0f);
		pDrawList->AddLine(
			oRect.Min + ImVec2(fX3, 0.0f),
			oRect.Min + ImVec2(fX3, 2.0f * fY3), uFrameCol2, 1.0f);

		ImGui::PopID();

		constexpr float fDragZOffsetX = 64.0f;

		ImRect oZDragRect(ImVec2(vStart.x + 2.0f * fX3 + fDragZOffsetX, vStart.y + 2.0f * fY3), ImVec2(vStart.x + vSize.x + fDragZOffsetX, vStart.y + vSize.y));

		ImVec2 const vMousePos = ImGui::GetMousePos();
		ImVec2 const vSecurity(15.0f, 15.0f);
		ImVec2 const vDragStart(oZDragRect.Min.x, oZDragRect.Max.y);
		ImVec2 const vDragEnd(oZDragRect.Max.x, oZDragRect.Min.y);
		ImRect frame_bb = ImRect(oRect.Min - vSecurity, oRect.Max + vSecurity);
		bool bModified = false;
		bool hovered;
		bool held;
		bool pressed = ImGui::ButtonBehavior(oZDragRect, ImGui::GetID("##HandleZ"), &hovered, &held);
		if (hovered && held)
		{
			if (DistToSegmentSqr(vMousePos, vDragStart, vDragEnd) < 100.0f) // 100 is arbitrary threshold
			{
				float const fMaxDist = ImSqrt(Dist2(vDragStart, vDragEnd));
				float const fDist = ImSaturate(ImSqrt(DistOnSegmentSqr(vMousePos, vDragStart, vDragEnd)) / fMaxDist);

				fZ = fDist * fDeltaZ * fDist + fMinZ;

				bModified = true;
			}
		}

		float const fScaleZ = (fZ - fMinZ) / fDeltaZ;

		ImVec2 const vRectStart(vStart.x, vStart.y + fX3);
		ImVec2 const vRectEnd(vStart.x + fX3, vStart.y);
		ImRect const oXYDrag((vRectEnd - vRectStart) * fScaleZ + vRectStart,
							 (vRectEnd - vRectStart) * fScaleZ + vRectStart + ImVec2(2.0f * fX3, 2.0f * fY3));
		//if (ImGui::IsMouseHoveringRect(oXYDrag.Min - vSecurity, oXYDrag.Max + vSecurity) && ImGui::IsMouseDown(ImGuiMouseButton_Left))
		pressed = ImGui::ButtonBehavior(oXYDrag, ImGui::GetID("##Zone"), &hovered, &held);
		if (hovered && held)
		{
			ImVec2 const vLocalPos = ImGui::GetMousePos() - oXYDrag.Min;

			fX = vLocalPos.x / (oXYDrag.Max.x - oXYDrag.Min.x) * fDeltaX + fMinX;
			fY = fDeltaY - vLocalPos.y / (oXYDrag.Max.y - oXYDrag.Min.y) * fDeltaY + fMinY;

			bModified = true;
		}

		fX = ImClamp(fX, fMinX, fMaxX);
		fY = ImClamp(fY, fMinY, fMaxY);
		fZ = ImClamp(fZ, fMinZ, fMaxZ);

		float const fScaleX = (fX - fMinX) / fDeltaX;
		float const fScaleY = 1.0f - (fY - fMinY) / fDeltaY;

		ImVec4 const vBlue(70.0f / 255.0f, 102.0f / 255.0f, 230.0f / 255.0f, 1.0f);
		ImVec4 const vOrange(255.0f / 255.0f, 128.0f / 255.0f, 64.0f / 255.0f, 1.0f);

		ImS32 const uBlue = ImGui::GetColorU32(vBlue);
		ImS32 const uOrange = ImGui::GetColorU32(vOrange);

		constexpr float fBorderThickness = 2.0f; // TODO: move as Style
		constexpr float fLineThickness = 3.0f; // TODO: move as Style
		constexpr float fHandleRadius = 7.0f; // TODO: move as Style
		constexpr float fHandleOffsetCoef = 2.0f; // TODO: move as Style

		pDrawList->AddLine(
			vDragStart,
			vDragEnd, uFrameCol2, 1.0f);
		pDrawList->AddRectFilled(
			oXYDrag.Min, oXYDrag.Max, uFrameCol);

		constexpr float fCursorOff = 10.0f;
		float const fXLimit = fCursorOff / oXYDrag.GetWidth();
		float const fYLimit = fCursorOff / oXYDrag.GetHeight();
		float const fZLimit = fCursorOff / oXYDrag.GetWidth();

		char pBufferX[16];
		char pBufferY[16];
		char pBufferZ[16];
		ImFormatString(pBufferX, IM_ARRAYSIZE(pBufferX), "%.5f", *(float const*)& fX);
		ImFormatString(pBufferY, IM_ARRAYSIZE(pBufferY), "%.5f", *(float const*)& fY);
		ImFormatString(pBufferZ, IM_ARRAYSIZE(pBufferZ), "%.5f", *(float const*)& fZ);

		ImU32 const uTextCol = ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]);

		ImVec2 const vCursorPos((oXYDrag.Max.x - oXYDrag.Min.x) * fScaleX + oXYDrag.Min.x, (oXYDrag.Max.y - oXYDrag.Min.y) * fScaleY + oXYDrag.Min.y);

		ImGui::SetWindowFontScale(0.75f);

		ImVec2 const vXSize = ImGui::CalcTextSize(pBufferX);
		ImVec2 const vYSize = ImGui::CalcTextSize(pBufferY);
		ImVec2 const vZSize = ImGui::CalcTextSize(pBufferZ);

		ImVec2 const vTextSlideXMin = oRect.Min + ImVec2(0.0f, vSize.y);
		ImVec2 const vTextSlideXMax = oRect.Min + ImVec2(2.0f * fX3, vSize.y);
		ImVec2 const vXTextPos((vTextSlideXMax - vTextSlideXMin) * fScaleX + vTextSlideXMin);

		ImVec2 const vTextSlideYMin = oRect.Min + ImVec2(vSize.x, 2.0f * fY3);
		ImVec2 const vTextSlideYMax = oRect.Min + ImVec2(vSize.x, 0.0f);
		ImVec2 const vYTextPos((vTextSlideYMax - vTextSlideYMin) * (1.0f - fScaleY) + vTextSlideYMin);

		ImVec2 const vTextSlideZMin = vDragStart + ImVec2(fCursorOff, fCursorOff);
		ImVec2 const vTextSlideZMax = vDragEnd + ImVec2(fCursorOff, fCursorOff);
		ImVec2 const vZTextPos((vTextSlideZMax - vTextSlideZMin) * fScaleZ + vTextSlideZMin);

		ImVec2 const vHandlePosX = vXTextPos + ImVec2(0.0f, vXSize.y + fHandleOffsetCoef * fCursorOff);
		ImVec2 const vHandlePosY = vYTextPos + ImVec2(vYSize.x + (fHandleOffsetCoef + 1.0f) * fCursorOff, 0.0f);

		ImRect handle_x_bb = ImRect(vHandlePosX - ImVec2(fHandleRadius, fHandleRadius) - vSecurity, vHandlePosX + ImVec2(fHandleRadius, fHandleRadius) + vSecurity);
		ImRect handle_y_bb = ImRect(vHandlePosY - ImVec2(fHandleRadius, fHandleRadius) - vSecurity, vHandlePosY + ImVec2(fHandleRadius, fHandleRadius) + vSecurity);
		//ImRect handle_z_bb = ImRect(vHandlePosY - ImVec2(fHandleRadius, fHandleRadius) - vSecurity, vHandlePosY + ImVec2(fHandleRadius, fHandleRadius) + vSecurity);

		//if (ImGui::IsMouseHoveringRect(vHandlePosX - ImVec2(fHandleRadius, fHandleRadius) - vSecurity, vHandlePosX + ImVec2(fHandleRadius, fHandleRadius) + vSecurity) &&
		//	ImGui::IsMouseDown(ImGuiMouseButton_Left))
		pressed = ImGui::ButtonBehavior(handle_x_bb, ImGui::GetID("##HandleX"), &hovered, &held);
		if (hovered && held)
		{
			float const fCursorPosX = ImGui::GetMousePos().x - vStart.x;

			fX = fDeltaX * fCursorPosX / (2.0f * fX3) + fMinX;

			bModified = true;
		}
		//else if (ImGui::IsMouseHoveringRect(vHandlePosY - ImVec2(fHandleRadius, fHandleRadius) - vSecurity, vHandlePosY + ImVec2(fHandleRadius, fHandleRadius) + vSecurity) &&
		//	ImGui::IsMouseDown(ImGuiMouseButton_Left))
		pressed = ImGui::ButtonBehavior(handle_y_bb, ImGui::GetID("##HandleY"), &hovered, &held);
		if (hovered && held)
		{
			float const fCursorPosY = ImGui::GetMousePos().y - vStart.y;

			fY = fDeltaY * (1.0f - fCursorPosY / (2.0f * fY3)) + fMinY;

			bModified = true;
		}

		pDrawList->AddText(
			ImVec2(
				ImMin(ImMax(vXTextPos.x - vXSize.x * 0.5f, vTextSlideXMin.x), vTextSlideXMax.x - vXSize.x),
				vXTextPos.y + fCursorOff),
			uTextCol,
			pBufferX);
		pDrawList->AddText(
			ImVec2(
				vYTextPos.x + fCursorOff,
				ImMin(ImMax(vYTextPos.y - vYSize.y * 0.5f, vTextSlideYMax.y), vTextSlideYMin.y - vYSize.y)),
			uTextCol,
			pBufferY);
		pDrawList->AddText(
			vZTextPos,
			uTextCol,
			pBufferZ);
		ImGui::SetWindowFontScale(1.0f);

		// Handles
		pDrawList->AddNgonFilled(vHandlePosX, fHandleRadius, uBlue, 4);
		pDrawList->AddNgonFilled(vHandlePosY, fHandleRadius, uBlue, 4);

		// Vertical Line
		if (fScaleY > 2.0f * fYLimit)
			pDrawList->AddLine(ImVec2(vCursorPos.x, oXYDrag.Min.y + fCursorOff), ImVec2(vCursorPos.x, vCursorPos.y - fCursorOff), uOrange, fLineThickness);
		if (fScaleY < 1.0f - 2.0f * fYLimit)
			pDrawList->AddLine(ImVec2(vCursorPos.x, oXYDrag.Max.y - fCursorOff), ImVec2(vCursorPos.x, vCursorPos.y + fCursorOff), uOrange, fLineThickness);

		// Horizontal Line
		if (fScaleX > 2.0f * fXLimit)
			pDrawList->AddLine(ImVec2(oXYDrag.Min.x + fCursorOff, vCursorPos.y), ImVec2(vCursorPos.x - fCursorOff, vCursorPos.y), uOrange, fLineThickness);
		if (fScaleX < 1.0f - 2.0f * fYLimit)
			pDrawList->AddLine(ImVec2(oXYDrag.Max.x - fCursorOff, vCursorPos.y), ImVec2(vCursorPos.x + fCursorOff, vCursorPos.y), uOrange, fLineThickness);

		// Line To Text
		// X
		if (fScaleZ > 2.0f * fZLimit)
			pDrawList->AddLine(
				ImVec2(vCursorPos.x - 0.5f * fCursorOff, oXYDrag.Max.y + 0.5f * fCursorOff),
				ImVec2(vXTextPos.x + 0.5f * fCursorOff, vXTextPos.y - 0.5f * fCursorOff), uOrange, fLineThickness
			);
		else
			pDrawList->AddLine(
				ImVec2(vCursorPos.x, oXYDrag.Max.y),
				ImVec2(vXTextPos.x, vXTextPos.y), uOrange, 1.0f
			);
		pDrawList->AddCircleFilled(vXTextPos, 2.0f, uOrange, 3);
		// Y
		if (fScaleZ < 1.0f - 2.0f * fZLimit)
			pDrawList->AddLine(
				ImVec2(oXYDrag.Max.x + 0.5f * fCursorOff, vCursorPos.y - 0.5f * fCursorOff),
				ImVec2(vYTextPos.x - 0.5f * fCursorOff, vYTextPos.y + 0.5f * fCursorOff), uOrange, fLineThickness
			);
		else
			pDrawList->AddLine(
				ImVec2(oXYDrag.Max.x, vCursorPos.y),
				ImVec2(vYTextPos.x, vYTextPos.y), uOrange, 1.0f
			);
		pDrawList->AddCircleFilled(vYTextPos, 2.0f, uOrange, 3);

		// Borders::Right
		pDrawList->AddCircleFilled(ImVec2(oXYDrag.Max.x, vCursorPos.y), 2.0f, uOrange, 3);
		if (fScaleY > fYLimit)
			pDrawList->AddLine(ImVec2(oXYDrag.Max.x, oXYDrag.Min.y), ImVec2(oXYDrag.Max.x, vCursorPos.y - fCursorOff), uBlue, fBorderThickness);
		if (fScaleY < 1.0f - fYLimit)
			pDrawList->AddLine(ImVec2(oXYDrag.Max.x, oXYDrag.Max.y), ImVec2(oXYDrag.Max.x, vCursorPos.y + fCursorOff), uBlue, fBorderThickness);
		// Borders::Top
		pDrawList->AddCircleFilled(ImVec2(vCursorPos.x, oXYDrag.Min.y), 2.0f, uOrange, 3);
		if (fScaleX > fXLimit)
			pDrawList->AddLine(ImVec2(oXYDrag.Min.x, oXYDrag.Min.y), ImVec2(vCursorPos.x - fCursorOff, oXYDrag.Min.y), uBlue, fBorderThickness);
		if (fScaleX < 1.0f - fXLimit)
			pDrawList->AddLine(ImVec2(oXYDrag.Max.x, oXYDrag.Min.y), ImVec2(vCursorPos.x + fCursorOff, oXYDrag.Min.y), uBlue, fBorderThickness);
		// Borders::Left
		pDrawList->AddCircleFilled(ImVec2(oXYDrag.Min.x, vCursorPos.y), 2.0f, uOrange, 3);
		if (fScaleY > fYLimit)
			pDrawList->AddLine(ImVec2(oXYDrag.Min.x, oXYDrag.Min.y), ImVec2(oXYDrag.Min.x, vCursorPos.y - fCursorOff), uBlue, fBorderThickness);
		if (fScaleY < 1.0f - fYLimit)
			pDrawList->AddLine(ImVec2(oXYDrag.Min.x, oXYDrag.Max.y), ImVec2(oXYDrag.Min.x, vCursorPos.y + fCursorOff), uBlue, fBorderThickness);
		// Borders::Bottom
		pDrawList->AddCircleFilled(ImVec2(vCursorPos.x, oXYDrag.Max.y), 2.0f, uOrange, 3);
		if (fScaleX > fXLimit)
			pDrawList->AddLine(ImVec2(oXYDrag.Min.x, oXYDrag.Max.y), ImVec2(vCursorPos.x - fCursorOff, oXYDrag.Max.y), uBlue, fBorderThickness);
		if (fScaleX < 1.0f - fXLimit)
			pDrawList->AddLine(ImVec2(oXYDrag.Max.x, oXYDrag.Max.y), ImVec2(vCursorPos.x + fCursorOff, oXYDrag.Max.y), uBlue, fBorderThickness);

		pDrawList->AddLine(
			oRect.Min + ImVec2(0.0f, fY3),
			oRect.Min + ImVec2(2.0f * fX3, fY3), uFrameCol2, 1.0f);
		pDrawList->AddLine(
			oRect.Min + ImVec2(2.0f * fX3, fY3),
			oRect.Min + ImVec2(vSize.x, 0.0f), uFrameCol2, 1.0f);
		pDrawList->AddLine(
			oRect.Min + ImVec2(2.0f * fX3, fY3),
			oRect.Min + ImVec2(2.0f * fX3, vSize.y), uFrameCol2, 1.0f);

		// Cursor
		pDrawList->AddCircleFilled(vCursorPos, 5.0f, uBlue, 16);
		// CursorZ
		pDrawList->AddNgonFilled((vDragEnd - vDragStart) * fScaleZ + vDragStart, fHandleRadius, uBlue, 4);

		ImGui::Dummy(vHeightOffset);
		ImGui::Dummy(vHeightOffset * 1.25f);
		ImGui::Dummy(vSize);

		return bModified;
	}

	//////////////////////////////////////////////////////////////////////////
	// External
	//////////////////////////////////////////////////////////////////////////
	static ImVector<ImRect> s_GroupPanelLabelStack;

	void BeginGroupPanel(const char* name, const ImVec2& size)
	{
		ImGui::BeginGroup();

		auto cursorPos = ImGui::GetCursorScreenPos();
		auto itemSpacing = ImGui::GetStyle().ItemSpacing;
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

		auto frameHeight = ImGui::GetFrameHeight();
		ImGui::BeginGroup();

		ImVec2 effectiveSize = size;
		if (size.x < 0.0f)
			effectiveSize.x = ImGui::GetContentRegionAvailWidth();
		else
			effectiveSize.x = size.x;
		ImGui::Dummy(ImVec2(effectiveSize.x, 0.0f));

		ImGui::Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::BeginGroup();
		ImGui::Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::TextUnformatted(name);
		auto labelMin = ImGui::GetItemRectMin();
		auto labelMax = ImGui::GetItemRectMax();
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Dummy(ImVec2(0.0, frameHeight + itemSpacing.y));
		ImGui::BeginGroup();

		//ImGui::GetWindowDrawList()->AddRect(labelMin, labelMax, IM_COL32(255, 0, 255, 255));

		ImGui::PopStyleVar(2);

#if IMGUI_VERSION_NUM >= 17301
		ImGui::GetCurrentWindow()->ContentRegionRect.Max.x -= frameHeight * 0.5f;
		ImGui::GetCurrentWindow()->WorkRect.Max.x -= frameHeight * 0.5f;
		ImGui::GetCurrentWindow()->InnerRect.Max.x -= frameHeight * 0.5f;
#else
		ImGui::GetCurrentWindow()->ContentsRegionRect.Max.x -= frameHeight * 0.5f;
#endif
		ImGui::GetCurrentWindow()->Size.x -= frameHeight;

		auto itemWidth = ImGui::CalcItemWidth();
		ImGui::PushItemWidth(ImMax(0.0f, itemWidth - frameHeight));

		s_GroupPanelLabelStack.push_back(ImRect(labelMin, labelMax));
	}

	void EndGroupPanel()
	{
		ImGui::PopItemWidth();

		auto itemSpacing = ImGui::GetStyle().ItemSpacing;

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

		auto frameHeight = ImGui::GetFrameHeight();

		ImGui::EndGroup();

		//ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(0, 255, 0, 64), 4.0f);

		ImGui::EndGroup();

		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
		ImGui::Dummy(ImVec2(0.0, frameHeight - frameHeight * 0.5f - itemSpacing.y));

		ImGui::EndGroup();

		auto itemMin = ImGui::GetItemRectMin();
		auto itemMax = ImGui::GetItemRectMax();
		//ImGui::GetWindowDrawList()->AddRectFilled(itemMin, itemMax, IM_COL32(255, 0, 0, 64), 4.0f);

		auto labelRect = s_GroupPanelLabelStack.back();
		s_GroupPanelLabelStack.pop_back();

		ImVec2 halfFrame = ImVec2(frameHeight * 0.25f, frameHeight) * 0.5f;
		ImRect frameRect = ImRect(itemMin + halfFrame, itemMax - ImVec2(halfFrame.x, 0.0f));
		labelRect.Min.x -= itemSpacing.x;
		labelRect.Max.x += itemSpacing.x;
		for (int i = 0; i < 4; ++i)
		{
			switch (i)
			{
				// left half-plane
			case 0: ImGui::PushClipRect(ImVec2(-FLT_MAX, -FLT_MAX), ImVec2(labelRect.Min.x, FLT_MAX), true); break;
				// right half-plane
			case 1: ImGui::PushClipRect(ImVec2(labelRect.Max.x, -FLT_MAX), ImVec2(FLT_MAX, FLT_MAX), true); break;
				// top
			case 2: ImGui::PushClipRect(ImVec2(labelRect.Min.x, -FLT_MAX), ImVec2(labelRect.Max.x, labelRect.Min.y), true); break;
				// bottom
			case 3: ImGui::PushClipRect(ImVec2(labelRect.Min.x, labelRect.Max.y), ImVec2(labelRect.Max.x, FLT_MAX), true); break;
			}

			ImGui::GetWindowDrawList()->AddRect(
				frameRect.Min, frameRect.Max,
				ImColor(ImGui::GetStyleColorVec4(ImGuiCol_Border)),
				halfFrame.x);

			ImGui::PopClipRect();
		}

		ImGui::PopStyleVar(2);

#if IMGUI_VERSION_NUM >= 17301
		ImGui::GetCurrentWindow()->ContentRegionRect.Max.x += frameHeight * 0.5f;
		ImGui::GetCurrentWindow()->WorkRect.Max.x += frameHeight * 0.5f;
		ImGui::GetCurrentWindow()->InnerRect.Max.x += frameHeight * 0.5f;
#else
		ImGui::GetCurrentWindow()->ContentsRegionRect.Max.x += frameHeight * 0.5f;
#endif
		ImGui::GetCurrentWindow()->Size.x += frameHeight;

		ImGui::Dummy(ImVec2(0.0f, 0.0f));

		ImGui::EndGroup();
	}
}