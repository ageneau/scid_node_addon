/*
# Copyright (C) 2016 Sylvain Ageneau

* This file is part of Scid (Shane's Chess Information Database).
*
* Scid is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation.
*
* Scid is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Scid. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCID_UI_TCLTK_H
#define SCID_UI_TCLTK_H

#include <memory>
#include <node.h>

namespace UI_impl {

using v8::Array;
using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Boolean;
using v8::Number;
using v8::Integer;
using v8::Object;
using v8::String;
using v8::Value;


typedef int   UI_res_t;
typedef void* UI_extra_t;

class List;

struct nodejs_result;
typedef nodejs_result *UI_handle_t;

inline int Main (int argc, char* argv[], void (*exit) (void*)) {
	return 0;
}
inline Progress CreateProgress(UI_handle_t) {
	return Progress();
}
inline Progress CreateProgressPosMask(UI_handle_t) {
	return Progress();
}
class List {
    std::vector<Local<Value>> list;
    bool append;
    UI_handle_t args;
    friend Local<Value> ObjMaker(UI_handle_t args, const List& v);

    void returnString();
    void returnArray();

public:
    explicit List(UI_handle_t args)
        : args(args),
          append(false)
    {}
	void clear() {
        list.clear();
    }

    bool empty() {
        return list.empty();
    }

    void returnResult();
	template <typename T> void push_back(const T&, bool append = false);
};

struct nodejs_result {
    nodejs_result(const FunctionCallbackInfo<Value>* callback_info)
        : callback_info(callback_info)
    {
        result = new List(this);
    }
    ~nodejs_result() {
        delete result;
    }
    
    const FunctionCallbackInfo<Value>* callback_info;
    List* result;
};

inline const Local<Value> ObjMaker(UI_handle_t args, bool v) {
	return Boolean::New(args->callback_info->GetIsolate(), v);
}

inline Local<Value> ObjMaker(UI_handle_t args, int v) {
	return Integer::New(args->callback_info->GetIsolate(), v);
}

inline Local<Value> ObjMaker(UI_handle_t args, uint v) {
	ASSERT(v < static_cast<uint>(std::numeric_limits<int>::max()));
	return Integer::New(args->callback_info->GetIsolate(), static_cast<int>(v));
}

inline Local<Value> ObjMaker(UI_handle_t args, uint64_t v) {
	ASSERT(v < static_cast<uint64_t>(std::numeric_limits<int>::max()));
	return Integer::New(args->callback_info->GetIsolate(), static_cast<int>(v));
}

inline Local<Value> ObjMaker(UI_handle_t args, double v) {
	return Number::New(args->callback_info->GetIsolate(), v);
}

inline Local<Value> ObjMaker(UI_handle_t args, const char* s) {
	return String::NewFromUtf8(args->callback_info->GetIsolate(), s);
}

inline Local<Value> ObjMaker(UI_handle_t args, const std::string& s) {
	return String::NewFromUtf8(args->callback_info->GetIsolate(), s.c_str());
}

inline Local<Value> ObjMaker(UI_handle_t args, const List& v) {
	Local<Array> ret = Array::New(args->callback_info->GetIsolate(), v.list.size());
    for(unsigned int i=0; i<v.list.size(); i++) {
        ret->Set(i, v.list[i]);
    }
    return ret;
}

template <typename T>
inline void List::push_back(const T& value, bool append) {
    if(append) {
        this->append = true;
    } else {
        ASSERT(!this->append);
    }
    list.push_back(ObjMaker(args, value));
}

inline void List::returnString() {
    if(list.size() > 0) {
        Local<String> ret = Local<String>::Cast(list[0]);
        for(int i=1; i<list.size(); i++) {
            Local<String> string = Local<String>::Cast(list[i]);
            ret = v8::String::Concat(args->callback_info->GetIsolate(), ret, string);
        }
        args->callback_info->GetReturnValue().Set(ret);
    }
}


inline void List::returnArray() {
    Isolate* isolate = args->callback_info->GetIsolate();
    Local<Array> array = Array::New(isolate, list.size());
    for(uint i=0; i<list.size(); i++) {
        array->Set(i, list[i]);
    }
    args->callback_info->GetReturnValue().Set(array);
}

inline void List::returnResult() {
    if(!this->empty()) {
        if(this->append)
            this->returnString();
        else
            this->returnArray();
    }
}

inline UI_res_t ResultHelper(UI_handle_t args, errorT res) {
	if (res == OK) return 0;

    Isolate* isolate = args->callback_info->GetIsolate();

    // Throw an Error that is passed back to JavaScript
    Local<Value> error = Exception::Error(String::NewFromUtf8(isolate, "Error in SCID"));
    Local<Object> obj = error->ToObject(isolate);
    
    obj->Set(String::NewFromUtf8(isolate, "code"), Integer::New(isolate, res));
    isolate->ThrowException(obj);

	return -1;
}

inline UI_res_t Result(UI_handle_t args, errorT res) {
	return UI_impl::ResultHelper(args, res);
}

template <typename T>
inline UI_res_t Result(UI_handle_t args, errorT res, const T& value) {
    args->callback_info->GetReturnValue().Set(UI_impl::ObjMaker(args, value));
	return UI_impl::ResultHelper(args, res);
}

}


#endif
