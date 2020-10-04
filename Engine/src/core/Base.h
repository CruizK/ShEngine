#pragma once
#include <memory>
/* Where all global engine definitions and structs/classes will go */

template<typename T>
using Scope = std::shared_ptr<T>;
template<typename T>
constexpr Scope<T> CreateScope()
{
	return std::make_unique<T>();
}

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T>
constexpr Ref<T> CreateRef()
{
	return std::make_shared<T>();
}