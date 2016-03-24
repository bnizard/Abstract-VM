#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP
# include <stdexcept>
# include <string>

class FILEException :  public std::runtime_error
{
	public:
		FILEException(const std::string & what_arg);
};

class SEMICOLONException : public std::runtime_error
{
	public:
		SEMICOLONException(const std::string & what_arg);
};

class EXITException : public std::runtime_error
{
	public:
		EXITException(const std::string & what_arg);
};

class SYNTAXEException : public std::runtime_error
{
	public:
		SYNTAXEException(const std::string & what_arg);
};

class OVERFLOWException : public std::runtime_error
{
	public:
		OVERFLOWException(const std::string & what_arg);
};

class UNDERFLOWException : public std::runtime_error
{
	public:
		UNDERFLOWException(const std::string & what_arg);
};

class DIFFERENTTYPEException : public std::runtime_error
{
	public:
		DIFFERENTTYPEException(const std::string & what_arg);
};

class DIFFERENTVALUEException : public std::runtime_error
{
	public:
		DIFFERENTVALUEException(const std::string & what_arg);
};

class EMPTYSTACKException : public std::runtime_error
{
	public:
		EMPTYSTACKException(const std::string & what_arg);
};

class EMPTYVALUESTACKException : public std::runtime_error
{
	public:
		EMPTYVALUESTACKException(const std::string & what_arg);
};

class DIVISIONZEROException : public std::runtime_error
{
	public:
		DIVISIONZEROException(const std::string & what_arg);
};

class MODULOFLOATException : public std::runtime_error
{
	public:
		MODULOFLOATException(const std::string & what_arg);
};
#endif
