#include <logger/logger.h>

int main() {
    Logger logger;
    logger.setShowTimestamp(true);
    logger.Print("KEKW");

    return 0;
}