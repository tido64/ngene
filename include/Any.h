/// Deprecated. For now, it's just too convenient with Boost as it takes care
/// of optimisations across platforms as well as compilers.
///
/// Dynamic container for ngene, modified for more performance. All type info
/// is lost when traveling between shared libraries, so it is not type safe! 
///
/// (C) Copyright Christopher Diggins 2005
/// (C) Copyright Pablo Aguilar 2005
/// (C) Copyright Kevlin Henney 2001
///
/// Distributed under Boost Software License - Version 1.0.
/// See http://www.boost.org/LICENSE_1_0.txt for more information.

#ifndef ANY_H_
#define ANY_H_

#if 1

#include <boost/any.hpp>
typedef boost::any Any;

#else

#include <cstdlib>
#include <cstring>

namespace ngene
{
	namespace any
	{
		struct empty { };

		template<bool is_small>
		struct fn
		{
			template<typename T>
			struct type
			{
				//static const std::type_info& get_type()
				//{
				//	return typeid(T);
				//}
				static void static_delete(void** x)
				{
					reinterpret_cast<T*>(x)->~T();
				}
				static void clone(void** dst, void* const* src)
				{
					new(dst) T(*reinterpret_cast<T const*>(src));
				}
				static void move(void** dst, void* const* src)
				{
					reinterpret_cast<T*>(dst)->~T();
					*reinterpret_cast<T*>(dst) = *reinterpret_cast<T const*>(src);
				}
			};
		};

		template<>
		struct fn<false>
		{
			template<typename T>
			struct type
			{
				//static const std::type_info& get_type()
				//{
				//	return typeid(T);
				//}
				static void static_delete(void** x)
				{
					delete(*reinterpret_cast<T**>(x));
				}
				static void clone(void** dst, void* const* src)
				{
					*dst = new T(**reinterpret_cast<T* const*>(src));
				}
				static void move(void** dst, void* const* src)
				{
					(*reinterpret_cast<T**>(dst))->~T();
					**reinterpret_cast<T**>(dst) = **reinterpret_cast<T* const*>(src);
				}
			};
		};

		/// Table for storing type-safe function pointers.
		struct fn_ptr_table
		{
			//const std::type_info& (*get_type)();
			void (*static_delete)(void**);
			void (*clone)(void**, void* const*);
			void (*move)(void**, void* const*);
		};

		/// Table for retrieving type-safe function pointers.
		template<typename T>
		struct table
		{
			static const bool is_small = (sizeof(T) <= sizeof(void *));
			static fn_ptr_table* get()
			{
				static fn_ptr_table static_table =
				{
					//fn<is_small>::template type<T>::get_type,
					fn<is_small>::template type<T>::static_delete,
					fn<is_small>::template type<T>::clone,
					fn<is_small>::template type<T>::move
				};
				return &static_table;
			}
		};
	}
}

class Any
{
public:
	Any() : ptr(0), tbl(ngene::any::table<ngene::any::empty>::get()) { }

	Any(const Any &a) : tbl(a.tbl)
	{
		tbl->clone(&ptr, &a.ptr);
	}

	template<typename T>
	Any(const T &a) : tbl(ngene::any::table<T>::get())
	{
		if (ngene::any::table<T>::is_small)
			new(&ptr) T(a);
		else
			ptr = new T(a);
	}

	~Any()
	{
		tbl->static_delete(&ptr);
	}

	/// Casts data to type T and returns a pointer to it.
	template<typename T>
	inline T *cast ()
	{
		if (ngene::any::table<T>::is_small)
			return reinterpret_cast<T *>(&ptr);
		else
			return reinterpret_cast<T *>(ptr);
	}

	template<typename T>
	inline const T *cast () const
	{
		if (ngene::any::table<T>::is_small)
			return reinterpret_cast<const T *>(&ptr);
		else
			return reinterpret_cast<const T *>(ptr);
	}

	//const std::type_info& get_type() const
	//{
	//	return tbl->get_type();
	//}

	Any &operator =(const Any &a)
	{
		if (a.tbl == tbl)
			tbl->move(&ptr, &a.ptr);
		else
		{
			reset();
			a.tbl->clone(&ptr, &a.ptr);
			tbl = a.tbl;
		}
		return *this;
	}

	template<typename T>
	Any &operator =(const T &a)
	{
		ngene::any::fn_ptr_table *a_tbl = ngene::any::table<T>::get();
		if (tbl == a_tbl)
		{
			if (ngene::any::table<T>::is_small)
				new(&ptr) T(a);
			else
				new(ptr) T(a);
		}
		else
		{
			reset();
			if (ngene::any::table<T>::is_small)
				new(&ptr) T(a);
			else
				ptr = new T(a);
			tbl = a_tbl;
		}
		return *this;
	}

private:
	void *ptr;
	ngene::any::fn_ptr_table *tbl;

	inline void reset()
	{
		if (tbl == ngene::any::table<ngene::any::empty>::get()) return;
		tbl->static_delete(&ptr);
		tbl = ngene::any::table<ngene::any::empty>::get();
		ptr = 0;
	}
};

#endif

#endif
