/** vim: set ts=4 sw=4 et tw=99:
 *
 * === Stripper for Metamod:Source ===
 * Copyright (C) 2005-2009 David "BAILOPAN" Anderson
 * No warranties of any kind.
 * Based on the original concept of Stripper2 by botman
 *
 * License: see LICENSE.TXT
 * ===================================
 */

#pragma once

#include <string>
#include <vector>

#ifndef _INCLUDE_STRIPPER_INTERCOM_H_
#define _INCLUDE_STRIPPER_INTERCOM_H_

namespace StripperSupport {
    extern const char* parse_map(const char* map, const char* entities);
    extern std::vector<std::string> AppliedFiles;
}

#endif /* _INCLUDE_STRIPPER_INTERCOM_H_ */