#ifndef VMFACTORY_HPP
# define VMFACTORY_HPP
# include <list>
# include <map>
# include "IOperand.hpp"




class VMFactory
{
	public:
		VMFactory();
		VMFactory(VMFactory const & src);
		virtual ~VMFactory();
		VMFactory & operator=(VMFactory const & rhs);
		std::list<const IOperand *> getStack() const;

		void push(eOperandType type, std::string const & value);
		void pop(eOperandType type, std::string const & value);
		void dump(eOperandType type, std::string const & value);
		void assert(eOperandType type, std::string const & value);
		void add(eOperandType type, std::string const & value);
		void sub(eOperandType type, std::string const & value);
		void mul(eOperandType type, std::string const & value);
		void div(eOperandType type, std::string const & value);
		void mod(eOperandType type, std::string const & value);
		void print(eOperandType type, std::string const & value);
		void exit(eOperandType type, std::string const & value);
		void bsin(eOperandType type, std::string const & value);
		void bcos(eOperandType type, std::string const & value);
		void btan(eOperandType type, std::string const & value);
		void bmoy(eOperandType type, std::string const & value);
		void bmax(eOperandType type, std::string const & value);
		void bmin(eOperandType type, std::string const & value);

		IOperand const * createOperand( eOperandType type, std::string const & value ) const;
		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;

		void doInstruction(std::string const & instr, eOperandType type, std::string const & value);
		eOperandType getTypeWithString(std::string type);		
	private:
		std::list<const IOperand *>	_stack;
		IOperand const * (VMFactory::*_tab[5]) (std::string const & value ) const;
		std::map<std::string, void (VMFactory::*)(eOperandType type, std::string const & value) > _instruction;
};

#endif