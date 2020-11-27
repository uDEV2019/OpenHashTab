﻿//    Copyright 2019-2020 namazso <admin@namazso.eu>
//    This file is part of OpenHashTab.
//
//    OpenHashTab is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    OpenHashTab is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with OpenHashTab.  If not, see <https://www.gnu.org/licenses/>.
#pragma once

#include <unordered_map>

#include "../Algorithms/Hasher.h"

struct ProcessedFileList
{
  // -2: not sumfile
  // -1: unknown sumfile
  // 0+: a sumfile belonging to the algorithm given
  // 
  // If the main file is a sumfile of a hash format we don't have enabled we want to enable it for this session.
  int sumfile_type;

  // A Win32 path to a directory that supposedly contains all files hashed. Ends with a slash.
  std::wstring base_path;

  struct FileData
  {
    // Path relative to base_path, absolute if base_path is not root for the file
    std::wstring relative_path;

    // Expected hashes indexed by algorithm idx
    std::array<std::vector<uint8_t>, HashAlgorithm::k_count> expected_hashes;

    // Unknown algorithm. This can only happen when opening a badly named sumfile
    std::vector<uint8_t> expected_unknown_hash;
  };

  // Files to hash, keyed by NT path
  std::unordered_map<std::wstring, FileData> files;
};

ProcessedFileList ProcessEverything(std::list<std::wstring> list);