#ifndef CMDFORMAT_HPP
#define CMDFORMAT_HPP

#include <iostream>
#include <string>
#include <vector>

namespace cmdFormat
{
    

struct cmdFormat
{
	std::string id, command;
	std::vector<std::string> args;
	unsigned int arglen;
	bool valid;
};

/**
 *brief	Converti une commande en chaine de caractères
 *\param	entry	Commande à convertir
 *\return   Chaine convertie
 */
std::string toString(cmdFormat &entry);

/**
 *brief	Converti une chaine de caractères en commande
 *\param	entry	Chaine à convertir
 *\return   Commande convertie
 */
cmdFormat parseCommand(std::string entry);

/**
 *brief	Affiche le contenu de la commande
 *\param	cmd	Commande à afficher
 */
void printCommand(cmdFormat cmd);

/**
 *brief	efface le contenu de la commande
 *\param	cmd	Commande à effacer
 */
void clearCommand(cmdFormat &cmd);

/**
 *brief	Sépare la chaine de caractères en elements tous les caractères délimitant
 *\param	in	Chaine à séparer
 *\param	token	Délimiteur
 *\return	Un tableau de chaines de caractères
 */
std::vector<std::string> split(const std::string &in, const char &token);
}

static const unsigned int MAX_NET_BUFFER_LENGTH = 65536;

#endif /* CMDFORMAT_HPP */
