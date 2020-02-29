#ifndef COMMAND
#define COMMAND

#include <map>

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
    LS = 201, PWD = 202, GET = 203
};

map<FTPCommandList, string> FTPCommandListMap = {
    { FTPCommandList::LS, "Okey, boy" }
};

class FTPCommandReader:
    protected BufferReader {
public:
    FTPCommandReader Unpack(string data);
    void Pack(string data);
};

#endif