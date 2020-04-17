//////////////////////////////////////////////////////////////////////
//
//  FILE:       jsscid.cpp
//              Scid extensions to the nodejs interpreter
//
//  Part of:    Scid (Shane's Chess Information Database)
//
//  Notice:     Copyright (c) 2016 Sylvain Ageneau. All rights reserved.
//
//  Scid is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation.
//
//  Scid is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with Scid.  If not, see <http://www.gnu.org/licenses/>.
//
//////////////////////////////////////////////////////////////////////

#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <set>
#include <algorithm>
#include <functional>
#include <iostream>
#include <node.h>

#include "game.h"
#include "scidbase.h"
#include "dbasepool.h"
#include "ui.h"

extern int scid_main(int argc, char * argv[]);

namespace scid {
using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Boolean;
using v8::Value;

// Extracts a C string from a V8 Utf8Value.
const char* ToCString(const v8::String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

std::vector<const char*> scidArgsFromV8(const FunctionCallbackInfo<Value>& args) {
    std::vector<const char*> argv;
    argv.push_back(strdup(""));

    for(int i=0; i<args.Length(); i++) {
        v8::String::Utf8Value str(args.GetIsolate(), args[i]);
        argv.push_back(strdup(ToCString(str)));
    }

    return argv;
}

void freeScidArgs(std::vector<const char*> argv) {
    for(const char* arg : argv) {
        free((void*)arg);
    }
}

typedef int (*scid_function) (UI_extra_t extra, UI_handle_t ti, int argc, const char ** argv);

void wrap_scid_function(const FunctionCallbackInfo<Value>& args, scid_function func) {
    std::vector<const char*> argv = scidArgsFromV8(args);
    struct UI_impl::nodejs_result res(&args);
    (*func)(0, &res, argv.size(), argv.data());
    freeScidArgs(argv);
    res.result->returnResult();
}

void js_base(const FunctionCallbackInfo<Value>& args) {
    wrap_scid_function(args, &sc_base);
}

void js_book(const FunctionCallbackInfo<Value>& args) {
    wrap_scid_function(args, &sc_book);
}

void js_clipbase(const FunctionCallbackInfo<Value>& args) {
    wrap_scid_function(args, &sc_clipbase);
}

void js_eco(const FunctionCallbackInfo<Value>& args) {
    wrap_scid_function(args, &sc_eco);
}

void js_filter(const FunctionCallbackInfo<Value>& args) {
    wrap_scid_function(args, &sc_filter);
}

void js_game(const FunctionCallbackInfo<Value>& args) {
    wrap_scid_function(args, &sc_game);
}

void js_info(const FunctionCallbackInfo<Value>& args) {
    wrap_scid_function(args, &sc_info);
}

void js_move(const FunctionCallbackInfo<Value>& args) {
    wrap_scid_function(args, &sc_move);
}

void js_name(const FunctionCallbackInfo<Value>& args) {
    wrap_scid_function(args, &sc_name);
}

void js_report(const FunctionCallbackInfo<Value>& args) {
    wrap_scid_function(args, &sc_report);
}

void js_pos(const FunctionCallbackInfo<Value>& args) {
    wrap_scid_function(args, &sc_pos);
}

void js_search(const FunctionCallbackInfo<Value>& args) {
    wrap_scid_function(args, &sc_search);
}

void js_tree(const FunctionCallbackInfo<Value>& args) {
    wrap_scid_function(args, &sc_tree);
}

void js_var(const FunctionCallbackInfo<Value>& args) {
    wrap_scid_function(args, &sc_var);
}

void init(Local<Object> exports) {
    char *scid = "scid";
    scid_main(1, &scid);
    NODE_SET_METHOD(exports, "base", js_base);
    NODE_SET_METHOD(exports, "book", js_book);
    NODE_SET_METHOD(exports, "clipbase", js_clipbase);
    NODE_SET_METHOD(exports, "eco", js_eco);
    NODE_SET_METHOD(exports, "filter", js_filter);
    NODE_SET_METHOD(exports, "game", js_game);
    NODE_SET_METHOD(exports, "info", js_info);
    NODE_SET_METHOD(exports, "move", js_move);
    NODE_SET_METHOD(exports, "name", js_name);
    NODE_SET_METHOD(exports, "report", js_report);
    NODE_SET_METHOD(exports, "pos", js_pos);
    NODE_SET_METHOD(exports, "search", js_search);
    NODE_SET_METHOD(exports, "tree", js_tree);
    NODE_SET_METHOD(exports, "var", js_var);
}

NODE_MODULE(addon, init)

} //  namespace scid
