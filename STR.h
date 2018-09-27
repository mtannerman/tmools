#pragma once

#define STR(expression) (((::std::ostringstream *)&(::std::ostringstream() << "" << expression))->str())
