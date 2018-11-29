/**
 * @author Kyle Akerstrom, Jonathan Flores, Mark Wagner
 * @date 2018-11-28
 * Copyright 2018 Team Fenrir
 */

#ifndef INCLUDE_EXCEPTIONS_H
#define INCLUDE_EXCEPTIONS_H

#include <stdexcept>

/**
* Exception when attempting to set Frame data longer than max allowed.
*/
class data_exceeds_max_length_error: public std::runtime_error {
 public:
  /**
  * @param errMessage An error message.
  */
  explicit data_exceeds_max_length_error(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

/**
* Exception when a frame fails to serialize.
*/
class serialization_error: public std::runtime_error {
 public:
  /**
  * @param errMessage An error message.
  */
  explicit serialization_error(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

/**
* Exception when a frame fails to deserialize.
*/
class deserialization_error: public std::runtime_error {
 public:
  /**
  * @param errMessage An error message.
  */
  explicit deserialization_error(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

#endif  // INCLUDE_EXCEPTIONS_H
