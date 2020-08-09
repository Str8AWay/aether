//
// Created by Jason Laqua on 8/9/20.
//

#include "Logger.h"

Logger::Logger() {
    this->levelLogged = INFO;
    Serial.begin(115200);
}

Logger::Logger(typelog levelLogged) {
    this->levelLogged = levelLogged;
    Serial.begin(115200);
}

void Logger::debug(const String& message) {
    log(DEBUG, message);
}

void Logger::info(const String& message) {
    log(INFO, message);
}

void Logger::warn(const String& message) {
    log(WARN, message);
}

void Logger::error(const String& message) {
    log(ERROR, message);
}

void Logger::log(typelog messageLevel, const String& message) const {
    switch (levelLogged) {
        case DEBUG:
            switch (messageLevel) {
                case DEBUG:
                case INFO:
                case WARN:
                case ERROR:
                    Serial.print(message);
                    break;
            }
            break;
        case INFO:
            switch (messageLevel) {
                case DEBUG:
                    break;
                case INFO:
                case WARN:
                case ERROR:
                    Serial.print(message);
                    break;
            }
            break;
        case WARN:
            switch (messageLevel) {
                case DEBUG:
                case INFO:
                    break;
                case WARN:
                case ERROR:
                    Serial.print(message);
                    break;
            }
            break;
        case ERROR:
            switch (messageLevel) {
                case DEBUG:
                case INFO:
                case WARN:
                    break;
                case ERROR:
                    Serial.print(message);
                    break;
            }
            break;
    }
}