#ifndef CALCULATOR_HPP
# define CALCULATOR_HPP

#include "VMFactory.hpp"
#include "IOperand.hpp"

extern VMFactory g_e;

template <typename T>
class Calculator : public IOperand
{
	public: 
		int getPrecision( void ) const
		{
			return _precision;
		}

		eOperandType getType( void ) const
		{
			return _type;
		}

		IOperand const * operator+( IOperand const & rhs ) const
		{
			int prec = 0;

			(rhs.getPrecision() >= _precision) ? prec = rhs.getPrecision() : prec = _precision;
			return (g_e.createOperand((eOperandType)prec, (std::to_string(stod(rhs.toString()) + stod(_str)))));
		}

		IOperand const * operator-( IOperand const & rhs ) const
		{
			int prec = 0;

			(rhs.getPrecision() >= _precision) ? prec = rhs.getPrecision() : prec = _precision;
			return (g_e.createOperand((eOperandType)prec, (std::to_string(stod(_str) - stod(rhs.toString())))));

		}

		IOperand const * operator*( IOperand const & rhs ) const
		{
			int prec = 0;

			(rhs.getPrecision() >= _precision) ? prec = rhs.getPrecision() : prec = _precision;
			return (g_e.createOperand((eOperandType)prec, (std::to_string(stod(rhs.toString()) * stod(_str)))));

		}

		IOperand const * operator/( IOperand const & rhs ) const
		{
			int prec = 0;
			double result = stod(_str);

			if (!stod(rhs.toString()))
				throw DIVISIONZEROException("Erreur division par zero");
			
			(rhs.getPrecision() >= _precision) ? prec = rhs.getPrecision() : prec = _precision;
			
			if (result != 0)
				result = stod(_str) / stod(rhs.toString());
			return (g_e.createOperand((eOperandType)prec, (std::to_string(result))));
		}

		IOperand const * operator%( IOperand const & rhs ) const
		{
			int prec = 0;

			if (rhs.getType() == 3 || rhs.getType() == 4 || _type == 3 || _type == 4)
				throw MODULOFLOATException("Erreur modulo avec un float");
			if (!stod(rhs.toString()))
				throw DIVISIONZEROException("Erreur division par zero");

			(rhs.getPrecision() >= _precision) ? prec = rhs.getPrecision() : prec = _precision;
			return (g_e.createOperand((eOperandType)prec, (std::to_string(stoi(rhs.toString()) % stoi(_str)))));
		}

		std::string const & toString( void ) const
		{
			return (_str);
		}

		~Calculator(void)
		{

		}

		Calculator(T value, eOperandType type): _value(value), _type(type)
		{
			_str = std::to_string(value);
			_precision = type;
		}

	private:
		T 				_value;
		eOperandType 	_type;
		int 			_precision;
		std::string		_str;
	};
#endif