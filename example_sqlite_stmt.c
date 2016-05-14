#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

static const char* const db_name_ = "test.db";

int main(int argc, char *argv[])
{
    sqlite3* db_handler_ = NULL;
    if (sqlite3_open(db_name_, &db_handler_)) {
        fprintf(stderr, "error: open %s failed\n", db_name_);
        exit(1);
    }

    char* error_msg_ = NULL;
    const char* sql_create_table_ = "CREATE TABLE COMPANY ( \
                                    ID INT PRIMARY KEY,     \
                                    NAME TEXT  NOT NULL,    \
                                    AGE INT NOT NULL,       \
                                    ADDRESS CHAR(50),       \
                                    SALARY REAL )";
    const char* sql_insert_ = "INSERT INTO COMPANY ( NAME, AGE, ADDRESS, SALARY ) VALUES (?,?,?,?)";
    sqlite3_stmt* stmt_insert_ = NULL;

    if (sqlite3_exec(db_handler_, sql_create_table_, NULL, NULL, &error_msg_)) {
        fprintf(stderr, "error: Create table COMPANY failed, %s\n", error_msg_);
        sqlite3_close(db_handler_);
        exit(2);
    }

    if (sqlite3_prepare_v2(db_handler_, sql_insert_, -1, &stmt_insert_, NULL)) {
        fprintf(stderr, "error: Prepare stmt stmt_insert_ failed, %s\n", sqlite3_errmsg(db_handler_));
        exit(3);
    }

    const char* name_ = "Paul";
    int age_ = 29;
    const char* addr_ = "LA";
    double salary_ = 100000.0;
    int rc= sqlite3_bind_text(stmt_insert_, 1, name_, strlen(name_), NULL);
    if (rc) {
        fprintf(stderr, "error: Bind %s to %d failed, %s\n", name_, rc, sqlite3_errmsg(db_handler_));
        sqlite3_close(db_handler_);
        exit(4);
    }

    rc = sqlite3_bind_int(stmt_insert_, 2, age_);
    if (rc) {
        fprintf(stderr, "error: Bind %d to %d failed, %s\n", age_, rc, sqlite3_errmsg(db_handler_));
        sqlite3_close(db_handler_);
        exit(4);
    }

    rc= sqlite3_bind_text(stmt_insert_, 3, addr_, strlen(name_), NULL);
    if (rc) {
        fprintf(stderr, "error: Bind %s to %d failed, %s\n", addr_, rc, sqlite3_errmsg(db_handler_));
        sqlite3_close(db_handler_);
        exit(4);
    }

    rc = sqlite3_bind_double(stmt_insert_, 4, salary_);
    if (rc) {
        fprintf(stderr, "error: Bind %lf to %d failed, %s\n", salary_, rc, sqlite3_errmsg(db_handler_));
        sqlite3_close(db_handler_);
        exit(4);
    }

    rc = sqlite3_step(stmt_insert_);
    if(SQLITE_DONE != rc) {
        fprintf(stderr, "insert statement didn't return DONE (%i): %s\n", rc, sqlite3_errmsg(db_handler_));
    } else {
        printf("INSERT completed\n\n");
    }

    sqlite3_finalize(stmt_insert_);
    sqlite3_close(db_handler_);
    return 0;
}
