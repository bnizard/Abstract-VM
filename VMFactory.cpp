#include "VMFactory.hpp"
#include <iostream>
#include "Exception.hpp"
#include "Calculator.hpp"
#include "IOperand.hpp"
#include <math.h>
 
VMFactory::VMFactory()
{
	_tab[Int8] 	 = 	&VMFactory::createInt8;
	_tab[Int16]  = 	&VMFactory::createInt16;
	_tab[Int32]  = 	&VMFactory::createInt32;
	_tab[Float]  = 	&VMFactory::createFloat;
	_tab[Double] = 	&VMFactory::createDouble;

	_instruction["push"]   = &VMFactory::push;
	_instruction["pop"]    = &VMFactory::pop;
	_instruction["dump"]   = &VMFactory::dump;
	_instruction["assert"] = &VMFactory::assert;
	_instruction["add"]    = &VMFactory::add;
	_instruction["sub"]    = &VMFactory::sub;
	_instruction["mul"]    = &VMFactory::mul;
	_instruction["div"]    = &VMFactory::div;
	_instruction["mod"]    = &VMFactory::mod;
	_instruction["print"]  = &VMFactory::print;
	_instruction["exit"]   = &VMFactory::exit;
	_instruction["sin"]   = &VMFactory::bsin;
	_instruction["cos"]   = &VMFactory::bcos;
	_instruction["tan"]   = &VMFactory::btan;
	_instruction["mid"]   = &VMFactory::bmoy;
	_instruction["max"]   = &VMFactory::bmax;
	_instruction["min"]   = &VMFactory::bmin;
}

void VMFactory::bsin(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;

	if (_stack.empty())
		throw EMPTYSTACKException("Erreur sin sur une stack vide");
	std::cout << std::to_string(sin(stod((**_stack.begin()).toString()))) << std::endl;
}

void VMFactory::bcos(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;

	if (_stack.empty())
		throw EMPTYSTACKException("Erreur cos sur une stack vide");
	std::cout << std::to_string(cos(stod((**_stack.begin()).toString()))) << std::endl;
}

void VMFactory::btan(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;

	if (_stack.empty())
		throw EMPTYSTACKException("Erreur tan sur une stack vide");
	std::cout << std::to_string(tan(stod((**_stack.begin()).toString()))) << std::endl;
}

void VMFactory::bmoy(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	double middle = 0;

	if (_stack.empty())
		throw EMPTYSTACKException("Erreur mid sur une stack vide");
	std::list<const IOperand*>::iterator p = _stack.begin();
	while (p != _stack.end())
		middle += stod((*p++)->toString());
	std::cout << std::to_string(middle / _stack.size()) << std::endl;
}

void VMFactory::bmax(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	double max = 0;

	if (_stack.empty())
		throw EMPTYSTACKException("Erreur max sur une stack vide");
	std::list<const IOperand*>::iterator p = _stack.begin();
	max = stod((**_stack.begin()).toString());
	while (p != _stack.end())
	{
		if (max < stod((*p)->toString()))
			max = stod((*p)->toString());
		p++;
	}
	std::cout << std::to_string(max) << std::endl;
}

void VMFactory::bmin(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	double min = 0;

	if (_stack.empty())
		throw EMPTYSTACKException("Erreur min sur une stack vide");
	std::list<const IOperand*>::iterator p = _stack.begin();
	min = stod((**_stack.begin()).toString());
	while (p != _stack.end())
	{
		if (min > stod((*p)->toString()))
			min = stod((*p)->toString());
		p++;
	}
	std::cout << std::to_string(min) << std::endl;
}

void VMFactory::push(eOperandType type, std::string const & value)
{
	const IOperand *result = createOperand(type, value);
	_stack.push_front(result);
}

void VMFactory::pop(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	if (_stack.empty())
		throw EMPTYSTACKException("Erreur pop sur une stack vide");
	_stack.erase(_stack.begin());
}

void VMFactory::dump(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	while (p != _stack.end())
		std::cout << (*p++)->toString() << std::endl;
}

void VMFactory::assert(eOperandType type, std::string const & value)
{
	std::list<const IOperand*>::iterator p = _stack.begin();

	if (type != (*p)->getType())
		throw DIFFERENTTYPEException("Erreur asset sur des types différents");
	if (stod(value) != stod((*p)->toString()))
		throw DIFFERENTVALUEException("Erreur asset sur des valeurs différentes");
}

void VMFactory::add(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	IOperand const *result;

	if (_stack.size() < 2)
		throw EMPTYVALUESTACKException("Erreur operation sur une stack qui ne contient pas au moins 2 élements");
	result = **(++p) + **(--p);
	g_e.pop(Int8, "");
	g_e.pop(Int8, "");
	_stack.push_front(result);
}

void VMFactory::sub(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	IOperand const *result;

	if (_stack.size() < 2)
		throw EMPTYVALUESTACKException("Erreur operation sur une stack qui ne contient pas au moins 2 élements");
	result = **(++p) - **(--p);
	g_e.pop(Int8, "");
	g_e.pop(Int8, "");
	_stack.push_front(result);
}

void VMFactory::mul(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	IOperand const *result;

	if (_stack.size() < 2)
		throw EMPTYVALUESTACKException("Erreur operation sur une stack qui ne contient pas au moins 2 élements");
	result = **(++p) * **(--p);
	g_e.pop(Int8, "");
	g_e.pop(Int8, "");
	_stack.push_front(result);
}

void VMFactory::div(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	IOperand const *result;

	if (_stack.size() < 2)
		throw EMPTYVALUESTACKException("Erreur operation sur une stack qui ne contient pas au moins 2 élements");
	result =  **(++p) / **(--p);
	g_e.pop(Int8, "");
	g_e.pop(Int8, "");
	_stack.push_front(result);
}

void VMFactory::mod(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	std::list<const IOperand*>::iterator p = _stack.begin();
	IOperand const *result;

	if (_stack.size() < 2)
		throw EMPTYVALUESTACKException("Erreur operation sur une stack qui ne contient pas au moins 2 élements");
	result = **(++p) % **(--p);
	g_e.pop(Int8, "");
	g_e.pop(Int8, "");
	_stack.push_front(result);
}

void VMFactory::print(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	if ((*_stack.begin())->getType())
		throw DIFFERENTTYPEException("Print type different de int8");
	printf("%c", std::stoi((*_stack.begin())->toString()));
}

void VMFactory::exit(eOperandType type, std::string const & value)
{
	(void)value;
	(void)type;
	std::exit(0);
}

IOperand const * VMFactory::createOperand( eOperandType type, std::string const & value ) const
{
	IOperand const *result = NULL;
	result = (this->*_tab[type])(value);
	return (result);
}

IOperand const * VMFactory::createInt8( std::string const & value ) const
{
	double nb = stod(value);

	if (nb > 127)
		throw OVERFLOWException("Overflow int8");
	if (nb < -127)
		throw UNDERFLOWException("Underflow int8");
	return (new Calculator<char>((char)nb, Int8));
}

IOperand const * VMFactory::createInt16( std::string const & value ) const
{
	double nb = stod(value);

	if (nb > 32767)
		throw OVERFLOWException("Overflow int16");
	if (nb < -32768)
		throw UNDERFLOWException("Underflow int16");
	return (new Calculator<short int>((short int)nb, Int16));
}

IOperand const * VMFactory::createInt32( std::string const & value ) const
{
	double nb = stod(value);

	if (nb > 2147483647)
		throw OVERFLOWException("Overflow int32");
	if (nb < -2147483648)
		throw UNDERFLOWException("Underflow int32");
	return (new Calculator<long int>((long int)nb, Int32));
}

IOperand const * VMFactory::createFloat( std::string const & value ) const
{
	double nb = stod(value);

	if (!isfinite(nb) && nb > 0)
		throw OVERFLOWException("Overflow float");
	if (!isfinite(nb) && nb < 0)
		throw UNDERFLOWException("Underflow float");
	return (new Calculator<float>((float)nb, Float));
}

IOperand const * VMFactory::createDouble( std::string const & value ) const
{
	double nb = stod(value);

	if (!isfinite(nb) && nb > 0)
		throw OVERFLOWException("Overflow double");
	if (!isfinite(nb) && nb < 0)
		throw UNDERFLOWException("Underflow double");
	return (new Calculator<double>((double)nb, Double));
}

VMFactory::~VMFactory()
{

}

VMFactory::VMFactory(VMFactory const & src)
{
	*this = src;
}

void VMFactory::doInstruction(std::string const & instr, eOperandType type, std::string const & value)
{
	(this->*_instruction[instr])(type, value);
}

VMFactory & VMFactory::operator=(VMFactory const & rhs)
{
	if (this != &rhs)
		this->_stack = rhs.getStack();
	return (*this);
}

std::list<const IOperand *> VMFactory::getStack() const
{
	return (_stack);
}

eOperandType VMFactory::getTypeWithString(std::string type)
{
	std::string names[5] = {"Int8", "Int16", "Int32", "Float", "Double"};
	
	if (!type.compare(names[0]))
		return (Int8);
	if (!type.compare(names[1]))
		return (Int16);
	if (!type.compare(names[2]))
		return (Int32);
	if (!type.compare(names[3]))
		return (Float);
	if (!type.compare(names[4]))
		return (Double);
	return (Int8);
}