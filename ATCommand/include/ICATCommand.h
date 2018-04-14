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

#define MAX_STRING_SIZE 30
#define MAX_PARAMETERS_SIZE 8
#define MAX_BUFFER_SIZE 30
#define MAX_COMMANDS 30
#define MAX_OP_SIZE 30

#define INTEGER 0
#define STRING 1
#define VOID 2

//Private

typedef struct StringParameter{
    char value[MAX_OP_SIZE];
}StringParameter;

typedef struct Command{
    char * command;
    int (*callback)(uint8_t**, uint8_t size);
    uint8_t parameterNumber;
    uint8_t parameterTypes[MAX_PARAMETERS_SIZE];
}Command;

static int ICATCommandInvoker();
static void ICATCommandParser(uint8_t data);
static Command * ICATCommandGetCommand(char *key);

//Public
void ICATCommandStart(void);
void listCommands();

int ICATCommandAddCommand(char * command, int (*callback)(uint8_t **data, uint8_t size),
                          uint8_t parameterNumber, uint8_t parameterType, ...);

#endif //ICATCOMMAND_ATCOMMAND_H
