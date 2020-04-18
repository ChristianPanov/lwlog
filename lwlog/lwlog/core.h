#pragma once

#ifdef _WIN32
	#define LWLOG_PLATFORM_WINDOWS
#endif
#ifdef __linux__
	#define LWLOG_PLATFORM_LINUX
#endif
#ifdef __APPLE__
	#define LWLOG_PLATFORM_MAC
#endif

#ifdef LWLOG_PLATFORM_WINDOWS
	#ifdef LWLOG_DYNAMIC_LINK
		#ifdef LWLOG_BUILD_DLL
			#define LWLOG_API __declspec(dllexport)
		#else
			#define LWLOG_API __declspec(dllimport)
		#endif
	#else
		#define LWLOG_API
	#endif
#endif
