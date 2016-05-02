/*
    Exercise 17: Heap and Stack Memory Allocation
    Manage small, simple databases.
*/

#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 511
#define MAX_RECORDS 100

struct Address {
    int id;
    int is_valid;
    char name[MAX_DATA + 1];
    char email[MAX_DATA + 1];
};

struct Database {
    struct Address records[MAX_RECORDS];
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void Database_close(struct Connection *);

void die(struct Connection *conn, const char *fmt, ...)
{
    Database_close(conn);

    va_list ap;
    va_start(ap, fmt);

    /* This buffer length is arbitrary. */
    const size_t buflen = 1024;
    static char message[buflen] = "ERROR: ";

    if (errno) {
        vsnprintf(message, buflen, fmt, ap);
        perror(message);
    } else {
        vsnprintf(strchr(message, '\0'), buflen - strlen(message), fmt, ap);
        fprintf(stderr, "%s\n", message);
    }

    va_end(ap);
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1)
        die(conn, "Failed to load database.");
}

struct Connection *Database_open(const char *filename, char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn)
        die(conn, "Memory error");

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db)
        die(conn, "Memory error");

    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");
        if (conn->file)
            Database_load(conn);
    }

    if (!conn->file)
        die(conn, "Failed to open the file");

    return conn;
}

void Database_close(struct Connection *conn)
{
    if (conn) {
        if (conn->file)
            fclose(conn->file);
        if (conn->db)
            free(conn->db);
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1)
        die(conn, "Failed to write database.");

    rc = fflush(conn->file);
    if (rc == -1)
        die(conn, "Cannot flush database.");
}

void Database_create(struct Connection *conn)
{
    for (size_t i = 0; i < MAX_RECORDS; ++i) {
        // make a prototype to initialize it
        struct Address addr = {
            .id = i,
            .is_valid = 0
        };
        // then just assign it
        conn->db->records[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id,
                  const char *name, const char *email)
{
    assert(id < MAX_RECORDS);

    struct Address *addr = &conn->db->records[id];
    if (addr->is_valid)
        die(conn, "Already set, delete it first");

    addr->is_valid = 1;

    char *res = strncpy(addr->name, name, MAX_DATA);
    if (!res)
        die(conn, "Name copy failed");
    addr->name[MAX_DATA] = '\0';

    res = strncpy(addr->email, email, MAX_DATA);
    if (!res)
        die(conn, "Email copy failed");
    addr->email[MAX_DATA] = '\0';
}

void Database_get(struct Connection *conn, int id)
{
    assert(id < MAX_RECORDS);

    struct Address *addr = &conn->db->records[id];
    if (!addr->is_valid)
        die(conn, "ID is not set");
    Address_print(addr);
}

void Database_delete(struct Connection *conn, int id)
{
    assert(id < MAX_RECORDS);

    struct Address addr = {
        .id = id,
        .is_valid = 0
    };
    conn->db->records[id] = addr;
}

void Database_list(struct Connection *conn)
{
    for (size_t i = 0; i < MAX_RECORDS; ++i) {
        struct Address *addr = &conn->db->records[i];
        if (addr->is_valid)
            Address_print(addr);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
        die(NULL, "USAGE: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);

    int id = (argc > 3) ? atoi(argv[3]) : 0;
    if (id < 0)
        die(conn, "ID cannot be negative");
    if (id >= MAX_RECORDS)
        die(conn, "There's not that many records.");

    switch (action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if (argc != 4)
                die(conn, "Need an id to get");
            Database_get(conn, id);
            break;

        case 's':
            if (argc != 6)
                die(conn, "Need id, name, email to set");
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if (argc != 4)
                die(conn, "Need id to delete");
            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;

        default:
            die(conn, "Invalid action: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(conn);
    return 0;
}
