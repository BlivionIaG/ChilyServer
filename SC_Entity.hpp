#ifndef SC_ENTITY_HPP
#define SC_ENTITY_HPP

#include <string>

class SC_Entity
{
public:
  /**
   *brief Constructeur
   */
  SC_Entity(long long int id) : id{id} {}
  SC_Entity(const SC_Entity &copy) : id{copy.getID()} {}
  virtual ~SC_Entity() {}

  void setID(long long int val) { id = val; }
  long long int getID() const { return id; }
  virtual std::string getClass() const = 0;
  virtual std::string getType() const = 0;

protected:
  long long int id;
};

#endif /* SC_ENTITY_HPP */