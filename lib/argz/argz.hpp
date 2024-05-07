// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//      http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <cstdint>
#include <functional>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace argz
{
   template <class T>
   using ref = std::reference_wrapper<T>;

   template <class T>
   using ref_opt = ref<std::optional<T>>;

   using var = std::variant<
      ref<bool>,
      ref<int32_t>,
      ref<uint32_t>,
      ref<int64_t>,
      ref<uint64_t>,
      ref<std::string>,
      ref_opt<int32_t>,
      ref_opt<uint32_t>,
      ref_opt<int64_t>,
      ref_opt<uint64_t>,
      ref_opt<std::string>>;
   
   struct ids_t final {
      std::string_view id{};
      char alias = '\0';
   };

   struct arg_t final {
      ids_t ids{};
      var value;
      std::string_view help{};
   };

   using options = std::vector<arg_t>;

   struct about final {
      std::string_view description{}, version{}, author{}, usage{};
      bool print_help_when_no_options = true;
      bool help{};
   };

   namespace detail
   {
      struct parse_visitor {
         const char* const c;

         void operator()(ref<std::string>& x) const { x.get() = c; }
         void operator()(ref<bool>& x) const { x.get() = std::strcmp(c, "true") == 0; }
         void operator()(ref<int32_t>& x) const { x.get() = std::stol(c); }
         void operator()(ref<uint32_t>& x) const { x.get() = std::stoul(c); }
         void operator()(ref<int64_t>& x) const { x.get() = std::stoll(c); }
         void operator()(ref<uint64_t>& x) const { x.get() = std::stoull(c); }
         void operator()(ref_opt<int32_t>& x) const { if (c) x.get().emplace(std::stol(c)); }
         void operator()(ref_opt<uint32_t>& x) const { if (c) x.get().emplace(std::stoul(c)); }
         void operator()(ref_opt<int64_t>& x) const { if (c) x.get().emplace(std::stoll(c)); }
         void operator()(ref_opt<uint64_t>& x) const { if (c) x.get().emplace(std::stoull(c)); }
         void operator()(ref_opt<std::string>& x) const { if (c) x.get().emplace(c); }
      };

      inline void parse(const char* const c, var& v)
      {
         std::visit(parse_visitor{c}, v);
      }

      struct to_string_visitor {
         std::string operator()(const ref<std::string>& x) const { return x.get(); }
         std::string operator()(const ref<bool>& x) const { return x.get() ? "true" : "false"; }
         std::string operator()(const ref<int32_t>& x) const { return std::to_string(x.get()); }
         std::string operator()(const ref<uint32_t>& x) const { return std::to_string(x.get()); }
         std::string operator()(const ref<int64_t>& x) const { return std::to_string(x.get()); }
         std::string operator()(const ref<uint64_t>& x) const { return std::to_string(x.get()); }
         std::string operator()(const ref_opt<int32_t>& x) const { return x.get().has_value() ? std::to_string(x.get().value()) : ""; }
         std::string operator()(const ref_opt<uint32_t>& x) const { return x.get().has_value() ? std::to_string(x.get().value()) : ""; }
         std::string operator()(const ref_opt<int64_t>& x) const { return x.get().has_value() ? std::to_string(x.get().value()) : ""; }
         std::string operator()(const ref_opt<uint64_t>& x) const { return x.get().has_value() ? std::to_string(x.get().value()) : ""; }
         std::string operator()(const ref_opt<std::string>& x) const { return x.get().has_value() ? x.get().value() : ""; }
      };

      inline std::string to_string(const var& v) {
         return std::visit(to_string_visitor{}, v);
      }
   }
   
   inline void help(const about& about, const options& opts)
   {
      std::cout << about.description << '\n';
      std::cout << "Version: " << about.version << '\n';
      std::cout << "Author: " << about.author << '\n';
      std::cout << "\nUsage: " << about.usage << '\n';

      std::cout<< "\nOptions:";      
      std::cout << '\n' << R"(-h, --help       write help to console)" << '\n';
      std::cout << R"(-v, --version    write the version to console)" << '\n';

      for (auto& [ids, v, h] : opts)
      {
         if (ids.alias != '\0') {
            std::cout << '-' << ids.alias << ", --" << ids.id;
         }
         else {
            std::cout << (ids.id.size() == 1 ? "-" : "--") << ids.id;
         }

         std::cout << "    " << h;
         detail::to_string(v).empty() ? std::cout << '\n' : std::cout << ", default: " << detail::to_string(v) << '\n';
      }
      std::cout << '\n';
   }

   template <class int_t, class char_ptr_t, typename = std::enable_if_t<std::is_pointer_v<char_ptr_t>>>
   inline void parse(about& about, options& opts, const int_t argc, char_ptr_t argv, int fileArgIndex)
   {
      if (argc == 1) {
         if (about.print_help_when_no_options) {
            help(about, opts);
         }
         return;
      }
      
      auto get_id = [&](char alias) -> std::string_view {
         for (auto& x : opts) {
            if (x.ids.alias == alias) {
               return x.ids.id;
            }
         }
         return {};
      };

      for (int_t i = 1; i < argc; ++i) {
         if (i == fileArgIndex) continue;

         const char* flag = argv[i];
         if (*flag != '-') {
            throw std::runtime_error("Error: expected '-'");
         }
         ++flag;
         
         if (*flag == '-') {
            ++flag;
         }
         std::string_view str{ flag };
         if (str == "h" || str == "help") {
            help(about, opts);
            continue;
         }
         if (str == "v" || str == "version") {
            std::cout << "Version: " << about.version << '\n';
            continue;
         }
         if (str.size() == 1) {
            str = get_id(*flag);
            if (str.empty()) {
               throw std::runtime_error("Error: invalid argument '-" + std::string(1, *flag) + "'");
            }
         }
         if (str.empty()) { break; }
         
         for (auto& [ids, v, h] : opts) {
            if (ids.id == str) {
               if (std::holds_alternative<ref<bool>>(v)) {
                  std::get<ref<bool>>(v).get() = true;
               }
               else {
                  detail::parse(argv[++i], v);
               }
            }
         }
      }
   }
}
