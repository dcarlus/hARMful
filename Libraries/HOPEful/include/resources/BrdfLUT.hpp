/**
 * This file was generated by bin2cpp v2.3.0
 * Copyright (C) 2013-2020 end2endzone.com. All rights reserved.
 * bin2cpp is open source software, see http://github.com/end2endzone/bin2cpp
 * Source code for file 'brdf.hdr', last modified 1591200330.
 * Do not modify this file.
 */
#ifndef BRDFLUT_HPP
#define BRDFLUT_HPP

#include <stddef.h>
#include <string>
#include <vector>

namespace Hope
{
  #ifndef BIN2CPP_EMBEDDEDFILE_CLASS
  #define BIN2CPP_EMBEDDEDFILE_CLASS
  class EmbeddedFileData
  {
  public:
    virtual size_t size() const = 0 ;
    virtual std::string filename() const = 0 ;
    virtual const std::vector<unsigned char>& buffer() const = 0 ;
  };
  #endif //BIN2CPP_EMBEDDEDFILE_CLASS
  const EmbeddedFileData& getBrdfLUTFile() ;
}; //Hope

#endif //BRDFLUT_HPP
