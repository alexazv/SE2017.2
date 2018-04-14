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

static uint8_t _buffer[MAX_STRING_SIZE];
static uint8_t _bufferSize;

static Command _commandList[MAX_COMMANDS];
static uint8_t _commandListSize;

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

    for(int i = 0; i < _commandListSize; i++)
        if(strcmp(_commandList[i].command, key) == 0)
            return &_commandList[i];

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

    char bufferSubString[MAX_OP_SIZE];

    int current_index = 0;

    current_index = subStringUntilToken((char*)_buffer, bufferSubString, current_index, '+');

    if(current_index == -1){
        if(strcmp(bufferSubString, "AT") == 0) {
            printk("STATUS OK\n");
            return kOK;
        } else{
            printk("ERROR: COMMANDS MUST BEGIN WITH \"AT\"\n");
            return kFAIL;
        }

    }

    current_index = subStringUntilToken((char*)_buffer, bufferSubString, current_index, '=');

    printk("RECEIVED COMMAND = %s\n", bufferSubString);

    Command * command = ICATCommandGetCommand((char *) bufferSubString); //change

    if (command == NULL) {
        printk("ERROR: COMMAND NOT FOUND\n");
        return kFAIL;
    }

    if(command->parameterNumber < 1 && current_index != -1){
        printk("TOO MANY ARGUMENTS FOR COMMAND %s: EXPECTED %d\n",command->command, command->parameterNumber);
        return kFAIL;
    }

    printk("FOUND COMMAND = %s\n", command->command);

    uint8_t * parameters[MAX_PARAMETERS_SIZE];
    StringParameter stringParameters[MAX_PARAMETERS_SIZE];
    uint8_t intParameters[MAX_PARAMETERS_SIZE];

    uint8_t parameterCount = 0;

    for(int i = 0; i < command->parameterNumber; i++) {

        current_index = subStringUntilToken((char *) _buffer, bufferSubString, current_index, ',');

        if(current_index == -1 && i != command->parameterNumber-1){
            printk("TOO FEW ARGUMENTS FOR COMMAND %s: EXPECTED %d\n",command->command, command->parameterNumber);
            return kFAIL;
        }

        switch(command->parameterTypes[i]) {

            case INTEGER:;

                int value = atoi(bufferSubString);

                if(value > 255){

                    intParameters[parameterCount] = (value & 0xff);
                    parameters[parameterCount] = &intParameters[parameterCount];

                    parameterCount++;

                    intParameters[parameterCount] = (value >> 8);
                    parameters[parameterCount] = &intParameters[parameterCount];
                } else {
                    intParameters[parameterCount] = (uint8_t)value;
                    parameters[parameterCount] = &intParameters[parameterCount];
                }
                //printk("RECEIVED PARAMETER = %d\n", *parameters[parameterCount]);
                parameterCount++;
                break;

            case STRING:

                if (!removeQuotes(bufferSubString)){
                    printk("ERROR: STRING PARAMETER %s MUST BE ON QUOTES\n", stringParameters[parameterCount].value);
                    return kFAIL;
                }

                strcpy(stringParameters[parameterCount].value, bufferSubString);

                parameters[parameterCount] = (uint8_t *) stringParameters[parameterCount].value;

                //printk("RECEIVED PARAMETER = \"%s\"\n", (char *) parameters[parameterCount]);
                parameterCount++;
                break;

            default:
                //printk("VOID PARAMETER");
                break;
        }

        //current_index = subStringUntilToken((char *) _buffer, bufferSubString, current_index, ',');
    }

    if(current_index != -1){
        printk("TOO MANY ARGUMENTS FOR COMMAND %s: EXPECTED %d\n",command->command, command->parameterNumber);
        return kFAIL;
    }

    return command->callback(parameters, parameterCount);
}

int ICATCommandAddCommand(char * command, int (*callback)(uint8_t **data, uint8_t size),
                          uint8_t parameterNumber, uint8_t parameterType, ... ){
    if(_commandListSize == MAX_COMMANDS)
        return kFAIL;

    uint8_t parameters[MAX_PARAMETERS_SIZE];

    va_list ap;
    va_start(ap, parameterType);
    parameters[0] = parameterType;
    for(int i = 1; i < parameterNumber; i++){
        int x = va_arg(ap,int);
        parameters[i] = x;
    }
    va_end(ap);

    Command new_command;
    new_command.command = command;
    new_command.parameterNumber = parameterNumber;
    new_command.callback = callback;
    memcpy(new_command.parameterTypes, parameters, sizeof(parameters));

    _commandList[_commandListSize] = new_command;
    /*for (int i = 0; i < parameterNumber; ++i) {
        printk("RECEIVED PARAMETER TYPE = %d\n",  _commandList[_commandListSize].parameterTypes[i]);
    }*/

    printk("ADDED COMMAND: %s\n", _commandList[_commandListSize].command);
    _commandListSize++;

    return kOK;
}
