#ifndef SC_GAZELLE_HPP
#define SC_GAZELLE_HPP

#include "SC_Animal.hpp"

class SC_Gazelle : public SC_Animal
{
public:
  SC_Gazelle(long long int id, int x = 0, int y = 0, int hp = 100) : SC_Animal(id, x, y, hp) {}
  ~SC_Gazelle() {}

  std::string getType() const { return "Gazelle"; }
  void attack(SC_Animal &target) {}

protected:
};

#endif /* SC_GAZELLE_HPP */