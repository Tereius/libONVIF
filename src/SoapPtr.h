#pragma once
#include <memory>

template <class T> class SoapPtr {

public:
	SoapPtr(T *pEntity, std::shared_ptr<SoapCtx> ctx);

public:
	virtual ~SoapPtr();

private:
	std::shared_ptr<T> entity;
	std::shared_ptr<SoapCtx> ctx;
};

template <class T>
SoapPtr<T>::SoapPtr(T *pEntity, std::shared_ptr<SoapCtx> ctx) :  {

}

template <class T>
SoapPtr<T>::SoapPtr(T *pEntity) :
entity(std::shared_ptr<T>(pEntity, [](T* p) { soap_delete(, pEntity) })) {

}
