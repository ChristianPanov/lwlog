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

#ifndef LWLOG_API
	#ifdef LWLOG_PLATFORM_WINDOWS
		#ifdef LWLOG_BUILD_SHARED
			#define LWLOG_API __declspec(dllexport)
		#elif !defined(LWLOG_BUILD_STATIC)
			#define LWLOG_API __declspec(dllimport)
		#else
			#define LWLOG_API
		#endif
	#endif
#endif
