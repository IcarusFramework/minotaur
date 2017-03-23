/*
 * @author Jamillo Santos <jamillo@gmail.com>
 * @date August 17, 2015
 */

#ifndef MINOTAUR_COMPILER_METAINFO_H
#define MINOTAUR_COMPILER_METAINFO_H

#include <string>
#include <vector>
#include <memory>

namespace minotaur
{
	class piece
	{
	public:
		virtual ~piece();
	};

	class content_block
		: public piece
	{
	public:
		content_block(const std::string &content);

		std::string content;
	};

	class code_block
		: public content_block
	{
	public:
		code_block(const std::string &content);
	};

	class quick_code_block
		: public content_block
	{
	public:
		quick_code_block(const std::string &content);
	};

	class group_block
		: public piece
	{
	public:
		group_block();

		std::vector<std::unique_ptr<piece>> pieces;

		void add_piece(minotaur::piece *piece);
	};

	class call_code_block
		: public group_block
	{
	public:
		call_code_block(const std::string &name, const std::string &parameters);

		std::string name;
		std::string parameters;
	};

	/**
	 * Class that represents the parameters of a method called in a route.
	 */
	enum class method_param_type
	{
		NORMAL, REFERENCE, POINTER, RVALUE, IDENTIFIER
	};

	class method_param
	{
	private:
		std::string _type;
		method_param_type _attribute;
		std::string _name;
	public:

		method_param(const std::string type, const method_param_type attribute, const std::string name);
		method_param();


		const std::string &type() const;

		method_param &type(const std::string &type);

		const method_param_type &attribute() const;

		method_param &attribute(const method_param_type &attr);

		const std::string &name() const;

		method_param &name(const std::string &name);

		method_param &operator=(const method_param &param);

		const std::string cpp();
	};

	class file_info
		: public group_block
	{
	public:
		std::vector<std::unique_ptr<method_param>> parameters;

		std::string path;
		std::string fullPath;

		std::vector<std::string> package;

		std::string name;
		std::string subextension;
		std::string extension;

		size_t size;
		size_t lines;
		std::string parameters_str;

		void add_param(method_param *param);
	};
}

#endif //MINOTAUR_COMPILER_METAINFO_H
