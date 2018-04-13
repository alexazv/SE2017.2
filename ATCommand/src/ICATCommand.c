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

//separate by delimiter ',' ignoring quotes
static int separateByToken(char *string, const char delimiter){

    int isOnQuotes = 0;
    for(int i = 0; string[i] != '\0'; i++){
        if(string[i] == '"')
            isOnQuotes = !isOnQuotes;

        if(!isOnQuotes) {
            if (string[i] == delimiter) {
                string[i] = '\0';
            }
        }
    }

    //TODO: still destroys the string, though
    if(isOnQuotes)
        return kFAIL;

    return kOK;
}

static Command * ICATCommandGetCommand(char *key){

    for(int i = 0; i < commandListSize; i++)
        if(strcmp(commandList[i].command, key) == 0)
            return &commandList[i];

    return NULL;
}

//returns pointer to element after token
//TODO: check safety
static uint8_t * findNextToken(uint8_t * string, uint8_t token){
    uint8_t *p = string;
    int i;
    for (i = 0; p[i] != token; i++);
    p = &p[i+1];
    return p;
}

static int nextIndexOf(uint8_t * string, int start, const char token){

    int i = start;
    for (;string[i] != token && string[i] != '\0'; i++);

    if(string[i] == '\0')
        return -1;

    return i;

}

//copies substring from src to dst from index start until token is found or until string ends;
// returns index of found token or -1 if not found;
static int subStringUntilToken(char * src, char * dst, int startIndex, const char token){
    int endIndex = startIndex;
    for (;src[endIndex] != token && src[endIndex] != '\0'; endIndex++);

    strncpy(dst, src+startIndex, (size_t)endIndex-startIndex);
    dst[endIndex-startIndex] = '\0';

    if(src[endIndex] == '\0')
        return -1;


    return endIndex+1;
}

static int ICATCommandInvoker(){

    if(strcmp((char*)_buffer, "AT") == 0){
        printk("STATUS OK\n");
        return kOK;
    }

    char p[MAX_OP_SIZE];

    int current_index = 0;

    current_index = subStringUntilToken((char*)_buffer, p, current_index, '+');

    if(current_index == -1)
        return kFAIL;

    current_index = subStringUntilToken((char*)_buffer, p, current_index, '=');

    if(current_index == -1)
        return kFAIL;

    printk("RECEIVED COMMAND = %s\n", p);

    Command * command = ICATCommandGetCommand((char *) p); //change

    if (command == NULL) {
        printk("ERROR: COMMAND NOT FOUND\n");
        return kFAIL;
    }

    printk("FOUND COMMAND = %s\n", command->command);

    if(command->parameterNumber < 1){
        return command->callback(NULL, command->parameterNumber);
    }

    uint8_t * parameters[command->parameterNumber];

    for(int i = 0; i < command->parameterNumber; i++) {

        current_index = subStringUntilToken((char*)_buffer, p, current_index, ',');

        printk("RECEIVED PARAMETER = %s\n", p);

        if(command->parameterTypes[i] == INTEGER){
            parameters[i] = (uint8_t*)atoi(p);
            /*uint64_t base = 1;
            uint64_t number = 0;
            for(int i = 0; p[0] != '\0'; p++){

                if(p[0] < '0' || p[0] > '9')
                    return kFAIL;

                number += base*(p[0] - '0');
                base *= 10;
            }
            parameters[i] = number;*/
        }
        else if(command->parameterTypes[i] == STRING){
            parameters[i] = (uint8_t*)&p;
        }
    }

    return command->callback(parameters, command->parameterNumber);

    return 1;

}


int ICATCommandAddCommand(char * command, int (*callback)(uint8_t **data, uint8_t size), uint8_t parameterNumber, ParameterTypes * parameterTypes){
    if(commandListSize == MAX_COMMANDS-1)
        return kFAIL;
    Command new_command = {command, callback, parameterNumber, NULL};
    commandList[commandListSize] = new_command;
    memcpy(commandList[commandListSize].parameterTypes, parameterTypes, sizeof(ParameterTypes)*parameterNumber);

    commandListSize++;

    return kOK;
}
