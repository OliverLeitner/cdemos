#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct Customer {
   int  customerNumber;
   char customerName[50];
   char contactFirstName[100];
   char contactLastName[100];
} customer;

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int get_num_rows(void)
{
    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "demo", "123",
                "classicmodels", 0, NULL, 0) == NULL)
    {
        finish_with_error(con);
    }

    if (mysql_query(con, "SELECT count(*) FROM customers"))
    {
        finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
        finish_with_error(con);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int counted = atoi(row[0]);
    return counted;
}

struct Customer * get_data(int num_rows)
{
    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "demo", "123",
                "classicmodels", 0, NULL, 0) == NULL)
    {
        finish_with_error(con);
    }

    if (mysql_query(con, "SELECT * FROM customers"))
    {
        finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
        finish_with_error(con);
    }

    int num_fields = mysql_num_fields(result);

    struct Customer *customers[1000];
    customer *c_ptr = (customer *)malloc(num_rows * sizeof(customer));
    unsigned int iterator = 0;

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        struct Customer scustomer;
        strcpy( scustomer.customerName, row[1]); // cannot be NULL
        strcpy( scustomer.contactFirstName, row[2] ? row[2] : NULL);
        strcpy( scustomer.contactLastName, row[3] ? row[3] : NULL);
        scustomer.customerNumber = atoi(row[0]);
        c_ptr[iterator] = scustomer;
        iterator++;
    }

    mysql_free_result(result);
    mysql_close(con);

    return c_ptr;
}

void objToJsonSerialize(struct Customer *customers, int num_rows) {
    for (int i = 0; i < num_rows; i++) {
        puts(customers[i].customerName);
    }
}

int main(int argc, char **argv) {
    int num_rows = get_num_rows();
    objToJsonSerialize(get_data(num_rows), num_rows);
    exit(0);
}
