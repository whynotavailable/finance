# TBD

## To build (outside of qt creator).

```
export CMAKE_PREFIX_PATH="{YOUR QT CMAKE DIR}"
cmake .

make
```

I have literally no idea if this will build outside of mac with the current lists. Try it and let me know if it doesn't
lol.

```cpp
#include <iostream>
#include <sqlite3.h>
#include <stdexcept>

class Database {
private:
    static Database* instance;
    sqlite3* db;

    Database() {
        int rc = sqlite3_open("mydb.db", &db);
        if (rc) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
    }

    ~Database() {
        sqlite3_close(db);
    }

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

public:
    static Database* getInstance() {
        if (instance == nullptr) {
            instance = new Database();
        }
        return instance;
    }

    sqlite3* getDB() {
        return db;
    }
};

Database* Database::instance = nullptr;

int main() {
    try {
        Database* db = Database::getInstance();

        // Use the database connection
        // ...

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
```
