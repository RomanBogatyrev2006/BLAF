// (core\core.h) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifndef BLAFCORE_CORE_CORE_H
#define BLAFCORE_CORE_CORE_H

#if defined(BLAF_TARGET_WINDOWS)
	#ifdef _DEBUG
		#define BLAF_InitializeString "Barely Lightweight Application Framework (BLAF)\n           -> VERSION: 0.0.0 Debug\n           -> GITHUB LINK: https://github.com/RomanBogatyrev2006/BLAF\n           -> PLATFORM: Windows"
	#else
		#define BLAF_InitializeString "Barely Lightweight Application Framework (BLAF)\n           -> VERSION: 0.0.0 Release\n           -> GITHUB LINK: https://github.com/RomanBogatyrev2006/BLAF\n           -> PLATFORM: Windows"
	#endif
#endif

#if defined(BLAF_TARGET_UNIX)
	#ifdef _DEBUG
		#define BLAF_InitializeString "Barely Lightweight Application Framework (BLAF)\n           -> VERSION: 0.0.0 Debug\n           -> GITHUB LINK: https://github.com/RomanBogatyrev2006/BLAF\n           -> PLATFORM: Unix/Linux"
	#else
		#define BLAF_InitializeString "Barely Lightweight Application Framework (BLAF)\n           -> VERSION: 0.0.0 Release\n           -> GITHUB LINK: https://github.com/RomanBogatyrev2006/BLAF\n           -> PLATFORM: Unix/Linux"
	#endif
#endif

#endif