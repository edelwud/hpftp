#pragma once

#include <map>
#include <string>
#include <regex>
#include <optional>

#include "../Constants.h"
#include "../Network/StatusCodes.h"

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

static map<string, FTPCommandList> FTPCommandListMap = {
    { "ABOR", FTPCommandList::ABOR },{ "CWD", FTPCommandList::CWD },
    { "CDUP", FTPCommandList::CDUP },{ "DELE", FTPCommandList::DELE },
    { "EPSV", FTPCommandList::EPSV },{ "HELP", FTPCommandList::HELP },
    { "LIST", FTPCommandList::LIST },{ "MDTM", FTPCommandList::MDTM },
    { "MKD", FTPCommandList::MKD },{ "NLST", FTPCommandList::NLST },
    { "NOOP", FTPCommandList::NOOP },{ "PASS", FTPCommandList::PASS },
    { "PASV", FTPCommandList::PASV },{ "PORT", FTPCommandList::PORT },
    { "PWD", FTPCommandList::PWD },{ "QUIT", FTPCommandList::QUIT },
    { "REIN", FTPCommandList::REIN },{ "RETR", FTPCommandList::RETR },
    { "RMD", FTPCommandList::RMD },{ "RNFR", FTPCommandList::RNFR },
    { "SIZE", FTPCommandList::SIZE },{ "STOR", FTPCommandList::STOR },
    { "SYST", FTPCommandList::SYST },{ "TYPE", FTPCommandList::TYPE },
    { "USER", FTPCommandList::USER }
};

/**
 * @class 
 * FTP command
 * Packing and unpacking messages
 */
class FTPCommand {
public:
    static pair<FTPCommandList, string> Unpack(const string& data);
    static string Pack(StatusCodes code, const string& data);

    static vector<string> ArgumentParse(string arguments);
    static string GetCommand(FTPCommandList command);
};