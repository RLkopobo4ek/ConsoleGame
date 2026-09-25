//#include <iostream>
//#include <vector>
//
//class Location {
//private:
//    int width;
//    int height;
//    std::vector<std::vector<char>> map;
//    int playerX, playerY;
//    char playerSymbol;
//
//public:
//    // Конструктор
//    Location(int w, int h, char playerSym = 'P')
//        : width(w), height(h), playerSymbol(playerSym) {
//        playerX = width / 2;
//        playerY = height / 2;
//        generateMap();
//    }
//
//    // Генерация карты с контуром
//    void generateMap() {
//        map.resize(height, std::vector<char>(width));
//
//        for (int i = 0; i < height; i++) {
//            for (int j = 0; j < width; j++) {
//                if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
//                    map[i][j] = '#';
//                }
//                else {
//                    map[i][j] = '.';
//                }
//            }
//        }
//    }
//
//    // Размещение игрока
//    void placePlayer(int x, int y) {
//        if (x > 0 && x < width - 1 && y > 0 && y < height - 1) {
//            playerX = x;
//            playerY = y;
//        }
//        else {
//            std::cout << "Ошибка: нельзя разместить игрока на стене!\n";
//        }
//    }
//
//    // Перемещение игрока
//    void movePlayer(int dx, int dy) {
//        int newX = playerX + dx;
//        int newY = playerY + dy;
//
//        if (newX > 0 && newX < width - 1 &&
//            newY > 0 && newY < height - 1) {
//            playerX = newX;
//            playerY = newY;
//        }
//    }
//
//    // Отрисовка локации
//    void render() const {
//        for (int i = 0; i < height; i++) {
//            for (int j = 0; j < width; j++) {
//                if (i == playerY && j == playerX) {
//                    std::cout << playerSymbol << ' ';
//                }
//                else {
//                    std::cout << map[i][j] << ' ';
//                }
//            }
//            std::cout << std::endl;
//        }
//    }
//
//    // Геттеры
//    int getPlayerX() const { return playerX; }
//    int getPlayerY() const { return playerY; }
//    int getWidth() const { return width; }
//    int getHeight() const { return height; }
//};
//
//int main() {
//    // Создание нескольких локаций разного размера
//    Location forest(5, 5, 'P');      // Лес 5x5
//    Location dungeon(7, 7, '@');     // Подземелье 7x7
//    Location castle(9, 5, 'K');      // Замок 9x5
//
//    // Настройка игроков в разных позициях
//    forest.placePlayer(2, 2);
//    dungeon.placePlayer(3, 3);
//    castle.placePlayer(4, 2);
//
//    // Вывод всех локаций
//    std::cout << "=== ЛОКАЦИЯ 1: ЛЕС ===\n";
//    forest.render();
//
//    std::cout << "\n=== ЛОКАЦИЯ 2: ПОДЗЕМЕЛЬЕ ===\n";
//    dungeon.render();
//
//    std::cout << "\n=== ЛОКАЦИЯ 3: ЗАМОК ===\n";
//    castle.render();
//
//    return 0;
//}