#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

typedef struct ListString {
    int num;
    char *str;
    struct ListString *next;
} ListString;

typedef struct PassInfo {
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    ListString *env;
    ListString *history;
    ListString *alias;
    char **environ;
    int env_changed;
    int status;

    char **cmd_buf;
    int cmd_buf_type;
    int readfd;
    int histcount;
} PassInfo;

#define INFO_INIT \
{ \
    .arg = NULL, \
    .argv = NULL, \
    .path = NULL, \
    .argc = 0, \
    .line_count = 0, \
    .err_num = 0, \
    .linecount_flag = 0, \
    .fname = NULL, \
    .env = NULL, \
    .history = NULL, \
    .alias = NULL, \
    .environ = NULL, \
    .env_changed = 0, \
    .status = 0, \
    .cmd_buf = NULL, \
    .cmd_buf_type = 0, \
    .readfd = 0, \
    .histcount = 0 \
}

typedef struct Builtin {
    char *type;
    int (*func)(PassInfo *);
} BuiltinTable;

int ExecuteShell(PassInfo *info, char **environ);
int FindBuiltinCommand(PassInfo *info);
void FindCommand(PassInfo *info);
void ForkCommand(PassInfo *info);

int IsCommand(PassInfo *info, char *cmd);
char *DuplicateChars(char *str, int start, int end);
char *FindPath(PassInfo *info, char *cmd, char *path);

void PrintError(char *message);
int PutCharacter(char c, int fd);
int PutString(char *str, int fd);

int StrLen(char *str);
int StrCmp(char *str1, char *str2);
char *StartsWith(const char *str, const char *prefix);
char *StringConcatenate(char *str1, char *str2);

char *StringCopy(char *dest, const char *src);
char *StringDuplicate(const char *str);
void PrintString(char *str);
int PutCharacter(char c, int fd);

char *StringCopyN(char *dest, const char *src, int n);
char *StringConcatenateN(char *dest, const char *src, int n);
char *StringFindCharacter(char *str, char c);

char **StringTokenize(char *str, char *delimiters);
char **StringTokenizeAlternative(char *str, char *delimiters);

char *MemorySet(char *ptr, char value, unsigned int num);
void FreeMemory(char **ptr);
void *ReallocateMemory(void *ptr, unsigned int oldSize, unsigned int newSize);

int FreeBuffer(void **ptr);
int InteractiveMode(PassInfo *info);
int IsDelimiter(char c, char *delimiters);
int StringToInteger(char *str);

int ErrorStringToInteger(char *str);
void PrintErrorMessage(PassInfo *info, char *message);
int PrintDigit(int num, int fd);
char *ConvertNumber(long int num, int lowercase, int unsignedFlag);
void RemoveComments(char *str);

int ExitShell(PassInfo *info);
int ChangeDirectory(PassInfo *info);
int DisplayHelp(PassInfo *info);

int DisplayHistory(PassInfo *info);
int DisplayAlias(PassInfo *info);

ssize_t GetInput(PassInfo *info);
int GetLine(PassInfo *info, char **line, size_t *len);
void SigintHandler(int);

void ClearInfo(PassInfo *info);
void SetInfo(PassInfo *info, char **environ);
void FreeInfo(PassInfo *info, int freeEnv);

int IsChain(PassInfo *info, char *input, size_t *pos);
void CheckChain(PassInfo *info, char *input, size_t *pos, size_t length, size_t start);
int ReplaceAlias(PassInfo *info);
int ReplaceVariables(PassInfo *info);
int ReplaceString(char **input, char *search);

#endif

