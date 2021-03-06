//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Hash/Crc.hpp"

namespace CPF
{
	namespace GOM
	{
		/** @brief A result code. */
		using Result = uint32_t;
		static_assert(sizeof(Result) == 4, "Invalid result code size.");

		/**
		 * @brief Creates a result code.
		 * @param e  If the result is an error or not.
		 * @param ss The system identifier.
		 * @param v  The error code identifier.
		 * @return The result code.
		 */
		constexpr Result CreateResult(uint8_t e, uint16_t ss, uint16_t v) { return (e == 0 ? 0 : 0x80000000) | (ss & 0x7FFF) << 16 | (v&0xFFFF); }

		/**
		 * @brief Test a result code for sucess.
		 * @param result The result code to test.
		 * @return True if the result code is a non-error code.
		 */
		constexpr bool Succeeded(Result result) { return (result & 0x80000000) == 0; }

		/**
		 * @brief Test if a result code indicates an error.
		 * @param result The result code to test.
		 * @return True if the result code is a failure code.
		 */
		constexpr bool Failed(Result result) { return (result & 0x80000000) != 0; }

		constexpr uint16_t GetError(Result result) { return uint16_t((result & 0x80000000) >> 31); }
		constexpr uint16_t GetSubSystem(Result result) { return uint16_t((result & 0x7FFF0000) >> 16); }
		constexpr uint16_t GetCode(Result result) { return uint16_t(result & 0x0000ffff); }
	}
}


// Utility macro for creating result codes.
#define GOM_RESULT(e, ss, v) Cpf::GOM::CreateResult(e, ss##_crc15, v##_crc16)
