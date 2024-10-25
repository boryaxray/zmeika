// zmeika.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
const int width = 20;
const int height = 10;
bool GameOver = false;
int foodX, foodY;

struct Snakee {
public:
    int x, y;
    Snakee* next;
    Snakee(int startX, int startY) : x(startX), y(startY), next(nullptr) {}
};
class Snake {
public:
    Snakee* head = nullptr;
    char dvi = 'd';
    Snake() {};
    Snake(int startX, int startY)
    {
        head = new Snakee{ startX,startY };
    }
    void genFood() {
        foodX = rand() % (width - 2) + 1;
        foodY = rand() % (height - 2) + 1;
        while (Game(foodX, foodY))
        {
            foodX = rand() % (width - 2) + 1;
            foodY = rand() % (height - 2) + 1;
        }
    }

    void move() {
        int newX = head->x;
        int newY = head->y;
        
        if (_kbhit())
        {
            int key = _getch();
            if (key == 87 || key == 119)
            {
                if (dvi != 's')
                {
                    dvi = 'w';
                }
            }
            else if (key == 65 || key == 97)
            {
                if (dvi != 'd')
                {
                    dvi = 'a';
                }
            }
            else if (key == 83 || key == 115)
            {
                if (dvi != 'w')
                {
                    dvi = 's';
                }
            }
            else if (key == 68 || key == 100)
            {
                if (dvi != 'a')
                {
                    dvi = 'd';
                }
            }
        }

        switch (dvi) {
        case 'w': newY--; break;
        case 's': newY++; break;
        case 'a': newX--; break;
        case 'd': newX++; break;
        }

        if (Game(newX, newY))
        {
            GameOver = true;
            return;
        }

        if (newX == foodX && newY == foodY)
        {
            Snakee* newHead = new Snakee(newX, newY);
            newHead->next = head;
            head = newHead;
            genFood();
        }
        else
        {
            Snakee* newHead = new Snakee(newX, newY);
            newHead->next = head;
            head = newHead;

            Snakee* temp = head;
            while (temp->next != head) { head = temp->next; }
            delete head;
            head = temp;
            head->next = nullptr;

        }
    }
    bool Game(int x, int y)
    {
        if (x < 1 || x >= width || y < 1 || y >= height)
        {
            GameOver = true;
            return true;
        }
        Snakee* current = head;
        while (current != nullptr)
        {
            if (current->x == x && current->y == y)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void draw() {
        system("cls");

        for (int i = 0; i < width; i++) {
            cout << '_';
        }
        cout << "\n";

        for (int i = 1; i < height-1 ; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0 || j == width -1) {
                    cout << '|';
                }
                else if (i == head->y && j == head->x) {
                    cout << 'O';
                }
                else if (i == foodY && j == foodX) {
                    cout << '*';
                }
                else {
                    bool isBodyPart = false;
                    Snakee* current = head->next;
                    while (current != nullptr) {
                        if (current->x == j && current->y == i) {
                            std::cout << 'o';
                            isBodyPart = true;
                            break;
                        }
                        current = current->next;
                    }
                    if (!isBodyPart) {
                        cout << '.';
                    }
                }
            }
            cout << "\n";
        }
        for (int i = 0; i < width; ++i) {
            cout << '-';
        }
        cout << "\n";
    }
};

int main()
{
    setlocale(0, "rus");
    Snake g;
    g.head = new Snakee(10, 1);
    g.genFood();
    while (!GameOver)
    {
        g.move();
        g.draw();
        Sleep(700);
    }
   cout << "Игра окончена";
    return 0;
}
