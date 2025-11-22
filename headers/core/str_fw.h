#pragma once
#include <iosfwd>
#include "core/export_decl.h"
class CORE String;
CORE std::ostream& operator <<(std::ostream& buf, const String& s);