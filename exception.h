#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

class PlayerException : public std::exception
{
public:
    virtual const char* what() const throw () = 0;
};

class UnsupportedMediaType : public PlayerException
{
public:
  const char* what() const throw() override;
};

class InvalidMetadata : public PlayerException
{
public:
  const char* what() const throw() override;
};

class CorruptedFile : public PlayerException {
public:
  const char* what() const throw() override;
};

class CycleFound : public PlayerException {
public:
  const char* what() const throw() override;
};

class PlaylistOutOfRange : public PlayerException {
public:
  const char* what() const throw() override;
};

class CorruptedContent : public PlayerException {
public:
  const char* what() const throw() override;
};

class YearNotANumber : public PlayerException {
public:
    const char* what() const throw() override;
};

#endif