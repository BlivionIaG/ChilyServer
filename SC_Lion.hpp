#ifndef SC_LION_HPP
#define SC_LION_HPP

#include "SC_Animal.hpp"

class SC_Lion : public SC_Animal
{
public:
  SC_Lion(long long int id, int x = 0, int y = 0, int hp = 100) : SC_Animal(id, x, y, hp) { kills = 0; }
  ~SC_Lion() {}

  std::string getType() const { return "Lion"; }
  void attack(SC_Animal &target);
  int getKills() const { return kills; };

protected:
  int kills;
};

#endif /* SC_SC_Lion_HPP */