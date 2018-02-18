// ----------------------------------------------------------------------------------------------------
// Copyright © 2016 - 2018 LeLe570929726. All rights reserved.
// 
// @Project: RalFlight
// @License: Licensed under GNU General Public License v3.
// @Description: A free and open-source flight simulator.
//
// @Craete: 2017/8/21 by LeLe570929726
// ----------------------------------------------------------------------------------------------------
#ifndef RALFLIGHT_SRC_CORE_STL_STRINGENCODE_H
#define RALFLIGHT_SRC_CORE_STL_STRINGENCODE_H

#include "../Global/Macro.h"
#include <string>
#include <cuchar>
#include <assert.h>
#include <malloc.h>
#if defined(RALFLIGHT_SYSTEM_WINDOWS)
	#include <Windows.h>
#elif defined(RALFLIGHT_SYSTEM_LINUX)
	#include <iconv.h>
	#include <string.h>
#endif

// Core namespace
namespace Core {

	namespace CodePage {
#if defined(RALFLIGHT_SYSTEM_WINDOWS)
		// Code page in windows reference from [MSDN](https://msdn.microsoft.com/library/windows/desktop/dd317756.aspx)
		const int UCS4 = 12000;
		const int UTF16 = 1200;
		const int UTF8 = CP_UTF8;
		const int Latin1 = 28591;
		const int GB2312 = 936;
		const int GBK = 936;
		const int GB18030 = 54936;
#elif defined(RALFLIGHT_SYSTEM_LINUX)
        const char *UCS4 = "UCS4";
		const char *UTF16 = "UTF-16";
		const char *UTF8 = "UTF-8";
		const char *GBK = "CP936";
#endif
	}

	class RALFLIGHT_API StringEncode {
	public:
		StringEncode() = delete;
		~StringEncode() = delete;
		StringEncode(const StringEncode &other) = delete;
		StringEncode &operator=(const StringEncode &other) = delete;

	public:
#if defined(RALFLIGHT_SYSTEM_WINDOWS)
		static unsigned int convertToUTF16(const std::string &source, std::u16string &contain, unsigned int codepage);
		static unsigned int convertFromUTF16(const std::u16string &source, std::string &contain, unsigned int codepage);
		static unsigned int convertToUCS4(const std::string &source, std::u32string &contain, unsigned int codepage);
		static unsigned int convertFromUCS4(const std::u32string &source, std::string &contain, unsigned int codepage);
		static unsigned int convertToWString(const std::string &source, std::wstring &contain, unsigned int codepage);
		static unsigned int convertFromWString(const std::wstring &source, std::string &contain, unsigned int codepage);
		static unsigned int convert(const std::string &source, std::string &contain, unsigned int sourceCP, unsigned int targetCP);
		static unsigned int getLocalCP();
#elif defined(RALFLIGHT_SYSTEM_LINUX)
		static unsigned int convertToUTF16(const std::string &source, std::u16string &contain, const std::string &codepage);
		static unsigned int convertFromUTF16(const std::u16string &source, std::string &contain, const std::string &codepage);
		static unsigned int convertToUCS4(const std::string &source, std::u32string &contain, const std::string &codepage);
		static unsigned int convertFromUCS4(const std::u32string &source, std::string &contain, const std::string &codepage);
		static unsigned int convertToWString(const std::string &source, std::wstring &contain, const std::string &codepage);
		static unsigned int convertFromWString(const std::wstring &source, std::string &contain, const std::string &codepage);
		static unsigned int convert(const std::string &source, std::string &contain, const std::string &sourceCP, const std::string &targetCP);
		static std::string getLocalCP();
#endif

	public:
		enum ErrorCode {
			Success = 0,
			InvalidCodePage = 1,
			InvalidString = 2
		};
	};

}

#endif		// RALFLIGHT_SRC_CORE_STL_STRINGENCODE_H