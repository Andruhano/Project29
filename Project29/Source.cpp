#include <iostream>
#include <vector>
using namespace std;

class Herbivore 
{
public:
    virtual void EatGrass() = 0;
    virtual int GetWeight() const = 0;
    virtual bool IsAlive() const = 0;
    virtual void Die() = 0;
    virtual ~Herbivore() = default;
};

class Carnivore 
{
public:
    virtual void Eat(Herbivore* herbivore) = 0;
    virtual int GetPower() const = 0;
    virtual ~Carnivore() = default;
};

class Wildebeest : public Herbivore 
{
    int weight;
    bool life;
public:
    Wildebeest() : weight(100), life(true) {}
    void EatGrass() override 
    {
        weight += 10;
    }
    int GetWeight() const override 
    {
        return weight;
    }
    bool IsAlive() const override 
    {
        return life;
    }
    void Die() override 
    {
        life = false;
    }
};

class Bison : public Herbivore 
{
    int weight;
    bool life;
public:
    Bison() : weight(150), life(true) {}
    void EatGrass() override 
    {
        weight += 10;
    }
    int GetWeight() const override 
    {
        return weight;
    }
    bool IsAlive() const override 
    {
        return life;
    }
    void Die() override 
    {
        life = false;
    }
};

class Elk : public Herbivore 
{
    int weight;
    bool life;
public:
    Elk() : weight(200), life(true) {}
    void EatGrass() override 
    {
        weight += 10;
    }
    int GetWeight() const override 
    {
        return weight;
    }
    bool IsAlive() const override 
    {
        return life;
    }
    void Die() override 
    {
        life = false;
    }
};

class Lion : public Carnivore 
{
    int power;
public:
    Lion() : power(120) {}
    void Eat(Herbivore* herbivore) override 
    {
        if (power > herbivore->GetWeight()) 
        {
            power += 10;
            herbivore->Die();
        }
        else 
        {
            power -= 10;
        }
    }
    int GetPower() const override 
    {
        return power;
    }
};

class Wolf : public Carnivore 
{
    int power;
public:
    Wolf() : power(80) {}
    void Eat(Herbivore* herbivore) override 
    {
        if (power > herbivore->GetWeight()) 
        {
            power += 10;
            herbivore->Die();
        }
        else {
            power -= 10;
        }
    }
    int GetPower() const override 
    {
        return power;
    }
};

class Tiger : public Carnivore 
{
    int power;
public:
    Tiger() : power(150) {}
    void Eat(Herbivore* herbivore) override
    {
        if (power > herbivore->GetWeight()) 
        {
            power += 10;
            herbivore->Die();
        }
        else 
        {
            power -= 10;
        }
    }
    int GetPower() const override 
    {
        return power;
    }
};

class Continent 
{
public:
    virtual Herbivore* CreateHerbivore() = 0;
    virtual Carnivore* CreateCarnivore() = 0;
    virtual ~Continent() = default;
};

class Africa : public Continent 
{
public:
    Herbivore* CreateHerbivore() override 
    {
        return new Wildebeest();
    }
    Carnivore* CreateCarnivore() override 
    {
        return new Lion();
    }
};

class NorthAmerica : public Continent 
{
public:
    Herbivore* CreateHerbivore() override 
    {
        return new Bison();
    }
    Carnivore* CreateCarnivore() override 
    {
        return new Wolf();
    }
};

class Eurasia : public Continent 
{
public:
    Herbivore* CreateHerbivore() override 
    {
        return new Elk();
    }
    Carnivore* CreateCarnivore() override 
    {
        return new Tiger();
    }
};

class AnimalWorld 
{
    vector<Herbivore*> herbivores;
    vector<Carnivore*> carnivores;
public:
    AnimalWorld(Continent* continent) 
    {
        herbivores.push_back(continent->CreateHerbivore());
        carnivores.push_back(continent->CreateCarnivore());
    }

    ~AnimalWorld() 
    {
        for (Herbivore* herbivore : herbivores) 
        {
            delete herbivore;
        }
        for (Carnivore* carnivore : carnivores) 
        {
            delete carnivore;
        }
    }

    void MealsHerbivores() 
    {
        for (Herbivore* herbivore : herbivores) 
        {
            if (herbivore->IsAlive()) 
            {
                herbivore->EatGrass();
                cout << "Herbivore ate grass. Weight: " << herbivore->GetWeight() << endl;
            }
        }
    }

    void NutritionCarnivores() 
    {
        for (Carnivore* carnivore : carnivores) 
        {
            for (Herbivore* herbivore : herbivores) 
            {
                if (herbivore->IsAlive()) 
                {
                    carnivore->Eat(herbivore);
                    cout << "Carnivore tried to eat herbivore. Power: " << carnivore->GetPower() << endl;
                }
            }
        }
    }
};

int main() 
{
    Continent* africa = new Africa();
    Continent* northAmerica = new NorthAmerica();
    Continent* eurasia = new Eurasia();

    AnimalWorld* africanWorld = new AnimalWorld(africa);
    AnimalWorld* northAmericanWorld = new AnimalWorld(northAmerica);
    AnimalWorld* eurasianWorld = new AnimalWorld(eurasia);

    cout << "African World:" << endl;
    africanWorld->MealsHerbivores();
    africanWorld->NutritionCarnivores();

    cout << "North American World:" << endl;
    northAmericanWorld->MealsHerbivores();
    northAmericanWorld->NutritionCarnivores();

    cout << "Eurasian World:" << endl;
    eurasianWorld->MealsHerbivores();
    eurasianWorld->NutritionCarnivores();

    delete africanWorld;
    delete northAmericanWorld;
    delete eurasianWorld;

    delete africa;
    delete northAmerica;
    delete eurasia;

    return 0;
}