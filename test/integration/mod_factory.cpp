/**
 * @file mod_factory.cpp
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

#include <gtest/gtest.h>

#include "mod_factory.hpp"
#include "test_mod_impl.hpp"

using namespace mm;

////////////////////////////////////////////////////////////////////////////
///
//
class TestModFactory : public ::testing::Test {
protected:
    void SetUp() { }

    void TearDown() { }
};

////////////////////////////////////////////////////////////////////////////
///
//
TEST_F(TestModFactory, impl) {
    mm::ModMgr::instance().setLibNameTmpl("libxxx.dylib");
    mm::ModMgr::instance().add({0x1, "mm-test-mod"});

    mm::ModFactory factory{0x1};
    
    ASSERT_EQ(true, factory.isInitialised());

    auto modInterface = factory.instance();

    auto modImpl = static_cast<TestModImpl*>(modInterface->getImpl());

    ASSERT_EQ(true, modImpl->impl());
}