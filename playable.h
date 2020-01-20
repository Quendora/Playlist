#pragma once

#include <unordered_map>

class Playable
{
public:
    virtual void play() = 0;
};

class Media : public Playable
{
public:
  Media(const std::unordered_map<std::string, std::string>& metadata, const std::string& content);
  virtual void play() = 0;

protected:
  std::string content;
  std::unordered_map<std::string, std::string> metadata;
};

class Song : public Media
{
public:
    Song(const std::unordered_map<std::string, std::string>& metadata, const std::string& content);
    void play() override;
};

class Movie : public Media
{
public:
    Movie(const std::unordered_map<std::string, std::string>& metadata, const std::string& content);
    void play() override;
};