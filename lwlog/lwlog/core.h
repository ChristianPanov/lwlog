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

#ifndef LWLOG
	#ifdef LWLOG_PLATFORM_WINDOWS
		#if defined(LWLOG_BUILD_DLL)
			#define LWLOG __declspec(dllexport)
		#elif !defined(LWLOG_BUILD_STATIC)
			#define LWLOG __declspec(dllimport)
		#else
			#define LWLOG
		#endif
	#else
		#if __GNUC__ >= 4
			#define LWLOG __attribute__((visibility("default")))
		#else
			#define LWLOG
		#endif
	#endif
#endif

