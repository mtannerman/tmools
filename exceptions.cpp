#include "exceptions.h"

namespace tmools
{

RuntimeException::RuntimeException(const std::string& message, const std::string& function,
	const std::string& file, int line)
	: message(message)
	, function(function)
	, file(file)
	, line(line)
{ }

Assertion::Assertion(const std::string& message, const std::string& function,
	const std::string& file, int line) : RuntimeException(message, function, file, line) {}

std::string Assertion::Type() NOEXCEPT {
	return "tmools::Assertion";
}

TestAssertion::TestAssertion(const std::string& message, const std::string& function,
	const std::string& file, int line) : RuntimeException(message, function, file, line) {}

std::string TestAssertion::Type() NOEXCEPT {
	return "tmools::TestAssertion";
}

BadFunctionInput::BadFunctionInput(const std::string& message, const std::string& function,
	const std::string& file, int line) : RuntimeException(message, function, file, line) {}

std::string BadFunctionInput::Type() NOEXCEPT {
	return "tmools::BadFunctionInput";
}

BadProgramInput::BadProgramInput(const std::string& message, const std::string& function,
	const std::string& file, int line) : RuntimeException(message, function, file, line) {}

std::string BadProgramInput::Type() NOEXCEPT {
	return "tmools::BadProgramInput";
}

UnreachableCode::UnreachableCode(const std::string& message, const std::string& function,
	const std::string& file, int line) : RuntimeException(message, function, file, line) {}

std::string UnreachableCode::Type() NOEXCEPT {
	return "tmools::UnreachableCode";
}

IndexError::IndexError(const std::string& message, const std::string& function,
	const std::string& file, int line) : RuntimeException(message, function, file, line) {}

std::string IndexError::Type() NOEXCEPT {
	return "tmools::IndexError";
}

SizeMismatch::SizeMismatch(const std::string& message, const std::string& function,
	const std::string& file, int line) : RuntimeException(message, function, file, line) {}

std::string SizeMismatch::Type() NOEXCEPT {
	return "tmools::SizeMismatch";
}

FileOperationFailure::FileOperationFailure(const std::string& message, const std::string& function,
	const std::string& file, int line) : RuntimeException(message, function, file, line) {}

std::string FileOperationFailure::Type() NOEXCEPT {
	return "tmools::FileOperationFailure";
}

UnImplementedFeature::UnImplementedFeature(const std::string& message, const std::string& function,
	const std::string& file, int line) : RuntimeException(message, function, file, line) {}

std::string UnImplementedFeature::Type() NOEXCEPT {
	return "tmools::UnImplementedFeature";
}

}