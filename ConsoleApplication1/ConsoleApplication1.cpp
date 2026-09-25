#include <iostream>
#include <vector>


using namespace std;

//class Item {
//
//public:
//    Item(int my_ID, int my_health_value, string my_name) {
//        ID = my_ID;
//        health_value = my_health_value;
//        name = my_name;
//    }
//
//    int get_health_value() { return health_value; }
//    int get_ID() { return ID; }
//    string get_name() { return name; }

//private:
//    int ID;
//    int health_value;
//    string name;
//};

class Enemy {
private:
    string Ename = "";
    int health;
    int damage;
    char symbol;
public:
    Enemy(string n, int dmg, int hp, char sym) {
        damage = dmg;
        health = hp;
        symbol = sym;
        Ename = n;
    }
    void takedamage(int dmg) {
        health -= dmg;
        if (health < 0) {
            health = 0;
        }
    }
    bool enemyalive() { return health > 0; }
    int get_damage() { return damage; }
    int get_health() { return health; }
    string get_name() { return Ename; }


};

class Character {
private:
    string name;
    int health;
    int damage;
public:

    Character(string n, int hp, int dmg, char sym = 'P') {
        name = n;
        health = hp;
        damage = dmg;
    }
    void add_health(int x) {
        health = health + x;
        if (health > 100) {
            health = 100;
        }
    }
    bool playeralive() {
        return health > 0;
    }

    int get_damage() { return damage; }
    int get_health() { return health; }


    void plusdamage(int dmg) {
        damage = damage + dmg;
    }
    void attack(Enemy& enemy) {
        enemy.takedamage(damage);
        cout << "Вы наносите " << damage << " урона \n";
    }
    void takedamage(int dmg) {
        health -= dmg;
        if (health < 0) {
            health = 0;
        }
    }
    void print() {
        cout << "health: " << health << "\n";
        cout << "damage: " << damage << "\n";

    }




};

class Location {
private:
    int width;
    int height;
    vector<vector<char>> map;
    int playerX, playerY;
    int enemyX, enemyY;
    char playerSymbol;
    char enemySymbol;
    int DoorX, DoorY;
    char doorsymbol;
    char enemydefsymbol;
    bool openedDoor;

public:
    Location(int w, int h, char playerSym = '@', char enemySym = 'O', char doorsym = 'D') {
        width = w;
        height = h;
        playerSymbol = playerSym;
        enemySymbol = enemySym;
        playerX = width / 2;
        playerY = height / 2;
        enemyX = width / 2;
        enemyY = height / 2;
        doorsymbol = doorsym;
        DoorX = width / 2;
        DoorY = height / 2;
        enemydefsymbol = '/';
        openedDoor = false;
        generateMap();
    }

    void generateMap() {
        map.resize(height, vector<char>(width));

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                    map[i][j] = '#';
                }
                else {
                    map[i][j] = '.';
                }
            }
        }
    }



    void placePlayer(int x, int y) {
        playerX = x;
        playerY = y;
    }

    void placeEnemy(int x, int y) {
        enemyX = x;
        enemyY = y;
        
    }
    void opendoor() {
        openedDoor = true;
    }
    void placeDoor(int x, int y) {
        DoorX = x;
        DoorY = y;

    }
    bool diddooropen() {
        return openedDoor;
    }

    void render(Enemy& enemy) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i == playerY && j == playerX) {
                    cout << playerSymbol << ' ';
                }
                else if (i == enemyY && j == enemyX && enemy.enemyalive()) {
                    cout << enemySymbol << ' ';
                }
                else if (i == enemyY && j == enemyX && !enemy.enemyalive()) {
                    cout << enemydefsymbol << ' ';
                }
                else if (i == DoorY && j == DoorX) {
                    if (openedDoor) {
                        cout << 'O' << ' ';
                    }
                    else {
                        cout << doorsymbol << ' ';
                    }

                }
                else {
                    cout << map[i][j] << ' ';
                }
            }
            cout << endl;
        }
    }
};

class Fight {
public:
    static void battle(Character& character, Enemy& enemy, Location& location) {
        cout << "Бой с " << enemy.get_name();
        while (character.playeralive() && enemy.enemyalive()) {
            cout << "\nВаше здоровье: " << character.get_health();
            cout << "\nЗдоровье врага: " << enemy.get_health();
            cout << "\nВыберите действие: \n1 - Ударить \n2 - Лечиться\n";

            int choice;
            cin >> choice;
            if (choice == 1) {
                system("cls");
                character.attack(enemy);
            }
            else if (choice == 2) {
                system("cls");
                character.add_health(15);
                cout << "Вы восстановили 15 хп\n";
            }

            if (!enemy.enemyalive()) {
                system("cls");
                cout << "Вы победили врага и прокачались! +5 урона\n";
                character.plusdamage(5);
                location.opendoor();
                break;
            }
            int enemyDamage = enemy.get_damage();
            character.takedamage(enemyDamage);
            cout << "Враг наносит " << enemyDamage << " урона\n";
            if (!character.playeralive()) {
                cout << "Вы умерли.";
                return;
            }
        }
    }
};

int main()
{
    srand(time(0));
    Character my_char("игрок", 100, 10);
    Enemy first("гоблин", 10, 50, 'G');
    Enemy second("гремлин", 12, 60, 'E');
    Enemy third("гоша", 15, 80, 'L');
    Location loc1(8, 8, '@', 'G');
    loc1.placePlayer(4, 6);
    loc1.placeEnemy(3, 3);
    loc1.placeDoor(1, 6);
    Location loc2(10, 10, '@', 'O');
    loc2.placePlayer(8, 8);
    loc2.placeEnemy(5, 5);
    loc2.placeDoor(3, 1);
    Location loc3(8, 8, '@', 'L');
    loc3.placePlayer(4, 6);
    loc3.placeEnemy(3, 3);
    Location* currentLocation = &loc1;
    Enemy* currentEnemy = &first;
    bool gameRunning = true;
    int locationNumber = 1;
    while (gameRunning && my_char.playeralive()) {
        cout << "\n локация " << locationNumber << "\n";
        currentLocation->render(*currentEnemy);
        if (currentEnemy->enemyalive()) {
            cout << "\nВраг: " << currentEnemy->get_name()
                << ", здоровье " << currentEnemy->get_health() << "/" << currentEnemy->get_health() << " HP\n";
        }
        else {
            cout << "\n Враг повержен!\n";
        }
        bool actionDone = false;
        while (!actionDone && my_char.playeralive()) {
            cout << "\n1 - Дверь. 2 - Враг\n";
            cout << "Выберите действие: ";
            int a;
            cin >> a;
            if (a == 1) {
                if (currentEnemy->enemyalive()) {
                    cout << "\nСначала победи врага\n";
                }
                else {
                    if (currentLocation->diddooropen()) {
                        actionDone = true;
                        locationNumber++;

                        if (locationNumber == 2) {
                            currentLocation = &loc2;
                            currentEnemy = &second;
                            cout << "\n локация 2\n";
                            cout << "Вы встречаете врага " << currentEnemy->get_name() << "\n";
                        }
                        else if (locationNumber == 3) {
                            currentLocation = &loc3;
                            currentEnemy = &third;
                            cout << "\n локация 3 \n";
                            cout << "Враг:  " << currentEnemy->get_name() << "\n";
                        }
                        else if (locationNumber > 3) {
                            cout << "\n вы прошли локации \n";
                            gameRunning = false;
                            actionDone = true;
                        }
                    }
                    else {
                        return 0;
                    }
                }
            }
            else if (a == 2) {

                if (currentEnemy->enemyalive()) {
                    cout << "\n бой с " << currentEnemy->get_name() << "\n";
                    Fight::battle(my_char, *currentEnemy, *currentLocation);
                    actionDone = true;
                    if (!my_char.playeralive()) {
                        cout << "\n Вы умерли\n";
                        gameRunning = false;
                    }
                }
                else {
                    cout << "\n Враг уже умер \n";
                }
            }
            else {
                cout << "\n неверный выбор \n";
            }
        }
    }
    cout << "\nигра окончена\n";
    cout << "Пройдено локаций: " << (locationNumber > 3 ? 3 : locationNumber - 1) << "/3\n";
    my_char.print();
    return 0;
}

