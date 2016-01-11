#pragma once

#include <Otter.h>

class GuiFileSystem: public Otter::IFileSystem
{
public:
	//GuiFileSystem(void);
	//~GuiFileSystem(void);

	/* @brief Opens a file*/
	virtual void* Open(const char* szFilename, Otter::AccessFlag flags) = 0;

	/* @brief Closes the file*/
	virtual void Close(void* pHandle) = 0;

	/* @brief Reads data from the file.*/
	virtual uint32 Read(void* pHandle, uint8* data, uint32 count) = 0;

	/* @brief Writes data to the file.*/
	virtual uint32 Write(void* pHandle, uint8* data, uint32 count) = 0;

	/* @brief Seeks within the file.*/
	virtual void Seek(void* pHandle, uint32 offset, Otter::SeekFlag seekFlag) = 0;

	/* @brief Returns the size of the file*/
	virtual uint32 Size(void* pHandle) = 0;
};

