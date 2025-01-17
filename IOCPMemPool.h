#ifndef _IOCPMEMPOOL_H_
#define _IOCPMEMPOOL_H_

/*
	A Simple IOCP Class
	Author:201724
	Email:number201724@me.com
*/

#include <list>

template <class T>
class IOCPMemPool
{
private:
	std::list <T*> m_vObjectPool;	//使用std::list,增加内存使用率
	ULONG m_dwAllocateCount;
public:
	IOCPMemPool()
	{
		m_dwAllocateCount = 50;
		GetNewBufferArray();
	}
	virtual ~IOCPMemPool()
	{
		DeleteAll();
	}
	VOID DeleteAll()
	{
		std::list <T*>::iterator iter;
		iter = m_vObjectPool.begin();
		while(iter != m_vObjectPool.end())
		{
			delete *iter;
			iter = m_vObjectPool.erase(iter);
		}
	}
	VOID SetAllocateCount(ULONG dwCount)
	{
		m_dwAllocateCount = dwCount;

		GetNewBufferArray();
	}
	VOID GetNewBufferArray()
	{
		if(m_vObjectPool.size() < m_dwAllocateCount)
		{
			for(ULONG i=0;i<m_dwAllocateCount;i++)
			{
				T* object = new T();
				m_vObjectPool.push_back(object);
			}
		}
	}

    //取内存池第一个buffer
	T* Alloc()
	{
		T* object = NULL;

		if(m_vObjectPool.empty())
		{
			GetNewBufferArray();
		}

		object = m_vObjectPool.front();
		m_vObjectPool.pop_front();
		return object;
	}

    //将buffer放回内存池，循环使用
	VOID Free(T* object)
	{
		m_vObjectPool.push_back(object);
	}

};

#endif