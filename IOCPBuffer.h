#pragma once

typedef struct IOCPBufferData
{
	ULONG m_nRefs;
	BYTE* m_pData;
	DWORD m_dwAllocLength;      //实际分配的内存大小，最小1024
	DWORD m_dwDataLength;       //postRecv的buffer长度，或者是实际接收到的数据长度

	IOCPBufferData( DWORD dwAllocLength );
	IOCPBufferData( );
	~IOCPBufferData( );

	VOID AddRef( );
	VOID Release( );
}IOCPBufferData, *PIOCPBufferData;

class CIOCPBuffer
{
public:
	IOCPBufferData* m_pData;
public:
	CIOCPBuffer(void);
	CIOCPBuffer(DWORD dwAllocLength);
	CIOCPBuffer(CIOCPBuffer& rhs);
	CIOCPBuffer(CIOCPBuffer* rhs);
	~CIOCPBuffer(void);
	
	CIOCPBuffer& operator = (const CIOCPBuffer& rhs);
	CIOCPBuffer& operator += (const CIOCPBuffer& rhs);
	CIOCPBuffer operator + (const CIOCPBuffer& rhs);

	void AddBytesAndReallocate(ULONG dwDataLength);
	void Reallocate(ULONG dwAllocLength);
	void Append(CONST BYTE* lpData,ULONG dwLength);


	BYTE* GetBytes();
	ULONG GetLength();
};

//管理内存池：IOCPMemPool <IOCPBufferData>
class IOCPBufferMngr
{
private:
	IOCPMutex m_MutexLock;                          //保护内存池：std::list<IOCPBufferData>
	IOCPMemPool <IOCPBufferData> m_BufferMemPool;
	static IOCPBufferMngr* m_Instance;
private:
	IOCPBufferMngr();
	virtual ~IOCPBufferMngr();
public:
	static IOCPBufferMngr* getInstance();
	static void ReleasePool( );
	static IOCPBufferData* Allocate(DWORD dwAllocLength);
	static VOID Free(IOCPBufferData* pData);
	static IOCPBufferData* Reallocate(IOCPBufferData* pData,DWORD dwAllocLength);
};



//
//template <class templateType>
//void __inline CIOCPBuffer::Write(const templateType &inTemplateVar)
//{
//	AddBytesAndReallocate(sizeof(templateType));
//
//	memcpy(&m_pData->m_pData[m_dwWriterPosition],&inTemplateVar,sizeof(templateType));
//
//	m_dwWriterPosition += sizeof(templateType);
//}
//template <class templateType>
//void __inline CIOCPBuffer::WritePtr(templateType *inTemplateVar)
//{
//	AddBytesAndReallocate(sizeof(templateType));
//
//	memcpy(&m_pData->m_pData[m_dwWriterPosition],inTemplateVar,sizeof(templateType));
//
//	m_dwWriterPosition += sizeof(templateType);
//}
//template <class templateType>
//void __inline CIOCPBuffer::Read(templateType &outTemplateVar) throw (...)
//{
//	if(m_dwReaderPosition + sizeof(templateType) > m_pData->m_dwDataLength)
//		throw std::exception("Read data length exceeds the buffer length.");
//
//	memcpy(&outTemplateVar,&m_pData->m_pData[m_dwReaderPosition],sizeof(templateType));
//
//	m_dwReaderPosition += sizeof(templateType);
//}
//
//template <class templateType>
//void __inline CIOCPBuffer::Peek(templateType &outTemplateVar) throw (...)
//{
//	if(m_dwReaderPosition + sizeof(templateType) > m_pData->m_dwDataLength)
//		throw std::exception("Read data length exceeds the buffer length.");
//
//	memcpy(&outTemplateVar,&m_pData->m_pData[m_dwReaderPosition],sizeof(templateType));
//}
