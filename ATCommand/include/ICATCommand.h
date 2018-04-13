//
// Created by alexandre on 05/04/18.
//

#ifndef ICATCOMMAND_ATCOMMAND_H
#define ICATCOMMAND_ATCOMMAND_H
#include <stdint.h>

//Private

#define CARRIAGE_RETURN 13
#define kOK 0
#define kFAIL 1

#define MAX_STRING_SIZE 20
#define MAX_PARAMETERS_SIZE 10
#define MAX_BUFFER_SIZE 20
#define MAX_COMMANDS 20
#define MAX_OP_SIZE 20

//Private

typedef enum ParameterType{
    INTEGER,
    STRING
}ParameterTypes;

typedef struct Command{
    char * command;
    int (*callback)(uint8_t**, uint8_t size);
    uint8_t parameterNumber;
    ParameterTypes parameterTypes[MAX_PARAMETERS_SIZE];
}Command;

static int ICATCommandInvoker();
static void ICATCommandParser(uint8_t data);
static Command * ICATCommandGetCommand(char *key);
static int nextIndexOf(uint8_t * string, int start, const char token);

//Public
void ICATCommandStart(void);

int ICATCommandAddCommand(char * command, int (*callback)(uint8_t **data, uint8_t size),
                          uint8_t parameterNumber, ParameterTypes * paramaterTypes);

#endif //ICATCOMMAND_ATCOMMAND_H
