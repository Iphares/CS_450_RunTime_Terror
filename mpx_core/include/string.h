/// @file

#ifndef _STRING_H
#define _STRING_H

#include <system.h>


  //Procedure: isspace
  ///Description: Determine if a character is whitespace.
  ///
  /// @param c character to check
int isspace(const char *c);

  //Procedure: memset
  ///Description: Set a region of memory.
  ///
  /// @param s destination
  /// @param c byte to write
  /// @param n count
void* memset(void *s, int c, size_t n);

  //Procedure: strcpy
  ///Description: Copy one string to another.
  ///
  /// @param s1 destination
  /// @param s2 source
char* strcpy(char *s1, const char *s2);

  //Procedure: strcat
  ///Description: Concatenate the contents of one string onto another.
  ///
  /// @param s1 destination
  /// @param s2 source
char* strcat(char *s1, const char *s2);

  //Procedure: strlen
  ///Description: Returns the length of a string.
  ///
  /// @param s input string
int   strlen(const char *s);

  //Procedure: strcmp
  ///Description: String comparison
  ///
  /// @param s1 string 1
  /// @param s2 string 2
int   strcmp(const char *s1, const char *s2);

  //Procedure: strtok
  ///Description: Split string into tokens
  ///
  /// @param s1 String
  /// @param s2 delimiter
char* strtok(char *s1, const char *s2);

  //Procedure: atoi
  ///Description: Convert an ASCII string to an integer
  ///
  /// @param s String
int atoi(const char *s);

#endif
