#include <memory>
#include <base.h>

template <typename V>
class base_v : public base
{
private:
    V __val;

public:
    explicit base_v(V v = V{}) : __val(v)
    {
        if (base::__trace)
        {
            base::__OS << "created base_v " << __val << std::endl;
        }
    };
    ~base_v() override
    {
        if (base::__trace)
        {
            base::__OS << "deleted base_v " << __val << std::endl;
        }
    };

    V getVal() const { return __val; };

    bool operator==(const base_v &v) const
    {
        return __val == v.getVal();
    }
};

template <typename T>
struct ListNone
{
    T data;
    std::shared_ptr<ListNone<T>> next;
};

template <typename T>
class list final
{
private:
    std::shared_ptr<ListNone<T>> head;
    std::shared_ptr<ListNone<T>> tail;

public:
    list(/* args */);
    virtual ~list();

    bool add(const T &) noexcept;
    bool del(const T &) noexcept;
};

template <typename T>
list<T>::list(/* args */) : head(nullptr), tail(nullptr)
{
}

template <typename T>
list<T>::~list()
{
}

template <typename T>
bool list<T>::add(const T &t) noexcept
{
    std::shared_ptr<ListNone<T>> node_ptr(new (std::nothrow) ListNone<T>());

    if (node_ptr.get() == nullptr)
    {
        return false;
    }

    node_ptr->data = t;

    if (head != nullptr)
    {
        tail->next = node_ptr;
        tail = node_ptr;
    }
    else
    {
        head = tail = node_ptr;
    }

    return true;
}

template <typename T>
bool list<T>::del(const T &t) noexcept
{
    if (this->head.get())
    {
        auto ptr = head;
        std::shared_ptr<ListNone<T>> prv(nullptr);
        while (ptr.get() != nullptr)
        {
            if (ptr->data.operator==(t))
            {
                if (head == ptr)
                {
                    head = head->next;
                }
                if (tail == ptr)
                {
                    tail = prv;
                }

                if (prv.get() != nullptr)
                {
                    prv->next = ptr->next;
                }

                return true;
            }
            else
            {
                prv = ptr;
                ptr = ptr->next;
            }
        }
    }

    return false;
}

int main(int argc __attribute((unused)), char const *argv[] __attribute((unused)))
{
    list<base_v<int>> l;
    l.add(base_v<int>(1));
    l.add(base_v<int>(2));
    l.add(base_v<int>(3));
    l.add(base_v<int>(4));
    l.add(base_v<int>(5));

    {
        l.del(base_v<int>(1));
        l.del(base_v<int>(5));
        l.del(base_v<int>(3));
        l.del(base_v<int>(2));
        l.del(base_v<int>(4));
    }

    l.add(base_v<int>(5));
    std::cout << "-----------auto clean up-----------" << std::endl;
    std::cout.flush();
    return 0;
}
