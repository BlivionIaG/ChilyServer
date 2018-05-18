#ifndef SC_ENVIRONNEMENT_HPP
#define SC_ENVIRONNEMENT_HPP

#include <random>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "SC_Gazelle.hpp"
#include "SC_Lion.hpp"
#include "SC_Register.hpp"

class SC_Environnement
{
public:
  SC_Environnement(int maxX, int maxY) : maxX{maxX}, maxY{maxY} { logs = std::make_shared<SC_Register>(); }
  SC_Environnement(int maxX, int maxY, std::shared_ptr<SC_Register> logs) : maxX{maxX}, maxY{maxY}, logs{logs} {}
  ~SC_Environnement();

  void addAnimal(std::shared_ptr<SC_Animal> animal, std::string type = "");
  void removeAnimal(std::shared_ptr<SC_Animal> animal);

  void populate(int nblion, int nbgazelle);
  size_t getPopulationSize();

  int moveAnimals();
  int move(std::shared_ptr<SC_Animal> animal);
  std::vector<std::shared_ptr<SC_Animal>> getAnimalsToDelete() const { return animalsToDelete; }
  void findAnimalsToDelete();
  void clearAnimalsToDelete();

  int getMaxX() const { return maxX; }
  int getMaxY() const { return maxY; }
  int entAleat(int min, int max);

private:
  std::map<std::string, std::vector<std::shared_ptr<SC_Animal>>> animals;
  std::vector<std::shared_ptr<SC_Animal>> animalsToDelete;
  int maxX, maxY;
  std::shared_ptr<SC_Register> logs;
};

#endif /* SC_ENVIRONNEMENT_HPP */