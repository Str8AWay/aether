//
// Created by Jason Laqua on 8/9/20.
//

#ifndef AETHER_LOGGER_H
#define AETHER_LOGGER_H

#include "Arduino.h"

enum typelog {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger {
public:
    typelog levelLogged;
    Logger();
    explicit Logger(typelog levelLogged);
    void debug(const String& message);
    void info(const String& message);
    void warn(const String& message);
    void error(const String& message);

private:
    void log(typelog messageLevel, const String& message) const;
};


#endif //AETHER_LOGGER_H
