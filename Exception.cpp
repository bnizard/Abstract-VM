#include "Exception.hpp"

FILEException::FILEException(const std::string & what_arg) : std::runtime_error(what_arg)
{
}

SEMICOLONException::SEMICOLONException(const std::string & what_arg) : std::runtime_error(what_arg)
{
}

EXITException::EXITException(const std::string & what_arg) : std::runtime_error(what_arg)
{
}

SYNTAXEException::SYNTAXEException(const std::string & what_arg) : std::runtime_error(what_arg)
{
}

OVERFLOWException::OVERFLOWException(const std::string & what_arg) : std::runtime_error(what_arg)
{
}

UNDERFLOWException::UNDERFLOWException(const std::string & what_arg) : std::runtime_error(what_arg)
{
}

DIFFERENTTYPEException::DIFFERENTTYPEException(const std::string & what_arg) : std::runtime_error(what_arg)
{
}

DIFFERENTVALUEException::DIFFERENTVALUEException(const std::string & what_arg) : std::runtime_error(what_arg)
{
}

EMPTYSTACKException::EMPTYSTACKException(const std::string & what_arg) : std::runtime_error(what_arg)
{
}

EMPTYVALUESTACKException::EMPTYVALUESTACKException(const std::string & what_arg) : std::runtime_error(what_arg)
{
}

DIVISIONZEROException::DIVISIONZEROException(const std::string & what_arg) : std::runtime_error(what_arg)
{
}

MODULOFLOATException::MODULOFLOATException(const std::string & what_arg) : std::runtime_error(what_arg)
{
}