
#include <minotaur/metainfo.h>

minotaur::piece::~piece()
{ }

minotaur::content_block::content_block(const std::string &content)
	: content(content)
{ }

minotaur::code_block::code_block(const std::string &content)
	: minotaur::content_block::content_block(content)
{ }

minotaur::quick_code_block::quick_code_block(const std::string &content)
	: minotaur::content_block::content_block(content)
{ }

minotaur::group_block::group_block()
{ }

minotaur::call_code_block::call_code_block(const std::string &name, const std::string &parameters)
	: minotaur::group_block::group_block(), name(name), parameters(parameters)
{ }

void minotaur::group_block::add_piece(minotaur::piece *piece)
{
	this->pieces.emplace_back(piece);
}

minotaur::method_param::method_param()
{ }

minotaur::method_param::method_param(const std::string type, const minotaur::method_param_type attribute, const std::string name)
	: _type(type), _attribute(attribute), _name(name)
{ }

const std::string &minotaur::method_param::type() const
{
	return this->_type;
}

minotaur::method_param &minotaur::method_param::type(const std::string &type)
{
	this->_type = type;
	return *this;
}

const minotaur::method_param_type &minotaur::method_param::attribute() const
{
	return this->_attribute;
}

minotaur::method_param &minotaur::method_param::attribute(const minotaur::method_param_type &attr)
{
	this->_attribute = attr;
	return *this;
}

const std::string &minotaur::method_param::name() const
{
	return this->_name;
}

minotaur::method_param &minotaur::method_param::name(const std::string &name)
{
	this->_name = name;
	return *this;
}

minotaur::method_param &minotaur::method_param::operator=(const minotaur::method_param &param)
{
	this->_attribute = param._attribute;
	this->_name = param._name;
	this->_type = param._type;
	return *this;
}

const std::string minotaur::method_param::cpp()
{
	std::string result(this->_type);
	result += " ";
	if (this->_attribute == minotaur::method_param_type::POINTER)
		result += "*";
	else if (this->_attribute == minotaur::method_param_type::REFERENCE)
		result += "&";
	else if (this->_attribute == minotaur::method_param_type::RVALUE)
		result += "&&";
	result += this->_name;
	return result;
}


void minotaur::file_info::add_param(minotaur::method_param *param)
{
	this->parameters.emplace_back(param);
}
