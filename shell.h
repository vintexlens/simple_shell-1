#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <fcntl.h>

#define LAUNCH_RUNTIME_PROCESS 7
#define DONT_CREATE_NEW_CHILD_PROCESS 6
#define TERMINATE_PROCESS_EXECUTION 5
#define PREFIX 4
#define EQUAL 3
#define NONE 2
#define POSITIVE 1
#define NEGATIVE 0

extern char **environ;

extern int status;

extern int lineNumber;

extern char *nameOfShell;

/**
 * struct Alias - aliases linked list
 * @node_name: alias name
 * @nodeValue: command called by alias
 * @nextNode: points to nextNode node
 */
typedef struct Alias
{
	char *node_name;
	char *nodeValue;
	struct Alias *nextNode;
} alias;



int commandRuntimeHandler(char **arguements);

int checkIfCommandInbuilt(char **arguements);

int logicalOperatorHandler(char **arguements, char operator, int last_compare);

char *checkIfNotBuiltIn(char **arguements);

int runCommand(char **arguements);

char *inputCleaner(char *previousBuffer, size_t *previousSize);

int errorCheckerForInput(char *pointer);

void displayErrorMessage(char *arg0, char *arg1);

void *_realloc(void *pointer, unsigned int previousSize, unsigned int createdArraySize);

int _getline(char **line_pointer, size_t *n, int file);

char *checkIfArgumentIsVariable(char *arguement);

int getStringLength(char *string);

char *copyString(char *src);

char *concatenateString(char *firstString, char *secondString);

int compareString(char *firstString, char *secondString, int pref_or_match);

char *findArrayElement(char **array, char *itemName);

char **createArray(char *string, char endOfListEntryChar, char **ifSemiColonPointer);

int lengthOfList(char **list, char *entry);

char **duplicateArray(char **previousArray, int createdArraySize);

int releaseArray(char **arguements);

int configureEnvironmentVariable(const char *name, const char *value);

int deleteEnvironmentVariable(const char *name);

int changeDirectory(char *name);

int commandAliasProcessing(char **arguements, int free);

int releaseAlias(alias *aliasPointer);

int replaceIfAlias(char **arguements, alias *aliasPointer);

int displayAliases(alias *aliasPointer);

int displayAliasValue(char *arguement, alias *aliasPointer);

int configureAlias(char *arguement, alias *aliasPointer, char *setValue);

int displayEnvironMentVariable(void);

char *_itoa(int integer);

int stringToInteger(char *string);

#endif
