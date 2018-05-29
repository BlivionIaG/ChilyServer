#ifndef SC_ANIMAL_HPP
#define SC_ANIMAL_HPP

#include "SC_Entity.hpp"

class SC_Animal : public SC_Entity
{
public:
  SC_Animal(long long int id, int x = 0, int y = 0, int hp = 100) : SC_Entity(id),
                                                                    x{x},
                                                                    y{y},
                                                                    hp{hp} {}
  SC_Animal(const SC_Animal &copy) : SC_Entity(copy.getID()),
                                     x{copy.getX()},
                                     y{copy.getY()},
                                     hp{copy.getHP()} {}
  ~SC_Animal() {}

  int getX() const { return x; }
  int getY() const { return y; }
  int getHP() const { return hp; }

  void setX(int x) { this->x = x; }
  void setY(int y) { this->y = y; }
  void setHP(int hp) { this->hp = hp; }

  void addX(int x) { this->x += x; }
  void addY(int y) { this->y += y; }
  void addHP(int hp) { this->hp += hp; }

  virtual void attack(SC_Animal &target){target.setHP(target.getHP()/4);}
  virtual std::string getType() const { return "Animal"; }
  virtual std::string getClass() const { return "Animal"; }
  virtual int getKills() const { return 0; }
  virtual bool operator==(SC_Animal &a) { return &a == this; }

protected:
  int x, y, hp;
};

#endif /* SC_ANIMAL_HPP */
