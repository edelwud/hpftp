#pragma once

enum class CommandList {
    ABOR, CDUP, CWD, DELE, EPSV,
    HELP, LIST, MDTM, MKD, NLST,
    NOOP, PASS, PASV, PORT, PWD,
    QUIT, REIN, RETR, RMD, RNFR,
    SIZE, STOR, SYST, TYPE, USER,
    AUTH, RNTO
};