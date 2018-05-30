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
    SC_Environnement(int maxX, int maxY);
    SC_Environnement(int maxX, int maxY, std::shared_ptr<SC_Register> logs) : maxX{maxX}, maxY{maxY}, logs{logs} {logs->addToLog(logs->getID() + "@createEnvironnement:2 "+ std::to_string(getMaxX())+ " " + std::to_string(getMaxY()));}
    ~SC_Environnement();

    void addAnimal(std::string type, int id, int x, int y, int hp);
    void addAnimal(std::shared_ptr<SC_Animal> animal, std::string type = "");
    void removeAnimal(std::shared_ptr<SC_Animal> animal);
    void attack(std::string attackerType, int attackerId, std::string victimType, int victimId);
    std::vector<std::shared_ptr<SC_Animal>>::iterator findAnimal(std::vector<std::shared_ptr<SC_Animal>> v, int id);
    void damage(std::string type, int id, int value);

    void populate(int nblion, int nbgazelle);
    size_t getPopulationSize();
    std::map<std::string, std::vector<std::shared_ptr<SC_Animal>>> getAnimals() const { return animals; }

    int moveAnimals();
    void move(std::string type, int id, std::string direction, int pas);
    int move(std::shared_ptr<SC_Animal> animal);
    int nbOfAnimals(std::string type){ return animals[type].size(); }
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
