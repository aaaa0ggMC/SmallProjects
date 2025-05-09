#ifndef AC_KERNEL
#define AC_KERNEL

typedef void (*DeFunc)(void *);

struct OnDestroyHandler{
public:
    bool destroy;
    OnDestroyHandler(){
        destroy = false;
    }
    DeFunc OnDestroy;
    virtual ~OnDestroyHandler(){}
};

#endif // AC_KERNEL
