// (assert\assert.h) This file is part of BLAF Debug module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifndef BLAFDEBUG_ASSERT_ASSERT_H
#define BLAFDEBUG_ASSERT_ASSERT_H

// Auto-define
#ifdef _DEBUG
#define BLAF_ASSERTS_ENABLED
#endif

#ifdef BLAF_ASSERTS_ENABLED
#define BLAF_ASSERT(x, ...) { if(!(x)) {std::cerr << "ASSERTION FAILED: " << __VA_ARGS__ << std::endl; __debugbreak(); } }
#else
#define BLAF_ASSERT(x, ...)
#endif

#endif
