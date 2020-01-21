#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

class PlayerException : public std::exception
{
public:
    //FIXME Jak zamiast override wpisze virtual to Clang krzyczy
    virtual const char* what() const throw () = 0;
};

class InvalidMediaType : public PlayerException
{
public:
  const char* what() const throw();
};

class InvalidMetadata : public PlayerException
{
public:
  const char* what() const throw();
};

#endif