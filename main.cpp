#include <string>
#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <regex>
#include <fstream>
#include <locale>
#include "Exception.hpp"
#include "VMFactory.hpp"

void parseconsole(std::string &, int nb, int &error);
void readline(std::list<std::string> &s);
void readfile(const char *fichier, std::list<std::string> &s);
void display(std::list<std::string> s);
void lexer(std::list<std::string> s);
std::string trim(std::string &str);

VMFactory g_e;

int main(int ac, const char **av)
{
	std::list<std::string> s;
	int error = 0;
	int offset = 0;

	try
	{
		if (ac == 1)
			readline(s);
		else if (ac == 2)
			readfile(av[1], s);
		else
		{
			std::cout << "usage ./avm or ./avm file" << std::endl;
			return (0);
		}
		std::list<std::string>::iterator p = s.begin();
		while (p != s.end())
		{
			parseconsole(*p, std::distance(s.begin(), p) + offset, error);
			if ((*p).empty())
			{
				s.erase(p);
				offset++;
			}
			p++;
		}
		if (error)
			throw SYNTAXEException("Erreur de syntaxe");
		// display(s);
		lexer(s);
	}
	catch (SEMICOLONException const& e)
	{
		std::cerr << "Exception : " << e.what() << std::endl;
		return (0);
	}
	catch (EXITException const& e)
	{
		std::cerr << "Exception : " << e.what() << std::endl;
		return (0);
	}
	catch (SYNTAXEException const& e)
	{
		std::cerr << "Exception : " << e.what() << std::endl;
		return (0);
	}
	catch (FILEException const& e)
	{
		std::cerr << "Exception : " << e.what() << std::endl;
		return (0);
	}
	catch (OVERFLOWException const& e)
	{
		std::cerr << "Exception : " << e.what() << std::endl;
		return(0);
	}
	catch (UNDERFLOWException const& e)
	{
		std::cerr << "Exception : " << e.what() << std::endl;
		return (0);
	}
	catch (DIFFERENTTYPEException const& e)
	{
		std::cerr << "Exception : " << e.what() << std::endl;
		return (0);
	}
	catch (DIFFERENTVALUEException const& e)
	{
		std::cerr << "Exception : " << e.what() << std::endl;
		return (0);
	}
	catch (EMPTYSTACKException const& e)
	{
		std::cerr << "Exception : " << e.what() << std::endl;
		return (0);
	}
	catch (EMPTYVALUESTACKException const& e)
	{
		std::cerr << "Exception : " << e.what() << std::endl;
		return (0);
	}
	catch (DIVISIONZEROException const& e)
	{
		std::cerr << "Exception : " << e.what() << std::endl;
		return (0);
	}
	catch (MODULOFLOATException const& e)
	{	
		std::cerr << "Exception : " << e.what() << std::endl;
		return (0);
	}
	return (0);
}

void readfile(const char *fichier, std::list<std::string> &s)
{	
	std::ifstream stream(fichier);
	std::string ligne;
	std::regex reg("([ \t]+)?exit([ \t]+)?");

	if (stream)
	{
		while (std::getline(stream, ligne) && !regex_match(ligne, reg))
			s.push_back(trim(ligne));
		if (!regex_match(ligne, reg))
			throw EXITException("Erreur instruction 'exit' manquante");
	}
	else
		throw FILEException("Impossible d'ouvrir le fichier");
}

void readline(std::list<std::string> &s)
{
	std::string ligne;
	std::regex reg("([ \t]+)?exit([ \t]+)?");
	int flag = 0;

	while (std::getline(std::cin, ligne) && ligne.compare(";;"))
	{
		s.push_back(trim(ligne));
		if (regex_match(ligne, reg))
			flag++;
	}
	if (ligne.compare(";;"))
		throw SEMICOLONException("Erreur instruction ';;' manquante");
	if (!flag)
		throw EXITException("Erreur instruction 'exit' manquante");
}

void parseconsole(std::string &s, int nb, int &error)
{
	int i = 0;
	std::regex reg("([ \t]+)?((add|pop|dump|sub|mul|div|mod|print|exit|sin|cos|tan|mid|max|min)|((push|assert)[ \t]((int(8|16|32)[(]-?[0-9]+[)])|(float|double)[(]-?[0-9]+(.[0-9]+)?[)])))([ \t]+)?");

	if ((i = s.find(";")) != -1)
		s.assign(s, 0, i);
	if (!s.empty())
	{
		if (!regex_match(s, reg))
		{
			std::cerr << "Erreur de syntaxe ligne " << nb + 1 << std::endl;
			error = 1;
		}
	}
}

std::string trim(std::string &str)
{
	size_t p = str.find_first_not_of(" \t");
   	str.erase(0, p);

	p = str.find_last_not_of(" \t");
   	if (std::string::npos != p)
      str.erase(p+1);
  return (str);
}

void display(std::list<std::string> s)
{
	std::list<std::string>::iterator p = s.begin();
	while (p != s.end())
	{
		std::cout << *p << std::endl;
		p++;
	}
}

void lexer(std::list<std::string> s)
{
	std::list<std::string>::iterator p = s.begin();

	std::locale loc;
	std::cmatch val;
	std::cmatch typ;
	std::cmatch ins;
	std::regex in("^[[:alpha:]]+");
	std::regex ty("[ \t][[:alnum:]]+");
    std::regex va("[(](-?[0-9]+(.[0-9]+)?)][)]");
     
	while (p != s.end())
	{	
		regex_search((*p).c_str(), val, va);
	    regex_search((*p).c_str(), typ, ty);
	    regex_search((*p).c_str(), ins, in);
	    std::string instruction(ins[0]);
	    std::string type(typ[0]);
	    type.erase(type.begin());
		type[0] = std::toupper(type[0], loc);
	    std::string valeur(val[1]);

	    // std::cout << "Instruction : " << trim(instruction) << std::endl;
	    // std::cout << "Type : " << trim(type) << std::endl;
	    // std::cout << "Valeur : " << trim(valeur) << std::endl;
	    g_e.doInstruction(trim(instruction), g_e.getTypeWithString(trim(type)), trim(valeur));
		p++;
	}
}