#ifndef COMMAND
#define COMMAND

#include <map>
#include <string>

#include "Executor.h"

using namespace std;

class BufferReader {
private:
    string buffer;
    int position = 0;
public:
    void LoadBuffer(string buffer);
    char ReadByte();
    int ReadInt();
    float ReadFloat();
    string ReadString(char delimiter);
};

enum class FTPCommandList {
    ABOR, /* Abort file loading */ 
    CDUP, /* Change dir to parent */ 
    CWD, /* Change dir */ 
    DELE, /* Delete file (DELE filename) */ 
    EPSV, /* Enter into passive mode */ 
    HELP, /* List of commnads */ 
    LIST, /* List of files (through DATA connection) */ 
    MDTM, /* Time of file modify */ 
    MKD, /* Abort file loading */ 
    NLST, /* Abort file loading */ 
    NOOP, /* Abort file loading */ 
    PASS, /* Abort file loading */ 
    PASV, /* Abort file loading */ 
    PORT, /* Abort file loading */ 
    PWD, /* Abort file loading */ 
    QUIT, /* Abort file loading */ 
    REIN, /* Abort file loading */ 
    RETR, /* Abort file loading */ 
    RMD, /* Abort file loading */ 
    RNFR, /* Abort file loading */ 
    SIZE, /* Abort file loading */ 
    STOR, /* Abort file loading */ 
    SYST, /* Abort file loading */ 
    TYPE, /* Abort file loading */ 
    USER, /* Abort file loading */ 
};

map<FTPCommandList, string> FTPCommandListMap = {
    { FTPCommandList::NOOP, "Okey, boy" }
};

class FTPCommandReader:
    protected BufferReader,
    protected Executor {
public:
    FTPCommandReader Unpack(string data);
    void Pack(string data);
};

#endif