#include <mutex>

// 定义跨平台的退出函数
#define ATEXIT(param) atexit(param)

template <typename T>
class Singleton
{
public:
    static T& getInstance()
    {
        if (m_pInstance == NULL)
        {
            std::mutex lock;
            lock.lock();
            if (m_pInstance == NULL)
            {
                m_pInstance = new(std::nothrow) T();
                m_pInstance->init();
                ATEXIT(Destroy);
            }
            return *m_pInstance;
        }
        return *m_pInstance;
    }
    
    
    virtual void init(){}
protected:
    Singleton(void) {}
    virtual ~Singleton(void) {}
private:
    Singleton(const Singleton& rhs) {}
    Singleton& operator = (const Singleton& rhs) {}
    
    static void Destroy()
    {
        if (m_pInstance != NULL)
            delete m_pInstance;
        m_pInstance = NULL;
    }
    
    static T* m_pInstance;
};

template <typename T>
T* Singleton<T>::m_pInstance = NULL;
