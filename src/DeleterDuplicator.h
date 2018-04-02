#pragma once


template <class T> struct ResolveTypeDeleter {

	void operator()(T* p) {
		if(p) soap_del_wsdd__ResolveType(p);
		delete p;
	}
};

template <class T> struct ResolveTypeDuplicator {

	T* operator()(const T *p) {
		return soap_dup_wsdd__ResolveType(nullptr, nullptr, p);
	}
};

template <class T> struct HelloTypeDeleterReq {

	void operator()(T* p) {
		if(p) soap_del_wsdd__HelloType(p);
	}
};

template <class T> struct HelloTypeDuplicator {

	T* operator()(const T *p) {
		return soap_dup_wsdd__HelloType(nullptr, nullptr, p);
	}
};

template <class T> struct ProbeMatchTypeDeleter {

	void operator()(T* p) {
		if(p) soap_del_wsdd__ProbeMatchesType(p);
		delete p;
	}
};

template <class T> struct ProbeMatchTypeDuplicator {

	T* operator()(const T *p) {
		return soap_dup_wsdd__ProbeMatchesType(nullptr, nullptr, p);
	}
};

template <class T> struct ProbeTypeDeleterReq {

	void operator()(T* p) {
		//if(p) soap_del_wsdd__ProbeType(p);
	}
};

template <class T> struct ProbeTypeDuplicator {

	T* operator()(const T *p) {
		return soap_dup_wsdd__ProbeType(nullptr, nullptr, p);
	}
};

template <class T> struct ByeTypeDeleterReq {

	void operator()(T* p) {
		if(p) soap_del_wsdd__ByeType(p);
	}
};

template <class T> struct ByeTypeDuplicator {

	T* operator()(const T *p) {
		return soap_dup_wsdd__ByeType(nullptr, nullptr, p);
	}
};

template <class T> struct ProbeMatchesDeleter {

	void operator()(T* p) {
		if(p) soap_del___wsdd__ProbeMatches(p);
		delete p;
	}
};

template <class T> struct ProbeMatchesDuplicator {

	T* operator()(const T *p) {
		return soap_dup___wsdd__ProbeMatches(nullptr, nullptr, p);
	}
};
