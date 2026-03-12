#include <string>

class Player {
    private:
        std::string name;
        int hp;
        int maxHp;
        int level;

    public:
        Player(std::string name, int maxHp);
        int takeDamage(int amount);
        int heal(int amount);
        int levelUp(int amount);
        void printStatus() const;
};
