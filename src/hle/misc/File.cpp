#include "File.h"
#include "StringUtils.h"
using namespace std;

#define SHARE (FILE_SHARE_READ | FILE_SHARE_WRITE)
bool File::Open(const string& fileName, int accessType, int openType)
{
	m_hFile = CreateFileA(fileName.c_str(), accessType, SHARE, NULL, openType, 0, NULL);
	return (m_hFile != INVALID_HANDLE_VALUE);
}
long long File::GetSize()
{
	LARGE_INTEGER lpSize;
	GetFileSizeEx(m_hFile, &lpSize);
	return lpSize.QuadPart;
}
int File::Read(void* buffer, unsigned size)
{
	DWORD lpSize;
	ReadFile(m_hFile, buffer, size, &lpSize, NULL);
	return lpSize;
}
int File::Write(void* buffer, unsigned size)
{
	DWORD lpSize;
	WriteFile(m_hFile, buffer, size, &lpSize, NULL);
	return lpSize;
}
void File::SetPtr(long long value)
{
	LARGE_INTEGER qvalue;
	assert(sizeof(value) == 8);
	qvalue.QuadPart = value;
	SetFilePointerEx(m_hFile, qvalue, NULL, FILE_BEGIN);
}
void File::Close()
{
	if(m_hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}
}
bool File::IsDirectory(const string& fileName)
{
	u32 attr = GetFileAttributesA(fileName.c_str());
	return (attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY));
}
bool File::IsFile(const string& fileName)
{
	u32 attr = GetFileAttributesA(fileName.c_str());
	return (attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY));
}
bool File::Exists(const string& fileName)
{
	u32 attr = GetFileAttributesA(fileName.c_str());
	return (attr != INVALID_FILE_ATTRIBUTES);
}
string File::ReadStr(const string& fileName)
{
	File file;
	file.Open(fileName, ReadOnly, OpenExisting);
	int size = file.GetSize();

	char* buffer = new char[size];
	file.Read(buffer, size);
	return MakeZStr(buffer, size);
}
bool FileFinder::Open(const string& fileName)
{
	WIN32_FIND_DATAA info;
	HANDLE hFind = FindFirstFileA(fileName.c_str(), &info);
	BOOL has = (hFind != INVALID_HANDLE_VALUE);
	while (has)
	{
		m_files.push_back(info);
		has = FindNextFileA(hFind, &info);
	}
	if (hFind != INVALID_HANDLE_VALUE)
		FindClose(hFind);
	return true;
}
unsigned FileFinder::GetNumFiles()
{
	return m_files.size();
}
bool FileFinder::IsDirectory(int index)
{
	return (m_files[index].dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? true : false;
}
const char* FileFinder::GetFileName(int index)
{
	return m_files[index].cFileName;
}
bool FileSys::CreateDir(const string& dirName)
{
	return CreateDirectoryA(dirName.c_str(), NULL) != 0;
}
bool FileSys::Move(const string& oldName, const string& newName)
{
	return MoveFileA(oldName.c_str(), newName.c_str()) != 0;
}
bool FileSys::RemoveFile(const string& name)
{
	return DeleteFileA(name.c_str()) != 0;
}
bool FileSys::RemoveEmptyDir(const string& name)
{
	return RemoveDirectoryA(name.c_str()) != 0;
}