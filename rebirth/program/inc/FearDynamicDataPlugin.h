#pragma once

#include "simConsolePlugin.h"
#include "simDictionary.h"
#include "streamio.h"
#include "persist.h"

class FearDynamicDataPlugin : public SimConsolePlugin, public CMDDataManager
{
	typedef SimConsolePlugin Parent;

	typedef Persistent::AbstractTaggedClass::Field Field;

	struct DataBlockClass
	{
		DataBlockClass* nextClass;

		size_t fieldTableSize;
		Field* fieldTable;
		const char* className;
		int dbmClass;
	};

	DataBlockClass* classes;
	DataBlockClass* curClass;

	Vector<Field> tempFields;
	Vector<char*> objectExportText;

public:
	FearDynamicDataPlugin();
	virtual ~FearDynamicDataPlugin();
	
	virtual void registerClassBegin(const char* className, const char* superClassName, int dbmType);
	// TODO default 1?
	virtual void registerData(const char* fieldName, int type, int offset, int elementCount = 1);
	virtual void registerClassEnd();
	virtual void exportObject(SimObject* obj, StreamIO& sio, bool onlySelected, int tabin = 0);
	
	void init() override;
	void declareDataBlock(StringTableEntry className, StringTableEntry objectName) override;
	const char* getDataField(StringTableEntry objectName, StringTableEntry slotName, const char* array) override;
	void setDataField(StringTableEntry objectName, StringTableEntry slotName, const char* array, int argc, const char** argv) override;
	void beginObject(StringTableEntry className, const char* objectName) override;
	void endObject() override;	
	const char * consoleCallback(CMDConsole *, int id, int argc, const char * argv[]) override;
};
