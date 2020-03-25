#ifndef COMMAND_H
#define COMMAND_H

#include <map>
#include <string>

using namespace std;

enum class FTPCommandList {
    ABOR, /* Abort file loading */                      CDUP, /* Change dir to parent */ 
    CWD, /* Change dir */                               DELE, /* Delete file (DELE filename) */ 
    EPSV, /* Enter into passive mode */                 HELP, /* List of commnads */ 
    LIST, /* List of files (through DATA connection) */ MDTM, /* Time of file modify */ 
    MKD, /* Abort file loading */                       NLST, /* Abort file loading */ 
    NOOP, /* Abort file loading */                      PASS, /* Abort file loading */ 
    PASV, /* Abort file loading */                      PORT, /* Abort file loading */ 
    PWD, /* Abort file loading */                       QUIT, /* Abort file loading */ 
    REIN, /* Abort file loading */                      RETR, /* Abort file loading */ 
    RMD, /* Abort file loading */                       RNFR, /* Abort file loading */ 
    SIZE, /* Abort file loading */                      STOR, /* Abort file loading */ 
    SYST, /* Abort file loading */                      TYPE, /* Abort file loading */ 
    USER, /* Abort file loading */ 
};

static map<FTPCommandList, string> FTPCommandListMap = {
    { FTPCommandList::ABOR, "ABOR" },{ FTPCommandList::CWD, "CDUP" },
    { FTPCommandList::CDUP, "CWD" },{ FTPCommandList::DELE, "DELE" },
    { FTPCommandList::EPSV, "EPSV" },{ FTPCommandList::HELP, "HELP" },
    { FTPCommandList::LIST, "LIST" },{ FTPCommandList::MDTM, "MDTM" },
    { FTPCommandList::MKD, "MKD" },{ FTPCommandList::NLST, "NLST" },
    { FTPCommandList::NOOP, "NOOP" },{ FTPCommandList::PASS, "PASS" },
    { FTPCommandList::PASV, "PASV" },{ FTPCommandList::PORT, "PORT" },
    { FTPCommandList::PWD, "PWD" },{ FTPCommandList::QUIT, "QUIT" },
    { FTPCommandList::REIN, "REIN" },{ FTPCommandList::RETR, "RETR" },
    { FTPCommandList::RMD, "RMD" },{ FTPCommandList::RNFR, "RNFR" },
    { FTPCommandList::SIZE, "SIZE" },{ FTPCommandList::STOR, "STOR" },
    { FTPCommandList::SYST, "SYST" },{ FTPCommandList::TYPE, "TYPE" },
    { FTPCommandList::USER, "USER" }
};

class FTPCommandReader {
public:
    FTPCommandReader Unpack(string data);
    void Pack(string data);
};

#endif