//
// File_VMS.cpp
//
// $Id: //poco/Main/Foundation/src/File_VMS.cpp#15 $
//
// Library: Foundation
// Package: Filesystem
// Module:  File
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/File_VMS.h"
#include "Poco/Exception.h"
#include "Poco/Path.h"
#include "Poco/String.h"
#include <stdio.h>
#include <unistd.h>
#include <unixio.h>
#include <file.h>
#include <stat.h>
#include <errno.h>
#include <utime.h>
#include <lib$routines.h>
#include <rmsdef.h>
#include <starlet.h>
#include <lnmdef.h>
#include <ssdef.h>
#include <descrip.h>


namespace Poco {


FileImpl::FileImpl()
{
}


FileImpl::FileImpl(const std::string& path): _path(path)
{
	if (!_path.empty())
	{
		Path p(_path);
		p.makeFile();
		_path = p.toString();
	}
}


FileImpl::~FileImpl()
{
}


void FileImpl::swapImpl(FileImpl& file)
{
	std::swap(_path, file._path);
}


void FileImpl::setPathImpl(const std::string& path)
{
	_path = path;
}


bool FileImpl::existsImpl() const
{
	poco_assert (!_path.empty());

	return access(_path.c_str(), F_OK) == 0;
}


bool FileImpl::canReadImpl() const
{
	poco_assert (!_path.empty());

	struct stat st;
	if (stat(_path.c_str(), &st) == 0)
	{
		if (st.st_uid == geteuid())
			return (st.st_mode & S_IRUSR) != 0;
		else if (st.st_gid == getegid())
			return (st.st_mode & S_IRGRP) != 0;
		else
			return (st.st_mode & S_IROTH) != 0;
	}
	else handleLastErrorImpl(_path);
	return false;
}


bool FileImpl::canWriteImpl() const
{
	poco_assert (!_path.empty());

	struct stat st;
	if (stat(_path.c_str(), &st) == 0)
	{
		if (st.st_uid == geteuid())
			return (st.st_mode & S_IWUSR) != 0;
		else if (st.st_gid == getegid())
			return (st.st_mode & S_IWGRP) != 0;
		else
			return (st.st_mode & S_IWOTH) != 0;
	}
	else handleLastErrorImpl(_path);
	return false;
}


bool FileImpl::canExecuteImpl() const
{
	Path p(_path);
	return icompare(p.getExtension(), "exe") == 0;
}


bool FileImpl::isFileImpl() const
{
	poco_assert (!_path.empty());

	struct stat st;
	if (stat(_path.c_str(), &st) == 0)
		return S_ISREG(st.st_mode);
	else
		handleLastErrorImpl(_path);
	return false;
}


bool FileImpl::isDirectoryImpl() const
{
	poco_assert (!_path.empty());

	struct stat st;
	if (stat(_path.c_str(), &st) == 0)
		return S_ISDIR(st.st_mode);
	else
		handleLastErrorImpl(_path);
	return false;
}


bool FileImpl::isLinkImpl() const
{
	return false;
}


Timestamp FileImpl::createdImpl() const
{
	poco_assert (!_path.empty());

	struct stat st;
	if (stat(_path.c_str(), &st) == 0)
		return Timestamp(st.st_mtime);
	else
		handleLastErrorImpl(_path);
	return 0;
}


Timestamp FileImpl::getLastModifiedImpl() const
{
	poco_assert (!_path.empty());

	struct stat st;
	if (stat(_path.c_str(), &st) == 0)
		return Timestamp(st.st_mtime);
	else
		handleLastErrorImpl(_path);
	return 0;
}


void FileImpl::setLastModifiedImpl(const Timestamp& ts)
{
	poco_assert (!_path.empty());

	struct utimbuf tb;
	tb.actime  = ts.epochTime();
	tb.modtime = ts.epochTime();
	if (utime(_path.c_str(), &tb) != 0)
		handleLastErrorImpl(_path);
}


FileImpl::FileSizeImpl FileImpl::getSizeImpl() const
{
	poco_assert (!_path.empty());

	struct stat st;
	if (stat(_path.c_str(), &st) == 0)
		return st.st_size;
	else
		handleLastErrorImpl(_path);
	return 0;
}


void FileImpl::setSizeImpl(FileSizeImpl size)
{
	poco_assert (!_path.empty());

	if (truncate(_path.c_str(), size) != 0)
		handleLastErrorImpl(_path);
}


void FileImpl::setWriteableImpl(bool flag)		
{
	poco_assert (!_path.empty());

	struct stat st;
	if (stat(_path.c_str(), &st) != 0) 
		handleLastErrorImpl(_path);
	mode_t mode;
	if (flag)
	{
		mode = st.st_mode | S_IWUSR;
	}
	else
	{
		mode_t wmask = S_IWUSR | S_IWGRP | S_IWOTH;
		mode = st.st_mode & ~wmask;
	}
	if (chmod(_path.c_str(), mode) != 0) 
		handleLastErrorImpl(_path);
}


void FileImpl::setExecutableImpl(bool flag)
{
	// not supported
}


void FileImpl::copyToImpl(const std::string& path) const
{
	poco_assert (!_path.empty());

	// copying a file correctly under OpenVMS is non-trivial,
	// so we just invoke the COPY program.
	std::string cmd = "COPY ";
	cmd.append(_path);
	cmd.append(" ");
	cmd.append(path);
	if (system(cmd.c_str()) != 0)
		throw FileException("COPY command failed", _path);
}


void FileImpl::renameToImpl(const std::string& path)
{
	poco_assert (!_path.empty());

	POCO_DESCRIPTOR_STRING(oldNameDsc, _path);
	POCO_DESCRIPTOR_STRING(newNameDsc, path);

	int res;
	if ((res = lib$rename_file(&oldNameDsc, &newNameDsc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)) != 1)
	{
		switch (res & 0x0FFFFFFF)
		{
		case RMS$_FNF: 
			throw FileNotFoundException(_path);
		case RMS$_DEV:
		case RMS$_DNF:
			throw PathNotFoundException(_path);
		case RMS$_SYN:
			throw PathSyntaxException(path);
		case RMS$_RMV:
			throw FileAccessDeniedException(_path);
		case RMS$_PRV:
			throw FileAccessDeniedException("insufficient privileges", _path);		
		default:
			throw FileException(path);
		}
	}
}


void FileImpl::removeImpl()
{
	poco_assert (!_path.empty());

	int rc;
	if (isDirectoryImpl())
	{
		setWriteableImpl(true);
		rc = rmdir(_path.c_str());
	}
	else
	{
		rc = unlink(_path.c_str());
	}
	if (rc) handleLastErrorImpl(_path);
}



bool FileImpl::createFileImpl()
{
	poco_assert (!_path.empty());

	int n = open(_path.c_str(), O_WRONLY | O_CREAT | O_EXCL);
	if (n != -1)
	{
		close(n);
		return true;
	}
	if (n == -1 && errno == EEXIST)
		return false;
	else
		handleLastErrorImpl(_path);
	return false;
}


bool FileImpl::createDirectoryImpl()
{
	poco_assert (!_path.empty());

	if (existsImpl() && isDirectoryImpl())
		return false;
	Path p(_path);
	p.makeDirectory();
	if (mkdir(p.toString().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) 
		handleLastErrorImpl(_path);
	return true;
}


void FileImpl::handleLastErrorImpl(const std::string& path)
{
	switch (errno)
	{
	case EIO:
		throw IOException(path);
	case EPERM:
		throw FileAccessDeniedException("insufficient permissions", path);
	case EACCES:
		throw FileAccessDeniedException(path);
	case ENOENT:
		throw FileNotFoundException(path);
	case ENOTDIR:
		throw OpenFileException("not a directory", path);
	case EISDIR:
		throw OpenFileException("not a file", path);
	case EROFS:
		throw FileReadOnlyException(path);
	case EEXIST:
		throw FileExistsException(path);
	case ENOSPC:
		throw FileException("no space left on device", path);
	case EDQUOT:
		throw FileException("disk quota exceeded", path);
	case ENOTEMPTY:
		throw FileException("directory not empty", path);
	case ENAMETOOLONG:
		throw PathSyntaxException(path);
	default:
		throw FileException(strerror(errno), path);
	}
}


} // namespace Poco
