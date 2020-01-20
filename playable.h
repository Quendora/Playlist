#ifndef PLAYABLE_H
#define PLAYABLE_H

#include <unordered_map>

using MetadataMap = std::unordered_map<std::string, std::string>;

class Playable
{
public:
    virtual void play() = 0;
};

class Media : public Playable
{
public:
  Media(const MetadataMap& metadata, const std::string& content);
  virtual void play() = 0;

protected:
  std::string content;
  MetadataMap metadata;
};

class Song : public Media
{
public:
    Song(const MetadataMap& metadata, const std::string& content);
    void play() override;
};

class Movie : public Media
{
public:
    Movie(const MetadataMap& metadata, const std::string& content);
    void play() override;
};

#endif