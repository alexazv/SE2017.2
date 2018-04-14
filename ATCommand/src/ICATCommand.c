//
// Created by alexandre on 05/04/18.
//
#include "ICATCommand.h"
#include <stdint.h>
#include <string.h>
#include <board.h>
#include <gpio.h>
#include <stdlib.h>
#include <zephyr.h>
#include <device.h>
#include <misc/printk.h>
#include <uart.h>
#include "uart_driver.h"

static uint8_t _buffer[MAX_BUFFER_SIZE];
static uint8_t _bufferSize;

static Command commandList[MAX_COMMANDS];
static uint8_t commandListSize;

static void ICATCommandParser(uint8_t data){

    printk("%c", data);

    if(data != CARRIAGE_RETURN){
        _buffer[_bufferSize] = data;
        _bufferSize++;
    } else {
        printk("\n");
        _buffer[_bufferSize] = '\0';
        ICATCommandInvoker();
        _bufferSize = 0;
    }
}

void ICATCommandStart(void){
    DriverOpen();
    DriverSetCallback(ICATCommandParser);
    printk("ATCOMMAND INITIALIZED\n");
    _bufferSize = 0;
}

static Command * ICATCommandGetCommand(char *key){

    for(int i = 0; i < commandListSize; i++)
        if(strcmp(commandList[i].command, key) == 0)
            return &commandList[i];

    return NULL;
}

//copies substring from src to dst from index start until token is found or until string ends;
// returns index of found token or -1 if not found;
static int subStringUntilToken(char * src, char * dst, int startIndex, const char token){
    int endIndex;
    int isOnQuotes = 0;
    for (endIndex = startIndex; src[endIndex] != '\0'; endIndex++){
        if(src[endIndex] == '\"')
            isOnQuotes = !isOnQuotes;

        if(!isOnQuotes) {
            if (src[endIndex] == token) {
                break;
            }
        }
    }

    strncpy(dst, src+startIndex, (size_t)endIndex-startIndex);
    dst[endIndex-startIndex] = '\0';

    if(src[endIndex] == '\0')
        return -1;

    return endIndex+1;
}

//removes quotes from start and finish of function
//returns 0 if cannot find quotes
//returns 1 otherwise
static int removeQuotes(char * src){

    int size = strlen(src);

    if(src[0] != '\"' || src[size-1] != '\"')
        return 0;

    //remove last quote
    src[size-1] = '\0';
    //shift string left by 1
    memmove(src, src+1, (size-1)* sizeof(char));

    return 1;
}

static int ICATCommandInvoker(){

    if(strcmp((char*)_buffer, "AT") == 0){
        printk("STATUS OK\n");
        return kOK;
    }

    char p[MAX_OP_SIZE];

    int current_index = 0;

    current_index = subStringUntilToken((char*)_buffer, p, current_index, '+');

    if(current_index == -1 || strcmp(p, "AT") != 0) {
        printk("ERROR: COMMANDS MUST BEGIN WITH \"AT\"\n");
        return kFAIL;
    }

    current_index = subStringUntilToken((char*)_buffer, p, current_index, '=');

    printk("RECEIVED COMMAND = %s\n", p);

    Command * command = ICATCommandGetCommand((char *) p); //change

    if (command == NULL) {
        printk("ERROR: COMMAND NOT FOUND\n");
        return kFAIL;
    }

    printk("FOUND COMMAND = %s\n", command->command);

    if(command->parameterNumber < 1){
        return command->callback((uint8_t*)NULL, command->parameterNumber);
    }

    uint8_t * parameters[command->parameterNumber];
    StringParameter parameters2[command->parameterNumber];

    for(int i = 0; i < command->parameterNumber; i++) {

        switch(command->parameterTypes[i]) {

            case INTEGER:
                current_index = subStringUntilToken((char *) _buffer, p, current_index, ',');
                parameters[i] = (uint8_t *) atoi(p);

                printk("RECEIVED PARAMETER = %d\n", (int)parameters[i]);
                break;

            case STRING:

                current_index = subStringUntilToken((char *) _buffer, parameters2[i].value, current_index, ',');

                if (!removeQuotes(parameters2[i].value)) {
                    printk("ERROR: STRING PARAMETER %s MUST BE ON QUOTES\n", parameters2[i].value);
                    return kFAIL;
                }

                parameters[i] = (uint8_t *) parameters2[i].value;

                printk("RECEIVED PARAMETER = \"%s\"\n", (char *) parameters[i]);
                break;

            default:
                printk("VOID PARAMETER: %d\n", command->parameterTypes[i]);
                break;
        }
    }

    return command->callback(parameters, command->parameterNumber);
}

void listCommands(){
    printk("{");
    for(int i = 0; i < commandListSize; i++){
        printk("[\n");
        printk("%s\n", commandList[i].command);
        for(int j = 0; j < commandList[i].parameterNumber; j++){
            printk("%d\n", commandList[i].parameterTypes[j]);
        }
        printk("]\n");
    }
}


int ICATCommandAddCommand(char * command, int (*callback)(uint8_t **data, uint8_t size),
                          uint8_t parameterNumber, uint8_t parameterType, ... ){
    if(commandListSize == MAX_COMMANDS)
        return kFAIL;

    uint8_t parameters[MAX_PARAMETERS_SIZE];

    va_list ap;
    va_start(ap, parameterType);
    parameters[0] = parameterType;
    printk("RECEIVED PARAMETER = %d\n", parameters[0]);
    for(int i = 1; i < parameterNumber; i++){
        int x = va_arg(ap,int);
        parameters[i] = x;
    }
    va_end(ap);

    Command new_command; //= {command, callback, parameterNumber, parameters};
    //strcpy(new_command.command, command);
    new_command.command = command;
    new_command.callback = callback;
    new_command.parameterNumber = parameterNumber;
    memcpy(new_command.parameterTypes, parameters, sizeof(parameters));

    commandList[commandListSize] = new_command;
    for (int i = 0; i < parameterNumber; ++i) {
        printk("RECEIVED PARAMETER TYPE = %d\n",  commandList[commandListSize].parameterTypes[i]);
    }

    printk("ADDED COMMAND: %s\n", commandList[commandListSize].command);
    commandListSize++;

    return kOK;
}
