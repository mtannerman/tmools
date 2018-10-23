#pragma once

#include "logging.h"

#define THROW(exceptionType, message) \
	LOG("\n\t" << exceptionType::Type() << "\n" <<\
		'\t' << "File: " << __FILE__ << "\n" <<\
		'\t' << "Line: " << __LINE__ << "\n" <<\
		'\t' << "Function: " << __FUNCTION__ << "\n" <<\
		'\t' << "Message: " << message);\
	throw exceptionType(message, __FUNCTION__, __FILE__, __LINE__); 

#define ASSERT(expression, message) if (!(expression)) { THROW(::tmools::Assertion, STR(#expression << message)); }
#define TEST_ASSERT(expression, doLog) if (!(expression)) { THROW(::tmools::TestAssertion, STR(__FUNCTION__ << __LINE__<< " FAILED")); } else if ((doLog)) { LOG(__FUNCTION__ << " PASSED"); }
#define ASSERT_THROWN_EXCEPTION(command, exceptionType, message) { try { command; }\
 	catch (const exceptionType& ex) { LOG(__FUNCTION__ << " PASSED"); }\
	catch(...) { THROW(::tmools::TestAssertion, message); }}

#define THROW_IF(expression, exceptionType, message) if ((expression)) { THROW(exceptionType, message); }

#if _WIN32
#	define NOEXCEPT
#elif __GNUG__
#	define NOEXCEPT noexcept
#endif

namespace tmools
{

class RuntimeException
{
public:
	RuntimeException(const std::string& message, const std::string& function,
		const std::string& file, int line);
	virtual ~RuntimeException() NOEXCEPT {}
protected:
	std::string message;
	std::string function;
	std::string file;
	int line;
};

class Assertion : public RuntimeException
{
public:
	Assertion(const std::string& message, const std::string& function,
		const std::string& file, int line);

	static std::string Type() NOEXCEPT;
};

class TestAssertion : public RuntimeException
{
public:
	TestAssertion(const std::string& message, const std::string& function,
		const std::string& file, int line);

	static std::string Type() NOEXCEPT;
};

class BadFunctionInput : public RuntimeException
{
public:
	BadFunctionInput(const std::string& message, const std::string& function,
		const std::string& file, int line);

	static std::string Type() NOEXCEPT;
};

class BadProgramInput : public RuntimeException
{
public:
	BadProgramInput(const std::string& message, const std::string& function,
		const std::string& file, int line);

	static std::string Type() NOEXCEPT;
};

class UnreachableCode : public RuntimeException
{
public:
	UnreachableCode(const std::string& message, const std::string& function,
		const std::string& file, int line);

	static std::string Type() NOEXCEPT;
};

class IndexError : public RuntimeException
{
public:
	IndexError(const std::string& message, const std::string& function,
		const std::string& file, int line);

	static std::string Type() NOEXCEPT;
};

class SizeMismatch : public RuntimeException
{
public:
	SizeMismatch(const std::string& message, const std::string& function,
		const std::string& file, int line);

	static std::string Type() NOEXCEPT;
};

class FileOperationFailure : public RuntimeException
{
public:
	FileOperationFailure(const std::string& message, const std::string& function,
		const std::string& file, int line);
	static std::string Type() NOEXCEPT;
};

class UnImplementedFeature : public RuntimeException
{
public:
	UnImplementedFeature(const std::string& message, const std::string& function,
		const std::string& file, int line);

	static std::string Type() NOEXCEPT;
};


}   // namespace tmools
