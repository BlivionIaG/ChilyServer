#include "SC_Environnement.hpp"

SC_Environnement::~SC_Environnement()
{
    auto tmp = animals["Lion"];

    for (const auto &i : tmp)
    {
        std::cout << "Entité " << i->getClass() << " de type " << i->getType() << " a tué " << i->getKills() << " fois." << std::endl;
    }

    findAnimalsToDelete();
    clearAnimalsToDelete();
}

void SC_Environnement::addAnimal(std::shared_ptr<SC_Animal> animal, std::string type)
{
    if (!type.compare(""))
    {
        type = animal->getType();
    }

    logs->addToLog(logs->getID() + "@addAnimal:2 " + type + " " + std::to_string(animal->getID()));

    animals[type].push_back(animal);
}

void SC_Environnement::removeAnimal(std::shared_ptr<SC_Animal> animal)
{
    logs->addToLog(logs->getID() + "@removeAnimal:2 " + animal->getType() + " " + std::to_string(animal->getID()));
    animalsToDelete.push_back(animal);
}

int SC_Environnement::moveAnimals()
{
    //clearAnimalsToDelete();
    int mouvement{0};

    for (const auto &it : animals)
    {
        for (const auto &animal : it.second)
        {
            mouvement += move(animal);
        }
    }

    return mouvement;
}

int SC_Environnement::move(std::shared_ptr<SC_Animal> animal)
{
    if (animal == nullptr)
        return 0;

    if (animal->getHP() < 0)
    {
        return 0;
    }

    if (!animal->getType().compare("Lion"))
    {
        auto proies = animals["Gazelle"];
        for (const auto &proie : proies)
        {
            if (proie->getX() == animal->getX() && proie->getY() == animal->getY())
            {
                animal->attack(*proie);
                logs->addToLog(logs->getID() + "@attack:4 " + animal->getType() + " " + std::to_string(animal->getID()) + " " + proie->getType() + " " + std::to_string(proie->getID()));
                break;
            }
        }
    }

    int direction;
    bool valid = false;
    do
    {
        direction = entAleat(0, 4);
        if ((direction == 0 && animal->getX() > 0) ||
            (direction == 1 && animal->getX() < maxX) ||
            (direction == 2 && animal->getY() > 0) ||
            (direction == 3 && animal->getY() < maxY))
        {
            valid = true;
        }
    } while (!valid);

    switch (direction)
    {
    case 0:
        animal->setX(animal->getX() - 1);
        logs->addToLog(logs->getID() + "@move:4 " + animal->getType() + " " + std::to_string(animal->getID()) + " LEFT 1");
        break;
    case 1:
        animal->setX(animal->getX() + 1);
        logs->addToLog(logs->getID() + "@move:4 " + animal->getType() + " " + std::to_string(animal->getID()) + " RIGHT 1");
        break;
    case 2:
        animal->setY(animal->getY() - 1);
        logs->addToLog(logs->getID() + "@move:4 " + animal->getType() + " " + std::to_string(animal->getID()) + " UP 1");
        break;
    case 3:
        animal->setY(animal->getY() + 1);
        logs->addToLog(logs->getID() + "@move:4 " + animal->getType() + " " + std::to_string(animal->getID()) + " DOWN 1");
        break;
    }

    animal->addHP(-1);
    logs->addToLog(logs->getID() + "@damage:3 " + animal->getType() + " " + std::to_string(animal->getID()) + " 1");

    return 1;
}

void SC_Environnement::findAnimalsToDelete()
{
    for (const auto &j : animals)
    {
        for (const auto &i : j.second)
        {
            if (i->getHP() <= 0)
            {
                removeAnimal(i);
            }
        }
    }
}

void SC_Environnement::clearAnimalsToDelete()
{
    for (const auto &animal : animalsToDelete)
    {
        auto &v = animals[animal->getType()];
        auto id = animal->getID();

        v.erase(std::find_if(v.begin(), v.end(), [id](std::shared_ptr<SC_Animal> a) { return a->getID() == id; }));
    }

    animalsToDelete.clear();
}

void SC_Environnement::populate(int nblion, int nbgazelle)
{
    for (auto i{0}; i < nblion - 1; ++i)
    {
        addAnimal(
            std::make_shared<SC_Lion>(
                SC_Lion(
                    getPopulationSize(),
                    entAleat(0, maxX),
                    entAleat(0, maxY))),
            "Lion");
    }
    for (auto i{0}; i < nbgazelle - 1; ++i)
    {
        addAnimal(
            std::make_shared<SC_Gazelle>(
                SC_Gazelle(
                    getPopulationSize(),
                    entAleat(0, maxX),
                    entAleat(0, maxY))),
            "Gazelle");
    }
}

size_t SC_Environnement::getPopulationSize()
{
    size_t out = 0;
    for (const auto &it : animals)
    {
        out += it.second.size();
    }

    return out;
}

int SC_Environnement::entAleat(int min, int max)
{
    std::random_device engine{};
    std::uniform_int_distribution<> normal(min, max);
    auto out = static_cast<int>(normal(engine));

    return out;
}