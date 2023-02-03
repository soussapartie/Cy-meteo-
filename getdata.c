#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

typedef struct list_s {

    int temperature;
    // int timestamp;
    /*cette ligne doit être delete */
    char *date;
    int tkt;

    struct list_s *next;

} list_t;

void error(void)
{
    fprintf(stderr, "Error message\n");
    exit(1);
}

/*
oublie pas de swap tous les champs de la structure :

void bubble_sort(list_t *list)
{
    //
        //
            if (list->temperature > list2->temperature) {
                int tmp = list->temperature;
                list->temperature = list2->temperature;
                list2->temperature = tmp;
                int tkt = list->tkt;
            }
}

*/

char *open_file(const char *filename)
{
    struct stat sb;
    int fd = open(filename, O_RDONLY);
    char *buffer = NULL;
    ssize_t rd = 0;

    if (fstat(fd, &sb) == -1) {
        error();
    }
    buffer = (char *) malloc(sizeof(char) * (sb.st_size + 1));
    if (buffer == NULL){
        error();
    }
    rd = read(fd, buffer, sb.st_size);
    if (rd == -1){
        error();
    }
    buffer[rd - 1] = '\0';

    return buffer;
}

char **str_to_word_arr(char *buffer, const char *delim)
{
    char **arr = (char **) malloc(sizeof(char *) * (strlen(buffer) + 1));
    int i = 0;
    char *token = strtok(buffer, delim);

    while (token != NULL) {
        arr[i++] = strdup(token);
        token = strtok(NULL, delim);
    }
    arr[i] = NULL;
    return arr;
}

list_t *create_node(int temp, char *date, int tkt)
{
    list_t *node = (list_t *) malloc(sizeof(list_t));

    node->temperature = temp;
    node->date = strdup(date);
    node->tkt = tkt;
    node->next = NULL;
    return node;
}

void add_to_list(list_t **list, int temp, char *date, int tkt)
{
    list_t *a = NULL, *b = NULL;

    if (*list == NULL) {
        a = create_node(temp, date, tkt);
        *list = a;
    }
    else {
        a = *list;
        while (a->next != NULL)
            a = a->next;
        b = create_node(temp, date, tkt);
        a->next = b;
    }
}

void print_list(list_t **list)
{
    for (list_t *tmp = *list; tmp != NULL; tmp = tmp->next) {
        printf("%d | %s | %d\n", tmp->temperature, tmp->date, tmp->tkt);
    }
}

void free_list(list_t **list)
{
    list_t *tmp;

    while (*list != NULL) {
        tmp = *list;
        *list = (*list)->next;
        free(tmp->date);
        free(tmp);
    }
}

void manage_line(list_t **list, char *str)
{
    char **arr = str_to_word_arr(str, ";");

    // struct tm tm;
    // strptime(arr[1], "%Y-%m-%dT%H:%M:%S%z", &tm);
    // time_t time = mktime(&tm);
    // int timestamp = (int)time;
    // add_to_list(&list, arr[0], timestamp, arr[2]);

    /* cette ligne doit etre delete */
    add_to_list(list, atoi(arr[0]), arr[1], atoi(arr[2]));

    for (int i = 0; arr[i] != NULL; i++) {
        free(arr[i]);
    }
    return;
}

size_t cactus(const char *str)
{
    size_t len = 0;

    if (str[0] == ';') {
        len++;
    }
    for (int i = 1; i < strlen(str); i++) {
        if (str[i - 1] == ';' && str[i] == ';') {
            len++;
        }
    }
    if (str[strlen(str) - 1] == ';') {
        len++;
    }
    return len;
}

char *new_str(char *new_str, const char *old_str)
{
    int j = 0;

    if (old_str[0] == ';') {
        new_str[j] = '0';
        new_str[j + 1] = ';';
        j += 2;
    }
    new_str[j++] = old_str[0];
    for (int i = 1; i < strlen(old_str); i++) {
        if (old_str[i - 1] == ';' && old_str[i] == ';') {
            new_str[j] = '0';
            new_str[j + 1] = ';';
            j += 2;
        } else {
            new_str[j++] = old_str[i];
        }
    }
    if (old_str[strlen(old_str) - 1] == ';') {
        new_str[j] = '0';
    }
    return new_str;
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        error();
    }
    char *buffer = open_file(argv[1]);
    char **arr = str_to_word_arr(buffer, "\r\n");
    list_t *list = NULL;

    for (int i = 0; arr[i] != NULL; i++){
        size_t len = cactus(arr[i]) + strlen(arr[i]);
        char *str = (char *) malloc(sizeof(char) * (len + 1));
        str[len] = '\0';
        str = new_str(str, arr[i]);
        manage_line(&list, str);
    }
    print_list(&list);
    free_list(&list);

    free(buffer);
    for (int i = 0; arr[i] != NULL; i++){
        free(arr[i]);
    }
    free(arr);
    return 0;
}
