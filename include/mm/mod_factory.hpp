/**
 * @file mod_factory.hpp
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

#ifndef __MM_MOD_FACTORY_HPP
#define __MM_MOD_FACTORY_HPP

#include <dlfcn.h>

#include "mod_int.hpp"
#include "mod_mgr.hpp"

/**
 * Lib space
 */
namespace mm {
    /**
     * Module factory
     */
    class ModFactory;
};

class mm::ModFactory {
private:
    void*     m_Handler; ///< module handler
    mod_maker m_Maker; ///< module instance maker
    bool      m_IsInitialised; ///< module is initialised?
public:
    /**
     * Ctor
     * 
     * @param[in] modid module ID
     */
    ModFactory(
        std::size_t modid
    ) : 
        m_Handler{nullptr}, 
        m_Maker{nullptr},
        m_IsInitialised{false}
    {
        auto lib{ModMgr::instance().getLibName(modid)};
        if (!lib.empty()) {
            m_Handler = dlopen(lib.c_str(), RTLD_NOW);
            if (m_Handler) {
                m_Maker = reinterpret_cast<mod_maker>(dlsym(m_Handler, ModMgr::instance().getModFactoryName().c_str()));
                m_IsInitialised = true;
            }
        }
    }

    /**
     * Dtor
     */
    ~ModFactory() {
        if (m_Handler)
            dlclose(m_Handler);
    }

    /**
     * Module is initialised?
     */
    bool isInitialised() const noexcept { return m_IsInitialised; }

    /**
     * Make module instance
     * 
     * @return smart pointer to module instance
     */
    std::shared_ptr<BaseModInterface> instance() const { return std::shared_ptr<BaseModInterface>(m_Maker()); }
};

#endif // __MM_MOD_FACTORY_HPP