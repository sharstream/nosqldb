/*____________________________________________
| Copyright (c) David Perez 2014-2015         |
| Prototype Pattern Interface                 |
| Global Exception Interface                  |
| Apex Data Solutions, LLC                    | 
|____________________________________________*/

#include "TGlobalContainer.hpp"

//____________________________________________________________________________//

class Global_Error : public std::exception {
public:
    Global_Error(const std::string & err) : err_(err) {
    }

    virtual ~Global_Error() throw() {
    }

    operator const std::string() const {
	return err_;
    }

    virtual const char* what() const throw() {
	return err_.c_str();
    }

private:
    std::string err_;
};

//____________________________________________________________________________//
//class CreationPolicy Prototype pattern
//____________________________________________________________________________//

template <typename TGlobalBase>
class CreationPolicy{
public:
	CreationPolicy(TGlobalBase* pObj = 0) : pPrototype_(pObj) {
	}

	TGlobalBase* Create() {
	    return pPrototype_ ? pPrototype_->Clone() : 0;
	}

	TGlobalBase* GetPrototype() {
	    return pPrototype_;
	}

	void SetPrototype(TGlobalBase* pObj) {
	    pPrototype_ = pObj;
	}

protected:
    TGlobalBase* pPrototype_;

    ~CreationPolicy() {
    }
};

//____________________________________________________________________________//

template<class T,
   template <class> class CheckingPolicy,
   template <class> class ThreadingModel,
   template <class> class Storage = DefaultSmartPtrStorage >
class SmartPtr : public CheckingPolicy<T>, public ThreadingModel<SmartPtr> {
    // ...
    T* operator->() {
	   typename ThreadingModel<SmartPtr>::Lock guard(*this);
	   CheckingPolicy<T>::Check(pointee_);
	   return pointee_;
    }

private:
    T* pointee_;
};

//____________________________________________________________________________//

template<class T>
class DefaultSmartPtrStorage {
public:
    typedef T* PointerType;
    typedef T& ReferenceType;

protected:
    PointerType GetPointer() {
	return ptr_;
    }

    void SetPointer(PointerType ptr) {
	ptr_ = ptr;
    }

private:
    PointerType ptr_;
};


