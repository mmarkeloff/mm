/**
 * @file mod_mgr.hpp
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

#ifndef __MM_MOD_MGR_HPP
#define __MM_MOD_MGR_HPP

#include <string>
#include <map>
#include <utility>
#include <cstdint>
#include <regex>

// https://github.com/mmarkeloff/cpp-crtp-singleton
#include "crtp_st.hpp"

/**
 * Lib space
 */
namespace mm {
    /**
     * Module manager
     * 
     * @warning singleton
     */
    class ModMgr;
};

class mm::ModMgr: public crtp_st::Base<ModMgr> {
private:
    using modid_pair_t    = std::pair<std::size_t, std::string>; ///< just shortcut
    using modid_mapping_t = std::map<std::size_t, std::string>; ///< just shortcut

    static constexpr const char* const DEFAULT_LIBNAME_TMPL{"libxxx.so"}; ///< default
    static constexpr const char* const DEFAULT_MOD_FACTORY_NAME{"instance"}; ///< default
    static constexpr const char* const UNKNOWN_LIBNAME{""}; ///< unknown
private:
    std::string     m_LibNameTmpl; ///< lib name template
    std::string     m_ModFactoryName; ///< module factory function name
    modid_mapping_t m_ModID2ModName; ///< modid -> modname
public:
    /**
     * Ctor
     * 
     * @warning lib name template is DEFAULT_LIBNAME_TMPL by default
     * @warning module factory function name is DEFAULT_MOD_FACTORY_NAME by default
     */
    ModMgr(
    ) : 
        m_LibNameTmpl{DEFAULT_LIBNAME_TMPL},
        m_ModFactoryName{DEFAULT_MOD_FACTORY_NAME} {
    }

    /**
     * Setter
     * 
     * @param[in] lib_name_tmpl lib name template
     * 
     * @warning lib_name_tmpl must be rvalue
     */
    void setLibNameTmpl(std::string&& lib_name_tmpl) noexcept { m_LibNameTmpl = std::move(lib_name_tmpl); }

    /**
     * Setter
     * 
     * @param[in] mod_factory_name module factory function name
     * 
     * @warning mod_factory_name must be rvalue
     */
    void setModFactoryName(std::string&& mod_factory_name) noexcept { m_ModFactoryName = std::move(mod_factory_name); }

    /**
     * Getter
     * 
     * @return lib name template
     */
    std::string getLibNameTmpl() const noexcept { return m_LibNameTmpl; }
    
    /**
     * Getter
     * 
     * @return module factory function name
     */
    std::string getModFactoryName() const noexcept { return m_ModFactoryName; }

    /**
     * Add a new module
     * 
     * @param[in] mod modid, modname
     * 
     * @warning mod must be rvalue
     */
    void add(modid_pair_t&& mod) noexcept { m_ModID2ModName.emplace(std::move(mod)); }

    /**
     * Get lib name
     * 
     * @return UNKNOWN_LIBNAME, if modid is not found
     */
    std::string getLibName(
        std::size_t modid
    ) const noexcept 
    { 
        auto it = m_ModID2ModName.find(modid);
	    if (m_ModID2ModName.end() == it)
	        return UNKNOWN_LIBNAME;
	    
        return std::regex_replace(m_LibNameTmpl, std::regex("xxx"), it->second);
    }
};

#endif // __MM_MOD_MGR_HPP