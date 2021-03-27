#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

struct Customer {
   int  customerNumber;
   char customerName[50];
   char contactFirstName[100];
   char contactLastName[100];
} customer;

/*struct Customers {
    struct Customer *arr;
    unsigned int count;
} customers;*/

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
    return counted; // count val, array starts at 0
}

struct Customer * get_data()
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

    // char *o_ptr = (char *)malloc(num_rows * sizeof(char)); // output;
    struct Customer customers[1000];
    unsigned int iterator = 0;

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        struct Customer customer;
        strcpy( customer.customerName, row[1]); // cannot be NULL
        strcpy( customer.contactFirstName, row[2] ? row[2] : NULL);
        strcpy( customer.contactLastName, row[3] ? row[3] : NULL);
        customer.customerNumber = atoi(row[0]);
        customers[iterator] = customer;
        // memcpy(customer, &customers, sizeof customers);
        puts(customers[iterator].customerName); // stuff gets corretly written into struct array.
        iterator = iterator + 1;
    }

    mysql_free_result(result);
    mysql_close(con);

    return customers;
}

// FIXME: this doesnt work, segfault... something with the length...
void objToJsonSerialize(struct Customer *customers) {
    int length = sizeof(customers);
    for (int i = 1; i < length; i++) {
        // printf("%s", customers[i].customerName);
    }
}

int main(int argc, char **argv) {
    // int num_rows = get_num_rows();
    // printf("num rows: %d", num_rows);
    // printf("%s", get_data(num_rows));
    objToJsonSerialize(get_data());
    exit(0);
}
