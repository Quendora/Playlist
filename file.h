#ifndef FILE_H
#define FILE_H

#include <string>
#include <unordered_map>
#include <regex>

#include "playable.h"

class File
{
public:
    File(const std::string& fileString);

    std::string getType() const;
    MetadataMap getMetadata() const;
    std::string getContent() const;

private:
    enum MediaType {
        VIDEO,
        AUDIO
    };

    void extractData(const std::string& fileString);
    void extractFileType(const std::string& typeString);
    void extractMetadata(const std::string& metadataString);
    void extractContent(const std::string& contentString);

    std::string fileType;
    MetadataMap metadata;
    std::string content;
};

#endif