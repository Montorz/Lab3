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

    // Создание казино с 5 пользователями и 2 слотами
    Casino casino(5, 2);

    // Добавление пользователей
    casino.addUser(0, User(1, "Леха", "леха123", "password123", "2024-10-08", 1000.0));
    casino.addUser(1, User(2, "Коля", "коля321", "password321", "2024-10-08", 500.0));
    casino.addUser(2, User(3, "Маша", "masha789", "password789", "2024-10-09", 2000.0));
    casino.addUser(3, User(4, "Иван", "ivan123", "ivanpass", "2024-10-10", 1500.0));
    casino.addUser(4, User(5, "Ольга", "olga456", "olgapass", "2024-10-11", 3000.0));

    // Добавление слотов
    casino.addSlot(0, Slot(1, "Lucky 7", 100, 10, 0.95));
    casino.addSlot(1, Slot(2, "Fruit Machine", 50, 5, 1.20));

    // Создание и добавление записей
    GameHistory history1(Slot(1, "Lucky 7", 100, 10, 0.95), User(1, "Леха", "леха123", "password123", "2024-10-08", 1000.0), 1, 100.0, 95.0, "2024-10-10");
    GameHistory history2(Slot(2, "Fruit Machine", 50, 5, 1.20), User(2, "Коля", "коля321", "password321", "2024-10-08", 500.0), 2, 50.0, 60.0, "2024-10-11");
    GameHistory history3(Slot(1, "Lucky 7", 100, 10, 0.95), User(3, "Маша", "masha789", "password789", "2024-10-09", 2000.0), 3, 150.0, 140.0, "2024-10-12");

    casino.addGameHistory(history1);
    casino.addGameHistory(history2);
    casino.addGameHistory(history3);

    // Отображение всех записей
    printf("Все записи истории игр:\n");
    casino.displayGameHistories();

    // Транзакции
    Transaction transaction1(1, 1, 100.0f, "2024-10-10 12:00");
    printf("\nТранзакция:\n");
    printf("ID транзакции: %d, ID пользователя: %d, Сумма: %.2f, Время: %s\n",
        transaction1.getUserId(), transaction1.getUserId(), transaction1.getAmount(), "2024-10-10 12:00");

    return 0;
}