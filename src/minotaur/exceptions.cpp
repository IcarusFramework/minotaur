
#include <minotaur/exceptions.h>

minotaur::exception::exception(const std::string &message, std::exception *cause)
	: std::exception(), _message(message), _cause(cause)
{ }

minotaur::exception::exception(const std::string &message)
	: exception(message, NULL)
{ }

const char *minotaur::exception::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT
{
	return this->_message.c_str();
}

const std::string minotaur::exception::message()
{
	return this->_message;
}

std::exception *minotaur::exception::cause() const
{
	return this->_cause;
}

minotaur::compiler_exception::compiler_exception(
	const unsigned int line, const std::string &message, std::exception *cause
) : minotaur::exception(message, cause), _line(line)
{ }

minotaur::compiler_exception::compiler_exception(const unsigned int line, const std::string &message)
	: compiler_exception(line, message, NULL)

{ }

unsigned int minotaur::compiler_exception::line() const
{
	return this->_line;
}

minotaur::premature_eof::premature_eof(unsigned int line)
	: compiler_exception(line, "Premature end of file.")
{ }

minotaur::premature_eof::premature_eof()
	: premature_eof(0)
{ }

minotaur::open_file_error::open_file_error(const std::string &message)
	: exception(message)
{ }
