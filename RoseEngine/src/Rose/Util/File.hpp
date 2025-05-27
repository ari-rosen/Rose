#pragma once

#include "Rose/Core/Core.hpp"

namespace Rose { namespace File {

std::filesystem::path createPath(const std::filesystem::path &relative);

std::filesystem::path getProjectSrcDirMacOS();

}}
