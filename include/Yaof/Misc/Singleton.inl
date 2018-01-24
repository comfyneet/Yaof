template <typename T>
T& Singleton<T>::getInstance()
{
    static T instance;

    return instance;
}

template <typename T>
Singleton<T>::Singleton()
{
}
