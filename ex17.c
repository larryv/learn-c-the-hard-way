#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Address {
    int id;
    int set;
    char *name;
    char *email;
};

struct Database {
    long max_data;
    long max_rows;
    struct Address *rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

static struct Connection conn = {NULL, NULL};

void Database_close();

void die(const char *message)
{
    Database_close();

    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

void Database_load(void)
{
    struct Database *db = conn.db;
    struct Address *addr;

    if (fread(&db->max_data, sizeof(db->max_data), 1, conn.file) != 1)
        die("Failed to load database.");
    if (fread(&db->max_rows, sizeof(db->max_rows), 1, conn.file) != 1)
        die("Failed to load database.");

    db->rows = malloc(db->max_rows * sizeof(struct Address));
    if (!db->rows) die("Memory error.");

    for (addr = db->rows; addr < db->rows + db->max_rows; ++addr) {
        if (fread(&addr->id, sizeof(addr->id), 1, conn.file) != 1)
            die("Failed to load database.");
        if (fread(&addr->set, sizeof(addr->set), 1, conn.file) != 1)
            die("Failed to load database.");

        addr->name = malloc(db->max_data);
        if (!addr->name) die("Memory error.");
        if (fread(addr->name, db->max_data, 1, conn.file) != 1)
            die("Failed to load database.");

        addr->email = malloc(db->max_data);
        if (!addr->email) die("Memory error.");
        if (fread(addr->email, db->max_data, 1, conn.file) != 1)
            die("Failed to load database.");
    }
}

void Database_open(const char *filename, char mode)
{
    conn.db = malloc(sizeof(struct Database));
    if (!conn.db) die("Memory error.");

    if (mode == 'c') {
        conn.file = fopen(filename, "w");
    } else {
        conn.file = fopen(filename, "r+");

        if (conn.file) {
            Database_load();
        }
    }

    if (!conn.file) die("Failed to open the file.");
}

void Database_close(void)
{
    struct Database *db;

    if (conn.file) fclose(conn.file);
    if ((db = conn.db)) {
        if (db->rows) {
            struct Address *addr;
            for (addr = db->rows;
                    addr < db->rows + db->max_rows;
                    ++addr) {
                if (addr->name) free(addr->name);
                if (addr->email) free(addr->email);
            }
            free(db->rows);
        }
        free(db);
    }
}

void Database_write(void)
{
    struct Database *db = conn.db;
    struct Address *addr;

    rewind(conn.file);

    if (fwrite(&db->max_data, sizeof(db->max_data), 1, conn.file) != 1)
        die("Failed to write database.");
    if (fwrite(&db->max_rows, sizeof(db->max_rows), 1, conn.file) != 1)
        die("Failed to write database.");

    for (addr = db->rows; addr < db->rows + db->max_rows; ++addr)
        if (fwrite(&addr->id, sizeof(addr->id), 1, conn.file) != 1 ||
                fwrite(&addr->set, sizeof(addr->set), 1, conn.file) != 1 ||
                fwrite(addr->name, db->max_data, 1, conn.file) != 1 ||
                fwrite(addr->email, db->max_data, 1, conn.file) != 1)
            die("Failed to write database.");

    if (fflush(conn.file) == -1)
        die("Cannot flush database.");
}

void Database_create(long max_data, long max_rows)
{
    int i = 0;
    struct Database *db = conn.db;
    struct Address *addr;

    db->rows = malloc(db->max_rows * sizeof(struct Address));
    if (!db->rows) die("Memory error.");

    for (i = 0; i < db->max_rows; ++i) {
        addr = &db->rows[i];
        addr->id = i;
        addr->set = 0;

        addr->name = malloc(db->max_data);
        if (!addr->name) die("Memory error.");
        addr->name[0] = '\0';

        addr->email = malloc(db->max_data);
        if (!addr->email) die("Memory error.");
        addr->email[0] = '\0';
    }
}

void Database_set(int id, const char *name, const char *email)
{
    struct Database *db = conn.db;

    struct Address *addr = &db->rows[id];
    if (addr->set) die("Already set, delete it first.");

    addr->set = 1;
    char *res = strncpy(addr->name, name, db->max_data);
    if (!res) die("Name copy failed");
    res[db->max_data - 1] = '\0';

    res = strncpy(addr->email, email, db->max_data);
    if (!res) die("Email copy failed");
    res[db->max_data - 1] = '\0';
}

void Database_get(int id)
{
    struct Address *addr = &conn.db->rows[id];

    if (addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set.");
    }
}

void Database_delete(int id)
{
    struct Address *addr = &conn.db->rows[id];
    addr->set = 0;
    addr->name[0] = '\0';
    addr->email[0] = '\0';
}

void Database_list(void)
{
    int i = 0;
    struct Database *db = conn.db;

    for (i = 0; i < db->max_rows; i++) {
        struct Address *cur = &db->rows[i];

        if (cur->set) {
            Address_print(cur);
        }
    }
}

void Database_find(const char *string)
{
    struct Database *db = conn.db;
    struct Address *addr;
    int match;

    for (addr = db->rows; addr < db->rows + db->max_rows; ++addr) {
        match = strstr(addr->name, string) || strstr(addr->email, string);
        if (addr->set && match)
            Address_print(addr);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
        die("USAGE: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    Database_open(filename, action);
    int id = 0;

    if (argc > 3) id = atoi(argv[3]);
    if (action != 'c' && id >= conn.db->max_rows)
        die("There's not that many records.");
    long max_data, max_rows;

    switch (action) {
    case 'c':
        max_data = (argc >= 4) ? strtol(argv[3], NULL, 10) : 512;
        max_rows = (argc >= 5) ? strtol(argv[4], NULL, 10) : 100;
        Database_create(max_data, max_rows);
        Database_write();
        break;

    case 'g':
        if (argc < 4) die("Need an id or id range to get.");

        Database_get(id);
        break;

    case 's':
        if (argc < 6) die("Need id, name, email to set.");

        Database_set(id, argv[4], argv[5]);
        Database_write();
        break;

    case 'd':
        if (argc < 4) die("Need id or id range to delete.");

        Database_delete(id);
        Database_write();
        break;

    case 'l':
        Database_list();
        break;

    case 'f':
        if (argc < 4) die("Need string to search for.");

        Database_find(argv[3]);
        break;

    default:
        die("Invalid action, only: c=create, g=get, s=set, d=del, l=list, f=find");
    }

    Database_close();

    return 0;
}
