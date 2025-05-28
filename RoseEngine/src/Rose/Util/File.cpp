#include "Rose/Util/File.hpp"

#ifdef ROSE_PLATFORM_MACOS
    #include <dlfcn.h>
    #include <libgen.h>
#endif

namespace Rose { namespace File {

std::filesystem::path createPath(const std::filesystem::path &relative) {
    std::filesystem::path rootPath;
#ifdef ROSE_PLATFORM_MACOS
    rootPath = getProjectSrcDirMacOS();    
#endif

    return rootPath/relative;
}
/*
std::filesystem::path getProjectSrcDirMacOS() {
    Dl_info info;
    dladdr((void*)&getProjectSrcDirMacOS, &info);  // Get path to the .dylib

    char pathCopy[1024];
    strncpy(pathCopy, info.dli_fname, sizeof(pathCopy));
    pathCopy[sizeof(pathCopy) - 1] = '\0';

    std::string folder = dirname(pathCopy);
    strncpy(pathCopy, folder.c_str(), sizeof(pathCopy));
    pathCopy[sizeof(pathCopy) - 1] = '\0';

    folder = dirname(pathCopy);

    std::filesystem::path projectRoot = folder;
    projectRoot /= "RoseEngine";
    projectRoot /= "src";
    
    return projectRoot;
}
*/
std::filesystem::path getProjectSrcDirMacOS() {
#ifdef ROSE_ASSETS_ROOT_PATH
    return std::filesystem::path(ROSE_ASSETS_ROOT_PATH);
#endif
    return "";
}


}}


