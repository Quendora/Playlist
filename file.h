#pragma once

#include <string>
#include <unordered_map>
#include <regex>

#include "playable.h"

class File
{
public:
    File(const std::string& fileString);

    std::shared_ptr<Media> generateMedia();

private:
    enum MediaType {
        VIDEO,
        AUDIO
    };

    std::string getSupportedMediaType() const;
    bool validateFileString(const std::string& fileString);
    void extractData(std::string fileString);

    MediaType media_type;
    std::unordered_map<std::string, std::string> metadata;
    std::string content;
};