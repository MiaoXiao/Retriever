#pragma once

#include <Otter.h>

class GuiFileSystem: public Otter::IFileSystem
{
public:
	GuiFileSystem();
	//~GuiFileSystem(void);

	/* @brief Opens a file*/
	void* Open(const char* szFilename, Otter::AccessFlag flags);

	/* @brief Closes the file*/
	void Close(void* pHandle);

	/* @brief Reads data from the file.*/
	uint32 Read(void* pHandle, uint8* data, uint32 count);

	/* @brief Writes data to the file.*/
	uint32 Write(void* pHandle, uint8* data, uint32 count);

	/* @brief Seeks within the file.*/
	void Seek(void* pHandle, uint32 offset, Otter::SeekFlag seekFlag);

	/* @brief Returns the size of the file*/
	uint32 Size(void* pHandle);
};

