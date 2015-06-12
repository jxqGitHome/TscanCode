/*
 * Cppcheck - A tool for static C/C++ code analysis
 * Copyright (C) 2007-2012 Daniel Marjamäki and Cppcheck team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * The above software in this distribution may have been modified by THL A29 Limited (“Tencent Modifications”).
 * All Tencent Modifications are Copyright (C) 2015 THL A29 Limited.
 */
//TO ignore the warning C4819

#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include <string>
#include <vector>
#include "config.h"

//add by TSC ignore some files such as .pb.cc
#define IGNOREFILE ".pb.cc"

/**
 * @brief Path handling routines.
 * Internally cppcheck wants to store paths with / separator which is also
 * native separator for Unix-derived systems. When giving path to user
 * or for other functions we convert path separators back to native type.
 */
class CPPCHECKLIB Path {
public:
    /**
     * Convert path to use native separators.
     * @param path Path string to convert.
     * @return converted path.
     */
    static std::string toNativeSeparators(std::string path);

    /**
      * Convert path to use internal path separators.
      * @param path Path string to convert.
      * @return converted path.
      */
    static std::string fromNativeSeparators(std::string path);

    /**
     * @brief Simplify path "foo/bar/.." => "foo"
     * @param originalPath path to be simplified, must have / -separators.
     * @return simplified path
     */
    static std::string simplifyPath(const char *originalPath);

    /**
     * @brief Compare filenames to see if they are the same.
     * On Linux the comparison is case-sensitive. On Windows it is case-insensitive.
     * @param fname1 one filename
     * @param fname2 other filename
     * @return true if the filenames match on the current platform
     */
    static bool sameFileName(const std::string &fname1, const std::string &fname2);

    /**
     * @brief Remove quotation marks (") from the path.
     * @param path path to be cleaned.
     * @return Cleaned path without quotation marks.
     */
    static std::string removeQuotationMarks(std::string path);

    /**
      * @brief Get an extension of the filename.
      * @param path Path containing filename.
      * @return Filename extension (containing the dot, e.g. ".h" or ".CPP").
      */
    static std::string getFilenameExtension(const std::string &path);

    /**
      * @brief Get an extension of the filename in lower case.
      * @param path Path containing filename.
      * @return Filename extension (containing the dot, e.g. ".h").
      */
    static std::string getFilenameExtensionInLowerCase(const std::string &path);

    /**
      * @brief Create a relative path from an absolute one, if absolute path is inside the basePaths.
      * @param absolutePath Path to be made relative.
      * @param basePaths Paths to which it may be made relative.
      * @return relative path, if possible. Otherwise absolutePath is returned unchanged
      */
    static std::string getRelativePath(const std::string& absolutePath, const std::vector<std::string>& basePaths);

    /**
     * @brief Check if the file extension indicates that it's a C/C++ source file.
     * Check if the file has source file extension: *.c;*.cpp;*.cxx;*.c++;*.cc;*.txx
     * @param filename filename to check
     * @return returns true if the file extension indicates it should be checked
     */
    static bool acceptFile(const std::string &filename);
	//add by TSC 20140909
	static bool acceptFile_h(const std::string &filename);
    /**
     * @brief Identify language based on file extension.
     * @param extensionInLowerCase e.g. ".c"
     * @return true if extension is meant for C files
     */
    static bool isC(const std::string &extensionInLowerCase);

	//add by TSC 20140909
	static bool isH(const std::string &extensionInLowerCase);

    /**
     * @brief Identify language based on file extension.
     * @param extensionInLowerCase e.g. ".cpp"
     * @return true if extension is meant for C++ files
     */
    static bool isCPP(const std::string &extensionInLowerCase);
};

//splitString函数的参数说明：  
//返回值是分割后字符串数组大小  
//strSrc 原始字符串  
//strDelims 自定义的分割字符串的分割数组  
//strDest 分割后的字符串数组，引用传递  
int splitString(const std::string & strSrc, const std::string& strDelims, std::vector<std::string>& strDest);

#endif // PATH_H_INCLUDED