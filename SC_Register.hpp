#ifndef SC_REGISTER_HPP
#define SC_REGISTER_HPP

#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <memory>
#include <iostream>

#include "cmdFormat.hpp"

class SC_Register
{
public:
  /**
   *\brief Constructeur
   */
  SC_Register(std::string path = "") : path{path} { id = "SERVER"; }

  /**
   *\brief Destructeur
   */
  ~SC_Register();

  std::vector<cmdFormat::cmdFormat> getLog() const { return log; }
  std::size_t getLogSize() const { return log.size(); }
  void addToLog(cmdFormat::cmdFormat &entry) { log.push_back(std::move(entry)); }
  void addToLog(std::vector<std::string> entry);
  void addToLog(std::string entry) { log.push_back(cmdFormat::parseCommand(entry)); }

  std::vector<std::string> loadFile(std::string path);
  void saveFile(std::string path);

  void setID(std::string p_id) { id = p_id; }
  std::string getID() const { return id; }

  void setReadCursor(int p_curs) { readCursor = p_curs; }
  int getReadCursor() const { return readCursor; }
  std::string getLine();

private:
  std::vector<cmdFormat::cmdFormat> log;
  std::string path;
  std::string id;
  int readCursor = 0;
};

#endif /* SC_REGISTER_HPP */