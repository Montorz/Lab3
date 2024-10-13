#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

class User {
private:
    int id;
    char name[50];
    char login[50];
    char password[50];
    char created_date[50];
    float balance;

public:
    User() : id(0), balance(0.0f) {
        strcpy(name, "");
        strcpy(login, "");
        strcpy(password, "");
        strcpy(created_date, "");
    }

    User(int id, const char* name, const char* login, const char* password, const char* created_date, float balance) {
        this->id = id;
        strncpy(this->name, name, sizeof(this->name));
        strncpy(this->login, login, sizeof(this->login));
        strncpy(this->password, password, sizeof(this->password));
        strncpy(this->created_date, created_date, sizeof(this->created_date));
        this->balance = balance;
    }

    int getId() const { return id; }
    const char* getName() const { return name; }
    float getBalance() const { return balance; }
};

class Slot {
private:
    int id;
    char name[50];
    int max_bet;
    int min_bet;
    float payout_ratio;

public:
    Slot() : id(0), max_bet(0), min_bet(0), payout_ratio(0.0f) {
        strcpy(name, "");
    }

    Slot(int id, const char* name, int max_bet, int min_bet, float payout_ratio) {
        this->id = id;
        strncpy(this->name, name, sizeof(this->name));
        this->max_bet = max_bet;
        this->min_bet = min_bet;
        this->payout_ratio = payout_ratio;
    }

    const char* getName() const { return name; }
    float getPayoutRatio() const { return payout_ratio; }
};

class Transaction {
private:
    int id;
    int user_id;
    float amount;
    char timestamp[20];

public:
    Transaction() : id(0), user_id(0), amount(0.0f) {
        strcpy(timestamp, "");
    }

    Transaction(int id, int user_id, float amount, const char* timestamp) {
        this->id = id;
        this->user_id = user_id;
        this->amount = amount;
        strncpy(this->timestamp, timestamp, sizeof(this->timestamp));
    }

    float getAmount() const { return amount; }
    int getUserId() const { return user_id; }
};

class GameHistory {
private:
    Slot slot;
    User user;
    int id;
    float bet_amount;
    float win_amount;
    char play_date[20];

public:
    GameHistory() : id(0), bet_amount(0.0f), win_amount(0.0f) {
        strcpy(play_date, "");
    }

    GameHistory(const Slot& slot, const User& user, int id, float bet_amount, float win_amount, const char* play_date)
        : slot(slot), user(user), id(id), bet_amount(bet_amount), win_amount(win_amount) {
        strncpy(this->play_date, play_date, sizeof(this->play_date));
    }

    void displayHistory() const {
        printf("История игры:\n");
        printf("Игрок: %s, Слот: %s, Ставка: %.2f, Выигрыш: %.2f, Дата игры: %s\n",
            user.getName(), slot.getName(), bet_amount, win_amount, play_date);
    }

    float getBetAmount() const { return bet_amount; }
    float getWinAmount() const { return win_amount; }
};

class Casino {
private:
    User* users;
    Slot* slots;
    GameHistory* gameHistories;
    int userCount;
    int slotCount;
    int historyCount;

public:
    Casino(int userCount, int slotCount)
        : userCount(userCount), slotCount(slotCount), historyCount(0) {
        users = new User[userCount];
        slots = new Slot[slotCount];
        gameHistories = new GameHistory[100];
    }

    void addUser(int index, const User& user) {
        if (index < userCount) {
            users[index] = user;
        }
    }

    void addSlot(int index, const Slot& slot) {
        if (index < slotCount) {
            slots[index] = slot;
        }
    }

    void addGameHistory(const GameHistory& history) {
        if (historyCount < 100) {
            gameHistories[historyCount++] = history;
        }
    }

    void displayGameHistories() const {
        for (int i = 0; i < historyCount; i++) {
            gameHistories[i].displayHistory();
        }
    }

    ~Casino() {
        delete[] users;
        delete[] slots;
        delete[] gameHistories;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    printf("Работа с классом User:\n");
    User* user = new User(1, "Алексей", "alex123", "alexpass", "2024-10-13", 1500.0);
    printf("ID: %d, Имя: %s, Баланс: %.2f\n", user->getId(), user->getName(), user->getBalance());
    delete user;

    printf("\nРабота с классом Slot:\n");
    Slot* slot = new Slot(1, "Lucky 7", 100, 10, 0.95);
    printf("Название: %s, Коэффициент выплат: %.2f\n", slot->getName(), slot->getPayoutRatio());
    delete slot;

    printf("\nРабота с классом Transaction:\n");
    Transaction* transaction = new Transaction(1, 1, 100.0f, "2024-10-13 12:00");
    printf("ID пользователя: %d, Сумма: %.2f, Время: %s\n",
        transaction->getUserId(), transaction->getAmount(), "2024-10-13 12:00");
    delete transaction;

    printf("\nРабота с классом GameHistory:\n");
    User player(2, "Борис", "boris123", "borispass", "2024-10-13", 2500.0);
    Slot game(2, "Fruit Machine", 50, 5, 1.2);
    GameHistory* history = new GameHistory(game, player, 1, 50.0f, 60.0f, "2024-10-13");
    history->displayHistory();
    delete history;

    printf("\nМассив динамических объектов User:\n");
    int userCount = 2;
    User** users = new User * [userCount];
    users[0] = new User(3, "Виктория", "viktoria789", "vikpass", "2024-10-13", 3500.0);
    users[1] = new User(4, "Дмитрий", "dmitry456", "dmitrypass", "2024-10-13", 2200.0);

    for (int i = 0; i < userCount; i++) {
        printf("Имя: %s, Баланс: %.2f\n", users[i]->getName(), users[i]->getBalance());
        delete users[i];
    }
    delete[] users;


    printf("\nДинамический массив объектов Slot:\n");
    int slotCount = 2;
    Slot* slotArray = new Slot[slotCount];
    slotArray[0] = Slot(1, "Lucky 7", 100, 10, 0.95);
    slotArray[1] = Slot(2, "Fruit Machine", 50, 5, 1.2);

    for (int i = 0; i < slotCount; i++) {
        printf("Название: %s, Коэффициент выплат: %.2f\n", slotArray[i].getName(), slotArray[i].getPayoutRatio());
    }
    delete[] slotArray;

    return 0;
}