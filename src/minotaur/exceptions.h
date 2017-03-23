/*
 * @author Jamillo Santos <jamillo@gmail.com>
 * @date August 19, 2015
 */

#ifndef MINOTAUR_COMPILER_EXCEPTIONS_HPP
#define MINOTAUR_COMPILER_EXCEPTIONS_HPP

#include <string>
#include <exception>

namespace minotaur
{
	class exception
		: public std::exception
	{
	private:
		std::string _message;
		std::exception *_cause;
	public:
		exception(const std::string &message, std::exception *cause);

		exception(const std::string &message);

		const std::string message();

		std::exception *cause() const;

		const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override;
	};

	class open_file_error
		: public exception
	{
	public:
		open_file_error(const std::string &message);
	};

	class compiler_exception
		: public exception
	{
	private:
		unsigned int _line;
	public:
		compiler_exception(const unsigned int line, const std::string &message, std::exception *cause);

		compiler_exception(const unsigned int line, const std::string &message);

		unsigned int line() const;
	};

	class premature_eof
		: public compiler_exception
	{
	public:
		premature_eof();
		premature_eof(unsigned int line);
	};
}


#endif // MINOTAUR_COMPILER_EXCEPTIONS_HPP
