/**
 * @file main.hpp
 * @authors Max Markeloff (https://github.com/mmarkeloff)
 */

// MIT License
//
// Copyright (c) 2021 Max
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "mod_factory.hpp"
#include "some_mod_impl.hpp"
#include "another_mod_impl.hpp"

#define SOME_MODID    0x1
#define ANOTHER_MODID 0x2

int main(int argc, char* argv[]) {
    mm::ModMgr::instance().setLibNameTmpl("libxxx.dylib");
    mm::ModMgr::instance().add({SOME_MODID, "mm-sample-some-mod"});
    mm::ModMgr::instance().add({ANOTHER_MODID, "mm-sample-another-mod"});

    mm::ModFactory someFactory{SOME_MODID};
    if (someFactory.isInitialised()) {
        auto modInterface = someFactory.instance();

        auto modImpl = static_cast<SomeModImpl*>(modInterface->getImpl());
        modImpl->impl();
    }

    mm::ModFactory anotherFactory{ANOTHER_MODID};
    if (anotherFactory.isInitialised()) {
        auto modInterface = anotherFactory.instance();

        auto modImpl = static_cast<AnotherModImpl*>(modInterface->getImpl());
        modImpl->impl();
    }

    return 0;
}