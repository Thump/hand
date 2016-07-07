
/*
 * (C) Copyright 1999 Denis McLaughlin
 *
 * Function protoypes for hand, generation of which should
 * probably be automated at some point.
 *
 */

int main(int, char **);
void PrintConfig(void);
void Initialize(int, char **);
void ReadConfig(void);
void ReadSwitch(int, char **);
void PrintHeader(void);
void OpenLog(void);
void log(char *);
void Exit(void);
void Usage(void);
int OpenListen();
int OpenConnect();
void DoServer(void);
