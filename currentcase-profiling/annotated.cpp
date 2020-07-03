*** File /usr/include/c++/4.8.2/bits/vector.tcc:
                // Vector implementation (out of line) -*- C++ -*-
                
                // Copyright (C) 2001-2013 Free Software Foundation, Inc.
                //
                // This file is part of the GNU ISO C++ Library.  This library is free
                // software; you can redistribute it and/or modify it under the
                // terms of the GNU General Public License as published by the
                // Free Software Foundation; either version 3, or (at your option)
                // any later version.
                
                // This library is distributed in the hope that it will be useful,
                // but WITHOUT ANY WARRANTY; without even the implied warranty of
                // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
                // GNU General Public License for more details.
                
                // Under Section 7 of GPL version 3, you are granted additional
                // permissions described in the GCC Runtime Library Exception, version
                // 3.1, as published by the Free Software Foundation.
                
                // You should have received a copy of the GNU General Public License and
                // a copy of the GCC Runtime Library Exception along with this program;
                // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
                // <http://www.gnu.org/licenses/>.
                
                /*
                 *
                 * Copyright (c) 1994
                 * Hewlett-Packard Company
                 *
                 * Permission to use, copy, modify, distribute and sell this software
                 * and its documentation for any purpose is hereby granted without fee,
                 * provided that the above copyright notice appear in all copies and
                 * that both that copyright notice and this permission notice appear
                 * in supporting documentation.  Hewlett-Packard Company makes no
                 * representations about the suitability of this software for any
                 * purpose.  It is provided "as is" without express or implied warranty.
                 *
                 *
                 * Copyright (c) 1996
                 * Silicon Graphics Computer Systems, Inc.
                 *
                 * Permission to use, copy, modify, distribute and sell this software
                 * and its documentation for any purpose is hereby granted without fee,
                 * provided that the above copyright notice appear in all copies and
                 * that both that copyright notice and this permission notice appear
                 * in supporting documentation.  Silicon Graphics makes no
                 * representations about the suitability of this  software for any
                 * purpose.  It is provided "as is" without express or implied warranty.
                 */
                
                /** @file bits/vector.tcc
                 *  This is an internal header file, included by other library headers.
                 *  Do not attempt to use it directly. @headername{vector}
                 */
                
                #ifndef _VECTOR_TCC
                #define _VECTOR_TCC 1
                
                namespace std _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_CONTAINER
                
                  template<typename _Tp, typename _Alloc>
                    void
                    vector<_Tp, _Alloc>::
                    reserve(size_type __n)
                    {
                      if (__n > this->max_size())
                	__throw_length_error(__N("vector::reserve"));
                      if (this->capacity() < __n)
                	{
                	  const size_type __old_size = size();
                	  pointer __tmp = _M_allocate_and_copy(__n,
                	    _GLIBCXX_MAKE_MOVE_IF_NOEXCEPT_ITERATOR(this->_M_impl._M_start),
                	    _GLIBCXX_MAKE_MOVE_IF_NOEXCEPT_ITERATOR(this->_M_impl._M_finish));
                	  std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
                			_M_get_Tp_allocator());
                	  _M_deallocate(this->_M_impl._M_start,
                			this->_M_impl._M_end_of_storage
                			- this->_M_impl._M_start);
                	  this->_M_impl._M_start = __tmp;
                	  this->_M_impl._M_finish = __tmp + __old_size;
                	  this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
                	}
                    }
                
                #if __cplusplus >= 201103L
                  template<typename _Tp, typename _Alloc>
                    template<typename... _Args>
                      void
                      vector<_Tp, _Alloc>::
                      emplace_back(_Args&&... __args)
                      {
                	if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
                	  {
                	    _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
                				     std::forward<_Args>(__args)...);
                	    ++this->_M_impl._M_finish;
                	  }
                	else
                	  _M_emplace_back_aux(std::forward<_Args>(__args)...);
                      }
                #endif
                
                  template<typename _Tp, typename _Alloc>
                    typename vector<_Tp, _Alloc>::iterator
                    vector<_Tp, _Alloc>::
                    insert(iterator __position, const value_type& __x)
                    {
                      const size_type __n = __position - begin();
                      if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage
                	  && __position == end())
                	{
                	  _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish, __x);
                	  ++this->_M_impl._M_finish;
                	}
                      else
                	{
                #if __cplusplus >= 201103L
                	  if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
                	    {
                	      _Tp __x_copy = __x;
                	      _M_insert_aux(__position, std::move(__x_copy));
                	    }
                	  else
                #endif
                	    _M_insert_aux(__position, __x);
                	}
                      return iterator(this->_M_impl._M_start + __n);
                    }
                
                  template<typename _Tp, typename _Alloc>
                    typename vector<_Tp, _Alloc>::iterator
                    vector<_Tp, _Alloc>::
                    erase(iterator __position)
                    {
                      if (__position + 1 != end())
                	_GLIBCXX_MOVE3(__position + 1, end(), __position);
                      --this->_M_impl._M_finish;
                      _Alloc_traits::destroy(this->_M_impl, this->_M_impl._M_finish);
                      return __position;
                    }
                
                  template<typename _Tp, typename _Alloc>
                    typename vector<_Tp, _Alloc>::iterator
    26080000 ->     vector<_Tp, _Alloc>::
                    erase(iterator __first, iterator __last)
                    {
    26080000 ->       if (__first != __last)
                	{
    26080000 -> 	  if (__last != end())
    26080000 -> 	    _GLIBCXX_MOVE3(__last, end(), __first);
    26080000 -> 	  _M_erase_at_end(__first.base() + (end() - __last));
                	}
    26080000 ->       return __first;
    26080000 ->     }
                
                  template<typename _Tp, typename _Alloc>
                    vector<_Tp, _Alloc>&
                    vector<_Tp, _Alloc>::
                    operator=(const vector<_Tp, _Alloc>& __x)
                    {
                      if (&__x != this)
                	{
                #if __cplusplus >= 201103L
                	  if (_Alloc_traits::_S_propagate_on_copy_assign())
                	    {
                	      if (!_Alloc_traits::_S_always_equal()
                	          && _M_get_Tp_allocator() != __x._M_get_Tp_allocator())
                	        {
                		  // replacement allocator cannot free existing storage
                		  this->clear();
                		  _M_deallocate(this->_M_impl._M_start,
                				this->_M_impl._M_end_of_storage
                				- this->_M_impl._M_start);
                		  this->_M_impl._M_start = nullptr;
                		  this->_M_impl._M_finish = nullptr;
                		  this->_M_impl._M_end_of_storage = nullptr;
                		}
                	      std::__alloc_on_copy(_M_get_Tp_allocator(),
                				   __x._M_get_Tp_allocator());
                	    }
                #endif
                	  const size_type __xlen = __x.size();
                	  if (__xlen > capacity())
                	    {
                	      pointer __tmp = _M_allocate_and_copy(__xlen, __x.begin(),
                						   __x.end());
                	      std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
                			    _M_get_Tp_allocator());
                	      _M_deallocate(this->_M_impl._M_start,
                			    this->_M_impl._M_end_of_storage
                			    - this->_M_impl._M_start);
                	      this->_M_impl._M_start = __tmp;
                	      this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __xlen;
                	    }
                	  else if (size() >= __xlen)
                	    {
                	      std::_Destroy(std::copy(__x.begin(), __x.end(), begin()),
                			    end(), _M_get_Tp_allocator());
                	    }
                	  else
                	    {
                	      std::copy(__x._M_impl._M_start, __x._M_impl._M_start + size(),
                			this->_M_impl._M_start);
                	      std::__uninitialized_copy_a(__x._M_impl._M_start + size(),
                					  __x._M_impl._M_finish,
                					  this->_M_impl._M_finish,
                					  _M_get_Tp_allocator());
                	    }
                	  this->_M_impl._M_finish = this->_M_impl._M_start + __xlen;
                	}
                      return *this;
                    }
                
                  template<typename _Tp, typename _Alloc>
                    void
                    vector<_Tp, _Alloc>::
                    _M_fill_assign(size_t __n, const value_type& __val)
                    {
                      if (__n > capacity())
                	{
                	  vector __tmp(__n, __val, _M_get_Tp_allocator());
                	  __tmp.swap(*this);
                	}
                      else if (__n > size())
                	{
                	  std::fill(begin(), end(), __val);
                	  std::__uninitialized_fill_n_a(this->_M_impl._M_finish,
                					__n - size(), __val,
                					_M_get_Tp_allocator());
                	  this->_M_impl._M_finish += __n - size();
                	}
                      else
                        _M_erase_at_end(std::fill_n(this->_M_impl._M_start, __n, __val));
                    }
                
                  template<typename _Tp, typename _Alloc>
                    template<typename _InputIterator>
                      void
                      vector<_Tp, _Alloc>::
                      _M_assign_aux(_InputIterator __first, _InputIterator __last,
                		    std::input_iterator_tag)
                      {
                	pointer __cur(this->_M_impl._M_start);
                	for (; __first != __last && __cur != this->_M_impl._M_finish;
                	     ++__cur, ++__first)
                	  *__cur = *__first;
                	if (__first == __last)
                	  _M_erase_at_end(__cur);
                	else
                	  insert(end(), __first, __last);
                      }
                
                  template<typename _Tp, typename _Alloc>
                    template<typename _ForwardIterator>
                      void
                      vector<_Tp, _Alloc>::
                      _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
                		    std::forward_iterator_tag)
                      {
                	const size_type __len = std::distance(__first, __last);
                
                	if (__len > capacity())
                	  {
                	    pointer __tmp(_M_allocate_and_copy(__len, __first, __last));
                	    std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
                			  _M_get_Tp_allocator());
                	    _M_deallocate(this->_M_impl._M_start,
                			  this->_M_impl._M_end_of_storage
                			  - this->_M_impl._M_start);
                	    this->_M_impl._M_start = __tmp;
                	    this->_M_impl._M_finish = this->_M_impl._M_start + __len;
                	    this->_M_impl._M_end_of_storage = this->_M_impl._M_finish;
                	  }
                	else if (size() >= __len)
                	  _M_erase_at_end(std::copy(__first, __last, this->_M_impl._M_start));
                	else
                	  {
                	    _ForwardIterator __mid = __first;
                	    std::advance(__mid, size());
                	    std::copy(__first, __mid, this->_M_impl._M_start);
                	    this->_M_impl._M_finish =
                	      std::__uninitialized_copy_a(__mid, __last,
                					  this->_M_impl._M_finish,
                					  _M_get_Tp_allocator());
                	  }
                      }
                
                #if __cplusplus >= 201103L
                  template<typename _Tp, typename _Alloc>
                    template<typename... _Args>
                      typename vector<_Tp, _Alloc>::iterator
                      vector<_Tp, _Alloc>::
                      emplace(iterator __position, _Args&&... __args)
                      {
                	const size_type __n = __position - begin();
                	if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage
                	    && __position == end())
                	  {
                	    _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
                				     std::forward<_Args>(__args)...);
                	    ++this->_M_impl._M_finish;
                	  }
                	else
                	  _M_insert_aux(__position, std::forward<_Args>(__args)...);
                	return iterator(this->_M_impl._M_start + __n);
                      }
                
                  template<typename _Tp, typename _Alloc>
                    template<typename... _Args>
                      void
                      vector<_Tp, _Alloc>::
                      _M_insert_aux(iterator __position, _Args&&... __args)
                #else
                  template<typename _Tp, typename _Alloc>
                    void
     1439982 ->     vector<_Tp, _Alloc>::
                    _M_insert_aux(iterator __position, const _Tp& __x)
                #endif
                    {
     1439982 ->       if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
                	{
     1439982 -> 	  _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
                			           _GLIBCXX_MOVE(*(this->_M_impl._M_finish
     1439982 -> 				                   - 1)));
     1439982 -> 	  ++this->_M_impl._M_finish;
                #if __cplusplus < 201103L
     1439982 -> 	  _Tp __x_copy = __x;
                #endif
     1439982 -> 	  _GLIBCXX_MOVE_BACKWARD3(__position.base(),
                				  this->_M_impl._M_finish - 2,
                				  this->_M_impl._M_finish - 1);
                #if __cplusplus < 201103L
     1439982 -> 	  *__position = __x_copy;
                #else
                	  *__position = _Tp(std::forward<_Args>(__args)...);
                #endif
                	}
                      else
                	{
                	  const size_type __len =
     1439982 -> 	    _M_check_len(size_type(1), "vector::_M_insert_aux");
     1439982 -> 	  const size_type __elems_before = __position - begin();
     1439982 -> 	  pointer __new_start(this->_M_allocate(__len));
     1439982 -> 	  pointer __new_finish(__new_start);
                	  __try
                	    {
                	      // The order of the three operations is dictated by the C++0x
                	      // case, where the moves could alter a new element belonging
                	      // to the existing vector.  This is an issue only for callers
                	      // taking the element by const lvalue ref (see 23.1/13).
     1439982 -> 	      _Alloc_traits::construct(this->_M_impl,
                		                       __new_start + __elems_before,
                #if __cplusplus >= 201103L
                				       std::forward<_Args>(__args)...);
                #else
     1439982 -> 	                               __x);
                #endif
     1439982 -> 	      __new_finish = 0;
                
     1439982 -> 	      __new_finish
                		= std::__uninitialized_move_if_noexcept_a
                		(this->_M_impl._M_start, __position.base(),
     1439982 -> 		 __new_start, _M_get_Tp_allocator());
                
     1439982 -> 	      ++__new_finish;
                
     1439982 -> 	      __new_finish
                		= std::__uninitialized_move_if_noexcept_a
                		(__position.base(), this->_M_impl._M_finish,
     1439982 -> 		 __new_finish, _M_get_Tp_allocator());
                	    }
     1439982 ->           __catch(...)
                	    {
     1439982 -> 	      if (!__new_finish)
     1439982 -> 		_Alloc_traits::destroy(this->_M_impl,
     1439982 -> 		                       __new_start + __elems_before);
                	      else
     1439982 -> 		std::_Destroy(__new_start, __new_finish, _M_get_Tp_allocator());
     1439982 -> 	      _M_deallocate(__new_start, __len);
     1439982 -> 	      __throw_exception_again;
                	    }
     1439982 -> 	  std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
     1439982 -> 			_M_get_Tp_allocator());
     1439982 -> 	  _M_deallocate(this->_M_impl._M_start,
                			this->_M_impl._M_end_of_storage
     1439982 -> 			- this->_M_impl._M_start);
     1439982 -> 	  this->_M_impl._M_start = __new_start;
     1439982 -> 	  this->_M_impl._M_finish = __new_finish;
     1439982 -> 	  this->_M_impl._M_end_of_storage = __new_start + __len;
                	}
     1439982 ->     }
                
                #if __cplusplus >= 201103L
                  template<typename _Tp, typename _Alloc>
                    template<typename... _Args>
                      void
                      vector<_Tp, _Alloc>::
                      _M_emplace_back_aux(_Args&&... __args)
                      {
                	const size_type __len =
                	  _M_check_len(size_type(1), "vector::_M_emplace_back_aux");
                	pointer __new_start(this->_M_allocate(__len));
                	pointer __new_finish(__new_start);
                	__try
                	  {
                	    _Alloc_traits::construct(this->_M_impl, __new_start + size(),
                				     std::forward<_Args>(__args)...);
                	    __new_finish = 0;
                
                	    __new_finish
                	      = std::__uninitialized_move_if_noexcept_a
                	      (this->_M_impl._M_start, this->_M_impl._M_finish,
                	       __new_start, _M_get_Tp_allocator());
                
                	    ++__new_finish;
                	  }
                	__catch(...)
                	  {
                	    if (!__new_finish)
                	      _Alloc_traits::destroy(this->_M_impl, __new_start + size());
                	    else
                	      std::_Destroy(__new_start, __new_finish, _M_get_Tp_allocator());
                	    _M_deallocate(__new_start, __len);
                	    __throw_exception_again;
                	  }
                	std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
                		      _M_get_Tp_allocator());
                	_M_deallocate(this->_M_impl._M_start,
                		      this->_M_impl._M_end_of_storage
                		      - this->_M_impl._M_start);
                	this->_M_impl._M_start = __new_start;
                	this->_M_impl._M_finish = __new_finish;
                	this->_M_impl._M_end_of_storage = __new_start + __len;
                      }
                #endif
                
                  template<typename _Tp, typename _Alloc>
                    void
                    vector<_Tp, _Alloc>::
                    _M_fill_insert(iterator __position, size_type __n, const value_type& __x)
                    {
                      if (__n != 0)
                	{
                	  if (size_type(this->_M_impl._M_end_of_storage
                			- this->_M_impl._M_finish) >= __n)
                	    {
                	      value_type __x_copy = __x;
                	      const size_type __elems_after = end() - __position;
                	      pointer __old_finish(this->_M_impl._M_finish);
                	      if (__elems_after > __n)
                		{
                		  std::__uninitialized_move_a(this->_M_impl._M_finish - __n,
                					      this->_M_impl._M_finish,
                					      this->_M_impl._M_finish,
                					      _M_get_Tp_allocator());
                		  this->_M_impl._M_finish += __n;
                		  _GLIBCXX_MOVE_BACKWARD3(__position.base(),
                					  __old_finish - __n, __old_finish);
                		  std::fill(__position.base(), __position.base() + __n,
                			    __x_copy);
                		}
                	      else
                		{
                		  std::__uninitialized_fill_n_a(this->_M_impl._M_finish,
                						__n - __elems_after,
                						__x_copy,
                						_M_get_Tp_allocator());
                		  this->_M_impl._M_finish += __n - __elems_after;
                		  std::__uninitialized_move_a(__position.base(), __old_finish,
                					      this->_M_impl._M_finish,
                					      _M_get_Tp_allocator());
                		  this->_M_impl._M_finish += __elems_after;
                		  std::fill(__position.base(), __old_finish, __x_copy);
                		}
                	    }
                	  else
                	    {
                	      const size_type __len =
                		_M_check_len(__n, "vector::_M_fill_insert");
                	      const size_type __elems_before = __position - begin();
                	      pointer __new_start(this->_M_allocate(__len));
                	      pointer __new_finish(__new_start);
                	      __try
                		{
                		  // See _M_insert_aux above.
                		  std::__uninitialized_fill_n_a(__new_start + __elems_before,
                						__n, __x,
                						_M_get_Tp_allocator());
                		  __new_finish = 0;
                
                		  __new_finish
                		    = std::__uninitialized_move_if_noexcept_a
                		    (this->_M_impl._M_start, __position.base(),
                		     __new_start, _M_get_Tp_allocator());
                
                		  __new_finish += __n;
                
                		  __new_finish
                		    = std::__uninitialized_move_if_noexcept_a
                		    (__position.base(), this->_M_impl._M_finish,
                		     __new_finish, _M_get_Tp_allocator());
                		}
                	      __catch(...)
                		{
                		  if (!__new_finish)
                		    std::_Destroy(__new_start + __elems_before,
                				  __new_start + __elems_before + __n,
                				  _M_get_Tp_allocator());
                		  else
                		    std::_Destroy(__new_start, __new_finish,
                				  _M_get_Tp_allocator());
                		  _M_deallocate(__new_start, __len);
                		  __throw_exception_again;
                		}
                	      std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
                			    _M_get_Tp_allocator());
                	      _M_deallocate(this->_M_impl._M_start,
                			    this->_M_impl._M_end_of_storage
                			    - this->_M_impl._M_start);
                	      this->_M_impl._M_start = __new_start;
                	      this->_M_impl._M_finish = __new_finish;
                	      this->_M_impl._M_end_of_storage = __new_start + __len;
                	    }
                	}
                    }
                
                #if __cplusplus >= 201103L
                  template<typename _Tp, typename _Alloc>
                    void
                    vector<_Tp, _Alloc>::
                    _M_default_append(size_type __n)
                    {
                      if (__n != 0)
                	{
                	  if (size_type(this->_M_impl._M_end_of_storage
                			- this->_M_impl._M_finish) >= __n)
                	    {
                	      std::__uninitialized_default_n_a(this->_M_impl._M_finish,
                					       __n, _M_get_Tp_allocator());
                	      this->_M_impl._M_finish += __n;
                	    }
                	  else
                	    {
                	      const size_type __len =
                		_M_check_len(__n, "vector::_M_default_append");
                	      const size_type __old_size = this->size();
                	      pointer __new_start(this->_M_allocate(__len));
                	      pointer __new_finish(__new_start);
                	      __try
                		{
                		  __new_finish
                		    = std::__uninitialized_move_if_noexcept_a
                		    (this->_M_impl._M_start, this->_M_impl._M_finish,
                		     __new_start, _M_get_Tp_allocator());
                		  std::__uninitialized_default_n_a(__new_finish, __n,
                						   _M_get_Tp_allocator());
                		  __new_finish += __n;
                		}
                	      __catch(...)
                		{
                		  std::_Destroy(__new_start, __new_finish,
                				_M_get_Tp_allocator());
                		  _M_deallocate(__new_start, __len);
                		  __throw_exception_again;
                		}
                	      std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
                			    _M_get_Tp_allocator());
                	      _M_deallocate(this->_M_impl._M_start,
                			    this->_M_impl._M_end_of_storage
                			    - this->_M_impl._M_start);
                	      this->_M_impl._M_start = __new_start;
                	      this->_M_impl._M_finish = __new_finish;
                	      this->_M_impl._M_end_of_storage = __new_start + __len;
                	    }
                	}
                    }
                
                  template<typename _Tp, typename _Alloc>
                    bool
                    vector<_Tp, _Alloc>::
                    _M_shrink_to_fit()
                    {
                      if (capacity() == size())
                	return false;
                      return std::__shrink_to_fit_aux<vector>::_S_do_it(*this);
                    }
                #endif
                
                  template<typename _Tp, typename _Alloc>
                    template<typename _InputIterator>
                      void
                      vector<_Tp, _Alloc>::
                      _M_range_insert(iterator __pos, _InputIterator __first,
                		      _InputIterator __last, std::input_iterator_tag)
                      {
                	for (; __first != __last; ++__first)
                	  {
                	    __pos = insert(__pos, *__first);
                	    ++__pos;
                	  }
                      }
                
                  template<typename _Tp, typename _Alloc>
                    template<typename _ForwardIterator>
                      void
                      vector<_Tp, _Alloc>::
                      _M_range_insert(iterator __position, _ForwardIterator __first,
                		      _ForwardIterator __last, std::forward_iterator_tag)
                      {
                	if (__first != __last)
                	  {
                	    const size_type __n = std::distance(__first, __last);
                	    if (size_type(this->_M_impl._M_end_of_storage
                			  - this->_M_impl._M_finish) >= __n)
                	      {
                		const size_type __elems_after = end() - __position;
                		pointer __old_finish(this->_M_impl._M_finish);
                		if (__elems_after > __n)
                		  {
                		    std::__uninitialized_move_a(this->_M_impl._M_finish - __n,
                						this->_M_impl._M_finish,
                						this->_M_impl._M_finish,
                						_M_get_Tp_allocator());
                		    this->_M_impl._M_finish += __n;
                		    _GLIBCXX_MOVE_BACKWARD3(__position.base(),
                					    __old_finish - __n, __old_finish);
                		    std::copy(__first, __last, __position);
                		  }
                		else
                		  {
                		    _ForwardIterator __mid = __first;
                		    std::advance(__mid, __elems_after);
                		    std::__uninitialized_copy_a(__mid, __last,
                						this->_M_impl._M_finish,
                						_M_get_Tp_allocator());
                		    this->_M_impl._M_finish += __n - __elems_after;
                		    std::__uninitialized_move_a(__position.base(),
                						__old_finish,
                						this->_M_impl._M_finish,
                						_M_get_Tp_allocator());
                		    this->_M_impl._M_finish += __elems_after;
                		    std::copy(__first, __mid, __position);
                		  }
                	      }
                	    else
                	      {
                		const size_type __len =
                		  _M_check_len(__n, "vector::_M_range_insert");
                		pointer __new_start(this->_M_allocate(__len));
                		pointer __new_finish(__new_start);
                		__try
                		  {
                		    __new_finish
                		      = std::__uninitialized_move_if_noexcept_a
                		      (this->_M_impl._M_start, __position.base(),
                		       __new_start, _M_get_Tp_allocator());
                		    __new_finish
                		      = std::__uninitialized_copy_a(__first, __last,
                						    __new_finish,
                						    _M_get_Tp_allocator());
                		    __new_finish
                		      = std::__uninitialized_move_if_noexcept_a
                		      (__position.base(), this->_M_impl._M_finish,
                		       __new_finish, _M_get_Tp_allocator());
                		  }
                		__catch(...)
                		  {
                		    std::_Destroy(__new_start, __new_finish,
                				  _M_get_Tp_allocator());
                		    _M_deallocate(__new_start, __len);
                		    __throw_exception_again;
                		  }
                		std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
                			      _M_get_Tp_allocator());
                		_M_deallocate(this->_M_impl._M_start,
                			      this->_M_impl._M_end_of_storage
                			      - this->_M_impl._M_start);
                		this->_M_impl._M_start = __new_start;
                		this->_M_impl._M_finish = __new_finish;
                		this->_M_impl._M_end_of_storage = __new_start + __len;
                	      }
                	  }
                      }
                
                
                  // vector<bool>
                  template<typename _Alloc>
                    void
                    vector<bool, _Alloc>::
                    _M_reallocate(size_type __n)
                    {
                      _Bit_type* __q = this->_M_allocate(__n);
                      this->_M_impl._M_finish = _M_copy_aligned(begin(), end(),
                						iterator(__q, 0));
                      this->_M_deallocate();
                      this->_M_impl._M_start = iterator(__q, 0);
                      this->_M_impl._M_end_of_storage = __q + _S_nword(__n);
                    }
                
                  template<typename _Alloc>
                    void
                    vector<bool, _Alloc>::
                    _M_fill_insert(iterator __position, size_type __n, bool __x)
                    {
                      if (__n == 0)
                	return;
                      if (capacity() - size() >= __n)
                	{
                	  std::copy_backward(__position, end(),
                			     this->_M_impl._M_finish + difference_type(__n));
                	  std::fill(__position, __position + difference_type(__n), __x);
                	  this->_M_impl._M_finish += difference_type(__n);
                	}
                      else
                	{
                	  const size_type __len = 
                	    _M_check_len(__n, "vector<bool>::_M_fill_insert");
                	  _Bit_type * __q = this->_M_allocate(__len);
                	  iterator __i = _M_copy_aligned(begin(), __position,
                					 iterator(__q, 0));
                	  std::fill(__i, __i + difference_type(__n), __x);
                	  this->_M_impl._M_finish = std::copy(__position, end(),
                					      __i + difference_type(__n));
                	  this->_M_deallocate();
                	  this->_M_impl._M_end_of_storage = __q + _S_nword(__len);
                	  this->_M_impl._M_start = iterator(__q, 0);
                	}
                    }
                
                  template<typename _Alloc>
                    template<typename _ForwardIterator>
                      void
                      vector<bool, _Alloc>::
                      _M_insert_range(iterator __position, _ForwardIterator __first, 
                		      _ForwardIterator __last, std::forward_iterator_tag)
                      {
                	if (__first != __last)
                	  {
                	    size_type __n = std::distance(__first, __last);
                	    if (capacity() - size() >= __n)
                	      {
                		std::copy_backward(__position, end(),
                				   this->_M_impl._M_finish
                				   + difference_type(__n));
                		std::copy(__first, __last, __position);
                		this->_M_impl._M_finish += difference_type(__n);
                	      }
                	    else
                	      {
                		const size_type __len =
                		  _M_check_len(__n, "vector<bool>::_M_insert_range");
                		_Bit_type * __q = this->_M_allocate(__len);
                		iterator __i = _M_copy_aligned(begin(), __position,
                					       iterator(__q, 0));
                		__i = std::copy(__first, __last, __i);
                		this->_M_impl._M_finish = std::copy(__position, end(), __i);
                		this->_M_deallocate();
                		this->_M_impl._M_end_of_storage = __q + _S_nword(__len);
                		this->_M_impl._M_start = iterator(__q, 0);
                	      }
                	  }
                      }
                
                  template<typename _Alloc>
                    void
                    vector<bool, _Alloc>::
                    _M_insert_aux(iterator __position, bool __x)
                    {
                      if (this->_M_impl._M_finish._M_p != this->_M_impl._M_end_of_storage)
                	{
                	  std::copy_backward(__position, this->_M_impl._M_finish, 
                			     this->_M_impl._M_finish + 1);
                	  *__position = __x;
                	  ++this->_M_impl._M_finish;
                	}
                      else
                	{
                	  const size_type __len =
                	    _M_check_len(size_type(1), "vector<bool>::_M_insert_aux");
                	  _Bit_type * __q = this->_M_allocate(__len);
                	  iterator __i = _M_copy_aligned(begin(), __position,
                					 iterator(__q, 0));
                	  *__i++ = __x;
                	  this->_M_impl._M_finish = std::copy(__position, end(), __i);
                	  this->_M_deallocate();
                	  this->_M_impl._M_end_of_storage = __q + _S_nword(__len);
                	  this->_M_impl._M_start = iterator(__q, 0);
                	}
                    }
                
                #if __cplusplus >= 201103L
                  template<typename _Alloc>
                    bool
                    vector<bool, _Alloc>::
                    _M_shrink_to_fit()
                    {
                      if (capacity() - size() < int(_S_word_bit))
                	return false;
                      __try
                	{
                	  _M_reallocate(size());
                	  return true;
                	}
                      __catch(...)
                	{ return false; }
                    }
                #endif
                
                _GLIBCXX_END_NAMESPACE_CONTAINER
                } // namespace std
                
                #if __cplusplus >= 201103L
                
                namespace std _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                  template<typename _Alloc>
                    size_t
                    hash<_GLIBCXX_STD_C::vector<bool, _Alloc>>::
                    operator()(const _GLIBCXX_STD_C::vector<bool, _Alloc>& __b) const noexcept
                    {
                      size_t __hash = 0;
                      using _GLIBCXX_STD_C::_S_word_bit;
                      using _GLIBCXX_STD_C::_Bit_type;
                
                      const size_t __words = __b.size() / _S_word_bit;
                      if (__words)
                	{
                	  const size_t __clength = __words * sizeof(_Bit_type);
                	  __hash = std::_Hash_impl::hash(__b._M_impl._M_start._M_p, __clength);
                	}
                
                      const size_t __extrabits = __b.size() % _S_word_bit;
                      if (__extrabits)
                	{
                	  _Bit_type __hiword = *__b._M_impl._M_finish._M_p;
                	  __hiword &= ~((~static_cast<_Bit_type>(0)) << __extrabits);
                
                	  const size_t __clength
                	    = (__extrabits + __CHAR_BIT__ - 1) / __CHAR_BIT__;
                	  if (__words)
                	    __hash = std::_Hash_impl::hash(&__hiword, __clength, __hash);
                	  else
                	    __hash = std::_Hash_impl::hash(&__hiword, __clength);
                	}
                
                      return __hash;
                    }
                
                _GLIBCXX_END_NAMESPACE_VERSION
                } // namespace std
                
                #endif // C++11
                
                #endif /* _VECTOR_TCC */


Top 10 Lines:

     Line      Count

      146   26080000
      318    1439982

Execution Summary:

       42   Executable lines in this file
       42   Lines executed
   100.00   Percent of the file executed

 27519982   Total number of line executions
655237.67   Average executions per line


*** File /usr/include/c++/4.8.2/ext/alloc_traits.h:
                // Allocator traits -*- C++ -*-
                
                // Copyright (C) 2011-2013 Free Software Foundation, Inc.
                //
                // This file is part of the GNU ISO C++ Library.  This library is free
                // software; you can redistribute it and/or modify it under the
                // terms of the GNU General Public License as published by the
                // Free Software Foundation; either version 3, or (at your option)
                // any later version.
                
                // This library is distributed in the hope that it will be useful,
                // but WITHOUT ANY WARRANTY; without even the implied warranty of
                // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
                // GNU General Public License for more details.
                
                // Under Section 7 of GPL version 3, you are granted additional
                // permissions described in the GCC Runtime Library Exception, version
                // 3.1, as published by the Free Software Foundation.
                
                // You should have received a copy of the GNU General Public License and
                // a copy of the GCC Runtime Library Exception along with this program;
                // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
                // <http://www.gnu.org/licenses/>.
                
                /** @file ext/alloc_traits.h
                 *  This file is a GNU extension to the Standard C++ Library.
                 */
                
                #ifndef _EXT_ALLOC_TRAITS_H
                #define _EXT_ALLOC_TRAITS_H 1
                
                #pragma GCC system_header
                
                #if __cplusplus >= 201103L
                # include <bits/move.h>
                # include <bits/alloc_traits.h>
                #else
                # include <bits/allocator.h>  // for __alloc_swap
                #endif
                
                namespace __gnu_cxx _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                #if __cplusplus >= 201103L
                  template<typename _Alloc>
                    struct __allocator_always_compares_equal
                    { static const bool value = false; };
                
                  template<typename _Alloc>
                    const bool __allocator_always_compares_equal<_Alloc>::value;
                
                  template<typename _Tp>
                    struct __allocator_always_compares_equal<std::allocator<_Tp>>
                    { static const bool value = true; };
                
                  template<typename _Tp>
                    const bool __allocator_always_compares_equal<std::allocator<_Tp>>::value;
                
                  template<typename, typename> struct array_allocator;
                
                  template<typename _Tp, typename _Array>
                    struct __allocator_always_compares_equal<array_allocator<_Tp, _Array>>
                    { static const bool value = true; };
                
                  template<typename _Tp, typename _Array>
                    const bool
                    __allocator_always_compares_equal<array_allocator<_Tp, _Array>>::value;
                
                  template<typename> struct bitmap_allocator;
                
                  template<typename _Tp>
                    struct __allocator_always_compares_equal<bitmap_allocator<_Tp>>
                    { static const bool value = true; };
                
                  template<typename _Tp>
                    const bool __allocator_always_compares_equal<bitmap_allocator<_Tp>>::value;
                
                  template<typename> struct malloc_allocator;
                
                  template<typename _Tp>
                    struct __allocator_always_compares_equal<malloc_allocator<_Tp>>
                    { static const bool value = true; };
                
                  template<typename _Tp>
                    const bool __allocator_always_compares_equal<malloc_allocator<_Tp>>::value;
                
                  template<typename> struct mt_allocator;
                
                  template<typename _Tp>
                    struct __allocator_always_compares_equal<mt_allocator<_Tp>>
                    { static const bool value = true; };
                
                  template<typename _Tp>
                    const bool __allocator_always_compares_equal<mt_allocator<_Tp>>::value;
                
                  template<typename> struct new_allocator;
                
                  template<typename _Tp>
                    struct __allocator_always_compares_equal<new_allocator<_Tp>>
                    { static const bool value = true; };
                
                  template<typename _Tp>
                    const bool __allocator_always_compares_equal<new_allocator<_Tp>>::value;
                
                  template<typename> struct pool_allocator;
                
                  template<typename _Tp>
                    struct __allocator_always_compares_equal<pool_allocator<_Tp>>
                    { static const bool value = true; };
                
                  template<typename _Tp>
                    const bool __allocator_always_compares_equal<pool_allocator<_Tp>>::value;
                #endif
                
                /**
                 * @brief  Uniform interface to C++98 and C++0x allocators.
                 * @ingroup allocators
                */
                template<typename _Alloc>
                  struct __alloc_traits
                #if __cplusplus >= 201103L
                  : std::allocator_traits<_Alloc>
                #endif
                  {
                    typedef _Alloc allocator_type;
                #if __cplusplus >= 201103L
                    typedef std::allocator_traits<_Alloc>           _Base_type;
                    typedef typename _Base_type::value_type         value_type;
                    typedef typename _Base_type::pointer            pointer;
                    typedef typename _Base_type::const_pointer      const_pointer;
                    typedef typename _Base_type::size_type          size_type;
                    typedef typename _Base_type::difference_type    difference_type;
                    // C++0x allocators do not define reference or const_reference
                    typedef value_type&                             reference;
                    typedef const value_type&                       const_reference;
                    using _Base_type::allocate;
                    using _Base_type::deallocate;
                    using _Base_type::construct;
                    using _Base_type::destroy;
                    using _Base_type::max_size;
                
                  private:
                    template<typename _Ptr>
                      struct __is_custom_pointer
                      : std::integral_constant<bool, std::is_same<pointer, _Ptr>::value
                                                     && !std::is_pointer<_Ptr>::value>
                      { };
                
                  public:
                    // overload construct for non-standard pointer types
                    template<typename _Ptr, typename... _Args>
                      static typename std::enable_if<__is_custom_pointer<_Ptr>::value>::type
                      construct(_Alloc& __a, _Ptr __p, _Args&&... __args)
                      {
                	_Base_type::construct(__a, std::addressof(*__p),
                			      std::forward<_Args>(__args)...);
                      }
                
                    // overload destroy for non-standard pointer types
                    template<typename _Ptr>
                      static typename std::enable_if<__is_custom_pointer<_Ptr>::value>::type
                      destroy(_Alloc& __a, _Ptr __p)
                      { _Base_type::destroy(__a, std::addressof(*__p)); }
                
                    static _Alloc _S_select_on_copy(const _Alloc& __a)
                    { return _Base_type::select_on_container_copy_construction(__a); }
                
                    static void _S_on_swap(_Alloc& __a, _Alloc& __b)
                    { std::__alloc_on_swap(__a, __b); }
                
                    static constexpr bool _S_propagate_on_copy_assign()
                    { return _Base_type::propagate_on_container_copy_assignment::value; }
                
                    static constexpr bool _S_propagate_on_move_assign()
                    { return _Base_type::propagate_on_container_move_assignment::value; }
                
                    static constexpr bool _S_propagate_on_swap()
                    { return _Base_type::propagate_on_container_swap::value; }
                
                    static constexpr bool _S_always_equal()
                    { return __allocator_always_compares_equal<_Alloc>::value; }
                
                    static constexpr bool _S_nothrow_move()
                    { return _S_propagate_on_move_assign() || _S_always_equal(); }
                
                    static constexpr bool _S_nothrow_swap()
                    {
                      using std::swap;
                      return !_S_propagate_on_swap()
                       	|| noexcept(swap(std::declval<_Alloc&>(), std::declval<_Alloc&>()));
                    }
                
                    template<typename _Tp>
                      struct rebind
                      { typedef typename _Base_type::template rebind_alloc<_Tp> other; };
                #else
                
                    typedef typename _Alloc::pointer                pointer;
                    typedef typename _Alloc::const_pointer          const_pointer;
                    typedef typename _Alloc::value_type             value_type;
                    typedef typename _Alloc::reference              reference;
                    typedef typename _Alloc::const_reference        const_reference;
                    typedef typename _Alloc::size_type              size_type;
                    typedef typename _Alloc::difference_type        difference_type;
                
                    static pointer
                    allocate(_Alloc& __a, size_type __n)
                    { return __a.allocate(__n); }
                
                    static void deallocate(_Alloc& __a, pointer __p, size_type __n)
                    { __a.deallocate(__p, __n); }
                
                    template<typename _Tp>
  3783529118 ->       static void construct(_Alloc& __a, pointer __p, const _Tp& __arg)
  3783529118 ->       { __a.construct(__p, __arg); }
                
       ##### ->     static void destroy(_Alloc& __a, pointer __p)
       ##### ->     { __a.destroy(__p); }
                
     2879964 ->     static size_type max_size(const _Alloc& __a)
     2879964 ->     { return __a.max_size(); }
                
                    static const _Alloc& _S_select_on_copy(const _Alloc& __a) { return __a; }
                
                    static void _S_on_swap(_Alloc& __a, _Alloc& __b)
                    {
                      // _GLIBCXX_RESOLVE_LIB_DEFECTS
                      // 431. Swapping containers with unequal allocators.
                      std::__alloc_swap<_Alloc>::_S_do_it(__a, __b);
                    }
                
                    template<typename _Tp>
                      struct rebind
                      { typedef typename _Alloc::template rebind<_Tp>::other other; };
                #endif
                  };
                
                _GLIBCXX_END_NAMESPACE_VERSION
                } // namespace std
                
                #endif


Top 10 Lines:

     Line      Count

      215 3783529118
      221    2879964

Execution Summary:

        6   Executable lines in this file
        6   Lines executed
   100.00   Percent of the file executed

3786409082   Total number of line executions
631068180.33   Average executions per line


*** File /usr/include/c++/4.8.2/new:
                // The -*- C++ -*- dynamic memory management header.
                
                // Copyright (C) 1994-2013 Free Software Foundation, Inc.
                
                // This file is part of GCC.
                //
                // GCC is free software; you can redistribute it and/or modify
                // it under the terms of the GNU General Public License as published by
                // the Free Software Foundation; either version 3, or (at your option)
                // any later version.
                // 
                // GCC is distributed in the hope that it will be useful,
                // but WITHOUT ANY WARRANTY; without even the implied warranty of
                // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
                // GNU General Public License for more details.
                // 
                // Under Section 7 of GPL version 3, you are granted additional
                // permissions described in the GCC Runtime Library Exception, version
                // 3.1, as published by the Free Software Foundation.
                
                // You should have received a copy of the GNU General Public License and
                // a copy of the GCC Runtime Library Exception along with this program;
                // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
                // <http://www.gnu.org/licenses/>.
                
                /** @file new
                 *  This is a Standard C++ Library header.
                 *
                 *  The header @c new defines several functions to manage dynamic memory and
                 *  handling memory allocation errors; see
                 *  http://gcc.gnu.org/onlinedocs/libstdc++/18_support/howto.html#4 for more.
                 */
                
                #ifndef _NEW
                #define _NEW
                
                #pragma GCC system_header
                
                #include <bits/c++config.h>
                #include <exception>
                
                #pragma GCC visibility push(default)
                
                extern "C++" {
                
                namespace std 
                {
                  /**
                   *  @brief  Exception possibly thrown by @c new.
                   *  @ingroup exceptions
                   *
                   *  @c bad_alloc (or classes derived from it) is used to report allocation
                   *  errors from the throwing forms of @c new.  */
                  class bad_alloc : public exception 
                  {
                  public:
                    bad_alloc() throw() { }
                
                    // This declaration is not useless:
                    // http://gcc.gnu.org/onlinedocs/gcc-3.0.2/gcc_6.html#SEC118
                    virtual ~bad_alloc() throw();
                
                    // See comment in eh_exception.cc.
                    virtual const char* what() const throw();
                  };
                
                  struct nothrow_t { };
                
                  extern const nothrow_t nothrow;
                
                  /** If you write your own error handler to be called by @c new, it must
                   *  be of this type.  */
                  typedef void (*new_handler)();
                
                  /// Takes a replacement handler as the argument, returns the
                  /// previous handler.
                  new_handler set_new_handler(new_handler) throw();
                } // namespace std
                
                //@{
                /** These are replaceable signatures:
                 *  - normal single new and delete (no arguments, throw @c bad_alloc on error)
                 *  - normal array new and delete (same)
                 *  - @c nothrow single new and delete (take a @c nothrow argument, return
                 *    @c NULL on error)
                 *  - @c nothrow array new and delete (same)
                 *
                 *  Placement new and delete signatures (take a memory address argument,
                 *  does nothing) may not be replaced by a user's program.
                */
                void* operator new(std::size_t) _GLIBCXX_THROW (std::bad_alloc)
                  __attribute__((__externally_visible__));
                void* operator new[](std::size_t) _GLIBCXX_THROW (std::bad_alloc)
                  __attribute__((__externally_visible__));
                void operator delete(void*) _GLIBCXX_USE_NOEXCEPT
                  __attribute__((__externally_visible__));
                void operator delete[](void*) _GLIBCXX_USE_NOEXCEPT
                  __attribute__((__externally_visible__));
                void* operator new(std::size_t, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
                  __attribute__((__externally_visible__));
                void* operator new[](std::size_t, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
                  __attribute__((__externally_visible__));
                void operator delete(void*, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
                  __attribute__((__externally_visible__));
                void operator delete[](void*, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
                  __attribute__((__externally_visible__));
                
                // Default placement versions of operator new.
                inline void* operator new(std::size_t, void* __p) _GLIBCXX_USE_NOEXCEPT
  3783529118 -> { return __p; }
                inline void* operator new[](std::size_t, void* __p) _GLIBCXX_USE_NOEXCEPT
                { return __p; }
                
                // Default placement versions of operator delete.
                inline void operator delete  (void*, void*) _GLIBCXX_USE_NOEXCEPT { }
                inline void operator delete[](void*, void*) _GLIBCXX_USE_NOEXCEPT { }
                //@}
                } // extern "C++"
                
                #pragma GCC visibility pop
                
                #endif


Top 10 Lines:

     Line      Count

      110 3783529118

Execution Summary:

        1   Executable lines in this file
        1   Lines executed
   100.00   Percent of the file executed

3783529118   Total number of line executions
3783529118.00   Average executions per line


*** File /usr/include/c++/4.8.2/bits/stl_construct.h:
                // nonstandard construct and destroy functions -*- C++ -*-
                
                // Copyright (C) 2001-2013 Free Software Foundation, Inc.
                //
                // This file is part of the GNU ISO C++ Library.  This library is free
                // software; you can redistribute it and/or modify it under the
                // terms of the GNU General Public License as published by the
                // Free Software Foundation; either version 3, or (at your option)
                // any later version.
                
                // This library is distributed in the hope that it will be useful,
                // but WITHOUT ANY WARRANTY; without even the implied warranty of
                // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
                // GNU General Public License for more details.
                
                // Under Section 7 of GPL version 3, you are granted additional
                // permissions described in the GCC Runtime Library Exception, version
                // 3.1, as published by the Free Software Foundation.
                
                // You should have received a copy of the GNU General Public License and
                // a copy of the GCC Runtime Library Exception along with this program;
                // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
                // <http://www.gnu.org/licenses/>.
                
                /*
                 *
                 * Copyright (c) 1994
                 * Hewlett-Packard Company
                 *
                 * Permission to use, copy, modify, distribute and sell this software
                 * and its documentation for any purpose is hereby granted without fee,
                 * provided that the above copyright notice appear in all copies and
                 * that both that copyright notice and this permission notice appear
                 * in supporting documentation.  Hewlett-Packard Company makes no
                 * representations about the suitability of this software for any
                 * purpose.  It is provided "as is" without express or implied warranty.
                 *
                 *
                 * Copyright (c) 1996,1997
                 * Silicon Graphics Computer Systems, Inc.
                 *
                 * Permission to use, copy, modify, distribute and sell this software
                 * and its documentation for any purpose is hereby granted without fee,
                 * provided that the above copyright notice appear in all copies and
                 * that both that copyright notice and this permission notice appear
                 * in supporting documentation.  Silicon Graphics makes no
                 * representations about the suitability of this software for any
                 * purpose.  It is provided "as is" without express or implied warranty.
                 */
                
                /** @file bits/stl_construct.h
                 *  This is an internal header file, included by other library headers.
                 *  Do not attempt to use it directly. @headername{memory}
                 */
                
                #ifndef _STL_CONSTRUCT_H
                #define _STL_CONSTRUCT_H 1
                
                #include <new>
                #include <bits/move.h>
                #include <ext/alloc_traits.h>
                
                namespace std _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                  /**
                   * Constructs an object in existing memory by invoking an allocated
                   * object's constructor with an initializer.
                   */
                #if __cplusplus >= 201103L
                  template<typename _T1, typename... _Args>
                    inline void
                    _Construct(_T1* __p, _Args&&... __args)
                    { ::new(static_cast<void*>(__p)) _T1(std::forward<_Args>(__args)...); }
                #else
                  template<typename _T1, typename _T2>
                    inline void
                    _Construct(_T1* __p, const _T2& __value)
                    {
                      // _GLIBCXX_RESOLVE_LIB_DEFECTS
                      // 402. wrong new expression in [some_]allocator::construct
                      ::new(static_cast<void*>(__p)) _T1(__value);
                    }
                #endif
                
                  /**
                   * Destroy the object pointed to by a pointer type.
                   */
                  template<typename _Tp>
                    inline void
                    _Destroy(_Tp* __pointer)
                    { __pointer->~_Tp(); }
                
                  template<bool>
                    struct _Destroy_aux
                    {
                      template<typename _ForwardIterator>
                        static void
                        __destroy(_ForwardIterator __first, _ForwardIterator __last)
                	{
                	  for (; __first != __last; ++__first)
                	    std::_Destroy(std::__addressof(*__first));
                	}
                    };
                
                  template<>
                    struct _Destroy_aux<true>
                    {
                      template<typename _ForwardIterator>
                        static void
   655625534 ->         __destroy(_ForwardIterator, _ForwardIterator) { }
                    };
                
                  /**
                   * Destroy a range of objects.  If the value_type of the object has
                   * a trivial destructor, the compiler should optimize all of this
                   * away, otherwise the objects' destructors must be invoked.
                   */
                  template<typename _ForwardIterator>
                    inline void
   655625534 ->     _Destroy(_ForwardIterator __first, _ForwardIterator __last)
                    {
                      typedef typename iterator_traits<_ForwardIterator>::value_type
                                       _Value_type;
   655625534 ->       std::_Destroy_aux<__has_trivial_destructor(_Value_type)>::
                	__destroy(__first, __last);
   655625534 ->     }
                
                  /**
                   * Destroy a range of objects using the supplied allocator.  For
                   * nondefault allocators we do not optimize away invocation of 
                   * destroy() even if _Tp has a trivial destructor.
                   */
                
                  template<typename _ForwardIterator, typename _Allocator>
                    void
                    _Destroy(_ForwardIterator __first, _ForwardIterator __last,
                	     _Allocator& __alloc)
                    {
                      typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
                      for (; __first != __last; ++__first)
                	__traits::destroy(__alloc, std::__addressof(*__first));
                    }
                
                  template<typename _ForwardIterator, typename _Tp>
                    inline void
   655625534 ->     _Destroy(_ForwardIterator __first, _ForwardIterator __last,
                	     allocator<_Tp>&)
                    {
   655625534 ->       _Destroy(__first, __last);
   655625534 ->     }
                
                _GLIBCXX_END_NAMESPACE_VERSION
                } // namespace std
                
                #endif /* _STL_CONSTRUCT_H */
                


Top 10 Lines:

     Line      Count

      112  655625534
      122  655625534
      148  655625534

Execution Summary:

        7   Executable lines in this file
        7   Lines executed
   100.00   Percent of the file executed

1966876602   Total number of line executions
280982371.71   Average executions per line


*** File /usr/include/c++/4.8.2/bits/stl_iterator_base_types.h:
                // Types used in iterator implementation -*- C++ -*-
                
                // Copyright (C) 2001-2013 Free Software Foundation, Inc.
                //
                // This file is part of the GNU ISO C++ Library.  This library is free
                // software; you can redistribute it and/or modify it under the
                // terms of the GNU General Public License as published by the
                // Free Software Foundation; either version 3, or (at your option)
                // any later version.
                
                // This library is distributed in the hope that it will be useful,
                // but WITHOUT ANY WARRANTY; without even the implied warranty of
                // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
                // GNU General Public License for more details.
                
                // Under Section 7 of GPL version 3, you are granted additional
                // permissions described in the GCC Runtime Library Exception, version
                // 3.1, as published by the Free Software Foundation.
                
                // You should have received a copy of the GNU General Public License and
                // a copy of the GCC Runtime Library Exception along with this program;
                // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
                // <http://www.gnu.org/licenses/>.
                
                /*
                 *
                 * Copyright (c) 1994
                 * Hewlett-Packard Company
                 *
                 * Permission to use, copy, modify, distribute and sell this software
                 * and its documentation for any purpose is hereby granted without fee,
                 * provided that the above copyright notice appear in all copies and
                 * that both that copyright notice and this permission notice appear
                 * in supporting documentation.  Hewlett-Packard Company makes no
                 * representations about the suitability of this software for any
                 * purpose.  It is provided "as is" without express or implied warranty.
                 *
                 *
                 * Copyright (c) 1996-1998
                 * Silicon Graphics Computer Systems, Inc.
                 *
                 * Permission to use, copy, modify, distribute and sell this software
                 * and its documentation for any purpose is hereby granted without fee,
                 * provided that the above copyright notice appear in all copies and
                 * that both that copyright notice and this permission notice appear
                 * in supporting documentation.  Silicon Graphics makes no
                 * representations about the suitability of this software for any
                 * purpose.  It is provided "as is" without express or implied warranty.
                 */
                
                /** @file bits/stl_iterator_base_types.h
                 *  This is an internal header file, included by other library headers.
                 *  Do not attempt to use it directly. @headername{iterator}
                 *
                 *  This file contains all of the general iterator-related utility types,
                 *  such as iterator_traits and struct iterator.
                 */
                
                #ifndef _STL_ITERATOR_BASE_TYPES_H
                #define _STL_ITERATOR_BASE_TYPES_H 1
                
                #pragma GCC system_header
                
                #include <bits/c++config.h>
                
                #if __cplusplus >= 201103L
                # include <type_traits>  // For _GLIBCXX_HAS_NESTED_TYPE, is_convertible
                #endif
                
                namespace std _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                  /**
                   *  @defgroup iterators Iterators
                   *  Abstractions for uniform iterating through various underlying types.
                  */
                  //@{ 
                
                  /**
                   *  @defgroup iterator_tags Iterator Tags
                   *  These are empty types, used to distinguish different iterators.  The
                   *  distinction is not made by what they contain, but simply by what they
                   *  are.  Different underlying algorithms can then be used based on the
                   *  different operations supported by different iterator types.
                  */
                  //@{ 
                  ///  Marking input iterators.
                  struct input_iterator_tag { };
                
                  ///  Marking output iterators.
                  struct output_iterator_tag { };
                
                  /// Forward iterators support a superset of input iterator operations.
                  struct forward_iterator_tag : public input_iterator_tag { };
                
                  /// Bidirectional iterators support a superset of forward iterator
                  /// operations.
                  struct bidirectional_iterator_tag : public forward_iterator_tag { };
                
                  /// Random-access iterators support a superset of bidirectional
                  /// iterator operations.
                  struct random_access_iterator_tag : public bidirectional_iterator_tag { };
                  //@}
                
                  /**
                   *  @brief  Common %iterator class.
                   *
                   *  This class does nothing but define nested typedefs.  %Iterator classes
                   *  can inherit from this class to save some work.  The typedefs are then
                   *  used in specializations and overloading.
                   *
                   *  In particular, there are no default implementations of requirements
                   *  such as @c operator++ and the like.  (How could there be?)
                  */
                  template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
                           typename _Pointer = _Tp*, typename _Reference = _Tp&>
                    struct iterator
                    {
                      /// One of the @link iterator_tags tag types@endlink.
                      typedef _Category  iterator_category;
                      /// The type "pointed to" by the iterator.
                      typedef _Tp        value_type;
                      /// Distance between iterators is represented as this type.
                      typedef _Distance  difference_type;
                      /// This type represents a pointer-to-value_type.
                      typedef _Pointer   pointer;
                      /// This type represents a reference-to-value_type.
                      typedef _Reference reference;
                    };
                
                  /**
                   *  @brief  Traits class for iterators.
                   *
                   *  This class does nothing but define nested typedefs.  The general
                   *  version simply @a forwards the nested typedefs from the Iterator
                   *  argument.  Specialized versions for pointers and pointers-to-const
                   *  provide tighter, more correct semantics.
                  */
                #if __cplusplus >= 201103L
                
                _GLIBCXX_HAS_NESTED_TYPE(iterator_category)
                
                  template<typename _Iterator,
                	   bool = __has_iterator_category<_Iterator>::value>
                    struct __iterator_traits { };
                
                  template<typename _Iterator>
                    struct __iterator_traits<_Iterator, true>
                    {
                      typedef typename _Iterator::iterator_category iterator_category;
                      typedef typename _Iterator::value_type        value_type;
                      typedef typename _Iterator::difference_type   difference_type;
                      typedef typename _Iterator::pointer           pointer;
                      typedef typename _Iterator::reference         reference;
                    };
                
                  template<typename _Iterator>
                    struct iterator_traits
                    : public __iterator_traits<_Iterator> { };
                #else
                  template<typename _Iterator>
                    struct iterator_traits
                    {
                      typedef typename _Iterator::iterator_category iterator_category;
                      typedef typename _Iterator::value_type        value_type;
                      typedef typename _Iterator::difference_type   difference_type;
                      typedef typename _Iterator::pointer           pointer;
                      typedef typename _Iterator::reference         reference;
                    };
                #endif
                
                  /// Partial specialization for pointer types.
                  template<typename _Tp>
                    struct iterator_traits<_Tp*>
                    {
                      typedef random_access_iterator_tag iterator_category;
                      typedef _Tp                         value_type;
                      typedef ptrdiff_t                   difference_type;
                      typedef _Tp*                        pointer;
                      typedef _Tp&                        reference;
                    };
                
                  /// Partial specialization for const pointer types.
                  template<typename _Tp>
                    struct iterator_traits<const _Tp*>
                    {
                      typedef random_access_iterator_tag iterator_category;
                      typedef _Tp                         value_type;
                      typedef ptrdiff_t                   difference_type;
                      typedef const _Tp*                  pointer;
                      typedef const _Tp&                  reference;
                    };
                
                  /**
                   *  This function is not a part of the C++ standard but is syntactic
                   *  sugar for internal library use only.
                  */
                  template<typename _Iter>
                    inline typename iterator_traits<_Iter>::iterator_category
    26080000 ->     __iterator_category(const _Iter&)
    26080000 ->     { return typename iterator_traits<_Iter>::iterator_category(); }
                
                  //@}
                
                  // If _Iterator has a base returns it otherwise _Iterator is returned
                  // untouched
                  template<typename _Iterator, bool _HasBase>
                    struct _Iter_base
                    {
                      typedef _Iterator iterator_type;
    14399820 ->       static iterator_type _S_base(_Iterator __it)
    14399820 ->       { return __it; }
                    };
                
                  template<typename _Iterator>
                    struct _Iter_base<_Iterator, true>
                    {
                      typedef typename _Iterator::iterator_type iterator_type;
       ##### ->       static iterator_type _S_base(_Iterator __it)
       ##### ->       { return __it.base(); }
                    };
                
                #if __cplusplus >= 201103L
                  template<typename _InIter>
                    using _RequireInputIter = typename
                      enable_if<is_convertible<typename
                		iterator_traits<_InIter>::iterator_category,
                			       input_iterator_tag>::value>::type;
                #endif
                
                _GLIBCXX_END_NAMESPACE_VERSION
                } // namespace
                
                #endif /* _STL_ITERATOR_BASE_TYPES_H */
                


Top 10 Lines:

     Line      Count

      201   26080000
      212   14399820

Execution Summary:

        6   Executable lines in this file
        6   Lines executed
   100.00   Percent of the file executed

 40479820   Total number of line executions
6746636.67   Average executions per line


*** File /usr/include/c++/4.8.2/bits/allocator.h:
                // Allocators -*- C++ -*-
                
                // Copyright (C) 2001-2013 Free Software Foundation, Inc.
                //
                // This file is part of the GNU ISO C++ Library.  This library is free
                // software; you can redistribute it and/or modify it under the
                // terms of the GNU General Public License as published by the
                // Free Software Foundation; either version 3, or (at your option)
                // any later version.
                
                // This library is distributed in the hope that it will be useful,
                // but WITHOUT ANY WARRANTY; without even the implied warranty of
                // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
                // GNU General Public License for more details.
                
                // Under Section 7 of GPL version 3, you are granted additional
                // permissions described in the GCC Runtime Library Exception, version
                // 3.1, as published by the Free Software Foundation.
                
                // You should have received a copy of the GNU General Public License and
                // a copy of the GCC Runtime Library Exception along with this program;
                // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
                // <http://www.gnu.org/licenses/>.
                
                /*
                 * Copyright (c) 1996-1997
                 * Silicon Graphics Computer Systems, Inc.
                 *
                 * Permission to use, copy, modify, distribute and sell this software
                 * and its documentation for any purpose is hereby granted without fee,
                 * provided that the above copyright notice appear in all copies and
                 * that both that copyright notice and this permission notice appear
                 * in supporting documentation.  Silicon Graphics makes no
                 * representations about the suitability of this software for any
                 * purpose.  It is provided "as is" without express or implied warranty.
                 */
                
                /** @file bits/allocator.h
                 *  This is an internal header file, included by other library headers.
                 *  Do not attempt to use it directly. @headername{memory}
                 */
                
                #ifndef _ALLOCATOR_H
                #define _ALLOCATOR_H 1
                
                #include <bits/c++allocator.h> // Define the base class to std::allocator.
                #include <bits/memoryfwd.h>
                #if __cplusplus >= 201103L
                #include <type_traits>
                #endif
                
                namespace std _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                  /**
                   *  @addtogroup allocators
                   *  @{
                   */
                
                  /// allocator<void> specialization.
                  template<>
                    class allocator<void>
                    {
                    public:
                      typedef size_t      size_type;
                      typedef ptrdiff_t   difference_type;
                      typedef void*       pointer;
                      typedef const void* const_pointer;
                      typedef void        value_type;
                
                      template<typename _Tp1>
                        struct rebind
                        { typedef allocator<_Tp1> other; };
                
                #if __cplusplus >= 201103L
                      // _GLIBCXX_RESOLVE_LIB_DEFECTS
                      // 2103. std::allocator propagate_on_container_move_assignment
                      typedef true_type propagate_on_container_move_assignment;
                #endif
                    };
                
                  /**
                   * @brief  The @a standard allocator, as per [20.4].
                   *
                   *  See http://gcc.gnu.org/onlinedocs/libstdc++/manual/bk01pt04ch11.html
                   *  for further details.
                   *
                   *  @tparam  _Tp  Type of allocated object.
                   */
                  template<typename _Tp>
                    class allocator: public __allocator_base<_Tp>
                    {
                   public:
                      typedef size_t     size_type;
                      typedef ptrdiff_t  difference_type;
                      typedef _Tp*       pointer;
                      typedef const _Tp* const_pointer;
                      typedef _Tp&       reference;
                      typedef const _Tp& const_reference;
                      typedef _Tp        value_type;
                
                      template<typename _Tp1>
                        struct rebind
                        { typedef allocator<_Tp1> other; };
                
                #if __cplusplus >= 201103L
                      // _GLIBCXX_RESOLVE_LIB_DEFECTS
                      // 2103. std::allocator propagate_on_container_move_assignment
                      typedef true_type propagate_on_container_move_assignment;
                #endif
                
      160000 ->       allocator() throw() { }
                
                      allocator(const allocator& __a) throw()
                      : __allocator_base<_Tp>(__a) { }
                
                      template<typename _Tp1>
                        allocator(const allocator<_Tp1>&) throw() { }
                
       ##### ->       ~allocator() throw() { }
                
                      // Inherit everything else.
                    };
                
                  template<typename _T1, typename _T2>
                    inline bool
                    operator==(const allocator<_T1>&, const allocator<_T2>&)
                    { return true; }
                
                  template<typename _Tp>
                    inline bool
                    operator==(const allocator<_Tp>&, const allocator<_Tp>&)
                    { return true; }
                
                  template<typename _T1, typename _T2>
                    inline bool
                    operator!=(const allocator<_T1>&, const allocator<_T2>&)
                    { return false; }
                
                  template<typename _Tp>
                    inline bool
                    operator!=(const allocator<_Tp>&, const allocator<_Tp>&)
                    { return false; }
                
                  /// @} group allocator
                
                  // Inhibit implicit instantiations for required instantiations,
                  // which are defined via explicit instantiations elsewhere.
                #if _GLIBCXX_EXTERN_TEMPLATE
                  extern template class allocator<char>;
                  extern template class allocator<wchar_t>;
                #endif
                
                  // Undefine.
                #undef __allocator_base
                
                  // To implement Option 3 of DR 431.
                  template<typename _Alloc, bool = __is_empty(_Alloc)>
                    struct __alloc_swap
                    { static void _S_do_it(_Alloc&, _Alloc&) { } };
                
                  template<typename _Alloc>
                    struct __alloc_swap<_Alloc, false>
                    {
                      static void
                      _S_do_it(_Alloc& __one, _Alloc& __two)
                      {
                	// Precondition: swappable allocators.
                	if (__one != __two)
                	  swap(__one, __two);
                      }
                    };
                
                  // Optimize for stateless allocators.
                  template<typename _Alloc, bool = __is_empty(_Alloc)>
                    struct __alloc_neq
                    {
                      static bool
                      _S_do_it(const _Alloc&, const _Alloc&)
                      { return false; }
                    };
                
                  template<typename _Alloc>
                    struct __alloc_neq<_Alloc, false>
                    {
                      static bool
                      _S_do_it(const _Alloc& __one, const _Alloc& __two)
                      { return __one != __two; }
                    };
                
                #if __cplusplus >= 201103L
                  template<typename _Tp, bool
                    = __or_<is_copy_constructible<typename _Tp::value_type>,
                            is_nothrow_move_constructible<typename _Tp::value_type>>::value>
                    struct __shrink_to_fit_aux
                    { static bool _S_do_it(_Tp&) { return false; } };
                
                  template<typename _Tp>
                    struct __shrink_to_fit_aux<_Tp, true>
                    {
                      static bool
                      _S_do_it(_Tp& __c)
                      {
                	__try
                	  {
                	    _Tp(__make_move_if_noexcept_iterator(__c.begin()),
                		__make_move_if_noexcept_iterator(__c.end()),
                		__c.get_allocator()).swap(__c);
                	    return true;
                	  }
                	__catch(...)
                	  { return false; }
                      }
                    };
                #endif
                
                _GLIBCXX_END_NAMESPACE_VERSION
                } // namespace std
                
                #endif


Top 10 Lines:

     Line      Count

      113     160000

Execution Summary:

        2   Executable lines in this file
        2   Lines executed
   100.00   Percent of the file executed

   160000   Total number of line executions
 80000.00   Average executions per line


*** File /usr/include/c++/4.8.2/bits/stl_algo.h:
                // Algorithm implementation -*- C++ -*-
                
                // Copyright (C) 2001-2013 Free Software Foundation, Inc.
                //
                // This file is part of the GNU ISO C++ Library.  This library is free
                // software; you can redistribute it and/or modify it under the
                // terms of the GNU General Public License as published by the
                // Free Software Foundation; either version 3, or (at your option)
                // any later version.
                
                // This library is distributed in the hope that it will be useful,
                // but WITHOUT ANY WARRANTY; without even the implied warranty of
                // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
                // GNU General Public License for more details.
                
                // Under Section 7 of GPL version 3, you are granted additional
                // permissions described in the GCC Runtime Library Exception, version
                // 3.1, as published by the Free Software Foundation.
                
                // You should have received a copy of the GNU General Public License and
                // a copy of the GCC Runtime Library Exception along with this program;
                // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
                // <http://www.gnu.org/licenses/>.
                
                /*
                 *
                 * Copyright (c) 1994
                 * Hewlett-Packard Company
                 *
                 * Permission to use, copy, modify, distribute and sell this software
                 * and its documentation for any purpose is hereby granted without fee,
                 * provided that the above copyright notice appear in all copies and
                 * that both that copyright notice and this permission notice appear
                 * in supporting documentation.  Hewlett-Packard Company makes no
                 * representations about the suitability of this software for any
                 * purpose.  It is provided "as is" without express or implied warranty.
                 *
                 *
                 * Copyright (c) 1996
                 * Silicon Graphics Computer Systems, Inc.
                 *
                 * Permission to use, copy, modify, distribute and sell this software
                 * and its documentation for any purpose is hereby granted without fee,
                 * provided that the above copyright notice appear in all copies and
                 * that both that copyright notice and this permission notice appear
                 * in supporting documentation.  Silicon Graphics makes no
                 * representations about the suitability of this software for any
                 * purpose.  It is provided "as is" without express or implied warranty.
                 */
                
                /** @file bits/stl_algo.h
                 *  This is an internal header file, included by other library headers.
                 *  Do not attempt to use it directly. @headername{algorithm}
                 */
                
                #ifndef _STL_ALGO_H
                #define _STL_ALGO_H 1
                
                #include <cstdlib>             // for rand
                #include <bits/algorithmfwd.h>
                #include <bits/stl_heap.h>
                #include <bits/stl_tempbuf.h>  // for _Temporary_buffer
                
                #if __cplusplus >= 201103L
                #include <random>     // for std::uniform_int_distribution
                #include <functional> // for std::bind
                #endif
                
                // See concept_check.h for the __glibcxx_*_requires macros.
                
                namespace std _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                  /// Swaps the median value of *__a, *__b and *__c to *__result
                  template<typename _Iterator>
                    void
                    __move_median_to_first(_Iterator __result, _Iterator __a,
                			   _Iterator __b, _Iterator __c)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_LessThanComparableConcept<
                	    typename iterator_traits<_Iterator>::value_type>)
                
                      if (*__a < *__b)
                	{
                	  if (*__b < *__c)
                	    std::iter_swap(__result, __b);
                	  else if (*__a < *__c)
                	    std::iter_swap(__result, __c);
                	  else
                	    std::iter_swap(__result, __a);
                	}
                      else if (*__a < *__c)
                      	std::iter_swap(__result, __a);
                      else if (*__b < *__c)
                	std::iter_swap(__result, __c);
                      else
                	std::iter_swap(__result, __b);
                    }
                
                  /// Swaps the median value of *__a, *__b and *__c under __comp to *__result
                  template<typename _Iterator, typename _Compare>
                    void
                    __move_median_to_first(_Iterator __result, _Iterator __a,
                			   _Iterator __b, _Iterator __c,
                			   _Compare __comp)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_BinaryFunctionConcept<_Compare, bool,
                	    typename iterator_traits<_Iterator>::value_type,
                	    typename iterator_traits<_Iterator>::value_type>)
                
                      if (__comp(*__a, *__b))
                	{
                	  if (__comp(*__b, *__c))
                	    std::iter_swap(__result, __b);
                	  else if (__comp(*__a, *__c))
                	    std::iter_swap(__result, __c);
                	  else
                	    std::iter_swap(__result, __a);
                	}
                      else if (__comp(*__a, *__c))
                	std::iter_swap(__result, __a);
                      else if (__comp(*__b, *__c))
                	std::iter_swap(__result, __c);
                      else
                	std::iter_swap(__result, __b);
                    }
                
                  // for_each
                
                  /// This is an overload used by find() for the Input Iterator case.
                  template<typename _InputIterator, typename _Tp>
                    inline _InputIterator
                    __find(_InputIterator __first, _InputIterator __last,
                	   const _Tp& __val, input_iterator_tag)
                    {
                      while (__first != __last && !(*__first == __val))
                	++__first;
                      return __first;
                    }
                
                  /// This is an overload used by find_if() for the Input Iterator case.
                  template<typename _InputIterator, typename _Predicate>
                    inline _InputIterator
                    __find_if(_InputIterator __first, _InputIterator __last,
                	      _Predicate __pred, input_iterator_tag)
                    {
                      while (__first != __last && !bool(__pred(*__first)))
                	++__first;
                      return __first;
                    }
                
                  /// This is an overload used by find() for the RAI case.
                  template<typename _RandomAccessIterator, typename _Tp>
                    _RandomAccessIterator
    26080000 ->     __find(_RandomAccessIterator __first, _RandomAccessIterator __last,
                	   const _Tp& __val, random_access_iterator_tag)
                    {
                      typename iterator_traits<_RandomAccessIterator>::difference_type
    26080000 -> 	__trip_count = (__last - __first) >> 2;
                
    26080000 ->       for (; __trip_count > 0; --__trip_count)
                	{
    26080000 -> 	  if (*__first == __val)
    26080000 -> 	    return __first;
    26080000 -> 	  ++__first;
                
    26080000 -> 	  if (*__first == __val)
    26080000 -> 	    return __first;
    26080000 -> 	  ++__first;
                
    26080000 -> 	  if (*__first == __val)
    26080000 -> 	    return __first;
    26080000 -> 	  ++__first;
                
    26080000 -> 	  if (*__first == __val)
    26080000 -> 	    return __first;
    26080000 -> 	  ++__first;
                	}
                
    26080000 ->       switch (__last - __first)
                	{
                	case 3:
    26080000 -> 	  if (*__first == __val)
    26080000 -> 	    return __first;
    26080000 -> 	  ++__first;
                	case 2:
    26080000 -> 	  if (*__first == __val)
    26080000 -> 	    return __first;
    26080000 -> 	  ++__first;
                	case 1:
    26080000 -> 	  if (*__first == __val)
    26080000 -> 	    return __first;
    26080000 -> 	  ++__first;
                	case 0:
                	default:
    26080000 -> 	  return __last;
                	}
    26080000 ->     }
                
                  /// This is an overload used by find_if() for the RAI case.
                  template<typename _RandomAccessIterator, typename _Predicate>
                    _RandomAccessIterator
                    __find_if(_RandomAccessIterator __first, _RandomAccessIterator __last,
                	      _Predicate __pred, random_access_iterator_tag)
                    {
                      typename iterator_traits<_RandomAccessIterator>::difference_type
                	__trip_count = (__last - __first) >> 2;
                
                      for (; __trip_count > 0; --__trip_count)
                	{
                	  if (__pred(*__first))
                	    return __first;
                	  ++__first;
                
                	  if (__pred(*__first))
                	    return __first;
                	  ++__first;
                
                	  if (__pred(*__first))
                	    return __first;
                	  ++__first;
                
                	  if (__pred(*__first))
                	    return __first;
                	  ++__first;
                	}
                
                      switch (__last - __first)
                	{
                	case 3:
                	  if (__pred(*__first))
                	    return __first;
                	  ++__first;
                	case 2:
                	  if (__pred(*__first))
                	    return __first;
                	  ++__first;
                	case 1:
                	  if (__pred(*__first))
                	    return __first;
                	  ++__first;
                	case 0:
                	default:
                	  return __last;
                	}
                    }
                
                  /// This is an overload used by find_if_not() for the Input Iterator case.
                  template<typename _InputIterator, typename _Predicate>
                    inline _InputIterator
                    __find_if_not(_InputIterator __first, _InputIterator __last,
                		  _Predicate __pred, input_iterator_tag)
                    {
                      while (__first != __last && bool(__pred(*__first)))
                	++__first;
                      return __first;
                    }
                
                  /// This is an overload used by find_if_not() for the RAI case.
                  template<typename _RandomAccessIterator, typename _Predicate>
                    _RandomAccessIterator
                    __find_if_not(_RandomAccessIterator __first, _RandomAccessIterator __last,
                		  _Predicate __pred, random_access_iterator_tag)
                    {
                      typename iterator_traits<_RandomAccessIterator>::difference_type
                	__trip_count = (__last - __first) >> 2;
                
                      for (; __trip_count > 0; --__trip_count)
                	{
                	  if (!bool(__pred(*__first)))
                	    return __first;
                	  ++__first;
                
                	  if (!bool(__pred(*__first)))
                	    return __first;
                	  ++__first;
                
                	  if (!bool(__pred(*__first)))
                	    return __first;
                	  ++__first;
                
                	  if (!bool(__pred(*__first)))
                	    return __first;
                	  ++__first;
                	}
                
                      switch (__last - __first)
                	{
                	case 3:
                	  if (!bool(__pred(*__first)))
                	    return __first;
                	  ++__first;
                	case 2:
                	  if (!bool(__pred(*__first)))
                	    return __first;
                	  ++__first;
                	case 1:
                	  if (!bool(__pred(*__first)))
                	    return __first;
                	  ++__first;
                	case 0:
                	default:
                	  return __last;
                	}
                    }
                
                  /// Provided for stable_partition to use.
                  template<typename _InputIterator, typename _Predicate>
                    inline _InputIterator
                    __find_if_not(_InputIterator __first, _InputIterator __last,
                		  _Predicate __pred)
                    {
                      return std::__find_if_not(__first, __last, __pred,
                				std::__iterator_category(__first));
                    }
                
                  /// Like find_if_not(), but uses and updates a count of the
                  /// remaining range length instead of comparing against an end
                  /// iterator.
                  template<typename _InputIterator, typename _Predicate, typename _Distance>
                    _InputIterator
                    __find_if_not_n(_InputIterator __first, _Distance& __len, _Predicate __pred)
                    {
                      for (; __len; --__len, ++__first)
                	if (!bool(__pred(*__first)))
                	  break;
                      return __first;
                    }
                
                  // set_difference
                  // set_intersection
                  // set_symmetric_difference
                  // set_union
                  // for_each
                  // find
                  // find_if
                  // find_first_of
                  // adjacent_find
                  // count
                  // count_if
                  // search
                
                  /**
                   *  This is an uglified
                   *  search_n(_ForwardIterator, _ForwardIterator, _Integer, const _Tp&)
                   *  overloaded for forward iterators.
                  */
                  template<typename _ForwardIterator, typename _Integer, typename _Tp>
                    _ForwardIterator
                    __search_n(_ForwardIterator __first, _ForwardIterator __last,
                	       _Integer __count, const _Tp& __val,
                	       std::forward_iterator_tag)
                    {
                      __first = _GLIBCXX_STD_A::find(__first, __last, __val);
                      while (__first != __last)
                	{
                	  typename iterator_traits<_ForwardIterator>::difference_type
                	    __n = __count;
                	  _ForwardIterator __i = __first;
                	  ++__i;
                	  while (__i != __last && __n != 1 && *__i == __val)
                	    {
                	      ++__i;
                	      --__n;
                	    }
                	  if (__n == 1)
                	    return __first;
                	  if (__i == __last)
                	    return __last;
                	  __first = _GLIBCXX_STD_A::find(++__i, __last, __val);
                	}
                      return __last;
                    }
                
                  /**
                   *  This is an uglified
                   *  search_n(_ForwardIterator, _ForwardIterator, _Integer, const _Tp&)
                   *  overloaded for random access iterators.
                  */
                  template<typename _RandomAccessIter, typename _Integer, typename _Tp>
                    _RandomAccessIter
                    __search_n(_RandomAccessIter __first, _RandomAccessIter __last,
                	       _Integer __count, const _Tp& __val, 
                	       std::random_access_iterator_tag)
                    {
                      
                      typedef typename std::iterator_traits<_RandomAccessIter>::difference_type
                	_DistanceType;
                
                      _DistanceType __tailSize = __last - __first;
                      _DistanceType __remainder = __count;
                
                      while (__remainder <= __tailSize) // the main loop...
                	{
                	  __first += __remainder;
                	  __tailSize -= __remainder;
                	  // __first here is always pointing to one past the last element of
                	  // next possible match.
                	  _RandomAccessIter __backTrack = __first; 
                	  while (*--__backTrack == __val)
                	    {
                	      if (--__remainder == 0)
                	        return (__first - __count); // Success
                	    }
                	  __remainder = __count + 1 - (__first - __backTrack);
                	}
                      return __last; // Failure
                    }
                
                  // search_n
                
                  /**
                   *  This is an uglified
                   *  search_n(_ForwardIterator, _ForwardIterator, _Integer, const _Tp&,
                   *	       _BinaryPredicate)
                   *  overloaded for forward iterators.
                  */
                  template<typename _ForwardIterator, typename _Integer, typename _Tp,
                           typename _BinaryPredicate>
                    _ForwardIterator
                    __search_n(_ForwardIterator __first, _ForwardIterator __last,
                	       _Integer __count, const _Tp& __val,
                	       _BinaryPredicate __binary_pred, std::forward_iterator_tag)
                    {
                      while (__first != __last && !bool(__binary_pred(*__first, __val)))
                        ++__first;
                
                      while (__first != __last)
                	{
                	  typename iterator_traits<_ForwardIterator>::difference_type
                	    __n = __count;
                	  _ForwardIterator __i = __first;
                	  ++__i;
                	  while (__i != __last && __n != 1 && bool(__binary_pred(*__i, __val)))
                	    {
                	      ++__i;
                	      --__n;
                	    }
                	  if (__n == 1)
                	    return __first;
                	  if (__i == __last)
                	    return __last;
                	  __first = ++__i;
                	  while (__first != __last
                		 && !bool(__binary_pred(*__first, __val)))
                	    ++__first;
                	}
                      return __last;
                    }
                
                  /**
                   *  This is an uglified
                   *  search_n(_ForwardIterator, _ForwardIterator, _Integer, const _Tp&,
                   *	       _BinaryPredicate)
                   *  overloaded for random access iterators.
                  */
                  template<typename _RandomAccessIter, typename _Integer, typename _Tp,
                	   typename _BinaryPredicate>
                    _RandomAccessIter
                    __search_n(_RandomAccessIter __first, _RandomAccessIter __last,
                	       _Integer __count, const _Tp& __val,
                	       _BinaryPredicate __binary_pred, std::random_access_iterator_tag)
                    {
                      
                      typedef typename std::iterator_traits<_RandomAccessIter>::difference_type
                	_DistanceType;
                
                      _DistanceType __tailSize = __last - __first;
                      _DistanceType __remainder = __count;
                
                      while (__remainder <= __tailSize) // the main loop...
                	{
                	  __first += __remainder;
                	  __tailSize -= __remainder;
                	  // __first here is always pointing to one past the last element of
                	  // next possible match.
                	  _RandomAccessIter __backTrack = __first; 
                	  while (__binary_pred(*--__backTrack, __val))
                	    {
                	      if (--__remainder == 0)
                	        return (__first - __count); // Success
                	    }
                	  __remainder = __count + 1 - (__first - __backTrack);
                	}
                      return __last; // Failure
                    }
                
                  // find_end for forward iterators.
                  template<typename _ForwardIterator1, typename _ForwardIterator2>
                    _ForwardIterator1
                    __find_end(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                	       _ForwardIterator2 __first2, _ForwardIterator2 __last2,
                	       forward_iterator_tag, forward_iterator_tag)
                    {
                      if (__first2 == __last2)
                	return __last1;
                      else
                	{
                	  _ForwardIterator1 __result = __last1;
                	  while (1)
                	    {
                	      _ForwardIterator1 __new_result
                		= _GLIBCXX_STD_A::search(__first1, __last1, __first2, __last2);
                	      if (__new_result == __last1)
                		return __result;
                	      else
                		{
                		  __result = __new_result;
                		  __first1 = __new_result;
                		  ++__first1;
                		}
                	    }
                	}
                    }
                
                  template<typename _ForwardIterator1, typename _ForwardIterator2,
                	   typename _BinaryPredicate>
                    _ForwardIterator1
                    __find_end(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                	       _ForwardIterator2 __first2, _ForwardIterator2 __last2,
                	       forward_iterator_tag, forward_iterator_tag,
                	       _BinaryPredicate __comp)
                    {
                      if (__first2 == __last2)
                	return __last1;
                      else
                	{
                	  _ForwardIterator1 __result = __last1;
                	  while (1)
                	    {
                	      _ForwardIterator1 __new_result
                		= _GLIBCXX_STD_A::search(__first1, __last1, __first2,
                					 __last2, __comp);
                	      if (__new_result == __last1)
                		return __result;
                	      else
                		{
                		  __result = __new_result;
                		  __first1 = __new_result;
                		  ++__first1;
                		}
                	    }
                	}
                    }
                
                  // find_end for bidirectional iterators (much faster).
                  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2>
                    _BidirectionalIterator1
                    __find_end(_BidirectionalIterator1 __first1,
                	       _BidirectionalIterator1 __last1,
                	       _BidirectionalIterator2 __first2,
                	       _BidirectionalIterator2 __last2,
                	       bidirectional_iterator_tag, bidirectional_iterator_tag)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_BidirectionalIteratorConcept<
                				  _BidirectionalIterator1>)
                      __glibcxx_function_requires(_BidirectionalIteratorConcept<
                				  _BidirectionalIterator2>)
                
                      typedef reverse_iterator<_BidirectionalIterator1> _RevIterator1;
                      typedef reverse_iterator<_BidirectionalIterator2> _RevIterator2;
                
                      _RevIterator1 __rlast1(__first1);
                      _RevIterator2 __rlast2(__first2);
                      _RevIterator1 __rresult = _GLIBCXX_STD_A::search(_RevIterator1(__last1),
                						       __rlast1,
                						       _RevIterator2(__last2),
                						       __rlast2);
                
                      if (__rresult == __rlast1)
                	return __last1;
                      else
                	{
                	  _BidirectionalIterator1 __result = __rresult.base();
                	  std::advance(__result, -std::distance(__first2, __last2));
                	  return __result;
                	}
                    }
                
                  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2,
                	   typename _BinaryPredicate>
                    _BidirectionalIterator1
                    __find_end(_BidirectionalIterator1 __first1,
                	       _BidirectionalIterator1 __last1,
                	       _BidirectionalIterator2 __first2,
                	       _BidirectionalIterator2 __last2,
                	       bidirectional_iterator_tag, bidirectional_iterator_tag,
                	       _BinaryPredicate __comp)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_BidirectionalIteratorConcept<
                				  _BidirectionalIterator1>)
                      __glibcxx_function_requires(_BidirectionalIteratorConcept<
                				  _BidirectionalIterator2>)
                
                      typedef reverse_iterator<_BidirectionalIterator1> _RevIterator1;
                      typedef reverse_iterator<_BidirectionalIterator2> _RevIterator2;
                
                      _RevIterator1 __rlast1(__first1);
                      _RevIterator2 __rlast2(__first2);
                      _RevIterator1 __rresult = std::search(_RevIterator1(__last1), __rlast1,
                					    _RevIterator2(__last2), __rlast2,
                					    __comp);
                
                      if (__rresult == __rlast1)
                	return __last1;
                      else
                	{
                	  _BidirectionalIterator1 __result = __rresult.base();
                	  std::advance(__result, -std::distance(__first2, __last2));
                	  return __result;
                	}
                    }
                
                  /**
                   *  @brief  Find last matching subsequence in a sequence.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first1  Start of range to search.
                   *  @param  __last1   End of range to search.
                   *  @param  __first2  Start of sequence to match.
                   *  @param  __last2   End of sequence to match.
                   *  @return   The last iterator @c i in the range
                   *  @p [__first1,__last1-(__last2-__first2)) such that @c *(i+N) ==
                   *  @p *(__first2+N) for each @c N in the range @p
                   *  [0,__last2-__first2), or @p __last1 if no such iterator exists.
                   *
                   *  Searches the range @p [__first1,__last1) for a sub-sequence that
                   *  compares equal value-by-value with the sequence given by @p
                   *  [__first2,__last2) and returns an iterator to the __first
                   *  element of the sub-sequence, or @p __last1 if the sub-sequence
                   *  is not found.  The sub-sequence will be the last such
                   *  subsequence contained in [__first,__last1).
                   *
                   *  Because the sub-sequence must lie completely within the range @p
                   *  [__first1,__last1) it must start at a position less than @p
                   *  __last1-(__last2-__first2) where @p __last2-__first2 is the
                   *  length of the sub-sequence.  This means that the returned
                   *  iterator @c i will be in the range @p
                   *  [__first1,__last1-(__last2-__first2))
                  */
                  template<typename _ForwardIterator1, typename _ForwardIterator2>
                    inline _ForwardIterator1
                    find_end(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                	     _ForwardIterator2 __first2, _ForwardIterator2 __last2)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator1>)
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator2>)
                      __glibcxx_function_requires(_EqualOpConcept<
                	    typename iterator_traits<_ForwardIterator1>::value_type,
                	    typename iterator_traits<_ForwardIterator2>::value_type>)
                      __glibcxx_requires_valid_range(__first1, __last1);
                      __glibcxx_requires_valid_range(__first2, __last2);
                
                      return std::__find_end(__first1, __last1, __first2, __last2,
                			     std::__iterator_category(__first1),
                			     std::__iterator_category(__first2));
                    }
                
                  /**
                   *  @brief  Find last matching subsequence in a sequence using a predicate.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first1  Start of range to search.
                   *  @param  __last1   End of range to search.
                   *  @param  __first2  Start of sequence to match.
                   *  @param  __last2   End of sequence to match.
                   *  @param  __comp    The predicate to use.
                   *  @return The last iterator @c i in the range @p
                   *  [__first1,__last1-(__last2-__first2)) such that @c
                   *  predicate(*(i+N), @p (__first2+N)) is true for each @c N in the
                   *  range @p [0,__last2-__first2), or @p __last1 if no such iterator
                   *  exists.
                   *
                   *  Searches the range @p [__first1,__last1) for a sub-sequence that
                   *  compares equal value-by-value with the sequence given by @p
                   *  [__first2,__last2) using comp as a predicate and returns an
                   *  iterator to the first element of the sub-sequence, or @p __last1
                   *  if the sub-sequence is not found.  The sub-sequence will be the
                   *  last such subsequence contained in [__first,__last1).
                   *
                   *  Because the sub-sequence must lie completely within the range @p
                   *  [__first1,__last1) it must start at a position less than @p
                   *  __last1-(__last2-__first2) where @p __last2-__first2 is the
                   *  length of the sub-sequence.  This means that the returned
                   *  iterator @c i will be in the range @p
                   *  [__first1,__last1-(__last2-__first2))
                  */
                  template<typename _ForwardIterator1, typename _ForwardIterator2,
                	   typename _BinaryPredicate>
                    inline _ForwardIterator1
                    find_end(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                	     _ForwardIterator2 __first2, _ForwardIterator2 __last2,
                	     _BinaryPredicate __comp)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator1>)
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator2>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_BinaryPredicate,
                	    typename iterator_traits<_ForwardIterator1>::value_type,
                	    typename iterator_traits<_ForwardIterator2>::value_type>)
                      __glibcxx_requires_valid_range(__first1, __last1);
                      __glibcxx_requires_valid_range(__first2, __last2);
                
                      return std::__find_end(__first1, __last1, __first2, __last2,
                			     std::__iterator_category(__first1),
                			     std::__iterator_category(__first2),
                			     __comp);
                    }
                
                #if __cplusplus >= 201103L
                  /**
                   *  @brief  Checks that a predicate is true for all the elements
                   *          of a sequence.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first   An input iterator.
                   *  @param  __last    An input iterator.
                   *  @param  __pred    A predicate.
                   *  @return  True if the check is true, false otherwise.
                   *
                   *  Returns true if @p __pred is true for each element in the range
                   *  @p [__first,__last), and false otherwise.
                  */
                  template<typename _InputIterator, typename _Predicate>
                    inline bool
                    all_of(_InputIterator __first, _InputIterator __last, _Predicate __pred)
                    { return __last == std::find_if_not(__first, __last, __pred); }
                
                  /**
                   *  @brief  Checks that a predicate is false for all the elements
                   *          of a sequence.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first   An input iterator.
                   *  @param  __last    An input iterator.
                   *  @param  __pred    A predicate.
                   *  @return  True if the check is true, false otherwise.
                   *
                   *  Returns true if @p __pred is false for each element in the range
                   *  @p [__first,__last), and false otherwise.
                  */
                  template<typename _InputIterator, typename _Predicate>
                    inline bool
                    none_of(_InputIterator __first, _InputIterator __last, _Predicate __pred)
                    { return __last == _GLIBCXX_STD_A::find_if(__first, __last, __pred); }
                
                  /**
                   *  @brief  Checks that a predicate is false for at least an element
                   *          of a sequence.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first   An input iterator.
                   *  @param  __last    An input iterator.
                   *  @param  __pred    A predicate.
                   *  @return  True if the check is true, false otherwise.
                   *
                   *  Returns true if an element exists in the range @p
                   *  [__first,__last) such that @p __pred is true, and false
                   *  otherwise.
                  */
                  template<typename _InputIterator, typename _Predicate>
                    inline bool
                    any_of(_InputIterator __first, _InputIterator __last, _Predicate __pred)
                    { return !std::none_of(__first, __last, __pred); }
                
                  /**
                   *  @brief  Find the first element in a sequence for which a
                   *          predicate is false.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first  An input iterator.
                   *  @param  __last   An input iterator.
                   *  @param  __pred   A predicate.
                   *  @return   The first iterator @c i in the range @p [__first,__last)
                   *  such that @p __pred(*i) is false, or @p __last if no such iterator exists.
                  */
                  template<typename _InputIterator, typename _Predicate>
                    inline _InputIterator
                    find_if_not(_InputIterator __first, _InputIterator __last,
                		_Predicate __pred)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_UnaryPredicateConcept<_Predicate,
                	      typename iterator_traits<_InputIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                      return std::__find_if_not(__first, __last, __pred);
                    }
                
                  /**
                   *  @brief  Checks whether the sequence is partitioned.
                   *  @ingroup mutating_algorithms
                   *  @param  __first  An input iterator.
                   *  @param  __last   An input iterator.
                   *  @param  __pred   A predicate.
                   *  @return  True if the range @p [__first,__last) is partioned by @p __pred,
                   *  i.e. if all elements that satisfy @p __pred appear before those that
                   *  do not.
                  */
                  template<typename _InputIterator, typename _Predicate>
                    inline bool
                    is_partitioned(_InputIterator __first, _InputIterator __last,
                		   _Predicate __pred)
                    {
                      __first = std::find_if_not(__first, __last, __pred);
                      return std::none_of(__first, __last, __pred);
                    }
                
                  /**
                   *  @brief  Find the partition point of a partitioned range.
                   *  @ingroup mutating_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @param  __pred    A predicate.
                   *  @return  An iterator @p mid such that @p all_of(__first, mid, __pred)
                   *           and @p none_of(mid, __last, __pred) are both true.
                  */
                  template<typename _ForwardIterator, typename _Predicate>
                    _ForwardIterator
                    partition_point(_ForwardIterator __first, _ForwardIterator __last,
                		    _Predicate __pred)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_UnaryPredicateConcept<_Predicate,
                	      typename iterator_traits<_ForwardIterator>::value_type>)
                
                      // A specific debug-mode test will be necessary...
                      __glibcxx_requires_valid_range(__first, __last);
                
                      typedef typename iterator_traits<_ForwardIterator>::difference_type
                	_DistanceType;
                
                      _DistanceType __len = std::distance(__first, __last);
                      _DistanceType __half;
                      _ForwardIterator __middle;
                
                      while (__len > 0)
                	{
                	  __half = __len >> 1;
                	  __middle = __first;
                	  std::advance(__middle, __half);
                	  if (__pred(*__middle))
                	    {
                	      __first = __middle;
                	      ++__first;
                	      __len = __len - __half - 1;
                	    }
                	  else
                	    __len = __half;
                	}
                      return __first;
                    }
                #endif
                
                
                  /**
                   *  @brief Copy a sequence, removing elements of a given value.
                   *  @ingroup mutating_algorithms
                   *  @param  __first   An input iterator.
                   *  @param  __last    An input iterator.
                   *  @param  __result  An output iterator.
                   *  @param  __value   The value to be removed.
                   *  @return   An iterator designating the end of the resulting sequence.
                   *
                   *  Copies each element in the range @p [__first,__last) not equal
                   *  to @p __value to the range beginning at @p __result.
                   *  remove_copy() is stable, so the relative order of elements that
                   *  are copied is unchanged.
                  */
                  template<typename _InputIterator, typename _OutputIterator, typename _Tp>
                    _OutputIterator
                    remove_copy(_InputIterator __first, _InputIterator __last,
                		_OutputIterator __result, const _Tp& __value)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                	    typename iterator_traits<_InputIterator>::value_type>)
                      __glibcxx_function_requires(_EqualOpConcept<
                	    typename iterator_traits<_InputIterator>::value_type, _Tp>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      for (; __first != __last; ++__first)
                	if (!(*__first == __value))
                	  {
                	    *__result = *__first;
                	    ++__result;
                	  }
                      return __result;
                    }
                
                  /**
                   *  @brief Copy a sequence, removing elements for which a predicate is true.
                   *  @ingroup mutating_algorithms
                   *  @param  __first   An input iterator.
                   *  @param  __last    An input iterator.
                   *  @param  __result  An output iterator.
                   *  @param  __pred    A predicate.
                   *  @return   An iterator designating the end of the resulting sequence.
                   *
                   *  Copies each element in the range @p [__first,__last) for which
                   *  @p __pred returns false to the range beginning at @p __result.
                   *
                   *  remove_copy_if() is stable, so the relative order of elements that are
                   *  copied is unchanged.
                  */
                  template<typename _InputIterator, typename _OutputIterator,
                	   typename _Predicate>
                    _OutputIterator
                    remove_copy_if(_InputIterator __first, _InputIterator __last,
                		   _OutputIterator __result, _Predicate __pred)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                	    typename iterator_traits<_InputIterator>::value_type>)
                      __glibcxx_function_requires(_UnaryPredicateConcept<_Predicate,
                	    typename iterator_traits<_InputIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      for (; __first != __last; ++__first)
                	if (!bool(__pred(*__first)))
                	  {
                	    *__result = *__first;
                	    ++__result;
                	  }
                      return __result;
                    }
                
                #if __cplusplus >= 201103L
                  /**
                   *  @brief Copy the elements of a sequence for which a predicate is true.
                   *  @ingroup mutating_algorithms
                   *  @param  __first   An input iterator.
                   *  @param  __last    An input iterator.
                   *  @param  __result  An output iterator.
                   *  @param  __pred    A predicate.
                   *  @return   An iterator designating the end of the resulting sequence.
                   *
                   *  Copies each element in the range @p [__first,__last) for which
                   *  @p __pred returns true to the range beginning at @p __result.
                   *
                   *  copy_if() is stable, so the relative order of elements that are
                   *  copied is unchanged.
                  */
                  template<typename _InputIterator, typename _OutputIterator,
                	   typename _Predicate>
                    _OutputIterator
                    copy_if(_InputIterator __first, _InputIterator __last,
                	    _OutputIterator __result, _Predicate __pred)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                	    typename iterator_traits<_InputIterator>::value_type>)
                      __glibcxx_function_requires(_UnaryPredicateConcept<_Predicate,
                	    typename iterator_traits<_InputIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      for (; __first != __last; ++__first)
                	if (__pred(*__first))
                	  {
                	    *__result = *__first;
                	    ++__result;
                	  }
                      return __result;
                    }
                
                
                  template<typename _InputIterator, typename _Size, typename _OutputIterator>
                    _OutputIterator
                    __copy_n(_InputIterator __first, _Size __n,
                	     _OutputIterator __result, input_iterator_tag)
                    {
                      if (__n > 0)
                	{
                	  while (true)
                	    {
                	      *__result = *__first;
                	      ++__result;
                	      if (--__n > 0)
                		++__first;
                	      else
                		break;
                	    }
                	}
                      return __result;
                    }
                
                  template<typename _RandomAccessIterator, typename _Size,
                	   typename _OutputIterator>
                    inline _OutputIterator
                    __copy_n(_RandomAccessIterator __first, _Size __n,
                	     _OutputIterator __result, random_access_iterator_tag)
                    { return std::copy(__first, __first + __n, __result); }
                
                  /**
                   *  @brief Copies the range [first,first+n) into [result,result+n).
                   *  @ingroup mutating_algorithms
                   *  @param  __first  An input iterator.
                   *  @param  __n      The number of elements to copy.
                   *  @param  __result An output iterator.
                   *  @return  result+n.
                   *
                   *  This inline function will boil down to a call to @c memmove whenever
                   *  possible.  Failing that, if random access iterators are passed, then the
                   *  loop count will be known (and therefore a candidate for compiler
                   *  optimizations such as unrolling).
                  */
                  template<typename _InputIterator, typename _Size, typename _OutputIterator>
                    inline _OutputIterator
                    copy_n(_InputIterator __first, _Size __n, _OutputIterator __result)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                	    typename iterator_traits<_InputIterator>::value_type>)
                
                      return std::__copy_n(__first, __n, __result,
                			   std::__iterator_category(__first));
                    }
                
                  /**
                   *  @brief Copy the elements of a sequence to separate output sequences
                   *         depending on the truth value of a predicate.
                   *  @ingroup mutating_algorithms
                   *  @param  __first   An input iterator.
                   *  @param  __last    An input iterator.
                   *  @param  __out_true   An output iterator.
                   *  @param  __out_false  An output iterator.
                   *  @param  __pred    A predicate.
                   *  @return   A pair designating the ends of the resulting sequences.
                   *
                   *  Copies each element in the range @p [__first,__last) for which
                   *  @p __pred returns true to the range beginning at @p out_true
                   *  and each element for which @p __pred returns false to @p __out_false.
                  */
                  template<typename _InputIterator, typename _OutputIterator1,
                	   typename _OutputIterator2, typename _Predicate>
                    pair<_OutputIterator1, _OutputIterator2>
                    partition_copy(_InputIterator __first, _InputIterator __last,
                		   _OutputIterator1 __out_true, _OutputIterator2 __out_false,
                		   _Predicate __pred)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator1,
                	    typename iterator_traits<_InputIterator>::value_type>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator2,
                	    typename iterator_traits<_InputIterator>::value_type>)
                      __glibcxx_function_requires(_UnaryPredicateConcept<_Predicate,
                	    typename iterator_traits<_InputIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                      
                      for (; __first != __last; ++__first)
                	if (__pred(*__first))
                	  {
                	    *__out_true = *__first;
                	    ++__out_true;
                	  }
                	else
                	  {
                	    *__out_false = *__first;
                	    ++__out_false;
                	  }
                
                      return pair<_OutputIterator1, _OutputIterator2>(__out_true, __out_false);
                    }
                #endif
                
                  /**
                   *  @brief Remove elements from a sequence.
                   *  @ingroup mutating_algorithms
                   *  @param  __first  An input iterator.
                   *  @param  __last   An input iterator.
                   *  @param  __value  The value to be removed.
                   *  @return   An iterator designating the end of the resulting sequence.
                   *
                   *  All elements equal to @p __value are removed from the range
                   *  @p [__first,__last).
                   *
                   *  remove() is stable, so the relative order of elements that are
                   *  not removed is unchanged.
                   *
                   *  Elements between the end of the resulting sequence and @p __last
                   *  are still present, but their value is unspecified.
                  */
                  template<typename _ForwardIterator, typename _Tp>
                    _ForwardIterator
    26080000 ->     remove(_ForwardIterator __first, _ForwardIterator __last,
                	   const _Tp& __value)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<
                				  _ForwardIterator>)
                      __glibcxx_function_requires(_EqualOpConcept<
                	    typename iterator_traits<_ForwardIterator>::value_type, _Tp>)
                      __glibcxx_requires_valid_range(__first, __last);
                
    26080000 ->       __first = _GLIBCXX_STD_A::find(__first, __last, __value);
    26080000 ->       if(__first == __last)
    26080000 ->         return __first;
    26080000 ->       _ForwardIterator __result = __first;
    26080000 ->       ++__first;
    26080000 ->       for(; __first != __last; ++__first)
    26080000 ->         if(!(*__first == __value))
                          {
    26080000 ->             *__result = _GLIBCXX_MOVE(*__first);
    26080000 ->             ++__result;
                          }
    26080000 ->       return __result;
    26080000 ->     }
                
                  /**
                   *  @brief Remove elements from a sequence using a predicate.
                   *  @ingroup mutating_algorithms
                   *  @param  __first  A forward iterator.
                   *  @param  __last   A forward iterator.
                   *  @param  __pred   A predicate.
                   *  @return   An iterator designating the end of the resulting sequence.
                   *
                   *  All elements for which @p __pred returns true are removed from the range
                   *  @p [__first,__last).
                   *
                   *  remove_if() is stable, so the relative order of elements that are
                   *  not removed is unchanged.
                   *
                   *  Elements between the end of the resulting sequence and @p __last
                   *  are still present, but their value is unspecified.
                  */
                  template<typename _ForwardIterator, typename _Predicate>
                    _ForwardIterator
                    remove_if(_ForwardIterator __first, _ForwardIterator __last,
                	      _Predicate __pred)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<
                				  _ForwardIterator>)
                      __glibcxx_function_requires(_UnaryPredicateConcept<_Predicate,
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      __first = _GLIBCXX_STD_A::find_if(__first, __last, __pred);
                      if(__first == __last)
                        return __first;
                      _ForwardIterator __result = __first;
                      ++__first;
                      for(; __first != __last; ++__first)
                        if(!bool(__pred(*__first)))
                          {
                            *__result = _GLIBCXX_MOVE(*__first);
                            ++__result;
                          }
                      return __result;
                    }
                
                  /**
                   *  @brief Remove consecutive duplicate values from a sequence.
                   *  @ingroup mutating_algorithms
                   *  @param  __first  A forward iterator.
                   *  @param  __last   A forward iterator.
                   *  @return  An iterator designating the end of the resulting sequence.
                   *
                   *  Removes all but the first element from each group of consecutive
                   *  values that compare equal.
                   *  unique() is stable, so the relative order of elements that are
                   *  not removed is unchanged.
                   *  Elements between the end of the resulting sequence and @p __last
                   *  are still present, but their value is unspecified.
                  */
                  template<typename _ForwardIterator>
                    _ForwardIterator
                    unique(_ForwardIterator __first, _ForwardIterator __last)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<
                				  _ForwardIterator>)
                      __glibcxx_function_requires(_EqualityComparableConcept<
                		     typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      // Skip the beginning, if already unique.
                      __first = _GLIBCXX_STD_A::adjacent_find(__first, __last);
                      if (__first == __last)
                	return __last;
                
                      // Do the real copy work.
                      _ForwardIterator __dest = __first;
                      ++__first;
                      while (++__first != __last)
                	if (!(*__dest == *__first))
                	  *++__dest = _GLIBCXX_MOVE(*__first);
                      return ++__dest;
                    }
                
                  /**
                   *  @brief Remove consecutive values from a sequence using a predicate.
                   *  @ingroup mutating_algorithms
                   *  @param  __first        A forward iterator.
                   *  @param  __last         A forward iterator.
                   *  @param  __binary_pred  A binary predicate.
                   *  @return  An iterator designating the end of the resulting sequence.
                   *
                   *  Removes all but the first element from each group of consecutive
                   *  values for which @p __binary_pred returns true.
                   *  unique() is stable, so the relative order of elements that are
                   *  not removed is unchanged.
                   *  Elements between the end of the resulting sequence and @p __last
                   *  are still present, but their value is unspecified.
                  */
                  template<typename _ForwardIterator, typename _BinaryPredicate>
                    _ForwardIterator
                    unique(_ForwardIterator __first, _ForwardIterator __last,
                           _BinaryPredicate __binary_pred)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<
                				  _ForwardIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_BinaryPredicate,
                		typename iterator_traits<_ForwardIterator>::value_type,
                		typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      // Skip the beginning, if already unique.
                      __first = _GLIBCXX_STD_A::adjacent_find(__first, __last, __binary_pred);
                      if (__first == __last)
                	return __last;
                
                      // Do the real copy work.
                      _ForwardIterator __dest = __first;
                      ++__first;
                      while (++__first != __last)
                	if (!bool(__binary_pred(*__dest, *__first)))
                	  *++__dest = _GLIBCXX_MOVE(*__first);
                      return ++__dest;
                    }
                
                  /**
                   *  This is an uglified unique_copy(_InputIterator, _InputIterator,
                   *                                  _OutputIterator)
                   *  overloaded for forward iterators and output iterator as result.
                  */
                  template<typename _ForwardIterator, typename _OutputIterator>
                    _OutputIterator
                    __unique_copy(_ForwardIterator __first, _ForwardIterator __last,
                		  _OutputIterator __result,
                		  forward_iterator_tag, output_iterator_tag)
                    {
                      // concept requirements -- taken care of in dispatching function
                      _ForwardIterator __next = __first;
                      *__result = *__first;
                      while (++__next != __last)
                	if (!(*__first == *__next))
                	  {
                	    __first = __next;
                	    *++__result = *__first;
                	  }
                      return ++__result;
                    }
                
                  /**
                   *  This is an uglified unique_copy(_InputIterator, _InputIterator,
                   *                                  _OutputIterator)
                   *  overloaded for input iterators and output iterator as result.
                  */
                  template<typename _InputIterator, typename _OutputIterator>
                    _OutputIterator
                    __unique_copy(_InputIterator __first, _InputIterator __last,
                		  _OutputIterator __result,
                		  input_iterator_tag, output_iterator_tag)
                    {
                      // concept requirements -- taken care of in dispatching function
                      typename iterator_traits<_InputIterator>::value_type __value = *__first;
                      *__result = __value;
                      while (++__first != __last)
                	if (!(__value == *__first))
                	  {
                	    __value = *__first;
                	    *++__result = __value;
                	  }
                      return ++__result;
                    }
                
                  /**
                   *  This is an uglified unique_copy(_InputIterator, _InputIterator,
                   *                                  _OutputIterator)
                   *  overloaded for input iterators and forward iterator as result.
                  */
                  template<typename _InputIterator, typename _ForwardIterator>
                    _ForwardIterator
                    __unique_copy(_InputIterator __first, _InputIterator __last,
                		  _ForwardIterator __result,
                		  input_iterator_tag, forward_iterator_tag)
                    {
                      // concept requirements -- taken care of in dispatching function
                      *__result = *__first;
                      while (++__first != __last)
                	if (!(*__result == *__first))
                	  *++__result = *__first;
                      return ++__result;
                    }
                
                  /**
                   *  This is an uglified
                   *  unique_copy(_InputIterator, _InputIterator, _OutputIterator,
                   *              _BinaryPredicate)
                   *  overloaded for forward iterators and output iterator as result.
                  */
                  template<typename _ForwardIterator, typename _OutputIterator,
                	   typename _BinaryPredicate>
                    _OutputIterator
                    __unique_copy(_ForwardIterator __first, _ForwardIterator __last,
                		  _OutputIterator __result, _BinaryPredicate __binary_pred,
                		  forward_iterator_tag, output_iterator_tag)
                    {
                      // concept requirements -- iterators already checked
                      __glibcxx_function_requires(_BinaryPredicateConcept<_BinaryPredicate,
                	  typename iterator_traits<_ForwardIterator>::value_type,
                	  typename iterator_traits<_ForwardIterator>::value_type>)
                
                      _ForwardIterator __next = __first;
                      *__result = *__first;
                      while (++__next != __last)
                	if (!bool(__binary_pred(*__first, *__next)))
                	  {
                	    __first = __next;
                	    *++__result = *__first;
                	  }
                      return ++__result;
                    }
                
                  /**
                   *  This is an uglified
                   *  unique_copy(_InputIterator, _InputIterator, _OutputIterator,
                   *              _BinaryPredicate)
                   *  overloaded for input iterators and output iterator as result.
                  */
                  template<typename _InputIterator, typename _OutputIterator,
                	   typename _BinaryPredicate>
                    _OutputIterator
                    __unique_copy(_InputIterator __first, _InputIterator __last,
                		  _OutputIterator __result, _BinaryPredicate __binary_pred,
                		  input_iterator_tag, output_iterator_tag)
                    {
                      // concept requirements -- iterators already checked
                      __glibcxx_function_requires(_BinaryPredicateConcept<_BinaryPredicate,
                	  typename iterator_traits<_InputIterator>::value_type,
                	  typename iterator_traits<_InputIterator>::value_type>)
                
                      typename iterator_traits<_InputIterator>::value_type __value = *__first;
                      *__result = __value;
                      while (++__first != __last)
                	if (!bool(__binary_pred(__value, *__first)))
                	  {
                	    __value = *__first;
                	    *++__result = __value;
                	  }
                      return ++__result;
                    }
                
                  /**
                   *  This is an uglified
                   *  unique_copy(_InputIterator, _InputIterator, _OutputIterator,
                   *              _BinaryPredicate)
                   *  overloaded for input iterators and forward iterator as result.
                  */
                  template<typename _InputIterator, typename _ForwardIterator,
                	   typename _BinaryPredicate>
                    _ForwardIterator
                    __unique_copy(_InputIterator __first, _InputIterator __last,
                		  _ForwardIterator __result, _BinaryPredicate __binary_pred,
                		  input_iterator_tag, forward_iterator_tag)
                    {
                      // concept requirements -- iterators already checked
                      __glibcxx_function_requires(_BinaryPredicateConcept<_BinaryPredicate,
                	  typename iterator_traits<_ForwardIterator>::value_type,
                	  typename iterator_traits<_InputIterator>::value_type>)
                
                      *__result = *__first;
                      while (++__first != __last)
                	if (!bool(__binary_pred(*__result, *__first)))
                	  *++__result = *__first;
                      return ++__result;
                    }
                
                  /**
                   *  This is an uglified reverse(_BidirectionalIterator,
                   *                              _BidirectionalIterator)
                   *  overloaded for bidirectional iterators.
                  */
                  template<typename _BidirectionalIterator>
                    void
                    __reverse(_BidirectionalIterator __first, _BidirectionalIterator __last,
                	      bidirectional_iterator_tag)
                    {
                      while (true)
                	if (__first == __last || __first == --__last)
                	  return;
                	else
                	  {
                	    std::iter_swap(__first, __last);
                	    ++__first;
                	  }
                    }
                
                  /**
                   *  This is an uglified reverse(_BidirectionalIterator,
                   *                              _BidirectionalIterator)
                   *  overloaded for random access iterators.
                  */
                  template<typename _RandomAccessIterator>
                    void
                    __reverse(_RandomAccessIterator __first, _RandomAccessIterator __last,
                	      random_access_iterator_tag)
                    {
                      if (__first == __last)
                	return;
                      --__last;
                      while (__first < __last)
                	{
                	  std::iter_swap(__first, __last);
                	  ++__first;
                	  --__last;
                	}
                    }
                
                  /**
                   *  @brief Reverse a sequence.
                   *  @ingroup mutating_algorithms
                   *  @param  __first  A bidirectional iterator.
                   *  @param  __last   A bidirectional iterator.
                   *  @return   reverse() returns no value.
                   *
                   *  Reverses the order of the elements in the range @p [__first,__last),
                   *  so that the first element becomes the last etc.
                   *  For every @c i such that @p 0<=i<=(__last-__first)/2), @p reverse()
                   *  swaps @p *(__first+i) and @p *(__last-(i+1))
                  */
                  template<typename _BidirectionalIterator>
                    inline void
                    reverse(_BidirectionalIterator __first, _BidirectionalIterator __last)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_BidirectionalIteratorConcept<
                				  _BidirectionalIterator>)
                      __glibcxx_requires_valid_range(__first, __last);
                      std::__reverse(__first, __last, std::__iterator_category(__first));
                    }
                
                  /**
                   *  @brief Copy a sequence, reversing its elements.
                   *  @ingroup mutating_algorithms
                   *  @param  __first   A bidirectional iterator.
                   *  @param  __last    A bidirectional iterator.
                   *  @param  __result  An output iterator.
                   *  @return  An iterator designating the end of the resulting sequence.
                   *
                   *  Copies the elements in the range @p [__first,__last) to the
                   *  range @p [__result,__result+(__last-__first)) such that the
                   *  order of the elements is reversed.  For every @c i such that @p
                   *  0<=i<=(__last-__first), @p reverse_copy() performs the
                   *  assignment @p *(__result+(__last-__first)-1-i) = *(__first+i).
                   *  The ranges @p [__first,__last) and @p
                   *  [__result,__result+(__last-__first)) must not overlap.
                  */
                  template<typename _BidirectionalIterator, typename _OutputIterator>
                    _OutputIterator
                    reverse_copy(_BidirectionalIterator __first, _BidirectionalIterator __last,
                		 _OutputIterator __result)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_BidirectionalIteratorConcept<
                				  _BidirectionalIterator>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                		typename iterator_traits<_BidirectionalIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      while (__first != __last)
                	{
                	  --__last;
                	  *__result = *__last;
                	  ++__result;
                	}
                      return __result;
                    }
                
                  /**
                   *  This is a helper function for the rotate algorithm specialized on RAIs.
                   *  It returns the greatest common divisor of two integer values.
                  */
                  template<typename _EuclideanRingElement>
                    _EuclideanRingElement
                    __gcd(_EuclideanRingElement __m, _EuclideanRingElement __n)
                    {
                      while (__n != 0)
                	{
                	  _EuclideanRingElement __t = __m % __n;
                	  __m = __n;
                	  __n = __t;
                	}
                      return __m;
                    }
                
                  /// This is a helper function for the rotate algorithm.
                  template<typename _ForwardIterator>
                    void
                    __rotate(_ForwardIterator __first,
                	     _ForwardIterator __middle,
                	     _ForwardIterator __last,
                	     forward_iterator_tag)
                    {
                      if (__first == __middle || __last  == __middle)
                	return;
                
                      _ForwardIterator __first2 = __middle;
                      do
                	{
                	  std::iter_swap(__first, __first2);
                	  ++__first;
                	  ++__first2;
                	  if (__first == __middle)
                	    __middle = __first2;
                	}
                      while (__first2 != __last);
                
                      __first2 = __middle;
                
                      while (__first2 != __last)
                	{
                	  std::iter_swap(__first, __first2);
                	  ++__first;
                	  ++__first2;
                	  if (__first == __middle)
                	    __middle = __first2;
                	  else if (__first2 == __last)
                	    __first2 = __middle;
                	}
                    }
                
                   /// This is a helper function for the rotate algorithm.
                  template<typename _BidirectionalIterator>
                    void
                    __rotate(_BidirectionalIterator __first,
                	     _BidirectionalIterator __middle,
                	     _BidirectionalIterator __last,
                	      bidirectional_iterator_tag)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_BidirectionalIteratorConcept<
                				  _BidirectionalIterator>)
                
                      if (__first == __middle || __last  == __middle)
                	return;
                
                      std::__reverse(__first,  __middle, bidirectional_iterator_tag());
                      std::__reverse(__middle, __last,   bidirectional_iterator_tag());
                
                      while (__first != __middle && __middle != __last)
                	{
                	  std::iter_swap(__first, --__last);
                	  ++__first;
                	}
                
                      if (__first == __middle)
                	std::__reverse(__middle, __last,   bidirectional_iterator_tag());
                      else
                	std::__reverse(__first,  __middle, bidirectional_iterator_tag());
                    }
                
                  /// This is a helper function for the rotate algorithm.
                  template<typename _RandomAccessIterator>
                    void
                    __rotate(_RandomAccessIterator __first,
                	     _RandomAccessIterator __middle,
                	     _RandomAccessIterator __last,
                	     random_access_iterator_tag)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_RandomAccessIteratorConcept<
                				  _RandomAccessIterator>)
                
                      if (__first == __middle || __last  == __middle)
                	return;
                
                      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
                	_Distance;
                      typedef typename iterator_traits<_RandomAccessIterator>::value_type
                	_ValueType;
                
                      _Distance __n = __last   - __first;
                      _Distance __k = __middle - __first;
                
                      if (__k == __n - __k)
                	{
                	  std::swap_ranges(__first, __middle, __middle);
                	  return;
                	}
                
                      _RandomAccessIterator __p = __first;
                
                      for (;;)
                	{
                	  if (__k < __n - __k)
                	    {
                	      if (__is_pod(_ValueType) && __k == 1)
                		{
                		  _ValueType __t = _GLIBCXX_MOVE(*__p);
                		  _GLIBCXX_MOVE3(__p + 1, __p + __n, __p);
                		  *(__p + __n - 1) = _GLIBCXX_MOVE(__t);
                		  return;
                		}
                	      _RandomAccessIterator __q = __p + __k;
                	      for (_Distance __i = 0; __i < __n - __k; ++ __i)
                		{
                		  std::iter_swap(__p, __q);
                		  ++__p;
                		  ++__q;
                		}
                	      __n %= __k;
                	      if (__n == 0)
                		return;
                	      std::swap(__n, __k);
                	      __k = __n - __k;
                	    }
                	  else
                	    {
                	      __k = __n - __k;
                	      if (__is_pod(_ValueType) && __k == 1)
                		{
                		  _ValueType __t = _GLIBCXX_MOVE(*(__p + __n - 1));
                		  _GLIBCXX_MOVE_BACKWARD3(__p, __p + __n - 1, __p + __n);
                		  *__p = _GLIBCXX_MOVE(__t);
                		  return;
                		}
                	      _RandomAccessIterator __q = __p + __n;
                	      __p = __q - __k;
                	      for (_Distance __i = 0; __i < __n - __k; ++ __i)
                		{
                		  --__p;
                		  --__q;
                		  std::iter_swap(__p, __q);
                		}
                	      __n %= __k;
                	      if (__n == 0)
                		return;
                	      std::swap(__n, __k);
                	    }
                	}
                    }
                
                  /**
                   *  @brief Rotate the elements of a sequence.
                   *  @ingroup mutating_algorithms
                   *  @param  __first   A forward iterator.
                   *  @param  __middle  A forward iterator.
                   *  @param  __last    A forward iterator.
                   *  @return  Nothing.
                   *
                   *  Rotates the elements of the range @p [__first,__last) by 
                   *  @p (__middle - __first) positions so that the element at @p __middle
                   *  is moved to @p __first, the element at @p __middle+1 is moved to
                   *  @p __first+1 and so on for each element in the range
                   *  @p [__first,__last).
                   *
                   *  This effectively swaps the ranges @p [__first,__middle) and
                   *  @p [__middle,__last).
                   *
                   *  Performs
                   *   @p *(__first+(n+(__last-__middle))%(__last-__first))=*(__first+n)
                   *  for each @p n in the range @p [0,__last-__first).
                  */
                  template<typename _ForwardIterator>
                    inline void
                    rotate(_ForwardIterator __first, _ForwardIterator __middle,
                	   _ForwardIterator __last)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<
                				  _ForwardIterator>)
                      __glibcxx_requires_valid_range(__first, __middle);
                      __glibcxx_requires_valid_range(__middle, __last);
                
                      typedef typename iterator_traits<_ForwardIterator>::iterator_category
                	_IterType;
                      std::__rotate(__first, __middle, __last, _IterType());
                    }
                
                  /**
                   *  @brief Copy a sequence, rotating its elements.
                   *  @ingroup mutating_algorithms
                   *  @param  __first   A forward iterator.
                   *  @param  __middle  A forward iterator.
                   *  @param  __last    A forward iterator.
                   *  @param  __result  An output iterator.
                   *  @return   An iterator designating the end of the resulting sequence.
                   *
                   *  Copies the elements of the range @p [__first,__last) to the
                   *  range beginning at @result, rotating the copied elements by 
                   *  @p (__middle-__first) positions so that the element at @p __middle
                   *  is moved to @p __result, the element at @p __middle+1 is moved
                   *  to @p __result+1 and so on for each element in the range @p
                   *  [__first,__last).
                   *
                   *  Performs 
                   *  @p *(__result+(n+(__last-__middle))%(__last-__first))=*(__first+n)
                   *  for each @p n in the range @p [0,__last-__first).
                  */
                  template<typename _ForwardIterator, typename _OutputIterator>
                    _OutputIterator
                    rotate_copy(_ForwardIterator __first, _ForwardIterator __middle,
                                _ForwardIterator __last, _OutputIterator __result)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                		typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __middle);
                      __glibcxx_requires_valid_range(__middle, __last);
                
                      return std::copy(__first, __middle,
                                       std::copy(__middle, __last, __result));
                    }
                
                  /// This is a helper function...
                  template<typename _ForwardIterator, typename _Predicate>
                    _ForwardIterator
                    __partition(_ForwardIterator __first, _ForwardIterator __last,
                		_Predicate __pred, forward_iterator_tag)
                    {
                      if (__first == __last)
                	return __first;
                
                      while (__pred(*__first))
                	if (++__first == __last)
                	  return __first;
                
                      _ForwardIterator __next = __first;
                
                      while (++__next != __last)
                	if (__pred(*__next))
                	  {
                	    std::iter_swap(__first, __next);
                	    ++__first;
                	  }
                
                      return __first;
                    }
                
                  /// This is a helper function...
                  template<typename _BidirectionalIterator, typename _Predicate>
                    _BidirectionalIterator
                    __partition(_BidirectionalIterator __first, _BidirectionalIterator __last,
                		_Predicate __pred, bidirectional_iterator_tag)
                    {
                      while (true)
                	{
                	  while (true)
                	    if (__first == __last)
                	      return __first;
                	    else if (__pred(*__first))
                	      ++__first;
                	    else
                	      break;
                	  --__last;
                	  while (true)
                	    if (__first == __last)
                	      return __first;
                	    else if (!bool(__pred(*__last)))
                	      --__last;
                	    else
                	      break;
                	  std::iter_swap(__first, __last);
                	  ++__first;
                	}
                    }
                
                  // partition
                
                  /// This is a helper function...
                  /// Requires __len != 0 and !__pred(*__first),
                  /// same as __stable_partition_adaptive.
                  template<typename _ForwardIterator, typename _Predicate, typename _Distance>
                    _ForwardIterator
                    __inplace_stable_partition(_ForwardIterator __first,
                			       _Predicate __pred, _Distance __len)
                    {
                      if (__len == 1)
                	return __first;
                      _ForwardIterator __middle = __first;
                      std::advance(__middle, __len / 2);
                      _ForwardIterator __left_split =
                	std::__inplace_stable_partition(__first, __pred, __len / 2);
                      // Advance past true-predicate values to satisfy this
                      // function's preconditions.
                      _Distance __right_len = __len - __len / 2;
                      _ForwardIterator __right_split =
                	std::__find_if_not_n(__middle, __right_len, __pred);
                      if (__right_len)
                	__right_split = std::__inplace_stable_partition(__middle,
                							__pred,
                							__right_len);
                      std::rotate(__left_split, __middle, __right_split);
                      std::advance(__left_split, std::distance(__middle, __right_split));
                      return __left_split;
                    }
                
                  /// This is a helper function...
                  /// Requires __first != __last and !__pred(*__first)
                  /// and __len == distance(__first, __last).
                  ///
                  /// !__pred(*__first) allows us to guarantee that we don't
                  /// move-assign an element onto itself.
                  template<typename _ForwardIterator, typename _Pointer, typename _Predicate,
                	   typename _Distance>
                    _ForwardIterator
                    __stable_partition_adaptive(_ForwardIterator __first,
                				_ForwardIterator __last,
                				_Predicate __pred, _Distance __len,
                				_Pointer __buffer,
                				_Distance __buffer_size)
                    {
                      if (__len <= __buffer_size)
                	{
                	  _ForwardIterator __result1 = __first;
                	  _Pointer __result2 = __buffer;
                	  // The precondition guarantees that !__pred(*__first), so
                	  // move that element to the buffer before starting the loop.
                	  // This ensures that we only call __pred once per element.
                	  *__result2 = _GLIBCXX_MOVE(*__first);
                	  ++__result2;
                	  ++__first;
                	  for (; __first != __last; ++__first)
                	    if (__pred(*__first))
                	      {
                		*__result1 = _GLIBCXX_MOVE(*__first);
                		++__result1;
                	      }
                	    else
                	      {
                		*__result2 = _GLIBCXX_MOVE(*__first);
                		++__result2;
                	      }
                	  _GLIBCXX_MOVE3(__buffer, __result2, __result1);
                	  return __result1;
                	}
                      else
                	{
                	  _ForwardIterator __middle = __first;
                	  std::advance(__middle, __len / 2);
                	  _ForwardIterator __left_split =
                	    std::__stable_partition_adaptive(__first, __middle, __pred,
                					     __len / 2, __buffer,
                					     __buffer_size);
                	  // Advance past true-predicate values to satisfy this
                	  // function's preconditions.
                	  _Distance __right_len = __len - __len / 2;
                	  _ForwardIterator __right_split =
                	    std::__find_if_not_n(__middle, __right_len, __pred);
                	  if (__right_len)
                	    __right_split =
                	      std::__stable_partition_adaptive(__right_split, __last, __pred,
                					       __right_len,
                					       __buffer, __buffer_size);
                	  std::rotate(__left_split, __middle, __right_split);
                	  std::advance(__left_split, std::distance(__middle, __right_split));
                	  return __left_split;
                	}
                    }
                
                  /**
                   *  @brief Move elements for which a predicate is true to the beginning
                   *         of a sequence, preserving relative ordering.
                   *  @ingroup mutating_algorithms
                   *  @param  __first   A forward iterator.
                   *  @param  __last    A forward iterator.
                   *  @param  __pred    A predicate functor.
                   *  @return  An iterator @p middle such that @p __pred(i) is true for each
                   *  iterator @p i in the range @p [first,middle) and false for each @p i
                   *  in the range @p [middle,last).
                   *
                   *  Performs the same function as @p partition() with the additional
                   *  guarantee that the relative ordering of elements in each group is
                   *  preserved, so any two elements @p x and @p y in the range
                   *  @p [__first,__last) such that @p __pred(x)==__pred(y) will have the same
                   *  relative ordering after calling @p stable_partition().
                  */
                  template<typename _ForwardIterator, typename _Predicate>
                    _ForwardIterator
                    stable_partition(_ForwardIterator __first, _ForwardIterator __last,
                		     _Predicate __pred)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<
                				  _ForwardIterator>)
                      __glibcxx_function_requires(_UnaryPredicateConcept<_Predicate,
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      __first = std::__find_if_not(__first, __last, __pred);
                
                      if (__first == __last)
                	return __first;
                      else
                	{
                	  typedef typename iterator_traits<_ForwardIterator>::value_type
                	    _ValueType;
                	  typedef typename iterator_traits<_ForwardIterator>::difference_type
                	    _DistanceType;
                
                	  _Temporary_buffer<_ForwardIterator, _ValueType> __buf(__first,
                								__last);
                	if (__buf.size() > 0)
                	  return
                	    std::__stable_partition_adaptive(__first, __last, __pred,
                					  _DistanceType(__buf.requested_size()),
                					  __buf.begin(),
                					  _DistanceType(__buf.size()));
                	else
                	  return
                	    std::__inplace_stable_partition(__first, __pred,
                					 _DistanceType(__buf.requested_size()));
                	}
                    }
                
                  /// This is a helper function for the sort routines.
                  template<typename _RandomAccessIterator>
                    void
                    __heap_select(_RandomAccessIterator __first,
                		  _RandomAccessIterator __middle,
                		  _RandomAccessIterator __last)
                    {
                      std::make_heap(__first, __middle);
                      for (_RandomAccessIterator __i = __middle; __i < __last; ++__i)
                	if (*__i < *__first)
                	  std::__pop_heap(__first, __middle, __i);
                    }
                
                  /// This is a helper function for the sort routines.
                  template<typename _RandomAccessIterator, typename _Compare>
                    void
                    __heap_select(_RandomAccessIterator __first,
                		  _RandomAccessIterator __middle,
                		  _RandomAccessIterator __last, _Compare __comp)
                    {
                      std::make_heap(__first, __middle, __comp);
                      for (_RandomAccessIterator __i = __middle; __i < __last; ++__i)
                	if (__comp(*__i, *__first))
                	  std::__pop_heap(__first, __middle, __i, __comp);
                    }
                
                  // partial_sort
                
                  /**
                   *  @brief Copy the smallest elements of a sequence.
                   *  @ingroup sorting_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @param  __result_first   A random-access iterator.
                   *  @param  __result_last    Another random-access iterator.
                   *  @return   An iterator indicating the end of the resulting sequence.
                   *
                   *  Copies and sorts the smallest N values from the range @p [__first,__last)
                   *  to the range beginning at @p __result_first, where the number of
                   *  elements to be copied, @p N, is the smaller of @p (__last-__first) and
                   *  @p (__result_last-__result_first).
                   *  After the sort if @e i and @e j are iterators in the range
                   *  @p [__result_first,__result_first+N) such that i precedes j then
                   *  *j<*i is false.
                   *  The value returned is @p __result_first+N.
                  */
                  template<typename _InputIterator, typename _RandomAccessIterator>
                    _RandomAccessIterator
                    partial_sort_copy(_InputIterator __first, _InputIterator __last,
                		      _RandomAccessIterator __result_first,
                		      _RandomAccessIterator __result_last)
                    {
                      typedef typename iterator_traits<_InputIterator>::value_type
                	_InputValueType;
                      typedef typename iterator_traits<_RandomAccessIterator>::value_type
                	_OutputValueType;
                      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
                	_DistanceType;
                
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_ConvertibleConcept<_InputValueType,
                				  _OutputValueType>)
                      __glibcxx_function_requires(_LessThanOpConcept<_InputValueType,
                				                     _OutputValueType>)
                      __glibcxx_function_requires(_LessThanComparableConcept<_OutputValueType>)
                      __glibcxx_requires_valid_range(__first, __last);
                      __glibcxx_requires_valid_range(__result_first, __result_last);
                
                      if (__result_first == __result_last)
                	return __result_last;
                      _RandomAccessIterator __result_real_last = __result_first;
                      while(__first != __last && __result_real_last != __result_last)
                	{
                	  *__result_real_last = *__first;
                	  ++__result_real_last;
                	  ++__first;
                	}
                      std::make_heap(__result_first, __result_real_last);
                      while (__first != __last)
                	{
                	  if (*__first < *__result_first)
                	    std::__adjust_heap(__result_first, _DistanceType(0),
                			       _DistanceType(__result_real_last
                					     - __result_first),
                			       _InputValueType(*__first));
                	  ++__first;
                	}
                      std::sort_heap(__result_first, __result_real_last);
                      return __result_real_last;
                    }
                
                  /**
                   *  @brief Copy the smallest elements of a sequence using a predicate for
                   *         comparison.
                   *  @ingroup sorting_algorithms
                   *  @param  __first   An input iterator.
                   *  @param  __last    Another input iterator.
                   *  @param  __result_first   A random-access iterator.
                   *  @param  __result_last    Another random-access iterator.
                   *  @param  __comp    A comparison functor.
                   *  @return   An iterator indicating the end of the resulting sequence.
                   *
                   *  Copies and sorts the smallest N values from the range @p [__first,__last)
                   *  to the range beginning at @p result_first, where the number of
                   *  elements to be copied, @p N, is the smaller of @p (__last-__first) and
                   *  @p (__result_last-__result_first).
                   *  After the sort if @e i and @e j are iterators in the range
                   *  @p [__result_first,__result_first+N) such that i precedes j then
                   *  @p __comp(*j,*i) is false.
                   *  The value returned is @p __result_first+N.
                  */
                  template<typename _InputIterator, typename _RandomAccessIterator, typename _Compare>
                    _RandomAccessIterator
                    partial_sort_copy(_InputIterator __first, _InputIterator __last,
                		      _RandomAccessIterator __result_first,
                		      _RandomAccessIterator __result_last,
                		      _Compare __comp)
                    {
                      typedef typename iterator_traits<_InputIterator>::value_type
                	_InputValueType;
                      typedef typename iterator_traits<_RandomAccessIterator>::value_type
                	_OutputValueType;
                      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
                	_DistanceType;
                
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_Mutable_RandomAccessIteratorConcept<
                				  _RandomAccessIterator>)
                      __glibcxx_function_requires(_ConvertibleConcept<_InputValueType,
                				  _OutputValueType>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _InputValueType, _OutputValueType>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _OutputValueType, _OutputValueType>)
                      __glibcxx_requires_valid_range(__first, __last);
                      __glibcxx_requires_valid_range(__result_first, __result_last);
                
                      if (__result_first == __result_last)
                	return __result_last;
                      _RandomAccessIterator __result_real_last = __result_first;
                      while(__first != __last && __result_real_last != __result_last)
                	{
                	  *__result_real_last = *__first;
                	  ++__result_real_last;
                	  ++__first;
                	}
                      std::make_heap(__result_first, __result_real_last, __comp);
                      while (__first != __last)
                	{
                	  if (__comp(*__first, *__result_first))
                	    std::__adjust_heap(__result_first, _DistanceType(0),
                			       _DistanceType(__result_real_last
                					     - __result_first),
                			       _InputValueType(*__first),
                			       __comp);
                	  ++__first;
                	}
                      std::sort_heap(__result_first, __result_real_last, __comp);
                      return __result_real_last;
                    }
                
                  /// This is a helper function for the sort routine.
                  template<typename _RandomAccessIterator>
                    void
                    __unguarded_linear_insert(_RandomAccessIterator __last)
                    {
                      typename iterator_traits<_RandomAccessIterator>::value_type
                	__val = _GLIBCXX_MOVE(*__last);
                      _RandomAccessIterator __next = __last;
                      --__next;
                      while (__val < *__next)
                	{
                	  *__last = _GLIBCXX_MOVE(*__next);
                	  __last = __next;
                	  --__next;
                	}
                      *__last = _GLIBCXX_MOVE(__val);
                    }
                
                  /// This is a helper function for the sort routine.
                  template<typename _RandomAccessIterator, typename _Compare>
                    void
                    __unguarded_linear_insert(_RandomAccessIterator __last,
                			      _Compare __comp)
                    {
                      typename iterator_traits<_RandomAccessIterator>::value_type
                	__val = _GLIBCXX_MOVE(*__last);
                      _RandomAccessIterator __next = __last;
                      --__next;
                      while (__comp(__val, *__next))
                	{
                	  *__last = _GLIBCXX_MOVE(*__next);
                	  __last = __next;
                	  --__next;
                	}
                      *__last = _GLIBCXX_MOVE(__val);
                    }
                
                  /// This is a helper function for the sort routine.
                  template<typename _RandomAccessIterator>
                    void
                    __insertion_sort(_RandomAccessIterator __first,
                		     _RandomAccessIterator __last)
                    {
                      if (__first == __last)
                	return;
                
                      for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
                	{
                	  if (*__i < *__first)
                	    {
                	      typename iterator_traits<_RandomAccessIterator>::value_type
                		__val = _GLIBCXX_MOVE(*__i);
                	      _GLIBCXX_MOVE_BACKWARD3(__first, __i, __i + 1);
                	      *__first = _GLIBCXX_MOVE(__val);
                	    }
                	  else
                	    std::__unguarded_linear_insert(__i);
                	}
                    }
                
                  /// This is a helper function for the sort routine.
                  template<typename _RandomAccessIterator, typename _Compare>
                    void
                    __insertion_sort(_RandomAccessIterator __first,
                		     _RandomAccessIterator __last, _Compare __comp)
                    {
                      if (__first == __last) return;
                
                      for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
                	{
                	  if (__comp(*__i, *__first))
                	    {
                	      typename iterator_traits<_RandomAccessIterator>::value_type
                		__val = _GLIBCXX_MOVE(*__i);
                	      _GLIBCXX_MOVE_BACKWARD3(__first, __i, __i + 1);
                	      *__first = _GLIBCXX_MOVE(__val);
                	    }
                	  else
                	    std::__unguarded_linear_insert(__i, __comp);
                	}
                    }
                
                  /// This is a helper function for the sort routine.
                  template<typename _RandomAccessIterator>
                    inline void
                    __unguarded_insertion_sort(_RandomAccessIterator __first,
                			       _RandomAccessIterator __last)
                    {
                      typedef typename iterator_traits<_RandomAccessIterator>::value_type
                	_ValueType;
                
                      for (_RandomAccessIterator __i = __first; __i != __last; ++__i)
                	std::__unguarded_linear_insert(__i);
                    }
                
                  /// This is a helper function for the sort routine.
                  template<typename _RandomAccessIterator, typename _Compare>
                    inline void
                    __unguarded_insertion_sort(_RandomAccessIterator __first,
                			       _RandomAccessIterator __last, _Compare __comp)
                    {
                      typedef typename iterator_traits<_RandomAccessIterator>::value_type
                	_ValueType;
                
                      for (_RandomAccessIterator __i = __first; __i != __last; ++__i)
                	std::__unguarded_linear_insert(__i, __comp);
                    }
                
                  /**
                   *  @doctodo
                   *  This controls some aspect of the sort routines.
                  */
                  enum { _S_threshold = 16 };
                
                  /// This is a helper function for the sort routine.
                  template<typename _RandomAccessIterator>
                    void
                    __final_insertion_sort(_RandomAccessIterator __first,
                			   _RandomAccessIterator __last)
                    {
                      if (__last - __first > int(_S_threshold))
                	{
                	  std::__insertion_sort(__first, __first + int(_S_threshold));
                	  std::__unguarded_insertion_sort(__first + int(_S_threshold), __last);
                	}
                      else
                	std::__insertion_sort(__first, __last);
                    }
                
                  /// This is a helper function for the sort routine.
                  template<typename _RandomAccessIterator, typename _Compare>
                    void
                    __final_insertion_sort(_RandomAccessIterator __first,
                			   _RandomAccessIterator __last, _Compare __comp)
                    {
                      if (__last - __first > int(_S_threshold))
                	{
                	  std::__insertion_sort(__first, __first + int(_S_threshold), __comp);
                	  std::__unguarded_insertion_sort(__first + int(_S_threshold), __last,
                					  __comp);
                	}
                      else
                	std::__insertion_sort(__first, __last, __comp);
                    }
                
                  /// This is a helper function...
                  template<typename _RandomAccessIterator, typename _Tp>
                    _RandomAccessIterator
                    __unguarded_partition(_RandomAccessIterator __first,
                			  _RandomAccessIterator __last, const _Tp& __pivot)
                    {
                      while (true)
                	{
                	  while (*__first < __pivot)
                	    ++__first;
                	  --__last;
                	  while (__pivot < *__last)
                	    --__last;
                	  if (!(__first < __last))
                	    return __first;
                	  std::iter_swap(__first, __last);
                	  ++__first;
                	}
                    }
                
                  /// This is a helper function...
                  template<typename _RandomAccessIterator, typename _Tp, typename _Compare>
                    _RandomAccessIterator
                    __unguarded_partition(_RandomAccessIterator __first,
                			  _RandomAccessIterator __last,
                			  const _Tp& __pivot, _Compare __comp)
                    {
                      while (true)
                	{
                	  while (__comp(*__first, __pivot))
                	    ++__first;
                	  --__last;
                	  while (__comp(__pivot, *__last))
                	    --__last;
                	  if (!(__first < __last))
                	    return __first;
                	  std::iter_swap(__first, __last);
                	  ++__first;
                	}
                    }
                
                  /// This is a helper function...
                  template<typename _RandomAccessIterator>
                    inline _RandomAccessIterator
                    __unguarded_partition_pivot(_RandomAccessIterator __first,
                				_RandomAccessIterator __last)
                    {
                      _RandomAccessIterator __mid = __first + (__last - __first) / 2;
                      std::__move_median_to_first(__first, __first + 1, __mid, __last - 1);
                      return std::__unguarded_partition(__first + 1, __last, *__first);
                    }
                
                
                  /// This is a helper function...
                  template<typename _RandomAccessIterator, typename _Compare>
                    inline _RandomAccessIterator
                    __unguarded_partition_pivot(_RandomAccessIterator __first,
                				_RandomAccessIterator __last, _Compare __comp)
                    {
                      _RandomAccessIterator __mid = __first + (__last - __first) / 2;
                      std::__move_median_to_first(__first, __first + 1, __mid, __last - 1,
                				  __comp);
                      return std::__unguarded_partition(__first + 1, __last, *__first, __comp);
                    }
                
                  /// This is a helper function for the sort routine.
                  template<typename _RandomAccessIterator, typename _Size>
                    void
                    __introsort_loop(_RandomAccessIterator __first,
                		     _RandomAccessIterator __last,
                		     _Size __depth_limit)
                    {
                      while (__last - __first > int(_S_threshold))
                	{
                	  if (__depth_limit == 0)
                	    {
                	      _GLIBCXX_STD_A::partial_sort(__first, __last, __last);
                	      return;
                	    }
                	  --__depth_limit;
                	  _RandomAccessIterator __cut =
                	    std::__unguarded_partition_pivot(__first, __last);
                	  std::__introsort_loop(__cut, __last, __depth_limit);
                	  __last = __cut;
                	}
                    }
                
                  /// This is a helper function for the sort routine.
                  template<typename _RandomAccessIterator, typename _Size, typename _Compare>
                    void
                    __introsort_loop(_RandomAccessIterator __first,
                		     _RandomAccessIterator __last,
                		     _Size __depth_limit, _Compare __comp)
                    {
                      while (__last - __first > int(_S_threshold))
                	{
                	  if (__depth_limit == 0)
                	    {
                	      _GLIBCXX_STD_A::partial_sort(__first, __last, __last, __comp);
                	      return;
                	    }
                	  --__depth_limit;
                	  _RandomAccessIterator __cut =
                	    std::__unguarded_partition_pivot(__first, __last, __comp);
                	  std::__introsort_loop(__cut, __last, __depth_limit, __comp);
                	  __last = __cut;
                	}
                    }
                
                  // sort
                
                  template<typename _RandomAccessIterator, typename _Size>
                    void
                    __introselect(_RandomAccessIterator __first, _RandomAccessIterator __nth,
                		  _RandomAccessIterator __last, _Size __depth_limit)
                    {
                      typedef typename iterator_traits<_RandomAccessIterator>::value_type
                	_ValueType;
                
                      while (__last - __first > 3)
                	{
                	  if (__depth_limit == 0)
                	    {
                	      std::__heap_select(__first, __nth + 1, __last);
                
                	      // Place the nth largest element in its final position.
                	      std::iter_swap(__first, __nth);
                	      return;
                	    }
                	  --__depth_limit;
                	  _RandomAccessIterator __cut =
                	    std::__unguarded_partition_pivot(__first, __last);
                	  if (__cut <= __nth)
                	    __first = __cut;
                	  else
                	    __last = __cut;
                	}
                      std::__insertion_sort(__first, __last);
                    }
                
                  template<typename _RandomAccessIterator, typename _Size, typename _Compare>
                    void
                    __introselect(_RandomAccessIterator __first, _RandomAccessIterator __nth,
                		  _RandomAccessIterator __last, _Size __depth_limit,
                		  _Compare __comp)
                    {
                      typedef typename iterator_traits<_RandomAccessIterator>::value_type
                	_ValueType;
                
                      while (__last - __first > 3)
                	{
                	  if (__depth_limit == 0)
                	    {
                	      std::__heap_select(__first, __nth + 1, __last, __comp);
                	      // Place the nth largest element in its final position.
                	      std::iter_swap(__first, __nth);
                	      return;
                	    }
                	  --__depth_limit;
                	  _RandomAccessIterator __cut =
                	    std::__unguarded_partition_pivot(__first, __last, __comp);
                	  if (__cut <= __nth)
                	    __first = __cut;
                	  else
                	    __last = __cut;
                	}
                      std::__insertion_sort(__first, __last, __comp);
                    }
                
                  // nth_element
                
                  // lower_bound moved to stl_algobase.h
                
                  /**
                   *  @brief Finds the first position in which @p __val could be inserted
                   *         without changing the ordering.
                   *  @ingroup binary_search_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @param  __val     The search term.
                   *  @param  __comp    A functor to use for comparisons.
                   *  @return An iterator pointing to the first element <em>not less
                   *           than</em> @p __val, or end() if every element is less
                   *           than @p __val.
                   *  @ingroup binary_search_algorithms
                   *
                   *  The comparison function should have the same effects on ordering as
                   *  the function used for the initial sort.
                  */
                  template<typename _ForwardIterator, typename _Tp, typename _Compare>
                    _ForwardIterator
                    lower_bound(_ForwardIterator __first, _ForwardIterator __last,
                		const _Tp& __val, _Compare __comp)
                    {
                      typedef typename iterator_traits<_ForwardIterator>::value_type
                	_ValueType;
                      typedef typename iterator_traits<_ForwardIterator>::difference_type
                	_DistanceType;
                
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _ValueType, _Tp>)
                      __glibcxx_requires_partitioned_lower_pred(__first, __last,
                						__val, __comp);
                
                      _DistanceType __len = std::distance(__first, __last);
                
                      while (__len > 0)
                	{
                	  _DistanceType __half = __len >> 1;
                	  _ForwardIterator __middle = __first;
                	  std::advance(__middle, __half);
                	  if (__comp(*__middle, __val))
                	    {
                	      __first = __middle;
                	      ++__first;
                	      __len = __len - __half - 1;
                	    }
                	  else
                	    __len = __half;
                	}
                      return __first;
                    }
                
                  /**
                   *  @brief Finds the last position in which @p __val could be inserted
                   *         without changing the ordering.
                   *  @ingroup binary_search_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @param  __val     The search term.
                   *  @return  An iterator pointing to the first element greater than @p __val,
                   *           or end() if no elements are greater than @p __val.
                   *  @ingroup binary_search_algorithms
                  */
                  template<typename _ForwardIterator, typename _Tp>
                    _ForwardIterator
                    upper_bound(_ForwardIterator __first, _ForwardIterator __last,
                		const _Tp& __val)
                    {
                      typedef typename iterator_traits<_ForwardIterator>::value_type
                	_ValueType;
                      typedef typename iterator_traits<_ForwardIterator>::difference_type
                	_DistanceType;
                
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_LessThanOpConcept<_Tp, _ValueType>)
                      __glibcxx_requires_partitioned_upper(__first, __last, __val);
                
                      _DistanceType __len = std::distance(__first, __last);
                
                      while (__len > 0)
                	{
                	  _DistanceType __half = __len >> 1;
                	  _ForwardIterator __middle = __first;
                	  std::advance(__middle, __half);
                	  if (__val < *__middle)
                	    __len = __half;
                	  else
                	    {
                	      __first = __middle;
                	      ++__first;
                	      __len = __len - __half - 1;
                	    }
                	}
                      return __first;
                    }
                
                  /**
                   *  @brief Finds the last position in which @p __val could be inserted
                   *         without changing the ordering.
                   *  @ingroup binary_search_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @param  __val     The search term.
                   *  @param  __comp    A functor to use for comparisons.
                   *  @return  An iterator pointing to the first element greater than @p __val,
                   *           or end() if no elements are greater than @p __val.
                   *  @ingroup binary_search_algorithms
                   *
                   *  The comparison function should have the same effects on ordering as
                   *  the function used for the initial sort.
                  */
                  template<typename _ForwardIterator, typename _Tp, typename _Compare>
                    _ForwardIterator
                    upper_bound(_ForwardIterator __first, _ForwardIterator __last,
                		const _Tp& __val, _Compare __comp)
                    {
                      typedef typename iterator_traits<_ForwardIterator>::value_type
                	_ValueType;
                      typedef typename iterator_traits<_ForwardIterator>::difference_type
                	_DistanceType;
                
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _Tp, _ValueType>)
                      __glibcxx_requires_partitioned_upper_pred(__first, __last,
                						__val, __comp);
                
                      _DistanceType __len = std::distance(__first, __last);
                
                      while (__len > 0)
                	{
                	  _DistanceType __half = __len >> 1;
                	  _ForwardIterator __middle = __first;
                	  std::advance(__middle, __half);
                	  if (__comp(__val, *__middle))
                	    __len = __half;
                	  else
                	    {
                	      __first = __middle;
                	      ++__first;
                	      __len = __len - __half - 1;
                	    }
                	}
                      return __first;
                    }
                
                  /**
                   *  @brief Finds the largest subrange in which @p __val could be inserted
                   *         at any place in it without changing the ordering.
                   *  @ingroup binary_search_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @param  __val     The search term.
                   *  @return  An pair of iterators defining the subrange.
                   *  @ingroup binary_search_algorithms
                   *
                   *  This is equivalent to
                   *  @code
                   *    std::make_pair(lower_bound(__first, __last, __val),
                   *                   upper_bound(__first, __last, __val))
                   *  @endcode
                   *  but does not actually call those functions.
                  */
                  template<typename _ForwardIterator, typename _Tp>
                    pair<_ForwardIterator, _ForwardIterator>
                    equal_range(_ForwardIterator __first, _ForwardIterator __last,
                		const _Tp& __val)
                    {
                      typedef typename iterator_traits<_ForwardIterator>::value_type
                	_ValueType;
                      typedef typename iterator_traits<_ForwardIterator>::difference_type
                	_DistanceType;
                
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_LessThanOpConcept<_ValueType, _Tp>)
                      __glibcxx_function_requires(_LessThanOpConcept<_Tp, _ValueType>)	
                      __glibcxx_requires_partitioned_lower(__first, __last, __val);
                      __glibcxx_requires_partitioned_upper(__first, __last, __val);      
                
                      _DistanceType __len = std::distance(__first, __last);
                 
                      while (__len > 0)
                	{
                	  _DistanceType __half = __len >> 1;
                	  _ForwardIterator __middle = __first;
                	  std::advance(__middle, __half);
                	  if (*__middle < __val)
                	    {
                	      __first = __middle;
                	      ++__first;
                	      __len = __len - __half - 1;
                	    }
                	  else if (__val < *__middle)
                	    __len = __half;
                	  else
                	    {
                	      _ForwardIterator __left = std::lower_bound(__first, __middle,
                							 __val);
                	      std::advance(__first, __len);
                	      _ForwardIterator __right = std::upper_bound(++__middle, __first,
                							  __val);
                	      return pair<_ForwardIterator, _ForwardIterator>(__left, __right);
                	    }
                	}
                      return pair<_ForwardIterator, _ForwardIterator>(__first, __first);
                    }
                
                  /**
                   *  @brief Finds the largest subrange in which @p __val could be inserted
                   *         at any place in it without changing the ordering.
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @param  __val     The search term.
                   *  @param  __comp    A functor to use for comparisons.
                   *  @return  An pair of iterators defining the subrange.
                   *  @ingroup binary_search_algorithms
                   *
                   *  This is equivalent to
                   *  @code
                   *    std::make_pair(lower_bound(__first, __last, __val, __comp),
                   *                   upper_bound(__first, __last, __val, __comp))
                   *  @endcode
                   *  but does not actually call those functions.
                  */
                  template<typename _ForwardIterator, typename _Tp, typename _Compare>
                    pair<_ForwardIterator, _ForwardIterator>
                    equal_range(_ForwardIterator __first, _ForwardIterator __last,
                		const _Tp& __val, _Compare __comp)
                    {
                      typedef typename iterator_traits<_ForwardIterator>::value_type
                	_ValueType;
                      typedef typename iterator_traits<_ForwardIterator>::difference_type
                	_DistanceType;
                
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _ValueType, _Tp>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _Tp, _ValueType>)
                      __glibcxx_requires_partitioned_lower_pred(__first, __last,
                						__val, __comp);
                      __glibcxx_requires_partitioned_upper_pred(__first, __last,
                						__val, __comp);
                
                      _DistanceType __len = std::distance(__first, __last);
                
                      while (__len > 0)
                	{
                	  _DistanceType __half = __len >> 1;
                	  _ForwardIterator __middle = __first;
                	  std::advance(__middle, __half);
                	  if (__comp(*__middle, __val))
                	    {
                	      __first = __middle;
                	      ++__first;
                	      __len = __len - __half - 1;
                	    }
                	  else if (__comp(__val, *__middle))
                	    __len = __half;
                	  else
                	    {
                	      _ForwardIterator __left = std::lower_bound(__first, __middle,
                							 __val, __comp);
                	      std::advance(__first, __len);
                	      _ForwardIterator __right = std::upper_bound(++__middle, __first,
                							  __val, __comp);
                	      return pair<_ForwardIterator, _ForwardIterator>(__left, __right);
                	    }
                	}
                      return pair<_ForwardIterator, _ForwardIterator>(__first, __first);
                    }
                
                  /**
                   *  @brief Determines whether an element exists in a range.
                   *  @ingroup binary_search_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @param  __val     The search term.
                   *  @return True if @p __val (or its equivalent) is in [@p
                   *  __first,@p __last ].
                   *
                   *  Note that this does not actually return an iterator to @p __val.  For
                   *  that, use std::find or a container's specialized find member functions.
                  */
                  template<typename _ForwardIterator, typename _Tp>
                    bool
                    binary_search(_ForwardIterator __first, _ForwardIterator __last,
                                  const _Tp& __val)
                    {
                      typedef typename iterator_traits<_ForwardIterator>::value_type
                	_ValueType;
                
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_LessThanOpConcept<_Tp, _ValueType>)
                      __glibcxx_requires_partitioned_lower(__first, __last, __val);
                      __glibcxx_requires_partitioned_upper(__first, __last, __val);
                
                      _ForwardIterator __i = std::lower_bound(__first, __last, __val);
                      return __i != __last && !(__val < *__i);
                    }
                
                  /**
                   *  @brief Determines whether an element exists in a range.
                   *  @ingroup binary_search_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @param  __val     The search term.
                   *  @param  __comp    A functor to use for comparisons.
                   *  @return  True if @p __val (or its equivalent) is in @p [__first,__last].
                   *
                   *  Note that this does not actually return an iterator to @p __val.  For
                   *  that, use std::find or a container's specialized find member functions.
                   *
                   *  The comparison function should have the same effects on ordering as
                   *  the function used for the initial sort.
                  */
                  template<typename _ForwardIterator, typename _Tp, typename _Compare>
                    bool
                    binary_search(_ForwardIterator __first, _ForwardIterator __last,
                                  const _Tp& __val, _Compare __comp)
                    {
                      typedef typename iterator_traits<_ForwardIterator>::value_type
                	_ValueType;
                
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _Tp, _ValueType>)
                      __glibcxx_requires_partitioned_lower_pred(__first, __last,
                						__val, __comp);
                      __glibcxx_requires_partitioned_upper_pred(__first, __last,
                						__val, __comp);
                
                      _ForwardIterator __i = std::lower_bound(__first, __last, __val, __comp);
                      return __i != __last && !bool(__comp(__val, *__i));
                    }
                
                  // merge
                
                  /// This is a helper function for the __merge_adaptive routines.
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _OutputIterator>
                    void
                    __move_merge_adaptive(_InputIterator1 __first1, _InputIterator1 __last1,
                			  _InputIterator2 __first2, _InputIterator2 __last2,
                			  _OutputIterator __result)
                    {
                      while (__first1 != __last1 && __first2 != __last2)
                	{
                	  if (*__first2 < *__first1)
                	    {
                	      *__result = _GLIBCXX_MOVE(*__first2);
                	      ++__first2;
                	    }
                	  else
                	    {
                	      *__result = _GLIBCXX_MOVE(*__first1);
                	      ++__first1;
                	    }
                	  ++__result;
                	}
                      if (__first1 != __last1)
                	_GLIBCXX_MOVE3(__first1, __last1, __result);
                    }
                
                  /// This is a helper function for the __merge_adaptive routines.
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _OutputIterator, typename _Compare>
                    void
                    __move_merge_adaptive(_InputIterator1 __first1, _InputIterator1 __last1,
                			  _InputIterator2 __first2, _InputIterator2 __last2,
                			  _OutputIterator __result, _Compare __comp)
                    {
                      while (__first1 != __last1 && __first2 != __last2)
                	{
                	  if (__comp(*__first2, *__first1))
                	    {
                	      *__result = _GLIBCXX_MOVE(*__first2);
                	      ++__first2;
                	    }
                	  else
                	    {
                	      *__result = _GLIBCXX_MOVE(*__first1);
                	      ++__first1;
                	    }
                	  ++__result;
                	}
                      if (__first1 != __last1)
                	_GLIBCXX_MOVE3(__first1, __last1, __result);
                    }
                
                  /// This is a helper function for the __merge_adaptive routines.
                  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2,
                	   typename _BidirectionalIterator3>
                    void
                    __move_merge_adaptive_backward(_BidirectionalIterator1 __first1,
                				   _BidirectionalIterator1 __last1,
                				   _BidirectionalIterator2 __first2,
                				   _BidirectionalIterator2 __last2,
                				   _BidirectionalIterator3 __result)
                    {
                      if (__first1 == __last1)
                	{
                	  _GLIBCXX_MOVE_BACKWARD3(__first2, __last2, __result);
                	  return;
                	}
                      else if (__first2 == __last2)
                	return;
                
                      --__last1;
                      --__last2;
                      while (true)
                	{
                	  if (*__last2 < *__last1)
                	    {
                	      *--__result = _GLIBCXX_MOVE(*__last1);
                	      if (__first1 == __last1)
                		{
                		  _GLIBCXX_MOVE_BACKWARD3(__first2, ++__last2, __result);
                		  return;
                		}
                	      --__last1;
                	    }
                	  else
                	    {
                	      *--__result = _GLIBCXX_MOVE(*__last2);
                	      if (__first2 == __last2)
                		return;
                	      --__last2;
                	    }
                	}
                    }
                
                  /// This is a helper function for the __merge_adaptive routines.
                  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2,
                	   typename _BidirectionalIterator3, typename _Compare>
                    void
                    __move_merge_adaptive_backward(_BidirectionalIterator1 __first1,
                				   _BidirectionalIterator1 __last1,
                				   _BidirectionalIterator2 __first2,
                				   _BidirectionalIterator2 __last2,
                				   _BidirectionalIterator3 __result,
                				   _Compare __comp)
                    {
                      if (__first1 == __last1)
                	{
                	  _GLIBCXX_MOVE_BACKWARD3(__first2, __last2, __result);
                	  return;
                	}
                      else if (__first2 == __last2)
                	return;
                
                      --__last1;
                      --__last2;
                      while (true)
                	{
                	  if (__comp(*__last2, *__last1))
                	    {
                	      *--__result = _GLIBCXX_MOVE(*__last1);
                	      if (__first1 == __last1)
                		{
                		  _GLIBCXX_MOVE_BACKWARD3(__first2, ++__last2, __result);
                		  return;
                		}
                	      --__last1;
                	    }
                	  else
                	    {
                	      *--__result = _GLIBCXX_MOVE(*__last2);
                	      if (__first2 == __last2)
                		return;
                	      --__last2;
                	    }
                	}
                    }
                
                  /// This is a helper function for the merge routines.
                  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2,
                	   typename _Distance>
                    _BidirectionalIterator1
                    __rotate_adaptive(_BidirectionalIterator1 __first,
                		      _BidirectionalIterator1 __middle,
                		      _BidirectionalIterator1 __last,
                		      _Distance __len1, _Distance __len2,
                		      _BidirectionalIterator2 __buffer,
                		      _Distance __buffer_size)
                    {
                      _BidirectionalIterator2 __buffer_end;
                      if (__len1 > __len2 && __len2 <= __buffer_size)
                	{
                	  if (__len2)
                	    {
                	      __buffer_end = _GLIBCXX_MOVE3(__middle, __last, __buffer);
                	      _GLIBCXX_MOVE_BACKWARD3(__first, __middle, __last);
                	      return _GLIBCXX_MOVE3(__buffer, __buffer_end, __first);
                	    }
                	  else
                	    return __first;
                	}
                      else if (__len1 <= __buffer_size)
                	{
                	  if (__len1)
                	    {
                	      __buffer_end = _GLIBCXX_MOVE3(__first, __middle, __buffer);
                	      _GLIBCXX_MOVE3(__middle, __last, __first);
                	      return _GLIBCXX_MOVE_BACKWARD3(__buffer, __buffer_end, __last);
                	    }
                	  else
                	    return __last;
                	}
                      else
                	{
                	  std::rotate(__first, __middle, __last);
                	  std::advance(__first, std::distance(__middle, __last));
                	  return __first;
                	}
                    }
                
                  /// This is a helper function for the merge routines.
                  template<typename _BidirectionalIterator, typename _Distance,
                	   typename _Pointer>
                    void
                    __merge_adaptive(_BidirectionalIterator __first,
                                     _BidirectionalIterator __middle,
                		     _BidirectionalIterator __last,
                		     _Distance __len1, _Distance __len2,
                		     _Pointer __buffer, _Distance __buffer_size)
                    {
                      if (__len1 <= __len2 && __len1 <= __buffer_size)
                	{
                	  _Pointer __buffer_end = _GLIBCXX_MOVE3(__first, __middle, __buffer);
                	  std::__move_merge_adaptive(__buffer, __buffer_end, __middle, __last,
                				     __first);
                	}
                      else if (__len2 <= __buffer_size)
                	{
                	  _Pointer __buffer_end = _GLIBCXX_MOVE3(__middle, __last, __buffer);
                	  std::__move_merge_adaptive_backward(__first, __middle, __buffer,
                					      __buffer_end, __last);
                	}
                      else
                	{
                	  _BidirectionalIterator __first_cut = __first;
                	  _BidirectionalIterator __second_cut = __middle;
                	  _Distance __len11 = 0;
                	  _Distance __len22 = 0;
                	  if (__len1 > __len2)
                	    {
                	      __len11 = __len1 / 2;
                	      std::advance(__first_cut, __len11);
                	      __second_cut = std::lower_bound(__middle, __last,
                					      *__first_cut);
                	      __len22 = std::distance(__middle, __second_cut);
                	    }
                	  else
                	    {
                	      __len22 = __len2 / 2;
                	      std::advance(__second_cut, __len22);
                	      __first_cut = std::upper_bound(__first, __middle,
                					     *__second_cut);
                	      __len11 = std::distance(__first, __first_cut);
                	    }
                	  _BidirectionalIterator __new_middle =
                	    std::__rotate_adaptive(__first_cut, __middle, __second_cut,
                				   __len1 - __len11, __len22, __buffer,
                				   __buffer_size);
                	  std::__merge_adaptive(__first, __first_cut, __new_middle, __len11,
                				__len22, __buffer, __buffer_size);
                	  std::__merge_adaptive(__new_middle, __second_cut, __last,
                				__len1 - __len11,
                				__len2 - __len22, __buffer, __buffer_size);
                	}
                    }
                
                  /// This is a helper function for the merge routines.
                  template<typename _BidirectionalIterator, typename _Distance, 
                	   typename _Pointer, typename _Compare>
                    void
                    __merge_adaptive(_BidirectionalIterator __first,
                                     _BidirectionalIterator __middle,
                		     _BidirectionalIterator __last,
                		     _Distance __len1, _Distance __len2,
                		     _Pointer __buffer, _Distance __buffer_size,
                		     _Compare __comp)
                    {
                      if (__len1 <= __len2 && __len1 <= __buffer_size)
                	{
                	  _Pointer __buffer_end = _GLIBCXX_MOVE3(__first, __middle, __buffer);
                	  std::__move_merge_adaptive(__buffer, __buffer_end, __middle, __last,
                				     __first, __comp);
                	}
                      else if (__len2 <= __buffer_size)
                	{
                	  _Pointer __buffer_end = _GLIBCXX_MOVE3(__middle, __last, __buffer);
                	  std::__move_merge_adaptive_backward(__first, __middle, __buffer,
                					      __buffer_end, __last, __comp);
                	}
                      else
                	{
                	  _BidirectionalIterator __first_cut = __first;
                	  _BidirectionalIterator __second_cut = __middle;
                	  _Distance __len11 = 0;
                	  _Distance __len22 = 0;
                	  if (__len1 > __len2)
                	    {
                	      __len11 = __len1 / 2;
                	      std::advance(__first_cut, __len11);
                	      __second_cut = std::lower_bound(__middle, __last, *__first_cut,
                					      __comp);
                	      __len22 = std::distance(__middle, __second_cut);
                	    }
                	  else
                	    {
                	      __len22 = __len2 / 2;
                	      std::advance(__second_cut, __len22);
                	      __first_cut = std::upper_bound(__first, __middle, *__second_cut,
                					     __comp);
                	      __len11 = std::distance(__first, __first_cut);
                	    }
                	  _BidirectionalIterator __new_middle =
                	    std::__rotate_adaptive(__first_cut, __middle, __second_cut,
                				   __len1 - __len11, __len22, __buffer,
                				   __buffer_size);
                	  std::__merge_adaptive(__first, __first_cut, __new_middle, __len11,
                				__len22, __buffer, __buffer_size, __comp);
                	  std::__merge_adaptive(__new_middle, __second_cut, __last,
                				__len1 - __len11,
                				__len2 - __len22, __buffer,
                				__buffer_size, __comp);
                	}
                    }
                
                  /// This is a helper function for the merge routines.
                  template<typename _BidirectionalIterator, typename _Distance>
                    void
                    __merge_without_buffer(_BidirectionalIterator __first,
                			   _BidirectionalIterator __middle,
                			   _BidirectionalIterator __last,
                			   _Distance __len1, _Distance __len2)
                    {
                      if (__len1 == 0 || __len2 == 0)
                	return;
                      if (__len1 + __len2 == 2)
                	{
                	  if (*__middle < *__first)
                	    std::iter_swap(__first, __middle);
                	  return;
                	}
                      _BidirectionalIterator __first_cut = __first;
                      _BidirectionalIterator __second_cut = __middle;
                      _Distance __len11 = 0;
                      _Distance __len22 = 0;
                      if (__len1 > __len2)
                	{
                	  __len11 = __len1 / 2;
                	  std::advance(__first_cut, __len11);
                	  __second_cut = std::lower_bound(__middle, __last, *__first_cut);
                	  __len22 = std::distance(__middle, __second_cut);
                	}
                      else
                	{
                	  __len22 = __len2 / 2;
                	  std::advance(__second_cut, __len22);
                	  __first_cut = std::upper_bound(__first, __middle, *__second_cut);
                	  __len11 = std::distance(__first, __first_cut);
                	}
                      std::rotate(__first_cut, __middle, __second_cut);
                      _BidirectionalIterator __new_middle = __first_cut;
                      std::advance(__new_middle, std::distance(__middle, __second_cut));
                      std::__merge_without_buffer(__first, __first_cut, __new_middle,
                				  __len11, __len22);
                      std::__merge_without_buffer(__new_middle, __second_cut, __last,
                				  __len1 - __len11, __len2 - __len22);
                    }
                
                  /// This is a helper function for the merge routines.
                  template<typename _BidirectionalIterator, typename _Distance,
                	   typename _Compare>
                    void
                    __merge_without_buffer(_BidirectionalIterator __first,
                                           _BidirectionalIterator __middle,
                			   _BidirectionalIterator __last,
                			   _Distance __len1, _Distance __len2,
                			   _Compare __comp)
                    {
                      if (__len1 == 0 || __len2 == 0)
                	return;
                      if (__len1 + __len2 == 2)
                	{
                	  if (__comp(*__middle, *__first))
                	    std::iter_swap(__first, __middle);
                	  return;
                	}
                      _BidirectionalIterator __first_cut = __first;
                      _BidirectionalIterator __second_cut = __middle;
                      _Distance __len11 = 0;
                      _Distance __len22 = 0;
                      if (__len1 > __len2)
                	{
                	  __len11 = __len1 / 2;
                	  std::advance(__first_cut, __len11);
                	  __second_cut = std::lower_bound(__middle, __last, *__first_cut,
                					  __comp);
                	  __len22 = std::distance(__middle, __second_cut);
                	}
                      else
                	{
                	  __len22 = __len2 / 2;
                	  std::advance(__second_cut, __len22);
                	  __first_cut = std::upper_bound(__first, __middle, *__second_cut,
                					 __comp);
                	  __len11 = std::distance(__first, __first_cut);
                	}
                      std::rotate(__first_cut, __middle, __second_cut);
                      _BidirectionalIterator __new_middle = __first_cut;
                      std::advance(__new_middle, std::distance(__middle, __second_cut));
                      std::__merge_without_buffer(__first, __first_cut, __new_middle,
                				  __len11, __len22, __comp);
                      std::__merge_without_buffer(__new_middle, __second_cut, __last,
                				  __len1 - __len11, __len2 - __len22, __comp);
                    }
                
                  /**
                   *  @brief Merges two sorted ranges in place.
                   *  @ingroup sorting_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __middle  Another iterator.
                   *  @param  __last    Another iterator.
                   *  @return  Nothing.
                   *
                   *  Merges two sorted and consecutive ranges, [__first,__middle) and
                   *  [__middle,__last), and puts the result in [__first,__last).  The
                   *  output will be sorted.  The sort is @e stable, that is, for
                   *  equivalent elements in the two ranges, elements from the first
                   *  range will always come before elements from the second.
                   *
                   *  If enough additional memory is available, this takes (__last-__first)-1
                   *  comparisons.  Otherwise an NlogN algorithm is used, where N is
                   *  distance(__first,__last).
                  */
                  template<typename _BidirectionalIterator>
                    void
                    inplace_merge(_BidirectionalIterator __first,
                		  _BidirectionalIterator __middle,
                		  _BidirectionalIterator __last)
                    {
                      typedef typename iterator_traits<_BidirectionalIterator>::value_type
                          _ValueType;
                      typedef typename iterator_traits<_BidirectionalIterator>::difference_type
                          _DistanceType;
                
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_BidirectionalIteratorConcept<
                	    _BidirectionalIterator>)
                      __glibcxx_function_requires(_LessThanComparableConcept<_ValueType>)
                      __glibcxx_requires_sorted(__first, __middle);
                      __glibcxx_requires_sorted(__middle, __last);
                
                      if (__first == __middle || __middle == __last)
                	return;
                
                      _DistanceType __len1 = std::distance(__first, __middle);
                      _DistanceType __len2 = std::distance(__middle, __last);
                
                      _Temporary_buffer<_BidirectionalIterator, _ValueType> __buf(__first,
                								  __last);
                      if (__buf.begin() == 0)
                	std::__merge_without_buffer(__first, __middle, __last, __len1, __len2);
                      else
                	std::__merge_adaptive(__first, __middle, __last, __len1, __len2,
                			      __buf.begin(), _DistanceType(__buf.size()));
                    }
                
                  /**
                   *  @brief Merges two sorted ranges in place.
                   *  @ingroup sorting_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __middle  Another iterator.
                   *  @param  __last    Another iterator.
                   *  @param  __comp    A functor to use for comparisons.
                   *  @return  Nothing.
                   *
                   *  Merges two sorted and consecutive ranges, [__first,__middle) and
                   *  [middle,last), and puts the result in [__first,__last).  The output will
                   *  be sorted.  The sort is @e stable, that is, for equivalent
                   *  elements in the two ranges, elements from the first range will always
                   *  come before elements from the second.
                   *
                   *  If enough additional memory is available, this takes (__last-__first)-1
                   *  comparisons.  Otherwise an NlogN algorithm is used, where N is
                   *  distance(__first,__last).
                   *
                   *  The comparison function should have the same effects on ordering as
                   *  the function used for the initial sort.
                  */
                  template<typename _BidirectionalIterator, typename _Compare>
                    void
                    inplace_merge(_BidirectionalIterator __first,
                		  _BidirectionalIterator __middle,
                		  _BidirectionalIterator __last,
                		  _Compare __comp)
                    {
                      typedef typename iterator_traits<_BidirectionalIterator>::value_type
                          _ValueType;
                      typedef typename iterator_traits<_BidirectionalIterator>::difference_type
                          _DistanceType;
                
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_BidirectionalIteratorConcept<
                	    _BidirectionalIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                	    _ValueType, _ValueType>)
                      __glibcxx_requires_sorted_pred(__first, __middle, __comp);
                      __glibcxx_requires_sorted_pred(__middle, __last, __comp);
                
                      if (__first == __middle || __middle == __last)
                	return;
                
                      const _DistanceType __len1 = std::distance(__first, __middle);
                      const _DistanceType __len2 = std::distance(__middle, __last);
                
                      _Temporary_buffer<_BidirectionalIterator, _ValueType> __buf(__first,
                								  __last);
                      if (__buf.begin() == 0)
                	std::__merge_without_buffer(__first, __middle, __last, __len1,
                				    __len2, __comp);
                      else
                	std::__merge_adaptive(__first, __middle, __last, __len1, __len2,
                			      __buf.begin(), _DistanceType(__buf.size()),
                			      __comp);
                    }
                
                
                  /// This is a helper function for the __merge_sort_loop routines.
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _OutputIterator>
                    _OutputIterator
                    __move_merge(_InputIterator1 __first1, _InputIterator1 __last1,
                		 _InputIterator2 __first2, _InputIterator2 __last2,
                		 _OutputIterator __result)
                    {
                      while (__first1 != __last1 && __first2 != __last2)
                	{
                	  if (*__first2 < *__first1)
                	    {
                	      *__result = _GLIBCXX_MOVE(*__first2);
                	      ++__first2;
                	    }
                	  else
                	    {
                	      *__result = _GLIBCXX_MOVE(*__first1);
                	      ++__first1;
                	    }
                	  ++__result;
                	}
                      return _GLIBCXX_MOVE3(__first2, __last2,
                			    _GLIBCXX_MOVE3(__first1, __last1,
                					   __result));
                    }
                
                  /// This is a helper function for the __merge_sort_loop routines.
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _OutputIterator, typename _Compare>
                    _OutputIterator
                    __move_merge(_InputIterator1 __first1, _InputIterator1 __last1,
                		 _InputIterator2 __first2, _InputIterator2 __last2,
                		 _OutputIterator __result, _Compare __comp)
                    {
                      while (__first1 != __last1 && __first2 != __last2)
                	{
                	  if (__comp(*__first2, *__first1))
                	    {
                	      *__result = _GLIBCXX_MOVE(*__first2);
                	      ++__first2;
                	    }
                	  else
                	    {
                	      *__result = _GLIBCXX_MOVE(*__first1);
                	      ++__first1;
                	    }
                	  ++__result;
                	}
                      return _GLIBCXX_MOVE3(__first2, __last2,
                			    _GLIBCXX_MOVE3(__first1, __last1,
                					   __result));
                    }
                
                  template<typename _RandomAccessIterator1, typename _RandomAccessIterator2,
                	   typename _Distance>
                    void
                    __merge_sort_loop(_RandomAccessIterator1 __first,
                		      _RandomAccessIterator1 __last,
                		      _RandomAccessIterator2 __result,
                		      _Distance __step_size)
                    {
                      const _Distance __two_step = 2 * __step_size;
                
                      while (__last - __first >= __two_step)
                	{
                	  __result = std::__move_merge(__first, __first + __step_size,
                				       __first + __step_size,
                				       __first + __two_step, __result);
                	  __first += __two_step;
                	}
                
                      __step_size = std::min(_Distance(__last - __first), __step_size);
                      std::__move_merge(__first, __first + __step_size,
                			__first + __step_size, __last, __result);
                    }
                
                  template<typename _RandomAccessIterator1, typename _RandomAccessIterator2,
                	   typename _Distance, typename _Compare>
                    void
                    __merge_sort_loop(_RandomAccessIterator1 __first,
                		      _RandomAccessIterator1 __last,
                		      _RandomAccessIterator2 __result, _Distance __step_size,
                		      _Compare __comp)
                    {
                      const _Distance __two_step = 2 * __step_size;
                
                      while (__last - __first >= __two_step)
                	{
                	  __result = std::__move_merge(__first, __first + __step_size,
                				       __first + __step_size,
                				       __first + __two_step,
                				       __result, __comp);
                	  __first += __two_step;
                	}
                      __step_size = std::min(_Distance(__last - __first), __step_size);
                
                      std::__move_merge(__first,__first + __step_size,
                			__first + __step_size, __last, __result, __comp);
                    }
                
                  template<typename _RandomAccessIterator, typename _Distance>
                    void
                    __chunk_insertion_sort(_RandomAccessIterator __first,
                			   _RandomAccessIterator __last,
                			   _Distance __chunk_size)
                    {
                      while (__last - __first >= __chunk_size)
                	{
                	  std::__insertion_sort(__first, __first + __chunk_size);
                	  __first += __chunk_size;
                	}
                      std::__insertion_sort(__first, __last);
                    }
                
                  template<typename _RandomAccessIterator, typename _Distance,
                	   typename _Compare>
                    void
                    __chunk_insertion_sort(_RandomAccessIterator __first,
                			   _RandomAccessIterator __last,
                			   _Distance __chunk_size, _Compare __comp)
                    {
                      while (__last - __first >= __chunk_size)
                	{
                	  std::__insertion_sort(__first, __first + __chunk_size, __comp);
                	  __first += __chunk_size;
                	}
                      std::__insertion_sort(__first, __last, __comp);
                    }
                
                  enum { _S_chunk_size = 7 };
                
                  template<typename _RandomAccessIterator, typename _Pointer>
                    void
                    __merge_sort_with_buffer(_RandomAccessIterator __first,
                			     _RandomAccessIterator __last,
                                             _Pointer __buffer)
                    {
                      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
                	_Distance;
                
                      const _Distance __len = __last - __first;
                      const _Pointer __buffer_last = __buffer + __len;
                
                      _Distance __step_size = _S_chunk_size;
                      std::__chunk_insertion_sort(__first, __last, __step_size);
                
                      while (__step_size < __len)
                	{
                	  std::__merge_sort_loop(__first, __last, __buffer, __step_size);
                	  __step_size *= 2;
                	  std::__merge_sort_loop(__buffer, __buffer_last, __first, __step_size);
                	  __step_size *= 2;
                	}
                    }
                
                  template<typename _RandomAccessIterator, typename _Pointer, typename _Compare>
                    void
                    __merge_sort_with_buffer(_RandomAccessIterator __first,
                			     _RandomAccessIterator __last,
                                             _Pointer __buffer, _Compare __comp)
                    {
                      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
                	_Distance;
                
                      const _Distance __len = __last - __first;
                      const _Pointer __buffer_last = __buffer + __len;
                
                      _Distance __step_size = _S_chunk_size;
                      std::__chunk_insertion_sort(__first, __last, __step_size, __comp);
                
                      while (__step_size < __len)
                	{
                	  std::__merge_sort_loop(__first, __last, __buffer,
                				 __step_size, __comp);
                	  __step_size *= 2;
                	  std::__merge_sort_loop(__buffer, __buffer_last, __first,
                				 __step_size, __comp);
                	  __step_size *= 2;
                	}
                    }
                
                  template<typename _RandomAccessIterator, typename _Pointer,
                	   typename _Distance>
                    void
                    __stable_sort_adaptive(_RandomAccessIterator __first,
                			   _RandomAccessIterator __last,
                                           _Pointer __buffer, _Distance __buffer_size)
                    {
                      const _Distance __len = (__last - __first + 1) / 2;
                      const _RandomAccessIterator __middle = __first + __len;
                      if (__len > __buffer_size)
                	{
                	  std::__stable_sort_adaptive(__first, __middle,
                				      __buffer, __buffer_size);
                	  std::__stable_sort_adaptive(__middle, __last,
                				      __buffer, __buffer_size);
                	}
                      else
                	{
                	  std::__merge_sort_with_buffer(__first, __middle, __buffer);
                	  std::__merge_sort_with_buffer(__middle, __last, __buffer);
                	}
                      std::__merge_adaptive(__first, __middle, __last,
                			    _Distance(__middle - __first),
                			    _Distance(__last - __middle),
                			    __buffer, __buffer_size);
                    }
                
                  template<typename _RandomAccessIterator, typename _Pointer,
                	   typename _Distance, typename _Compare>
                    void
                    __stable_sort_adaptive(_RandomAccessIterator __first,
                			   _RandomAccessIterator __last,
                                           _Pointer __buffer, _Distance __buffer_size,
                                           _Compare __comp)
                    {
                      const _Distance __len = (__last - __first + 1) / 2;
                      const _RandomAccessIterator __middle = __first + __len;
                      if (__len > __buffer_size)
                	{
                	  std::__stable_sort_adaptive(__first, __middle, __buffer,
                				      __buffer_size, __comp);
                	  std::__stable_sort_adaptive(__middle, __last, __buffer,
                				      __buffer_size, __comp);
                	}
                      else
                	{
                	  std::__merge_sort_with_buffer(__first, __middle, __buffer, __comp);
                	  std::__merge_sort_with_buffer(__middle, __last, __buffer, __comp);
                	}
                      std::__merge_adaptive(__first, __middle, __last,
                			    _Distance(__middle - __first),
                			    _Distance(__last - __middle),
                			    __buffer, __buffer_size,
                			    __comp);
                    }
                
                  /// This is a helper function for the stable sorting routines.
                  template<typename _RandomAccessIterator>
                    void
                    __inplace_stable_sort(_RandomAccessIterator __first,
                			  _RandomAccessIterator __last)
                    {
                      if (__last - __first < 15)
                	{
                	  std::__insertion_sort(__first, __last);
                	  return;
                	}
                      _RandomAccessIterator __middle = __first + (__last - __first) / 2;
                      std::__inplace_stable_sort(__first, __middle);
                      std::__inplace_stable_sort(__middle, __last);
                      std::__merge_without_buffer(__first, __middle, __last,
                				  __middle - __first,
                				  __last - __middle);
                    }
                
                  /// This is a helper function for the stable sorting routines.
                  template<typename _RandomAccessIterator, typename _Compare>
                    void
                    __inplace_stable_sort(_RandomAccessIterator __first,
                			  _RandomAccessIterator __last, _Compare __comp)
                    {
                      if (__last - __first < 15)
                	{
                	  std::__insertion_sort(__first, __last, __comp);
                	  return;
                	}
                      _RandomAccessIterator __middle = __first + (__last - __first) / 2;
                      std::__inplace_stable_sort(__first, __middle, __comp);
                      std::__inplace_stable_sort(__middle, __last, __comp);
                      std::__merge_without_buffer(__first, __middle, __last,
                				  __middle - __first,
                				  __last - __middle,
                				  __comp);
                    }
                
                  // stable_sort
                
                  // Set algorithms: includes, set_union, set_intersection, set_difference,
                  // set_symmetric_difference.  All of these algorithms have the precondition
                  // that their input ranges are sorted and the postcondition that their output
                  // ranges are sorted.
                
                  /**
                   *  @brief Determines whether all elements of a sequence exists in a range.
                   *  @param  __first1  Start of search range.
                   *  @param  __last1   End of search range.
                   *  @param  __first2  Start of sequence
                   *  @param  __last2   End of sequence.
                   *  @return  True if each element in [__first2,__last2) is contained in order
                   *  within [__first1,__last1).  False otherwise.
                   *  @ingroup set_algorithms
                   *
                   *  This operation expects both [__first1,__last1) and
                   *  [__first2,__last2) to be sorted.  Searches for the presence of
                   *  each element in [__first2,__last2) within [__first1,__last1).
                   *  The iterators over each range only move forward, so this is a
                   *  linear algorithm.  If an element in [__first2,__last2) is not
                   *  found before the search iterator reaches @p __last2, false is
                   *  returned.
                  */
                  template<typename _InputIterator1, typename _InputIterator2>
                    bool
                    includes(_InputIterator1 __first1, _InputIterator1 __last1,
                	     _InputIterator2 __first2, _InputIterator2 __last2)
                    {
                      typedef typename iterator_traits<_InputIterator1>::value_type
                	_ValueType1;
                      typedef typename iterator_traits<_InputIterator2>::value_type
                	_ValueType2;
                
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator2>)
                      __glibcxx_function_requires(_LessThanOpConcept<_ValueType1, _ValueType2>)
                      __glibcxx_function_requires(_LessThanOpConcept<_ValueType2, _ValueType1>)
                      __glibcxx_requires_sorted_set(__first1, __last1, __first2);
                      __glibcxx_requires_sorted_set(__first2, __last2, __first1);
                
                      while (__first1 != __last1 && __first2 != __last2)
                	if (*__first2 < *__first1)
                	  return false;
                	else if(*__first1 < *__first2)
                	  ++__first1;
                	else
                	  ++__first1, ++__first2;
                
                      return __first2 == __last2;
                    }
                
                  /**
                   *  @brief Determines whether all elements of a sequence exists in a range
                   *  using comparison.
                   *  @ingroup set_algorithms
                   *  @param  __first1  Start of search range.
                   *  @param  __last1   End of search range.
                   *  @param  __first2  Start of sequence
                   *  @param  __last2   End of sequence.
                   *  @param  __comp    Comparison function to use.
                   *  @return True if each element in [__first2,__last2) is contained
                   *  in order within [__first1,__last1) according to comp.  False
                   *  otherwise.  @ingroup set_algorithms
                   *
                   *  This operation expects both [__first1,__last1) and
                   *  [__first2,__last2) to be sorted.  Searches for the presence of
                   *  each element in [__first2,__last2) within [__first1,__last1),
                   *  using comp to decide.  The iterators over each range only move
                   *  forward, so this is a linear algorithm.  If an element in
                   *  [__first2,__last2) is not found before the search iterator
                   *  reaches @p __last2, false is returned.
                  */
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _Compare>
                    bool
                    includes(_InputIterator1 __first1, _InputIterator1 __last1,
                	     _InputIterator2 __first2, _InputIterator2 __last2,
                	     _Compare __comp)
                    {
                      typedef typename iterator_traits<_InputIterator1>::value_type
                	_ValueType1;
                      typedef typename iterator_traits<_InputIterator2>::value_type
                	_ValueType2;
                
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator2>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _ValueType1, _ValueType2>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _ValueType2, _ValueType1>)
                      __glibcxx_requires_sorted_set_pred(__first1, __last1, __first2, __comp);
                      __glibcxx_requires_sorted_set_pred(__first2, __last2, __first1, __comp);
                
                      while (__first1 != __last1 && __first2 != __last2)
                	if (__comp(*__first2, *__first1))
                	  return false;
                	else if(__comp(*__first1, *__first2))
                	  ++__first1;
                	else
                	  ++__first1, ++__first2;
                
                      return __first2 == __last2;
                    }
                
                  // nth_element
                  // merge
                  // set_difference
                  // set_intersection
                  // set_union
                  // stable_sort
                  // set_symmetric_difference
                  // min_element
                  // max_element
                
                  /**
                   *  @brief  Permute range into the next @e dictionary ordering.
                   *  @ingroup sorting_algorithms
                   *  @param  __first  Start of range.
                   *  @param  __last   End of range.
                   *  @return  False if wrapped to first permutation, true otherwise.
                   *
                   *  Treats all permutations of the range as a set of @e dictionary sorted
                   *  sequences.  Permutes the current sequence into the next one of this set.
                   *  Returns true if there are more sequences to generate.  If the sequence
                   *  is the largest of the set, the smallest is generated and false returned.
                  */
                  template<typename _BidirectionalIterator>
                    bool
                    next_permutation(_BidirectionalIterator __first,
                		     _BidirectionalIterator __last)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_BidirectionalIteratorConcept<
                				  _BidirectionalIterator>)
                      __glibcxx_function_requires(_LessThanComparableConcept<
                	    typename iterator_traits<_BidirectionalIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__first == __last)
                	return false;
                      _BidirectionalIterator __i = __first;
                      ++__i;
                      if (__i == __last)
                	return false;
                      __i = __last;
                      --__i;
                
                      for(;;)
                	{
                	  _BidirectionalIterator __ii = __i;
                	  --__i;
                	  if (*__i < *__ii)
                	    {
                	      _BidirectionalIterator __j = __last;
                	      while (!(*__i < *--__j))
                		{}
                	      std::iter_swap(__i, __j);
                	      std::reverse(__ii, __last);
                	      return true;
                	    }
                	  if (__i == __first)
                	    {
                	      std::reverse(__first, __last);
                	      return false;
                	    }
                	}
                    }
                
                  /**
                   *  @brief  Permute range into the next @e dictionary ordering using
                   *          comparison functor.
                   *  @ingroup sorting_algorithms
                   *  @param  __first  Start of range.
                   *  @param  __last   End of range.
                   *  @param  __comp   A comparison functor.
                   *  @return  False if wrapped to first permutation, true otherwise.
                   *
                   *  Treats all permutations of the range [__first,__last) as a set of
                   *  @e dictionary sorted sequences ordered by @p __comp.  Permutes the current
                   *  sequence into the next one of this set.  Returns true if there are more
                   *  sequences to generate.  If the sequence is the largest of the set, the
                   *  smallest is generated and false returned.
                  */
                  template<typename _BidirectionalIterator, typename _Compare>
                    bool
                    next_permutation(_BidirectionalIterator __first,
                		     _BidirectionalIterator __last, _Compare __comp)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_BidirectionalIteratorConcept<
                				  _BidirectionalIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                	    typename iterator_traits<_BidirectionalIterator>::value_type,
                	    typename iterator_traits<_BidirectionalIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__first == __last)
                	return false;
                      _BidirectionalIterator __i = __first;
                      ++__i;
                      if (__i == __last)
                	return false;
                      __i = __last;
                      --__i;
                
                      for(;;)
                	{
                	  _BidirectionalIterator __ii = __i;
                	  --__i;
                	  if (__comp(*__i, *__ii))
                	    {
                	      _BidirectionalIterator __j = __last;
                	      while (!bool(__comp(*__i, *--__j)))
                		{}
                	      std::iter_swap(__i, __j);
                	      std::reverse(__ii, __last);
                	      return true;
                	    }
                	  if (__i == __first)
                	    {
                	      std::reverse(__first, __last);
                	      return false;
                	    }
                	}
                    }
                
                  /**
                   *  @brief  Permute range into the previous @e dictionary ordering.
                   *  @ingroup sorting_algorithms
                   *  @param  __first  Start of range.
                   *  @param  __last   End of range.
                   *  @return  False if wrapped to last permutation, true otherwise.
                   *
                   *  Treats all permutations of the range as a set of @e dictionary sorted
                   *  sequences.  Permutes the current sequence into the previous one of this
                   *  set.  Returns true if there are more sequences to generate.  If the
                   *  sequence is the smallest of the set, the largest is generated and false
                   *  returned.
                  */
                  template<typename _BidirectionalIterator>
                    bool
                    prev_permutation(_BidirectionalIterator __first,
                		     _BidirectionalIterator __last)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_BidirectionalIteratorConcept<
                				  _BidirectionalIterator>)
                      __glibcxx_function_requires(_LessThanComparableConcept<
                	    typename iterator_traits<_BidirectionalIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__first == __last)
                	return false;
                      _BidirectionalIterator __i = __first;
                      ++__i;
                      if (__i == __last)
                	return false;
                      __i = __last;
                      --__i;
                
                      for(;;)
                	{
                	  _BidirectionalIterator __ii = __i;
                	  --__i;
                	  if (*__ii < *__i)
                	    {
                	      _BidirectionalIterator __j = __last;
                	      while (!(*--__j < *__i))
                		{}
                	      std::iter_swap(__i, __j);
                	      std::reverse(__ii, __last);
                	      return true;
                	    }
                	  if (__i == __first)
                	    {
                	      std::reverse(__first, __last);
                	      return false;
                	    }
                	}
                    }
                
                  /**
                   *  @brief  Permute range into the previous @e dictionary ordering using
                   *          comparison functor.
                   *  @ingroup sorting_algorithms
                   *  @param  __first  Start of range.
                   *  @param  __last   End of range.
                   *  @param  __comp   A comparison functor.
                   *  @return  False if wrapped to last permutation, true otherwise.
                   *
                   *  Treats all permutations of the range [__first,__last) as a set of
                   *  @e dictionary sorted sequences ordered by @p __comp.  Permutes the current
                   *  sequence into the previous one of this set.  Returns true if there are
                   *  more sequences to generate.  If the sequence is the smallest of the set,
                   *  the largest is generated and false returned.
                  */
                  template<typename _BidirectionalIterator, typename _Compare>
                    bool
                    prev_permutation(_BidirectionalIterator __first,
                		     _BidirectionalIterator __last, _Compare __comp)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_BidirectionalIteratorConcept<
                				  _BidirectionalIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                	    typename iterator_traits<_BidirectionalIterator>::value_type,
                	    typename iterator_traits<_BidirectionalIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__first == __last)
                	return false;
                      _BidirectionalIterator __i = __first;
                      ++__i;
                      if (__i == __last)
                	return false;
                      __i = __last;
                      --__i;
                
                      for(;;)
                	{
                	  _BidirectionalIterator __ii = __i;
                	  --__i;
                	  if (__comp(*__ii, *__i))
                	    {
                	      _BidirectionalIterator __j = __last;
                	      while (!bool(__comp(*--__j, *__i)))
                		{}
                	      std::iter_swap(__i, __j);
                	      std::reverse(__ii, __last);
                	      return true;
                	    }
                	  if (__i == __first)
                	    {
                	      std::reverse(__first, __last);
                	      return false;
                	    }
                	}
                    }
                
                  // replace
                  // replace_if
                
                  /**
                   *  @brief Copy a sequence, replacing each element of one value with another
                   *         value.
                   *  @param  __first      An input iterator.
                   *  @param  __last       An input iterator.
                   *  @param  __result     An output iterator.
                   *  @param  __old_value  The value to be replaced.
                   *  @param  __new_value  The replacement value.
                   *  @return   The end of the output sequence, @p result+(last-first).
                   *
                   *  Copies each element in the input range @p [__first,__last) to the
                   *  output range @p [__result,__result+(__last-__first)) replacing elements
                   *  equal to @p __old_value with @p __new_value.
                  */
                  template<typename _InputIterator, typename _OutputIterator, typename _Tp>
                    _OutputIterator
                    replace_copy(_InputIterator __first, _InputIterator __last,
                		 _OutputIterator __result,
                		 const _Tp& __old_value, const _Tp& __new_value)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                	    typename iterator_traits<_InputIterator>::value_type>)
                      __glibcxx_function_requires(_EqualOpConcept<
                	    typename iterator_traits<_InputIterator>::value_type, _Tp>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      for (; __first != __last; ++__first, ++__result)
                	if (*__first == __old_value)
                	  *__result = __new_value;
                	else
                	  *__result = *__first;
                      return __result;
                    }
                
                  /**
                   *  @brief Copy a sequence, replacing each value for which a predicate
                   *         returns true with another value.
                   *  @ingroup mutating_algorithms
                   *  @param  __first      An input iterator.
                   *  @param  __last       An input iterator.
                   *  @param  __result     An output iterator.
                   *  @param  __pred       A predicate.
                   *  @param  __new_value  The replacement value.
                   *  @return   The end of the output sequence, @p __result+(__last-__first).
                   *
                   *  Copies each element in the range @p [__first,__last) to the range
                   *  @p [__result,__result+(__last-__first)) replacing elements for which
                   *  @p __pred returns true with @p __new_value.
                  */
                  template<typename _InputIterator, typename _OutputIterator,
                	   typename _Predicate, typename _Tp>
                    _OutputIterator
                    replace_copy_if(_InputIterator __first, _InputIterator __last,
                		    _OutputIterator __result,
                		    _Predicate __pred, const _Tp& __new_value)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                	    typename iterator_traits<_InputIterator>::value_type>)
                      __glibcxx_function_requires(_UnaryPredicateConcept<_Predicate,
                	    typename iterator_traits<_InputIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      for (; __first != __last; ++__first, ++__result)
                	if (__pred(*__first))
                	  *__result = __new_value;
                	else
                	  *__result = *__first;
                      return __result;
                    }
                
                #if __cplusplus >= 201103L
                  /**
                   *  @brief  Determines whether the elements of a sequence are sorted.
                   *  @ingroup sorting_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @return  True if the elements are sorted, false otherwise.
                  */
                  template<typename _ForwardIterator>
                    inline bool
                    is_sorted(_ForwardIterator __first, _ForwardIterator __last)
                    { return std::is_sorted_until(__first, __last) == __last; }
                
                  /**
                   *  @brief  Determines whether the elements of a sequence are sorted
                   *          according to a comparison functor.
                   *  @ingroup sorting_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @param  __comp    A comparison functor.
                   *  @return  True if the elements are sorted, false otherwise.
                  */
                  template<typename _ForwardIterator, typename _Compare>
                    inline bool
                    is_sorted(_ForwardIterator __first, _ForwardIterator __last,
                	      _Compare __comp)
                    { return std::is_sorted_until(__first, __last, __comp) == __last; }
                
                  /**
                   *  @brief  Determines the end of a sorted sequence.
                   *  @ingroup sorting_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @return  An iterator pointing to the last iterator i in [__first, __last)
                   *           for which the range [__first, i) is sorted.
                  */
                  template<typename _ForwardIterator>
                    _ForwardIterator
                    is_sorted_until(_ForwardIterator __first, _ForwardIterator __last)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_LessThanComparableConcept<
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__first == __last)
                	return __last;
                
                      _ForwardIterator __next = __first;
                      for (++__next; __next != __last; __first = __next, ++__next)
                	if (*__next < *__first)
                	  return __next;
                      return __next;
                    }
                
                  /**
                   *  @brief  Determines the end of a sorted sequence using comparison functor.
                   *  @ingroup sorting_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @param  __comp    A comparison functor.
                   *  @return  An iterator pointing to the last iterator i in [__first, __last)
                   *           for which the range [__first, i) is sorted.
                  */
                  template<typename _ForwardIterator, typename _Compare>
                    _ForwardIterator
                    is_sorted_until(_ForwardIterator __first, _ForwardIterator __last,
                		    _Compare __comp)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                	    typename iterator_traits<_ForwardIterator>::value_type,
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__first == __last)
                	return __last;
                
                      _ForwardIterator __next = __first;
                      for (++__next; __next != __last; __first = __next, ++__next)
                	if (__comp(*__next, *__first))
                	  return __next;
                      return __next;
                    }
                
                  /**
                   *  @brief  Determines min and max at once as an ordered pair.
                   *  @ingroup sorting_algorithms
                   *  @param  __a  A thing of arbitrary type.
                   *  @param  __b  Another thing of arbitrary type.
                   *  @return A pair(__b, __a) if __b is smaller than __a, pair(__a,
                   *  __b) otherwise.
                  */
                  template<typename _Tp>
                    inline pair<const _Tp&, const _Tp&>
                    minmax(const _Tp& __a, const _Tp& __b)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_LessThanComparableConcept<_Tp>)
                
                      return __b < __a ? pair<const _Tp&, const _Tp&>(__b, __a)
                	               : pair<const _Tp&, const _Tp&>(__a, __b);
                    }
                
                  /**
                   *  @brief  Determines min and max at once as an ordered pair.
                   *  @ingroup sorting_algorithms
                   *  @param  __a  A thing of arbitrary type.
                   *  @param  __b  Another thing of arbitrary type.
                   *  @param  __comp  A @link comparison_functors comparison functor @endlink.
                   *  @return A pair(__b, __a) if __b is smaller than __a, pair(__a,
                   *  __b) otherwise.
                  */
                  template<typename _Tp, typename _Compare>
                    inline pair<const _Tp&, const _Tp&>
                    minmax(const _Tp& __a, const _Tp& __b, _Compare __comp)
                    {
                      return __comp(__b, __a) ? pair<const _Tp&, const _Tp&>(__b, __a)
                	                      : pair<const _Tp&, const _Tp&>(__a, __b);
                    }
                
                  /**
                   *  @brief  Return a pair of iterators pointing to the minimum and maximum
                   *          elements in a range.
                   *  @ingroup sorting_algorithms
                   *  @param  __first  Start of range.
                   *  @param  __last   End of range.
                   *  @return  make_pair(m, M), where m is the first iterator i in 
                   *           [__first, __last) such that no other element in the range is
                   *           smaller, and where M is the last iterator i in [__first, __last)
                   *           such that no other element in the range is larger.
                  */
                  template<typename _ForwardIterator>
                    pair<_ForwardIterator, _ForwardIterator>
                    minmax_element(_ForwardIterator __first, _ForwardIterator __last)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_LessThanComparableConcept<
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      _ForwardIterator __next = __first;
                      if (__first == __last
                	  || ++__next == __last)
                	return std::make_pair(__first, __first);
                
                      _ForwardIterator __min, __max;
                      if (*__next < *__first)
                	{
                	  __min = __next;
                	  __max = __first;
                	}
                      else
                	{
                	  __min = __first;
                	  __max = __next;
                	}
                
                      __first = __next;
                      ++__first;
                
                      while (__first != __last)
                	{
                	  __next = __first;
                	  if (++__next == __last)
                	    {
                	      if (*__first < *__min)
                		__min = __first;
                	      else if (!(*__first < *__max))
                		__max = __first;
                	      break;
                	    }
                
                	  if (*__next < *__first)
                	    {
                	      if (*__next < *__min)
                		__min = __next;
                	      if (!(*__first < *__max))
                		__max = __first;
                	    }
                	  else
                	    {
                	      if (*__first < *__min)
                		__min = __first;
                	      if (!(*__next < *__max))
                		__max = __next;
                	    }
                
                	  __first = __next;
                	  ++__first;
                	}
                
                      return std::make_pair(__min, __max);
                    }
                
                  /**
                   *  @brief  Return a pair of iterators pointing to the minimum and maximum
                   *          elements in a range.
                   *  @ingroup sorting_algorithms
                   *  @param  __first  Start of range.
                   *  @param  __last   End of range.
                   *  @param  __comp   Comparison functor.
                   *  @return  make_pair(m, M), where m is the first iterator i in 
                   *           [__first, __last) such that no other element in the range is
                   *           smaller, and where M is the last iterator i in [__first, __last)
                   *           such that no other element in the range is larger.
                  */
                  template<typename _ForwardIterator, typename _Compare>
                    pair<_ForwardIterator, _ForwardIterator>
                    minmax_element(_ForwardIterator __first, _ForwardIterator __last,
                		   _Compare __comp)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                	    typename iterator_traits<_ForwardIterator>::value_type,
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      _ForwardIterator __next = __first;
                      if (__first == __last
                	  || ++__next == __last)
                	return std::make_pair(__first, __first);
                
                      _ForwardIterator __min, __max;
                      if (__comp(*__next, *__first))
                	{
                	  __min = __next;
                	  __max = __first;
                	}
                      else
                	{
                	  __min = __first;
                	  __max = __next;
                	}
                
                      __first = __next;
                      ++__first;
                
                      while (__first != __last)
                	{
                	  __next = __first;
                	  if (++__next == __last)
                	    {
                	      if (__comp(*__first, *__min))
                		__min = __first;
                	      else if (!__comp(*__first, *__max))
                		__max = __first;
                	      break;
                	    }
                
                	  if (__comp(*__next, *__first))
                	    {
                	      if (__comp(*__next, *__min))
                		__min = __next;
                	      if (!__comp(*__first, *__max))
                		__max = __first;
                	    }
                	  else
                	    {
                	      if (__comp(*__first, *__min))
                		__min = __first;
                	      if (!__comp(*__next, *__max))
                		__max = __next;
                	    }
                
                	  __first = __next;
                	  ++__first;
                	}
                
                      return std::make_pair(__min, __max);
                    }
                
                  // N2722 + DR 915.
                  template<typename _Tp>
                    inline _Tp
                    min(initializer_list<_Tp> __l)
                    { return *std::min_element(__l.begin(), __l.end()); }
                
                  template<typename _Tp, typename _Compare>
                    inline _Tp
                    min(initializer_list<_Tp> __l, _Compare __comp)
                    { return *std::min_element(__l.begin(), __l.end(), __comp); }
                
                  template<typename _Tp>
                    inline _Tp
                    max(initializer_list<_Tp> __l)
                    { return *std::max_element(__l.begin(), __l.end()); }
                
                  template<typename _Tp, typename _Compare>
                    inline _Tp
                    max(initializer_list<_Tp> __l, _Compare __comp)
                    { return *std::max_element(__l.begin(), __l.end(), __comp); }
                
                  template<typename _Tp>
                    inline pair<_Tp, _Tp>
                    minmax(initializer_list<_Tp> __l)
                    {
                      pair<const _Tp*, const _Tp*> __p =
                	std::minmax_element(__l.begin(), __l.end());
                      return std::make_pair(*__p.first, *__p.second);
                    }
                
                  template<typename _Tp, typename _Compare>
                    inline pair<_Tp, _Tp>
                    minmax(initializer_list<_Tp> __l, _Compare __comp)
                    {
                      pair<const _Tp*, const _Tp*> __p =
                	std::minmax_element(__l.begin(), __l.end(), __comp);
                      return std::make_pair(*__p.first, *__p.second);
                    }
                
                  /**
                   *  @brief  Checks whether a permutaion of the second sequence is equal
                   *          to the first sequence.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first1  Start of first range.
                   *  @param  __last1   End of first range.
                   *  @param  __first2  Start of second range.
                   *  @return true if there exists a permutation of the elements in the range
                   *          [__first2, __first2 + (__last1 - __first1)), beginning with 
                   *          ForwardIterator2 begin, such that equal(__first1, __last1, begin)
                   *          returns true; otherwise, returns false.
                  */
                  template<typename _ForwardIterator1, typename _ForwardIterator2>
                    bool
                    is_permutation(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                		   _ForwardIterator2 __first2)
                    {
                      // Efficiently compare identical prefixes:  O(N) if sequences
                      // have the same elements in the same order.
                      for (; __first1 != __last1; ++__first1, ++__first2)
                	if (!(*__first1 == *__first2))
                	  break;
                
                      if (__first1 == __last1)
                	return true;
                
                      // Establish __last2 assuming equal ranges by iterating over the
                      // rest of the list.
                      _ForwardIterator2 __last2 = __first2;
                      std::advance(__last2, std::distance(__first1, __last1));
                      for (_ForwardIterator1 __scan = __first1; __scan != __last1; ++__scan)
                	{
                	  if (__scan != _GLIBCXX_STD_A::find(__first1, __scan, *__scan))
                	    continue; // We've seen this one before.
                
                	  auto __matches = std::count(__first2, __last2, *__scan);
                	  if (0 == __matches
                	      || std::count(__scan, __last1, *__scan) != __matches)
                	    return false;
                	}
                      return true;
                    }
                
                  /**
                   *  @brief  Checks whether a permutation of the second sequence is equal
                   *          to the first sequence.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first1  Start of first range.
                   *  @param  __last1   End of first range.
                   *  @param  __first2  Start of second range.
                   *  @param  __pred    A binary predicate.
                   *  @return true if there exists a permutation of the elements in
                   *          the range [__first2, __first2 + (__last1 - __first1)),
                   *          beginning with ForwardIterator2 begin, such that
                   *          equal(__first1, __last1, __begin, __pred) returns true;
                   *          otherwise, returns false.
                  */
                  template<typename _ForwardIterator1, typename _ForwardIterator2,
                	   typename _BinaryPredicate>
                    bool
                    is_permutation(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                		   _ForwardIterator2 __first2, _BinaryPredicate __pred)
                    {
                      // Efficiently compare identical prefixes:  O(N) if sequences
                      // have the same elements in the same order.
                      for (; __first1 != __last1; ++__first1, ++__first2)
                	if (!bool(__pred(*__first1, *__first2)))
                	  break;
                
                      if (__first1 == __last1)
                	return true;
                
                      // Establish __last2 assuming equal ranges by iterating over the
                      // rest of the list.
                      _ForwardIterator2 __last2 = __first2;
                      std::advance(__last2, std::distance(__first1, __last1));
                      for (_ForwardIterator1 __scan = __first1; __scan != __last1; ++__scan)
                	{
                	  using std::placeholders::_1;
                
                	  if (__scan != _GLIBCXX_STD_A::find_if(__first1, __scan,
                						std::bind(__pred, _1, *__scan)))
                	    continue; // We've seen this one before.
                	  
                	  auto __matches = std::count_if(__first2, __last2,
                					 std::bind(__pred, _1, *__scan));
                	  if (0 == __matches
                	      || std::count_if(__scan, __last1,
                			       std::bind(__pred, _1, *__scan)) != __matches)
                	    return false;
                	}
                      return true;
                    }
                
                #ifdef _GLIBCXX_USE_C99_STDINT_TR1
                  /**
                   *  @brief Shuffle the elements of a sequence using a uniform random
                   *         number generator.
                   *  @ingroup mutating_algorithms
                   *  @param  __first   A forward iterator.
                   *  @param  __last    A forward iterator.
                   *  @param  __g       A UniformRandomNumberGenerator (26.5.1.3).
                   *  @return  Nothing.
                   *
                   *  Reorders the elements in the range @p [__first,__last) using @p __g to
                   *  provide random numbers.
                  */
                  template<typename _RandomAccessIterator,
                	   typename _UniformRandomNumberGenerator>
                    void
                    shuffle(_RandomAccessIterator __first, _RandomAccessIterator __last,
                	    _UniformRandomNumberGenerator&& __g)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_RandomAccessIteratorConcept<
                	    _RandomAccessIterator>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__first == __last)
                	return;
                
                      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
                	_DistanceType;
                
                      typedef typename std::make_unsigned<_DistanceType>::type __ud_type;
                      typedef typename std::uniform_int_distribution<__ud_type> __distr_type;
                      typedef typename __distr_type::param_type __p_type;
                      __distr_type __d;
                
                      for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
                	std::iter_swap(__i, __first + __d(__g, __p_type(0, __i - __first)));
                    }
                #endif
                
                #endif // C++11
                
                _GLIBCXX_END_NAMESPACE_VERSION
                
                _GLIBCXX_BEGIN_NAMESPACE_ALGO
                
                  /**
                   *  @brief Apply a function to every element of a sequence.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first  An input iterator.
                   *  @param  __last   An input iterator.
                   *  @param  __f      A unary function object.
                   *  @return   @p __f (std::move(@p __f) in C++0x).
                   *
                   *  Applies the function object @p __f to each element in the range
                   *  @p [first,last).  @p __f must not modify the order of the sequence.
                   *  If @p __f has a return value it is ignored.
                  */
                  template<typename _InputIterator, typename _Function>
                    _Function
                    for_each(_InputIterator __first, _InputIterator __last, _Function __f)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_requires_valid_range(__first, __last);
                      for (; __first != __last; ++__first)
                	__f(*__first);
                      return _GLIBCXX_MOVE(__f);
                    }
                
                  /**
                   *  @brief Find the first occurrence of a value in a sequence.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first  An input iterator.
                   *  @param  __last   An input iterator.
                   *  @param  __val    The value to find.
                   *  @return   The first iterator @c i in the range @p [__first,__last)
                   *  such that @c *i == @p __val, or @p __last if no such iterator exists.
                  */
                  template<typename _InputIterator, typename _Tp>
                    inline _InputIterator
    26080000 ->     find(_InputIterator __first, _InputIterator __last,
                	 const _Tp& __val)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_EqualOpConcept<
                		typename iterator_traits<_InputIterator>::value_type, _Tp>)
                      __glibcxx_requires_valid_range(__first, __last);
                      return std::__find(__first, __last, __val,
    26080000 -> 		         std::__iterator_category(__first));
    26080000 ->     }
                
                  /**
                   *  @brief Find the first element in a sequence for which a
                   *         predicate is true.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first  An input iterator.
                   *  @param  __last   An input iterator.
                   *  @param  __pred   A predicate.
                   *  @return   The first iterator @c i in the range @p [__first,__last)
                   *  such that @p __pred(*i) is true, or @p __last if no such iterator exists.
                  */
                  template<typename _InputIterator, typename _Predicate>
                    inline _InputIterator
                    find_if(_InputIterator __first, _InputIterator __last,
                	    _Predicate __pred)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_UnaryPredicateConcept<_Predicate,
                	      typename iterator_traits<_InputIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                      return std::__find_if(__first, __last, __pred,
                			    std::__iterator_category(__first));
                    }
                
                  /**
                   *  @brief  Find element from a set in a sequence.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first1  Start of range to search.
                   *  @param  __last1   End of range to search.
                   *  @param  __first2  Start of match candidates.
                   *  @param  __last2   End of match candidates.
                   *  @return   The first iterator @c i in the range
                   *  @p [__first1,__last1) such that @c *i == @p *(i2) such that i2 is an
                   *  iterator in [__first2,__last2), or @p __last1 if no such iterator exists.
                   *
                   *  Searches the range @p [__first1,__last1) for an element that is
                   *  equal to some element in the range [__first2,__last2).  If
                   *  found, returns an iterator in the range [__first1,__last1),
                   *  otherwise returns @p __last1.
                  */
                  template<typename _InputIterator, typename _ForwardIterator>
                    _InputIterator
                    find_first_of(_InputIterator __first1, _InputIterator __last1,
                		  _ForwardIterator __first2, _ForwardIterator __last2)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_EqualOpConcept<
                	    typename iterator_traits<_InputIterator>::value_type,
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first1, __last1);
                      __glibcxx_requires_valid_range(__first2, __last2);
                
                      for (; __first1 != __last1; ++__first1)
                	for (_ForwardIterator __iter = __first2; __iter != __last2; ++__iter)
                	  if (*__first1 == *__iter)
                	    return __first1;
                      return __last1;
                    }
                
                  /**
                   *  @brief  Find element from a set in a sequence using a predicate.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first1  Start of range to search.
                   *  @param  __last1   End of range to search.
                   *  @param  __first2  Start of match candidates.
                   *  @param  __last2   End of match candidates.
                   *  @param  __comp    Predicate to use.
                   *  @return   The first iterator @c i in the range
                   *  @p [__first1,__last1) such that @c comp(*i, @p *(i2)) is true
                   *  and i2 is an iterator in [__first2,__last2), or @p __last1 if no
                   *  such iterator exists.
                   *
                
                   *  Searches the range @p [__first1,__last1) for an element that is
                   *  equal to some element in the range [__first2,__last2).  If
                   *  found, returns an iterator in the range [__first1,__last1),
                   *  otherwise returns @p __last1.
                  */
                  template<typename _InputIterator, typename _ForwardIterator,
                	   typename _BinaryPredicate>
                    _InputIterator
                    find_first_of(_InputIterator __first1, _InputIterator __last1,
                		  _ForwardIterator __first2, _ForwardIterator __last2,
                		  _BinaryPredicate __comp)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_BinaryPredicate,
                	    typename iterator_traits<_InputIterator>::value_type,
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first1, __last1);
                      __glibcxx_requires_valid_range(__first2, __last2);
                
                      for (; __first1 != __last1; ++__first1)
                	for (_ForwardIterator __iter = __first2; __iter != __last2; ++__iter)
                	  if (__comp(*__first1, *__iter))
                	    return __first1;
                      return __last1;
                    }
                
                  /**
                   *  @brief Find two adjacent values in a sequence that are equal.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first  A forward iterator.
                   *  @param  __last   A forward iterator.
                   *  @return   The first iterator @c i such that @c i and @c i+1 are both
                   *  valid iterators in @p [__first,__last) and such that @c *i == @c *(i+1),
                   *  or @p __last if no such iterator exists.
                  */
                  template<typename _ForwardIterator>
                    _ForwardIterator
                    adjacent_find(_ForwardIterator __first, _ForwardIterator __last)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_EqualityComparableConcept<
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                      if (__first == __last)
                	return __last;
                      _ForwardIterator __next = __first;
                      while(++__next != __last)
                	{
                	  if (*__first == *__next)
                	    return __first;
                	  __first = __next;
                	}
                      return __last;
                    }
                
                  /**
                   *  @brief Find two adjacent values in a sequence using a predicate.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first         A forward iterator.
                   *  @param  __last          A forward iterator.
                   *  @param  __binary_pred   A binary predicate.
                   *  @return   The first iterator @c i such that @c i and @c i+1 are both
                   *  valid iterators in @p [__first,__last) and such that
                   *  @p __binary_pred(*i,*(i+1)) is true, or @p __last if no such iterator
                   *  exists.
                  */
                  template<typename _ForwardIterator, typename _BinaryPredicate>
                    _ForwardIterator
                    adjacent_find(_ForwardIterator __first, _ForwardIterator __last,
                		  _BinaryPredicate __binary_pred)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_BinaryPredicate,
                	    typename iterator_traits<_ForwardIterator>::value_type,
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                      if (__first == __last)
                	return __last;
                      _ForwardIterator __next = __first;
                      while(++__next != __last)
                	{
                	  if (__binary_pred(*__first, *__next))
                	    return __first;
                	  __first = __next;
                	}
                      return __last;
                    }
                
                  /**
                   *  @brief Count the number of copies of a value in a sequence.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first  An input iterator.
                   *  @param  __last   An input iterator.
                   *  @param  __value  The value to be counted.
                   *  @return   The number of iterators @c i in the range @p [__first,__last)
                   *  for which @c *i == @p __value
                  */
                  template<typename _InputIterator, typename _Tp>
                    typename iterator_traits<_InputIterator>::difference_type
                    count(_InputIterator __first, _InputIterator __last, const _Tp& __value)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_EqualOpConcept<
                	typename iterator_traits<_InputIterator>::value_type, _Tp>)
                      __glibcxx_requires_valid_range(__first, __last);
                      typename iterator_traits<_InputIterator>::difference_type __n = 0;
                      for (; __first != __last; ++__first)
                	if (*__first == __value)
                	  ++__n;
                      return __n;
                    }
                
                  /**
                   *  @brief Count the elements of a sequence for which a predicate is true.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first  An input iterator.
                   *  @param  __last   An input iterator.
                   *  @param  __pred   A predicate.
                   *  @return   The number of iterators @c i in the range @p [__first,__last)
                   *  for which @p __pred(*i) is true.
                  */
                  template<typename _InputIterator, typename _Predicate>
                    typename iterator_traits<_InputIterator>::difference_type
                    count_if(_InputIterator __first, _InputIterator __last, _Predicate __pred)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_UnaryPredicateConcept<_Predicate,
                	    typename iterator_traits<_InputIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                      typename iterator_traits<_InputIterator>::difference_type __n = 0;
                      for (; __first != __last; ++__first)
                	if (__pred(*__first))
                	  ++__n;
                      return __n;
                    }
                
                  /**
                   *  @brief Search a sequence for a matching sub-sequence.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first1  A forward iterator.
                   *  @param  __last1   A forward iterator.
                   *  @param  __first2  A forward iterator.
                   *  @param  __last2   A forward iterator.
                   *  @return The first iterator @c i in the range @p
                   *  [__first1,__last1-(__last2-__first2)) such that @c *(i+N) == @p
                   *  *(__first2+N) for each @c N in the range @p
                   *  [0,__last2-__first2), or @p __last1 if no such iterator exists.
                   *
                   *  Searches the range @p [__first1,__last1) for a sub-sequence that
                   *  compares equal value-by-value with the sequence given by @p
                   *  [__first2,__last2) and returns an iterator to the first element
                   *  of the sub-sequence, or @p __last1 if the sub-sequence is not
                   *  found.
                   *
                   *  Because the sub-sequence must lie completely within the range @p
                   *  [__first1,__last1) it must start at a position less than @p
                   *  __last1-(__last2-__first2) where @p __last2-__first2 is the
                   *  length of the sub-sequence.
                   *
                   *  This means that the returned iterator @c i will be in the range
                   *  @p [__first1,__last1-(__last2-__first2))
                  */
                  template<typename _ForwardIterator1, typename _ForwardIterator2>
                    _ForwardIterator1
                    search(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                	   _ForwardIterator2 __first2, _ForwardIterator2 __last2)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator1>)
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator2>)
                      __glibcxx_function_requires(_EqualOpConcept<
                	    typename iterator_traits<_ForwardIterator1>::value_type,
                	    typename iterator_traits<_ForwardIterator2>::value_type>)
                      __glibcxx_requires_valid_range(__first1, __last1);
                      __glibcxx_requires_valid_range(__first2, __last2);
                
                      // Test for empty ranges
                      if (__first1 == __last1 || __first2 == __last2)
                	return __first1;
                
                      // Test for a pattern of length 1.
                      _ForwardIterator2 __p1(__first2);
                      if (++__p1 == __last2)
                	return _GLIBCXX_STD_A::find(__first1, __last1, *__first2);
                
                      // General case.
                      _ForwardIterator2 __p;
                      _ForwardIterator1 __current = __first1;
                
                      for (;;)
                	{
                	  __first1 = _GLIBCXX_STD_A::find(__first1, __last1, *__first2);
                	  if (__first1 == __last1)
                	    return __last1;
                
                	  __p = __p1;
                	  __current = __first1;
                	  if (++__current == __last1)
                	    return __last1;
                
                	  while (*__current == *__p)
                	    {
                	      if (++__p == __last2)
                		return __first1;
                	      if (++__current == __last1)
                		return __last1;
                	    }
                	  ++__first1;
                	}
                      return __first1;
                    }
                
                  /**
                   *  @brief Search a sequence for a matching sub-sequence using a predicate.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first1     A forward iterator.
                   *  @param  __last1      A forward iterator.
                   *  @param  __first2     A forward iterator.
                   *  @param  __last2      A forward iterator.
                   *  @param  __predicate  A binary predicate.
                   *  @return   The first iterator @c i in the range
                   *  @p [__first1,__last1-(__last2-__first2)) such that
                   *  @p __predicate(*(i+N),*(__first2+N)) is true for each @c N in the range
                   *  @p [0,__last2-__first2), or @p __last1 if no such iterator exists.
                   *
                   *  Searches the range @p [__first1,__last1) for a sub-sequence that
                   *  compares equal value-by-value with the sequence given by @p
                   *  [__first2,__last2), using @p __predicate to determine equality,
                   *  and returns an iterator to the first element of the
                   *  sub-sequence, or @p __last1 if no such iterator exists.
                   *
                   *  @see search(_ForwardIter1, _ForwardIter1, _ForwardIter2, _ForwardIter2)
                  */
                  template<typename _ForwardIterator1, typename _ForwardIterator2,
                	   typename _BinaryPredicate>
                    _ForwardIterator1
                    search(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                	   _ForwardIterator2 __first2, _ForwardIterator2 __last2,
                	   _BinaryPredicate  __predicate)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator1>)
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator2>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_BinaryPredicate,
                	    typename iterator_traits<_ForwardIterator1>::value_type,
                	    typename iterator_traits<_ForwardIterator2>::value_type>)
                      __glibcxx_requires_valid_range(__first1, __last1);
                      __glibcxx_requires_valid_range(__first2, __last2);
                
                      // Test for empty ranges
                      if (__first1 == __last1 || __first2 == __last2)
                	return __first1;
                
                      // Test for a pattern of length 1.
                      _ForwardIterator2 __p1(__first2);
                      if (++__p1 == __last2)
                	{
                	  while (__first1 != __last1
                		 && !bool(__predicate(*__first1, *__first2)))
                	    ++__first1;
                	  return __first1;
                	}
                
                      // General case.
                      _ForwardIterator2 __p;
                      _ForwardIterator1 __current = __first1;
                
                      for (;;)
                	{
                	  while (__first1 != __last1
                		 && !bool(__predicate(*__first1, *__first2)))
                	    ++__first1;
                	  if (__first1 == __last1)
                	    return __last1;
                
                	  __p = __p1;
                	  __current = __first1;
                	  if (++__current == __last1)
                	    return __last1;
                
                	  while (__predicate(*__current, *__p))
                	    {
                	      if (++__p == __last2)
                		return __first1;
                	      if (++__current == __last1)
                		return __last1;
                	    }
                	  ++__first1;
                	}
                      return __first1;
                    }
                
                
                  /**
                   *  @brief Search a sequence for a number of consecutive values.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first  A forward iterator.
                   *  @param  __last   A forward iterator.
                   *  @param  __count  The number of consecutive values.
                   *  @param  __val    The value to find.
                   *  @return The first iterator @c i in the range @p
                   *  [__first,__last-__count) such that @c *(i+N) == @p __val for
                   *  each @c N in the range @p [0,__count), or @p __last if no such
                   *  iterator exists.
                   *
                   *  Searches the range @p [__first,__last) for @p count consecutive elements
                   *  equal to @p __val.
                  */
                  template<typename _ForwardIterator, typename _Integer, typename _Tp>
                    _ForwardIterator
                    search_n(_ForwardIterator __first, _ForwardIterator __last,
                	     _Integer __count, const _Tp& __val)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_EqualOpConcept<
                	typename iterator_traits<_ForwardIterator>::value_type, _Tp>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__count <= 0)
                	return __first;
                      if (__count == 1)
                	return _GLIBCXX_STD_A::find(__first, __last, __val);
                      return std::__search_n(__first, __last, __count, __val,
                			     std::__iterator_category(__first));
                    }
                
                
                  /**
                   *  @brief Search a sequence for a number of consecutive values using a
                   *         predicate.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first        A forward iterator.
                   *  @param  __last         A forward iterator.
                   *  @param  __count        The number of consecutive values.
                   *  @param  __val          The value to find.
                   *  @param  __binary_pred  A binary predicate.
                   *  @return The first iterator @c i in the range @p
                   *  [__first,__last-__count) such that @p
                   *  __binary_pred(*(i+N),__val) is true for each @c N in the range
                   *  @p [0,__count), or @p __last if no such iterator exists.
                   *
                   *  Searches the range @p [__first,__last) for @p __count
                   *  consecutive elements for which the predicate returns true.
                  */
                  template<typename _ForwardIterator, typename _Integer, typename _Tp,
                           typename _BinaryPredicate>
                    _ForwardIterator
                    search_n(_ForwardIterator __first, _ForwardIterator __last,
                	     _Integer __count, const _Tp& __val,
                	     _BinaryPredicate __binary_pred)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_BinaryPredicate,
                	    typename iterator_traits<_ForwardIterator>::value_type, _Tp>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__count <= 0)
                	return __first;
                      if (__count == 1)
                	{
                	  while (__first != __last && !bool(__binary_pred(*__first, __val)))
                	    ++__first;
                	  return __first;
                	}
                      return std::__search_n(__first, __last, __count, __val, __binary_pred,
                			     std::__iterator_category(__first));
                    }
                
                
                  /**
                   *  @brief Perform an operation on a sequence.
                   *  @ingroup mutating_algorithms
                   *  @param  __first     An input iterator.
                   *  @param  __last      An input iterator.
                   *  @param  __result    An output iterator.
                   *  @param  __unary_op  A unary operator.
                   *  @return   An output iterator equal to @p __result+(__last-__first).
                   *
                   *  Applies the operator to each element in the input range and assigns
                   *  the results to successive elements of the output sequence.
                   *  Evaluates @p *(__result+N)=unary_op(*(__first+N)) for each @c N in the
                   *  range @p [0,__last-__first).
                   *
                   *  @p unary_op must not alter its argument.
                  */
                  template<typename _InputIterator, typename _OutputIterator,
                	   typename _UnaryOperation>
                    _OutputIterator
                    transform(_InputIterator __first, _InputIterator __last,
                	      _OutputIterator __result, _UnaryOperation __unary_op)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                            // "the type returned by a _UnaryOperation"
                            __typeof__(__unary_op(*__first))>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      for (; __first != __last; ++__first, ++__result)
                	*__result = __unary_op(*__first);
                      return __result;
                    }
                
                  /**
                   *  @brief Perform an operation on corresponding elements of two sequences.
                   *  @ingroup mutating_algorithms
                   *  @param  __first1     An input iterator.
                   *  @param  __last1      An input iterator.
                   *  @param  __first2     An input iterator.
                   *  @param  __result     An output iterator.
                   *  @param  __binary_op  A binary operator.
                   *  @return   An output iterator equal to @p result+(last-first).
                   *
                   *  Applies the operator to the corresponding elements in the two
                   *  input ranges and assigns the results to successive elements of the
                   *  output sequence.
                   *  Evaluates @p
                   *  *(__result+N)=__binary_op(*(__first1+N),*(__first2+N)) for each
                   *  @c N in the range @p [0,__last1-__first1).
                   *
                   *  @p binary_op must not alter either of its arguments.
                  */
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _OutputIterator, typename _BinaryOperation>
                    _OutputIterator
                    transform(_InputIterator1 __first1, _InputIterator1 __last1,
                	      _InputIterator2 __first2, _OutputIterator __result,
                	      _BinaryOperation __binary_op)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator2>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                            // "the type returned by a _BinaryOperation"
                            __typeof__(__binary_op(*__first1,*__first2))>)
                      __glibcxx_requires_valid_range(__first1, __last1);
                
                      for (; __first1 != __last1; ++__first1, ++__first2, ++__result)
                	*__result = __binary_op(*__first1, *__first2);
                      return __result;
                    }
                
                  /**
                   *  @brief Replace each occurrence of one value in a sequence with another
                   *         value.
                   *  @ingroup mutating_algorithms
                   *  @param  __first      A forward iterator.
                   *  @param  __last       A forward iterator.
                   *  @param  __old_value  The value to be replaced.
                   *  @param  __new_value  The replacement value.
                   *  @return   replace() returns no value.
                   *
                   *  For each iterator @c i in the range @p [__first,__last) if @c *i ==
                   *  @p __old_value then the assignment @c *i = @p __new_value is performed.
                  */
                  template<typename _ForwardIterator, typename _Tp>
                    void
                    replace(_ForwardIterator __first, _ForwardIterator __last,
                	    const _Tp& __old_value, const _Tp& __new_value)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<
                				  _ForwardIterator>)
                      __glibcxx_function_requires(_EqualOpConcept<
                	    typename iterator_traits<_ForwardIterator>::value_type, _Tp>)
                      __glibcxx_function_requires(_ConvertibleConcept<_Tp,
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      for (; __first != __last; ++__first)
                	if (*__first == __old_value)
                	  *__first = __new_value;
                    }
                
                  /**
                   *  @brief Replace each value in a sequence for which a predicate returns
                   *         true with another value.
                   *  @ingroup mutating_algorithms
                   *  @param  __first      A forward iterator.
                   *  @param  __last       A forward iterator.
                   *  @param  __pred       A predicate.
                   *  @param  __new_value  The replacement value.
                   *  @return   replace_if() returns no value.
                   *
                   *  For each iterator @c i in the range @p [__first,__last) if @p __pred(*i)
                   *  is true then the assignment @c *i = @p __new_value is performed.
                  */
                  template<typename _ForwardIterator, typename _Predicate, typename _Tp>
                    void
                    replace_if(_ForwardIterator __first, _ForwardIterator __last,
                	       _Predicate __pred, const _Tp& __new_value)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<
                				  _ForwardIterator>)
                      __glibcxx_function_requires(_ConvertibleConcept<_Tp,
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_function_requires(_UnaryPredicateConcept<_Predicate,
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      for (; __first != __last; ++__first)
                	if (__pred(*__first))
                	  *__first = __new_value;
                    }
                
                  /**
                   *  @brief Assign the result of a function object to each value in a
                   *         sequence.
                   *  @ingroup mutating_algorithms
                   *  @param  __first  A forward iterator.
                   *  @param  __last   A forward iterator.
                   *  @param  __gen    A function object taking no arguments and returning
                   *                 std::iterator_traits<_ForwardIterator>::value_type
                   *  @return   generate() returns no value.
                   *
                   *  Performs the assignment @c *i = @p __gen() for each @c i in the range
                   *  @p [__first,__last).
                  */
                  template<typename _ForwardIterator, typename _Generator>
                    void
                    generate(_ForwardIterator __first, _ForwardIterator __last,
                	     _Generator __gen)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_GeneratorConcept<_Generator,
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      for (; __first != __last; ++__first)
                	*__first = __gen();
                    }
                
                  /**
                   *  @brief Assign the result of a function object to each value in a
                   *         sequence.
                   *  @ingroup mutating_algorithms
                   *  @param  __first  A forward iterator.
                   *  @param  __n      The length of the sequence.
                   *  @param  __gen    A function object taking no arguments and returning
                   *                 std::iterator_traits<_ForwardIterator>::value_type
                   *  @return   The end of the sequence, @p __first+__n
                   *
                   *  Performs the assignment @c *i = @p __gen() for each @c i in the range
                   *  @p [__first,__first+__n).
                   *
                   *  _GLIBCXX_RESOLVE_LIB_DEFECTS
                   *  DR 865. More algorithms that throw away information
                  */
                  template<typename _OutputIterator, typename _Size, typename _Generator>
                    _OutputIterator
                    generate_n(_OutputIterator __first, _Size __n, _Generator __gen)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                            // "the type returned by a _Generator"
                            __typeof__(__gen())>)
                
                      for (__decltype(__n + 0) __niter = __n;
                	   __niter > 0; --__niter, ++__first)
                	*__first = __gen();
                      return __first;
                    }
                
                
                  /**
                   *  @brief Copy a sequence, removing consecutive duplicate values.
                   *  @ingroup mutating_algorithms
                   *  @param  __first   An input iterator.
                   *  @param  __last    An input iterator.
                   *  @param  __result  An output iterator.
                   *  @return   An iterator designating the end of the resulting sequence.
                   *
                   *  Copies each element in the range @p [__first,__last) to the range
                   *  beginning at @p __result, except that only the first element is copied
                   *  from groups of consecutive elements that compare equal.
                   *  unique_copy() is stable, so the relative order of elements that are
                   *  copied is unchanged.
                   *
                   *  _GLIBCXX_RESOLVE_LIB_DEFECTS
                   *  DR 241. Does unique_copy() require CopyConstructible and Assignable?
                   *  
                   *  _GLIBCXX_RESOLVE_LIB_DEFECTS
                   *  DR 538. 241 again: Does unique_copy() require CopyConstructible and 
                   *  Assignable?
                  */
                  template<typename _InputIterator, typename _OutputIterator>
                    inline _OutputIterator
                    unique_copy(_InputIterator __first, _InputIterator __last,
                		_OutputIterator __result)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                	    typename iterator_traits<_InputIterator>::value_type>)
                      __glibcxx_function_requires(_EqualityComparableConcept<
                	    typename iterator_traits<_InputIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__first == __last)
                	return __result;
                      return std::__unique_copy(__first, __last, __result,
                				std::__iterator_category(__first),
                				std::__iterator_category(__result));
                    }
                
                  /**
                   *  @brief Copy a sequence, removing consecutive values using a predicate.
                   *  @ingroup mutating_algorithms
                   *  @param  __first        An input iterator.
                   *  @param  __last         An input iterator.
                   *  @param  __result       An output iterator.
                   *  @param  __binary_pred  A binary predicate.
                   *  @return   An iterator designating the end of the resulting sequence.
                   *
                   *  Copies each element in the range @p [__first,__last) to the range
                   *  beginning at @p __result, except that only the first element is copied
                   *  from groups of consecutive elements for which @p __binary_pred returns
                   *  true.
                   *  unique_copy() is stable, so the relative order of elements that are
                   *  copied is unchanged.
                   *
                   *  _GLIBCXX_RESOLVE_LIB_DEFECTS
                   *  DR 241. Does unique_copy() require CopyConstructible and Assignable?
                  */
                  template<typename _InputIterator, typename _OutputIterator,
                	   typename _BinaryPredicate>
                    inline _OutputIterator
                    unique_copy(_InputIterator __first, _InputIterator __last,
                		_OutputIterator __result,
                		_BinaryPredicate __binary_pred)
                    {
                      // concept requirements -- predicates checked later
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                	    typename iterator_traits<_InputIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__first == __last)
                	return __result;
                      return std::__unique_copy(__first, __last, __result, __binary_pred,
                				std::__iterator_category(__first),
                				std::__iterator_category(__result));
                    }
                
                
                  /**
                   *  @brief Randomly shuffle the elements of a sequence.
                   *  @ingroup mutating_algorithms
                   *  @param  __first   A forward iterator.
                   *  @param  __last    A forward iterator.
                   *  @return  Nothing.
                   *
                   *  Reorder the elements in the range @p [__first,__last) using a random
                   *  distribution, so that every possible ordering of the sequence is
                   *  equally likely.
                  */
                  template<typename _RandomAccessIterator>
                    inline void
                    random_shuffle(_RandomAccessIterator __first, _RandomAccessIterator __last)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_RandomAccessIteratorConcept<
                	    _RandomAccessIterator>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__first != __last)
                	for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
                	  {
                	    _RandomAccessIterator __j = __first
                					+ std::rand() % ((__i - __first) + 1);
                	    if (__i != __j)
                	      std::iter_swap(__i, __j);
                	  }
                    }
                
                  /**
                   *  @brief Shuffle the elements of a sequence using a random number
                   *         generator.
                   *  @ingroup mutating_algorithms
                   *  @param  __first   A forward iterator.
                   *  @param  __last    A forward iterator.
                   *  @param  __rand    The RNG functor or function.
                   *  @return  Nothing.
                   *
                   *  Reorders the elements in the range @p [__first,__last) using @p __rand to
                   *  provide a random distribution. Calling @p __rand(N) for a positive
                   *  integer @p N should return a randomly chosen integer from the
                   *  range [0,N).
                  */
                  template<typename _RandomAccessIterator, typename _RandomNumberGenerator>
                    void
                    random_shuffle(_RandomAccessIterator __first, _RandomAccessIterator __last,
                #if __cplusplus >= 201103L
                		   _RandomNumberGenerator&& __rand)
                #else
                		   _RandomNumberGenerator& __rand)
                #endif
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_RandomAccessIteratorConcept<
                	    _RandomAccessIterator>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__first == __last)
                	return;
                      for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
                	{
                	  _RandomAccessIterator __j = __first + __rand((__i - __first) + 1);
                	  if (__i != __j)
                	    std::iter_swap(__i, __j);
                	}
                    }
                
                
                  /**
                   *  @brief Move elements for which a predicate is true to the beginning
                   *         of a sequence.
                   *  @ingroup mutating_algorithms
                   *  @param  __first   A forward iterator.
                   *  @param  __last    A forward iterator.
                   *  @param  __pred    A predicate functor.
                   *  @return  An iterator @p middle such that @p __pred(i) is true for each
                   *  iterator @p i in the range @p [__first,middle) and false for each @p i
                   *  in the range @p [middle,__last).
                   *
                   *  @p __pred must not modify its operand. @p partition() does not preserve
                   *  the relative ordering of elements in each group, use
                   *  @p stable_partition() if this is needed.
                  */
                  template<typename _ForwardIterator, typename _Predicate>
                    inline _ForwardIterator
                    partition(_ForwardIterator __first, _ForwardIterator __last,
                	      _Predicate   __pred)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<
                				  _ForwardIterator>)
                      __glibcxx_function_requires(_UnaryPredicateConcept<_Predicate,
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      return std::__partition(__first, __last, __pred,
                			      std::__iterator_category(__first));
                    }
                
                
                
                  /**
                   *  @brief Sort the smallest elements of a sequence.
                   *  @ingroup sorting_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __middle  Another iterator.
                   *  @param  __last    Another iterator.
                   *  @return  Nothing.
                   *
                   *  Sorts the smallest @p (__middle-__first) elements in the range
                   *  @p [first,last) and moves them to the range @p [__first,__middle). The
                   *  order of the remaining elements in the range @p [__middle,__last) is
                   *  undefined.
                   *  After the sort if @e i and @e j are iterators in the range
                   *  @p [__first,__middle) such that i precedes j and @e k is an iterator in
                   *  the range @p [__middle,__last) then *j<*i and *k<*i are both false.
                  */
                  template<typename _RandomAccessIterator>
                    inline void
                    partial_sort(_RandomAccessIterator __first,
                		 _RandomAccessIterator __middle,
                		 _RandomAccessIterator __last)
                    {
                      typedef typename iterator_traits<_RandomAccessIterator>::value_type
                	_ValueType;
                
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_RandomAccessIteratorConcept<
                	    _RandomAccessIterator>)
                      __glibcxx_function_requires(_LessThanComparableConcept<_ValueType>)
                      __glibcxx_requires_valid_range(__first, __middle);
                      __glibcxx_requires_valid_range(__middle, __last);
                
                      std::__heap_select(__first, __middle, __last);
                      std::sort_heap(__first, __middle);
                    }
                
                  /**
                   *  @brief Sort the smallest elements of a sequence using a predicate
                   *         for comparison.
                   *  @ingroup sorting_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __middle  Another iterator.
                   *  @param  __last    Another iterator.
                   *  @param  __comp    A comparison functor.
                   *  @return  Nothing.
                   *
                   *  Sorts the smallest @p (__middle-__first) elements in the range
                   *  @p [__first,__last) and moves them to the range @p [__first,__middle). The
                   *  order of the remaining elements in the range @p [__middle,__last) is
                   *  undefined.
                   *  After the sort if @e i and @e j are iterators in the range
                   *  @p [__first,__middle) such that i precedes j and @e k is an iterator in
                   *  the range @p [__middle,__last) then @p *__comp(j,*i) and @p __comp(*k,*i)
                   *  are both false.
                  */
                  template<typename _RandomAccessIterator, typename _Compare>
                    inline void
                    partial_sort(_RandomAccessIterator __first,
                		 _RandomAccessIterator __middle,
                		 _RandomAccessIterator __last,
                		 _Compare __comp)
                    {
                      typedef typename iterator_traits<_RandomAccessIterator>::value_type
                	_ValueType;
                
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_RandomAccessIteratorConcept<
                	    _RandomAccessIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _ValueType, _ValueType>)
                      __glibcxx_requires_valid_range(__first, __middle);
                      __glibcxx_requires_valid_range(__middle, __last);
                
                      std::__heap_select(__first, __middle, __last, __comp);
                      std::sort_heap(__first, __middle, __comp);
                    }
                
                  /**
                   *  @brief Sort a sequence just enough to find a particular position.
                   *  @ingroup sorting_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __nth     Another iterator.
                   *  @param  __last    Another iterator.
                   *  @return  Nothing.
                   *
                   *  Rearranges the elements in the range @p [__first,__last) so that @p *__nth
                   *  is the same element that would have been in that position had the
                   *  whole sequence been sorted. The elements either side of @p *__nth are
                   *  not completely sorted, but for any iterator @e i in the range
                   *  @p [__first,__nth) and any iterator @e j in the range @p [__nth,__last) it
                   *  holds that *j < *i is false.
                  */
                  template<typename _RandomAccessIterator>
                    inline void
                    nth_element(_RandomAccessIterator __first, _RandomAccessIterator __nth,
                		_RandomAccessIterator __last)
                    {
                      typedef typename iterator_traits<_RandomAccessIterator>::value_type
                	_ValueType;
                
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_RandomAccessIteratorConcept<
                				  _RandomAccessIterator>)
                      __glibcxx_function_requires(_LessThanComparableConcept<_ValueType>)
                      __glibcxx_requires_valid_range(__first, __nth);
                      __glibcxx_requires_valid_range(__nth, __last);
                
                      if (__first == __last || __nth == __last)
                	return;
                
                      std::__introselect(__first, __nth, __last,
                			 std::__lg(__last - __first) * 2);
                    }
                
                  /**
                   *  @brief Sort a sequence just enough to find a particular position
                   *         using a predicate for comparison.
                   *  @ingroup sorting_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __nth     Another iterator.
                   *  @param  __last    Another iterator.
                   *  @param  __comp    A comparison functor.
                   *  @return  Nothing.
                   *
                   *  Rearranges the elements in the range @p [__first,__last) so that @p *__nth
                   *  is the same element that would have been in that position had the
                   *  whole sequence been sorted. The elements either side of @p *__nth are
                   *  not completely sorted, but for any iterator @e i in the range
                   *  @p [__first,__nth) and any iterator @e j in the range @p [__nth,__last) it
                   *  holds that @p __comp(*j,*i) is false.
                  */
                  template<typename _RandomAccessIterator, typename _Compare>
                    inline void
                    nth_element(_RandomAccessIterator __first, _RandomAccessIterator __nth,
                		_RandomAccessIterator __last, _Compare __comp)
                    {
                      typedef typename iterator_traits<_RandomAccessIterator>::value_type
                	_ValueType;
                
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_RandomAccessIteratorConcept<
                				  _RandomAccessIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _ValueType, _ValueType>)
                      __glibcxx_requires_valid_range(__first, __nth);
                      __glibcxx_requires_valid_range(__nth, __last);
                
                      if (__first == __last || __nth == __last)
                	return;
                
                      std::__introselect(__first, __nth, __last,
                			 std::__lg(__last - __first) * 2, __comp);
                    }
                
                
                  /**
                   *  @brief Sort the elements of a sequence.
                   *  @ingroup sorting_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @return  Nothing.
                   *
                   *  Sorts the elements in the range @p [__first,__last) in ascending order,
                   *  such that for each iterator @e i in the range @p [__first,__last-1),  
                   *  *(i+1)<*i is false.
                   *
                   *  The relative ordering of equivalent elements is not preserved, use
                   *  @p stable_sort() if this is needed.
                  */
                  template<typename _RandomAccessIterator>
                    inline void
                    sort(_RandomAccessIterator __first, _RandomAccessIterator __last)
                    {
                      typedef typename iterator_traits<_RandomAccessIterator>::value_type
                	_ValueType;
                
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_RandomAccessIteratorConcept<
                	    _RandomAccessIterator>)
                      __glibcxx_function_requires(_LessThanComparableConcept<_ValueType>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__first != __last)
                	{
                	  std::__introsort_loop(__first, __last,
                				std::__lg(__last - __first) * 2);
                	  std::__final_insertion_sort(__first, __last);
                	}
                    }
                
                  /**
                   *  @brief Sort the elements of a sequence using a predicate for comparison.
                   *  @ingroup sorting_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @param  __comp    A comparison functor.
                   *  @return  Nothing.
                   *
                   *  Sorts the elements in the range @p [__first,__last) in ascending order,
                   *  such that @p __comp(*(i+1),*i) is false for every iterator @e i in the
                   *  range @p [__first,__last-1).
                   *
                   *  The relative ordering of equivalent elements is not preserved, use
                   *  @p stable_sort() if this is needed.
                  */
                  template<typename _RandomAccessIterator, typename _Compare>
                    inline void
                    sort(_RandomAccessIterator __first, _RandomAccessIterator __last,
                	 _Compare __comp)
                    {
                      typedef typename iterator_traits<_RandomAccessIterator>::value_type
                	_ValueType;
                
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_RandomAccessIteratorConcept<
                	    _RandomAccessIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare, _ValueType,
                				  _ValueType>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__first != __last)
                	{
                	  std::__introsort_loop(__first, __last,
                				std::__lg(__last - __first) * 2, __comp);
                	  std::__final_insertion_sort(__first, __last, __comp);
                	}
                    }
                
                  /**
                   *  @brief Merges two sorted ranges.
                   *  @ingroup sorting_algorithms
                   *  @param  __first1  An iterator.
                   *  @param  __first2  Another iterator.
                   *  @param  __last1   Another iterator.
                   *  @param  __last2   Another iterator.
                   *  @param  __result  An iterator pointing to the end of the merged range.
                   *  @return         An iterator pointing to the first element <em>not less
                   *                  than</em> @e val.
                   *
                   *  Merges the ranges @p [__first1,__last1) and @p [__first2,__last2) into
                   *  the sorted range @p [__result, __result + (__last1-__first1) +
                   *  (__last2-__first2)).  Both input ranges must be sorted, and the
                   *  output range must not overlap with either of the input ranges.
                   *  The sort is @e stable, that is, for equivalent elements in the
                   *  two ranges, elements from the first range will always come
                   *  before elements from the second.
                  */
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _OutputIterator>
                    _OutputIterator
                    merge(_InputIterator1 __first1, _InputIterator1 __last1,
                	  _InputIterator2 __first2, _InputIterator2 __last2,
                	  _OutputIterator __result)
                    {
                      typedef typename iterator_traits<_InputIterator1>::value_type
                	_ValueType1;
                      typedef typename iterator_traits<_InputIterator2>::value_type
                	_ValueType2;
                
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator2>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                				  _ValueType1>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                				  _ValueType2>)
                      __glibcxx_function_requires(_LessThanOpConcept<_ValueType2, _ValueType1>)	
                      __glibcxx_requires_sorted_set(__first1, __last1, __first2);
                      __glibcxx_requires_sorted_set(__first2, __last2, __first1);
                
                      while (__first1 != __last1 && __first2 != __last2)
                	{
                	  if (*__first2 < *__first1)
                	    {
                	      *__result = *__first2;
                	      ++__first2;
                	    }
                	  else
                	    {
                	      *__result = *__first1;
                	      ++__first1;
                	    }
                	  ++__result;
                	}
                      return std::copy(__first2, __last2, std::copy(__first1, __last1,
                						    __result));
                    }
                
                  /**
                   *  @brief Merges two sorted ranges.
                   *  @ingroup sorting_algorithms
                   *  @param  __first1  An iterator.
                   *  @param  __first2  Another iterator.
                   *  @param  __last1   Another iterator.
                   *  @param  __last2   Another iterator.
                   *  @param  __result  An iterator pointing to the end of the merged range.
                   *  @param  __comp    A functor to use for comparisons.
                   *  @return         An iterator pointing to the first element "not less
                   *                  than" @e val.
                   *
                   *  Merges the ranges @p [__first1,__last1) and @p [__first2,__last2) into
                   *  the sorted range @p [__result, __result + (__last1-__first1) +
                   *  (__last2-__first2)).  Both input ranges must be sorted, and the
                   *  output range must not overlap with either of the input ranges.
                   *  The sort is @e stable, that is, for equivalent elements in the
                   *  two ranges, elements from the first range will always come
                   *  before elements from the second.
                   *
                   *  The comparison function should have the same effects on ordering as
                   *  the function used for the initial sort.
                  */
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _OutputIterator, typename _Compare>
                    _OutputIterator
                    merge(_InputIterator1 __first1, _InputIterator1 __last1,
                	  _InputIterator2 __first2, _InputIterator2 __last2,
                	  _OutputIterator __result, _Compare __comp)
                    {
                      typedef typename iterator_traits<_InputIterator1>::value_type
                	_ValueType1;
                      typedef typename iterator_traits<_InputIterator2>::value_type
                	_ValueType2;
                
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator2>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                				  _ValueType1>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                				  _ValueType2>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _ValueType2, _ValueType1>)
                      __glibcxx_requires_sorted_set_pred(__first1, __last1, __first2, __comp);
                      __glibcxx_requires_sorted_set_pred(__first2, __last2, __first1, __comp);
                
                      while (__first1 != __last1 && __first2 != __last2)
                	{
                	  if (__comp(*__first2, *__first1))
                	    {
                	      *__result = *__first2;
                	      ++__first2;
                	    }
                	  else
                	    {
                	      *__result = *__first1;
                	      ++__first1;
                	    }
                	  ++__result;
                	}
                      return std::copy(__first2, __last2, std::copy(__first1, __last1,
                						    __result));
                    }
                
                
                  /**
                   *  @brief Sort the elements of a sequence, preserving the relative order
                   *         of equivalent elements.
                   *  @ingroup sorting_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @return  Nothing.
                   *
                   *  Sorts the elements in the range @p [__first,__last) in ascending order,
                   *  such that for each iterator @p i in the range @p [__first,__last-1),
                   *  @p *(i+1)<*i is false.
                   *
                   *  The relative ordering of equivalent elements is preserved, so any two
                   *  elements @p x and @p y in the range @p [__first,__last) such that
                   *  @p x<y is false and @p y<x is false will have the same relative
                   *  ordering after calling @p stable_sort().
                  */
                  template<typename _RandomAccessIterator>
                    inline void
                    stable_sort(_RandomAccessIterator __first, _RandomAccessIterator __last)
                    {
                      typedef typename iterator_traits<_RandomAccessIterator>::value_type
                	_ValueType;
                      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
                	_DistanceType;
                
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_RandomAccessIteratorConcept<
                	    _RandomAccessIterator>)
                      __glibcxx_function_requires(_LessThanComparableConcept<_ValueType>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      _Temporary_buffer<_RandomAccessIterator, _ValueType> __buf(__first,
                								 __last);
                      if (__buf.begin() == 0)
                	std::__inplace_stable_sort(__first, __last);
                      else
                	std::__stable_sort_adaptive(__first, __last, __buf.begin(),
                				    _DistanceType(__buf.size()));
                    }
                
                  /**
                   *  @brief Sort the elements of a sequence using a predicate for comparison,
                   *         preserving the relative order of equivalent elements.
                   *  @ingroup sorting_algorithms
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @param  __comp    A comparison functor.
                   *  @return  Nothing.
                   *
                   *  Sorts the elements in the range @p [__first,__last) in ascending order,
                   *  such that for each iterator @p i in the range @p [__first,__last-1),
                   *  @p __comp(*(i+1),*i) is false.
                   *
                   *  The relative ordering of equivalent elements is preserved, so any two
                   *  elements @p x and @p y in the range @p [__first,__last) such that
                   *  @p __comp(x,y) is false and @p __comp(y,x) is false will have the same
                   *  relative ordering after calling @p stable_sort().
                  */
                  template<typename _RandomAccessIterator, typename _Compare>
                    inline void
                    stable_sort(_RandomAccessIterator __first, _RandomAccessIterator __last,
                		_Compare __comp)
                    {
                      typedef typename iterator_traits<_RandomAccessIterator>::value_type
                	_ValueType;
                      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
                	_DistanceType;
                
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_RandomAccessIteratorConcept<
                	    _RandomAccessIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _ValueType,
                				  _ValueType>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      _Temporary_buffer<_RandomAccessIterator, _ValueType> __buf(__first,
                								 __last);
                      if (__buf.begin() == 0)
                	std::__inplace_stable_sort(__first, __last, __comp);
                      else
                	std::__stable_sort_adaptive(__first, __last, __buf.begin(),
                				    _DistanceType(__buf.size()), __comp);
                    }
                
                
                  /**
                   *  @brief Return the union of two sorted ranges.
                   *  @ingroup set_algorithms
                   *  @param  __first1  Start of first range.
                   *  @param  __last1   End of first range.
                   *  @param  __first2  Start of second range.
                   *  @param  __last2   End of second range.
                   *  @return  End of the output range.
                   *  @ingroup set_algorithms
                   *
                   *  This operation iterates over both ranges, copying elements present in
                   *  each range in order to the output range.  Iterators increment for each
                   *  range.  When the current element of one range is less than the other,
                   *  that element is copied and the iterator advanced.  If an element is
                   *  contained in both ranges, the element from the first range is copied and
                   *  both ranges advance.  The output range may not overlap either input
                   *  range.
                  */
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _OutputIterator>
                    _OutputIterator
                    set_union(_InputIterator1 __first1, _InputIterator1 __last1,
                	      _InputIterator2 __first2, _InputIterator2 __last2,
                	      _OutputIterator __result)
                    {
                      typedef typename iterator_traits<_InputIterator1>::value_type
                	_ValueType1;
                      typedef typename iterator_traits<_InputIterator2>::value_type
                	_ValueType2;
                
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator2>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                				  _ValueType1>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                				  _ValueType2>)
                      __glibcxx_function_requires(_LessThanOpConcept<_ValueType1, _ValueType2>)
                      __glibcxx_function_requires(_LessThanOpConcept<_ValueType2, _ValueType1>)
                      __glibcxx_requires_sorted_set(__first1, __last1, __first2);
                      __glibcxx_requires_sorted_set(__first2, __last2, __first1);
                
                      while (__first1 != __last1 && __first2 != __last2)
                	{
                	  if (*__first1 < *__first2)
                	    {
                	      *__result = *__first1;
                	      ++__first1;
                	    }
                	  else if (*__first2 < *__first1)
                	    {
                	      *__result = *__first2;
                	      ++__first2;
                	    }
                	  else
                	    {
                	      *__result = *__first1;
                	      ++__first1;
                	      ++__first2;
                	    }
                	  ++__result;
                	}
                      return std::copy(__first2, __last2, std::copy(__first1, __last1,
                						    __result));
                    }
                
                  /**
                   *  @brief Return the union of two sorted ranges using a comparison functor.
                   *  @ingroup set_algorithms
                   *  @param  __first1  Start of first range.
                   *  @param  __last1   End of first range.
                   *  @param  __first2  Start of second range.
                   *  @param  __last2   End of second range.
                   *  @param  __comp    The comparison functor.
                   *  @return  End of the output range.
                   *  @ingroup set_algorithms
                   *
                   *  This operation iterates over both ranges, copying elements present in
                   *  each range in order to the output range.  Iterators increment for each
                   *  range.  When the current element of one range is less than the other
                   *  according to @p __comp, that element is copied and the iterator advanced.
                   *  If an equivalent element according to @p __comp is contained in both
                   *  ranges, the element from the first range is copied and both ranges
                   *  advance.  The output range may not overlap either input range.
                  */
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _OutputIterator, typename _Compare>
                    _OutputIterator
                    set_union(_InputIterator1 __first1, _InputIterator1 __last1,
                	      _InputIterator2 __first2, _InputIterator2 __last2,
                	      _OutputIterator __result, _Compare __comp)
                    {
                      typedef typename iterator_traits<_InputIterator1>::value_type
                	_ValueType1;
                      typedef typename iterator_traits<_InputIterator2>::value_type
                	_ValueType2;
                
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator2>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                				  _ValueType1>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                				  _ValueType2>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _ValueType1, _ValueType2>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _ValueType2, _ValueType1>)
                      __glibcxx_requires_sorted_set_pred(__first1, __last1, __first2, __comp);
                      __glibcxx_requires_sorted_set_pred(__first2, __last2, __first1, __comp);
                
                      while (__first1 != __last1 && __first2 != __last2)
                	{
                	  if (__comp(*__first1, *__first2))
                	    {
                	      *__result = *__first1;
                	      ++__first1;
                	    }
                	  else if (__comp(*__first2, *__first1))
                	    {
                	      *__result = *__first2;
                	      ++__first2;
                	    }
                	  else
                	    {
                	      *__result = *__first1;
                	      ++__first1;
                	      ++__first2;
                	    }
                	  ++__result;
                	}
                      return std::copy(__first2, __last2, std::copy(__first1, __last1,
                						    __result));
                    }
                
                  /**
                   *  @brief Return the intersection of two sorted ranges.
                   *  @ingroup set_algorithms
                   *  @param  __first1  Start of first range.
                   *  @param  __last1   End of first range.
                   *  @param  __first2  Start of second range.
                   *  @param  __last2   End of second range.
                   *  @return  End of the output range.
                   *  @ingroup set_algorithms
                   *
                   *  This operation iterates over both ranges, copying elements present in
                   *  both ranges in order to the output range.  Iterators increment for each
                   *  range.  When the current element of one range is less than the other,
                   *  that iterator advances.  If an element is contained in both ranges, the
                   *  element from the first range is copied and both ranges advance.  The
                   *  output range may not overlap either input range.
                  */
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _OutputIterator>
                    _OutputIterator
                    set_intersection(_InputIterator1 __first1, _InputIterator1 __last1,
                		     _InputIterator2 __first2, _InputIterator2 __last2,
                		     _OutputIterator __result)
                    {
                      typedef typename iterator_traits<_InputIterator1>::value_type
                	_ValueType1;
                      typedef typename iterator_traits<_InputIterator2>::value_type
                	_ValueType2;
                
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator2>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                				  _ValueType1>)
                      __glibcxx_function_requires(_LessThanOpConcept<_ValueType1, _ValueType2>)
                      __glibcxx_function_requires(_LessThanOpConcept<_ValueType2, _ValueType1>)
                      __glibcxx_requires_sorted_set(__first1, __last1, __first2);
                      __glibcxx_requires_sorted_set(__first2, __last2, __first1);
                
                      while (__first1 != __last1 && __first2 != __last2)
                	if (*__first1 < *__first2)
                	  ++__first1;
                	else if (*__first2 < *__first1)
                	  ++__first2;
                	else
                	  {
                	    *__result = *__first1;
                	    ++__first1;
                	    ++__first2;
                	    ++__result;
                	  }
                      return __result;
                    }
                
                  /**
                   *  @brief Return the intersection of two sorted ranges using comparison
                   *  functor.
                   *  @ingroup set_algorithms
                   *  @param  __first1  Start of first range.
                   *  @param  __last1   End of first range.
                   *  @param  __first2  Start of second range.
                   *  @param  __last2   End of second range.
                   *  @param  __comp    The comparison functor.
                   *  @return  End of the output range.
                   *  @ingroup set_algorithms
                   *
                   *  This operation iterates over both ranges, copying elements present in
                   *  both ranges in order to the output range.  Iterators increment for each
                   *  range.  When the current element of one range is less than the other
                   *  according to @p __comp, that iterator advances.  If an element is
                   *  contained in both ranges according to @p __comp, the element from the
                   *  first range is copied and both ranges advance.  The output range may not
                   *  overlap either input range.
                  */
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _OutputIterator, typename _Compare>
                    _OutputIterator
                    set_intersection(_InputIterator1 __first1, _InputIterator1 __last1,
                		     _InputIterator2 __first2, _InputIterator2 __last2,
                		     _OutputIterator __result, _Compare __comp)
                    {
                      typedef typename iterator_traits<_InputIterator1>::value_type
                	_ValueType1;
                      typedef typename iterator_traits<_InputIterator2>::value_type
                	_ValueType2;
                
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator2>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                				  _ValueType1>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _ValueType1, _ValueType2>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _ValueType2, _ValueType1>)
                      __glibcxx_requires_sorted_set_pred(__first1, __last1, __first2, __comp);
                      __glibcxx_requires_sorted_set_pred(__first2, __last2, __first1, __comp);
                
                      while (__first1 != __last1 && __first2 != __last2)
                	if (__comp(*__first1, *__first2))
                	  ++__first1;
                	else if (__comp(*__first2, *__first1))
                	  ++__first2;
                	else
                	  {
                	    *__result = *__first1;
                	    ++__first1;
                	    ++__first2;
                	    ++__result;
                	  }
                      return __result;
                    }
                
                  /**
                   *  @brief Return the difference of two sorted ranges.
                   *  @ingroup set_algorithms
                   *  @param  __first1  Start of first range.
                   *  @param  __last1   End of first range.
                   *  @param  __first2  Start of second range.
                   *  @param  __last2   End of second range.
                   *  @return  End of the output range.
                   *  @ingroup set_algorithms
                   *
                   *  This operation iterates over both ranges, copying elements present in
                   *  the first range but not the second in order to the output range.
                   *  Iterators increment for each range.  When the current element of the
                   *  first range is less than the second, that element is copied and the
                   *  iterator advances.  If the current element of the second range is less,
                   *  the iterator advances, but no element is copied.  If an element is
                   *  contained in both ranges, no elements are copied and both ranges
                   *  advance.  The output range may not overlap either input range.
                  */
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _OutputIterator>
                    _OutputIterator
                    set_difference(_InputIterator1 __first1, _InputIterator1 __last1,
                		   _InputIterator2 __first2, _InputIterator2 __last2,
                		   _OutputIterator __result)
                    {
                      typedef typename iterator_traits<_InputIterator1>::value_type
                	_ValueType1;
                      typedef typename iterator_traits<_InputIterator2>::value_type
                	_ValueType2;
                
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator2>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                				  _ValueType1>)
                      __glibcxx_function_requires(_LessThanOpConcept<_ValueType1, _ValueType2>)
                      __glibcxx_function_requires(_LessThanOpConcept<_ValueType2, _ValueType1>)	
                      __glibcxx_requires_sorted_set(__first1, __last1, __first2);
                      __glibcxx_requires_sorted_set(__first2, __last2, __first1);
                
                      while (__first1 != __last1 && __first2 != __last2)
                	if (*__first1 < *__first2)
                	  {
                	    *__result = *__first1;
                	    ++__first1;
                	    ++__result;
                	  }
                	else if (*__first2 < *__first1)
                	  ++__first2;
                	else
                	  {
                	    ++__first1;
                	    ++__first2;
                	  }
                      return std::copy(__first1, __last1, __result);
                    }
                
                  /**
                   *  @brief  Return the difference of two sorted ranges using comparison
                   *  functor.
                   *  @ingroup set_algorithms
                   *  @param  __first1  Start of first range.
                   *  @param  __last1   End of first range.
                   *  @param  __first2  Start of second range.
                   *  @param  __last2   End of second range.
                   *  @param  __comp    The comparison functor.
                   *  @return  End of the output range.
                   *  @ingroup set_algorithms
                   *
                   *  This operation iterates over both ranges, copying elements present in
                   *  the first range but not the second in order to the output range.
                   *  Iterators increment for each range.  When the current element of the
                   *  first range is less than the second according to @p __comp, that element
                   *  is copied and the iterator advances.  If the current element of the
                   *  second range is less, no element is copied and the iterator advances.
                   *  If an element is contained in both ranges according to @p __comp, no
                   *  elements are copied and both ranges advance.  The output range may not
                   *  overlap either input range.
                  */
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _OutputIterator, typename _Compare>
                    _OutputIterator
                    set_difference(_InputIterator1 __first1, _InputIterator1 __last1,
                		   _InputIterator2 __first2, _InputIterator2 __last2,
                		   _OutputIterator __result, _Compare __comp)
                    {
                      typedef typename iterator_traits<_InputIterator1>::value_type
                	_ValueType1;
                      typedef typename iterator_traits<_InputIterator2>::value_type
                	_ValueType2;
                
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator2>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                				  _ValueType1>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _ValueType1, _ValueType2>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _ValueType2, _ValueType1>)
                      __glibcxx_requires_sorted_set_pred(__first1, __last1, __first2, __comp);
                      __glibcxx_requires_sorted_set_pred(__first2, __last2, __first1, __comp);
                
                      while (__first1 != __last1 && __first2 != __last2)
                	if (__comp(*__first1, *__first2))
                	  {
                	    *__result = *__first1;
                	    ++__first1;
                	    ++__result;
                	  }
                	else if (__comp(*__first2, *__first1))
                	  ++__first2;
                	else
                	  {
                	    ++__first1;
                	    ++__first2;
                	  }
                      return std::copy(__first1, __last1, __result);
                    }
                
                  /**
                   *  @brief  Return the symmetric difference of two sorted ranges.
                   *  @ingroup set_algorithms
                   *  @param  __first1  Start of first range.
                   *  @param  __last1   End of first range.
                   *  @param  __first2  Start of second range.
                   *  @param  __last2   End of second range.
                   *  @return  End of the output range.
                   *  @ingroup set_algorithms
                   *
                   *  This operation iterates over both ranges, copying elements present in
                   *  one range but not the other in order to the output range.  Iterators
                   *  increment for each range.  When the current element of one range is less
                   *  than the other, that element is copied and the iterator advances.  If an
                   *  element is contained in both ranges, no elements are copied and both
                   *  ranges advance.  The output range may not overlap either input range.
                  */
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _OutputIterator>
                    _OutputIterator
                    set_symmetric_difference(_InputIterator1 __first1, _InputIterator1 __last1,
                			     _InputIterator2 __first2, _InputIterator2 __last2,
                			     _OutputIterator __result)
                    {
                      typedef typename iterator_traits<_InputIterator1>::value_type
                	_ValueType1;
                      typedef typename iterator_traits<_InputIterator2>::value_type
                	_ValueType2;
                
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator2>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                				  _ValueType1>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                				  _ValueType2>)
                      __glibcxx_function_requires(_LessThanOpConcept<_ValueType1, _ValueType2>)
                      __glibcxx_function_requires(_LessThanOpConcept<_ValueType2, _ValueType1>)	
                      __glibcxx_requires_sorted_set(__first1, __last1, __first2);
                      __glibcxx_requires_sorted_set(__first2, __last2, __first1);
                
                      while (__first1 != __last1 && __first2 != __last2)
                	if (*__first1 < *__first2)
                	  {
                	    *__result = *__first1;
                	    ++__first1;
                	    ++__result;
                	  }
                	else if (*__first2 < *__first1)
                	  {
                	    *__result = *__first2;
                	    ++__first2;
                	    ++__result;
                	  }
                	else
                	  {
                	    ++__first1;
                	    ++__first2;
                	  }
                      return std::copy(__first2, __last2, std::copy(__first1,
                						    __last1, __result));
                    }
                
                  /**
                   *  @brief  Return the symmetric difference of two sorted ranges using
                   *  comparison functor.
                   *  @ingroup set_algorithms
                   *  @param  __first1  Start of first range.
                   *  @param  __last1   End of first range.
                   *  @param  __first2  Start of second range.
                   *  @param  __last2   End of second range.
                   *  @param  __comp    The comparison functor.
                   *  @return  End of the output range.
                   *  @ingroup set_algorithms
                   *
                   *  This operation iterates over both ranges, copying elements present in
                   *  one range but not the other in order to the output range.  Iterators
                   *  increment for each range.  When the current element of one range is less
                   *  than the other according to @p comp, that element is copied and the
                   *  iterator advances.  If an element is contained in both ranges according
                   *  to @p __comp, no elements are copied and both ranges advance.  The output
                   *  range may not overlap either input range.
                  */
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _OutputIterator, typename _Compare>
                    _OutputIterator
                    set_symmetric_difference(_InputIterator1 __first1, _InputIterator1 __last1,
                			     _InputIterator2 __first2, _InputIterator2 __last2,
                			     _OutputIterator __result,
                			     _Compare __comp)
                    {
                      typedef typename iterator_traits<_InputIterator1>::value_type
                	_ValueType1;
                      typedef typename iterator_traits<_InputIterator2>::value_type
                	_ValueType2;
                
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator2>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                				  _ValueType1>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OutputIterator,
                				  _ValueType2>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _ValueType1, _ValueType2>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                				  _ValueType2, _ValueType1>)
                      __glibcxx_requires_sorted_set_pred(__first1, __last1, __first2, __comp);
                      __glibcxx_requires_sorted_set_pred(__first2, __last2, __first1, __comp);
                
                      while (__first1 != __last1 && __first2 != __last2)
                	if (__comp(*__first1, *__first2))
                	  {
                	    *__result = *__first1;
                	    ++__first1;
                	    ++__result;
                	  }
                	else if (__comp(*__first2, *__first1))
                	  {
                	    *__result = *__first2;
                	    ++__first2;
                	    ++__result;
                	  }
                	else
                	  {
                	    ++__first1;
                	    ++__first2;
                	  }
                      return std::copy(__first2, __last2, 
                		       std::copy(__first1, __last1, __result));
                    }
                
                
                  /**
                   *  @brief  Return the minimum element in a range.
                   *  @ingroup sorting_algorithms
                   *  @param  __first  Start of range.
                   *  @param  __last   End of range.
                   *  @return  Iterator referencing the first instance of the smallest value.
                  */
                  template<typename _ForwardIterator>
                    _ForwardIterator
                    min_element(_ForwardIterator __first, _ForwardIterator __last)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_LessThanComparableConcept<
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__first == __last)
                	return __first;
                      _ForwardIterator __result = __first;
                      while (++__first != __last)
                	if (*__first < *__result)
                	  __result = __first;
                      return __result;
                    }
                
                  /**
                   *  @brief  Return the minimum element in a range using comparison functor.
                   *  @ingroup sorting_algorithms
                   *  @param  __first  Start of range.
                   *  @param  __last   End of range.
                   *  @param  __comp   Comparison functor.
                   *  @return  Iterator referencing the first instance of the smallest value
                   *  according to __comp.
                  */
                  template<typename _ForwardIterator, typename _Compare>
                    _ForwardIterator
                    min_element(_ForwardIterator __first, _ForwardIterator __last,
                		_Compare __comp)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                	    typename iterator_traits<_ForwardIterator>::value_type,
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__first == __last)
                	return __first;
                      _ForwardIterator __result = __first;
                      while (++__first != __last)
                	if (__comp(*__first, *__result))
                	  __result = __first;
                      return __result;
                    }
                
                  /**
                   *  @brief  Return the maximum element in a range.
                   *  @ingroup sorting_algorithms
                   *  @param  __first  Start of range.
                   *  @param  __last   End of range.
                   *  @return  Iterator referencing the first instance of the largest value.
                  */
                  template<typename _ForwardIterator>
                    _ForwardIterator
                    max_element(_ForwardIterator __first, _ForwardIterator __last)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_LessThanComparableConcept<
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__first == __last)
                	return __first;
                      _ForwardIterator __result = __first;
                      while (++__first != __last)
                	if (*__result < *__first)
                	  __result = __first;
                      return __result;
                    }
                
                  /**
                   *  @brief  Return the maximum element in a range using comparison functor.
                   *  @ingroup sorting_algorithms
                   *  @param  __first  Start of range.
                   *  @param  __last   End of range.
                   *  @param  __comp   Comparison functor.
                   *  @return  Iterator referencing the first instance of the largest value
                   *  according to __comp.
                  */
                  template<typename _ForwardIterator, typename _Compare>
                    _ForwardIterator
                    max_element(_ForwardIterator __first, _ForwardIterator __last,
                		_Compare __comp)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
                	    typename iterator_traits<_ForwardIterator>::value_type,
                	    typename iterator_traits<_ForwardIterator>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      if (__first == __last) return __first;
                      _ForwardIterator __result = __first;
                      while (++__first != __last)
                	if (__comp(*__result, *__first))
                	  __result = __first;
                      return __result;
                    }
                
                _GLIBCXX_END_NAMESPACE_ALGO
                } // namespace std
                
                #endif /* _STL_ALGO_H */


Top 10 Lines:

     Line      Count

      158   26080000
     1091   26080000
     4432   26080000

Execution Summary:

       42   Executable lines in this file
       42   Lines executed
   100.00   Percent of the file executed

 78240000   Total number of line executions
1862857.14   Average executions per line


*** File /usr/include/c++/4.8.2/bits/stl_iterator.h:
                // Iterators -*- C++ -*-
                
                // Copyright (C) 2001-2013 Free Software Foundation, Inc.
                //
                // This file is part of the GNU ISO C++ Library.  This library is free
                // software; you can redistribute it and/or modify it under the
                // terms of the GNU General Public License as published by the
                // Free Software Foundation; either version 3, or (at your option)
                // any later version.
                
                // This library is distributed in the hope that it will be useful,
                // but WITHOUT ANY WARRANTY; without even the implied warranty of
                // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
                // GNU General Public License for more details.
                
                // Under Section 7 of GPL version 3, you are granted additional
                // permissions described in the GCC Runtime Library Exception, version
                // 3.1, as published by the Free Software Foundation.
                
                // You should have received a copy of the GNU General Public License and
                // a copy of the GCC Runtime Library Exception along with this program;
                // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
                // <http://www.gnu.org/licenses/>.
                
                /*
                 *
                 * Copyright (c) 1994
                 * Hewlett-Packard Company
                 *
                 * Permission to use, copy, modify, distribute and sell this software
                 * and its documentation for any purpose is hereby granted without fee,
                 * provided that the above copyright notice appear in all copies and
                 * that both that copyright notice and this permission notice appear
                 * in supporting documentation.  Hewlett-Packard Company makes no
                 * representations about the suitability of this software for any
                 * purpose.  It is provided "as is" without express or implied warranty.
                 *
                 *
                 * Copyright (c) 1996-1998
                 * Silicon Graphics Computer Systems, Inc.
                 *
                 * Permission to use, copy, modify, distribute and sell this software
                 * and its documentation for any purpose is hereby granted without fee,
                 * provided that the above copyright notice appear in all copies and
                 * that both that copyright notice and this permission notice appear
                 * in supporting documentation.  Silicon Graphics makes no
                 * representations about the suitability of this software for any
                 * purpose.  It is provided "as is" without express or implied warranty.
                 */
                
                /** @file bits/stl_iterator.h
                 *  This is an internal header file, included by other library headers.
                 *  Do not attempt to use it directly. @headername{iterator}
                 *
                 *  This file implements reverse_iterator, back_insert_iterator,
                 *  front_insert_iterator, insert_iterator, __normal_iterator, and their
                 *  supporting functions and overloaded operators.
                 */
                
                #ifndef _STL_ITERATOR_H
                #define _STL_ITERATOR_H 1
                
                #include <bits/cpp_type_traits.h>
                #include <ext/type_traits.h>
                #include <bits/move.h>
                
                namespace std _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                  /**
                   * @addtogroup iterators
                   * @{
                   */
                
                  // 24.4.1 Reverse iterators
                  /**
                   *  Bidirectional and random access iterators have corresponding reverse
                   *  %iterator adaptors that iterate through the data structure in the
                   *  opposite direction.  They have the same signatures as the corresponding
                   *  iterators.  The fundamental relation between a reverse %iterator and its
                   *  corresponding %iterator @c i is established by the identity:
                   *  @code
                   *      &*(reverse_iterator(i)) == &*(i - 1)
                   *  @endcode
                   *
                   *  <em>This mapping is dictated by the fact that while there is always a
                   *  pointer past the end of an array, there might not be a valid pointer
                   *  before the beginning of an array.</em> [24.4.1]/1,2
                   *
                   *  Reverse iterators can be tricky and surprising at first.  Their
                   *  semantics make sense, however, and the trickiness is a side effect of
                   *  the requirement that the iterators must be safe.
                  */
                  template<typename _Iterator>
                    class reverse_iterator
                    : public iterator<typename iterator_traits<_Iterator>::iterator_category,
                		      typename iterator_traits<_Iterator>::value_type,
                		      typename iterator_traits<_Iterator>::difference_type,
                		      typename iterator_traits<_Iterator>::pointer,
                                      typename iterator_traits<_Iterator>::reference>
                    {
                    protected:
                      _Iterator current;
                
                      typedef iterator_traits<_Iterator>		__traits_type;
                
                    public:
                      typedef _Iterator					iterator_type;
                      typedef typename __traits_type::difference_type	difference_type;
                      typedef typename __traits_type::pointer		pointer;
                      typedef typename __traits_type::reference		reference;
                
                      /**
                       *  The default constructor value-initializes member @p current.
                       *  If it is a pointer, that means it is zero-initialized.
                      */
                      // _GLIBCXX_RESOLVE_LIB_DEFECTS
                      // 235 No specification of default ctor for reverse_iterator
                      reverse_iterator() : current() { }
                
                      /**
                       *  This %iterator will move in the opposite direction that @p x does.
                      */
                      explicit
                      reverse_iterator(iterator_type __x) : current(__x) { }
                
                      /**
                       *  The copy constructor is normal.
                      */
                      reverse_iterator(const reverse_iterator& __x)
                      : current(__x.current) { }
                
                      /**
                       *  A %reverse_iterator across other types can be copied if the
                       *  underlying %iterator can be converted to the type of @c current.
                      */
                      template<typename _Iter>
                        reverse_iterator(const reverse_iterator<_Iter>& __x)
                	: current(__x.base()) { }
                
                      /**
                       *  @return  @c current, the %iterator used for underlying work.
                      */
                      iterator_type
                      base() const
                      { return current; }
                
                      /**
                       *  @return  A reference to the value at @c --current
                       *
                       *  This requires that @c --current is dereferenceable.
                       *
                       *  @warning This implementation requires that for an iterator of the
                       *           underlying iterator type, @c x, a reference obtained by
                       *           @c *x remains valid after @c x has been modified or
                       *           destroyed. This is a bug: http://gcc.gnu.org/PR51823
                      */
                      reference
                      operator*() const
                      {
                	_Iterator __tmp = current;
                	return *--__tmp;
                      }
                
                      /**
                       *  @return  A pointer to the value at @c --current
                       *
                       *  This requires that @c --current is dereferenceable.
                      */
                      pointer
                      operator->() const
                      { return &(operator*()); }
                
                      /**
                       *  @return  @c *this
                       *
                       *  Decrements the underlying iterator.
                      */
                      reverse_iterator&
                      operator++()
                      {
                	--current;
                	return *this;
                      }
                
                      /**
                       *  @return  The original value of @c *this
                       *
                       *  Decrements the underlying iterator.
                      */
                      reverse_iterator
                      operator++(int)
                      {
                	reverse_iterator __tmp = *this;
                	--current;
                	return __tmp;
                      }
                
                      /**
                       *  @return  @c *this
                       *
                       *  Increments the underlying iterator.
                      */
                      reverse_iterator&
                      operator--()
                      {
                	++current;
                	return *this;
                      }
                
                      /**
                       *  @return  A reverse_iterator with the previous value of @c *this
                       *
                       *  Increments the underlying iterator.
                      */
                      reverse_iterator
                      operator--(int)
                      {
                	reverse_iterator __tmp = *this;
                	++current;
                	return __tmp;
                      }
                
                      /**
                       *  @return  A reverse_iterator that refers to @c current - @a __n
                       *
                       *  The underlying iterator must be a Random Access Iterator.
                      */
                      reverse_iterator
                      operator+(difference_type __n) const
                      { return reverse_iterator(current - __n); }
                
                      /**
                       *  @return  *this
                       *
                       *  Moves the underlying iterator backwards @a __n steps.
                       *  The underlying iterator must be a Random Access Iterator.
                      */
                      reverse_iterator&
                      operator+=(difference_type __n)
                      {
                	current -= __n;
                	return *this;
                      }
                
                      /**
                       *  @return  A reverse_iterator that refers to @c current - @a __n
                       *
                       *  The underlying iterator must be a Random Access Iterator.
                      */
                      reverse_iterator
                      operator-(difference_type __n) const
                      { return reverse_iterator(current + __n); }
                
                      /**
                       *  @return  *this
                       *
                       *  Moves the underlying iterator forwards @a __n steps.
                       *  The underlying iterator must be a Random Access Iterator.
                      */
                      reverse_iterator&
                      operator-=(difference_type __n)
                      {
                	current += __n;
                	return *this;
                      }
                
                      /**
                       *  @return  The value at @c current - @a __n - 1
                       *
                       *  The underlying iterator must be a Random Access Iterator.
                      */
                      reference
                      operator[](difference_type __n) const
                      { return *(*this + __n); }
                    };
                
                  //@{
                  /**
                   *  @param  __x  A %reverse_iterator.
                   *  @param  __y  A %reverse_iterator.
                   *  @return  A simple bool.
                   *
                   *  Reverse iterators forward many operations to their underlying base()
                   *  iterators.  Others are implemented in terms of one another.
                   *
                  */
                  template<typename _Iterator>
                    inline bool
                    operator==(const reverse_iterator<_Iterator>& __x,
                	       const reverse_iterator<_Iterator>& __y)
                    { return __x.base() == __y.base(); }
                
                  template<typename _Iterator>
                    inline bool
                    operator<(const reverse_iterator<_Iterator>& __x,
                	      const reverse_iterator<_Iterator>& __y)
                    { return __y.base() < __x.base(); }
                
                  template<typename _Iterator>
                    inline bool
                    operator!=(const reverse_iterator<_Iterator>& __x,
                	       const reverse_iterator<_Iterator>& __y)
                    { return !(__x == __y); }
                
                  template<typename _Iterator>
                    inline bool
                    operator>(const reverse_iterator<_Iterator>& __x,
                	      const reverse_iterator<_Iterator>& __y)
                    { return __y < __x; }
                
                  template<typename _Iterator>
                    inline bool
                    operator<=(const reverse_iterator<_Iterator>& __x,
                	       const reverse_iterator<_Iterator>& __y)
                    { return !(__y < __x); }
                
                  template<typename _Iterator>
                    inline bool
                    operator>=(const reverse_iterator<_Iterator>& __x,
                	       const reverse_iterator<_Iterator>& __y)
                    { return !(__x < __y); }
                
                  template<typename _Iterator>
                    inline typename reverse_iterator<_Iterator>::difference_type
                    operator-(const reverse_iterator<_Iterator>& __x,
                	      const reverse_iterator<_Iterator>& __y)
                    { return __y.base() - __x.base(); }
                
                  template<typename _Iterator>
                    inline reverse_iterator<_Iterator>
                    operator+(typename reverse_iterator<_Iterator>::difference_type __n,
                	      const reverse_iterator<_Iterator>& __x)
                    { return reverse_iterator<_Iterator>(__x.base() - __n); }
                
                  // _GLIBCXX_RESOLVE_LIB_DEFECTS
                  // DR 280. Comparison of reverse_iterator to const reverse_iterator.
                  template<typename _IteratorL, typename _IteratorR>
                    inline bool
                    operator==(const reverse_iterator<_IteratorL>& __x,
                	       const reverse_iterator<_IteratorR>& __y)
                    { return __x.base() == __y.base(); }
                
                  template<typename _IteratorL, typename _IteratorR>
                    inline bool
                    operator<(const reverse_iterator<_IteratorL>& __x,
                	      const reverse_iterator<_IteratorR>& __y)
                    { return __y.base() < __x.base(); }
                
                  template<typename _IteratorL, typename _IteratorR>
                    inline bool
                    operator!=(const reverse_iterator<_IteratorL>& __x,
                	       const reverse_iterator<_IteratorR>& __y)
                    { return !(__x == __y); }
                
                  template<typename _IteratorL, typename _IteratorR>
                    inline bool
                    operator>(const reverse_iterator<_IteratorL>& __x,
                	      const reverse_iterator<_IteratorR>& __y)
                    { return __y < __x; }
                
                  template<typename _IteratorL, typename _IteratorR>
                    inline bool
                    operator<=(const reverse_iterator<_IteratorL>& __x,
                	       const reverse_iterator<_IteratorR>& __y)
                    { return !(__y < __x); }
                
                  template<typename _IteratorL, typename _IteratorR>
                    inline bool
                    operator>=(const reverse_iterator<_IteratorL>& __x,
                	       const reverse_iterator<_IteratorR>& __y)
                    { return !(__x < __y); }
                
                  template<typename _IteratorL, typename _IteratorR>
                #if __cplusplus >= 201103L
                    // DR 685.
                    inline auto
                    operator-(const reverse_iterator<_IteratorL>& __x,
                	      const reverse_iterator<_IteratorR>& __y)
                    -> decltype(__y.base() - __x.base())
                #else
                    inline typename reverse_iterator<_IteratorL>::difference_type
                    operator-(const reverse_iterator<_IteratorL>& __x,
                	      const reverse_iterator<_IteratorR>& __y)
                #endif
                    { return __y.base() - __x.base(); }
                  //@}
                
                  // 24.4.2.2.1 back_insert_iterator
                  /**
                   *  @brief  Turns assignment into insertion.
                   *
                   *  These are output iterators, constructed from a container-of-T.
                   *  Assigning a T to the iterator appends it to the container using
                   *  push_back.
                   *
                   *  Tip:  Using the back_inserter function to create these iterators can
                   *  save typing.
                  */
                  template<typename _Container>
                    class back_insert_iterator
                    : public iterator<output_iterator_tag, void, void, void, void>
                    {
                    protected:
                      _Container* container;
                
                    public:
                      /// A nested typedef for the type of whatever container you used.
                      typedef _Container          container_type;
                
                      /// The only way to create this %iterator is with a container.
                      explicit
                      back_insert_iterator(_Container& __x) : container(&__x) { }
                
                      /**
                       *  @param  __value  An instance of whatever type
                       *                 container_type::const_reference is; presumably a
                       *                 reference-to-const T for container<T>.
                       *  @return  This %iterator, for chained operations.
                       *
                       *  This kind of %iterator doesn't really have a @a position in the
                       *  container (you can think of the position as being permanently at
                       *  the end, if you like).  Assigning a value to the %iterator will
                       *  always append the value to the end of the container.
                      */
                #if __cplusplus < 201103L
                      back_insert_iterator&
                      operator=(typename _Container::const_reference __value)
                      {
                	container->push_back(__value);
                	return *this;
                      }
                #else
                      back_insert_iterator&
                      operator=(const typename _Container::value_type& __value)
                      {
                	container->push_back(__value);
                	return *this;
                      }
                
                      back_insert_iterator&
                      operator=(typename _Container::value_type&& __value)
                      {
                	container->push_back(std::move(__value));
                	return *this;
                      }
                #endif
                
                      /// Simply returns *this.
                      back_insert_iterator&
                      operator*()
                      { return *this; }
                
                      /// Simply returns *this.  (This %iterator does not @a move.)
                      back_insert_iterator&
                      operator++()
                      { return *this; }
                
                      /// Simply returns *this.  (This %iterator does not @a move.)
                      back_insert_iterator
                      operator++(int)
                      { return *this; }
                    };
                
                  /**
                   *  @param  __x  A container of arbitrary type.
                   *  @return  An instance of back_insert_iterator working on @p __x.
                   *
                   *  This wrapper function helps in creating back_insert_iterator instances.
                   *  Typing the name of the %iterator requires knowing the precise full
                   *  type of the container, which can be tedious and impedes generic
                   *  programming.  Using this function lets you take advantage of automatic
                   *  template parameter deduction, making the compiler match the correct
                   *  types for you.
                  */
                  template<typename _Container>
                    inline back_insert_iterator<_Container>
                    back_inserter(_Container& __x)
                    { return back_insert_iterator<_Container>(__x); }
                
                  /**
                   *  @brief  Turns assignment into insertion.
                   *
                   *  These are output iterators, constructed from a container-of-T.
                   *  Assigning a T to the iterator prepends it to the container using
                   *  push_front.
                   *
                   *  Tip:  Using the front_inserter function to create these iterators can
                   *  save typing.
                  */
                  template<typename _Container>
                    class front_insert_iterator
                    : public iterator<output_iterator_tag, void, void, void, void>
                    {
                    protected:
                      _Container* container;
                
                    public:
                      /// A nested typedef for the type of whatever container you used.
                      typedef _Container          container_type;
                
                      /// The only way to create this %iterator is with a container.
                      explicit front_insert_iterator(_Container& __x) : container(&__x) { }
                
                      /**
                       *  @param  __value  An instance of whatever type
                       *                 container_type::const_reference is; presumably a
                       *                 reference-to-const T for container<T>.
                       *  @return  This %iterator, for chained operations.
                       *
                       *  This kind of %iterator doesn't really have a @a position in the
                       *  container (you can think of the position as being permanently at
                       *  the front, if you like).  Assigning a value to the %iterator will
                       *  always prepend the value to the front of the container.
                      */
                #if __cplusplus < 201103L
                      front_insert_iterator&
                      operator=(typename _Container::const_reference __value)
                      {
                	container->push_front(__value);
                	return *this;
                      }
                #else
                      front_insert_iterator&
                      operator=(const typename _Container::value_type& __value)
                      {
                	container->push_front(__value);
                	return *this;
                      }
                
                      front_insert_iterator&
                      operator=(typename _Container::value_type&& __value)
                      {
                	container->push_front(std::move(__value));
                	return *this;
                      }
                #endif
                
                      /// Simply returns *this.
                      front_insert_iterator&
                      operator*()
                      { return *this; }
                
                      /// Simply returns *this.  (This %iterator does not @a move.)
                      front_insert_iterator&
                      operator++()
                      { return *this; }
                
                      /// Simply returns *this.  (This %iterator does not @a move.)
                      front_insert_iterator
                      operator++(int)
                      { return *this; }
                    };
                
                  /**
                   *  @param  __x  A container of arbitrary type.
                   *  @return  An instance of front_insert_iterator working on @p x.
                   *
                   *  This wrapper function helps in creating front_insert_iterator instances.
                   *  Typing the name of the %iterator requires knowing the precise full
                   *  type of the container, which can be tedious and impedes generic
                   *  programming.  Using this function lets you take advantage of automatic
                   *  template parameter deduction, making the compiler match the correct
                   *  types for you.
                  */
                  template<typename _Container>
                    inline front_insert_iterator<_Container>
                    front_inserter(_Container& __x)
                    { return front_insert_iterator<_Container>(__x); }
                
                  /**
                   *  @brief  Turns assignment into insertion.
                   *
                   *  These are output iterators, constructed from a container-of-T.
                   *  Assigning a T to the iterator inserts it in the container at the
                   *  %iterator's position, rather than overwriting the value at that
                   *  position.
                   *
                   *  (Sequences will actually insert a @e copy of the value before the
                   *  %iterator's position.)
                   *
                   *  Tip:  Using the inserter function to create these iterators can
                   *  save typing.
                  */
                  template<typename _Container>
                    class insert_iterator
                    : public iterator<output_iterator_tag, void, void, void, void>
                    {
                    protected:
                      _Container* container;
                      typename _Container::iterator iter;
                
                    public:
                      /// A nested typedef for the type of whatever container you used.
                      typedef _Container          container_type;
                
                      /**
                       *  The only way to create this %iterator is with a container and an
                       *  initial position (a normal %iterator into the container).
                      */
                      insert_iterator(_Container& __x, typename _Container::iterator __i)
                      : container(&__x), iter(__i) {}
                
                      /**
                       *  @param  __value  An instance of whatever type
                       *                 container_type::const_reference is; presumably a
                       *                 reference-to-const T for container<T>.
                       *  @return  This %iterator, for chained operations.
                       *
                       *  This kind of %iterator maintains its own position in the
                       *  container.  Assigning a value to the %iterator will insert the
                       *  value into the container at the place before the %iterator.
                       *
                       *  The position is maintained such that subsequent assignments will
                       *  insert values immediately after one another.  For example,
                       *  @code
                       *     // vector v contains A and Z
                       *
                       *     insert_iterator i (v, ++v.begin());
                       *     i = 1;
                       *     i = 2;
                       *     i = 3;
                       *
                       *     // vector v contains A, 1, 2, 3, and Z
                       *  @endcode
                      */
                #if __cplusplus < 201103L
                      insert_iterator&
                      operator=(typename _Container::const_reference __value)
                      {
                	iter = container->insert(iter, __value);
                	++iter;
                	return *this;
                      }
                #else
                      insert_iterator&
                      operator=(const typename _Container::value_type& __value)
                      {
                	iter = container->insert(iter, __value);
                	++iter;
                	return *this;
                      }
                
                      insert_iterator&
                      operator=(typename _Container::value_type&& __value)
                      {
                	iter = container->insert(iter, std::move(__value));
                	++iter;
                	return *this;
                      }
                #endif
                
                      /// Simply returns *this.
                      insert_iterator&
                      operator*()
                      { return *this; }
                
                      /// Simply returns *this.  (This %iterator does not @a move.)
                      insert_iterator&
                      operator++()
                      { return *this; }
                
                      /// Simply returns *this.  (This %iterator does not @a move.)
                      insert_iterator&
                      operator++(int)
                      { return *this; }
                    };
                
                  /**
                   *  @param __x  A container of arbitrary type.
                   *  @return  An instance of insert_iterator working on @p __x.
                   *
                   *  This wrapper function helps in creating insert_iterator instances.
                   *  Typing the name of the %iterator requires knowing the precise full
                   *  type of the container, which can be tedious and impedes generic
                   *  programming.  Using this function lets you take advantage of automatic
                   *  template parameter deduction, making the compiler match the correct
                   *  types for you.
                  */
                  template<typename _Container, typename _Iterator>
                    inline insert_iterator<_Container>
                    inserter(_Container& __x, _Iterator __i)
                    {
                      return insert_iterator<_Container>(__x,
                					 typename _Container::iterator(__i));
                    }
                
                  // @} group iterators
                
                _GLIBCXX_END_NAMESPACE_VERSION
                } // namespace
                
                namespace __gnu_cxx _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                  // This iterator adapter is @a normal in the sense that it does not
                  // change the semantics of any of the operators of its iterator
                  // parameter.  Its primary purpose is to convert an iterator that is
                  // not a class, e.g. a pointer, into an iterator that is a class.
                  // The _Container parameter exists solely so that different containers
                  // using this template can instantiate different types, even if the
                  // _Iterator parameter is the same.
                  using std::iterator_traits;
                  using std::iterator;
                  template<typename _Iterator, typename _Container>
                    class __normal_iterator
                    {
                    protected:
                      _Iterator _M_current;
                
                      typedef iterator_traits<_Iterator>		__traits_type;
                
                    public:
                      typedef _Iterator					iterator_type;
                      typedef typename __traits_type::iterator_category iterator_category;
                      typedef typename __traits_type::value_type  	value_type;
                      typedef typename __traits_type::difference_type 	difference_type;
                      typedef typename __traits_type::reference 	reference;
                      typedef typename __traits_type::pointer   	pointer;
                
                      _GLIBCXX_CONSTEXPR __normal_iterator() : _M_current(_Iterator()) { }
                
                      explicit
    81119964 ->       __normal_iterator(const _Iterator& __i) : _M_current(__i) { }
                
                      // Allow iterator to const_iterator conversion
                      template<typename _Iter>
                        __normal_iterator(const __normal_iterator<_Iter,
                			  typename __enable_if<
                      	       (std::__are_same<_Iter, typename _Container::pointer>::__value),
                		      _Container>::__type>& __i)
                        : _M_current(__i.base()) { }
                
                      // Forward iterator requirements
                      reference
       ##### ->       operator*() const
       ##### ->       { return *_M_current; }
                
                      pointer
                      operator->() const
                      { return _M_current; }
                
                      __normal_iterator&
       ##### ->       operator++()
                      {
       ##### -> 	++_M_current;
       ##### -> 	return *this;
       ##### ->       }
                
                      __normal_iterator
                      operator++(int)
                      { return __normal_iterator(_M_current++); }
                
                      // Bidirectional iterator requirements
                      __normal_iterator&
                      operator--()
                      {
                	--_M_current;
                	return *this;
                      }
                
                      __normal_iterator
                      operator--(int)
                      { return __normal_iterator(_M_current--); }
                
                      // Random access iterator requirements
                      reference
                      operator[](const difference_type& __n) const
                      { return _M_current[__n]; }
                
                      __normal_iterator&
                      operator+=(const difference_type& __n)
                      { _M_current += __n; return *this; }
                
                      __normal_iterator
                      operator+(const difference_type& __n) const
                      { return __normal_iterator(_M_current + __n); }
                
                      __normal_iterator&
                      operator-=(const difference_type& __n)
                      { _M_current -= __n; return *this; }
                
                      __normal_iterator
                      operator-(const difference_type& __n) const
                      { return __normal_iterator(_M_current - __n); }
                
                      const _Iterator&
   214399928 ->       base() const
   214399928 ->       { return _M_current; }
                    };
                
                  // Note: In what follows, the left- and right-hand-side iterators are
                  // allowed to vary in types (conceptually in cv-qualification) so that
                  // comparison between cv-qualified and non-cv-qualified iterators be
                  // valid.  However, the greedy and unfriendly operators in std::rel_ops
                  // will make overload resolution ambiguous (when in scope) if we don't
                  // provide overloads whose operands are of the same type.  Can someone
                  // remind me what generic programming is about? -- Gaby
                
                  // Forward iterator requirements
                  template<typename _IteratorL, typename _IteratorR, typename _Container>
                    inline bool
                    operator==(const __normal_iterator<_IteratorL, _Container>& __lhs,
                	       const __normal_iterator<_IteratorR, _Container>& __rhs)
                    { return __lhs.base() == __rhs.base(); }
                
                  template<typename _Iterator, typename _Container>
                    inline bool
    26080000 ->     operator==(const __normal_iterator<_Iterator, _Container>& __lhs,
                	       const __normal_iterator<_Iterator, _Container>& __rhs)
    26080000 ->     { return __lhs.base() == __rhs.base(); }
                
                  template<typename _IteratorL, typename _IteratorR, typename _Container>
                    inline bool
                    operator!=(const __normal_iterator<_IteratorL, _Container>& __lhs,
                	       const __normal_iterator<_IteratorR, _Container>& __rhs)
                    { return __lhs.base() != __rhs.base(); }
                
                  template<typename _Iterator, typename _Container>
                    inline bool
    26080000 ->     operator!=(const __normal_iterator<_Iterator, _Container>& __lhs,
                	       const __normal_iterator<_Iterator, _Container>& __rhs)
    26080000 ->     { return __lhs.base() != __rhs.base(); }
                
                  // Random access iterator requirements
                  template<typename _IteratorL, typename _IteratorR, typename _Container>
                    inline bool
                    operator<(const __normal_iterator<_IteratorL, _Container>& __lhs,
                	      const __normal_iterator<_IteratorR, _Container>& __rhs)
                    { return __lhs.base() < __rhs.base(); }
                
                  template<typename _Iterator, typename _Container>
                    inline bool
                    operator<(const __normal_iterator<_Iterator, _Container>& __lhs,
                	      const __normal_iterator<_Iterator, _Container>& __rhs)
                    { return __lhs.base() < __rhs.base(); }
                
                  template<typename _IteratorL, typename _IteratorR, typename _Container>
                    inline bool
                    operator>(const __normal_iterator<_IteratorL, _Container>& __lhs,
                	      const __normal_iterator<_IteratorR, _Container>& __rhs)
                    { return __lhs.base() > __rhs.base(); }
                
                  template<typename _Iterator, typename _Container>
                    inline bool
                    operator>(const __normal_iterator<_Iterator, _Container>& __lhs,
                	      const __normal_iterator<_Iterator, _Container>& __rhs)
                    { return __lhs.base() > __rhs.base(); }
                
                  template<typename _IteratorL, typename _IteratorR, typename _Container>
                    inline bool
                    operator<=(const __normal_iterator<_IteratorL, _Container>& __lhs,
                	       const __normal_iterator<_IteratorR, _Container>& __rhs)
                    { return __lhs.base() <= __rhs.base(); }
                
                  template<typename _Iterator, typename _Container>
                    inline bool
                    operator<=(const __normal_iterator<_Iterator, _Container>& __lhs,
                	       const __normal_iterator<_Iterator, _Container>& __rhs)
                    { return __lhs.base() <= __rhs.base(); }
                
                  template<typename _IteratorL, typename _IteratorR, typename _Container>
                    inline bool
                    operator>=(const __normal_iterator<_IteratorL, _Container>& __lhs,
                	       const __normal_iterator<_IteratorR, _Container>& __rhs)
                    { return __lhs.base() >= __rhs.base(); }
                
                  template<typename _Iterator, typename _Container>
                    inline bool
                    operator>=(const __normal_iterator<_Iterator, _Container>& __lhs,
                	       const __normal_iterator<_Iterator, _Container>& __rhs)
                    { return __lhs.base() >= __rhs.base(); }
                
                  // _GLIBCXX_RESOLVE_LIB_DEFECTS
                  // According to the resolution of DR179 not only the various comparison
                  // operators but also operator- must accept mixed iterator/const_iterator
                  // parameters.
                  template<typename _IteratorL, typename _IteratorR, typename _Container>
                #if __cplusplus >= 201103L
                    // DR 685.
                    inline auto
                    operator-(const __normal_iterator<_IteratorL, _Container>& __lhs,
                	      const __normal_iterator<_IteratorR, _Container>& __rhs)
                    -> decltype(__lhs.base() - __rhs.base())
                #else
                    inline typename __normal_iterator<_IteratorL, _Container>::difference_type
                    operator-(const __normal_iterator<_IteratorL, _Container>& __lhs,
                	      const __normal_iterator<_IteratorR, _Container>& __rhs)
                #endif
                    { return __lhs.base() - __rhs.base(); }
                
                  template<typename _Iterator, typename _Container>
                    inline typename __normal_iterator<_Iterator, _Container>::difference_type
    53599982 ->     operator-(const __normal_iterator<_Iterator, _Container>& __lhs,
                	      const __normal_iterator<_Iterator, _Container>& __rhs)
    53599982 ->     { return __lhs.base() - __rhs.base(); }
                
                  template<typename _Iterator, typename _Container>
                    inline __normal_iterator<_Iterator, _Container>
                    operator+(typename __normal_iterator<_Iterator, _Container>::difference_type
                	      __n, const __normal_iterator<_Iterator, _Container>& __i)
                    { return __normal_iterator<_Iterator, _Container>(__i.base() + __n); }
                
                _GLIBCXX_END_NAMESPACE_VERSION
                } // namespace
                
                #if __cplusplus >= 201103L
                
                namespace std _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                  /**
                   * @addtogroup iterators
                   * @{
                   */
                
                  // 24.4.3  Move iterators
                  /**
                   *  Class template move_iterator is an iterator adapter with the same
                   *  behavior as the underlying iterator except that its dereference
                   *  operator implicitly converts the value returned by the underlying
                   *  iterator's dereference operator to an rvalue reference.  Some
                   *  generic algorithms can be called with move iterators to replace
                   *  copying with moving.
                   */
                  template<typename _Iterator>
                    class move_iterator
                    {
                    protected:
                      _Iterator _M_current;
                
                      typedef iterator_traits<_Iterator>		__traits_type;
                
                    public:
                      typedef _Iterator					iterator_type;
                      typedef typename __traits_type::iterator_category iterator_category;
                      typedef typename __traits_type::value_type  	value_type;
                      typedef typename __traits_type::difference_type	difference_type;
                      // NB: DR 680.
                      typedef _Iterator					pointer;
                      typedef value_type&&				reference;
                
                      move_iterator()
                      : _M_current() { }
                
                      explicit
                      move_iterator(iterator_type __i)
                      : _M_current(__i) { }
                
                      template<typename _Iter>
                	move_iterator(const move_iterator<_Iter>& __i)
                	: _M_current(__i.base()) { }
                
                      iterator_type
                      base() const
                      { return _M_current; }
                
                      reference
                      operator*() const
                      { return std::move(*_M_current); }
                
                      pointer
                      operator->() const
                      { return _M_current; }
                
                      move_iterator&
                      operator++()
                      {
                	++_M_current;
                	return *this;
                      }
                
                      move_iterator
                      operator++(int)
                      {
                	move_iterator __tmp = *this;
                	++_M_current;
                	return __tmp;
                      }
                
                      move_iterator&
                      operator--()
                      {
                	--_M_current;
                	return *this;
                      }
                
                      move_iterator
                      operator--(int)
                      {
                	move_iterator __tmp = *this;
                	--_M_current;
                	return __tmp;
                      }
                
                      move_iterator
                      operator+(difference_type __n) const
                      { return move_iterator(_M_current + __n); }
                
                      move_iterator&
                      operator+=(difference_type __n)
                      {
                	_M_current += __n;
                	return *this;
                      }
                
                      move_iterator
                      operator-(difference_type __n) const
                      { return move_iterator(_M_current - __n); }
                    
                      move_iterator&
                      operator-=(difference_type __n)
                      { 
                	_M_current -= __n;
                	return *this;
                      }
                
                      reference
                      operator[](difference_type __n) const
                      { return std::move(_M_current[__n]); }
                    };
                
                  // Note: See __normal_iterator operators note from Gaby to understand
                  // why there are always 2 versions for most of the move_iterator
                  // operators.
                  template<typename _IteratorL, typename _IteratorR>
                    inline bool
                    operator==(const move_iterator<_IteratorL>& __x,
                	       const move_iterator<_IteratorR>& __y)
                    { return __x.base() == __y.base(); }
                
                  template<typename _Iterator>
                    inline bool
                    operator==(const move_iterator<_Iterator>& __x,
                	       const move_iterator<_Iterator>& __y)
                    { return __x.base() == __y.base(); }
                
                  template<typename _IteratorL, typename _IteratorR>
                    inline bool
                    operator!=(const move_iterator<_IteratorL>& __x,
                	       const move_iterator<_IteratorR>& __y)
                    { return !(__x == __y); }
                
                  template<typename _Iterator>
                    inline bool
                    operator!=(const move_iterator<_Iterator>& __x,
                	       const move_iterator<_Iterator>& __y)
                    { return !(__x == __y); }
                
                  template<typename _IteratorL, typename _IteratorR>
                    inline bool
                    operator<(const move_iterator<_IteratorL>& __x,
                	      const move_iterator<_IteratorR>& __y)
                    { return __x.base() < __y.base(); }
                
                  template<typename _Iterator>
                    inline bool
                    operator<(const move_iterator<_Iterator>& __x,
                	      const move_iterator<_Iterator>& __y)
                    { return __x.base() < __y.base(); }
                
                  template<typename _IteratorL, typename _IteratorR>
                    inline bool
                    operator<=(const move_iterator<_IteratorL>& __x,
                	       const move_iterator<_IteratorR>& __y)
                    { return !(__y < __x); }
                
                  template<typename _Iterator>
                    inline bool
                    operator<=(const move_iterator<_Iterator>& __x,
                	       const move_iterator<_Iterator>& __y)
                    { return !(__y < __x); }
                
                  template<typename _IteratorL, typename _IteratorR>
                    inline bool
                    operator>(const move_iterator<_IteratorL>& __x,
                	      const move_iterator<_IteratorR>& __y)
                    { return __y < __x; }
                
                  template<typename _Iterator>
                    inline bool
                    operator>(const move_iterator<_Iterator>& __x,
                	      const move_iterator<_Iterator>& __y)
                    { return __y < __x; }
                
                  template<typename _IteratorL, typename _IteratorR>
                    inline bool
                    operator>=(const move_iterator<_IteratorL>& __x,
                	       const move_iterator<_IteratorR>& __y)
                    { return !(__x < __y); }
                
                  template<typename _Iterator>
                    inline bool
                    operator>=(const move_iterator<_Iterator>& __x,
                	       const move_iterator<_Iterator>& __y)
                    { return !(__x < __y); }
                
                  // DR 685.
                  template<typename _IteratorL, typename _IteratorR>
                    inline auto
                    operator-(const move_iterator<_IteratorL>& __x,
                	      const move_iterator<_IteratorR>& __y)
                    -> decltype(__x.base() - __y.base())
                    { return __x.base() - __y.base(); }
                
                  template<typename _Iterator>
                    inline auto
                    operator-(const move_iterator<_Iterator>& __x,
                	      const move_iterator<_Iterator>& __y)
                    -> decltype(__x.base() - __y.base())
                    { return __x.base() - __y.base(); }
                
                  template<typename _Iterator>
                    inline move_iterator<_Iterator>
                    operator+(typename move_iterator<_Iterator>::difference_type __n,
                	      const move_iterator<_Iterator>& __x)
                    { return __x + __n; }
                
                  template<typename _Iterator>
                    inline move_iterator<_Iterator>
                    make_move_iterator(_Iterator __i)
                    { return move_iterator<_Iterator>(__i); }
                
                  template<typename _Iterator, typename _ReturnType
                    = typename conditional<__move_if_noexcept_cond
                      <typename iterator_traits<_Iterator>::value_type>::value,
                                _Iterator, move_iterator<_Iterator>>::type>
                    inline _ReturnType
                    __make_move_if_noexcept_iterator(_Iterator __i)
                    { return _ReturnType(__i); }
                
                  // @} group iterators
                
                _GLIBCXX_END_NAMESPACE_VERSION
                } // namespace
                
                #define _GLIBCXX_MAKE_MOVE_ITERATOR(_Iter) std::make_move_iterator(_Iter)
                #define _GLIBCXX_MAKE_MOVE_IF_NOEXCEPT_ITERATOR(_Iter) \
                  std::__make_move_if_noexcept_iterator(_Iter)
                #else
                #define _GLIBCXX_MAKE_MOVE_ITERATOR(_Iter) (_Iter)
                #define _GLIBCXX_MAKE_MOVE_IF_NOEXCEPT_ITERATOR(_Iter) (_Iter)
                #endif // C++11
                
                #endif


Top 10 Lines:

     Line      Count

      790  214399928
      726   81119964
      896   53599982
      811   26080000
      823   26080000

Execution Summary:

       15   Executable lines in this file
       15   Lines executed
   100.00   Percent of the file executed

401279874   Total number of line executions
26751991.60   Average executions per line


*** File /usr/include/c++/4.8.2/bits/stl_vector.h:
                // Vector implementation -*- C++ -*-
                
                // Copyright (C) 2001-2013 Free Software Foundation, Inc.
                //
                // This file is part of the GNU ISO C++ Library.  This library is free
                // software; you can redistribute it and/or modify it under the
                // terms of the GNU General Public License as published by the
                // Free Software Foundation; either version 3, or (at your option)
                // any later version.
                
                // This library is distributed in the hope that it will be useful,
                // but WITHOUT ANY WARRANTY; without even the implied warranty of
                // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
                // GNU General Public License for more details.
                
                // Under Section 7 of GPL version 3, you are granted additional
                // permissions described in the GCC Runtime Library Exception, version
                // 3.1, as published by the Free Software Foundation.
                
                // You should have received a copy of the GNU General Public License and
                // a copy of the GCC Runtime Library Exception along with this program;
                // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
                // <http://www.gnu.org/licenses/>.
                
                /*
                 *
                 * Copyright (c) 1994
                 * Hewlett-Packard Company
                 *
                 * Permission to use, copy, modify, distribute and sell this software
                 * and its documentation for any purpose is hereby granted without fee,
                 * provided that the above copyright notice appear in all copies and
                 * that both that copyright notice and this permission notice appear
                 * in supporting documentation.  Hewlett-Packard Company makes no
                 * representations about the suitability of this software for any
                 * purpose.  It is provided "as is" without express or implied warranty.
                 *
                 *
                 * Copyright (c) 1996
                 * Silicon Graphics Computer Systems, Inc.
                 *
                 * Permission to use, copy, modify, distribute and sell this software
                 * and its documentation for any purpose is hereby granted without fee,
                 * provided that the above copyright notice appear in all copies and
                 * that both that copyright notice and this permission notice appear
                 * in supporting documentation.  Silicon Graphics makes no
                 * representations about the suitability of this  software for any
                 * purpose.  It is provided "as is" without express or implied warranty.
                 */
                
                /** @file bits/stl_vector.h
                 *  This is an internal header file, included by other library headers.
                 *  Do not attempt to use it directly. @headername{vector}
                 */
                
                #ifndef _STL_VECTOR_H
                #define _STL_VECTOR_H 1
                
                #include <bits/stl_iterator_base_funcs.h>
                #include <bits/functexcept.h>
                #include <bits/concept_check.h>
                #if __cplusplus >= 201103L
                #include <initializer_list>
                #endif
                
                namespace std _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_CONTAINER
                
                  /// See bits/stl_deque.h's _Deque_base for an explanation.
                  template<typename _Tp, typename _Alloc>
                    struct _Vector_base
                    {
                      typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template
                        rebind<_Tp>::other _Tp_alloc_type;
                      typedef typename __gnu_cxx::__alloc_traits<_Tp_alloc_type>::pointer
                       	pointer;
                
       ##### ->       struct _Vector_impl 
                      : public _Tp_alloc_type
                      {
                	pointer _M_start;
                	pointer _M_finish;
                	pointer _M_end_of_storage;
                
      160000 -> 	_Vector_impl()
      160000 -> 	: _Tp_alloc_type(), _M_start(0), _M_finish(0), _M_end_of_storage(0)
      160000 -> 	{ }
                
                	_Vector_impl(_Tp_alloc_type const& __a)
                	: _Tp_alloc_type(__a), _M_start(0), _M_finish(0), _M_end_of_storage(0)
                	{ }
                
                #if __cplusplus >= 201103L
                	_Vector_impl(_Tp_alloc_type&& __a)
                	: _Tp_alloc_type(std::move(__a)),
                	  _M_start(0), _M_finish(0), _M_end_of_storage(0)
                	{ }
                #endif
                
                	void _M_swap_data(_Vector_impl& __x)
                	{
                	  std::swap(_M_start, __x._M_start);
                	  std::swap(_M_finish, __x._M_finish);
                	  std::swap(_M_end_of_storage, __x._M_end_of_storage);
                	}
                      };
                      
                    public:
                      typedef _Alloc allocator_type;
                
                      _Tp_alloc_type&
   658505498 ->       _M_get_Tp_allocator() _GLIBCXX_NOEXCEPT
   658505498 ->       { return *static_cast<_Tp_alloc_type*>(&this->_M_impl); }
                
                      const _Tp_alloc_type&
     2879964 ->       _M_get_Tp_allocator() const _GLIBCXX_NOEXCEPT
     2879964 ->       { return *static_cast<const _Tp_alloc_type*>(&this->_M_impl); }
                
                      allocator_type
                      get_allocator() const _GLIBCXX_NOEXCEPT
                      { return allocator_type(_M_get_Tp_allocator()); }
                
      160000 ->       _Vector_base()
      160000 ->       : _M_impl() { }
                
                      _Vector_base(const allocator_type& __a)
                      : _M_impl(__a) { }
                
                      _Vector_base(size_t __n)
                      : _M_impl()
                      { _M_create_storage(__n); }
                
                      _Vector_base(size_t __n, const allocator_type& __a)
                      : _M_impl(__a)
                      { _M_create_storage(__n); }
                
                #if __cplusplus >= 201103L
                      _Vector_base(_Tp_alloc_type&& __a)
                      : _M_impl(std::move(__a)) { }
                
                      _Vector_base(_Vector_base&& __x)
                      : _M_impl(std::move(__x._M_get_Tp_allocator()))
                      { this->_M_impl._M_swap_data(__x._M_impl); }
                
                      _Vector_base(_Vector_base&& __x, const allocator_type& __a)
                      : _M_impl(__a)
                      {
                	if (__x.get_allocator() == __a)
                	  this->_M_impl._M_swap_data(__x._M_impl);
                	else
                	  {
                	    size_t __n = __x._M_impl._M_finish - __x._M_impl._M_start;
                	    _M_create_storage(__n);
                	  }
                      }
                #endif
                
       ##### ->       ~_Vector_base()
       ##### ->       { _M_deallocate(this->_M_impl._M_start, this->_M_impl._M_end_of_storage
       ##### -> 		      - this->_M_impl._M_start); }
                
                    public:
                      _Vector_impl _M_impl;
                
                      pointer
     1439982 ->       _M_allocate(size_t __n)
     1439982 ->       { return __n != 0 ? _M_impl.allocate(__n) : 0; }
                
                      void
     1439982 ->       _M_deallocate(pointer __p, size_t __n)
                      {
     1439982 -> 	if (__p)
     1439982 -> 	  _M_impl.deallocate(__p, __n);
     1439982 ->       }
                
                    private:
                      void
                      _M_create_storage(size_t __n)
                      {
                	this->_M_impl._M_start = this->_M_allocate(__n);
                	this->_M_impl._M_finish = this->_M_impl._M_start;
                	this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
                      }
                    };
                
                
                  /**
                   *  @brief A standard container which offers fixed time access to
                   *  individual elements in any order.
                   *
                   *  @ingroup sequences
                   *
                   *  @tparam _Tp  Type of element.
                   *  @tparam _Alloc  Allocator type, defaults to allocator<_Tp>.
                   *
                   *  Meets the requirements of a <a href="tables.html#65">container</a>, a
                   *  <a href="tables.html#66">reversible container</a>, and a
                   *  <a href="tables.html#67">sequence</a>, including the
                   *  <a href="tables.html#68">optional sequence requirements</a> with the
                   *  %exception of @c push_front and @c pop_front.
                   *
                   *  In some terminology a %vector can be described as a dynamic
                   *  C-style array, it offers fast and efficient access to individual
                   *  elements in any order and saves the user from worrying about
                   *  memory and size allocation.  Subscripting ( @c [] ) access is
                   *  also provided as with C-style arrays.
                  */
                  template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
                    class vector : protected _Vector_base<_Tp, _Alloc>
                    {
                      // Concept requirements.
                      typedef typename _Alloc::value_type                _Alloc_value_type;
                      __glibcxx_class_requires(_Tp, _SGIAssignableConcept)
                      __glibcxx_class_requires2(_Tp, _Alloc_value_type, _SameTypeConcept)
                      
                      typedef _Vector_base<_Tp, _Alloc>			 _Base;
                      typedef typename _Base::_Tp_alloc_type		 _Tp_alloc_type;
                      typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type>  _Alloc_traits;
                
                    public:
                      typedef _Tp					 value_type;
                      typedef typename _Base::pointer                    pointer;
                      typedef typename _Alloc_traits::const_pointer      const_pointer;
                      typedef typename _Alloc_traits::reference          reference;
                      typedef typename _Alloc_traits::const_reference    const_reference;
                      typedef __gnu_cxx::__normal_iterator<pointer, vector> iterator;
                      typedef __gnu_cxx::__normal_iterator<const_pointer, vector>
                      const_iterator;
                      typedef std::reverse_iterator<const_iterator>  const_reverse_iterator;
                      typedef std::reverse_iterator<iterator>		 reverse_iterator;
                      typedef size_t					 size_type;
                      typedef ptrdiff_t					 difference_type;
                      typedef _Alloc                        		 allocator_type;
                
                    protected:
                      using _Base::_M_allocate;
                      using _Base::_M_deallocate;
                      using _Base::_M_impl;
                      using _Base::_M_get_Tp_allocator;
                
                    public:
                      // [23.2.4.1] construct/copy/destroy
                      // (assign() and get_allocator() are also listed in this section)
                      /**
                       *  @brief  Default constructor creates no elements.
                       */
      160000 ->       vector()
      160000 ->       : _Base() { }
                
                      /**
                       *  @brief  Creates a %vector with no elements.
                       *  @param  __a  An allocator object.
                       */
                      explicit
                      vector(const allocator_type& __a)
                      : _Base(__a) { }
                
                #if __cplusplus >= 201103L
                      /**
                       *  @brief  Creates a %vector with default constructed elements.
                       *  @param  __n  The number of elements to initially create.
                       *  @param  __a  An allocator.
                       *
                       *  This constructor fills the %vector with @a __n default
                       *  constructed elements.
                       */
                      explicit
                      vector(size_type __n, const allocator_type& __a = allocator_type())
                      : _Base(__n, __a)
                      { _M_default_initialize(__n); }
                
                      /**
                       *  @brief  Creates a %vector with copies of an exemplar element.
                       *  @param  __n  The number of elements to initially create.
                       *  @param  __value  An element to copy.
                       *  @param  __a  An allocator.
                       *
                       *  This constructor fills the %vector with @a __n copies of @a __value.
                       */
                      vector(size_type __n, const value_type& __value,
                	     const allocator_type& __a = allocator_type())
                      : _Base(__n, __a)
                      { _M_fill_initialize(__n, __value); }
                #else
                      /**
                       *  @brief  Creates a %vector with copies of an exemplar element.
                       *  @param  __n  The number of elements to initially create.
                       *  @param  __value  An element to copy.
                       *  @param  __a  An allocator.
                       *
                       *  This constructor fills the %vector with @a __n copies of @a __value.
                       */
                      explicit
                      vector(size_type __n, const value_type& __value = value_type(),
                	     const allocator_type& __a = allocator_type())
                      : _Base(__n, __a)
                      { _M_fill_initialize(__n, __value); }
                #endif
                
                      /**
                       *  @brief  %Vector copy constructor.
                       *  @param  __x  A %vector of identical element and allocator types.
                       *
                       *  The newly-created %vector uses a copy of the allocation
                       *  object used by @a __x.  All the elements of @a __x are copied,
                       *  but any extra memory in
                       *  @a __x (for fast expansion) will not be copied.
                       */
                      vector(const vector& __x)
                      : _Base(__x.size(),
                        _Alloc_traits::_S_select_on_copy(__x._M_get_Tp_allocator()))
                      { this->_M_impl._M_finish =
                	  std::__uninitialized_copy_a(__x.begin(), __x.end(),
                				      this->_M_impl._M_start,
                				      _M_get_Tp_allocator());
                      }
                
                #if __cplusplus >= 201103L
                      /**
                       *  @brief  %Vector move constructor.
                       *  @param  __x  A %vector of identical element and allocator types.
                       *
                       *  The newly-created %vector contains the exact contents of @a __x.
                       *  The contents of @a __x are a valid, but unspecified %vector.
                       */
                      vector(vector&& __x) noexcept
                      : _Base(std::move(__x)) { }
                
                      /// Copy constructor with alternative allocator
                      vector(const vector& __x, const allocator_type& __a)
                      : _Base(__x.size(), __a)
                      { this->_M_impl._M_finish =
                	  std::__uninitialized_copy_a(__x.begin(), __x.end(),
                				      this->_M_impl._M_start,
                				      _M_get_Tp_allocator());
                      }
                
                      /// Move constructor with alternative allocator
                      vector(vector&& __rv, const allocator_type& __m)
                      : _Base(std::move(__rv), __m)
                      {
                	if (__rv.get_allocator() != __m)
                	  {
                	    this->_M_impl._M_finish =
                	      std::__uninitialized_move_a(__rv.begin(), __rv.end(),
                					  this->_M_impl._M_start,
                					  _M_get_Tp_allocator());
                	    __rv.clear();
                	  }
                      }
                
                      /**
                       *  @brief  Builds a %vector from an initializer list.
                       *  @param  __l  An initializer_list.
                       *  @param  __a  An allocator.
                       *
                       *  Create a %vector consisting of copies of the elements in the
                       *  initializer_list @a __l.
                       *
                       *  This will call the element type's copy constructor N times
                       *  (where N is @a __l.size()) and do no memory reallocation.
                       */
                      vector(initializer_list<value_type> __l,
                	     const allocator_type& __a = allocator_type())
                      : _Base(__a)
                      {
                	_M_range_initialize(__l.begin(), __l.end(),
                			    random_access_iterator_tag());
                      }
                #endif
                
                      /**
                       *  @brief  Builds a %vector from a range.
                       *  @param  __first  An input iterator.
                       *  @param  __last  An input iterator.
                       *  @param  __a  An allocator.
                       *
                       *  Create a %vector consisting of copies of the elements from
                       *  [first,last).
                       *
                       *  If the iterators are forward, bidirectional, or
                       *  random-access, then this will call the elements' copy
                       *  constructor N times (where N is distance(first,last)) and do
                       *  no memory reallocation.  But if only input iterators are
                       *  used, then this will do at most 2N calls to the copy
                       *  constructor, and logN memory reallocations.
                       */
                #if __cplusplus >= 201103L
                      template<typename _InputIterator,
                	       typename = std::_RequireInputIter<_InputIterator>>
                        vector(_InputIterator __first, _InputIterator __last,
                	       const allocator_type& __a = allocator_type())
                	: _Base(__a)
                        { _M_initialize_dispatch(__first, __last, __false_type()); }
                #else
                      template<typename _InputIterator>
                        vector(_InputIterator __first, _InputIterator __last,
                	       const allocator_type& __a = allocator_type())
                	: _Base(__a)
                        {
                	  // Check whether it's an integral type.  If so, it's not an iterator.
                	  typedef typename std::__is_integer<_InputIterator>::__type _Integral;
                	  _M_initialize_dispatch(__first, __last, _Integral());
                	}
                #endif
                
                      /**
                       *  The dtor only erases the elements, and note that if the
                       *  elements themselves are pointers, the pointed-to memory is
                       *  not touched in any way.  Managing the pointer is the user's
                       *  responsibility.
                       */
       ##### ->       ~vector() _GLIBCXX_NOEXCEPT
       ##### ->       { std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
       ##### -> 		      _M_get_Tp_allocator()); }
                
                      /**
                       *  @brief  %Vector assignment operator.
                       *  @param  __x  A %vector of identical element and allocator types.
                       *
                       *  All the elements of @a __x are copied, but any extra memory in
                       *  @a __x (for fast expansion) will not be copied.  Unlike the
                       *  copy constructor, the allocator object is not copied.
                       */
                      vector&
                      operator=(const vector& __x);
                
                #if __cplusplus >= 201103L
                      /**
                       *  @brief  %Vector move assignment operator.
                       *  @param  __x  A %vector of identical element and allocator types.
                       *
                       *  The contents of @a __x are moved into this %vector (without copying,
                       *  if the allocators permit it).
                       *  @a __x is a valid, but unspecified %vector.
                       */
                      vector&
                      operator=(vector&& __x) noexcept(_Alloc_traits::_S_nothrow_move())
                      {
                        constexpr bool __move_storage =
                          _Alloc_traits::_S_propagate_on_move_assign()
                          || _Alloc_traits::_S_always_equal();
                        _M_move_assign(std::move(__x),
                                       integral_constant<bool, __move_storage>());
                	return *this;
                      }
                
                      /**
                       *  @brief  %Vector list assignment operator.
                       *  @param  __l  An initializer_list.
                       *
                       *  This function fills a %vector with copies of the elements in the
                       *  initializer list @a __l.
                       *
                       *  Note that the assignment completely changes the %vector and
                       *  that the resulting %vector's size is the same as the number
                       *  of elements assigned.  Old data may be lost.
                       */
                      vector&
                      operator=(initializer_list<value_type> __l)
                      {
                	this->assign(__l.begin(), __l.end());
                	return *this;
                      }
                #endif
                
                      /**
                       *  @brief  Assigns a given value to a %vector.
                       *  @param  __n  Number of elements to be assigned.
                       *  @param  __val  Value to be assigned.
                       *
                       *  This function fills a %vector with @a __n copies of the given
                       *  value.  Note that the assignment completely changes the
                       *  %vector and that the resulting %vector's size is the same as
                       *  the number of elements assigned.  Old data may be lost.
                       */
                      void
                      assign(size_type __n, const value_type& __val)
                      { _M_fill_assign(__n, __val); }
                
                      /**
                       *  @brief  Assigns a range to a %vector.
                       *  @param  __first  An input iterator.
                       *  @param  __last   An input iterator.
                       *
                       *  This function fills a %vector with copies of the elements in the
                       *  range [__first,__last).
                       *
                       *  Note that the assignment completely changes the %vector and
                       *  that the resulting %vector's size is the same as the number
                       *  of elements assigned.  Old data may be lost.
                       */
                #if __cplusplus >= 201103L
                      template<typename _InputIterator,
                	       typename = std::_RequireInputIter<_InputIterator>>
                        void
                        assign(_InputIterator __first, _InputIterator __last)
                        { _M_assign_dispatch(__first, __last, __false_type()); }
                #else
                      template<typename _InputIterator>
                        void
                        assign(_InputIterator __first, _InputIterator __last)
                        {
                	  // Check whether it's an integral type.  If so, it's not an iterator.
                	  typedef typename std::__is_integer<_InputIterator>::__type _Integral;
                	  _M_assign_dispatch(__first, __last, _Integral());
                	}
                #endif
                
                #if __cplusplus >= 201103L
                      /**
                       *  @brief  Assigns an initializer list to a %vector.
                       *  @param  __l  An initializer_list.
                       *
                       *  This function fills a %vector with copies of the elements in the
                       *  initializer list @a __l.
                       *
                       *  Note that the assignment completely changes the %vector and
                       *  that the resulting %vector's size is the same as the number
                       *  of elements assigned.  Old data may be lost.
                       */
                      void
                      assign(initializer_list<value_type> __l)
                      { this->assign(__l.begin(), __l.end()); }
                #endif
                
                      /// Get a copy of the memory allocation object.
                      using _Base::get_allocator;
                
                      // iterators
                      /**
                       *  Returns a read/write iterator that points to the first
                       *  element in the %vector.  Iteration is done in ordinary
                       *  element order.
                       */
                      iterator
    27519982 ->       begin() _GLIBCXX_NOEXCEPT
    27519982 ->       { return iterator(this->_M_impl._M_start); }
                
                      /**
                       *  Returns a read-only (constant) iterator that points to the
                       *  first element in the %vector.  Iteration is done in ordinary
                       *  element order.
                       */
                      const_iterator
                      begin() const _GLIBCXX_NOEXCEPT
                      { return const_iterator(this->_M_impl._M_start); }
                
                      /**
                       *  Returns a read/write iterator that points one past the last
                       *  element in the %vector.  Iteration is done in ordinary
                       *  element order.
                       */
                      iterator
    53599982 ->       end() _GLIBCXX_NOEXCEPT
    53599982 ->       { return iterator(this->_M_impl._M_finish); }
                
                      /**
                       *  Returns a read-only (constant) iterator that points one past
                       *  the last element in the %vector.  Iteration is done in
                       *  ordinary element order.
                       */
                      const_iterator
                      end() const _GLIBCXX_NOEXCEPT
                      { return const_iterator(this->_M_impl._M_finish); }
                
                      /**
                       *  Returns a read/write reverse iterator that points to the
                       *  last element in the %vector.  Iteration is done in reverse
                       *  element order.
                       */
                      reverse_iterator
                      rbegin() _GLIBCXX_NOEXCEPT
                      { return reverse_iterator(end()); }
                
                      /**
                       *  Returns a read-only (constant) reverse iterator that points
                       *  to the last element in the %vector.  Iteration is done in
                       *  reverse element order.
                       */
                      const_reverse_iterator
                      rbegin() const _GLIBCXX_NOEXCEPT
                      { return const_reverse_iterator(end()); }
                
                      /**
                       *  Returns a read/write reverse iterator that points to one
                       *  before the first element in the %vector.  Iteration is done
                       *  in reverse element order.
                       */
                      reverse_iterator
                      rend() _GLIBCXX_NOEXCEPT
                      { return reverse_iterator(begin()); }
                
                      /**
                       *  Returns a read-only (constant) reverse iterator that points
                       *  to one before the first element in the %vector.  Iteration
                       *  is done in reverse element order.
                       */
                      const_reverse_iterator
                      rend() const _GLIBCXX_NOEXCEPT
                      { return const_reverse_iterator(begin()); }
                
                #if __cplusplus >= 201103L
                      /**
                       *  Returns a read-only (constant) iterator that points to the
                       *  first element in the %vector.  Iteration is done in ordinary
                       *  element order.
                       */
                      const_iterator
                      cbegin() const noexcept
                      { return const_iterator(this->_M_impl._M_start); }
                
                      /**
                       *  Returns a read-only (constant) iterator that points one past
                       *  the last element in the %vector.  Iteration is done in
                       *  ordinary element order.
                       */
                      const_iterator
                      cend() const noexcept
                      { return const_iterator(this->_M_impl._M_finish); }
                
                      /**
                       *  Returns a read-only (constant) reverse iterator that points
                       *  to the last element in the %vector.  Iteration is done in
                       *  reverse element order.
                       */
                      const_reverse_iterator
                      crbegin() const noexcept
                      { return const_reverse_iterator(end()); }
                
                      /**
                       *  Returns a read-only (constant) reverse iterator that points
                       *  to one before the first element in the %vector.  Iteration
                       *  is done in reverse element order.
                       */
                      const_reverse_iterator
                      crend() const noexcept
                      { return const_reverse_iterator(begin()); }
                #endif
                
                      // [23.2.4.2] capacity
                      /**  Returns the number of elements in the %vector.  */
                      size_type
   311574376 ->       size() const _GLIBCXX_NOEXCEPT
   311574376 ->       { return size_type(this->_M_impl._M_finish - this->_M_impl._M_start); }
                
                      /**  Returns the size() of the largest possible %vector.  */
                      size_type
     2879964 ->       max_size() const _GLIBCXX_NOEXCEPT
     2879964 ->       { return _Alloc_traits::max_size(_M_get_Tp_allocator()); }
                
                #if __cplusplus >= 201103L
                      /**
                       *  @brief  Resizes the %vector to the specified number of elements.
                       *  @param  __new_size  Number of elements the %vector should contain.
                       *
                       *  This function will %resize the %vector to the specified
                       *  number of elements.  If the number is smaller than the
                       *  %vector's current size the %vector is truncated, otherwise
                       *  default constructed elements are appended.
                       */
                      void
                      resize(size_type __new_size)
                      {
                	if (__new_size > size())
                	  _M_default_append(__new_size - size());
                	else if (__new_size < size())
                	  _M_erase_at_end(this->_M_impl._M_start + __new_size);
                      }
                
                      /**
                       *  @brief  Resizes the %vector to the specified number of elements.
                       *  @param  __new_size  Number of elements the %vector should contain.
                       *  @param  __x  Data with which new elements should be populated.
                       *
                       *  This function will %resize the %vector to the specified
                       *  number of elements.  If the number is smaller than the
                       *  %vector's current size the %vector is truncated, otherwise
                       *  the %vector is extended and new elements are populated with
                       *  given data.
                       */
                      void
                      resize(size_type __new_size, const value_type& __x)
                      {
                	if (__new_size > size())
                	  insert(end(), __new_size - size(), __x);
                	else if (__new_size < size())
                	  _M_erase_at_end(this->_M_impl._M_start + __new_size);
                      }
                #else
                      /**
                       *  @brief  Resizes the %vector to the specified number of elements.
                       *  @param  __new_size  Number of elements the %vector should contain.
                       *  @param  __x  Data with which new elements should be populated.
                       *
                       *  This function will %resize the %vector to the specified
                       *  number of elements.  If the number is smaller than the
                       *  %vector's current size the %vector is truncated, otherwise
                       *  the %vector is extended and new elements are populated with
                       *  given data.
                       */
                      void
                      resize(size_type __new_size, value_type __x = value_type())
                      {
                	if (__new_size > size())
                	  insert(end(), __new_size - size(), __x);
                	else if (__new_size < size())
                	  _M_erase_at_end(this->_M_impl._M_start + __new_size);
                      }
                #endif
                
                #if __cplusplus >= 201103L
                      /**  A non-binding request to reduce capacity() to size().  */
                      void
                      shrink_to_fit()
                      { _M_shrink_to_fit(); }
                #endif
                
                      /**
                       *  Returns the total number of elements that the %vector can
                       *  hold before needing to allocate more memory.
                       */
                      size_type
                      capacity() const _GLIBCXX_NOEXCEPT
                      { return size_type(this->_M_impl._M_end_of_storage
                			 - this->_M_impl._M_start); }
                
                      /**
                       *  Returns true if the %vector is empty.  (Thus begin() would
                       *  equal end().)
                       */
                      bool
                      empty() const _GLIBCXX_NOEXCEPT
                      { return begin() == end(); }
                
                      /**
                       *  @brief  Attempt to preallocate enough memory for specified number of
                       *          elements.
                       *  @param  __n  Number of elements required.
                       *  @throw  std::length_error  If @a n exceeds @c max_size().
                       *
                       *  This function attempts to reserve enough memory for the
                       *  %vector to hold the specified number of elements.  If the
                       *  number requested is more than max_size(), length_error is
                       *  thrown.
                       *
                       *  The advantage of this function is that if optimal code is a
                       *  necessity and the user can determine the number of elements
                       *  that will be required, the user can reserve the memory in
                       *  %advance, and thus prevent a possible reallocation of memory
                       *  and copying of %vector data.
                       */
                      void
                      reserve(size_type __n);
                
                      // element access
                      /**
                       *  @brief  Subscript access to the data contained in the %vector.
                       *  @param __n The index of the element for which data should be
                       *  accessed.
                       *  @return  Read/write reference to data.
                       *
                       *  This operator allows for easy, array-style, data access.
                       *  Note that data access with this operator is unchecked and
                       *  out_of_range lookups are not defined. (For checked lookups
                       *  see at().)
                       */
                      reference
   305647461 ->       operator[](size_type __n)
   305647461 ->       { return *(this->_M_impl._M_start + __n); }
                
                      /**
                       *  @brief  Subscript access to the data contained in the %vector.
                       *  @param __n The index of the element for which data should be
                       *  accessed.
                       *  @return  Read-only (constant) reference to data.
                       *
                       *  This operator allows for easy, array-style, data access.
                       *  Note that data access with this operator is unchecked and
                       *  out_of_range lookups are not defined. (For checked lookups
                       *  see at().)
                       */
                      const_reference
                      operator[](size_type __n) const
                      { return *(this->_M_impl._M_start + __n); }
                
                    protected:
                      /// Safety check used only from at().
                      void
                      _M_range_check(size_type __n) const
                      {
                	if (__n >= this->size())
                	  __throw_out_of_range(__N("vector::_M_range_check"));
                      }
                
                    public:
                      /**
                       *  @brief  Provides access to the data contained in the %vector.
                       *  @param __n The index of the element for which data should be
                       *  accessed.
                       *  @return  Read/write reference to data.
                       *  @throw  std::out_of_range  If @a __n is an invalid index.
                       *
                       *  This function provides for safer data access.  The parameter
                       *  is first checked that it is in the range of the vector.  The
                       *  function throws out_of_range if the check fails.
                       */
                      reference
                      at(size_type __n)
                      {
                	_M_range_check(__n);
                	return (*this)[__n]; 
                      }
                
                      /**
                       *  @brief  Provides access to the data contained in the %vector.
                       *  @param __n The index of the element for which data should be
                       *  accessed.
                       *  @return  Read-only (constant) reference to data.
                       *  @throw  std::out_of_range  If @a __n is an invalid index.
                       *
                       *  This function provides for safer data access.  The parameter
                       *  is first checked that it is in the range of the vector.  The
                       *  function throws out_of_range if the check fails.
                       */
                      const_reference
                      at(size_type __n) const
                      {
                	_M_range_check(__n);
                	return (*this)[__n];
                      }
                
                      /**
                       *  Returns a read/write reference to the data at the first
                       *  element of the %vector.
                       */
                      reference
                      front()
                      { return *begin(); }
                
                      /**
                       *  Returns a read-only (constant) reference to the data at the first
                       *  element of the %vector.
                       */
                      const_reference
                      front() const
                      { return *begin(); }
                
                      /**
                       *  Returns a read/write reference to the data at the last
                       *  element of the %vector.
                       */
                      reference
                      back()
                      { return *(end() - 1); }
                      
                      /**
                       *  Returns a read-only (constant) reference to the data at the
                       *  last element of the %vector.
                       */
                      const_reference
                      back() const
                      { return *(end() - 1); }
                
                      // _GLIBCXX_RESOLVE_LIB_DEFECTS
                      // DR 464. Suggestion for new member functions in standard containers.
                      // data access
                      /**
                       *   Returns a pointer such that [data(), data() + size()) is a valid
                       *   range.  For a non-empty %vector, data() == &front().
                       */
                #if __cplusplus >= 201103L
                      _Tp*
                #else
                      pointer
                #endif
                      data() _GLIBCXX_NOEXCEPT
                      { return std::__addressof(front()); }
                
                #if __cplusplus >= 201103L
                      const _Tp*
                #else
                      const_pointer
                #endif
                      data() const _GLIBCXX_NOEXCEPT
                      { return std::__addressof(front()); }
                
                      // [23.2.4.3] modifiers
                      /**
                       *  @brief  Add data to the end of the %vector.
                       *  @param  __x  Data to be added.
                       *
                       *  This is a typical stack operation.  The function creates an
                       *  element at the end of the %vector and assigns the given data
                       *  to it.  Due to the nature of a %vector this operation can be
                       *  done in constant time if the %vector has preallocated space
                       *  available.
                       */
                      void
  3783529118 ->       push_back(const value_type& __x)
                      {
  3783529118 -> 	if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
                	  {
  3783529118 -> 	    _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
  3783529118 -> 	                             __x);
  3783529118 -> 	    ++this->_M_impl._M_finish;
                	  }
                	else
                #if __cplusplus >= 201103L
                	  _M_emplace_back_aux(__x);
                #else
  3783529118 -> 	  _M_insert_aux(end(), __x);
                #endif
  3783529118 ->       }
                
                #if __cplusplus >= 201103L
                      void
                      push_back(value_type&& __x)
                      { emplace_back(std::move(__x)); }
                
                      template<typename... _Args>
                        void
                        emplace_back(_Args&&... __args);
                #endif
                
                      /**
                       *  @brief  Removes last element.
                       *
                       *  This is a typical stack operation. It shrinks the %vector by one.
                       *
                       *  Note that no data is returned, and if the last element's
                       *  data is needed, it should be retrieved before pop_back() is
                       *  called.
                       */
                      void
                      pop_back()
                      {
                	--this->_M_impl._M_finish;
                	_Alloc_traits::destroy(this->_M_impl, this->_M_impl._M_finish);
                      }
                
                #if __cplusplus >= 201103L
                      /**
                       *  @brief  Inserts an object in %vector before specified iterator.
                       *  @param  __position  An iterator into the %vector.
                       *  @param  __args  Arguments.
                       *  @return  An iterator that points to the inserted data.
                       *
                       *  This function will insert an object of type T constructed
                       *  with T(std::forward<Args>(args)...) before the specified location.
                       *  Note that this kind of operation could be expensive for a %vector
                       *  and if it is frequently used the user should consider using
                       *  std::list.
                       */
                      template<typename... _Args>
                        iterator
                        emplace(iterator __position, _Args&&... __args);
                #endif
                
                      /**
                       *  @brief  Inserts given value into %vector before specified iterator.
                       *  @param  __position  An iterator into the %vector.
                       *  @param  __x  Data to be inserted.
                       *  @return  An iterator that points to the inserted data.
                       *
                       *  This function will insert a copy of the given value before
                       *  the specified location.  Note that this kind of operation
                       *  could be expensive for a %vector and if it is frequently
                       *  used the user should consider using std::list.
                       */
                      iterator
                      insert(iterator __position, const value_type& __x);
                
                #if __cplusplus >= 201103L
                      /**
                       *  @brief  Inserts given rvalue into %vector before specified iterator.
                       *  @param  __position  An iterator into the %vector.
                       *  @param  __x  Data to be inserted.
                       *  @return  An iterator that points to the inserted data.
                       *
                       *  This function will insert a copy of the given rvalue before
                       *  the specified location.  Note that this kind of operation
                       *  could be expensive for a %vector and if it is frequently
                       *  used the user should consider using std::list.
                       */
                      iterator
                      insert(iterator __position, value_type&& __x)
                      { return emplace(__position, std::move(__x)); }
                
                      /**
                       *  @brief  Inserts an initializer_list into the %vector.
                       *  @param  __position  An iterator into the %vector.
                       *  @param  __l  An initializer_list.
                       *
                       *  This function will insert copies of the data in the 
                       *  initializer_list @a l into the %vector before the location
                       *  specified by @a position.
                       *
                       *  Note that this kind of operation could be expensive for a
                       *  %vector and if it is frequently used the user should
                       *  consider using std::list.
                       */
                      void
                      insert(iterator __position, initializer_list<value_type> __l)
                      { this->insert(__position, __l.begin(), __l.end()); }
                #endif
                
                      /**
                       *  @brief  Inserts a number of copies of given data into the %vector.
                       *  @param  __position  An iterator into the %vector.
                       *  @param  __n  Number of elements to be inserted.
                       *  @param  __x  Data to be inserted.
                       *
                       *  This function will insert a specified number of copies of
                       *  the given data before the location specified by @a position.
                       *
                       *  Note that this kind of operation could be expensive for a
                       *  %vector and if it is frequently used the user should
                       *  consider using std::list.
                       */
                      void
                      insert(iterator __position, size_type __n, const value_type& __x)
                      { _M_fill_insert(__position, __n, __x); }
                
                      /**
                       *  @brief  Inserts a range into the %vector.
                       *  @param  __position  An iterator into the %vector.
                       *  @param  __first  An input iterator.
                       *  @param  __last   An input iterator.
                       *
                       *  This function will insert copies of the data in the range
                       *  [__first,__last) into the %vector before the location specified
                       *  by @a pos.
                       *
                       *  Note that this kind of operation could be expensive for a
                       *  %vector and if it is frequently used the user should
                       *  consider using std::list.
                       */
                #if __cplusplus >= 201103L
                      template<typename _InputIterator,
                	       typename = std::_RequireInputIter<_InputIterator>>
                        void
                        insert(iterator __position, _InputIterator __first,
                	       _InputIterator __last)
                        { _M_insert_dispatch(__position, __first, __last, __false_type()); }
                #else
                      template<typename _InputIterator>
                        void
                        insert(iterator __position, _InputIterator __first,
                	       _InputIterator __last)
                        {
                	  // Check whether it's an integral type.  If so, it's not an iterator.
                	  typedef typename std::__is_integer<_InputIterator>::__type _Integral;
                	  _M_insert_dispatch(__position, __first, __last, _Integral());
                	}
                #endif
                
                      /**
                       *  @brief  Remove element at given position.
                       *  @param  __position  Iterator pointing to element to be erased.
                       *  @return  An iterator pointing to the next element (or end()).
                       *
                       *  This function will erase the element at the given position and thus
                       *  shorten the %vector by one.
                       *
                       *  Note This operation could be expensive and if it is
                       *  frequently used the user should consider using std::list.
                       *  The user is also cautioned that this function only erases
                       *  the element, and that if the element is itself a pointer,
                       *  the pointed-to memory is not touched in any way.  Managing
                       *  the pointer is the user's responsibility.
                       */
                      iterator
                      erase(iterator __position);
                
                      /**
                       *  @brief  Remove a range of elements.
                       *  @param  __first  Iterator pointing to the first element to be erased.
                       *  @param  __last  Iterator pointing to one past the last element to be
                       *                  erased.
                       *  @return  An iterator pointing to the element pointed to by @a __last
                       *           prior to erasing (or end()).
                       *
                       *  This function will erase the elements in the range
                       *  [__first,__last) and shorten the %vector accordingly.
                       *
                       *  Note This operation could be expensive and if it is
                       *  frequently used the user should consider using std::list.
                       *  The user is also cautioned that this function only erases
                       *  the elements, and that if the elements themselves are
                       *  pointers, the pointed-to memory is not touched in any way.
                       *  Managing the pointer is the user's responsibility.
                       */
                      iterator
                      erase(iterator __first, iterator __last);
                
                      /**
                       *  @brief  Swaps data with another %vector.
                       *  @param  __x  A %vector of the same element and allocator types.
                       *
                       *  This exchanges the elements between two vectors in constant time.
                       *  (Three pointers, so it should be quite fast.)
                       *  Note that the global std::swap() function is specialized such that
                       *  std::swap(v1,v2) will feed to this function.
                       */
                      void
                      swap(vector& __x)
                #if __cplusplus >= 201103L
                			noexcept(_Alloc_traits::_S_nothrow_swap())
                #endif
                      {
                	this->_M_impl._M_swap_data(__x._M_impl);
                	_Alloc_traits::_S_on_swap(_M_get_Tp_allocator(),
                	                          __x._M_get_Tp_allocator());
                      }
                
                      /**
                       *  Erases all the elements.  Note that this function only erases the
                       *  elements, and that if the elements themselves are pointers, the
                       *  pointed-to memory is not touched in any way.  Managing the pointer is
                       *  the user's responsibility.
                       */
                      void
   654185552 ->       clear() _GLIBCXX_NOEXCEPT
   654185552 ->       { _M_erase_at_end(this->_M_impl._M_start); }
                
                    protected:
                      /**
                       *  Memory expansion handler.  Uses the member allocation function to
                       *  obtain @a n bytes of memory, and then copies [first,last) into it.
                       */
                      template<typename _ForwardIterator>
                        pointer
                        _M_allocate_and_copy(size_type __n,
                			     _ForwardIterator __first, _ForwardIterator __last)
                        {
                	  pointer __result = this->_M_allocate(__n);
                	  __try
                	    {
                	      std::__uninitialized_copy_a(__first, __last, __result,
                					  _M_get_Tp_allocator());
                	      return __result;
                	    }
                	  __catch(...)
                	    {
                	      _M_deallocate(__result, __n);
                	      __throw_exception_again;
                	    }
                	}
                
                
                      // Internal constructor functions follow.
                
                      // Called by the range constructor to implement [23.1.1]/9
                
                      // _GLIBCXX_RESOLVE_LIB_DEFECTS
                      // 438. Ambiguity in the "do the right thing" clause
                      template<typename _Integer>
                        void
                        _M_initialize_dispatch(_Integer __n, _Integer __value, __true_type)
                        {
                	  this->_M_impl._M_start = _M_allocate(static_cast<size_type>(__n));
                	  this->_M_impl._M_end_of_storage =
                	    this->_M_impl._M_start + static_cast<size_type>(__n);
                	  _M_fill_initialize(static_cast<size_type>(__n), __value);
                	}
                
                      // Called by the range constructor to implement [23.1.1]/9
                      template<typename _InputIterator>
                        void
                        _M_initialize_dispatch(_InputIterator __first, _InputIterator __last,
                			       __false_type)
                        {
                	  typedef typename std::iterator_traits<_InputIterator>::
                	    iterator_category _IterCategory;
                	  _M_range_initialize(__first, __last, _IterCategory());
                	}
                
                      // Called by the second initialize_dispatch above
                      template<typename _InputIterator>
                        void
                        _M_range_initialize(_InputIterator __first,
                			    _InputIterator __last, std::input_iterator_tag)
                        {
                	  for (; __first != __last; ++__first)
                #if __cplusplus >= 201103L
                	    emplace_back(*__first);
                #else
                	    push_back(*__first);
                #endif
                	}
                
                      // Called by the second initialize_dispatch above
                      template<typename _ForwardIterator>
                        void
                        _M_range_initialize(_ForwardIterator __first,
                			    _ForwardIterator __last, std::forward_iterator_tag)
                        {
                	  const size_type __n = std::distance(__first, __last);
                	  this->_M_impl._M_start = this->_M_allocate(__n);
                	  this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
                	  this->_M_impl._M_finish =
                	    std::__uninitialized_copy_a(__first, __last,
                					this->_M_impl._M_start,
                					_M_get_Tp_allocator());
                	}
                
                      // Called by the first initialize_dispatch above and by the
                      // vector(n,value,a) constructor.
                      void
                      _M_fill_initialize(size_type __n, const value_type& __value)
                      {
                	std::__uninitialized_fill_n_a(this->_M_impl._M_start, __n, __value, 
                				      _M_get_Tp_allocator());
                	this->_M_impl._M_finish = this->_M_impl._M_end_of_storage;
                      }
                
                #if __cplusplus >= 201103L
                      // Called by the vector(n) constructor.
                      void
                      _M_default_initialize(size_type __n)
                      {
                	std::__uninitialized_default_n_a(this->_M_impl._M_start, __n, 
                					 _M_get_Tp_allocator());
                	this->_M_impl._M_finish = this->_M_impl._M_end_of_storage;
                      }
                #endif
                
                      // Internal assign functions follow.  The *_aux functions do the actual
                      // assignment work for the range versions.
                
                      // Called by the range assign to implement [23.1.1]/9
                
                      // _GLIBCXX_RESOLVE_LIB_DEFECTS
                      // 438. Ambiguity in the "do the right thing" clause
                      template<typename _Integer>
                        void
                        _M_assign_dispatch(_Integer __n, _Integer __val, __true_type)
                        { _M_fill_assign(__n, __val); }
                
                      // Called by the range assign to implement [23.1.1]/9
                      template<typename _InputIterator>
                        void
                        _M_assign_dispatch(_InputIterator __first, _InputIterator __last,
                			   __false_type)
                        {
                	  typedef typename std::iterator_traits<_InputIterator>::
                	    iterator_category _IterCategory;
                	  _M_assign_aux(__first, __last, _IterCategory());
                	}
                
                      // Called by the second assign_dispatch above
                      template<typename _InputIterator>
                        void
                        _M_assign_aux(_InputIterator __first, _InputIterator __last,
                		      std::input_iterator_tag);
                
                      // Called by the second assign_dispatch above
                      template<typename _ForwardIterator>
                        void
                        _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
                		      std::forward_iterator_tag);
                
                      // Called by assign(n,t), and the range assign when it turns out
                      // to be the same thing.
                      void
                      _M_fill_assign(size_type __n, const value_type& __val);
                
                
                      // Internal insert functions follow.
                
                      // Called by the range insert to implement [23.1.1]/9
                
                      // _GLIBCXX_RESOLVE_LIB_DEFECTS
                      // 438. Ambiguity in the "do the right thing" clause
                      template<typename _Integer>
                        void
                        _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __val,
                			   __true_type)
                        { _M_fill_insert(__pos, __n, __val); }
                
                      // Called by the range insert to implement [23.1.1]/9
                      template<typename _InputIterator>
                        void
                        _M_insert_dispatch(iterator __pos, _InputIterator __first,
                			   _InputIterator __last, __false_type)
                        {
                	  typedef typename std::iterator_traits<_InputIterator>::
                	    iterator_category _IterCategory;
                	  _M_range_insert(__pos, __first, __last, _IterCategory());
                	}
                
                      // Called by the second insert_dispatch above
                      template<typename _InputIterator>
                        void
                        _M_range_insert(iterator __pos, _InputIterator __first,
                			_InputIterator __last, std::input_iterator_tag);
                
                      // Called by the second insert_dispatch above
                      template<typename _ForwardIterator>
                        void
                        _M_range_insert(iterator __pos, _ForwardIterator __first,
                			_ForwardIterator __last, std::forward_iterator_tag);
                
                      // Called by insert(p,n,x), and the range insert when it turns out to be
                      // the same thing.
                      void
                      _M_fill_insert(iterator __pos, size_type __n, const value_type& __x);
                
                #if __cplusplus >= 201103L
                      // Called by resize(n).
                      void
                      _M_default_append(size_type __n);
                
                      bool
                      _M_shrink_to_fit();
                #endif
                
                      // Called by insert(p,x)
                #if __cplusplus < 201103L
                      void
                      _M_insert_aux(iterator __position, const value_type& __x);
                #else
                      template<typename... _Args>
                        void
                        _M_insert_aux(iterator __position, _Args&&... __args);
                
                      template<typename... _Args>
                        void
                        _M_emplace_back_aux(_Args&&... __args);
                #endif
                
                      // Called by the latter.
                      size_type
     1439982 ->       _M_check_len(size_type __n, const char* __s) const
                      {
     1439982 -> 	if (max_size() - size() < __n)
     1439982 -> 	  __throw_length_error(__N(__s));
                
     1439982 -> 	const size_type __len = size() + std::max(size(), __n);
     1439982 -> 	return (__len < size() || __len > max_size()) ? max_size() : __len;
     1439982 ->       }
                
                      // Internal erase functions follow.
                
                      // Called by erase(q1,q2), clear(), resize(), _M_fill_assign,
                      // _M_assign_aux.
                      void
   654185552 ->       _M_erase_at_end(pointer __pos)
                      {
   654185552 -> 	std::_Destroy(__pos, this->_M_impl._M_finish, _M_get_Tp_allocator());
   654185552 -> 	this->_M_impl._M_finish = __pos;
   654185552 ->       }
                
                #if __cplusplus >= 201103L
                    private:
                      // Constant-time move assignment when source object's memory can be
                      // moved, either because the source's allocator will move too
                      // or because the allocators are equal.
                      void
                      _M_move_assign(vector&& __x, std::true_type) noexcept
                      {
                	vector __tmp(get_allocator());
                	this->_M_impl._M_swap_data(__tmp._M_impl);
                	this->_M_impl._M_swap_data(__x._M_impl);
                	if (_Alloc_traits::_S_propagate_on_move_assign())
                	  std::__alloc_on_move(_M_get_Tp_allocator(),
                			       __x._M_get_Tp_allocator());
                      }
                
                      // Do move assignment when it might not be possible to move source
                      // object's memory, resulting in a linear-time operation.
                      void
                      _M_move_assign(vector&& __x, std::false_type)
                      {
                	if (__x._M_get_Tp_allocator() == this->_M_get_Tp_allocator())
                	  _M_move_assign(std::move(__x), std::true_type());
                	else
                	  {
                	    // The rvalue's allocator cannot be moved and is not equal,
                	    // so we need to individually move each element.
                	    this->assign(std::__make_move_if_noexcept_iterator(__x.begin()),
                			 std::__make_move_if_noexcept_iterator(__x.end()));
                	    __x.clear();
                	  }
                      }
                #endif
                    };
                
                
                  /**
                   *  @brief  Vector equality comparison.
                   *  @param  __x  A %vector.
                   *  @param  __y  A %vector of the same type as @a __x.
                   *  @return  True iff the size and elements of the vectors are equal.
                   *
                   *  This is an equivalence relation.  It is linear in the size of the
                   *  vectors.  Vectors are considered equivalent if their sizes are equal,
                   *  and if corresponding elements compare equal.
                  */
                  template<typename _Tp, typename _Alloc>
                    inline bool
                    operator==(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
                    { return (__x.size() == __y.size()
                	      && std::equal(__x.begin(), __x.end(), __y.begin())); }
                
                  /**
                   *  @brief  Vector ordering relation.
                   *  @param  __x  A %vector.
                   *  @param  __y  A %vector of the same type as @a __x.
                   *  @return  True iff @a __x is lexicographically less than @a __y.
                   *
                   *  This is a total ordering relation.  It is linear in the size of the
                   *  vectors.  The elements must be comparable with @c <.
                   *
                   *  See std::lexicographical_compare() for how the determination is made.
                  */
                  template<typename _Tp, typename _Alloc>
                    inline bool
                    operator<(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
                    { return std::lexicographical_compare(__x.begin(), __x.end(),
                					  __y.begin(), __y.end()); }
                
                  /// Based on operator==
                  template<typename _Tp, typename _Alloc>
                    inline bool
                    operator!=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
                    { return !(__x == __y); }
                
                  /// Based on operator<
                  template<typename _Tp, typename _Alloc>
                    inline bool
                    operator>(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
                    { return __y < __x; }
                
                  /// Based on operator<
                  template<typename _Tp, typename _Alloc>
                    inline bool
                    operator<=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
                    { return !(__y < __x); }
                
                  /// Based on operator<
                  template<typename _Tp, typename _Alloc>
                    inline bool
                    operator>=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
                    { return !(__x < __y); }
                
                  /// See std::vector::swap().
                  template<typename _Tp, typename _Alloc>
                    inline void
                    swap(vector<_Tp, _Alloc>& __x, vector<_Tp, _Alloc>& __y)
                    { __x.swap(__y); }
                
                _GLIBCXX_END_NAMESPACE_CONTAINER
                } // namespace std
                
                #endif /* _STL_VECTOR_H */


Top 10 Lines:

     Line      Count

      901 3783529118
      113  658505498
     1125  654185552
     1350  654185552
      645  311574376
      770  305647461
      556   53599982
      538   27519982
      117    2879964
      650    2879964

Execution Summary:

       53   Executable lines in this file
       53   Lines executed
   100.00   Percent of the file executed

6459307395   Total number of line executions
121873724.43   Average executions per line


*** File /usr/include/c++/4.8.2/cmath:
                // -*- C++ -*- C forwarding header.
                
                // Copyright (C) 1997-2013 Free Software Foundation, Inc.
                //
                // This file is part of the GNU ISO C++ Library.  This library is free
                // software; you can redistribute it and/or modify it under the
                // terms of the GNU General Public License as published by the
                // Free Software Foundation; either version 3, or (at your option)
                // any later version.
                
                // This library is distributed in the hope that it will be useful,
                // but WITHOUT ANY WARRANTY; without even the implied warranty of
                // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
                // GNU General Public License for more details.
                
                // Under Section 7 of GPL version 3, you are granted additional
                // permissions described in the GCC Runtime Library Exception, version
                // 3.1, as published by the Free Software Foundation.
                
                // You should have received a copy of the GNU General Public License and
                // a copy of the GCC Runtime Library Exception along with this program;
                // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
                // <http://www.gnu.org/licenses/>.
                
                /** @file include/cmath
                 *  This is a Standard C++ Library file.  You should @c \#include this file
                 *  in your programs, rather than any of the @a *.h implementation files.
                 *
                 *  This is the C++ version of the Standard C Library header @c math.h,
                 *  and its contents are (mostly) the same as that header, but are all
                 *  contained in the namespace @c std (except for names which are defined
                 *  as macros in C).
                 */
                
                //
                // ISO C++ 14882: 26.5  C library
                //
                
                #pragma GCC system_header
                
                #include <bits/c++config.h>
                #include <bits/cpp_type_traits.h>
                #include <ext/type_traits.h>
                #include <math.h>
                
                #ifndef _GLIBCXX_CMATH
                #define _GLIBCXX_CMATH 1
                
                // Get rid of those macros defined in <math.h> in lieu of real functions.
                #undef abs
                #undef div
                #undef acos
                #undef asin
                #undef atan
                #undef atan2
                #undef ceil
                #undef cos
                #undef cosh
                #undef exp
                #undef fabs
                #undef floor
                #undef fmod
                #undef frexp
                #undef ldexp
                #undef log
                #undef log10
                #undef modf
                #undef pow
                #undef sin
                #undef sinh
                #undef sqrt
                #undef tan
                #undef tanh
                
                namespace std _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR double
                  abs(double __x)
                  { return __builtin_fabs(__x); }
                #endif
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  abs(float __x)
                  { return __builtin_fabsf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  abs(long double __x)
                  { return __builtin_fabsl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    abs(_Tp __x)
                    { return __builtin_fabs(__x); }
                
                  using ::acos;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  acos(float __x)
                  { return __builtin_acosf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  acos(long double __x)
                  { return __builtin_acosl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    acos(_Tp __x)
                    { return __builtin_acos(__x); }
                
                  using ::asin;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  asin(float __x)
                  { return __builtin_asinf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  asin(long double __x)
                  { return __builtin_asinl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    asin(_Tp __x)
                    { return __builtin_asin(__x); }
                
                  using ::atan;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  atan(float __x)
                  { return __builtin_atanf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  atan(long double __x)
                  { return __builtin_atanl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    atan(_Tp __x)
                    { return __builtin_atan(__x); }
                
                  using ::atan2;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  atan2(float __y, float __x)
       ##### ->   { return __builtin_atan2f(__y, __x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  atan2(long double __y, long double __x)
                  { return __builtin_atan2l(__y, __x); }
                #endif
                
                  template<typename _Tp, typename _Up>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    atan2(_Tp __y, _Up __x)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return atan2(__type(__y), __type(__x));
                    }
                
                  using ::ceil;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  ceil(float __x)
                  { return __builtin_ceilf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  ceil(long double __x)
                  { return __builtin_ceill(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    ceil(_Tp __x)
                    { return __builtin_ceil(__x); }
                
                  using ::cos;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  cos(float __x)
   147525962 ->   { return __builtin_cosf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  cos(long double __x)
                  { return __builtin_cosl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    cos(_Tp __x)
                    { return __builtin_cos(__x); }
                
                  using ::cosh;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  cosh(float __x)
                  { return __builtin_coshf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  cosh(long double __x)
                  { return __builtin_coshl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    cosh(_Tp __x)
                    { return __builtin_cosh(__x); }
                
                  using ::exp;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  exp(float __x)
   305647861 ->   { return __builtin_expf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  exp(long double __x)
                  { return __builtin_expl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    exp(_Tp __x)
                    { return __builtin_exp(__x); }
                
                  using ::fabs;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  fabs(float __x)
                  { return __builtin_fabsf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  fabs(long double __x)
                  { return __builtin_fabsl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    fabs(_Tp __x)
                    { return __builtin_fabs(__x); }
                
                  using ::floor;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  floor(float __x)
                  { return __builtin_floorf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  floor(long double __x)
                  { return __builtin_floorl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    floor(_Tp __x)
                    { return __builtin_floor(__x); }
                
                  using ::fmod;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  fmod(float __x, float __y)
                  { return __builtin_fmodf(__x, __y); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  fmod(long double __x, long double __y)
                  { return __builtin_fmodl(__x, __y); }
                #endif
                
                  template<typename _Tp, typename _Up>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    fmod(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return fmod(__type(__x), __type(__y));
                    }
                
                  using ::frexp;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline float
                  frexp(float __x, int* __exp)
                  { return __builtin_frexpf(__x, __exp); }
                
                  inline long double
                  frexp(long double __x, int* __exp)
                  { return __builtin_frexpl(__x, __exp); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    frexp(_Tp __x, int* __exp)
                    { return __builtin_frexp(__x, __exp); }
                
                  using ::ldexp;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  ldexp(float __x, int __exp)
                  { return __builtin_ldexpf(__x, __exp); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  ldexp(long double __x, int __exp)
                  { return __builtin_ldexpl(__x, __exp); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    ldexp(_Tp __x, int __exp)
                    { return __builtin_ldexp(__x, __exp); }
                
                  using ::log;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  log(float __x)
       ##### ->   { return __builtin_logf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  log(long double __x)
                  { return __builtin_logl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    log(_Tp __x)
                    { return __builtin_log(__x); }
                
                  using ::log10;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  log10(float __x)
         815 ->   { return __builtin_log10f(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  log10(long double __x)
                  { return __builtin_log10l(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                    double>::__type
                    log10(_Tp __x)
                    { return __builtin_log10(__x); }
                
                  using ::modf;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline float
                  modf(float __x, float* __iptr)
                  { return __builtin_modff(__x, __iptr); }
                
                  inline long double
                  modf(long double __x, long double* __iptr)
                  { return __builtin_modfl(__x, __iptr); }
                #endif
                
                  using ::pow;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  pow(float __x, float __y)
                  { return __builtin_powf(__x, __y); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  pow(long double __x, long double __y)
                  { return __builtin_powl(__x, __y); }
                
                #if __cplusplus < 201103L
                  // _GLIBCXX_RESOLVE_LIB_DEFECTS
                  // DR 550. What should the return type of pow(float,int) be?
                  inline double
                  pow(double __x, int __i)
                  { return __builtin_powi(__x, __i); }
                
                  inline float
                  pow(float __x, int __n)
                  { return __builtin_powif(__x, __n); }
                
                  inline long double
                  pow(long double __x, int __n)
                  { return __builtin_powil(__x, __n); }
                #endif
                #endif
                
                  template<typename _Tp, typename _Up>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
   654295189 ->     pow(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
   654295189 ->       return pow(__type(__x), __type(__y));
   654295189 ->     }
                
                  using ::sin;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  sin(float __x)
   147524424 ->   { return __builtin_sinf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  sin(long double __x)
                  { return __builtin_sinl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    sin(_Tp __x)
                    { return __builtin_sin(__x); }
                
                  using ::sinh;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  sinh(float __x)
                  { return __builtin_sinhf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  sinh(long double __x)
                  { return __builtin_sinhl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    sinh(_Tp __x)
                    { return __builtin_sinh(__x); }
                
                  using ::sqrt;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  sqrt(float __x)
  3156856902 ->   { return __builtin_sqrtf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  sqrt(long double __x)
                  { return __builtin_sqrtl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
       ##### ->     sqrt(_Tp __x)
       ##### ->     { return __builtin_sqrt(__x); }
                
                  using ::tan;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  tan(float __x)
                  { return __builtin_tanf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  tan(long double __x)
                  { return __builtin_tanl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    tan(_Tp __x)
                    { return __builtin_tan(__x); }
                
                  using ::tanh;
                
                #ifndef __CORRECT_ISO_CPP_MATH_H_PROTO
                  inline _GLIBCXX_CONSTEXPR float
                  tanh(float __x)
                  { return __builtin_tanhf(__x); }
                
                  inline _GLIBCXX_CONSTEXPR long double
                  tanh(long double __x)
                  { return __builtin_tanhl(__x); }
                #endif
                
                  template<typename _Tp>
                    inline _GLIBCXX_CONSTEXPR
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    double>::__type
                    tanh(_Tp __x)
                    { return __builtin_tanh(__x); }
                
                _GLIBCXX_END_NAMESPACE_VERSION
                } // namespace
                
                #if _GLIBCXX_USE_C99_MATH
                #if !_GLIBCXX_USE_C99_FP_MACROS_DYNAMIC
                
                // These are possible macros imported from C99-land.
                #undef fpclassify
                #undef isfinite
                #undef isinf
                #undef isnan
                #undef isnormal
                #undef signbit
                #undef isgreater
                #undef isgreaterequal
                #undef isless
                #undef islessequal
                #undef islessgreater
                #undef isunordered
                
                namespace std _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                #if __cplusplus >= 201103L
                  constexpr int
                  fpclassify(float __x)
                  { return __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL,
                				FP_SUBNORMAL, FP_ZERO, __x); }
                
                  constexpr int
                  fpclassify(double __x)
                  { return __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL,
                				FP_SUBNORMAL, FP_ZERO, __x); }
                
                  constexpr int
                  fpclassify(long double __x)
                  { return __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL,
                				FP_SUBNORMAL, FP_ZERO, __x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                              int>::__type
                    fpclassify(_Tp __x)
                    { return __x != 0 ? FP_NORMAL : FP_ZERO; }
                
                  constexpr bool
                  isfinite(float __x)
                  { return __builtin_isfinite(__x); }
                
                  constexpr bool
                  isfinite(double __x)
                  { return __builtin_isfinite(__x); }
                
                  constexpr bool
                  isfinite(long double __x)
                  { return __builtin_isfinite(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                              bool>::__type
                    isfinite(_Tp __x)
                    { return true; }
                
                  constexpr bool
                  isinf(float __x)
                  { return __builtin_isinf(__x); }
                
                  constexpr bool
                  isinf(double __x)
                  { return __builtin_isinf(__x); }
                
                  constexpr bool
                  isinf(long double __x)
                  { return __builtin_isinf(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                              bool>::__type
                    isinf(_Tp __x)
                    { return false; }
                
                  constexpr bool
                  isnan(float __x)
                  { return __builtin_isnan(__x); }
                
                  constexpr bool
                  isnan(double __x)
                  { return __builtin_isnan(__x); }
                
                  constexpr bool
                  isnan(long double __x)
                  { return __builtin_isnan(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                              bool>::__type
                    isnan(_Tp __x)
                    { return false; }
                
                  constexpr bool
                  isnormal(float __x)
                  { return __builtin_isnormal(__x); }
                
                  constexpr bool
                  isnormal(double __x)
                  { return __builtin_isnormal(__x); }
                
                  constexpr bool
                  isnormal(long double __x)
                  { return __builtin_isnormal(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                              bool>::__type
                    isnormal(_Tp __x)
                    { return __x != 0 ? true : false; }
                
                  constexpr bool
                  signbit(float __x)
                  { return __builtin_signbit(__x); }
                
                  constexpr bool
                  signbit(double __x)
                  { return __builtin_signbit(__x); }
                
                  constexpr bool
                  signbit(long double __x)
                  { return __builtin_signbit(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value,
                                                              bool>::__type
                    signbit(_Tp __x)
                    { return __x < 0 ? true : false; }
                
                  constexpr bool
                  isgreater(float __x, float __y)
                  { return __builtin_isgreater(__x, __y); }
                
                  constexpr bool
                  isgreater(double __x, double __y)
                  { return __builtin_isgreater(__x, __y); }
                
                  constexpr bool
                  isgreater(long double __x, long double __y)
                  { return __builtin_isgreater(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename
                    __gnu_cxx::__enable_if<(__is_arithmetic<_Tp>::__value
                			    && __is_arithmetic<_Up>::__value), bool>::__type
                    isgreater(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return __builtin_isgreater(__type(__x), __type(__y));
                    }
                
                  constexpr bool
                  isgreaterequal(float __x, float __y)
                  { return __builtin_isgreaterequal(__x, __y); }
                
                  constexpr bool
                  isgreaterequal(double __x, double __y)
                  { return __builtin_isgreaterequal(__x, __y); }
                
                  constexpr bool
                  isgreaterequal(long double __x, long double __y)
                  { return __builtin_isgreaterequal(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename
                    __gnu_cxx::__enable_if<(__is_arithmetic<_Tp>::__value
                			    && __is_arithmetic<_Up>::__value), bool>::__type
                    isgreaterequal(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return __builtin_isgreaterequal(__type(__x), __type(__y));
                    }
                
                  constexpr bool
                  isless(float __x, float __y)
                  { return __builtin_isless(__x, __y); }
                
                  constexpr bool
                  isless(double __x, double __y)
                  { return __builtin_isless(__x, __y); }
                
                  constexpr bool
                  isless(long double __x, long double __y)
                  { return __builtin_isless(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename
                    __gnu_cxx::__enable_if<(__is_arithmetic<_Tp>::__value
                			    && __is_arithmetic<_Up>::__value), bool>::__type
                    isless(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return __builtin_isless(__type(__x), __type(__y));
                    }
                
                  constexpr bool
                  islessequal(float __x, float __y)
                  { return __builtin_islessequal(__x, __y); }
                
                  constexpr bool
                  islessequal(double __x, double __y)
                  { return __builtin_islessequal(__x, __y); }
                
                  constexpr bool
                  islessequal(long double __x, long double __y)
                  { return __builtin_islessequal(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename
                    __gnu_cxx::__enable_if<(__is_arithmetic<_Tp>::__value
                			    && __is_arithmetic<_Up>::__value), bool>::__type
                    islessequal(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return __builtin_islessequal(__type(__x), __type(__y));
                    }
                
                  constexpr bool
                  islessgreater(float __x, float __y)
                  { return __builtin_islessgreater(__x, __y); }
                
                  constexpr bool
                  islessgreater(double __x, double __y)
                  { return __builtin_islessgreater(__x, __y); }
                
                  constexpr bool
                  islessgreater(long double __x, long double __y)
                  { return __builtin_islessgreater(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename
                    __gnu_cxx::__enable_if<(__is_arithmetic<_Tp>::__value
                			    && __is_arithmetic<_Up>::__value), bool>::__type
                    islessgreater(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return __builtin_islessgreater(__type(__x), __type(__y));
                    }
                
                  constexpr bool
                  isunordered(float __x, float __y)
                  { return __builtin_isunordered(__x, __y); }
                
                  constexpr bool
                  isunordered(double __x, double __y)
                  { return __builtin_isunordered(__x, __y); }
                
                  constexpr bool
                  isunordered(long double __x, long double __y)
                  { return __builtin_isunordered(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename
                    __gnu_cxx::__enable_if<(__is_arithmetic<_Tp>::__value
                			    && __is_arithmetic<_Up>::__value), bool>::__type
                    isunordered(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return __builtin_isunordered(__type(__x), __type(__y));
                    }
                
                #else
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    fpclassify(_Tp __f)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL,
                				  FP_SUBNORMAL, FP_ZERO, __type(__f));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    isfinite(_Tp __f)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_isfinite(__type(__f));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    isinf(_Tp __f)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_isinf(__type(__f));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    isnan(_Tp __f)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_isnan(__type(__f));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    isnormal(_Tp __f)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_isnormal(__type(__f));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    signbit(_Tp __f)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_signbit(__type(__f));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    isgreater(_Tp __f1, _Tp __f2)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_isgreater(__type(__f1), __type(__f2));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    isgreaterequal(_Tp __f1, _Tp __f2)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_isgreaterequal(__type(__f1), __type(__f2));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    isless(_Tp __f1, _Tp __f2)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_isless(__type(__f1), __type(__f2));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    islessequal(_Tp __f1, _Tp __f2)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_islessequal(__type(__f1), __type(__f2));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    islessgreater(_Tp __f1, _Tp __f2)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_islessgreater(__type(__f1), __type(__f2));
                    }
                
                  template<typename _Tp>
                    inline typename __gnu_cxx::__enable_if<__is_arithmetic<_Tp>::__value,
                					   int>::__type
                    isunordered(_Tp __f1, _Tp __f2)
                    {
                      typedef typename __gnu_cxx::__promote<_Tp>::__type __type;
                      return __builtin_isunordered(__type(__f1), __type(__f2));
                    }
                
                #endif
                
                _GLIBCXX_END_NAMESPACE_VERSION
                } // namespace
                
                #endif /* _GLIBCXX_USE_C99_FP_MACROS_DYNAMIC */
                #endif
                
                #if __cplusplus >= 201103L
                
                #ifdef _GLIBCXX_USE_C99_MATH_TR1
                
                #undef acosh
                #undef acoshf
                #undef acoshl
                #undef asinh
                #undef asinhf
                #undef asinhl
                #undef atanh
                #undef atanhf
                #undef atanhl
                #undef cbrt
                #undef cbrtf
                #undef cbrtl
                #undef copysign
                #undef copysignf
                #undef copysignl
                #undef erf
                #undef erff
                #undef erfl
                #undef erfc
                #undef erfcf
                #undef erfcl
                #undef exp2
                #undef exp2f
                #undef exp2l
                #undef expm1
                #undef expm1f
                #undef expm1l
                #undef fdim
                #undef fdimf
                #undef fdiml
                #undef fma
                #undef fmaf
                #undef fmal
                #undef fmax
                #undef fmaxf
                #undef fmaxl
                #undef fmin
                #undef fminf
                #undef fminl
                #undef hypot
                #undef hypotf
                #undef hypotl
                #undef ilogb
                #undef ilogbf
                #undef ilogbl
                #undef lgamma
                #undef lgammaf
                #undef lgammal
                #undef llrint
                #undef llrintf
                #undef llrintl
                #undef llround
                #undef llroundf
                #undef llroundl
                #undef log1p
                #undef log1pf
                #undef log1pl
                #undef log2
                #undef log2f
                #undef log2l
                #undef logb
                #undef logbf
                #undef logbl
                #undef lrint
                #undef lrintf
                #undef lrintl
                #undef lround
                #undef lroundf
                #undef lroundl
                #undef nan
                #undef nanf
                #undef nanl
                #undef nearbyint
                #undef nearbyintf
                #undef nearbyintl
                #undef nextafter
                #undef nextafterf
                #undef nextafterl
                #undef nexttoward
                #undef nexttowardf
                #undef nexttowardl
                #undef remainder
                #undef remainderf
                #undef remainderl
                #undef remquo
                #undef remquof
                #undef remquol
                #undef rint
                #undef rintf
                #undef rintl
                #undef round
                #undef roundf
                #undef roundl
                #undef scalbln
                #undef scalblnf
                #undef scalblnl
                #undef scalbn
                #undef scalbnf
                #undef scalbnl
                #undef tgamma
                #undef tgammaf
                #undef tgammal
                #undef trunc
                #undef truncf
                #undef truncl
                
                namespace std _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                  // types
                  using ::double_t;
                  using ::float_t;
                
                  // functions
                  using ::acosh;
                  using ::acoshf;
                  using ::acoshl;
                
                  using ::asinh;
                  using ::asinhf;
                  using ::asinhl;
                
                  using ::atanh;
                  using ::atanhf;
                  using ::atanhl;
                
                  using ::cbrt;
                  using ::cbrtf;
                  using ::cbrtl;
                
                  using ::copysign;
                  using ::copysignf;
                  using ::copysignl;
                
                  using ::erf;
                  using ::erff;
                  using ::erfl;
                
                  using ::erfc;
                  using ::erfcf;
                  using ::erfcl;
                
                  using ::exp2;
                  using ::exp2f;
                  using ::exp2l;
                
                  using ::expm1;
                  using ::expm1f;
                  using ::expm1l;
                
                  using ::fdim;
                  using ::fdimf;
                  using ::fdiml;
                
                  using ::fma;
                  using ::fmaf;
                  using ::fmal;
                
                  using ::fmax;
                  using ::fmaxf;
                  using ::fmaxl;
                
                  using ::fmin;
                  using ::fminf;
                  using ::fminl;
                
                  using ::hypot;
                  using ::hypotf;
                  using ::hypotl;
                
                  using ::ilogb;
                  using ::ilogbf;
                  using ::ilogbl;
                
                  using ::lgamma;
                  using ::lgammaf;
                  using ::lgammal;
                
                  using ::llrint;
                  using ::llrintf;
                  using ::llrintl;
                
                  using ::llround;
                  using ::llroundf;
                  using ::llroundl;
                
                  using ::log1p;
                  using ::log1pf;
                  using ::log1pl;
                
                  using ::log2;
                  using ::log2f;
                  using ::log2l;
                
                  using ::logb;
                  using ::logbf;
                  using ::logbl;
                
                  using ::lrint;
                  using ::lrintf;
                  using ::lrintl;
                
                  using ::lround;
                  using ::lroundf;
                  using ::lroundl;
                
                  using ::nan;
                  using ::nanf;
                  using ::nanl;
                
                  using ::nearbyint;
                  using ::nearbyintf;
                  using ::nearbyintl;
                
                  using ::nextafter;
                  using ::nextafterf;
                  using ::nextafterl;
                
                  using ::nexttoward;
                  using ::nexttowardf;
                  using ::nexttowardl;
                
                  using ::remainder;
                  using ::remainderf;
                  using ::remainderl;
                
                  using ::remquo;
                  using ::remquof;
                  using ::remquol;
                
                  using ::rint;
                  using ::rintf;
                  using ::rintl;
                
                  using ::round;
                  using ::roundf;
                  using ::roundl;
                
                  using ::scalbln;
                  using ::scalblnf;
                  using ::scalblnl;
                
                  using ::scalbn;
                  using ::scalbnf;
                  using ::scalbnl;
                
                  using ::tgamma;
                  using ::tgammaf;
                  using ::tgammal;
                
                  using ::trunc;
                  using ::truncf;
                  using ::truncl;
                
                  /// Additional overloads.
                  constexpr float
                  acosh(float __x)
                  { return __builtin_acoshf(__x); }
                
                  constexpr long double
                  acosh(long double __x)
                  { return __builtin_acoshl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    acosh(_Tp __x)
                    { return __builtin_acosh(__x); }
                
                  constexpr float
                  asinh(float __x)
                  { return __builtin_asinhf(__x); }
                
                  constexpr long double
                  asinh(long double __x)
                  { return __builtin_asinhl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    asinh(_Tp __x)
                    { return __builtin_asinh(__x); }
                
                  constexpr float
                  atanh(float __x)
                  { return __builtin_atanhf(__x); }
                
                  constexpr long double
                  atanh(long double __x)
                  { return __builtin_atanhl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    atanh(_Tp __x)
                    { return __builtin_atanh(__x); }
                
                  constexpr float
                  cbrt(float __x)
                  { return __builtin_cbrtf(__x); }
                
                  constexpr long double
                  cbrt(long double __x)
                  { return __builtin_cbrtl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    cbrt(_Tp __x)
                    { return __builtin_cbrt(__x); }
                
                  constexpr float
                  copysign(float __x, float __y)
                  { return __builtin_copysignf(__x, __y); }
                
                  constexpr long double
                  copysign(long double __x, long double __y)
                  { return __builtin_copysignl(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    copysign(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return copysign(__type(__x), __type(__y));
                    }
                
                  constexpr float
                  erf(float __x)
                  { return __builtin_erff(__x); }
                
                  constexpr long double
                  erf(long double __x)
                  { return __builtin_erfl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    erf(_Tp __x)
                    { return __builtin_erf(__x); }
                
                  constexpr float
                  erfc(float __x)
                  { return __builtin_erfcf(__x); }
                
                  constexpr long double
                  erfc(long double __x)
                  { return __builtin_erfcl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    erfc(_Tp __x)
                    { return __builtin_erfc(__x); }
                
                  constexpr float
                  exp2(float __x)
                  { return __builtin_exp2f(__x); }
                
                  constexpr long double
                  exp2(long double __x)
                  { return __builtin_exp2l(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    exp2(_Tp __x)
                    { return __builtin_exp2(__x); }
                
                  constexpr float
                  expm1(float __x)
                  { return __builtin_expm1f(__x); }
                
                  constexpr long double
                  expm1(long double __x)
                  { return __builtin_expm1l(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    expm1(_Tp __x)
                    { return __builtin_expm1(__x); }
                
                  constexpr float
                  fdim(float __x, float __y)
                  { return __builtin_fdimf(__x, __y); }
                
                  constexpr long double
                  fdim(long double __x, long double __y)
                  { return __builtin_fdiml(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    fdim(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return fdim(__type(__x), __type(__y));
                    }
                
                  constexpr float
                  fma(float __x, float __y, float __z)
                  { return __builtin_fmaf(__x, __y, __z); }
                
                  constexpr long double
                  fma(long double __x, long double __y, long double __z)
                  { return __builtin_fmal(__x, __y, __z); }
                
                  template<typename _Tp, typename _Up, typename _Vp>
                    constexpr typename __gnu_cxx::__promote_3<_Tp, _Up, _Vp>::__type
                    fma(_Tp __x, _Up __y, _Vp __z)
                    {
                      typedef typename __gnu_cxx::__promote_3<_Tp, _Up, _Vp>::__type __type;
                      return fma(__type(__x), __type(__y), __type(__z));
                    }
                
                  constexpr float
                  fmax(float __x, float __y)
                  { return __builtin_fmaxf(__x, __y); }
                
                  constexpr long double
                  fmax(long double __x, long double __y)
                  { return __builtin_fmaxl(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    fmax(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return fmax(__type(__x), __type(__y));
                    }
                
                  constexpr float
                  fmin(float __x, float __y)
                  { return __builtin_fminf(__x, __y); }
                
                  constexpr long double
                  fmin(long double __x, long double __y)
                  { return __builtin_fminl(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    fmin(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return fmin(__type(__x), __type(__y));
                    }
                
                  constexpr float
                  hypot(float __x, float __y)
                  { return __builtin_hypotf(__x, __y); }
                
                  constexpr long double
                  hypot(long double __x, long double __y)
                  { return __builtin_hypotl(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    hypot(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return hypot(__type(__x), __type(__y));
                    }
                
                  constexpr int
                  ilogb(float __x)
                  { return __builtin_ilogbf(__x); }
                
                  constexpr int
                  ilogb(long double __x)
                  { return __builtin_ilogbl(__x); }
                
                  template<typename _Tp>
                    constexpr
                    typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                    int>::__type
                    ilogb(_Tp __x)
                    { return __builtin_ilogb(__x); }
                
                  constexpr float
                  lgamma(float __x)
                  { return __builtin_lgammaf(__x); }
                
                  constexpr long double
                  lgamma(long double __x)
                  { return __builtin_lgammal(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    lgamma(_Tp __x)
                    { return __builtin_lgamma(__x); }
                
                  constexpr long long
                  llrint(float __x)
                  { return __builtin_llrintf(__x); }
                
                  constexpr long long
                  llrint(long double __x)
                  { return __builtin_llrintl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              long long>::__type
                    llrint(_Tp __x)
                    { return __builtin_llrint(__x); }
                
                  constexpr long long
                  llround(float __x)
                  { return __builtin_llroundf(__x); }
                
                  constexpr long long
                  llround(long double __x)
                  { return __builtin_llroundl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              long long>::__type
                    llround(_Tp __x)
                    { return __builtin_llround(__x); }
                
                  constexpr float
                  log1p(float __x)
                  { return __builtin_log1pf(__x); }
                
                  constexpr long double
                  log1p(long double __x)
                  { return __builtin_log1pl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    log1p(_Tp __x)
                    { return __builtin_log1p(__x); }
                
                  // DR 568.
                  constexpr float
                  log2(float __x)
                  { return __builtin_log2f(__x); }
                
                  constexpr long double
                  log2(long double __x)
                  { return __builtin_log2l(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    log2(_Tp __x)
                    { return __builtin_log2(__x); }
                
                  constexpr float
                  logb(float __x)
                  { return __builtin_logbf(__x); }
                
                  constexpr long double
                  logb(long double __x)
                  { return __builtin_logbl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    logb(_Tp __x)
                    { return __builtin_logb(__x); }
                
                  constexpr long
                  lrint(float __x)
                  { return __builtin_lrintf(__x); }
                
                  constexpr long
                  lrint(long double __x)
                  { return __builtin_lrintl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              long>::__type
                    lrint(_Tp __x)
                    { return __builtin_lrint(__x); }
                
                  constexpr long
                  lround(float __x)
                  { return __builtin_lroundf(__x); }
                
                  constexpr long
                  lround(long double __x)
                  { return __builtin_lroundl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              long>::__type
                    lround(_Tp __x)
                    { return __builtin_lround(__x); }
                
                  constexpr float
                  nearbyint(float __x)
                  { return __builtin_nearbyintf(__x); }
                
                  constexpr long double
                  nearbyint(long double __x)
                  { return __builtin_nearbyintl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    nearbyint(_Tp __x)
                    { return __builtin_nearbyint(__x); }
                
                  constexpr float
                  nextafter(float __x, float __y)
                  { return __builtin_nextafterf(__x, __y); }
                
                  constexpr long double
                  nextafter(long double __x, long double __y)
                  { return __builtin_nextafterl(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    nextafter(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return nextafter(__type(__x), __type(__y));
                    }
                
                  constexpr float
                  nexttoward(float __x, long double __y)
                  { return __builtin_nexttowardf(__x, __y); }
                
                  constexpr long double
                  nexttoward(long double __x, long double __y)
                  { return __builtin_nexttowardl(__x, __y); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    nexttoward(_Tp __x, long double __y)
                    { return __builtin_nexttoward(__x, __y); }
                
                  constexpr float
                  remainder(float __x, float __y)
                  { return __builtin_remainderf(__x, __y); }
                
                  constexpr long double
                  remainder(long double __x, long double __y)
                  { return __builtin_remainderl(__x, __y); }
                
                  template<typename _Tp, typename _Up>
                    constexpr typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    remainder(_Tp __x, _Up __y)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return remainder(__type(__x), __type(__y));
                    }
                
                  inline float
                  remquo(float __x, float __y, int* __pquo)
                  { return __builtin_remquof(__x, __y, __pquo); }
                
                  inline long double
                  remquo(long double __x, long double __y, int* __pquo)
                  { return __builtin_remquol(__x, __y, __pquo); }
                
                  template<typename _Tp, typename _Up>
                    inline typename __gnu_cxx::__promote_2<_Tp, _Up>::__type
                    remquo(_Tp __x, _Up __y, int* __pquo)
                    {
                      typedef typename __gnu_cxx::__promote_2<_Tp, _Up>::__type __type;
                      return remquo(__type(__x), __type(__y), __pquo);
                    }
                
                  constexpr float
                  rint(float __x)
                  { return __builtin_rintf(__x); }
                
                  constexpr long double
                  rint(long double __x)
                  { return __builtin_rintl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    rint(_Tp __x)
                    { return __builtin_rint(__x); }
                
                  constexpr float
                  round(float __x)
                  { return __builtin_roundf(__x); }
                
                  constexpr long double
                  round(long double __x)
                  { return __builtin_roundl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    round(_Tp __x)
                    { return __builtin_round(__x); }
                
                  constexpr float
                  scalbln(float __x, long __ex)
                  { return __builtin_scalblnf(__x, __ex); }
                
                  constexpr long double
                  scalbln(long double __x, long __ex)
                  { return __builtin_scalblnl(__x, __ex); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    scalbln(_Tp __x, long __ex)
                    { return __builtin_scalbln(__x, __ex); }
                 
                  constexpr float
                  scalbn(float __x, int __ex)
                  { return __builtin_scalbnf(__x, __ex); }
                
                  constexpr long double
                  scalbn(long double __x, int __ex)
                  { return __builtin_scalbnl(__x, __ex); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    scalbn(_Tp __x, int __ex)
                    { return __builtin_scalbn(__x, __ex); }
                
                  constexpr float
                  tgamma(float __x)
                  { return __builtin_tgammaf(__x); }
                
                  constexpr long double
                  tgamma(long double __x)
                  { return __builtin_tgammal(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    tgamma(_Tp __x)
                    { return __builtin_tgamma(__x); }
                 
                  constexpr float
                  trunc(float __x)
                  { return __builtin_truncf(__x); }
                
                  constexpr long double
                  trunc(long double __x)
                  { return __builtin_truncl(__x); }
                
                  template<typename _Tp>
                    constexpr typename __gnu_cxx::__enable_if<__is_integer<_Tp>::__value, 
                                                              double>::__type
                    trunc(_Tp __x)
                    { return __builtin_trunc(__x); }
                
                _GLIBCXX_END_NAMESPACE_VERSION
                } // namespace
                
                #endif // _GLIBCXX_USE_C99_MATH_TR1
                
                #endif // C++11
                
                #endif


Top 10 Lines:

     Line      Count

      483 3156856902
      434  654295189
      242  305647861
      204  147525962
      445  147524424
      377        815

Execution Summary:

       12   Executable lines in this file
       12   Lines executed
   100.00   Percent of the file executed

4411851153   Total number of line executions
367654262.75   Average executions per line


*** File /usr/include/c++/4.8.2/bits/stl_uninitialized.h:
                // Raw memory manipulators -*- C++ -*-
                
                // Copyright (C) 2001-2013 Free Software Foundation, Inc.
                //
                // This file is part of the GNU ISO C++ Library.  This library is free
                // software; you can redistribute it and/or modify it under the
                // terms of the GNU General Public License as published by the
                // Free Software Foundation; either version 3, or (at your option)
                // any later version.
                
                // This library is distributed in the hope that it will be useful,
                // but WITHOUT ANY WARRANTY; without even the implied warranty of
                // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
                // GNU General Public License for more details.
                
                // Under Section 7 of GPL version 3, you are granted additional
                // permissions described in the GCC Runtime Library Exception, version
                // 3.1, as published by the Free Software Foundation.
                
                // You should have received a copy of the GNU General Public License and
                // a copy of the GCC Runtime Library Exception along with this program;
                // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
                // <http://www.gnu.org/licenses/>.
                
                /*
                 *
                 * Copyright (c) 1994
                 * Hewlett-Packard Company
                 *
                 * Permission to use, copy, modify, distribute and sell this software
                 * and its documentation for any purpose is hereby granted without fee,
                 * provided that the above copyright notice appear in all copies and
                 * that both that copyright notice and this permission notice appear
                 * in supporting documentation.  Hewlett-Packard Company makes no
                 * representations about the suitability of this software for any
                 * purpose.  It is provided "as is" without express or implied warranty.
                 *
                 *
                 * Copyright (c) 1996,1997
                 * Silicon Graphics Computer Systems, Inc.
                 *
                 * Permission to use, copy, modify, distribute and sell this software
                 * and its documentation for any purpose is hereby granted without fee,
                 * provided that the above copyright notice appear in all copies and
                 * that both that copyright notice and this permission notice appear
                 * in supporting documentation.  Silicon Graphics makes no
                 * representations about the suitability of this software for any
                 * purpose.  It is provided "as is" without express or implied warranty.
                 */
                
                /** @file bits/stl_uninitialized.h
                 *  This is an internal header file, included by other library headers.
                 *  Do not attempt to use it directly. @headername{memory}
                 */
                
                #ifndef _STL_UNINITIALIZED_H
                #define _STL_UNINITIALIZED_H 1
                
                namespace std _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                  template<bool _TrivialValueTypes>
                    struct __uninitialized_copy
                    {
                      template<typename _InputIterator, typename _ForwardIterator>
                        static _ForwardIterator
                        __uninit_copy(_InputIterator __first, _InputIterator __last,
                		      _ForwardIterator __result)
                        {
                	  _ForwardIterator __cur = __result;
                	  __try
                	    {
                	      for (; __first != __last; ++__first, ++__cur)
                		std::_Construct(std::__addressof(*__cur), *__first);
                	      return __cur;
                	    }
                	  __catch(...)
                	    {
                	      std::_Destroy(__result, __cur);
                	      __throw_exception_again;
                	    }
                	}
                    };
                
                  template<>
                    struct __uninitialized_copy<true>
                    {
                      template<typename _InputIterator, typename _ForwardIterator>
                        static _ForwardIterator
     2879964 ->         __uninit_copy(_InputIterator __first, _InputIterator __last,
                		      _ForwardIterator __result)
     2879964 ->         { return std::copy(__first, __last, __result); }
                    };
                
                  /**
                   *  @brief Copies the range [first,last) into result.
                   *  @param  __first  An input iterator.
                   *  @param  __last   An input iterator.
                   *  @param  __result An output iterator.
                   *  @return   __result + (__first - __last)
                   *
                   *  Like copy(), but does not require an initialized output range.
                  */
                  template<typename _InputIterator, typename _ForwardIterator>
                    inline _ForwardIterator
     2879964 ->     uninitialized_copy(_InputIterator __first, _InputIterator __last,
                		       _ForwardIterator __result)
                    {
                      typedef typename iterator_traits<_InputIterator>::value_type
                	_ValueType1;
                      typedef typename iterator_traits<_ForwardIterator>::value_type
                	_ValueType2;
                
                      return std::__uninitialized_copy<(__is_trivial(_ValueType1)
                					&& __is_trivial(_ValueType2))>::
     2879964 -> 	__uninit_copy(__first, __last, __result);
     2879964 ->     }
                
                
                  template<bool _TrivialValueType>
                    struct __uninitialized_fill
                    {
                      template<typename _ForwardIterator, typename _Tp>
                        static void
                        __uninit_fill(_ForwardIterator __first, _ForwardIterator __last,
                		      const _Tp& __x)
                        {
                	  _ForwardIterator __cur = __first;
                	  __try
                	    {
                	      for (; __cur != __last; ++__cur)
                		std::_Construct(std::__addressof(*__cur), __x);
                	    }
                	  __catch(...)
                	    {
                	      std::_Destroy(__first, __cur);
                	      __throw_exception_again;
                	    }
                	}
                    };
                
                  template<>
                    struct __uninitialized_fill<true>
                    {
                      template<typename _ForwardIterator, typename _Tp>
                        static void
                        __uninit_fill(_ForwardIterator __first, _ForwardIterator __last,
                		      const _Tp& __x)
                        { std::fill(__first, __last, __x); }
                    };
                
                  /**
                   *  @brief Copies the value x into the range [first,last).
                   *  @param  __first  An input iterator.
                   *  @param  __last   An input iterator.
                   *  @param  __x      The source value.
                   *  @return   Nothing.
                   *
                   *  Like fill(), but does not require an initialized output range.
                  */
                  template<typename _ForwardIterator, typename _Tp>
                    inline void
                    uninitialized_fill(_ForwardIterator __first, _ForwardIterator __last,
                		       const _Tp& __x)
                    {
                      typedef typename iterator_traits<_ForwardIterator>::value_type
                	_ValueType;
                
                      std::__uninitialized_fill<__is_trivial(_ValueType)>::
                	__uninit_fill(__first, __last, __x);
                    }
                
                
                  template<bool _TrivialValueType>
                    struct __uninitialized_fill_n
                    {
                      template<typename _ForwardIterator, typename _Size, typename _Tp>
                        static void
                        __uninit_fill_n(_ForwardIterator __first, _Size __n,
                			const _Tp& __x)
                        {
                	  _ForwardIterator __cur = __first;
                	  __try
                	    {
                	      for (; __n > 0; --__n, ++__cur)
                		std::_Construct(std::__addressof(*__cur), __x);
                	    }
                	  __catch(...)
                	    {
                	      std::_Destroy(__first, __cur);
                	      __throw_exception_again;
                	    }
                	}
                    };
                
                  template<>
                    struct __uninitialized_fill_n<true>
                    {
                      template<typename _ForwardIterator, typename _Size, typename _Tp>
                        static void
                        __uninit_fill_n(_ForwardIterator __first, _Size __n,
                			const _Tp& __x)
                        { std::fill_n(__first, __n, __x); }
                    };
                
                  /**
                   *  @brief Copies the value x into the range [first,first+n).
                   *  @param  __first  An input iterator.
                   *  @param  __n      The number of copies to make.
                   *  @param  __x      The source value.
                   *  @return   Nothing.
                   *
                   *  Like fill_n(), but does not require an initialized output range.
                  */
                  template<typename _ForwardIterator, typename _Size, typename _Tp>
                    inline void
                    uninitialized_fill_n(_ForwardIterator __first, _Size __n, const _Tp& __x)
                    {
                      typedef typename iterator_traits<_ForwardIterator>::value_type
                	_ValueType;
                
                      std::__uninitialized_fill_n<__is_trivial(_ValueType)>::
                	__uninit_fill_n(__first, __n, __x);
                    }
                
                  // Extensions: versions of uninitialized_copy, uninitialized_fill,
                  //  and uninitialized_fill_n that take an allocator parameter.
                  //  We dispatch back to the standard versions when we're given the
                  //  default allocator.  For nondefault allocators we do not use 
                  //  any of the POD optimizations.
                
                  template<typename _InputIterator, typename _ForwardIterator,
                	   typename _Allocator>
                    _ForwardIterator
                    __uninitialized_copy_a(_InputIterator __first, _InputIterator __last,
                			   _ForwardIterator __result, _Allocator& __alloc)
                    {
                      _ForwardIterator __cur = __result;
                      __try
                	{
                	  typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
                	  for (; __first != __last; ++__first, ++__cur)
                	    __traits::construct(__alloc, std::__addressof(*__cur), *__first);
                	  return __cur;
                	}
                      __catch(...)
                	{
                	  std::_Destroy(__result, __cur, __alloc);
                	  __throw_exception_again;
                	}
                    }
                
                  template<typename _InputIterator, typename _ForwardIterator, typename _Tp>
                    inline _ForwardIterator
     2879964 ->     __uninitialized_copy_a(_InputIterator __first, _InputIterator __last,
                			   _ForwardIterator __result, allocator<_Tp>&)
     2879964 ->     { return std::uninitialized_copy(__first, __last, __result); }
                
                  template<typename _InputIterator, typename _ForwardIterator,
                	   typename _Allocator>
                    inline _ForwardIterator
                    __uninitialized_move_a(_InputIterator __first, _InputIterator __last,
                			   _ForwardIterator __result, _Allocator& __alloc)
                    {
                      return std::__uninitialized_copy_a(_GLIBCXX_MAKE_MOVE_ITERATOR(__first),
                					 _GLIBCXX_MAKE_MOVE_ITERATOR(__last),
                					 __result, __alloc);
                    }
                
                  template<typename _InputIterator, typename _ForwardIterator,
                	   typename _Allocator>
                    inline _ForwardIterator
     2879964 ->     __uninitialized_move_if_noexcept_a(_InputIterator __first,
                				       _InputIterator __last,
                				       _ForwardIterator __result,
                				       _Allocator& __alloc)
                    {
                      return std::__uninitialized_copy_a
                	(_GLIBCXX_MAKE_MOVE_IF_NOEXCEPT_ITERATOR(__first),
     2879964 -> 	 _GLIBCXX_MAKE_MOVE_IF_NOEXCEPT_ITERATOR(__last), __result, __alloc);
     2879964 ->     }
                
                  template<typename _ForwardIterator, typename _Tp, typename _Allocator>
                    void
                    __uninitialized_fill_a(_ForwardIterator __first, _ForwardIterator __last,
                			   const _Tp& __x, _Allocator& __alloc)
                    {
                      _ForwardIterator __cur = __first;
                      __try
                	{
                	  typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
                	  for (; __cur != __last; ++__cur)
                	    __traits::construct(__alloc, std::__addressof(*__cur), __x);
                	}
                      __catch(...)
                	{
                	  std::_Destroy(__first, __cur, __alloc);
                	  __throw_exception_again;
                	}
                    }
                
                  template<typename _ForwardIterator, typename _Tp, typename _Tp2>
                    inline void
                    __uninitialized_fill_a(_ForwardIterator __first, _ForwardIterator __last,
                			   const _Tp& __x, allocator<_Tp2>&)
                    { std::uninitialized_fill(__first, __last, __x); }
                
                  template<typename _ForwardIterator, typename _Size, typename _Tp,
                	   typename _Allocator>
                    void
                    __uninitialized_fill_n_a(_ForwardIterator __first, _Size __n, 
                			     const _Tp& __x, _Allocator& __alloc)
                    {
                      _ForwardIterator __cur = __first;
                      __try
                	{
                	  typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
                	  for (; __n > 0; --__n, ++__cur)
                	    __traits::construct(__alloc, std::__addressof(*__cur), __x);
                	}
                      __catch(...)
                	{
                	  std::_Destroy(__first, __cur, __alloc);
                	  __throw_exception_again;
                	}
                    }
                
                  template<typename _ForwardIterator, typename _Size, typename _Tp,
                	   typename _Tp2>
                    inline void
                    __uninitialized_fill_n_a(_ForwardIterator __first, _Size __n, 
                			     const _Tp& __x, allocator<_Tp2>&)
                    { std::uninitialized_fill_n(__first, __n, __x); }
                
                
                  // Extensions: __uninitialized_copy_move, __uninitialized_move_copy,
                  // __uninitialized_fill_move, __uninitialized_move_fill.
                  // All of these algorithms take a user-supplied allocator, which is used
                  // for construction and destruction.
                
                  // __uninitialized_copy_move
                  // Copies [first1, last1) into [result, result + (last1 - first1)), and
                  //  move [first2, last2) into
                  //  [result, result + (last1 - first1) + (last2 - first2)).
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _ForwardIterator, typename _Allocator>
                    inline _ForwardIterator
                    __uninitialized_copy_move(_InputIterator1 __first1,
                			      _InputIterator1 __last1,
                			      _InputIterator2 __first2,
                			      _InputIterator2 __last2,
                			      _ForwardIterator __result,
                			      _Allocator& __alloc)
                    {
                      _ForwardIterator __mid = std::__uninitialized_copy_a(__first1, __last1,
                							   __result,
                							   __alloc);
                      __try
                	{
                	  return std::__uninitialized_move_a(__first2, __last2, __mid, __alloc);
                	}
                      __catch(...)
                	{
                	  std::_Destroy(__result, __mid, __alloc);
                	  __throw_exception_again;
                	}
                    }
                
                  // __uninitialized_move_copy
                  // Moves [first1, last1) into [result, result + (last1 - first1)), and
                  //  copies [first2, last2) into
                  //  [result, result + (last1 - first1) + (last2 - first2)).
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _ForwardIterator, typename _Allocator>
                    inline _ForwardIterator
                    __uninitialized_move_copy(_InputIterator1 __first1,
                			      _InputIterator1 __last1,
                			      _InputIterator2 __first2,
                			      _InputIterator2 __last2,
                			      _ForwardIterator __result,
                			      _Allocator& __alloc)
                    {
                      _ForwardIterator __mid = std::__uninitialized_move_a(__first1, __last1,
                							   __result,
                							   __alloc);
                      __try
                	{
                	  return std::__uninitialized_copy_a(__first2, __last2, __mid, __alloc);
                	}
                      __catch(...)
                	{
                	  std::_Destroy(__result, __mid, __alloc);
                	  __throw_exception_again;
                	}
                    }
                  
                  // __uninitialized_fill_move
                  // Fills [result, mid) with x, and moves [first, last) into
                  //  [mid, mid + (last - first)).
                  template<typename _ForwardIterator, typename _Tp, typename _InputIterator,
                	   typename _Allocator>
                    inline _ForwardIterator
                    __uninitialized_fill_move(_ForwardIterator __result, _ForwardIterator __mid,
                			      const _Tp& __x, _InputIterator __first,
                			      _InputIterator __last, _Allocator& __alloc)
                    {
                      std::__uninitialized_fill_a(__result, __mid, __x, __alloc);
                      __try
                	{
                	  return std::__uninitialized_move_a(__first, __last, __mid, __alloc);
                	}
                      __catch(...)
                	{
                	  std::_Destroy(__result, __mid, __alloc);
                	  __throw_exception_again;
                	}
                    }
                
                  // __uninitialized_move_fill
                  // Moves [first1, last1) into [first2, first2 + (last1 - first1)), and
                  //  fills [first2 + (last1 - first1), last2) with x.
                  template<typename _InputIterator, typename _ForwardIterator, typename _Tp,
                	   typename _Allocator>
                    inline void
                    __uninitialized_move_fill(_InputIterator __first1, _InputIterator __last1,
                			      _ForwardIterator __first2,
                			      _ForwardIterator __last2, const _Tp& __x,
                			      _Allocator& __alloc)
                    {
                      _ForwardIterator __mid2 = std::__uninitialized_move_a(__first1, __last1,
                							    __first2,
                							    __alloc);
                      __try
                	{
                	  std::__uninitialized_fill_a(__mid2, __last2, __x, __alloc);
                	}
                      __catch(...)
                	{
                	  std::_Destroy(__first2, __mid2, __alloc);
                	  __throw_exception_again;
                	}
                    }
                
                #if __cplusplus >= 201103L
                  // Extensions: __uninitialized_default, __uninitialized_default_n,
                  // __uninitialized_default_a, __uninitialized_default_n_a.
                
                  template<bool _TrivialValueType>
                    struct __uninitialized_default_1
                    {
                      template<typename _ForwardIterator>
                        static void
                        __uninit_default(_ForwardIterator __first, _ForwardIterator __last)
                        {
                	  _ForwardIterator __cur = __first;
                	  __try
                	    {
                	      for (; __cur != __last; ++__cur)
                		std::_Construct(std::__addressof(*__cur));
                	    }
                	  __catch(...)
                	    {
                	      std::_Destroy(__first, __cur);
                	      __throw_exception_again;
                	    }
                	}
                    };
                
                  template<>
                    struct __uninitialized_default_1<true>
                    {
                      template<typename _ForwardIterator>
                        static void
                        __uninit_default(_ForwardIterator __first, _ForwardIterator __last)
                        {
                	  typedef typename iterator_traits<_ForwardIterator>::value_type
                	    _ValueType;
                
                	  std::fill(__first, __last, _ValueType());
                	}
                    };
                
                  template<bool _TrivialValueType>
                    struct __uninitialized_default_n_1
                    {
                      template<typename _ForwardIterator, typename _Size>
                        static void
                        __uninit_default_n(_ForwardIterator __first, _Size __n)
                        {
                	  _ForwardIterator __cur = __first;
                	  __try
                	    {
                	      for (; __n > 0; --__n, ++__cur)
                		std::_Construct(std::__addressof(*__cur));
                	    }
                	  __catch(...)
                	    {
                	      std::_Destroy(__first, __cur);
                	      __throw_exception_again;
                	    }
                	}
                    };
                
                  template<>
                    struct __uninitialized_default_n_1<true>
                    {
                      template<typename _ForwardIterator, typename _Size>
                        static void
                        __uninit_default_n(_ForwardIterator __first, _Size __n)
                        {
                	  typedef typename iterator_traits<_ForwardIterator>::value_type
                	    _ValueType;
                
                	  std::fill_n(__first, __n, _ValueType());
                	}
                    };
                
                  // __uninitialized_default
                  // Fills [first, last) with std::distance(first, last) default
                  // constructed value_types(s).
                  template<typename _ForwardIterator>
                    inline void
                    __uninitialized_default(_ForwardIterator __first,
                			    _ForwardIterator __last)
                    {
                      typedef typename iterator_traits<_ForwardIterator>::value_type
                	_ValueType;
                
                      std::__uninitialized_default_1<__is_trivial(_ValueType)>::
                	__uninit_default(__first, __last);
                    }
                
                  // __uninitialized_default_n
                  // Fills [first, first + n) with n default constructed value_type(s).
                  template<typename _ForwardIterator, typename _Size>
                    inline void
                    __uninitialized_default_n(_ForwardIterator __first, _Size __n)
                    {
                      typedef typename iterator_traits<_ForwardIterator>::value_type
                	_ValueType;
                
                      std::__uninitialized_default_n_1<__is_trivial(_ValueType)>::
                	__uninit_default_n(__first, __n);
                    }
                
                
                  // __uninitialized_default_a
                  // Fills [first, last) with std::distance(first, last) default
                  // constructed value_types(s), constructed with the allocator alloc.
                  template<typename _ForwardIterator, typename _Allocator>
                    void
                    __uninitialized_default_a(_ForwardIterator __first,
                			      _ForwardIterator __last,
                			      _Allocator& __alloc)
                    {
                      _ForwardIterator __cur = __first;
                      __try
                	{
                	  typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
                	  for (; __cur != __last; ++__cur)
                	    __traits::construct(__alloc, std::__addressof(*__cur));
                	}
                      __catch(...)
                	{
                	  std::_Destroy(__first, __cur, __alloc);
                	  __throw_exception_again;
                	}
                    }
                
                  template<typename _ForwardIterator, typename _Tp>
                    inline void
                    __uninitialized_default_a(_ForwardIterator __first,
                			      _ForwardIterator __last,
                			      allocator<_Tp>&)
                    { std::__uninitialized_default(__first, __last); }
                
                
                  // __uninitialized_default_n_a
                  // Fills [first, first + n) with n default constructed value_types(s),
                  // constructed with the allocator alloc.
                  template<typename _ForwardIterator, typename _Size, typename _Allocator>
                    void
                    __uninitialized_default_n_a(_ForwardIterator __first, _Size __n, 
                				_Allocator& __alloc)
                    {
                      _ForwardIterator __cur = __first;
                      __try
                	{
                	  typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
                	  for (; __n > 0; --__n, ++__cur)
                	    __traits::construct(__alloc, std::__addressof(*__cur));
                	}
                      __catch(...)
                	{
                	  std::_Destroy(__first, __cur, __alloc);
                	  __throw_exception_again;
                	}
                    }
                
                  template<typename _ForwardIterator, typename _Size, typename _Tp>
                    inline void
                    __uninitialized_default_n_a(_ForwardIterator __first, _Size __n, 
                				allocator<_Tp>&)
                    { std::__uninitialized_default_n(__first, __n); }
                
                
                  template<typename _InputIterator, typename _Size,
                	   typename _ForwardIterator>
                    _ForwardIterator
                    __uninitialized_copy_n(_InputIterator __first, _Size __n,
                			   _ForwardIterator __result, input_iterator_tag)
                    {
                      _ForwardIterator __cur = __result;
                      __try
                	{
                	  for (; __n > 0; --__n, ++__first, ++__cur)
                	    std::_Construct(std::__addressof(*__cur), *__first);
                	  return __cur;
                	}
                      __catch(...)
                	{
                	  std::_Destroy(__result, __cur);
                	  __throw_exception_again;
                	}
                    }
                
                  template<typename _RandomAccessIterator, typename _Size,
                	   typename _ForwardIterator>
                    inline _ForwardIterator
                    __uninitialized_copy_n(_RandomAccessIterator __first, _Size __n,
                			   _ForwardIterator __result,
                			   random_access_iterator_tag)
                    { return std::uninitialized_copy(__first, __first + __n, __result); }
                
                  /**
                   *  @brief Copies the range [first,first+n) into result.
                   *  @param  __first  An input iterator.
                   *  @param  __n      The number of elements to copy.
                   *  @param  __result An output iterator.
                   *  @return  __result + __n
                   *
                   *  Like copy_n(), but does not require an initialized output range.
                  */
                  template<typename _InputIterator, typename _Size, typename _ForwardIterator>
                    inline _ForwardIterator
                    uninitialized_copy_n(_InputIterator __first, _Size __n,
                			 _ForwardIterator __result)
                    { return std::__uninitialized_copy_n(__first, __n, __result,
                					 std::__iterator_category(__first)); }
                #endif
                
                _GLIBCXX_END_NAMESPACE_VERSION
                } // namespace
                
                #endif /* _STL_UNINITIALIZED_H */


Top 10 Lines:

     Line      Count

       91    2879964
      107    2879964
      256    2879964
      274    2879964

Execution Summary:

       10   Executable lines in this file
       10   Lines executed
   100.00   Percent of the file executed

 11519856   Total number of line executions
1151985.60   Average executions per line


*** File /usr/include/c++/4.8.2/ext/new_allocator.h:
                // Allocator that wraps operator new -*- C++ -*-
                
                // Copyright (C) 2001-2013 Free Software Foundation, Inc.
                //
                // This file is part of the GNU ISO C++ Library.  This library is free
                // software; you can redistribute it and/or modify it under the
                // terms of the GNU General Public License as published by the
                // Free Software Foundation; either version 3, or (at your option)
                // any later version.
                
                // This library is distributed in the hope that it will be useful,
                // but WITHOUT ANY WARRANTY; without even the implied warranty of
                // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
                // GNU General Public License for more details.
                
                // Under Section 7 of GPL version 3, you are granted additional
                // permissions described in the GCC Runtime Library Exception, version
                // 3.1, as published by the Free Software Foundation.
                
                // You should have received a copy of the GNU General Public License and
                // a copy of the GCC Runtime Library Exception along with this program;
                // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
                // <http://www.gnu.org/licenses/>.
                
                /** @file ext/new_allocator.h
                 *  This file is a GNU extension to the Standard C++ Library.
                 */
                
                #ifndef _NEW_ALLOCATOR_H
                #define _NEW_ALLOCATOR_H 1
                
                #include <bits/c++config.h>
                #include <new>
                #include <bits/functexcept.h>
                #include <bits/move.h>
                #if __cplusplus >= 201103L
                #include <type_traits>
                #endif
                
                namespace __gnu_cxx _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                  using std::size_t;
                  using std::ptrdiff_t;
                
                  /**
                   *  @brief  An allocator that uses global new, as per [20.4].
                   *  @ingroup allocators
                   *
                   *  This is precisely the allocator defined in the C++ Standard. 
                   *    - all allocation calls operator new
                   *    - all deallocation calls operator delete
                   *
                   *  @tparam  _Tp  Type of allocated object.
                   */
                  template<typename _Tp>
                    class new_allocator
                    {
                    public:
                      typedef size_t     size_type;
                      typedef ptrdiff_t  difference_type;
                      typedef _Tp*       pointer;
                      typedef const _Tp* const_pointer;
                      typedef _Tp&       reference;
                      typedef const _Tp& const_reference;
                      typedef _Tp        value_type;
                
                      template<typename _Tp1>
                        struct rebind
                        { typedef new_allocator<_Tp1> other; };
                
                #if __cplusplus >= 201103L
                      // _GLIBCXX_RESOLVE_LIB_DEFECTS
                      // 2103. propagate_on_container_move_assignment
                      typedef std::true_type propagate_on_container_move_assignment;
                #endif
                
      160000 ->       new_allocator() _GLIBCXX_USE_NOEXCEPT { }
                
                      new_allocator(const new_allocator&) _GLIBCXX_USE_NOEXCEPT { }
                
                      template<typename _Tp1>
                        new_allocator(const new_allocator<_Tp1>&) _GLIBCXX_USE_NOEXCEPT { }
                
       ##### ->       ~new_allocator() _GLIBCXX_USE_NOEXCEPT { }
                
                      pointer
                      address(reference __x) const _GLIBCXX_NOEXCEPT
                      { return std::__addressof(__x); }
                
                      const_pointer
                      address(const_reference __x) const _GLIBCXX_NOEXCEPT
                      { return std::__addressof(__x); }
                
                      // NB: __n is permitted to be 0.  The C++ standard says nothing
                      // about what the return value is when __n == 0.
                      pointer
     1439982 ->       allocate(size_type __n, const void* = 0)
                      { 
     1439982 -> 	if (__n > this->max_size())
     1439982 -> 	  std::__throw_bad_alloc();
                
     1439982 -> 	return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
     1439982 ->       }
                
                      // __p is not permitted to be a null pointer.
                      void
     1279982 ->       deallocate(pointer __p, size_type)
     1279982 ->       { ::operator delete(__p); }
                
                      size_type
     4319946 ->       max_size() const _GLIBCXX_USE_NOEXCEPT
     4319946 ->       { return size_t(-1) / sizeof(_Tp); }
                
                #if __cplusplus >= 201103L
                      template<typename _Up, typename... _Args>
                        void
                        construct(_Up* __p, _Args&&... __args)
                	{ ::new((void *)__p) _Up(std::forward<_Args>(__args)...); }
                
                      template<typename _Up>
                        void 
                        destroy(_Up* __p) { __p->~_Up(); }
                #else
                      // _GLIBCXX_RESOLVE_LIB_DEFECTS
                      // 402. wrong new expression in [some_] allocator::construct
                      void 
  3783529118 ->       construct(pointer __p, const _Tp& __val) 
  3783529118 ->       { ::new((void *)__p) _Tp(__val); }
                
                      void 
       ##### ->       destroy(pointer __p) { __p->~_Tp(); }
                #endif
                    };
                
                  template<typename _Tp>
                    inline bool
                    operator==(const new_allocator<_Tp>&, const new_allocator<_Tp>&)
                    { return true; }
                  
                  template<typename _Tp>
                    inline bool
                    operator!=(const new_allocator<_Tp>&, const new_allocator<_Tp>&)
                    { return false; }
                
                _GLIBCXX_END_NAMESPACE_VERSION
                } // namespace
                
                #endif


Top 10 Lines:

     Line      Count

      129 3783529118
      113    4319946
       99    1439982
      109    1279982
       79     160000

Execution Summary:

       14   Executable lines in this file
       14   Lines executed
   100.00   Percent of the file executed

3790729028   Total number of line executions
270766359.14   Average executions per line


*** File /usr/include/c++/4.8.2/bits/stl_algobase.h:
                // Core algorithmic facilities -*- C++ -*-
                
                // Copyright (C) 2001-2013 Free Software Foundation, Inc.
                //
                // This file is part of the GNU ISO C++ Library.  This library is free
                // software; you can redistribute it and/or modify it under the
                // terms of the GNU General Public License as published by the
                // Free Software Foundation; either version 3, or (at your option)
                // any later version.
                
                // This library is distributed in the hope that it will be useful,
                // but WITHOUT ANY WARRANTY; without even the implied warranty of
                // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
                // GNU General Public License for more details.
                
                // Under Section 7 of GPL version 3, you are granted additional
                // permissions described in the GCC Runtime Library Exception, version
                // 3.1, as published by the Free Software Foundation.
                
                // You should have received a copy of the GNU General Public License and
                // a copy of the GCC Runtime Library Exception along with this program;
                // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
                // <http://www.gnu.org/licenses/>.
                
                /*
                 *
                 * Copyright (c) 1994
                 * Hewlett-Packard Company
                 *
                 * Permission to use, copy, modify, distribute and sell this software
                 * and its documentation for any purpose is hereby granted without fee,
                 * provided that the above copyright notice appear in all copies and
                 * that both that copyright notice and this permission notice appear
                 * in supporting documentation.  Hewlett-Packard Company makes no
                 * representations about the suitability of this software for any
                 * purpose.  It is provided "as is" without express or implied warranty.
                 *
                 *
                 * Copyright (c) 1996-1998
                 * Silicon Graphics Computer Systems, Inc.
                 *
                 * Permission to use, copy, modify, distribute and sell this software
                 * and its documentation for any purpose is hereby granted without fee,
                 * provided that the above copyright notice appear in all copies and
                 * that both that copyright notice and this permission notice appear
                 * in supporting documentation.  Silicon Graphics makes no
                 * representations about the suitability of this software for any
                 * purpose.  It is provided "as is" without express or implied warranty.
                 */
                
                /** @file bits/stl_algobase.h
                 *  This is an internal header file, included by other library headers.
                 *  Do not attempt to use it directly. @headername{algorithm}
                 */
                
                #ifndef _STL_ALGOBASE_H
                #define _STL_ALGOBASE_H 1
                
                #include <bits/c++config.h>
                #include <bits/functexcept.h>
                #include <bits/cpp_type_traits.h>
                #include <ext/type_traits.h>
                #include <ext/numeric_traits.h>
                #include <bits/stl_pair.h>
                #include <bits/stl_iterator_base_types.h>
                #include <bits/stl_iterator_base_funcs.h>
                #include <bits/stl_iterator.h>
                #include <bits/concept_check.h>
                #include <debug/debug.h>
                #include <bits/move.h> // For std::swap and _GLIBCXX_MOVE
                
                namespace std _GLIBCXX_VISIBILITY(default)
                {
                _GLIBCXX_BEGIN_NAMESPACE_VERSION
                
                #if __cplusplus < 201103L
                  // See http://gcc.gnu.org/ml/libstdc++/2004-08/msg00167.html: in a
                  // nutshell, we are partially implementing the resolution of DR 187,
                  // when it's safe, i.e., the value_types are equal.
                  template<bool _BoolType>
                    struct __iter_swap
                    {
                      template<typename _ForwardIterator1, typename _ForwardIterator2>
                        static void
                        iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
                        {
                          typedef typename iterator_traits<_ForwardIterator1>::value_type
                            _ValueType1;
                          _ValueType1 __tmp = _GLIBCXX_MOVE(*__a);
                          *__a = _GLIBCXX_MOVE(*__b);
                          *__b = _GLIBCXX_MOVE(__tmp);
                	}
                    };
                
                  template<>
                    struct __iter_swap<true>
                    {
                      template<typename _ForwardIterator1, typename _ForwardIterator2>
                        static void 
                        iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
                        {
                          swap(*__a, *__b);
                        }
                    };
                #endif
                
                  /**
                   *  @brief Swaps the contents of two iterators.
                   *  @ingroup mutating_algorithms
                   *  @param  __a  An iterator.
                   *  @param  __b  Another iterator.
                   *  @return   Nothing.
                   *
                   *  This function swaps the values pointed to by two iterators, not the
                   *  iterators themselves.
                  */
                  template<typename _ForwardIterator1, typename _ForwardIterator2>
                    inline void
                    iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<
                				  _ForwardIterator1>)
                      __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<
                				  _ForwardIterator2>)
                
                #if __cplusplus < 201103L
                      typedef typename iterator_traits<_ForwardIterator1>::value_type
                	_ValueType1;
                      typedef typename iterator_traits<_ForwardIterator2>::value_type
                	_ValueType2;
                
                      __glibcxx_function_requires(_ConvertibleConcept<_ValueType1,
                				  _ValueType2>)
                      __glibcxx_function_requires(_ConvertibleConcept<_ValueType2,
                				  _ValueType1>)
                
                      typedef typename iterator_traits<_ForwardIterator1>::reference
                	_ReferenceType1;
                      typedef typename iterator_traits<_ForwardIterator2>::reference
                	_ReferenceType2;
                      std::__iter_swap<__are_same<_ValueType1, _ValueType2>::__value
                	&& __are_same<_ValueType1&, _ReferenceType1>::__value
                	&& __are_same<_ValueType2&, _ReferenceType2>::__value>::
                	iter_swap(__a, __b);
                #else
                      swap(*__a, *__b);
                #endif
                    }
                
                  /**
                   *  @brief Swap the elements of two sequences.
                   *  @ingroup mutating_algorithms
                   *  @param  __first1  A forward iterator.
                   *  @param  __last1   A forward iterator.
                   *  @param  __first2  A forward iterator.
                   *  @return   An iterator equal to @p first2+(last1-first1).
                   *
                   *  Swaps each element in the range @p [first1,last1) with the
                   *  corresponding element in the range @p [first2,(last1-first1)).
                   *  The ranges must not overlap.
                  */
                  template<typename _ForwardIterator1, typename _ForwardIterator2>
                    _ForwardIterator2
                    swap_ranges(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                		_ForwardIterator2 __first2)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<
                				  _ForwardIterator1>)
                      __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<
                				  _ForwardIterator2>)
                      __glibcxx_requires_valid_range(__first1, __last1);
                
                      for (; __first1 != __last1; ++__first1, ++__first2)
                	std::iter_swap(__first1, __first2);
                      return __first2;
                    }
                
                  /**
                   *  @brief This does what you think it does.
                   *  @ingroup sorting_algorithms
                   *  @param  __a  A thing of arbitrary type.
                   *  @param  __b  Another thing of arbitrary type.
                   *  @return   The lesser of the parameters.
                   *
                   *  This is the simple classic generic implementation.  It will work on
                   *  temporary expressions, since they are only evaluated once, unlike a
                   *  preprocessor macro.
                  */
                  template<typename _Tp>
                    inline const _Tp&
                    min(const _Tp& __a, const _Tp& __b)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_LessThanComparableConcept<_Tp>)
                      //return __b < __a ? __b : __a;
                      if (__b < __a)
                	return __b;
                      return __a;
                    }
                
                  /**
                   *  @brief This does what you think it does.
                   *  @ingroup sorting_algorithms
                   *  @param  __a  A thing of arbitrary type.
                   *  @param  __b  Another thing of arbitrary type.
                   *  @return   The greater of the parameters.
                   *
                   *  This is the simple classic generic implementation.  It will work on
                   *  temporary expressions, since they are only evaluated once, unlike a
                   *  preprocessor macro.
                  */
                  template<typename _Tp>
                    inline const _Tp&
     1439982 ->     max(const _Tp& __a, const _Tp& __b)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_LessThanComparableConcept<_Tp>)
                      //return  __a < __b ? __b : __a;
     1439982 ->       if (__a < __b)
     1439982 -> 	return __b;
     1439982 ->       return __a;
     1439982 ->     }
                
                  /**
                   *  @brief This does what you think it does.
                   *  @ingroup sorting_algorithms
                   *  @param  __a  A thing of arbitrary type.
                   *  @param  __b  Another thing of arbitrary type.
                   *  @param  __comp  A @link comparison_functors comparison functor@endlink.
                   *  @return   The lesser of the parameters.
                   *
                   *  This will work on temporary expressions, since they are only evaluated
                   *  once, unlike a preprocessor macro.
                  */
                  template<typename _Tp, typename _Compare>
                    inline const _Tp&
                    min(const _Tp& __a, const _Tp& __b, _Compare __comp)
                    {
                      //return __comp(__b, __a) ? __b : __a;
                      if (__comp(__b, __a))
                	return __b;
                      return __a;
                    }
                
                  /**
                   *  @brief This does what you think it does.
                   *  @ingroup sorting_algorithms
                   *  @param  __a  A thing of arbitrary type.
                   *  @param  __b  Another thing of arbitrary type.
                   *  @param  __comp  A @link comparison_functors comparison functor@endlink.
                   *  @return   The greater of the parameters.
                   *
                   *  This will work on temporary expressions, since they are only evaluated
                   *  once, unlike a preprocessor macro.
                  */
                  template<typename _Tp, typename _Compare>
                    inline const _Tp&
                    max(const _Tp& __a, const _Tp& __b, _Compare __comp)
                    {
                      //return __comp(__a, __b) ? __b : __a;
                      if (__comp(__a, __b))
                	return __b;
                      return __a;
                    }
                
                  // If _Iterator is a __normal_iterator return its base (a plain pointer,
                  // normally) otherwise return it untouched.  See copy, fill, ... 
                  template<typename _Iterator>
                    struct _Niter_base
                    : _Iter_base<_Iterator, __is_normal_iterator<_Iterator>::__value>
                    { };
                
                  template<typename _Iterator>
                    inline typename _Niter_base<_Iterator>::iterator_type
     8639892 ->     __niter_base(_Iterator __it)
     8639892 ->     { return std::_Niter_base<_Iterator>::_S_base(__it); }
                
                  // Likewise, for move_iterator.
                  template<typename _Iterator>
                    struct _Miter_base
                    : _Iter_base<_Iterator, __is_move_iterator<_Iterator>::__value>
                    { };
                
                  template<typename _Iterator>
                    inline typename _Miter_base<_Iterator>::iterator_type
     5759928 ->     __miter_base(_Iterator __it)
     5759928 ->     { return std::_Miter_base<_Iterator>::_S_base(__it); }
                
                  // All of these auxiliary structs serve two purposes.  (1) Replace
                  // calls to copy with memmove whenever possible.  (Memmove, not memcpy,
                  // because the input and output ranges are permitted to overlap.)
                  // (2) If we're using random access iterators, then write the loop as
                  // a for loop with an explicit count.
                
                  template<bool, bool, typename>
                    struct __copy_move
                    {
                      template<typename _II, typename _OI>
                        static _OI
                        __copy_m(_II __first, _II __last, _OI __result)
                        {
                	  for (; __first != __last; ++__result, ++__first)
                	    *__result = *__first;
                	  return __result;
                	}
                    };
                
                #if __cplusplus >= 201103L
                  template<typename _Category>
                    struct __copy_move<true, false, _Category>
                    {
                      template<typename _II, typename _OI>
                        static _OI
                        __copy_m(_II __first, _II __last, _OI __result)
                        {
                	  for (; __first != __last; ++__result, ++__first)
                	    *__result = std::move(*__first);
                	  return __result;
                	}
                    };
                #endif
                
                  template<>
                    struct __copy_move<false, false, random_access_iterator_tag>
                    {
                      template<typename _II, typename _OI>
                        static _OI
                        __copy_m(_II __first, _II __last, _OI __result)
                        { 
                	  typedef typename iterator_traits<_II>::difference_type _Distance;
                	  for(_Distance __n = __last - __first; __n > 0; --__n)
                	    {
                	      *__result = *__first;
                	      ++__first;
                	      ++__result;
                	    }
                	  return __result;
                	}
                    };
                
                #if __cplusplus >= 201103L
                  template<>
                    struct __copy_move<true, false, random_access_iterator_tag>
                    {
                      template<typename _II, typename _OI>
                        static _OI
                        __copy_m(_II __first, _II __last, _OI __result)
                        { 
                	  typedef typename iterator_traits<_II>::difference_type _Distance;
                	  for(_Distance __n = __last - __first; __n > 0; --__n)
                	    {
                	      *__result = std::move(*__first);
                	      ++__first;
                	      ++__result;
                	    }
                	  return __result;
                	}
                    };
                #endif
                
                  template<bool _IsMove>
                    struct __copy_move<_IsMove, true, random_access_iterator_tag>
                    {
                      template<typename _Tp>
                        static _Tp*
     2879964 ->         __copy_m(const _Tp* __first, const _Tp* __last, _Tp* __result)
                        {
     2879964 -> 	  const ptrdiff_t _Num = __last - __first;
     2879964 -> 	  if (_Num)
     2879964 -> 	    __builtin_memmove(__result, __first, sizeof(_Tp) * _Num);
     2879964 -> 	  return __result + _Num;
     2879964 -> 	}
                    };
                
                  template<bool _IsMove, typename _II, typename _OI>
                    inline _OI
     2879964 ->     __copy_move_a(_II __first, _II __last, _OI __result)
                    {
                      typedef typename iterator_traits<_II>::value_type _ValueTypeI;
                      typedef typename iterator_traits<_OI>::value_type _ValueTypeO;
                      typedef typename iterator_traits<_II>::iterator_category _Category;
                      const bool __simple = (__is_trivial(_ValueTypeI)
                	                     && __is_pointer<_II>::__value
                	                     && __is_pointer<_OI>::__value
     2879964 -> 			     && __are_same<_ValueTypeI, _ValueTypeO>::__value);
                
                      return std::__copy_move<_IsMove, __simple,
     2879964 -> 	                      _Category>::__copy_m(__first, __last, __result);
     2879964 ->     }
                
                  // Helpers for streambuf iterators (either istream or ostream).
                  // NB: avoid including <iosfwd>, relatively large.
                  template<typename _CharT>
                    struct char_traits;
                
                  template<typename _CharT, typename _Traits>
                    class istreambuf_iterator;
                
                  template<typename _CharT, typename _Traits>
                    class ostreambuf_iterator;
                
                  template<bool _IsMove, typename _CharT>
                    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value, 
                	     ostreambuf_iterator<_CharT, char_traits<_CharT> > >::__type
                    __copy_move_a2(_CharT*, _CharT*,
                		   ostreambuf_iterator<_CharT, char_traits<_CharT> >);
                
                  template<bool _IsMove, typename _CharT>
                    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value, 
                	     ostreambuf_iterator<_CharT, char_traits<_CharT> > >::__type
                    __copy_move_a2(const _CharT*, const _CharT*,
                		   ostreambuf_iterator<_CharT, char_traits<_CharT> >);
                
                  template<bool _IsMove, typename _CharT>
                    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
                				    _CharT*>::__type
                    __copy_move_a2(istreambuf_iterator<_CharT, char_traits<_CharT> >,
                		   istreambuf_iterator<_CharT, char_traits<_CharT> >, _CharT*);
                
                  template<bool _IsMove, typename _II, typename _OI>
                    inline _OI
     2879964 ->     __copy_move_a2(_II __first, _II __last, _OI __result)
                    {
                      return _OI(std::__copy_move_a<_IsMove>(std::__niter_base(__first),
                					     std::__niter_base(__last),
     2879964 -> 					     std::__niter_base(__result)));
     2879964 ->     }
                
                  /**
                   *  @brief Copies the range [first,last) into result.
                   *  @ingroup mutating_algorithms
                   *  @param  __first  An input iterator.
                   *  @param  __last   An input iterator.
                   *  @param  __result An output iterator.
                   *  @return   result + (first - last)
                   *
                   *  This inline function will boil down to a call to @c memmove whenever
                   *  possible.  Failing that, if random access iterators are passed, then the
                   *  loop count will be known (and therefore a candidate for compiler
                   *  optimizations such as unrolling).  Result may not be contained within
                   *  [first,last); the copy_backward function should be used instead.
                   *
                   *  Note that the end of the output range is permitted to be contained
                   *  within [first,last).
                  */
                  template<typename _II, typename _OI>
                    inline _OI
     2879964 ->     copy(_II __first, _II __last, _OI __result)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_II>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OI,
                	    typename iterator_traits<_II>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      return (std::__copy_move_a2<__is_move_iterator<_II>::__value>
                	      (std::__miter_base(__first), std::__miter_base(__last),
     2879964 -> 	       __result));
     2879964 ->     }
                
                #if __cplusplus >= 201103L
                  /**
                   *  @brief Moves the range [first,last) into result.
                   *  @ingroup mutating_algorithms
                   *  @param  __first  An input iterator.
                   *  @param  __last   An input iterator.
                   *  @param  __result An output iterator.
                   *  @return   result + (first - last)
                   *
                   *  This inline function will boil down to a call to @c memmove whenever
                   *  possible.  Failing that, if random access iterators are passed, then the
                   *  loop count will be known (and therefore a candidate for compiler
                   *  optimizations such as unrolling).  Result may not be contained within
                   *  [first,last); the move_backward function should be used instead.
                   *
                   *  Note that the end of the output range is permitted to be contained
                   *  within [first,last).
                  */
                  template<typename _II, typename _OI>
                    inline _OI
                    move(_II __first, _II __last, _OI __result)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_II>)
                      __glibcxx_function_requires(_OutputIteratorConcept<_OI,
                	    typename iterator_traits<_II>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      return std::__copy_move_a2<true>(std::__miter_base(__first),
                				       std::__miter_base(__last), __result);
                    }
                
                #define _GLIBCXX_MOVE3(_Tp, _Up, _Vp) std::move(_Tp, _Up, _Vp)
                #else
                #define _GLIBCXX_MOVE3(_Tp, _Up, _Vp) std::copy(_Tp, _Up, _Vp)
                #endif
                
                  template<bool, bool, typename>
                    struct __copy_move_backward
                    {
                      template<typename _BI1, typename _BI2>
                        static _BI2
                        __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
                        {
                	  while (__first != __last)
                	    *--__result = *--__last;
                	  return __result;
                	}
                    };
                
                #if __cplusplus >= 201103L
                  template<typename _Category>
                    struct __copy_move_backward<true, false, _Category>
                    {
                      template<typename _BI1, typename _BI2>
                        static _BI2
                        __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
                        {
                	  while (__first != __last)
                	    *--__result = std::move(*--__last);
                	  return __result;
                	}
                    };
                #endif
                
                  template<>
                    struct __copy_move_backward<false, false, random_access_iterator_tag>
                    {
                      template<typename _BI1, typename _BI2>
                        static _BI2
                        __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
                        {
                	  typename iterator_traits<_BI1>::difference_type __n;
                	  for (__n = __last - __first; __n > 0; --__n)
                	    *--__result = *--__last;
                	  return __result;
                	}
                    };
                
                #if __cplusplus >= 201103L
                  template<>
                    struct __copy_move_backward<true, false, random_access_iterator_tag>
                    {
                      template<typename _BI1, typename _BI2>
                        static _BI2
                        __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
                        {
                	  typename iterator_traits<_BI1>::difference_type __n;
                	  for (__n = __last - __first; __n > 0; --__n)
                	    *--__result = std::move(*--__last);
                	  return __result;
                	}
                    };
                #endif
                
                  template<bool _IsMove>
                    struct __copy_move_backward<_IsMove, true, random_access_iterator_tag>
                    {
                      template<typename _Tp>
                        static _Tp*
       ##### ->         __copy_move_b(const _Tp* __first, const _Tp* __last, _Tp* __result)
                        {
       ##### -> 	  const ptrdiff_t _Num = __last - __first;
       ##### -> 	  if (_Num)
       ##### -> 	    __builtin_memmove(__result - _Num, __first, sizeof(_Tp) * _Num);
       ##### -> 	  return __result - _Num;
       ##### -> 	}
                    };
                
                  template<bool _IsMove, typename _BI1, typename _BI2>
                    inline _BI2
       ##### ->     __copy_move_backward_a(_BI1 __first, _BI1 __last, _BI2 __result)
                    {
                      typedef typename iterator_traits<_BI1>::value_type _ValueType1;
                      typedef typename iterator_traits<_BI2>::value_type _ValueType2;
                      typedef typename iterator_traits<_BI1>::iterator_category _Category;
                      const bool __simple = (__is_trivial(_ValueType1)
                	                     && __is_pointer<_BI1>::__value
                	                     && __is_pointer<_BI2>::__value
       ##### -> 			     && __are_same<_ValueType1, _ValueType2>::__value);
                
                      return std::__copy_move_backward<_IsMove, __simple,
                	                               _Category>::__copy_move_b(__first,
                								 __last,
       ##### -> 								 __result);
       ##### ->     }
                
                  template<bool _IsMove, typename _BI1, typename _BI2>
                    inline _BI2
       ##### ->     __copy_move_backward_a2(_BI1 __first, _BI1 __last, _BI2 __result)
                    {
                      return _BI2(std::__copy_move_backward_a<_IsMove>
                		  (std::__niter_base(__first), std::__niter_base(__last),
       ##### -> 		   std::__niter_base(__result)));
       ##### ->     }
                
                  /**
                   *  @brief Copies the range [first,last) into result.
                   *  @ingroup mutating_algorithms
                   *  @param  __first  A bidirectional iterator.
                   *  @param  __last   A bidirectional iterator.
                   *  @param  __result A bidirectional iterator.
                   *  @return   result - (first - last)
                   *
                   *  The function has the same effect as copy, but starts at the end of the
                   *  range and works its way to the start, returning the start of the result.
                   *  This inline function will boil down to a call to @c memmove whenever
                   *  possible.  Failing that, if random access iterators are passed, then the
                   *  loop count will be known (and therefore a candidate for compiler
                   *  optimizations such as unrolling).
                   *
                   *  Result may not be in the range (first,last].  Use copy instead.  Note
                   *  that the start of the output range may overlap [first,last).
                  */
                  template<typename _BI1, typename _BI2>
                    inline _BI2
       ##### ->     copy_backward(_BI1 __first, _BI1 __last, _BI2 __result)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_BidirectionalIteratorConcept<_BI1>)
                      __glibcxx_function_requires(_Mutable_BidirectionalIteratorConcept<_BI2>)
                      __glibcxx_function_requires(_ConvertibleConcept<
                	    typename iterator_traits<_BI1>::value_type,
                	    typename iterator_traits<_BI2>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      return (std::__copy_move_backward_a2<__is_move_iterator<_BI1>::__value>
                	      (std::__miter_base(__first), std::__miter_base(__last),
       ##### -> 	       __result));
       ##### ->     }
                
                #if __cplusplus >= 201103L
                  /**
                   *  @brief Moves the range [first,last) into result.
                   *  @ingroup mutating_algorithms
                   *  @param  __first  A bidirectional iterator.
                   *  @param  __last   A bidirectional iterator.
                   *  @param  __result A bidirectional iterator.
                   *  @return   result - (first - last)
                   *
                   *  The function has the same effect as move, but starts at the end of the
                   *  range and works its way to the start, returning the start of the result.
                   *  This inline function will boil down to a call to @c memmove whenever
                   *  possible.  Failing that, if random access iterators are passed, then the
                   *  loop count will be known (and therefore a candidate for compiler
                   *  optimizations such as unrolling).
                   *
                   *  Result may not be in the range (first,last].  Use move instead.  Note
                   *  that the start of the output range may overlap [first,last).
                  */
                  template<typename _BI1, typename _BI2>
                    inline _BI2
                    move_backward(_BI1 __first, _BI1 __last, _BI2 __result)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_BidirectionalIteratorConcept<_BI1>)
                      __glibcxx_function_requires(_Mutable_BidirectionalIteratorConcept<_BI2>)
                      __glibcxx_function_requires(_ConvertibleConcept<
                	    typename iterator_traits<_BI1>::value_type,
                	    typename iterator_traits<_BI2>::value_type>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      return std::__copy_move_backward_a2<true>(std::__miter_base(__first),
                						std::__miter_base(__last),
                						__result);
                    }
                
                #define _GLIBCXX_MOVE_BACKWARD3(_Tp, _Up, _Vp) std::move_backward(_Tp, _Up, _Vp)
                #else
                #define _GLIBCXX_MOVE_BACKWARD3(_Tp, _Up, _Vp) std::copy_backward(_Tp, _Up, _Vp)
                #endif
                
                  template<typename _ForwardIterator, typename _Tp>
                    inline typename
                    __gnu_cxx::__enable_if<!__is_scalar<_Tp>::__value, void>::__type
                    __fill_a(_ForwardIterator __first, _ForwardIterator __last,
                 	     const _Tp& __value)
                    {
                      for (; __first != __last; ++__first)
                	*__first = __value;
                    }
                    
                  template<typename _ForwardIterator, typename _Tp>
                    inline typename
                    __gnu_cxx::__enable_if<__is_scalar<_Tp>::__value, void>::__type
                    __fill_a(_ForwardIterator __first, _ForwardIterator __last,
                	     const _Tp& __value)
                    {
                      const _Tp __tmp = __value;
                      for (; __first != __last; ++__first)
                	*__first = __tmp;
                    }
                
                  // Specialization: for char types we can use memset.
                  template<typename _Tp>
                    inline typename
                    __gnu_cxx::__enable_if<__is_byte<_Tp>::__value, void>::__type
                    __fill_a(_Tp* __first, _Tp* __last, const _Tp& __c)
                    {
                      const _Tp __tmp = __c;
                      __builtin_memset(__first, static_cast<unsigned char>(__tmp),
                		       __last - __first);
                    }
                
                  /**
                   *  @brief Fills the range [first,last) with copies of value.
                   *  @ingroup mutating_algorithms
                   *  @param  __first  A forward iterator.
                   *  @param  __last   A forward iterator.
                   *  @param  __value  A reference-to-const of arbitrary type.
                   *  @return   Nothing.
                   *
                   *  This function fills a range with copies of the same value.  For char
                   *  types filling contiguous areas of memory, this becomes an inline call
                   *  to @c memset or @c wmemset.
                  */
                  template<typename _ForwardIterator, typename _Tp>
                    inline void
                    fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __value)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<
                				  _ForwardIterator>)
                      __glibcxx_requires_valid_range(__first, __last);
                
                      std::__fill_a(std::__niter_base(__first), std::__niter_base(__last),
                		    __value);
                    }
                
                  template<typename _OutputIterator, typename _Size, typename _Tp>
                    inline typename
                    __gnu_cxx::__enable_if<!__is_scalar<_Tp>::__value, _OutputIterator>::__type
                    __fill_n_a(_OutputIterator __first, _Size __n, const _Tp& __value)
                    {
                      for (__decltype(__n + 0) __niter = __n;
                	   __niter > 0; --__niter, ++__first)
                	*__first = __value;
                      return __first;
                    }
                
                  template<typename _OutputIterator, typename _Size, typename _Tp>
                    inline typename
                    __gnu_cxx::__enable_if<__is_scalar<_Tp>::__value, _OutputIterator>::__type
                    __fill_n_a(_OutputIterator __first, _Size __n, const _Tp& __value)
                    {
                      const _Tp __tmp = __value;
                      for (__decltype(__n + 0) __niter = __n;
                	   __niter > 0; --__niter, ++__first)
                	*__first = __tmp;
                      return __first;
                    }
                
                  template<typename _Size, typename _Tp>
                    inline typename
                    __gnu_cxx::__enable_if<__is_byte<_Tp>::__value, _Tp*>::__type
                    __fill_n_a(_Tp* __first, _Size __n, const _Tp& __c)
                    {
                      std::__fill_a(__first, __first + __n, __c);
                      return __first + __n;
                    }
                
                  /**
                   *  @brief Fills the range [first,first+n) with copies of value.
                   *  @ingroup mutating_algorithms
                   *  @param  __first  An output iterator.
                   *  @param  __n      The count of copies to perform.
                   *  @param  __value  A reference-to-const of arbitrary type.
                   *  @return   The iterator at first+n.
                   *
                   *  This function fills a range with copies of the same value.  For char
                   *  types filling contiguous areas of memory, this becomes an inline call
                   *  to @c memset or @ wmemset.
                   *
                   *  _GLIBCXX_RESOLVE_LIB_DEFECTS
                   *  DR 865. More algorithms that throw away information
                  */
                  template<typename _OI, typename _Size, typename _Tp>
                    inline _OI
                    fill_n(_OI __first, _Size __n, const _Tp& __value)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_OutputIteratorConcept<_OI, _Tp>)
                
                      return _OI(std::__fill_n_a(std::__niter_base(__first), __n, __value));
                    }
                
                  template<bool _BoolType>
                    struct __equal
                    {
                      template<typename _II1, typename _II2>
                        static bool
                        equal(_II1 __first1, _II1 __last1, _II2 __first2)
                        {
                	  for (; __first1 != __last1; ++__first1, ++__first2)
                	    if (!(*__first1 == *__first2))
                	      return false;
                	  return true;
                	}
                    };
                
                  template<>
                    struct __equal<true>
                    {
                      template<typename _Tp>
                        static bool
                        equal(const _Tp* __first1, const _Tp* __last1, const _Tp* __first2)
                        {
                	  return !__builtin_memcmp(__first1, __first2, sizeof(_Tp)
                				   * (__last1 - __first1));
                	}
                    };
                
                  template<typename _II1, typename _II2>
                    inline bool
                    __equal_aux(_II1 __first1, _II1 __last1, _II2 __first2)
                    {
                      typedef typename iterator_traits<_II1>::value_type _ValueType1;
                      typedef typename iterator_traits<_II2>::value_type _ValueType2;
                      const bool __simple = ((__is_integer<_ValueType1>::__value
                			      || __is_pointer<_ValueType1>::__value)
                	                     && __is_pointer<_II1>::__value
                	                     && __is_pointer<_II2>::__value
                			     && __are_same<_ValueType1, _ValueType2>::__value);
                
                      return std::__equal<__simple>::equal(__first1, __last1, __first2);
                    }
                
                
                  template<typename, typename>
                    struct __lc_rai
                    {
                      template<typename _II1, typename _II2>
                        static _II1
                        __newlast1(_II1, _II1 __last1, _II2, _II2)
                        { return __last1; }
                
                      template<typename _II>
                        static bool
                        __cnd2(_II __first, _II __last)
                        { return __first != __last; }
                    };
                
                  template<>
                    struct __lc_rai<random_access_iterator_tag, random_access_iterator_tag>
                    {
                      template<typename _RAI1, typename _RAI2>
                        static _RAI1
                        __newlast1(_RAI1 __first1, _RAI1 __last1,
                		   _RAI2 __first2, _RAI2 __last2)
                        {
                	  const typename iterator_traits<_RAI1>::difference_type
                	    __diff1 = __last1 - __first1;
                	  const typename iterator_traits<_RAI2>::difference_type
                	    __diff2 = __last2 - __first2;
                	  return __diff2 < __diff1 ? __first1 + __diff2 : __last1;
                	}
                
                      template<typename _RAI>
                        static bool
                        __cnd2(_RAI, _RAI)
                        { return true; }
                    };
                
                  template<bool _BoolType>
                    struct __lexicographical_compare
                    {
                      template<typename _II1, typename _II2>
                        static bool __lc(_II1, _II1, _II2, _II2);
                    };
                
                  template<bool _BoolType>
                    template<typename _II1, typename _II2>
                      bool
                      __lexicographical_compare<_BoolType>::
                      __lc(_II1 __first1, _II1 __last1, _II2 __first2, _II2 __last2)
                      {
                	typedef typename iterator_traits<_II1>::iterator_category _Category1;
                	typedef typename iterator_traits<_II2>::iterator_category _Category2;
                	typedef std::__lc_rai<_Category1, _Category2> 	__rai_type;
                	
                	__last1 = __rai_type::__newlast1(__first1, __last1,
                					 __first2, __last2);
                	for (; __first1 != __last1 && __rai_type::__cnd2(__first2, __last2);
                	     ++__first1, ++__first2)
                	  {
                	    if (*__first1 < *__first2)
                	      return true;
                	    if (*__first2 < *__first1)
                	      return false;
                	  }
                	return __first1 == __last1 && __first2 != __last2;
                      }
                
                  template<>
                    struct __lexicographical_compare<true>
                    {
                      template<typename _Tp, typename _Up>
                        static bool
                        __lc(const _Tp* __first1, const _Tp* __last1,
                	     const _Up* __first2, const _Up* __last2)
                	{
                	  const size_t __len1 = __last1 - __first1;
                	  const size_t __len2 = __last2 - __first2;
                	  const int __result = __builtin_memcmp(__first1, __first2,
                						std::min(__len1, __len2));
                	  return __result != 0 ? __result < 0 : __len1 < __len2;
                	}
                    };
                
                  template<typename _II1, typename _II2>
                    inline bool
                    __lexicographical_compare_aux(_II1 __first1, _II1 __last1,
                				  _II2 __first2, _II2 __last2)
                    {
                      typedef typename iterator_traits<_II1>::value_type _ValueType1;
                      typedef typename iterator_traits<_II2>::value_type _ValueType2;
                      const bool __simple =
                	(__is_byte<_ValueType1>::__value && __is_byte<_ValueType2>::__value
                	 && !__gnu_cxx::__numeric_traits<_ValueType1>::__is_signed
                	 && !__gnu_cxx::__numeric_traits<_ValueType2>::__is_signed
                	 && __is_pointer<_II1>::__value
                	 && __is_pointer<_II2>::__value);
                
                      return std::__lexicographical_compare<__simple>::__lc(__first1, __last1,
                							    __first2, __last2);
                    }
                
                  /**
                   *  @brief Finds the first position in which @a val could be inserted
                   *         without changing the ordering.
                   *  @param  __first   An iterator.
                   *  @param  __last    Another iterator.
                   *  @param  __val     The search term.
                   *  @return         An iterator pointing to the first element <em>not less
                   *                  than</em> @a val, or end() if every element is less than 
                   *                  @a val.
                   *  @ingroup binary_search_algorithms
                  */
                  template<typename _ForwardIterator, typename _Tp>
                    _ForwardIterator
                    lower_bound(_ForwardIterator __first, _ForwardIterator __last,
                		const _Tp& __val)
                    {
                #ifdef _GLIBCXX_CONCEPT_CHECKS
                      typedef typename iterator_traits<_ForwardIterator>::value_type
                	_ValueType;
                #endif
                      typedef typename iterator_traits<_ForwardIterator>::difference_type
                	_DistanceType;
                
                      // concept requirements
                      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
                      __glibcxx_function_requires(_LessThanOpConcept<_ValueType, _Tp>)
                      __glibcxx_requires_partitioned_lower(__first, __last, __val);
                
                      _DistanceType __len = std::distance(__first, __last);
                
                      while (__len > 0)
                	{
                	  _DistanceType __half = __len >> 1;
                	  _ForwardIterator __middle = __first;
                	  std::advance(__middle, __half);
                	  if (*__middle < __val)
                	    {
                	      __first = __middle;
                	      ++__first;
                	      __len = __len - __half - 1;
                	    }
                	  else
                	    __len = __half;
                	}
                      return __first;
                    }
                
                  /// This is a helper function for the sort routines and for random.tcc.
                  //  Precondition: __n > 0.
                  inline _GLIBCXX_CONSTEXPR int
                  __lg(int __n)
                  { return sizeof(int) * __CHAR_BIT__  - 1 - __builtin_clz(__n); }
                
                  inline _GLIBCXX_CONSTEXPR unsigned
                  __lg(unsigned __n)
                  { return sizeof(int) * __CHAR_BIT__  - 1 - __builtin_clz(__n); }
                
                  inline _GLIBCXX_CONSTEXPR long
                  __lg(long __n)
                  { return sizeof(long) * __CHAR_BIT__ - 1 - __builtin_clzl(__n); }
                
                  inline _GLIBCXX_CONSTEXPR unsigned long
                  __lg(unsigned long __n)
                  { return sizeof(long) * __CHAR_BIT__ - 1 - __builtin_clzl(__n); }
                
                  inline _GLIBCXX_CONSTEXPR long long
                  __lg(long long __n)
                  { return sizeof(long long) * __CHAR_BIT__ - 1 - __builtin_clzll(__n); }
                
                  inline _GLIBCXX_CONSTEXPR unsigned long long
                  __lg(unsigned long long __n)
                  { return sizeof(long long) * __CHAR_BIT__ - 1 - __builtin_clzll(__n); }
                
                _GLIBCXX_END_NAMESPACE_VERSION
                
                _GLIBCXX_BEGIN_NAMESPACE_ALGO
                
                  /**
                   *  @brief Tests a range for element-wise equality.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first1  An input iterator.
                   *  @param  __last1   An input iterator.
                   *  @param  __first2  An input iterator.
                   *  @return   A boolean true or false.
                   *
                   *  This compares the elements of two ranges using @c == and returns true or
                   *  false depending on whether all of the corresponding elements of the
                   *  ranges are equal.
                  */
                  template<typename _II1, typename _II2>
                    inline bool
                    equal(_II1 __first1, _II1 __last1, _II2 __first2)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_II1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_II2>)
                      __glibcxx_function_requires(_EqualOpConcept<
                	    typename iterator_traits<_II1>::value_type,
                	    typename iterator_traits<_II2>::value_type>)
                      __glibcxx_requires_valid_range(__first1, __last1);
                
                      return std::__equal_aux(std::__niter_base(__first1),
                			      std::__niter_base(__last1),
                			      std::__niter_base(__first2));
                    }
                
                  /**
                   *  @brief Tests a range for element-wise equality.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first1  An input iterator.
                   *  @param  __last1   An input iterator.
                   *  @param  __first2  An input iterator.
                   *  @param __binary_pred A binary predicate @link functors
                   *                  functor@endlink.
                   *  @return         A boolean true or false.
                   *
                   *  This compares the elements of two ranges using the binary_pred
                   *  parameter, and returns true or
                   *  false depending on whether all of the corresponding elements of the
                   *  ranges are equal.
                  */
                  template<typename _IIter1, typename _IIter2, typename _BinaryPredicate>
                    inline bool
                    equal(_IIter1 __first1, _IIter1 __last1,
                	  _IIter2 __first2, _BinaryPredicate __binary_pred)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_IIter1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_IIter2>)
                      __glibcxx_requires_valid_range(__first1, __last1);
                
                      for (; __first1 != __last1; ++__first1, ++__first2)
                	if (!bool(__binary_pred(*__first1, *__first2)))
                	  return false;
                      return true;
                    }
                
                  /**
                   *  @brief Performs @b dictionary comparison on ranges.
                   *  @ingroup sorting_algorithms
                   *  @param  __first1  An input iterator.
                   *  @param  __last1   An input iterator.
                   *  @param  __first2  An input iterator.
                   *  @param  __last2   An input iterator.
                   *  @return   A boolean true or false.
                   *
                   *  <em>Returns true if the sequence of elements defined by the range
                   *  [first1,last1) is lexicographically less than the sequence of elements
                   *  defined by the range [first2,last2).  Returns false otherwise.</em>
                   *  (Quoted from [25.3.8]/1.)  If the iterators are all character pointers,
                   *  then this is an inline call to @c memcmp.
                  */
                  template<typename _II1, typename _II2>
                    inline bool
                    lexicographical_compare(_II1 __first1, _II1 __last1,
                			    _II2 __first2, _II2 __last2)
                    {
                #ifdef _GLIBCXX_CONCEPT_CHECKS
                      // concept requirements
                      typedef typename iterator_traits<_II1>::value_type _ValueType1;
                      typedef typename iterator_traits<_II2>::value_type _ValueType2;
                #endif
                      __glibcxx_function_requires(_InputIteratorConcept<_II1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_II2>)
                      __glibcxx_function_requires(_LessThanOpConcept<_ValueType1, _ValueType2>)
                      __glibcxx_function_requires(_LessThanOpConcept<_ValueType2, _ValueType1>)
                      __glibcxx_requires_valid_range(__first1, __last1);
                      __glibcxx_requires_valid_range(__first2, __last2);
                
                      return std::__lexicographical_compare_aux(std::__niter_base(__first1),
                						std::__niter_base(__last1),
                						std::__niter_base(__first2),
                						std::__niter_base(__last2));
                    }
                
                  /**
                   *  @brief Performs @b dictionary comparison on ranges.
                   *  @ingroup sorting_algorithms
                   *  @param  __first1  An input iterator.
                   *  @param  __last1   An input iterator.
                   *  @param  __first2  An input iterator.
                   *  @param  __last2   An input iterator.
                   *  @param  __comp  A @link comparison_functors comparison functor@endlink.
                   *  @return   A boolean true or false.
                   *
                   *  The same as the four-parameter @c lexicographical_compare, but uses the
                   *  comp parameter instead of @c <.
                  */
                  template<typename _II1, typename _II2, typename _Compare>
                    bool
                    lexicographical_compare(_II1 __first1, _II1 __last1,
                			    _II2 __first2, _II2 __last2, _Compare __comp)
                    {
                      typedef typename iterator_traits<_II1>::iterator_category _Category1;
                      typedef typename iterator_traits<_II2>::iterator_category _Category2;
                      typedef std::__lc_rai<_Category1, _Category2> 	__rai_type;
                
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_II1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_II2>)
                      __glibcxx_requires_valid_range(__first1, __last1);
                      __glibcxx_requires_valid_range(__first2, __last2);
                
                      __last1 = __rai_type::__newlast1(__first1, __last1, __first2, __last2);
                      for (; __first1 != __last1 && __rai_type::__cnd2(__first2, __last2);
                	   ++__first1, ++__first2)
                	{
                	  if (__comp(*__first1, *__first2))
                	    return true;
                	  if (__comp(*__first2, *__first1))
                	    return false;
                	}
                      return __first1 == __last1 && __first2 != __last2;
                    }
                
                  /**
                   *  @brief Finds the places in ranges which don't match.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first1  An input iterator.
                   *  @param  __last1   An input iterator.
                   *  @param  __first2  An input iterator.
                   *  @return   A pair of iterators pointing to the first mismatch.
                   *
                   *  This compares the elements of two ranges using @c == and returns a pair
                   *  of iterators.  The first iterator points into the first range, the
                   *  second iterator points into the second range, and the elements pointed
                   *  to by the iterators are not equal.
                  */
                  template<typename _InputIterator1, typename _InputIterator2>
                    pair<_InputIterator1, _InputIterator2>
                    mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
                	     _InputIterator2 __first2)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator2>)
                      __glibcxx_function_requires(_EqualOpConcept<
                	    typename iterator_traits<_InputIterator1>::value_type,
                	    typename iterator_traits<_InputIterator2>::value_type>)
                      __glibcxx_requires_valid_range(__first1, __last1);
                
                      while (__first1 != __last1 && *__first1 == *__first2)
                        {
                	  ++__first1;
                	  ++__first2;
                        }
                      return pair<_InputIterator1, _InputIterator2>(__first1, __first2);
                    }
                
                  /**
                   *  @brief Finds the places in ranges which don't match.
                   *  @ingroup non_mutating_algorithms
                   *  @param  __first1  An input iterator.
                   *  @param  __last1   An input iterator.
                   *  @param  __first2  An input iterator.
                   *  @param __binary_pred A binary predicate @link functors
                   *         functor@endlink.
                   *  @return   A pair of iterators pointing to the first mismatch.
                   *
                   *  This compares the elements of two ranges using the binary_pred
                   *  parameter, and returns a pair
                   *  of iterators.  The first iterator points into the first range, the
                   *  second iterator points into the second range, and the elements pointed
                   *  to by the iterators are not equal.
                  */
                  template<typename _InputIterator1, typename _InputIterator2,
                	   typename _BinaryPredicate>
                    pair<_InputIterator1, _InputIterator2>
                    mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
                	     _InputIterator2 __first2, _BinaryPredicate __binary_pred)
                    {
                      // concept requirements
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator1>)
                      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator2>)
                      __glibcxx_requires_valid_range(__first1, __last1);
                
                      while (__first1 != __last1 && bool(__binary_pred(*__first1, *__first2)))
                        {
                	  ++__first1;
                	  ++__first2;
                        }
                      return pair<_InputIterator1, _InputIterator2>(__first1, __first2);
                    }
                
                _GLIBCXX_END_NAMESPACE_ALGO
                } // namespace std
                
                // NB: This file is included within many other C++ includes, as a way
                // of getting the base algorithms. So, make sure that parallel bits
                // come in too if requested. 
                #ifdef _GLIBCXX_PARALLEL
                # include <parallel/algobase.h>
                #endif
                
                #endif


Top 10 Lines:

     Line      Count

      277    8639892
      288    5759928
      368    2879964
      379    2879964
      424    2879964
      450    2879964
      216    1439982

Execution Summary:

       41   Executable lines in this file
       41   Lines executed
   100.00   Percent of the file executed

 27359658   Total number of line executions
667308.73   Average executions per line


*** File /root/newtroll/troll.cpp:
                /*####################################################################
                 ###  TROLL
                 ###  Individual-based forest dynamics simulator
                 ###    Version 1: Jerome Chave
                 ###    Version 2.1 & 2.2: Isabelle Marechaux & Jerome Chave
                 ###    Version 2.3 onwards: Isabelle Marechaux, Fabian Fischer, Jerome Chave
                 ###
                 ###  History:
                 ###    version 0.1 --- JC - 22 Sep 97
                 ###    version 0.2 --- JC - 06 Oct 97
                 ###    version 0.3 --- JC - 11-14 Nov 97
                 ###    version 1.0 --- JC - stable version Chave, Ecological Modelling (1999)
                 ###    version 1.1 --- JC - 02-30 Sep 98
                 ###    version 1.2 --- JC - 22 Jan 00
                 ###    version 1.3 --- JC - 28 Sep 01 stable version Chave, American Naturalist (2001)
                 ###
                 ###    version 2.0 --- JC - 23 Mar 11 (physiology-based version, translation of comments into English)
                 ###    version 2.01 --- IM - oct-nov 13
                 ###    version 2.02 --- IM - apr-may 2015
                 ###    version 2.03 --- IM - jul 2015
                 ###    version 2.04 --- IM - jul 2015 (monthly timestep)
                 ###    version 2.1  --- IM - dec 2015 (undef/defined alternative versions)
                 ###    version 2.11 --- IM - jan 2016 timestep better used
                 ###    version 2.12 --- JC - jan 2016 porting to GitHub for social coding, check of the MPI routines and update, new header for code, trivia: reindentation (orphan lines removed)
                 ###    version 2.2  --- IM - may 2016 core changes in: daily coupling with environment; respiration; treefall module; leaf pool dynamics
                 ###    version 2.3  --- FF - oct-nov 2016: bug fixing (including UpdateSeed() bug), general reworking of code, changes in CalcLAI(), initialisation from data, toolbox with alternative fine flux calculation (cf. end of script)
                 ###    version 2.3.0 --- IM & JC - janv-feb 2017: new tree size threshold to maturity (dbhmature), changes in input file structure, corrections of temperature dependencies in GPPleaf. Code acceleration (use of lookup tables instead of functions in the calculations of the Fluxh() and GPPleaf() routines; faster whole-tree GPP calculation. This results in an increase in speed of a factor 4.
                 ###    version 2.3.1 --- IM & JC - feb-mar 2017: introduces the dispersal cell, or dcell concept (square subplot of linear size length_dcell)
                 ###    code acceleration FASTGPP concept improved.
                 ###    DCELL: GNU scientific library is needed -- on osx, type "brew install gsl"
                 ###    DCELL: Compile command (osx/linux):
                 ###                    g++ -O3 -Wall -o troll main_xx.cpp -lgsl -lgslcblas -lm
                 ###    DCELL: Code profiling (unix): g++ -O3 -Wall -o troll main_xx.cpp -lgsl -lgslcblas -lm -g -pg
                 ###
                 ####################################################################*/
                
                
                /*
                 Glossary: MPI = Message Passing Interface. Software for sharing information
                 across processors in parallel computers. If global variable MPI is not defined,
                 TROLL functions on one processor only.
                 */
                
                #undef MPI              /* If flag MPI defined, parallel routines (MPI software) are switched on */
                #undef easyMPI          /* If flag easyMPI defined, parallel routine for fast search of parameter space are switched on */
                #undef toolbox          /* never to be defined! Toolbox is an assortment of alternative formulations of TROLL procedures, attached to the code */
                
                #undef DCELL // this explores the need for an intermediate grid cell size
                
                /* Libraries */
                # include <cstdio>
                # include <iostream>
                # include <fstream>
                # include <cstdlib>
                # include <string>
                # include <limits>
                # include <ctime>
                # include <cmath>
                # include <cstring>
                
                # include <list>
                # include <iterator>
                # include <algorithm>
                # include <vector>
                
                # ifdef MPI
                # include "mpi.h"
                # endif
                # ifdef easyMPI
                # include "mpi.h"
                # endif
                
                using namespace std;
                
                /* Global constants (e.g. PI and various derivatives...) */
                # define PI 3.141592654
                # define twoPi 6.2831853071
                # define Pis2 1.570796327
                # define iPi 0.3183099
                char buffer[256], inputfile[256], outputinfo[256], inputfile_data[256], *bufi(0), *buf(0), *bufi_data(0);
                
                
                /* random number generators */
                double genrand2(void);
                void sgenrand2(unsigned long);
                unsigned long genrand2i(void);
                void sgenrand2i(unsigned long);
                
                /* file output streams */
                
       ##### -> fstream out,out2;
                
       ##### -> fstream output[38];
                
                /****************/
                /* User control */
                /****************/
                
                /* options can be turned on (1) or off (0). This comes, however, at computational costs. Where routines have to be called frequently, if-conditioning should be done as far outside the loop as possible (e.g. for DAILYLIGHT outside voxel loops) */
                /* currenly, options are set below, but inclusion in parameter sheet needed (for control from R) */
                
                bool
                _FASTGPP=0,             /* This defines an option to compute only GPP from the topmost value of PPFD and GPP, instead of looping within the crown. Much faster and more accurate */
                _BASICTREEFALL=1,       /* if defined: treefall is a source of tree death (and if TREEFALL not defined, this is modeled through simple comparison between tree height and a threshold t_Ct, if not defined, treefall is not represented as a separated and independent source of death, but instead, all tree death are due to the deathrate value) */
                _TREEFALL=0,            /* computation of the force field if TREEFALL is defined, neighboring trees contribute to fell each tree */
                _DAILYLIGHT=1,          /* if defined: the rate of carbon assimilation integrates an average daily fluctuation of light (thanks to GPPDaily). Should be defined to ensure an appropriate use of Farquhar model */
                _SEEDTRADEOFF=0,        /* if defined: the number of seeds produced by each tree is determined by the tree NPP allocated to reproduction and the species seed mass, otherwise the number of seeds is fixed; besides, seedling recruitment in one site is not made by randomly and 'equiprobably' picking one species among the seeds present at that site but the probability of recruitment among the present seeds is proportional to the number of seeds (in s_Seed[site]) time the seed mass of each species */
                _NDD=0,                 /* if defined, negative density dependant processes affect both the probability of seedling recruitment and the local tree death rate. The term of density-dependance is computed as the sum of conspecific tree basal area divided by their distance to the focal tree within a neighbourhood (circle of radius 15m) */
                _OUTPUT_reduced=1,      /* reduced set of ouput files */
                _OUTPUT_last100=0,      /* output that tracks the last 100 years of the simulation for the whole grid (2D) */
                _OUTPUT_fullLAI=0,       /* output of full final voxel field */
                _FromData=0;            /* if defined, an additional input file can be provided to start simulations from an existing data set or a simulated data set (5 parameters are needed: x and y coordinates, dbh, species_label, species */
                
                
                /********************************/
                /* Parameters of the simulation */
                /********************************/
                
                int sites,          /* number of sites */
                cols,               /* nb of columns */
                rows,               /* nb of lines */
                numesp,             /* nb of species */
                iterperyear,        /* nb of iter in a year (=12 if monthly timestep, =365 if daily timestep) */
                nbiter,             /* total nb of timesteps */
                iter,               /* current timestep */
                nbout,              /* nb of outputs */
                freqout;            /* frequency HDF outputs */
                
                /* NEW CHANGE: site_has_S[site_id] is a vector stores all the species_id of the available seeds on a site */
                /* NEW CHANGE: seed_count[site_id][species_id] replaces S[species_id].s_Seed[site_id] */
                // initialise an array storing the species_id that S[species_id].s_seed[site_id] > 0
                typedef vector<int> L;
                L *site_has_S(0);
                int **seed_count(0);
                
                
                #ifdef DCELL
                gsl_rng *gslrand;
                int length_dcell,   /* v2.3.1 linear size of a dcell */
                linear_nb_dcells,    /* linear number of dcells note that nbdcells = linear_nb_dcells^2 */
                sites_per_dcell,    /* number of sites per dcell */
                nbdcells;           /* total number of dcells */
                int **MAP_DCELL(0);   /* list of sites per dcell (for fast fillin) */
                double *prior_DCELL(0); /* prior for picking the dispersal sites within the dcell -- vector of size sites_per_dcell and with all entries equal to 1/sites_per_dcell (because the dispersal is equiprobable) */
                unsigned int *post_DCELL(0); /* number of seeds per site within the dcell */
                double *prior_GERM(0); /* prior for picking the germination event within a site -- vector of size numesp and with entries equal to the number of seeds multiplied by seedsize */
                unsigned int *post_GERM(0); /* vector with only one non-null entry (the successful germination event) */
                #endif
                
                int HEIGHT,         /* max height (in m) */
                dbhmaxincm,         /* max DBH times 100 (ie dbh in cm *100 = in meters) */
                RMAX,               /* max crown radius */
                SBORD;              /* RMAX*cols */
                
                float NV,           /* nb cells per m (vertical) */
                NH,                 /* nb cells per m (horizontal) */
                LV,                 /* LV = 1.0/NV */
                LH,                 /* LH = 1.0/NH */
                timestep;           /* duration of one timestep (in years)=1/iterperyear */
                
                float p_nonvert,    /* ratio of non-vertical incident light */
                Cseedrain,          /* constant used to scale total seed rain per hectare across species */
                nbs0,               /* nb of seeds produced and dispersed by each mature tree when SEEDTRADEOFF is not defined */
                Cair,               /* atmosphericCO2 concentration, if we aim at making CO2 vary (scenarios), CO2 will have to have the same status as other climatic variables  */
                iCair;              /* inverse of Cair */
                
                /* new version 2.2 */
                float daily_light[24];    /* normalized (ie between 0 and 1) daily light variation (used if DAILYLIGHT defined) */
                float daily_vpd[24];      /* normalized (ie between 0 and 1) daily vpd variation (used if DAILYLIGHT defined) */
                float daily_T[24];        /* normalized (ie between 0 and 1) daily T variation (used if DAILYLIGHTdefined) */
                
                /*parameter for NDD*/
                float R,                    /* distance beyond which NDD effect is not accounted anymore*/
                deltaR,                     /* NDD strength parameter in recruitment */
                deltaD,                     /* NDD strength parameter in deathrate */
                BAtot;
                
                
                /*********************************************/
                /* Environmental variables of the simulation */
                /*********************************************/
                
                /* Climate input data  */
                /* these climate input data are given in the input file, its structure depends on the timestep and scenario used for the simulation */
                /* new version 2.2 */
                float *Temperature(0);                      /* in degree Celsius */
                float *DailyMaxTemperature(0);              /* in degree Celsius */
                float *NightTemperature(0);                 /* in degree Celsius */
                float *Rainfall(0);                         /* in mm */
                float *WindSpeed(0);                        /* in m/s */
                float *MaxIrradiance(0);                    /* in W/m2 */
                float *MeanIrradiance(0);                   /* in W/m2 */
                float *SaturatedVapourPressure(0);          /* in kPa */
                float *VapourPressure(0);                   /* in kPa */
                float *VapourPressureDeficit(0);            /* in kPa */
                float *DailyVapourPressureDeficit(0);       /* in kPa */
                float *DailyMaxVapourPressureDeficit(0);    /* in kPa */
                
                /* New in v.2.3.0 */
                int nbTbins;                    /*nb of bins for the temperature lookup tables */
                float iTaccuracy;                /* inverse of accuracy of a temperature bin (e.g. Taccuracy us 0.1 or 0.5 °C, so iTaccuracy is 10.0 or 2.0, resp) */
                float *LookUp_KmT(0);                   /* lookup table for fast comput of Farquhar as a function of T */
                /* !! leaf temperature must be comprised between 0°C and 60°C
                 (T_leaf is stored every 0.5°C, so 120 values in total */
                float *LookUp_GammaT(0);                   /* lookup table for fast comput of Farquhar */
                float *LookUp_tempRday(0);                 /* lookup table for fast comput of Farquhar */
                float *LookUp_VcmaxT(0);                   /* lookup table for fast comput of Farquhar */
                float *LookUp_JmaxT(0);                   /* lookup table for fast comput of Farquhar */
                
                float *LookUp_flux(0);                 /* lookup table for faster computation of PPFD*/
                float *LookUp_VPD(0);                  /* lookup table for faster computation of VPD */
                float *LookUp_T(0);                    /* lookup table for faster computation of T */
                float *LookUp_Rstem(0);                /* lookup table for faster computation of Rstem */
                float *LookUp_Rnight(0);                /* lookup table for faster computation of Rstem */
                
                /***** Environmental variables, changed at each timestep *****/
                float temp,         /* Temperature */
                tmax,               /* Daily max temperature */
                tnight,             /* Night mean temperature */
                precip,             /* Rainfall  */
                WS,                 /* WindSpeed */
                Wmax,               /* Daily max irradiance (average for timestep) (in micromol PAR photon/m^2/s)*/
                /* used in the photosynthesis part. see if it would not be better to have value in the right unit in the input file, however W/m2 is the common unit of meteo station */
                /* below: new version 2.2 */
                Wmean,              /* mean irradiance (in W/m2)*/
                e_s,                /* SaturatedVapourPressure */
                e_a,                /* VapourPressure*/
                VPDbasic,           /* VapourPressureDeficit */
                VPDday,             /* DailyVapourPressureDeficit */
                VPDmax;             /* DailyMaxVapourPressureDeficit */
                
                
                /****************************************/
                /*  Common variables for the species    */
                /* (simplifies initial version 170199)  */
                /****************************************/
                
                //int Cm;           /* Treefall threshold */
                float klight,       /* light absorption rate or extinction cefficient used in Beer-Lambert law to compute light within the canopy */
                phi,                /* apparent quantum yield (in micromol C/micromol photon). phi is the quantum yield multiplied by leaf absorbance (in the literature, the quantum yield is often given per absorbed light flux, so one should multiply incident PPFD by leaf absorbance, see Poorter et al American Journal of Botany (assumed to be 0.91 for tropical tree species). Even though holding phi constant across species is widely assumed, in reality, phi varies across species and environmental conditions (see eg Domingues et al 2014 Plant Ecology & Diversity) */
                theta,              /* parameter of the Farquhar model set to 0.7 in this version. For some authors, it should be species-dependent or temperature dependent, but these options are not implemented here */
                g1,                 /* g1 parameter of Medlyn et al's model of stomatal conductance. v230: defined as a global parameter shared by species, instead of a Species class's variable */
                alpha,              /* apparent quantum yield to electron transport in mol e-/mol photons, equal to the true quantum yield multiplied by the leaf absorbance -- v.2.2 */
                vC,                 /* variance of treefall threshold */
                H0,                 /* initial height (in m) */
                DBH0,               /* initial DBH (in m) */
                de0,                /* initial crown Crown_Depth (in m) */
                de1,                /* Crown_Depth/height slope */
                /* fallocwood and falloccanopy new -- v.2.2 */
                fallocwood,         /* fraction of biomass allocated to above ground wood (branches+stem) */
                falloccanopy,       /* fraction of biomass allocated to canopy (leaves + reproductive organs + twigs) */
                dens,               /* initial leaf density (in m^2/m^3) */
                ra1,                /* crown radius - dbh slope */
                ra0,                /* initial crown radius (in m) */
                m,                  /* basal death rate */
                m1;                 /* deathrate-wsg slope -- new v.2.2 */
                
                float halfDividedByTheta;
                
                
                float **LAI3D(0);   /* leaf density (per volume unit) */
                unsigned short *Thurt[3];            /* Treefall field */
                
                int    *SPECIES_GERM (0);
                float  *PROB_S (0); /* _SEEDTRADEOFF */
                float tempRday;     /* temporary variable used for the computation of leaf day respiration -- new v.2.2 */
                
                
                /***************/
                /* Diagnostics */
                /***************/
                
                int nbdead_n1,             /* nb deaths other than treefall dbh > 1 cm, computed at each timestep */
                nbdead_n10,                /* nb deaths other than treefall dbh > 10 cm, computed at each timestep */
                nblivetrees,            /* nb live trees for each timestep  */
                nbdead_c1,                 /* nb deaths caused by a treefall dbh > 1 cm, computed at each timestep, _BASICTREEFALL */
                nbdead_c10,                /* nb deaths caused by a treefall dbh > 10 cm, computed at each timestep, _BASICTREEFALL */
                nbTreefall1,            /* nb treefalls for each timestep (dbh > 1cm), _BASICTREEFALL */
                nbTreefall10;           /* nb treefalls for each timestep (dbh > 10 cm), _BASICTREEFALL */
                
                //long int *persist;	/* persistence histogram */
                int *nbdbh(0);          /* dbh size distribution */
                float *layer(0);        /* vertical LAI histogram */
                
                /**************/
                /* Processors */
                /**************/
                
                int mpi_rank,mpi_size;
                int easympi_rank,easympi_size;
                
                
                /******************/
                /* MPI procedures */
                /******************/
                
                #ifdef MPI
                unsigned short **LAIc[2];
                void
                MPI_ShareSeed(unsigned char **,int),
                MPI_ShareField(unsigned short **,unsigned short ***,int),
                MPI_ShareTreefall(unsigned short **,int);
                #endif
                
                
                /**********************/
                /* Simulator routines */
                /**********************/
                
                void
                Initialise(void),
                InitialiseFromData(void),
                AllocMem(void),
                BirthInit(void),
                Evolution(void),
                UpdateField(void),
                UpdateTreefall(void),               // _BASICTREEFALL
                UpdateTree(void),
                Average(void),
                OutputField(void),
                FreeMem(void);
                
                /**********************/
                /** Output routines ***/
                /**********************/
                
                void
                OutputSnapshot(fstream& output),
                OutputSnapshotDetail(fstream& output),
                OutputSpeciesParameters(fstream& output),
                OutputFullLAI(fstream& output_CHM, fstream& output_LAD);
                
                /****************************/
                /* Various inline functions */
                /****************************/
                
                
   870355305 -> inline float flor(float f) {
   870355305 ->     if(f>0.) return f;
   870355305 ->     else return 0.;
   870355305 -> }
                inline float florif(int i) {
                    if(i>0) return float(i);
                    else return 0.;
                }
         726 -> inline float maxf(float f1, float f2) {
         726 ->     if(f1>f2) return f1;
         726 ->     else return f2;
         726 -> }
  5899500952 -> inline float minf(float f1, float f2) {
  5899500952 ->     if(f1<f2) return f1;
  5899500952 ->     else return f2;
  5899500952 -> }
 11780403896 -> inline int min(int i1, int i2) {
 11780403896 ->     if(i1<i2) return i1;
 11780403896 ->     else return i2;
 11780403896 -> }
  4730107229 -> inline int max(int i1, int i2) {
  4730107229 ->     if(i1>i2) return i1;
  4730107229 ->     else return i2;
  4730107229 -> }
       ##### -> inline int sgn(float f) {
       ##### ->     if(f>0.0) return 1;
       ##### ->     else return -1;
       ##### -> }
                
                
                /*############################################
                 ############################################
                 ###########     Species  class   ###########
                 ############################################
                 ############################################*/
                
                class Species {
                    
                public:
                    int    s_nbind,			/* nb of individuals per species */
                    s_dormDuration,         /* seed dormancy duration -- not used in v.2.2 */
                    s_nbext;                /* total number of incoming seeds in the simulated plot at each timestep (seed rain) -- v.2.2 */
                
                    int s_id; /* species id */
                    //int s_index;
                
                    char	s_name[256];	/* species name */
                    float  s_LCP,			/* light compensation point  (in micromol photon/m^2/s) */
                    s_Rdark,                /* dark respiration rate (at PPFD = 0) in micromol C/m^2/s) */
                    s_ds,                   /* average dispersal distance */
                    //  de1,                /* (crown depth) - height slope deprecated v.2.1 */
                    s_dmax,                 /* maximal dbh (given in m) */
                    s_hmax,                 /* maximal height (given in m) */
                    s_dbh0,                 /* Initial dbh at recruitement, computed for each species with the species-specific allometric relationship at h=H0=1m -- in v230 */
                    s_Vcmax,                /* maximal rate of carboxylation, on an area basis (in micromolC/m^2/s) */
                    s_Vcmaxm,               /* maximal rate of carboxylation, on a mass basis (in micromolC/g-1/s) */
                    s_Jmax,                 /* maximal rate of electron transport, on an area basis (in micromol/m^2/s) */
                    s_Jmaxm,                /* maximal rate of electron transport, on a mass basis (in micromol/g-1/s) */
                    s_fci,                  /* fraction of CO2 partial pressure in intercellular spaces divided by ambiant CO2 partial pressure (both in microbar, or ppm = micromol/mol) */
                    s_Gamma,                /* compensation point for the carboxylation rate, here NORMALIZED by atm CO2 concentration (Cair) */
                    s_Km,                   /* apparent kinetic constant for the rubiscco = Kc*(1+[O]/Ko), here normalized by atm CO2 concentration (Cair) */
                    //s_d13C,                 /* isotopic carbon discrimination NOW normalized at zero height -- deprecated v.2.2 */
                    s_LMA,                  /* leaf mass per area (in g/m^2) */
                    s_Nmass,                /* leaf nitrogen concentration (in g/g) v.2.01 */
                    s_Pmass,                /* leaf phosphorous concentration (in g/g) v.2.01 */
                    s_wsg,                  /* wood specific gravity (in g/cm^3) */
                    s_ah,                   /* parameter for allometric height-dbh equation */
                    s_seedmass,             /* seed mass, in g (from Baraloto & Forget 2007 dataset, in classes) v.2.3: seeminlgy deprecated in v.2.2, but still necessary for SEEDTRADEOFF */
                    s_iseedmass,            /* inverse of seed mass, v.2.3: seeminlgy deprecated in v.2.2, but still necessary for SEEDTRADEOFF */
                    //s_factord13Ca,        /* deprecated v.2.2 -- factor used for a previous version of ci/ca ratio computation, from d13C value */
                    //s_factord13Cb,        /* deprecated v.2.2 -- factor used for a previous version of ci/ca ratio computation, from d13C value */
                    /* Below: new in v.2.2 */
                    s_leaflifespan,         /* average leaf lifespan, in month */
                    s_time_young,           /* leaf resident time in the young leaf class */
                    s_time_mature,          /* leaf resident time in the mature leaf class */
                    s_time_old,             /* leaf resident time in the old leaf class */
                    s_output_field[24];         /* scalar output fields per species (<24) */
                
                    // look-up tables within species to store calculated results given a T
                    float s_LookUp_tempRday[500],
                          s_LookUp_VcmaxT[500],
                          s_LookUp_JmaxT[500],
                          s_LookUp_thetaJmaxT[500];
                    bool s_calculated[500];
                    
                #ifdef DCELL
                    int *s_DCELL;	/* number of seeds from the species in each dcell */
                    int *s_Seed;	/* presence/absence of seeds at each site; if def SEEDTRADEOFF, the number of seeds */
                #else
                    int *s_Seed;	/* presence/absence of seeds; if def SEEDTRADEOFF, the number of seeds */
                #endif
                    
                #ifdef MPI
                    unsigned char *s_Gc[4]; /* MPI: seeds on neighboring procs */
                #endif
                    
                    
         164 ->     Species() {
         164 ->         s_nbind=0;
         164 ->         s_Seed=0;
                #ifdef DCELL
                        s_DCELL=0;
                #endif
         164 ->     };                              /* constructor */
                    
         164 ->     virtual ~Species() {
         164 ->         delete [] s_Seed;
                #ifdef DCELL
                        delete [] s_DCELL;
                #endif
         164 ->     };                              /* destructor */
                    
                    void Init(int,fstream&);        /* init Species class */
                #ifdef DCELL
                    void FillSeed(int,int,int);         /* assigns the produced seeds to s_DCELL */
                #else
                    void FillSeed(int,int);         /* fills s_Seed field (and s_Gc (MPI)) */
                #endif
                    void UpdateSeed(void);       /* Updates s_Seed field */
                #ifdef MPI
                    void AddSeed(void);             /* MPI: adds fields s_Gc  to field s_Seed */
                #endif
                    inline float DeathRateNDD(float, float,int, float); /* _NDD, overloading with function in following line */
                    inline float DeathRate(float, float, int);  /* actual death rate -- new argument int v.2.2 */
                    inline float GPPleaf(float, float, float);    /* Computation of the light-limited leaf-level NPP per m^2 (in micromol/m^2/s) -- two new arguments float v.2.2 */
                    /* Farquhar von Caemmerer Berry model */
                    inline float dailyGPPleaf(float, float, float, float, float);    /* computation of the daily average assimilation rate, taking into account the daily variation in light, VPD and temperature two new arguments float v.2.2, _DAILYLIGHT */
                };
                
                
                /*############################
                 ###  Initialize Species  ###
                 ###    Species::Init     ###
                 ############################*/
                
         163 -> void Species::Init(int nesp,fstream& is) {
                    
                    int site;
                    float regionalfreq;     // "regional" relative abundance of the species -- new name v.2.2
                    float SLA;              // specific leaf area = 1/LMA
                
         163 ->     for (int i = 0; i < 500; i++) s_calculated[i] = false;
                
         163 ->     s_id = nesp;
                    //s_index = pow(2, seed_height) - 1 + s_id;
                    
                    /*** Read parameters ***/
                    
                    //new input file -- in v230
         163 ->     is  >> s_name >> s_LMA >> s_Nmass >>  s_Pmass  >> s_wsg >> s_dmax >> s_hmax  >> s_ah >> s_seedmass >> regionalfreq;
                    
                    // instead of seedmass we are given seedvolume
                    // from this we assume a conversion factor of 1 to wet mass (~density of water, makes seeds float)
                    // to convert to drymass we use a conversion factor of 0.4 (~40% of the seed are water)
                    
         163 ->     s_seedmass *= 0.4;
         163 ->     s_iseedmass=1.0/s_seedmass;
         163 ->     s_ds=40.0;
                    
         163 ->     s_dbh0=s_ah*H0/(s_hmax-H0);
                    
                #ifdef DCELL
                    /* NEW in 2.3.1: input of seeds per timestep and per dcell is assumed proportional to seed size (large seeds are less numerous) this is compensated for by a lower recruitment probability for small seeds compared to large ones. Thus, in essence, we still have the seed number regeneration tradeoff but we allow more stochasticity in this process. Also, at least one seed arrives in the dcell from each species at each timestep (this is the +1 term) */
                #endif
                    
                    // uniform composition of the seed rain -- in v230
         163 ->     regionalfreq=1.0/float(numesp);
                    
         163 ->     if(_SEEDTRADEOFF){
         163 ->         s_nbext = (int(regionalfreq*Cseedrain*s_iseedmass)+1);
                    }
                    else {
         163 ->         s_nbext = int(regionalfreq*Cseedrain*(sites*LH*LH/10000));
                    }
                    
         163 ->     SLA=10000.0/s_LMA;    // computation of specific leaf area in cm^2/g for use in Domingues et al 2010 model of photosynthetic capacities
                    
                    //s_leaflifespan=1.5+pow(10,(7.18+3.03*log10(s_LMA*0.0001)));           //this is the expression from Reich et al 1991 Oecologia (San Carlos Rio Negro).
         163 ->     s_leaflifespan=pow(10,(2.040816*(2.579713-log10(SLA))));    //this is the expression from Reich et al. 1997 PNAS (provides probably more realistic estimates for species with high LMA).
                    //s_leaflifespan=0.5+pow(10,(-2.509+1.71*log10(s_LMA)));    //this is the expression from Wright et al 2004 Nature (leaf economics spectrum).
         163 ->     s_time_young=1;
         163 ->     s_time_mature=s_leaflifespan/3.0;
         163 ->     s_time_old=s_leaflifespan-s_time_mature-s_time_young;
                    
                    /*** Normalization of the parameters ***/
                    /* vertical (NV) and horizontal (NH) scales */
                    
         163 ->     s_ah   *= NV*LH;
         163 ->     s_ds   *= NH;
         163 ->     s_hmax *= NV;
         163 ->     s_dmax *= NH;
         163 ->     s_dbh0 *= NH;
                    
         163 ->     s_nbind=0;
         163 ->     s_fci = 0.0;
                    
         163 ->     s_Vcmaxm=pow(10.0, minf((-1.56+0.43*log10(s_Nmass*1000.0)+0.37*log10(SLA)), (-0.80+0.45*log10(s_Pmass*1000.0)+0.25*log10(SLA))));
                    // this is equation 2 in Domingues et al 2010 PCE (coefficients from fig7) which made better fits than equation 1 (without LMA)
         163 ->     s_Jmaxm=pow(10.0, minf((-1.50+0.41*log10(s_Nmass*1000.0)+0.45*log10(SLA)), (-0.74+0.44*log10(s_Pmass*1000.0)+0.32*log10(SLA))));
                    // added as a Species member variable 14-04-2015; this is equ 2 in Domingues et al 2010 PCE (coefficients from fig7)
                    
         163 ->     s_Vcmax=s_Vcmaxm*s_LMA;
         163 ->     s_Jmax=s_Jmaxm*s_LMA;
                    
         163 ->     s_Rdark=s_LMA*(8.5341-130.6*s_Nmass-567.0*s_Pmass-0.0137*s_LMA+11.1*s_Vcmaxm+187600.0*s_Nmass*s_Pmass)*0.001;
                    
                    //s_Rdark corresponds to leaf maintenance respiration. From Table 6 in Atkin et al 2015 New phytologist v.2.0 */
                    
                    //s_Rdark=(82.36*(s_LMA*1e-3)-0.1561)*(s_LMA*1e-3);                 /* from Domingues et al 2007 */
                    //s_Rdark=0.01*s_Vcmax;                                             /* parameterization of Rdark commonly used in vegetation models */
                    //s_Rdark=0.02*s_Vcmax-0.01;                                        /* parameterization of von Caemmerer 2000 Table 2.3 page 45 */
                    
         163 ->     s_Gamma = 38.0*iCair;
                    
                    // s_Gamma at 25°C computed according to von Caemmerer 2000 formula: gamma=Kc*O*0.25/(2*Ko), with Kc=260 microbar, Ko=179mbar and O=210 mbar (the last value is from Farquhar et al 1980, the first two one are from von Caemmerer 2000 table 2.3 page 45). gamma is set to 36.9 on Atkin et al 2015. Could be a global variable. v.2.0
                    
         163 ->     s_LCP = s_Rdark/phi;    /* Computation of the light compensation point from dark respiration and the quantum yield phi. By definition, Rdark is in micromolC/m^2/s and it is used in the Species::NPP() routine */
                    
                    
                    
                #ifdef DCELL
                    if (NULL==(s_DCELL = new int[nbdcells])) cerr<<"!!! Mem_Alloc s_DCELLn";
                    for(int dcell=0;dcell<nbdcells;dcell++) s_DCELL[dcell]=0;
                    /***  field initialization ***/
                    if (NULL==(s_Seed = new int[sites])) cerr<<"!!! Mem_Alloc\n";
                
                    /* NEW CHANGE: site_has_S */
                    for(site=0;site<sites;site++) {
                        seed_count[site][s_id] = 0;
                        site_has_S[site].erase(s_id);
                    }
                
                #else
                    /***  field initialization ***/
         163 ->     if (NULL==(s_Seed = new int[sites])) cerr<<"!!! Mem_Alloc\n";
                
                    /* NEW CHANGE: site_has_S */
         163 ->     for(site=0;site<sites;++site) {
         163 ->         seed_count[site][s_id] = 0;
         163 ->         site_has_S[site].erase(std::remove(site_has_S[site].begin(), site_has_S[site].end(), s_id), site_has_S[site].end());
                    }
                
                
                #endif
                    
                #ifdef MPI
                    for(int i=0;i<4;i++) {
                        if (NULL==(s_Gc[i] = new unsigned char[sites])) cerr<<"!!! Mem_Alloc\n";
                        for(site=0;site<sites;site++) s_Gc[i][site]=0;
                    }
                #endif
         163 -> }
                
                
                /*############################
                 ###     Species Seeds     ###
                 ###   Species::FillSeed   ###
                 ###  Species::UpdateSeed  ###
                 ###   Species::AddSeed    ###
                 #############################*/
                
                /*###  Species::FillSeed  ###*/
                /* creates one seed at point (col,row) */
                
                #ifdef DCELL
                /* in the new approach with a mean field seed flux (DCELL), the function FillSeed has a new
                 role: it fills the vector s_DCELL that stores the number of produced seeds per timestep and per dcell */
                
                void Species::FillSeed(int dcol, int drow, int nbs) {
                    
                    s_DCELL[dcol+linear_nb_dcells*drow]+=nbs;
                }
                
                #else
                
   147361510 -> void Species::FillSeed(int col, int row) {
                    int site;
   147361510 ->     if(col < cols) {
   147361510 ->         if((row >= 0) && (row < rows)) {
   147361510 ->             site=col+cols*row;
   147361510 ->             if(_SEEDTRADEOFF){
                                //if (s_Seed[site] == 0) site_has_S[site].push_back(s_id);
   147361510 ->                 s_Seed[site]++;                         /* ifdef SEEDTRADEOFF, s_Seed[site] is the number of seeds of this species at that site */
                            }
                            else{
                
                                /* NEW CHANGE: site_has_S */
   147361510 ->                 if (seed_count[site][s_id] == 0){
   147361510 ->                     site_has_S[site].push_back(s_id);
   147361510 ->                     seed_count[site][s_id] = 1;
                                }
                                //If s_Seed[site] = 0, site is not occupied, if s_Seed[site] > 1, s_Seed[site] is the age of the youngest seed
   147361510 ->                 else if (seed_count[site][s_id] != 1) seed_count[site][s_id] = 1;
                
                
                            }
                        }
                        
                #ifdef MPI                                       /* on each processor a stripe of forest is simulated.
                Nearest neighboring stripes are shared. Rque, this version is not valid ifdef SEEDTRADEOFF */
                        else if((row+rows >=0) && (row < 0)) {
                            site=col+cols*(row+rows);
                            if(s_Gc[0][site]!=1) s_Gc[0][site]=1;
                        }
                        else if((row >=rows) && (row < 2*rows)) {
                            site=col+cols*(row-rows);
                            if(s_Gc[1][site]!=1) s_Gc[1][site]=1;
                        }
                #endif
                    }
   147361510 -> }
                #endif
                
                
                
                /*### Species::UpdateSeed ###*/
                /* updates s_Seed field */
                /* new in v.2.3: not called within loop over sites,
                 * instead includes loop --> less function calling,
                 * BUT: no check of site occupation anymore, cf. below */
                
                #ifdef DCELL
                /* in the new approach with a mean field seed flux (DCELL), the function UpdateSeed
                 has a new role: it uses the vector s_DCELL to fill the s_Seed local seed bank */
                
                void Species::UpdateSeed() {
                    int site;
                
                    /* NEW CHANGE: site_has_S */
                    for(site=0;site<sites;site++) {
                        seed_count[site][s_id] = 0;
                        site_has_S[site].erase(std::remove(site_has_S[site].begin(), site_has_S[site].end(), s_id), site_has_S[site].end());
                    }
                
                
                    for(int dcell=0;dcell<nbdcells;dcell++){ // loop over dcells
                        int localseeds=min(s_DCELL[dcell],sites_per_dcell);
                        // store number of seeds in this dcell
                        // localseeds is capped by the max number of available sites in the dcell
                        s_DCELL[dcell]=0;
                        gsl_ran_multinomial(gslrand,sites_per_dcell,localseeds,prior_DCELL,post_DCELL);
                        //cerr << "Localseeds in dcell\t" << dcell << " : " << localseeds << endl;
                        /*float sumprior=0.0,sumpost=0;
                         for(int i=0;i<sites_per_dcell;i++){
                         sumprior+=prior_DCELL[i];sumpost+=post_DCELL[i];
                         }*/
                        //cerr <<"localseeds\t"<< localseeds << "\tsumprior\t"<< sumprior << "\tsumpost\t"<< sumpost << "\n";
                        // sample equiprobably all the sites in the dcell
                        for(int i=0;i<sites_per_dcell;i++){ // update the s_Seed site
                            site=MAP_DCELL[dcell][i];
                            if (s_Seed[site] == 0 && post_DCELL[i] != 0) site_has_Seed[site].push_back(s_id);
                            s_Seed[site] = post_DCELL[i];
                            //cerr << "site\t" << site << "\tdcell\t" << dcell << "\tlocal_site\t" << i << "\tpost_DCELL[i]\t" << post_DCELL[i] << "\ts_Seed[site]\t" << s_Seed[site] << endl;
                        }
                    }
                    /*int summ=0;
                     for(site=0;site<sites;site++) summ=summ+s_Seed[site];
                     cerr << "Localseeds of species \t" << s_name  << "\t: " << summ << endl; */
                    
                    
                }
                #else
      978000 -> void Species::UpdateSeed() {
                    
                    /* should probably be modified, since as implemented now seeds are erased every timestep
                     * (i.e. month in default mode)--> to be discussed */
                    
      978000 ->     if(_SEEDTRADEOFF){
      978000 ->         for(int site=0;site<sites;site++){
                # ifdef MPI
                            s_Gc[0][site]=s_Gc[1][site]=s_Gc[2][site]=s_Gc[3][site]=0;
                #endif
                            //s_Seed[site]=0;
      978000 ->             seed_count[site][s_id] = 0;
                            //site_has_S[site].erase(s_id);
                        }
                    }
                    
                    else{
                        /* new in v.2.3: version 2.2 checked whether site was occupied by tree: T[site].t_age>0) s_Seed[site]=0;     */
                        /* v.2.3 does not do this within UpdateSeed() anymore.
                         * Instead, it sets all occupied sites to zero directly within UpdateTree() */
                        //for(int site=0;site<sites;site++){
                            
                # ifdef MPI
                            //s_Gc[0][site]=s_Gc[1][site]=s_Gc[2][site]=s_Gc[3][site]=0;
                #endif
                            /* seed bank ages or disappears */
                
                            /*if(s_Seed[site]==s_dormDuration) {
                                s_Seed[site]=0;   //!!!!
                                site_has_S[site].remove(s_id);
                            }*/
                
                            //else
                                //if(s_Seed[site]!=0) s_Seed[site]++;      //!!!!
                                //if (seed_count[site][s_id] != 0) seed_count[site][s_id] ++;
                            // v.2.3: bug fix: before, procedure was not restricted to existing seeds, therefore creation of seeds
                
                
                
                            /*
                            if (seed_count[site][s_id] == s_dormDuration){
                                seed_count[site][s_id] = 0;
                                int i = s_index;
                                if (species_count[site][i] > 0){
                                    while (i > 0){
                                        species_count[site][i] --;
                                        i = i >> 1;
                                    }
                                }
                            }
                            else if (seed_count[site][s_id] != 0) seed_count[site][s_id] ++;*/
                        //}
                    }
      978000 -> }
                #endif
                
                #ifdef MPI
                /* deprecated in v.2 -- needs a new concept for spatial parallelization -- hopefully soon */
                /*########################################
                 ###  Calculation of shared fields s_Gc ###
                 ########################################*/
                void Species::AddSeed() {
                    /* Stripes shared by several processors are redefined */
                    for(int site=0;site<sites;site++) {
                        if(p_rank){
                            if(!s_Seed[site]) {
                                s_Seed[site] = s_Gc[2][site];
                                site_has_S[site].push_back(s_id);
                            }
                            if(s_Seed[site]>1)
                                if(s_Gc[2][site]) s_Seed[site] = min(s_Seed[site],s_Gc[2][site]);
                        }
                        if(p_rank<size-1){
                            if(!s_Seed[site]) {
                                s_Seed[site] = s_Gc[3][site];
                                //_S[site].push_back(s_id);
                            }
                            if(s_Seed[site]>1)
                                if(s_Gc[3][site]) s_Seed[site] = min(s_Seed[site],s_Gc[3][site]);
                        }
                    }
                }
                #endif
                
                
                /*############################
                 ###   Species::DeathRate  ###
                 #############################*/
                
                /* Here we assume a light-dependent version of the mortality.
                 basal is the minimal species death rate, depending on the species wood density.
                 When PPFD is smaller than the light compensation point, mortality risk is increased.
                 When NDD is defined, this death rate is increased by density-dependence effect that impact survival of trees with a dbh<10cm . */
                
                
                /* v.2.2 Simplify function Species::DeathRate -- JChave */
                
                /* Changed v.2.2, _NDD */
                /* v;2.3.0 function has been renamed to avoid possible confusion downstream */
                
                
       ##### -> inline float Species::DeathRateNDD(float PPFD, float dbh, int nppneg, float ndd) {
                    
       ##### ->     float dr=0;
       ##### ->     float basal=m*(1-s_wsg);
       ##### ->     float dd=deltaD*ndd*(1-2*dbh/s_dmax);
                    
       ##### ->     dr=basal;
       ##### ->     if (nppneg > s_leaflifespan) {
       ##### ->         dr+=1.0/timestep;
                    }
       ##### ->     if (dd > 0) {
       ##### ->         dr+=dd;
                    }
                    
       ##### ->     return dr*timestep;
       ##### -> }
                
                
                
   681296615 -> inline float Species::DeathRate(float PPFD, float dbh, int nppneg) {
                    
   681296615 ->     float dr=0;
   681296615 ->     float basal=m-m1*s_wsg;
                    
   681296615 ->     dr=basal;
                    
   681296615 ->     if (nppneg > s_leaflifespan) dr+=1.0/timestep;
                    
   681296615 ->     if (iter == int(nbiter-1))
   681296615 ->         output[26]<< s_wsg << "\t" << basal << "\t"  << dbh << "\t"  << dr   <<  "\n";
                    
   681296615 ->     return dr*timestep;
   681296615 -> }
                
                /*#############################################
                 ###   Farquhar von Caemmerer Berry model  ###
                 ###           Species:: NPP               ###
                 #############################################*/
                
                /* This function returns the leaf-level carbon assimilation rate in micromoles C/m^2/s according to Farquhar-von Caemmerer-Berry model */
                /* The function Species::dailyGPPleaf returns the primary productivity per unit leaf area, i.e. in micromoles C/m^2/s.
                 It is converted into gC per m^2 of leaf per timestep by "*189.3*timestep" accounting only for the light hours (12 hours instead of 24): 189.3=12*3600*365.25*12/1000000
                 BEWARE: 12 is the molar mass of C, and also the number of light hours in a day
                 BEWARE: timestep is given as fraction of a year, so what is computed is actually the full assimilation per year which, in turn, is multiplied by the fraction per year that is under consideration
                 BEWARE: slight inconsistency through use of 365.25 when daily timestep is likely to be given as 365, but not incorrect
                 Commented version below was in use prior to version 2.3.0 -- use of lookup tables for acceleration of T dependence. cf. Bernacchi et al 2003 PCE; von Caemmerer 2000
                 derivation of s_fci (ci/ca) according to Medlyn et al 2011, see also Prentice et al 2014 Ecology Letters and Lin et al 2015 Nature Climate Change --- initial version: s_fci = minf(-0.04*s_d13C-0.3*(log(PPFD)-s_factord13Cb)*s_factord13Ca-0.57, 1.0);
                 from d13C (see cernusak et al 2013) without explicit model of stomatal conductance; min added in order to prevent ci:ca bigger than 1 (even though Ehleringer et al 1986 reported some values above 1 (Fig3) */
                
                
 35938166619 -> inline float Species::GPPleaf(float PPFD, float VPD, float T) {
                    
                    /* v.2.3.0: theta defined as a global variable */
                    //theta=0.7;   // this is the fixed value of theta used by von Caemmerer 2000
                    
                    //float theta=0.76+0.018*T-0.00037*T*T;         // theta, but temperature dependent cf. Bernacchi et al 2003 PCE
                    
                    /* Parameters for Farquhar model, with temperature dependencies */
 35938166619 ->     int convT= int(iTaccuracy*T); // temperature data at a resolution of Taccuracy=0.1°C -- stored in lookup tables ranging from 0°C to 50°C ---
                
 35938166619 ->     float KmT = LookUp_KmT[convT];
 35938166619 ->     float GammaT = LookUp_GammaT[convT];
                    float VcmaxT;
                    float JmaxT;
                
                    /* NEW CHANGE: use s_calculated to check if convT has been calculated before, if so, use previously calculated results */
                    /* NEW CHANGE: the new look-up tables are defined within species class */
                    /* (FOR FUTURE): KmT, VcmaxT are not required to be defined, insert into eqn directly */
                
 35938166619 ->     if (s_calculated[convT]){
                
 35938166619 ->         tempRday += s_LookUp_tempRday[convT];
 35938166619 ->         VcmaxT = s_LookUp_VcmaxT[convT];
 35938166619 ->         JmaxT = s_LookUp_JmaxT[convT];
                
                    }
                    else {
                
 35938166619 ->         s_calculated[convT] = true;
                
 35938166619 ->         s_LookUp_tempRday[convT] = s_Rdark * LookUp_tempRday[convT];
 35938166619 ->         tempRday += s_LookUp_tempRday[convT];
 35938166619 ->         VcmaxT = s_LookUp_VcmaxT[convT] = s_Vcmax * LookUp_VcmaxT[convT];
 35938166619 ->         JmaxT = s_LookUp_JmaxT[convT] = s_Jmax * LookUp_JmaxT[convT];
 35938166619 ->         s_LookUp_thetaJmaxT[convT] = 4.0 * theta * JmaxT;
                
                    }
                
 35938166619 ->     s_fci = g1 / (g1 + sqrt(VPD));       /*!!!!*/
                
                    /* FvCB model */
                
 35938166619 ->     float I = alpha * PPFD;
 35938166619 ->     float Ji = JmaxT + I;
 35938166619 ->     float J = (Ji - sqrt(Ji * Ji - s_LookUp_thetaJmaxT[convT] * I)) * halfDividedByTheta;
                
 35938166619 ->     return minf(VcmaxT / (s_fci + KmT), 0.25 * J / (s_fci + 2.0 * GammaT)) * (s_fci - GammaT);
                
 35938166619 -> }
                
                /* dailyGPPleaf returns the assimilation rate (computed from Species::GPPleaf) averaged across the daily fluctuations in climatic conditions (light, VPD and T), in micromoles C/m^2/s */
                
                /* used only by _DAILYLIGHT */
                
                
  1500806301 -> inline float Species::dailyGPPleaf(float PPFD, float VPD, float T, float dens, float CD) {
  1500806301 ->     float ppfde, dailyA=0.0;
                
                    /* NEW CHANGE: loop unrolling; calculate ppfde directly because daily_light[] are all non-zero */
  1500806301 ->     ppfde = PPFD * daily_light[0];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[0], T*daily_T[0]);
  1500806301 ->     ppfde = PPFD * daily_light[1];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[1], T*daily_T[1]);
  1500806301 ->     ppfde = PPFD * daily_light[2];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[2], T*daily_T[2]);
  1500806301 ->     ppfde = PPFD * daily_light[3];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[3], T*daily_T[3]);
  1500806301 ->     ppfde = PPFD * daily_light[4];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[4], T*daily_T[4]);
  1500806301 ->     ppfde = PPFD * daily_light[5];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[5], T*daily_T[5]);
  1500806301 ->     ppfde = PPFD * daily_light[6];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[6], T*daily_T[6]);
  1500806301 ->     ppfde = PPFD * daily_light[7];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[7], T*daily_T[7]);
  1500806301 ->     ppfde = PPFD * daily_light[8];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[8], T*daily_T[8]);
  1500806301 ->     ppfde = PPFD * daily_light[9];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[9], T*daily_T[9]);
  1500806301 ->     ppfde = PPFD * daily_light[10];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[10], T*daily_T[10]);
  1500806301 ->     ppfde = PPFD * daily_light[11];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[11], T*daily_T[11]);
  1500806301 ->     ppfde = PPFD * daily_light[12];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[12], T*daily_T[12]);
  1500806301 ->     ppfde = PPFD * daily_light[13];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[13], T*daily_T[13]);
  1500806301 ->     ppfde = PPFD * daily_light[14];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[14], T*daily_T[14]);
  1500806301 ->     ppfde = PPFD * daily_light[15];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[15], T*daily_T[15]);
  1500806301 ->     ppfde = PPFD * daily_light[16];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[16], T*daily_T[16]);
  1500806301 ->     ppfde = PPFD * daily_light[17];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[17], T*daily_T[17]);
  1500806301 ->     ppfde = PPFD * daily_light[18];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[18], T*daily_T[18]);
  1500806301 ->     ppfde = PPFD * daily_light[19];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[19], T*daily_T[19]);
  1500806301 ->     ppfde = PPFD * daily_light[20];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[20], T*daily_T[20]);
  1500806301 ->     ppfde = PPFD * daily_light[21];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[21], T*daily_T[21]);
  1500806301 ->     ppfde = PPFD * daily_light[22];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[22], T*daily_T[22]);
  1500806301 ->     ppfde = PPFD * daily_light[23];
  1500806301 ->     if (ppfde > 0.1) dailyA += GPPleaf(ppfde, VPD*daily_vpd[23], T*daily_T[23]);
                
                    /* Original Code:
                    for(int i = 0; i < 24; i++) {
                        ppfde = PPFD * daily_light[i];
                        if (ppfde > 0.1)
                            // new v.2.3.0: compute GPP only if enough light is available threshold is arbitrary, but set to be low: in full sunlight ppfd is aroung 700 W/m2, and even at dawn, it is ca 3% of the max value, or 20 W/m2. The minimum threshold is set to 0.1 W/m2
                            // Future update: compute slightly more efficiently, using 3-hourly values? This will have to be aligned with climate forcing layers (e.g. NCAR)
                            dailyA += GPPleaf(ppfde, VPD*daily_vpd[i], T*daily_T[i]);         !!!
                        //the 6 lines in comment below corresponds to a finer version in which the multiplier is computed and used every 48 half hour, ie. with the corresponding environment instead of assuming a constant multiplier correponding the one at maximum incoming irradiance
                        //float hhA=0;
                        //hhA=GPPleaf(PPFD*daily_light[i], VPD*daily_vpd[i], T*daily_T[i]);
                        //float alpha=phi*PPFD*daily_light[i]/hhA;
                        //float D=klight*dens*CD;
                        //hhA*=alpha/(D*(alpha-1))*log(alpha/(1+(alpha-1)*exp(-D)));
                        //dailyA+=hhA;
                    }*/
                    //daily_light is the averaged (across one year, meteo station Nouragues DZ) and normalized (from 0 to 1) daily fluctuation of light, with half-hour time step, during the day time (from 7am to 7pm, ie 12 hours in total), same for daily_vpd and daily_T. Taking into account these daily variation is necessary considering the non-linearity of FvCB model
                    
  1500806301 ->     if(_FASTGPP){
  1500806301 ->         float alpha=phi*PPFD/GPPleaf(PPFD, VPD, T);             //alpha is a non-dimensional figure used to compute the multiplier below
  1500806301 ->         float D=klight*dens*CD;                                 //D is a non-dimensional figure used to compute the multiplier below
  1500806301 ->         float m=alpha/(D*(alpha-1))*log(alpha/(1+(alpha-1)*exp(-D)));
  1500806301 ->         if (m>=1.0 || CD > 7.0) {
  1500806301 ->             cout << "m pb FASTGPP !!!" << endl;
                            
                        }
  1500806301 ->         dailyA*=alpha/(D*(alpha-1))*log(alpha/(1+(alpha-1)*exp(-D)));  // the FvCB assimilation rate computed at the top of the tree crown is multiplied by a multiplier<1, to account for the lower rate at lower light level within the crown depth. This multiplier is computed assuming that change in photosynthetic assimilation rate within a tree crown is mainly due to light decrease due to self-shading following a Michealis-menten relationship (ie. we assume that 1/ the change is not due to changes in VPD or temperature, which are supposed homogeneous at the intra-crown scale, and 2/ that other tree contributions to light decrease is neglected).
                    }
  1500806301 ->     dailyA *= 0.0417;                                 // 0.0417=1/24 (24=12*2 = number of half hours in the 12 hours of daily light)
  1500806301 ->     tempRday *= 0.0417;
  1500806301 ->     return dailyA;
  1500806301 -> }
                
                
                /*############################################
                 ############################################
                 ############     Tree  class    ############
                 ############################################
                 ############################################*/
                
                class Tree {
                    
                private:
                    float t_C;                    /* flexural force intensity, _TREEFALL, float? */
                    
                public:
                    int   t_site,           /* location */
                    t_NPPneg;               /* diagnostic variable: number of consecutive timesteps with NPP<0 -- V.2.2 */
                    float t_dbh_thresh,       /* dbh threshold */
                    t_hmax,                 /* hmax, but not real maximum */
                    t_angle,                /* orientation of applied force, _TREEFALL */
                    t_dbhmature,            /* reproductive size threshold IM janv2017 -- v230 */
                    t_dbh,                  /* diameter at breast height (in m, but used in number of horizontal cells throughout all the code) */
                    t_Tree_Height,          /* total tree height (in m, but used in number of vertical cells throughout all the code) */
                    t_Crown_Depth,          /* crown depth (in m, but used in number of vertical cells throughout all the code) */
                    t_Crown_Radius,         /* crown radius (in m, but used in number of horizontal cells throughout all the code)*/
                    t_Ct,                   /* flexural force threshold, _BASICTREEFALL */
                    t_GPP,                  /* tree gross primary productivity */
                    t_NPP,                  /* tree net primary productivity (in gC/timestep) */
                    t_Rday,                 /* leaf respiration during day */
                    t_Rnight,               /* leaf respiration during night */
                    t_Rstem,                /* stem respiration */
                    t_PPFD,                 /* light intensity received by the tree (computed by Tree::Flux, depending of the LAI at the tree height) */
                    t_VPD,                    /* VPD at tree height -- v.2.2 */
                    t_T,                    /* Temperature at tree height -- v.2.2 */
                    t_ddbh,                 /* increment of dbh per timestep */
                    t_age,                  /* tree age */
                    t_youngLA,              /* total young leaf area, in m2 -- v.2.2  */
                    t_matureLA,             /* total mature leaf area, in m2 -- v.2.2  */
                    t_oldLA,                /* total old leaf area, in m2 -- v.2.2  */
                    t_leafarea,             /* total crown leaf area in m2 -- v.2.2  */
                    t_dens,                 /* tree crown average leaf density in m2/m2 -- v.2.2  */
                    t_litter;               /* tree litterfall at each timestep, in g (of dry mass) -- v.2.2  */
                    float *t_NDDfield;      /* _NDD */
                    
                    Species *t_s;
                    
                    unsigned short
                    t_from_Data,            /* indicator of whether tree is born through initialisation or through simulation routine */
                    t_sp_lab,               /* species label */
                    t_hurt;                 /* treefall index */
                    
      160000 ->     Tree(){                 /* constructor */
      160000 ->         t_from_Data = 0;
      160000 ->         t_sp_lab = 0;
      160000 ->         t_age = 0;
      160000 ->         t_hurt = 0;
      160000 ->         t_NPP=t_GPP=t_Rday=t_Rnight=t_Rstem=t_PPFD=t_VPD=t_T=0.0; /* new v.2.2 */
                        
      160000 ->         if(_TREEFALL){
      160000 ->             t_C  = 0;
      160000 ->             t_angle = 0.0;
                        }
      160000 ->         if(_BASICTREEFALL) t_Ct = 0.0;
                        
      160000 ->         t_dbh = t_Tree_Height = t_Crown_Radius = 0.0;
                        
      160000 ->     };
                    
      160000 ->     virtual ~Tree() {
      160000 ->         delete [] t_NDDfield;   /* _NDD */
      160000 ->     };	/* destructor */
                    
                    
                    void Birth(Species*,int,int);	/* tree birth */
                    
                    
                    void BirthFromData(Species *S, int nume, int site0, float dbh_measured); /* tree initialisation from field data */
                    void Death();                   /* tree death */
                    void Growth();                  /* tree growth */
                    void Fluxh(int h);             /* compute mean light flux received by the tree crown layer at height h new version (PPFD symmetrical with T and VPD) -- v230 */
                    void UpdateLeafDynamics();           /* computes within-canopy leaf dynamics (IM since v 2.1, as a standalone function in v.2.3.0) */
                    void UpdateTreeBiometry();      /* compute biometric relations, including allometry -- contains a large part of empirical functions */
                    int   Couple();                 /* force exerted by other trees, _TREEFALL */
                    
                    void DisperseSeed();            /* update Seed field */
                    void FallTree();                /* tree falling routine, _TREEFALL */
                    
                    void Update();                  /* tree evolution at each timestep */
                    void Average();                 /* local computation of the averages */
                    void CalcLAI();
                    //void TrunkLAI();              /* computation  of trunk LAI -- deprecated v.2.2 */
                    void histdbh();                 /* computation of dbh histograms */
                    void OutputTreeStandard();  /* creates standard output for trees, writes directly to cout stream */
                    void OutputTreeStandard(fstream& output);         /* overloading of function, creates standard output for trees */
                };
                
                
                /*##############################################
                 ####	            Tree birth              ####
                 ####  called by BirthInit and UpdateTree   ####
                 ##############################################*/
                
                
    27111063 -> void Tree::Birth(Species *S, int nume, int site0) {
                    
    27111063 ->     t_site = site0;
    27111063 ->     t_sp_lab = nume;            /* t_sp_lab is the species label of a site. Can be defined even if the site is empty (cf. persistence function defined in Chave, Am Nat. 2001) */
    27111063 ->     t_NPPneg=0.0;
    27111063 ->     t_s = S+t_sp_lab;
                
    27111063 ->     t_age = 1;
                    // put this site index into T_alive
                    //T_alive.push_back(site0);
                
    27111063 ->     t_hurt = 0;
    27111063 ->     t_dbh=(t_s->s_dbh0);
    27111063 ->     t_ddbh=0.0;
    27111063 ->     t_dbh_thresh = ((t_s->s_dmax)-t_dbh)*flor(1.0+log(genrand2())*0.01)+t_dbh;
    27111063 ->     t_hmax = (t_s->s_hmax);
    27111063 ->     t_Tree_Height = H0;
    27111063 ->     t_Crown_Radius  = ra0;
    27111063 ->     t_Crown_Depth = de0;
    27111063 ->     t_dens=dens;
                    
    27111063 ->     t_youngLA=t_dens*PI*t_Crown_Radius*LH*t_Crown_Radius*LH*t_Crown_Depth*LV;
                    /* initially, all stems have only young leaves -- LA stands for leaf area */
    27111063 ->     t_matureLA=0;           /* this is the amount of leaf area at maturity */
    27111063 ->     t_oldLA=0;              /* leaf area of senescing leaves */
    27111063 ->     t_leafarea=t_youngLA;   /* should be sum of LA young+mature+old, but the equation is correct initially */
    27111063 ->     tempRday=0.0;
                    
    27111063 ->     float hrealmax=3*t_hmax * t_dbh_thresh/(3*t_dbh_thresh + 2*t_s->s_ah);
                    
    27111063 ->     t_dbhmature=t_s->s_dmax*0.5; // this correponds to the mean thresholds of tree size to maturity, according to Visser et al. 2016 Functional Ecology (suited to both understory short-statured species, and top canopy large-statured species). NOTE that if we decide to keep it as a fixed species-specific value, this could be defined as a Species calss variable, and computed once in Species::Init. -- v230
                    //float u=genrand2();
                    //t_dbhmature=maxf(0, -(t_s->s_dmax)*0.25*log((1-u)/u)+t_s->s_dmax*0.5);    // IM test 02-2017, try to introduce intra-species inter-individual variability in dbhmature, following a sigmoidal repartition function, as in Visser et al. 2016 and Wright et al. 2005
                    
    27111063 ->     if(_BASICTREEFALL) t_Ct = hrealmax*flor(1.0-vC*sqrt(-log(genrand2())));
    27111063 ->     (t_s->s_nbind)++;
    27111063 ->     nblivetrees++;
                    
                    /* setting diagnostic variables */
    27111063 -> }
                
                
                /*##############################################
                 ####   Tree Initialization from Data       ####
                 ##############################################*/
                
       ##### -> void Tree::BirthFromData(Species *S, int nume, int site0, float dbh_measured) {
                    
                    // entirely modelled following Tree::Birth
                    // main differences: dbh is given, related parameters are not set to fixed initial values, but derived through allometries
                    // for comments regarding allometries and t_leafarea cf. Tree::Growth
                    // for comments regarding everything else cf. Tree::Birth
                    
       ##### ->     t_site = site0;
       ##### ->     t_sp_lab = nume;
       ##### ->     t_NPPneg=0;
       ##### ->     t_s = S+t_sp_lab;
                
       ##### ->     t_age = 1;          //value not correct, but generally not problematic, used mainly as diagnostic variable and as indicator of whether tree is alive or not (death itself is independent of age), BUT: use as diagnostic variable cannot be ensured anymore and be careful if conditioning on t_age (e.g. for maturation)
                    // put this site index into T_alive
                    //T_alive.push_back(site0);
                
       ##### ->     t_from_Data = 1;    //indicates that tree stems from data (and therefore t_age could not be used, etc.)
       ##### ->     t_hurt = 0;
                    
       ##### ->     if((t_s->s_dmax)*1.5 > dbh_measured) t_dbh = dbh_measured;                          // force dbh to be within limits of TROLL specifications
                    else {
       ##### ->         t_dbh = (t_s->s_dmax);
       ##### ->         cout << "Warning: DBH_measured > 1.5*DBH_max for species. DBH set to DBH_max for species \n";
                    }
                    
       ##### ->     t_ddbh=0.0;
       ##### ->     t_dbh_thresh = (t_s->s_dmax);
       ##### ->     t_hmax = (t_s->s_hmax);
                    
       ##### ->     t_Tree_Height = t_hmax * t_dbh/(t_dbh + (t_s->s_ah));
       ##### ->     t_Crown_Radius  = 0.80+10.47*t_dbh-3.33*t_dbh*t_dbh;;
       ##### ->     if (t_Tree_Height<5.0) t_Crown_Depth = 0.133+0.168*t_Tree_Height;
       ##### ->     else t_Crown_Depth = -0.48+0.26*t_Tree_Height;
       ##### ->     t_dens=dens;
       ##### ->     t_leafarea=t_dens*PI*t_Crown_Radius*LH*t_Crown_Radius*LH*t_Crown_Depth;
       ##### ->     t_youngLA=0.25*t_leafarea;
       ##### ->     t_matureLA=0.5*t_leafarea;
       ##### ->     t_oldLA=0.25*t_leafarea;
       ##### ->     Fluxh(int(t_Tree_Height)+1);
       ##### ->     tempRday=0.0;
                    
                    /* v.2.3.0 in version 2.3 and prior, fluxes were also initialized, resulting in a longer code, with multiple repetitions of the same empirical functions. It is better *NOT* to call empirical functions more than once. */
                    
       ##### ->     float hrealmax = 3*t_hmax * t_dbh_thresh/(3*t_dbh_thresh + 2*t_s->s_ah);
                    
       ##### ->     t_dbhmature=t_s->s_dmax*0.5; // after Visser et al. (2016)
                    
       ##### ->     if(_BASICTREEFALL) t_Ct = hrealmax*flor(1.0-vC*sqrt(-log(genrand2())));
       ##### ->     (t_s->s_nbind)++;
       ##### ->     nblivetrees++;
                    
       ##### -> }
                
                
                
                /*################################################
                 #### Contribution of each tree in LAI field  ####
                 ####          called by UpdateField          ####
                 #################################################*/
                
                /* modified in v.2.3: additional contribution to voxels that are not fully occupied by the tree crown.
                 * !!!: this does not calculate LAI3D directly, this only calculates the density in each voxel belonging to a tree.
                 * The final LAI field is calculated outside of the class Tree */
                
   960000000 -> void Tree::CalcLAI() {
   960000000 ->     if(t_age > 0) {
                        int crown_base,
                        crown_top,
                        crown_r,
                        row_trunc,
                        col_trunc,
                        xx, yy,
                        col, row,
                        site;
                        
   960000000 ->         crown_r = int(t_Crown_Radius);
   960000000 ->         row_trunc = t_site / cols;
   960000000 ->         col_trunc = t_site % cols;
   960000000 ->         crown_base = int(t_Tree_Height - t_Crown_Depth);
   960000000 ->         crown_top = int(t_Tree_Height);
                        // loop over the tree crown
                
                        /* NEW CHANGE: take "if (crown_top - crown_base == 0)" out to avoid repeated logic evaluation inside the loop */
   960000000 ->         if (crown_top - crown_base == 0){
   960000000 ->             for(col = max(0, col_trunc - crown_r); col <= min(cols - 1, col_trunc + crown_r); col++) {
   960000000 ->                 for(row = max(0, row_trunc - crown_r); row <= min(rows - 1, row_trunc + crown_r); row++) {
   960000000 ->                     xx = col_trunc - col;
   960000000 ->                     yy = row_trunc - row;
   960000000 ->                     if(xx*xx + yy*yy <= crown_r*crown_r){      // check whether voxel is within crown
   960000000 ->                         site = col + cols * row + SBORD;
                                        //cout << crown_top << " " << site<<endl;
   960000000 ->                         LAI3D[crown_top][site] += t_dens * t_Crown_Depth;
                                    }
                                }
                            }
                        }
                        else{
                            /* NEW CHANGE: take minus1, minus2 out to avoid repeated calculations inside the loop */
   960000000 ->             float minus1 = t_Tree_Height - crown_top;
   960000000 ->             float minus2 = crown_base + 1 - (t_Tree_Height - t_Crown_Depth);
                
   960000000 ->             for(col = max(0, col_trunc - crown_r); col <= min(cols - 1, col_trunc + crown_r); col++) {
   960000000 ->                 for(row = max(0, row_trunc - crown_r); row <= min(rows - 1, row_trunc + crown_r); row++) {
   960000000 ->                     xx = col_trunc - col;
   960000000 ->                     yy = row_trunc - row;
   960000000 ->                     if(xx*xx + yy*yy <= crown_r*crown_r){  // check whether voxel is within crown
   960000000 ->                         site = col + cols * row + SBORD;
   960000000 ->                         LAI3D[crown_top][site] += t_dens * minus1;
   960000000 ->                         LAI3D[crown_base][site] += t_dens * minus2;
   960000000 ->                         if(crown_top - crown_base >= 2){
   960000000 ->                             for(int h = crown_base + 1; h <= crown_top - 1; h++)
   960000000 ->                                 LAI3D[h][site] += t_dens;    // loop over the crown depth
                                        }
                                    }
                                }
                            }
                        }
                        /* (FOR FUTURE): LAI3D[][] can times t_dens in the final stage */
                
                    }
   960000000 -> }
                
                
                
                /*###################################################
                 ####  Computation of PPFD right above the tree  ####
                 ####    called by Tree::Birth and Growth   in     ####
                 ####################################################*/
                
                /* v.2.3.: Tree::Fluxh() computes the average light flux received by a tree crown layer at height h , and also the average VPD and T it is thriving in (modified 1/02/2016)*/
                
  1500806301 -> void Tree::Fluxh(int h) {
  1500806301 ->     int count = 0,
                    xx, yy, radius_int;
  1500806301 ->     float absorb = 0.0;
  1500806301 ->     t_PPFD = 0.0;
  1500806301 ->     t_VPD  = 0.0;
  1500806301 ->     t_T    = 0.0;
  1500806301 ->     radius_int = int(t_Crown_Radius);
                
  1500806301 ->     if(radius_int == 0) {
  1500806301 ->         count = 1;
  1500806301 ->         if (h < HEIGHT) absorb = minf(LAI3D[h][t_site+SBORD], 19.5);
                        // absorb = 0.0 by default
  1500806301 ->         int intabsorb = int(absorb * 20.0);
  1500806301 ->         t_PPFD = LookUp_flux[intabsorb];
  1500806301 ->         t_VPD  = LookUp_VPD[intabsorb];
  1500806301 ->         t_T    = tmax - LookUp_T[intabsorb];
                    }
                    else {
                        int row0, col0, row, index;
  1500806301 ->         row0 = t_site / cols;
  1500806301 ->         col0 = t_site % cols;
                
                        /* NEW CHANGE: use index to avoid repeated calculation of "col+cols*row+SBORD" inside the loop */
  1500806301 ->         for(int col = max(0, col0-radius_int); col < min(cols, col0+radius_int+1); col ++) {
  1500806301 ->             row = max(0, row0-radius_int);
  1500806301 ->             index = col + cols * row + SBORD;
  1500806301 ->             for(row; row < min(rows, row0+radius_int+1); row ++) {
                                //loop over the tree crown
  1500806301 ->                 xx = col0 - col;
  1500806301 ->                 yy = row0 - row;
  1500806301 ->                 if(xx*xx + yy*yy <= radius_int*radius_int) {
                                    //is the voxel within crown?
  1500806301 ->                     count ++;
  1500806301 ->                     if (h < HEIGHT) absorb = minf(LAI3D[h][index], 19.5);         /* FOR FUTURE: replace index with index+col*row */
  1500806301 ->                     int intabsorb = int(absorb*20.0);
  1500806301 ->                     t_PPFD += LookUp_flux[intabsorb];
  1500806301 ->                     t_VPD  += LookUp_VPD[intabsorb];
  1500806301 ->                     t_T    += tmax - LookUp_T[intabsorb];
                                }
  1500806301 ->                 index += cols;
                            }
                        }
                    }
                
                    /* NEW CHANGE: take Wmax and VPDmax out to avoid repeated multiplication within the loop */
                    /* NEW CHANGE: deleted "* 1.0" ? */
  1500806301 ->     t_PPFD *= Wmax / float(count);
  1500806301 ->     t_VPD  *= VPDmax / float(count);
  1500806301 ->     t_T    /= float(count);
                
                    /* (FOR FUTURE): Wmax, VPDmax changes per iteration, can cache Wmax/float(count) */
  1500806301 -> }
                
                
                /*############################################
                 ####            Tree growth              ####
                 ####         called by UpdateTree        ####
                 #############################################*/
                
   654301400 -> void Tree::Growth() {
                    
                    /* Flux Tree variables */
   654301400 ->     t_GPP=0.0;
   654301400 ->     t_NPP=0.0;
   654301400 ->     t_Rday=0.0;
   654301400 ->     t_Rnight=0.0;
   654301400 ->     t_Rstem=0.0;
   654301400 ->     tempRday=0.0;
                    
                    /* Local environmental Tree variables */
   654301400 ->     t_PPFD=0.0;
   654301400 ->     t_VPD=0.0;
   654301400 ->     t_T=0.0;
                    
                    /* Leaf dynamics module */
                    //t_litter=0.0;
                    //float flush=0.0; // flushing leaves
                    
                    /* variables for flux computations */
                    
   654301400 ->     t_age+= timestep;                               /* new v.2.2: increments are not 1 yr, but the duration of the timestep (usually 1 or <1, i.e. 1/12 if monthly, 1/365 if daily */
                    
                    // computation of average t_GPP (per area) from the sum of GPP of each tree crown layer:
                    
                    // Farquhar is applied once per tree crown (at the top of the crown) (48 times per timestepifdef DAILIGHT, once per timestep if not), a pultiplier is net used to account for the decrease in photosynthetic rate with light decreae within the tree crown.
                    /* v.2.3.1 -- fast GPP calculation option. In addition, the daily computation of the Farquhar model is now the default option (_DAILYLIGHT is deprecated) */
   654301400 ->     if(_FASTGPP){
   654301400 ->         Fluxh(int(t_Tree_Height)+1);
   654301400 ->         t_GPP = (t_s->dailyGPPleaf(t_PPFD, t_VPD, t_T, t_dens, t_Crown_Depth));
   654301400 ->         t_Rday += tempRday;
   654301400 ->         tempRday=0.0;
                    }
                    else{
   654301400 ->         int crown_base=int(t_Tree_Height-t_Crown_Depth)+1; // for flux above crown base
   654301400 ->         int crown_top=int(t_Tree_Height)+1;                // for flux above crown top
                        
   654301400 ->         for(int h=crown_base; h<=crown_top; h++) {
   654301400 ->             Fluxh(h);
   654301400 ->             t_GPP+=t_s->dailyGPPleaf(t_PPFD, t_VPD, t_T, t_dens, t_Crown_Depth);
   654301400 ->             t_Rday+=tempRday;
   654301400 ->             tempRday=0.0;
                        }
   654301400 ->         float inb_layer=1.0/float(crown_top-crown_base+1);  // for averaging procedure
   654301400 ->         t_GPP   *=inb_layer;
   654301400 ->         t_Rday  *=inb_layer;
                    }
                    
                    /* Computation of GPP. New v.2.2: assumes an efficiency of 0.5 for young and old leaves vs. 1 for mature leaves */
                    //t_GPP*=(0.5*t_youngLA+t_matureLA+0.5*t_oldLA)*189.3*timestep;
                    
                    /* effLA is the scaling factor used for all fluxes new in v.2.3.0 */
   654301400 ->     float effLA=0.5*(t_leafarea+t_matureLA)*189.3*timestep;
                    
   654301400 ->     t_GPP*=effLA;
                    
                    /* new v.2.2. sapwood thickness (useful to compute stem respiration) */
   654301400 ->     float sapthick=0.04;
   654301400 ->     if (t_dbh < 0.08) sapthick=0.5*t_dbh;
                    
                    /* new v.2.2 stem respiration -- update lookup v230 */
   654301400 ->     int convT= int(iTaccuracy*temp); // temperature data at a resolution of Taccuracy=0.1°C -- stored in lookup tables ranging from 0°C to 50°C ---
   654301400 ->     int convTnight= int(iTaccuracy*tnight); // temperature data at a resolution of Taccuracy=0.1°C -- stored in lookup tables ranging from 0°C to 50°C ---
   654301400 ->     t_Rstem=sapthick*(t_dbh-sapthick)*(t_Tree_Height-t_Crown_Depth)*LookUp_Rstem[convT];
   654301400 ->     t_Rday *= effLA*0.40;
   654301400 ->     t_Rnight=(t_s->s_Rdark)*effLA*LookUp_Rnight[convTnight];
                    
   654301400 ->     t_NPP = 0.75*(t_GPP - 1.5*(t_Rday+t_Rnight+t_Rstem));
                    /* Rleaf=Rday+Rnight is multiplied by 1.5 to also account for fine root respiration (cf as in Fyllas et al 2014 and Malhi 2012); Rstem is multiplied by 1.5 to account for coarse root respiration (according to the shoot root biomass ratio of 0.2 - Jérôme's paper in prep- and also to branch respiration (Meir & Grace 2002, Cavaleri 2006, Asao 2005). */
                    
   654301400 ->     if(t_NPP<0.0){
   654301400 ->         t_NPPneg++;
   654301400 ->         t_NPP=0.0;
                        /* v.2.3.0 -- Line of code below was odd. If NPP <0.0, then to ensure C balance it should be simply reset to NPP=0 at this stage */
                        //t_NPP=t_GPP - 1.5*(t_Rday+t_Rnight+t_Rstem); REMOVED AS OF v.2.3.0.a4
                    }
                    else {
   654301400 ->         t_NPPneg=0;
                        /**** NPP allocation to wood and tree size increment *****/
   654301400 ->         UpdateTreeBiometry();
                    }
                    
                    /**** NPP allocation to leaves *****/
   654301400 ->     UpdateLeafDynamics();
                    
                    /* Output for control purposes */
                    
                #ifdef BEWARE_OF_PARAMETERIZED_OUTPUTS
                    // option below (FF v 2.3.1 may not work for some choices of timesteps
                #endif
                    
   654301400 ->     if(!_OUTPUT_reduced){
   654301400 ->         if (iter == 2) OutputTreeStandard(output[28]);
   654301400 ->         if (iter == int(nbiter/2)) OutputTreeStandard(output[29]);
   654301400 ->         if (iter == int(nbiter-1)) OutputTreeStandard(output[30]);
                        
   654301400 ->         if (t_site==2500) OutputTreeStandard(output[11]);
   654301400 ->         if (t_site==10380) OutputTreeStandard(output[12]);
   654301400 ->         if (t_site==100950) OutputTreeStandard(output[13]);
   654301400 ->         if (t_site==12090) OutputTreeStandard(output[14]);
   654301400 ->         if (t_site==120090) OutputTreeStandard(output[15]);
   654301400 ->         if (t_site==150667) OutputTreeStandard(output[16]);
                    }
   654301400 -> }
                
                /*####################################################
                 ####       Leaf dynamics and C allocation        ####
                 ####         called by Tree::Growth              ####
                 #####################################################*/
                
   654301400 -> void Tree::UpdateLeafDynamics() {
                    
                    // make a standalone function for leaf dynamics & litter?
                    
                    /**** NPP allocation to leaves *****/                                       /* rk: in this current scheme of leaf demography and phenology in three leaf age classes: only the old leaves generate treefall, and the dynamic of leaves cycle is generated by the dynamic of NPP, with a total leaf biomass varying - as opposed to De Weirdt et al 2012 in ORCHIDEE, but as in Wu et al 2016 but importantly without prescribing litterfall- */
                    
   654301400 ->     float flush=2.0*t_NPP*falloccanopy*0.68/(t_s->s_LMA);                           /* this is to convert the NPP allocated to leaves (falloccanopy is the fraction of biomass assumed to be alloacted to canopy (leaves+reproductive organs+twigs) at each timestep - Malhi et al 2011-, 68% of which is allocated to leaves - chave et al 2008, Chave et al 2010-), in new leaf area (2 is to convert carbon mass in biomass and LMA to convert leaf biomass into leaf area).*/
                    
                    /* litter module */
                    
                    
   654301400 ->     t_litter=t_oldLA/(t_s->s_time_old);
                    
                    /* leaf cycle */
                    
   654301400 ->     float new_mature = t_youngLA/(t_s->s_time_young);
   654301400 ->     float new_old    = t_matureLA/(t_s->s_time_mature);
   654301400 ->     t_youngLA  += flush - new_mature;
   654301400 ->     t_matureLA += new_mature - new_old;
   654301400 ->     t_oldLA    += new_old - t_litter;
   654301400 ->     t_leafarea  = t_youngLA + t_matureLA + t_oldLA;
                    
                    /* update t_dens */
                    
   654301400 ->     t_litter*=t_s->s_LMA;
                    
   654301400 ->     float crownvolume=PI*t_Crown_Radius*LH*t_Crown_Radius*LH*t_Crown_Depth*LV;
   654301400 ->     t_dens=t_leafarea/crownvolume;
                    
   654301400 -> }
                
   213506447 -> void Tree::UpdateTreeBiometry(){
                    /* New standalone function in v.2.3.0 */
                    
                    /* Tree dbh increment */
   213506447 ->     t_ddbh=0.0;
   213506447 ->     float volume=2.0*t_NPP/(t_s->s_wsg) * fallocwood * 1.0e-6;
   213506447 ->     if (t_dbh>t_dbh_thresh) volume*=flor(3.0-2.0*t_dbh/t_dbh_thresh);
                    
                    /* volume in m^3: the first factor of 2 is to convert C into biomass. the 1/s_wsg to convert biomass into volume. the 1e-6 term converts cm^3 into m^3 (the sole metric unit in the model). fallocwood is the fraction of biomass allocated to aboveground wood (stem + branches) growth. For the time being, we shall assume that a fixed proportion of NPP is allocated into AGB production. Currently, 0.20=%biomasse allocated to stem increment could be a global variable, even though this % allocation could in fact vary with resouce variation/co-limitation*/
                    
                    /* taking into account wood elements recycling (ex. fallen branches etc...) */
                    //t_ddbh = flor( volume* 4.0/( 3.0*PI*t_dbh*LH*t_Tree_Height*LV ) )* NH;
   213506447 ->     t_ddbh = flor( volume/(0.559*t_dbh*LH*t_Tree_Height*LV*(3.0-t_dbh/(t_dbh+t_s->s_ah))) )* NH;
                    
                    /* With V=pi*r^2*h, increment of volume = dV = 2*pi*r*h*dr + pi*r^2*dh */
                    /* With isometric growth assumption (ddbh/dbh=dh/h)and dbh=2*r: dV=3/4*pi*dbh*h*ddbh, ddbh in m, it follows: ddbh = 4/3 * V = 4/3 * 1/(pi*dbh*h)   */
                    
   213506447 ->     t_dbh += t_ddbh;
                    
                    /* update of tree height */
                    /* alternative calculation in concordance with isometric growth assumption: dh = h*ddbh/dbh */
                    /* t_Tree_Height += t_Tree_Height*t_ddbh/t_dbh; */
                    
   213506447 ->     t_Tree_Height = t_hmax * t_dbh/(t_dbh + (t_s->s_ah));
                    
                    /* update of tree crown depth -- allometry deduced from Piste Saint-Elie dataset */
   213506447 ->     if (t_Tree_Height<5.0) t_Crown_Depth = 0.17 + 0.13*t_Tree_Height;
   213506447 ->     else t_Crown_Depth = -0.48+0.26*t_Tree_Height;
                    /*t_Crown_Depth=exp(-1.169+1.098*log(t_Tree_Height));
                     29/04/15: try with allometry used in Fyllas et al 2014 (see SI, from Poorter et al 2006)*/
                    
   213506447 ->     t_Crown_Radius  = 0.80+10.47*t_dbh-3.33*t_dbh*t_dbh;
                    // allometry deduced from Piste Saint-Elie dataset
                    //t_Crown_Radius=sqrt(iPi*exp(-1.853+1.888*log(t_Tree_Height)));
                    // 29/04/15: try with allometry used in Fyllas et al 2014 (see SI, from Poorter et al 2006)
   213506447 -> }
                
                
                /*####################################################
                 ####           Death of the tree                ####
                 ####         called by Tree::Update             ####
                 ####################################################*/
                
    27001915 -> void Tree::Death() {
                    
    27001915 ->     t_age=0;
                    // remove this tree index from T_alive
                    //T_alive.remove(t_site);
                
    27001915 ->     t_dbh = t_Tree_Height = t_Crown_Radius = t_Crown_Depth= 0.0;
    27001915 ->     t_hurt = 0;
    27001915 ->     if(_TREEFALL){
    27001915 ->         t_angle = 0.;
    27001915 ->         t_C = t_Ct = 0;
                    }
    27001915 ->     if ((t_s->s_nbind)>0) (t_s->s_nbind)--;
    27001915 ->     nblivetrees--;
    27001915 ->     t_s = NULL;
                    
    27001915 -> }
                
                
                /*#################################
                 ####      Seed dispersal      ####
                 ####  called by UpdateField   ####
                 #################################*/
                
   654185552 -> void Tree::DisperseSeed(){
                    /* New v.2.0 reproduction can only occur for trees that receive enough
                     light (twice the LCP) */
                    /* New v.2.1 threshold of maturity is defined as a size threshold
                     (and not age as before), following Wright et al 2005 JTE */
   654185552 ->     if((t_dbh>=t_dbhmature)&&(t_PPFD>2.0*(t_s->s_LCP))) {
                        float rho,theta_angle;
   654185552 ->         int nbs=0;
   654185552 ->         if(_SEEDTRADEOFF){
   654185552 ->             nbs=int(t_NPP*2.0*falloccanopy*0.08*0.5*(t_s->s_iseedmass)*0.05);    /* nbs is the number of seeds produced at this time step; it is computed from the NPP (in g) allocated to reproductive organs -fruits and seeds-, *2 is to convert in biomass,  * 0.40 is to obtain the NPP allocated to canopy (often measured as litterfall), drawn from Malhi et al 2011 Phil. trans roy. Soc. and 0.08 is the part of litterfall corresponding the fruits+seeds, drawn from Chave et al 2008 JTE; assumed to be twice the biomass dedicated to seeds only (ie without fruits), and then divided by the mass of a seed to obtain the number of seeds */
                            //nbs=(int)nbs;
                        }
   654185552 ->         else nbs=nbs0;
                        //else nbs=int(t_NPP*2*falloccanopy*0.08*0.5); /* test 17/01/2017: use a factor to translate NPP into seeds produced, but not species specific, not linked to mass of grains */
                        
   654185552 ->         for(int ii=0;ii<nbs;ii++){                                                 /* Loop over number of produced seeds */
                            
   654185552 ->             rho = 2.0*((t_s->s_ds)+t_Crown_Radius)*float(sqrt(fabs(log(genrand2()*iPi))));    /* Dispersal distance rho: P(rho) = rho*exp(-rho^2) */
   654185552 ->             theta_angle = float(twoPi*genrand2());                                                /* Dispersal angle theta */
   654185552 ->             t_s->FillSeed(flor(int(rho*cos(theta_angle))+t_site%cols), /* column */               /* Update of field s_Seed */
   654185552 ->                           flor(int(rho*sin(theta_angle))+t_site/cols));      /* line */
                            
                        }
                    }
                    
   654185552 -> }
                //#endif
                
                
                /*##################################
                 ####   Tree death and growth   ####
                 ####   called by UpdateTree    ####
                 ##################################*/
                
   960000000 -> void Tree::Update() {
                    
                    int death;
                    
   960000000 ->     if(t_age) {
                        
   960000000 ->         if(_NDD)
   960000000 ->             death = int(genrand2()+t_s->DeathRateNDD(t_PPFD, t_dbh,t_NPPneg, t_NDDfield[t_sp_lab]));
                        else
   960000000 ->             death = int(genrand2()+t_s->DeathRate(t_PPFD, t_dbh, t_NPPneg));
                        
   960000000 ->         if(death){
                            /* Natural death caused by unsustained photosynthesis and density dependance */
   960000000 ->             nbdead_n1++;
                            /* Increments number of deaths */
   960000000 ->             if(t_dbh*LH>0.1) nbdead_n10++;
                            /* same but only for trees > 10cm */
                            /* New v.2.2. new outputs */
   960000000 ->             if(!_OUTPUT_reduced) {
   960000000 ->                 if(iter == 2) output[23] << "N\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
   960000000 ->                 if(iter == int(nbiter/2)) output[24]<< "N\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
   960000000 ->                 if(iter == int(nbiter-1)) output[25]<< "N\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
                            }
   960000000 ->             Death();
                        }
   960000000 ->         else if(_BASICTREEFALL && t_Tree_Height<2*t_hurt*genrand2()) {          // given probability of death is 1-0.5*t_Tree_Height/t_hurt
                            /* Death caused by a treefall (t_hurt) */
   960000000 ->             nbdead_c1++;   /* Increments number of treefalls */
   960000000 ->             if(t_dbh*LH>0.1) nbdead_c10++;/* same but only for trees > 10cm */
   960000000 ->             if(!_OUTPUT_reduced){
   960000000 ->                 if(iter == 2) output[23] << "OT\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
   960000000 ->                 if(iter == int(nbiter/2)) output[24]<< "OT\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
   960000000 ->                 if(iter == int(nbiter-1)) output[25]<< "OT\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
                            }
   960000000 ->             Death();
                        }
                        else {/* If no death, then growth */
   960000000 ->             t_hurt = 0;
   960000000 ->             Growth();
                        }
                    }
   960000000 -> }
                
                
                /*##################################
                 ####           Treefall         ####
                 #### called by UpdateTreefall   ####
                 ####################################*/
                
                
   654301400 -> void Tree::FallTree() {
                    int xx,yy;
                    //if(_TREEFALL)
                    //if(Couple()>t_Ct) { /* above a given stress threshold the tree falls */
                    
   654301400 ->     if(genrand2()*t_Tree_Height > t_Ct){
                        // given: probability of treefall = 1-t_Ct/t_Tree_Height
   654301400 ->         float t_angle = float(twoPi*genrand2());
                        // random angle
                        int row0,col0,h_int, r_int;
   654301400 ->         float h_true = t_Tree_Height*LV;
   654301400 ->         nbTreefall1++;
   654301400 ->         if(t_dbh*LH>0.1) nbTreefall10++;
   654301400 ->         Thurt[0][t_site+sites] = int(t_Tree_Height);
                        // Thurt[0] saves the integer tree height, here exactly at the place where the tree fell...
   654301400 ->         row0=t_site/cols;       /* fallen stem destructs other trees */
   654301400 ->         col0=t_site%cols;
   654301400 ->         h_int = int(h_true*NH);
   654301400 ->         for(int h=1;h<h_int;h++) {
                            // loop on the fallen stem (horizontally)
   654301400 ->             xx=int(flor(col0+h*cos(t_angle)));
                            // get projection in col (= xx) direction, where xx is absolute location
   654301400 ->             if(xx<cols){
   654301400 ->                 yy=   int(row0+h*sin(t_angle));
                                // get projection in row (= yy) direction, where yy is absolute location
   654301400 ->                 Thurt[0][xx+(yy+rows)*cols] = int(t_Tree_Height);                           // Thurt[0] where the stem fell, calculation: xx+(yy+rows)*cols= xx + yy*cols + rows*cols = xx + yy*cols + sites
                            }
                        }
   654301400 ->         xx=col0+int((h_true*NH-t_Crown_Radius)*cos(t_angle));
                        // where crown ends/starts
                        /* fallen crown destructs other trees */
   654301400 ->         yy=row0+int((h_true*NH-t_Crown_Radius)*sin(t_angle));
   654301400 ->         r_int = int(t_Crown_Radius);
   654301400 ->         for(int col=max(0,xx-r_int);col<min(cols,xx+r_int+1);col++) {
                            /* loop on the fallen crown (horizontally) */
   654301400 ->             for(int row=yy-r_int;row<yy+r_int+1;row++) {
   654301400 ->                 if((col-xx)*(col-xx)+(row-yy)*(row-yy)<r_int*r_int) Thurt[0][col+(row+rows)*cols] = int((t_Tree_Height-t_Crown_Radius*NV*LH)*0.5);
                            }
                        }
   654301400 ->         if(iter == 2) output[23] << "T\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
   654301400 ->         if(iter == int(nbiter/2)) output[24]<< "T\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
   654301400 ->         if(iter == int(nbiter-1)) output[25]<< "T\t" << t_sp_lab << "\t" << t_dbh << "\t" << t_age << "\t" << t_Tree_Height <<  "\n";
   654301400 ->         Death();
                    }
                    //}
   654301400 -> }
                
       ##### -> int Tree::Couple() {
                    int site2,quadist,haut0,xx,yy, radius_int,h_int;
                    float fx, fy,temp,lai;
       ##### ->     radius_int = int(t_Crown_Radius);
       ##### ->     h_int = int(t_Tree_Height);
       ##### ->     haut0 = int(t_Tree_Height-t_Crown_Depth);
       ##### ->     if(radius_int){
                        int row0,col0;
       ##### ->         row0=t_site/cols;
       ##### ->         col0=t_site%cols;
       ##### ->         fx = fy = 0.0;
       ##### ->         for(int col=max(0,col0-radius_int);col<min(cols,col0+radius_int+1);col++) {
       ##### ->             for(int row=row0-radius_int;row<=row0+radius_int;row++) {
       ##### ->                 xx=col0-col;
       ##### ->                 yy=row0-row;
       ##### ->                 quadist = xx*xx+yy*yy;
       ##### ->                 if((quadist<=radius_int*radius_int)&&quadist) {
                                    //site2 = col+cols*(row+RMAX); //modif 23/03/2011
       ##### ->                     site2 = col+cols*row+SBORD;
       ##### ->                     for(int h=haut0;h<=h_int;h++) {
       ##### ->                         if(h_int<HEIGHT) lai = LAI3D[h_int][site2]-LAI3D[h_int+1][site2];
       ##### ->                         else  lai = LAI3D[h_int][site2];
       ##### ->                         if(lai>dens) { // needs to be changed when TREEFALL is revised
       ##### ->                             temp = 1.0/sqrt(float(quadist));
       ##### ->                             if(temp>0.0) {
       ##### ->                                 fx += float(xx)*temp;
       ##### ->                                 fy += float(yy)*temp;
                                            }
                                        }
                                    }
                                }
                            }
                        }
       ##### ->         t_C = int(sqrt(fx*fx+fy*fy)*t_Tree_Height);
       ##### ->         if(fx!=0.0) t_angle=atan2(fy,fx);
       ##### ->         else t_angle = Pis2*sgn(fy);
                    }
       ##### ->     else{t_C = 0; t_angle = 0.0; }
       ##### ->     return t_C;
       ##### -> }
                
                
                
                /*#####################################################
                 ####      For Average and OutputField             ####
                 ######################################################*/
                
   960000000 -> void Tree::Average() {
   960000000 ->     if(t_age>0) {
   960000000 ->         if(t_dbh*LH >= 0.1) {
   960000000 ->             (t_s->s_output_field[1])++;
   960000000 ->             t_s->s_output_field[6] += t_dbh*LH*t_dbh*LH;
                        }
   960000000 ->         if(t_dbh*LH >= 0.3) (t_s->s_output_field[2])++;
   960000000 ->         t_s->s_output_field[3] += t_dbh*LH*t_dbh*LH;
   960000000 ->         t_s->s_output_field[4] += t_NPP*1.0e-6;
   960000000 ->         t_s->s_output_field[5] += t_GPP*1.0e-6;
   960000000 ->         t_s->s_output_field[7] += 0.0673*pow(t_s->s_wsg*t_Tree_Height*LV*t_dbh*t_dbh*LH*LH*10000, 0.976);  // this is the allometrtic equ 4 in Chave et al. 2014 Global Change Biology to compute above ground biomass
   960000000 ->         t_s->s_output_field[8] += t_Rday*1.0e-6;
   960000000 ->         t_s->s_output_field[9] += t_Rnight*1.0e-6;
   960000000 ->         t_s->s_output_field[10] += t_Rstem*1.0e-6;
   960000000 ->         t_s->s_output_field[11] += t_litter*1.0e-6;
                        
                    }
   960000000 -> }
                
      640000 -> void Tree::histdbh() {
      640000 ->     if(t_age) nbdbh[int(100.*t_dbh*LH)]++;
                    // compute the diameter distribution density
                    // where dbh is in cm (it is in number of horizontal cells throughout the code)
                    // values are always rounded down (so nbdbh[30] gives you trees with more than 30 cm dbh, and less than 31))
      640000 -> }
                
                
                /*#####################################################
                 ####      User Output for Control Purposes        ####
                 ######################################################*/
                
                
       ##### -> void Tree::OutputTreeStandard(fstream& output){
       ##### ->     output << iter << "\t" << t_site << "\t" << t_sp_lab << "\t" << t_Tree_Height << "\t" << t_dbh << "\t"  << t_ddbh << "\t" << t_litter << "\t" << t_age << "\t" << t_leafarea << "\t" << t_youngLA<< "\t" << t_matureLA << "\t" << t_oldLA << "\t" << t_Crown_Radius << "\t" << t_Crown_Depth << "\t" << t_dens  <<  "\t" << t_PPFD  <<"\t" << t_GPP  <<"\t" << t_NPP <<"\t" << t_Rstem <<"\t" << t_Rday  <<"\t" << t_Rnight << "\t" << t_site << "\t" << LAI3D[int(t_Tree_Height)][t_site+SBORD] << "\t" << LAI3D[int(t_Tree_Height-t_Crown_Depth)+1][t_site+SBORD] << endl;
       ##### -> }
                
       ##### -> void Tree::OutputTreeStandard(){
       ##### ->     cout << iter << "\t" << t_site << "\t" << t_sp_lab << "\t" << t_Tree_Height << "\t" << t_dbh << "\t"  << t_ddbh << "\t" << t_litter << "\t" << t_age << "\t" << t_leafarea << "\t" << t_youngLA<< "\t" << t_matureLA << "\t" << t_oldLA << "\t" << t_Crown_Radius << "\t" << t_Crown_Depth << "\t" << t_dens  <<  "\t" << t_PPFD  <<"\t" << t_GPP  <<"\t" << t_NPP <<"\t" << t_Rstem <<"\t" << t_Rday  <<"\t" << t_Rnight << "\t" << t_site << "\t" << LAI3D[int(t_Tree_Height)][t_site+SBORD] << "\t" << LAI3D[int(t_Tree_Height-t_Crown_Depth)+1][t_site+SBORD] << endl;
       ##### -> }
                
                
                /* Class objects */
                
                Species *S=NULL;
                Tree *T=NULL;
                
                
                /*############################################
                 ############################################
                 ############     MAIN PROGRAM    ###########
                 ############################################
                 ############################################*/
                
                //int main(int argc,char *argv[]) {
                
       ##### -> int main(){
                    
                    /***********************/
                    /*** Initializations ***/
                    /***********************/
                #ifdef MPI   /* Lookup processor number / total number of processors */
                    MPI_Init(&argc,&argv);
                    MPI_Comm_rank(MPI_COMM_WORLD,&p_rank);
                    MPI_Comm_size(MPI_COMM_WORLD,&size);
                #else
       ##### ->     mpi_rank = 0;
       ##### ->     mpi_size = 1;
                #endif
                #ifdef easyMPI
                    MPI::Init();
                    easympi_rank = MPI::COMM_WORLD.Get_rank();
                    easympi_size = MPI::COMM_WORLD.Get_size();
                    //MPI_Get_library_version(version, &len);
                    //std::cout << "Hello, world!  I am " << rank << " of " << size << "(" << version << ", " << len << ")" << std::endl;
                    //cout<< "Hello, world!  I am " << easympi_rank << " of " << easympi_size<<endl;
                #else
       ##### ->     easympi_rank = 0;
       ##### ->     easympi_size =1;
                #endif
                    
                    
                #ifdef DCELL
                    // Stuff for constant number generator
                    const gsl_rng_type *Trandgsl;
                    gsl_rng_env_setup();
                    Trandgsl = gsl_rng_default;
                    gslrand = gsl_rng_alloc (Trandgsl);
                #endif
                    /*
                    for(int argn=1;argn<argc;argn++){ // Arguments of the input and output files 
                        if(*argv[argn] == '-'){
                            switch(*(argv[argn]+1)){
                                case 'i':
                                    bufi = argv[argn]+2;
                                    break;
                                case 'o':
                                    buf = argv[argn]+2;
                                    break;
                                case 'f':                      // new v.2.3: initialisation from field, 'f' for "forest", "field data" 
                                    bufi_data = argv[argn]+2;
                                    break;
                                case 'n':
                                    easympi_rank=atoi(argv[argn]+2); // new v.2.2 
                            }
                        } 
                    }*/
                  
       ##### ->     cout<< easympi_rank;
       ##### ->     int t=(int) time(NULL);
       ##### ->     int seed =3*t+2*(easympi_rank+1)+1;
       ##### ->     sgenrand2i(seed);
       ##### ->     sgenrand2(seed);
       ##### ->     cout<< "On proc #" << easympi_rank << " seed: " << seed <<  " rng: "<< genrand2() << endl;
       ##### ->     cout << genrand2()<< endl;
       ##### ->     cout << genrand2()<< endl;
                    
                    // input files
                
                    //sprintf(inputfile,"%s",bufi);
       ##### ->     sprintf(inputfile, "%s", "input_file_v231.txt");
                    //sprintf(buf, "%s", "output");
                    
                
       ##### ->     if(_FromData){
       ##### ->         sprintf(inputfile_data,"%s",bufi_data);
                    }
                    //in this version of the code, the code user is expected to use the input txt file name with its extension name, as eg. "input.txt", when setting the program's argument
                    //sprintf(inputfile,"%s.txt",bufi);
                    
       ##### ->     if(!_OUTPUT_reduced)
                    {
       ##### ->         sprintf(outputinfo,"%s_%i_par.txt",buf, easympi_rank);                     /* Files with general output info */
       ##### ->         cout<< "On proc #" << easympi_rank << " seed: " << seed <<  " rng: "<< genrand2() <<  endl;
       ##### ->         out.open(outputinfo, ios::out);
       ##### ->         if(!out) cerr<< "ERROR with par file"<< endl;
       ##### ->         sprintf(outputinfo,"%s_%i_info.txt",buf, easympi_rank);
       ##### ->         out2.open(outputinfo, ios::out);
       ##### ->         if(!out2) cerr<< "ERROR with info file"<< endl;
                    }
       ##### ->     Initialise();           /* Read global parameters */
                    
       ##### ->     AllocMem();             /* Memory allocation */
                    
       ##### ->     if(_FromData){
       ##### ->         InitialiseFromData();   /* Initial configuration of the forest, read from data */
                    }
                    
       ##### ->     BirthInit();            /* Initial configuration of the forest */
       ##### ->     out.close();
                    
       ##### ->     cout << "klight is: " << klight << endl;
       ##### ->     cout << "CO2 concentration is: " << Cair << endl;
                    
                    /***********************/
                    /*** Evolution loop  ***/
                    /***********************/
                    
       ##### ->     double start_time,stop_time, duration=0.0;           /* for simulation duration */
       ##### ->     stop_time = clock();
       ##### ->     for(iter=0;iter<nbiter;iter++) {
       ##### ->         start_time = stop_time;
                        
       ##### ->         Evolution();
       ##### ->         stop_time = clock();
       ##### ->         duration +=flor(stop_time-start_time);
                        
                        /****** Output for 100 year analysis ******/
                        
       ##### ->         if(_OUTPUT_last100 && nbiter>100 && iter > (nbiter-101)) OutputSnapshotDetail(output[33]);  // 100 years development
                        
                        /****** Final Outputs ******/
                        
       ##### ->         if(iter == nbiter-2){
       ##### ->             OutputSnapshot(output[10]);                         // Final Pattern
                            
                            
       ##### ->             if(!_OUTPUT_reduced){
       ##### ->                 OutputSnapshot(output[10]);                         // Final Pattern
       ##### ->                 OutputSpeciesParameters(output[18]);
                            }
       ##### ->             if(_OUTPUT_fullLAI){
       ##### ->                 OutputFullLAI(output[36],output[37]);               // CHM and LAD patterns
                            }
                        }
                    }
                    
                    /*************************/
                    /*** End of simulation ***/
                    /*************************/
                    
       ##### ->     float durf = duration/double(CLOCKS_PER_SEC);        /* output of the effective CPU time */
                #ifdef MPI
                    MPI_Reduce(&durf,&durf,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
                #endif
       ##### ->     if(!mpi_rank) {
       ##### ->         cout << "\n";
                #ifdef MPI
                        out2 << "Number of processors : "<< mpi_size << "\n";
                #endif
       ##### ->         out2 << "Average computation time : "<< durf/float(mpi_size) << " seconds.\n";
       ##### ->         out2 << "End of simulation.\n";
       ##### ->         cout << "\nNumber of processors : "<< mpi_size << "\n";
       ##### ->         cout << "Average computation time : "<< durf/float(mpi_size) << " seconds.\n";
       ##### ->         cout << "End of simulation.\n";
                    }
       ##### ->     out2.close();
                    
                    /*Free dynamic memory */ /* added in oct2013 */
       ##### ->     FreeMem();
                    
                #ifdef easyMPI
                    MPI::Finalize();
                #endif
                    
       ##### ->     exit(1);
                }
                
                
                /*###########################################
                 ############################################
                 #######  Initialization routines    ########
                 ############################################
                 ############################################*/
                
           1 -> void Initialise() {
                    
                    int ligne;
                    
           1 ->     fstream In(inputfile, ios::in);
                    
                    /*** Initialization of the simulation parametres ***/
                    /***************************************************/
                    
           1 ->     if (In) {
           1 ->         for(ligne=0;ligne<4;ligne++) In.getline(buffer,128,'\n');
                        
                        /*General parameters */
           1 ->         In >> cols; In.getline(buffer,128,'\n');
           1 ->         In >> rows; In.getline(buffer,128,'\n');
           1 ->         sites = rows*cols;
                        //S_has_seed_on_site = list<int>[sites];
                #ifdef DCELL
                        In >> length_dcell; In.getline(buffer,128,'\n');
                        sites_per_dcell = length_dcell*length_dcell;
                        nbdcells = int(sites/sites_per_dcell);
                        linear_nb_dcells = int(cols/length_dcell);
                        cerr << "Number of dcells" << nbdcells << endl;
                        cerr << "Lin number of dcells" << linear_nb_dcells << endl;
                #endif
           1 ->         In >> nbiter; In.getline(buffer,128,'\n');
           1 ->         In >> iterperyear; In.getline(buffer,128,'\n');
           1 ->         timestep=1.0/float(iterperyear);
           1 ->         cerr << "iterperyear " << iterperyear << endl;
           1 ->         In >> NV; In.getline(buffer,128,'\n');
           1 ->         In >> NH; In.getline(buffer,128,'\n');
           1 ->         LV = 1.0/NV;
           1 ->         LH = 1.0/NH;
           1 ->         In >> nbout; In.getline(buffer,128,'\n');
           1 ->         if(nbout) freqout = nbiter/nbout;
           1 ->         In >> numesp; In.getline(buffer,128,'\n');
           1 ->         In >> p_nonvert; In.getline(buffer,128,'\n');
           1 ->         for (int i=0; i<=23; i++) In >> daily_light[i];
           1 ->         In.getline(buffer,128,'\n');
           1 ->         for (int i=0; i<=23; i++) In >> daily_vpd[i];
           1 ->         In.getline(buffer,128,'\n');
           1 ->         for (int i=0; i<=23; i++) In >> daily_T[i];
           1 ->         In.getline(buffer,128,'\n');
           1 ->         In.getline(buffer,128,'\n');
                        
                        /*Characters shared by species */
           1 ->         In >> klight; In.getline(buffer,128,'\n');
           1 ->         theta = 0.70; /* v.2.3.0 This could be added in the input file, just like klight */
           1 ->         halfDividedByTheta = 0.5 / theta;
           1 ->         In >> phi; In.getline(buffer,128,'\n');
           1 ->         In >> g1; In.getline(buffer,128,'\n');
           1 ->         In >> vC; In.getline(buffer,128,'\n');
           1 ->         In >> DBH0; In.getline(buffer,128,'\n');
           1 ->         In >> H0; In.getline(buffer,128,'\n');
           1 ->         In >> ra0; In.getline(buffer,128,'\n');
           1 ->         In >> ra1; In.getline(buffer,128,'\n');
           1 ->         In >> de0; In.getline(buffer,128,'\n');
           1 ->         In >> de1; In.getline(buffer,128,'\n');
           1 ->         In >> dens; In.getline(buffer,128,'\n');
           1 ->         In >> fallocwood; In.getline(buffer,128,'\n');
           1 ->         In >> falloccanopy; In.getline(buffer,128,'\n');
           1 ->         In >> Cseedrain; In.getline(buffer,128,'\n');
           1 ->         In >> nbs0; In.getline(buffer,128,'\n');
           1 ->         In >> m; In.getline(buffer,128,'\n');
           1 ->         In >> m1; In.getline(buffer,128,'\n');
           1 ->         In >> Cair; In.getline(buffer,128,'\n');
           1 ->         iCair = 1.0/Cair;
           1 ->         if (_NDD) {
           1 ->             In >> R; In.getline(buffer,128,'\n');
           1 ->             In >> deltaR; In.getline(buffer,128,'\n');
           1 ->             In >> deltaD; In.getline(buffer,128,'\n');
                        }
                        
           1 ->         DBH0 *= NH;
           1 ->         H0   *= NV;
           1 ->         ra0  *= NH;
           1 ->         de0  *= NV;
           1 ->         alpha = 4.0*phi;
                        /* apparent quantum yield to electron transport in mol e-/mol photons */
                        // see Mercado et al 2009 , the conversion of the apparent quantum yield in micromolCO2/micromol quantum into micromol e-/micxromol quantum is done by multipliyng by 4, since four electrons are needed to regenerate RuBP.
                        /* alpha is fixed at 0.3 mol e-/mol photons in Medlyn et al 2002
                         but see equ8 and Appendix 1 in Farquahr et al 1980: it seems that alpha should vary with leaf thickness: there is a fraction of incident light which is lost by absorption by other leaf parts than the chloroplast lamellae, and this fraction f may increase with leaf thickness.
                         With the values of the paper: alpha= 0.5*(1-f)=0.5*(1-0.23)=0.385, but this is a theoretical value and observations often report lower values (see ex discussion in medlyn et al 2005 Tree phsyiology, Lore Veeryckt values, Mercado et al 2009 Table 10, Domingues et al. 2014)*/
                    }
                    
                    else {
           1 ->         cout<< "ERROR with the input file of parameters" << endl;
                    }
                    
                    
                    /*** Information in file info ***/
                    /***********************************/
                    
           1 ->     if(!mpi_rank){
           1 ->         out2 << "\nTROLL simulator\n\n";
           1 ->         out2 << "\n   2D discrete network: horizontal step = " << LH
           1 ->         << " m, one tree per "<< LH*LH << " m^2 \n\n";
           1 ->         out2 << "\n   Tree : (t_dbh,t_Tree_Height,t_Crown_Radius,t_Crown_Depth) \n\n";
           1 ->         out2 << "\n            + one species label \n\n";
           1 ->         out2 << " Number of sites      : "<<rows<<"x"<<cols<<"\n";
           1 ->         out2 << " Number of iterations : "<<nbiter<<"\n";
           1 ->         out2 << " Duration of timestep : "<<timestep<<" years\n";
           1 ->         out2 << " Number of Species    : "<<numesp << "\n\n";
           1 ->         out2.flush();
                    }
                    
                    
                    /*** Initialization of trees ***/
                    /*******************************/
                    
           1 ->     if(NULL==(T=new Tree[sites])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc Tree" << endl;
                    }
                    
           1 ->     if(_NDD){
           1 ->         for(int site=0;site<sites;site++) {
           1 ->             if (NULL==(T[site].t_NDDfield = new float[numesp+1])) cerr<<"!!! Mem_Alloc\n";
           1 ->             for(int ii=0;ii<(numesp+1);ii++) T[site].t_NDDfield[ii]=0;
                        }
                    }
                
                
                
                    /* NEW CHANGE: site_has_S */
           1 ->     seed_count = new int*[sites];
           1 ->     for (int i = 0; i < sites; ++ i ){
           1 ->         seed_count[i] = new int[numesp];
                    }
                    // fill up seed_count with 0
           1 ->     for (int i = 0; i < sites; ++ i)
           1 ->         for (int j = 1; j <= numesp; ++j)
           1 ->             seed_count[i][j] = 0;
           1 ->     site_has_S = new L[sites];
                
                
                
                    /*** Initialization of species ***/
                    /*********************************/
                    
                    int sp;
           1 ->     if(NULL==(S=new Species[numesp+1])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc Species" << endl;
                    }
                
                
                
                
           1 ->     for(ligne=0;ligne<3;ligne++) In.getline(buffer,128,'\n');                           /* Read species parameters (ifstream In) */
           1 ->     for(sp=1;sp<=numesp;sp++) {
           1 ->         S[sp].Init(sp,In);
                    }
                
                
                    
                    /*** Initialization of environmental variables ***/
                    /*************************************************/
                    
           1 ->     In.getline(buffer,128,'\n');
           1 ->     In.getline(buffer,128,'\n');
           1 ->     In.getline(buffer,128,'\n');
                    
           1 ->     if(NULL==(Temperature=new float[iterperyear])) {                                // rk, the current structure of code suppose that environment is periodic (a period = a year), if one want to make climate vary, with interannual variation and climate change along the simulation, one just need to provide the full climate input of the whole simulation (ie number of columns=iter and not iterperyear) and change iterperyear by nbiter here.
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc Temperature" << endl;
                    }
                    
           1 ->     for (int i=0; i<iterperyear; i++) In >> Temperature[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "Temperature" << i << "\t"  << Temperature[i] <<  "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(DailyMaxTemperature=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc DailyMaxTemperature" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> DailyMaxTemperature[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "DailyMaxTemperature" << i << "\t"  << DailyMaxTemperature[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(NightTemperature=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc NightTemperature" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> NightTemperature[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "NightTemperature" << i << "\t"  << NightTemperature[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(Rainfall=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc Rainfall" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> Rainfall[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "Rainfall" << i << "\t"  << Rainfall[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(WindSpeed=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc WindSpeed" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> WindSpeed[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "WindSpeed" << i << "\t"  << WindSpeed[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(MaxIrradiance=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc Irradiance" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> MaxIrradiance[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "MaxIrradiance" << i << "\t"  << MaxIrradiance[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(MeanIrradiance=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc Irradiance" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> MeanIrradiance[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "MeanIrradiance" << i << "\t"  << MeanIrradiance[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(SaturatedVapourPressure=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc SaturatedVapourPressure" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> SaturatedVapourPressure[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "SaturatedVapourPressure" << i << "\t"  << SaturatedVapourPressure[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(VapourPressure=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc VapourPressure" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> VapourPressure[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "VapourPressure" << i << "\t"  << VapourPressure[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(VapourPressureDeficit=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc VapourPressureDeficit" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> VapourPressureDeficit[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "VapourPressureDeficit" << i << "\t"  << VapourPressureDeficit[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(DailyVapourPressureDeficit=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc DailyVapourPressureDeficit" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> DailyVapourPressureDeficit[i];
           1 ->     In.getline(buffer,128,'\n');
                    
                    //for (int i=0; i<iterperyear; i++) cout<< "DailyVapourPressureDeficit" << i << "\t"  << DailyVapourPressureDeficit[i] << "\t";
                    //cout<<endl;
                    
           1 ->     if(NULL==(DailyMaxVapourPressureDeficit=new float[iterperyear])) {
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->         cout<<"!!! Mem_Alloc DailyMaxVapourPressureDeficit" << endl;
                    }
           1 ->     for (int i=0; i<iterperyear; i++) In >> DailyMaxVapourPressureDeficit[i];
           1 ->     In.getline(buffer,128,'\n');
                
                    /* NEW CHANGE: take (liter % iterperyear) out to reduce repeated calculation of index */
           1 ->     int index = iter % iterperyear;
                
           1 ->     temp = Temperature[index];
           1 ->     tmax = DailyMaxTemperature[index];
           1 ->     tnight = NightTemperature[index];
           1 ->     precip = Rainfall[index];
           1 ->     WS = WindSpeed[index];
           1 ->     Wmax = MaxIrradiance[index] * 1.678;       // 1.678 is to convert irradiance from W/m2 to micromol of PAR /s /m2, the unit used in the FvCB model of photosynthesis
           1 ->     Wmean = MeanIrradiance[index];            // still in W/m2
           1 ->     e_s = SaturatedVapourPressure[index];
           1 ->     e_a = VapourPressure[index];
           1 ->     VPDbasic = VapourPressureDeficit[index];
           1 ->     VPDday = DailyVapourPressureDeficit[index];
           1 ->     VPDmax = DailyMaxVapourPressureDeficit[index];
                    
           1 ->     In.close();
                    /* Close ifstream In */
                    
           1 ->     nbTbins=500;
           1 ->     float Taccuracy=0.1;
           1 ->     iTaccuracy=1.0/Taccuracy;
           1 ->     cerr << "Built-in maximal temperature: " << float(nbTbins)*Taccuracy <<endl;
           1 ->     if(NULL==(LookUp_KmT=new float[nbTbins])) cerr<<"!!! Mem_Alloc LookUp_KmT" << endl;
           1 ->     if(NULL==(LookUp_GammaT=new float[nbTbins])) cerr<<"!!! Mem_Alloc LookUp_GammaT" << endl;
           1 ->     if(NULL==(LookUp_tempRday=new float[nbTbins])) cerr<<"!!! Mem_Alloc LookUp_tempRday" << endl;
           1 ->     if(NULL==(LookUp_VcmaxT=new float[nbTbins])) cerr<<"!!! Mem_Alloc LookUp_VcmaxT" << endl;
           1 ->     if(NULL==(LookUp_JmaxT=new float[nbTbins])) cerr<<"!!! Mem_Alloc LookUp_JmaxT" << endl;
           1 ->     if(NULL==(LookUp_Rstem=new float[nbTbins])) cerr<<"!!! Mem_Alloc LookUp_Rstem" << endl;
           1 ->     if(NULL==(LookUp_Rnight=new float[nbTbins])) cerr<<"!!! Mem_Alloc LookUp_Rnight" << endl;
           1 ->     for(int i=0;i<nbTbins;i++) { // loop over "T" in GPPleaf()
           1 ->         float temper=float(i)*Taccuracy;
           1 ->         LookUp_KmT[i] = 404.0*exp(((temper-25.0)/(298*0.00831*(273+temper)))*59.36)*
           1 ->         (1+210*1.0/248.0*exp(-(temper-25.0)/(298*0.00831*(273+temper))*35.94))*iCair;
           1 ->         LookUp_GammaT[i]=37.0*exp(((temper-25.0)/(298*0.00831*(273+temper)))*23.4)*iCair;
           1 ->         LookUp_tempRday[i]=exp((temper-25.0)*0.1*log(3.09-0.0215*(25.0+temper)));
           1 ->         LookUp_VcmaxT[i]=exp(26.35-65.33/(0.00831*(temper+273.15)));
           1 ->         LookUp_JmaxT[i]=exp(17.57-43.54/(0.00831*(temper+273.15)));
                        
           1 ->         LookUp_Rstem[i]=39.6*378.7*PI*timestep*exp((temper-25.0)/10.0*log(2.0));
           1 ->         LookUp_Rnight[i]=exp((temper-25.0)*0.1*log(3.09-0.0215*(25.0+temper)));
                        /* exp((temp-25)/10*log(2)) is the temperature dependency of Rstem, supposing a constant Q10=2, according to Ryan et al 1994 and Meir & Grace 2002
                         exp((tnight-25)*0.1*log(3.09-0.0215*(25+tnight))) is the temperature dependencies used by Atkin 2015 (equ1) */
                        
                        
                    }
                    
                    
           1 ->     if(NULL==(LookUp_flux=new float[400])) cerr<<"!!! Mem_Alloc LookUp_flux" << endl;
           1 ->     if(NULL==(LookUp_VPD=new float[400])) cerr<<"!!! Mem_Alloc LookUp_VPD" << endl;
           1 ->     if(NULL==(LookUp_T=new float[400])) cerr<<"!!! Mem_Alloc LookUp_T" << endl;
           1 ->     for(int i=0;i<400;i++) { // loop over "absorb" in Fluxh()
           1 ->         float absorbance=float(i)/20.0;
           1 ->         LookUp_flux[i]=exp(-klight*absorbance);
           1 ->         LookUp_VPD[i]= 0.25+sqrt(maxf(0.0 , 0.08035714*(7.0-absorbance)));
                        // this expressions results from fit of observations of relationships between VPD and height within dense canopy (HOBO data on COPAS tower, Shuttleworth et al 1985; Camargo & Kapos 1995 journal of Tropical Ecology)
           1 ->         LookUp_T[i] =  0.4285714*(minf(7.0,absorbance));
                        // 0.4285714=3/7, assuming deltaT between the top canopy and dense understorey is constant = 3°C, could be refined.
                        
                    }
                    
           1 ->     In.open(inputfile, ios::in);
           1 ->     if(!mpi_rank) {
           1 ->         do{
           1 ->             In.getline(buffer,256,'\n');
           1 ->             out << buffer <<endl;
           1 ->         }while (!In.eof()) ;
                    }
                    
           1 ->     In.close();
                    /* Close ifstream In */
                    
                    
                    
                    /*** Initialization of output streams ***/
                    /****************************************/
                    
                    
                    
                    char nnn[200];
           1 ->     if(!mpi_rank) {
           1 ->         if(_OUTPUT_reduced){
           1 ->             sprintf(nnn,"%s_%i_outputs.txt",buf, easympi_rank);
           1 ->             output[0].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_final_pattern.txt",buf, easympi_rank);
           1 ->             output[10].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_vertd.txt",buf, easympi_rank);
           1 ->             output[32].open(nnn,ios::out);
           1 ->             sprintf(nnn,"%s_%i_litterfall.txt",buf, easympi_rank);
           1 ->             output[27].open(nnn, ios::out);
                            //sprintf(nnn,"%s_%i_endstate.txt",buf, easympi_rank);
                            //output[30].open(nnn, ios::out);
                        }
                        else{
           1 ->             sprintf(nnn,"%s_%i_abund.txt",buf, easympi_rank);
           1 ->             output[0].open(nnn, ios::out);
           1 ->             if (!output[0]) {
           1 ->                 cout<< "ERROR with abund file"<< endl;
                            }
           1 ->             sprintf(nnn,"%s_%i_abu10.txt",buf, easympi_rank);
           1 ->             output[1].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_abu30.txt",buf, easympi_rank);
           1 ->             output[2].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_ba.txt",buf, easympi_rank);
           1 ->             output[3].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_npp.txt",buf, easympi_rank);
           1 ->             output[4].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_gpp.txt",buf, easympi_rank);
           1 ->             output[5].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_ba10.txt",buf, easympi_rank);
           1 ->             output[6].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_ppfd0.txt",buf, easympi_rank);
           1 ->             output[7].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_death.txt",buf, easympi_rank);
           1 ->             output[8].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_state.txt",buf, easympi_rank);
           1 ->             output[9].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_final_pattern.txt",buf, easympi_rank);
           1 ->             output[10].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_site1.txt",buf, easympi_rank);
                            
                            // used to be added to explore potential link with Belassen curve, could be suppressed, but maybe useful to have an idea of the magnitude and distribution of increment of dbh
                            
           1 ->             output[11].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_site2.txt",buf, easympi_rank);
           1 ->             output[12].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_site3.txt",buf, easympi_rank);
           1 ->             output[13].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_site4.txt",buf, easympi_rank);
           1 ->             output[14].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_site5.txt",buf, easympi_rank);
           1 ->             output[15].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_site6.txt",buf, easympi_rank);
           1 ->             output[16].open(nnn, ios::out);
                            
                            //output[17] for parameter space is valid both for reduced and standard output, defined below
                            
           1 ->             sprintf(nnn,"%s_%i_sp_par.txt",buf, easympi_rank);
           1 ->             output[18].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_agb.txt",buf, easympi_rank);
           1 ->             output[19].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_Rday.txt",buf, easympi_rank);
           1 ->             output[20].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_Rnight.txt",buf, easympi_rank);
           1 ->             output[21].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_Rstem.txt",buf, easympi_rank);
           1 ->             output[22].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_death1.txt",buf, easympi_rank);
           1 ->             output[23].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_death2.txt",buf, easympi_rank);
           1 ->             output[24].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_death3.txt",buf, easympi_rank);
           1 ->             output[25].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_deathrate.txt",buf, easympi_rank);
           1 ->             output[26].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_litterfall.txt",buf, easympi_rank);
           1 ->             output[27].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_leafdens1.txt",buf, easympi_rank);
           1 ->             output[28].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_leafdens2.txt",buf, easympi_rank);
           1 ->             output[29].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_leafdens3.txt",buf, easympi_rank);
           1 ->             output[30].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_dbh.txt",buf, easympi_rank);
           1 ->             output[31].open(nnn,ios::out);
           1 ->             sprintf(nnn,"%s_%i_100yearsofsolitude.txt",buf, easympi_rank);
           1 ->             output[33].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_NDDfield.txt",buf, easympi_rank);
           1 ->             output[34].open(nnn, ios::out);
           1 ->             sprintf(nnn,"%s_%i_cica.txt",buf, easympi_rank);
           1 ->             output[35].open(nnn, ios::out);
                        }
                        
                        /*sprintf(nnn,"%s_%i_paramspace.txt",buf, easympi_rank);
                         output[17].open(nnn, ios::out);
                         
                         output[17] << "proc"  << "\t" << easympi_rank << endl;
                         output[17] << "phi"  << "\t" << phi << endl;
                         output[17] << "k"  << "\t" <<klight << endl;
                         output[17] << "fallocwood"  << "\t" << fallocwood << endl;
                         output[17] << "falloccanopy"  << "\t" << falloccanopy << endl;
                         output[17] << "m"  << "\t" << m << endl;
                         output[17] << "m1"  << "\t" << m1 << endl;
                         if(_OUTPUT_fullLAI){
                         sprintf(nnn,"%s_%i_CHM.txt",buf, easympi_rank);
                         output[36].open(nnn, ios::out);
                         sprintf(nnn,"%s_%i_LAI3D_avg.txt",buf, easympi_rank);
                         output[37].open(nnn, ios::out);
                         }*/
           1 ->     }
                    
                    
           1 -> }
                
                
                /***************************************
                 *** Initialisation from inventories ***
                 ***************************************/
                
                
       ##### -> void InitialiseFromData(){
                    // prepare data set beforehand: col/x_dim, row/y_dim, dbh_measured, species_label,
                    
       ##### ->     fstream In(inputfile_data, ios::in);                                                // input stream
                    float col_data, row_data, dbh_measured, sp_lab_data;                            // values needed for tree initialisation
                    
       ##### ->     int col_int, row_int, data_read=0, data_initialised=0;                          // diagnostics
       ##### ->     float height_max=0;                                                             // diagnostics
                    
       ##### ->     nblivetrees=0;
                    
                    //for (int line=0;line<30;line++) In.getline(buffer,128,'\n');
                    
       ##### ->     cout << "Reading from file " << inputfile_data << "\n";
                    
       ##### ->     In.getline(buffer,256,'\n');                                                    // skip header lines
                    
       ##### ->     cout << "Header line skipped \n";
                    
       ##### ->     while ((In >> col_data >> row_data >> dbh_measured  >> sp_lab_data) && data_read < sites)       // restricting to data sets with a maximum number of values corresponding to no. of sites
                    {
       ##### ->         In.getline(buffer, 256, '\n'); // reads additional information into buffer
                        
       ##### ->         if((sp_lab_data > 0) && (sp_lab_data <= numesp) && (col_data >= 0) && (col_data < cols) && (row_data >= 0) && (row_data < rows)){
                            
                            // read only species that are rendered in TROLL (species label to be added via R / comparison input file and data)
                            // cout << "col: " << round(col_data) << " row: " << round(row_data) << " species: " << sp_lab_data << " dbh: " << dbh_measured << " data measured \n";
                            
       ##### ->             dbh_measured = 0.001*dbh_measured;          //here given in mm, converting to m
       ##### ->             cout << dbh_measured << "\n";
       ##### ->             col_int = (int) (col_data+0.5f);            //rounding, works since negatives have been eliminated before
       ##### ->             row_int = (int) (row_data+0.5f);
                            
                            // immediate tree birth
                
                            /* NEW CHANGE: lift (col_int + row_int * cols) out to reduce repeated calculation of index */
       ##### ->             int index = col_int + row_int * cols;
       ##### ->             if(T[index].t_age == 0){
       ##### ->                 T[index].BirthFromData(S, sp_lab_data, index, dbh_measured);
       ##### ->                 cout << "yes" << endl;
                            }
                            
       ##### ->             if(height_max < T[index].t_Tree_Height) height_max = T[index].t_Tree_Height;
                            
                            // first attempt: simple, only trees with coordinates, only known species
                            // other possibilities: not spatially explicit and/or assign species randomnly to trees whose species are not known
                            
       ##### ->             data_initialised++;
                        }
       ##### ->         data_read++;
                    }
                    
       ##### ->     cout << "\n" << data_read << " rows read from file. " << data_initialised << " rows usable for initialisation from data. \n";
       ##### ->     cout << "Maximum height of trees included is: " << height_max << "\n";
       ##### ->     cout << "NBtrees from Data:\t" << nblivetrees << "\n";
       ##### ->     cout << "Initialisation from data finished \n";
       ##### -> }
                
                
                /***************************************
                 *** Field dynamic memory allocation ***
                 ***************************************/
                
           1 -> void AllocMem() {
                    
                    int spp,haut,i;
                    
                    // HEIGHT = 80;
                    // instead of static definition of height, calculate according to maximum height that can be reached by trees
                    
           1 ->     HEIGHT = 0;
                    
           1 ->     for(spp=1;spp<=numesp;spp++) {
           1 ->         HEIGHT = max(HEIGHT,int(S[spp].s_hmax*S[spp].s_dmax*1.5/(S[spp].s_dmax*1.5+S[spp].s_ah)));  //   in number of vertical cells
                    }
                    
           1 ->     cout << "HEIGHT " << HEIGHT << endl;
                    
                    float d,r;
           1 ->     d = 0.0;
           1 ->     r = 0.0;
           1 ->     for(spp=1;spp<=numesp;spp++){
           1 ->         d = maxf(d,S[spp].s_dmax*1.5);
                        /* in number of horizontal cells */
           1 ->         r = maxf(r,ra0+S[spp].s_dmax*1.5*ra1);
                        /* in number of horizontal cells */
                    }
                    
           1 ->     RMAX = int(r+p_nonvert*NH*LV*HEIGHT);
                    //  RMAX = int(r);
           1 ->     SBORD = cols*RMAX;
           1 ->     dbhmaxincm = int(100.*d);
                    
           1 ->     if(!mpi_rank) {
                        /*cout << "HEIGHT : " << HEIGHT
                         << " RMAX : " << RMAX << " DBH : " << DBH <<"\n";
                         cout.flush();*/
                        
           1 ->         if(RMAX>rows){
                            /* Consistency tests */
           1 ->             cerr << "Error : RMAX > rows \n";
           1 ->             exit(-1);
                        }
           1 ->         if(HEIGHT > rows){
           1 ->             cerr << "Error : HEIGHT > rows \n";
           1 ->             exit(-1);
                        }
                    }
                    
                    
                    /*** Initialization of dynamic Fields ***/
                    /****************************************/
                    
           1 ->     if (NULL==(nbdbh=new int[dbhmaxincm])) cerr<<"!!! Mem_Alloc\n";                         /* Field for DBH histogram */
           1 ->     if (NULL==(layer=new float[HEIGHT+1])) cerr<<"!!! Mem_Alloc\n";                         /* Field for variables averaged by vertical layer */
           1 ->     if (NULL==(SPECIES_GERM=new int[numesp+1])) cerr<<"!!! Mem_Alloc\n";                           /* Field for democratic seed germination */
           1 ->     if(_SEEDTRADEOFF){
           1 ->         if (NULL==(PROB_S=new float[numesp+1])) cerr<<"!!! Mem_Alloc\n";
                    }
           1 ->     if(_NDD){
           1 ->         if (NULL==(PROB_S=new float[numesp+1])) cerr<<"!!! Mem_Alloc\n";
                    }
                    //  if (NULL==(persist=new long int[nbiter])) cerr<<"!!! Mem_Alloc\n";                  /* Field for persistence */
                    //  if (NULL==(distr=new int[cols])) cerr<<"!!! Mem_Alloc\n";
                    
           1 ->     if (NULL==(LAI3D=new float*[HEIGHT+1]))                                                   /* Field 3D */
           1 ->         cerr<<"!!! Mem_Alloc\n";                                                            /* Trees at the border of the simulated forest need to know the canopy occupancy by trees in the neighboring processor.*/
           1 ->     for(haut=0;haut<(HEIGHT+1);haut++)                                                          /* For each processor, we define a stripe above (labelled 0) and a stripe below (1). Each stripe is SBORD in width.*/
           1 ->         if (NULL==(LAI3D[haut]=new float[sites+2*SBORD]))                                   /* ALL the sites need to be updated.*/
           1 ->             cerr<<"!!! Mem_Alloc\n";
           1 ->     for(haut=0;haut<(HEIGHT+1);haut++)
           1 ->         for(int site=0;site<sites+2*SBORD;site++)
           1 ->             LAI3D[haut][site] = 0.0;
                    
           1 ->     if (NULL==(Thurt[0]=new unsigned short[3*sites]))                                       /* Field for treefall impacts */
           1 ->         cerr<<"!!! Mem_Alloc\n";
           1 ->     for(i=1;i<3;i++)
           1 ->         if (NULL==(Thurt[i]=new unsigned short[sites]))
           1 ->             cerr<<"!!! Mem_Alloc\n";
                    
                #ifdef DCELL
                    /* MAP_DCELL is a list of vectors -- there is one vector per dcell, and the vector has as many entries as the number of sites per dcell, and returns the absolute site value of these sites -- this is useful to distribute seeds across the dcell */
                    int x0,y0,x,y,site0,site,dcol,drow;
                    if (NULL==(MAP_DCELL=new int*[nbdcells])) cerr<<"!!! Mem_Alloc\n";
                    for(int dcell=0;dcell<nbdcells;dcell++){
                        if (NULL==(MAP_DCELL[dcell]=new int[sites_per_dcell])) cerr<<"!!! Mem_Alloc\n";
                        for(x0=0;x0<length_dcell;x0++)
                            for(y0=0;y0<length_dcell;y0++){
                                site0=x0+y0*length_dcell;
                                dcol=dcell%linear_nb_dcells;
                                drow=dcell/linear_nb_dcells;
                                x=dcol*length_dcell+x0;
                                y=drow*length_dcell+y0;
                                //cerr << "x_MAP " << x << "\ty_MAP " << y << "\t";
                                site=x+y*cols;
                                MAP_DCELL[dcell][site0] = site;
                            }
                    }
                    if (NULL==(prior_DCELL=new double[sites_per_dcell])) cerr<<"!!! Mem_Alloc\n";
                    for(int i=0;i<sites_per_dcell;i++) prior_DCELL[i]=1.0;
                    if (NULL==(post_DCELL=new unsigned int[sites_per_dcell])) cerr<<"!!! Mem_Alloc\n";
                    for(int i=0;i<sites_per_dcell;i++) post_DCELL[i]=0;
                    
                    if (NULL==(prior_GERM=new double[numesp+1])) cerr<<"!!! Mem_Alloc\n";
                    for(int i=0;i<=numesp;i++) prior_GERM[i]=0.0;
                    if (NULL==(post_GERM=new unsigned int[numesp+1])) cerr<<"!!! Mem_Alloc\n";
                    for(int i=0;i<=numesp;i++) post_GERM[i]=0;
                    
                #endif
                    
                #ifdef MPI                                                                                      /* Fields for MPI operations */
                    for(i=0;i<2;i++){                                                                       /*  Two fields: one for the CL north (0) one for the CL south (1) */
                        if (NULL==(LAIc[i]=new unsigned short*[HEIGHT+1]))                                    /* These fields contain the light info in the neighboring procs (2*SBORD in width, not SBORD !). They are used to update local fields */
                            cerr<<"!!! Mem_Alloc\n";
                        for(haut=0;haut<(HEIGHT+1);haut++)
                            if (NULL==(LAIc[i][haut]=new unsigned short[2*SBORD]))
                                cerr<<"!!! Mem_Alloc\n";
                    }
                #endif
           1 -> }
                
                
                /***************************************
                 **** Initial non-local germination ****
                 ***************************************/
                
           1 -> void BirthInit() {
                    
           1 ->     if(!_FromData){
           1 ->         nblivetrees=0;
                    }
                #ifdef MPI
                    MPI_Barrier(MPI_COMM_WORLD);
                #endif
           1 ->     cout<<endl;
           1 -> }
                
                
                /*###############################################
                 ###############################################
                 #######  Evolution at each timestep    ########
                 ###############################################
                 ###############################################*/
                
        6000 -> void Evolution() {
                    
        6000 ->     UpdateField();                                          /* Update light fields and seed banks */
        6000 ->     UpdateTree();                                           /* Update trees */
        6000 ->     if(_BASICTREEFALL) UpdateTreefall();                    /* Compute and distribute Treefall events */
        6000 ->     Average();                                              /* Compute averages for outputs */
        6000 ->     OutputField();                                          /* Output the statistics */
        6000 -> }
                
                
                /*##################################
                 ####    Compute field LAI 3D    ###
                 ####    Compute field Seed     ####
                 ##################################*/
                
        6000 -> void UpdateField() {
                    
                    int site, haut;
        6000 ->     int spp = 0;
                    
                    
                    /* set the iteration environment -- nb: the current structure of code suppose that environment is periodic (a period = a year),
                     * if one wants to input a variable climate, with interannual variation and climate change along the simulation,
                     * a full climatic input needs to be input (ie number of columns=iter and not iterperyear) and change iterperyear by nbiter here. */
                    //CURRENTLY NOT USED: precip, WS, Wmean, e_s, e_a,VPDbasic,VPDday
                
                    /* NEW CHANGE:  */
        6000 ->     int index = iter % iterperyear;
                
        6000 ->     temp = Temperature[index];
        6000 ->     tmax = DailyMaxTemperature[index];
        6000 ->     tnight = NightTemperature[index];
        6000 ->     precip = Rainfall[index];
        6000 ->     WS = WindSpeed[index];
        6000 ->     Wmax = MaxIrradiance[index] * 1.678;       // 1.678 is to convert irradiance from W/m2 to micromol of PAR /s /m2, the unit used in the FvCB model of photosynthesis
        6000 ->     Wmean = MeanIrradiance[index];            // still in W/m2
        6000 ->     e_s = SaturatedVapourPressure[index];
        6000 ->     e_a = VapourPressure[index];
        6000 ->     VPDbasic = VapourPressureDeficit[index];
        6000 ->     VPDday = DailyVapourPressureDeficit[index];
        6000 ->     VPDmax = DailyMaxVapourPressureDeficit[index];
                    
                    /***  Compute Field LAI3D  ***/
                    /*****************************/
                    
                    
                #ifdef MPI
                    /* Reinitialize field LAI3D */
                    for(i=0;i<2;i++)
                        for(haut=0;haut<(HEIGHT+1);haut++)
                            for(site=0;site<2*SBORD;site++)
                                LAIc[i][haut][site] = 0;
                #endif
                    
                    int sbsite;
                
                    /* NEW CHANGE: not sure? */
        6000 ->     for(haut = 0; haut < (HEIGHT+1); haut++)
        6000 ->         for(sbsite = 0; sbsite < sites + 2 * SBORD; sbsite++)       //!!!!
        6000 ->             LAI3D[haut][sbsite] = 0.0;      //!!!!
                
                    //fill(&LAI3D[0][0], &LAI3D[0][0] + sizeof(LAI3D), 0.0);
                    /*
                    for (haut = 0; haut < (HEIGHT + 1); ++ haut){
                        fill(&LAI3D[haut][0], &LAI3D[haut][0] + sizeof(LAI3D[haut]), 0.0);
                    }*/
                    
        6000 ->     for(site = 0; site < sites; site++)                                    /* Each tree contributes to LAI3D */
        6000 ->         T[site].CalcLAI();
                
                    /* NEW CHANGE: take out the computation of index from loops */
        6000 ->     for(haut = HEIGHT; haut > 0; haut--){                                 /* LAI is computed by summing LAI from the canopy top to the ground */
        6000 ->         sbsite = SBORD;
        6000 ->         index = haut - 1;
        6000 ->         for(site = 0; site < sites; site++){
        6000 ->             LAI3D[index][sbsite] += LAI3D[haut][sbsite];         /*!!!!*/
        6000 ->             if (LAI3D[index][sbsite] < 0) T[site].OutputTreeStandard();   /*!!!!*/
        6000 ->             ++ sbsite;
                        }
                    }
                    
                    /*  for(site=0;site<sites;site++)       Trunks shade the cells in which they are
                     T[site].TrunkLAI();*/
                    
                #ifdef MPI
                    /* Communicate border of field */
                    /*MPI_ShareField(LAI3D,LAIc,2*SBORD);
                     This MPI command no longer exists in openMPI
                     Action 20/01/2016 TODO: FIX THIS */
                    MPI_ShareField(LAI3D,LAIc,2*SBORD);
                    for(haut=0;haut<(HEIGHT+1);haut++){
                        /* Add border effects in local fields */
                        if(mpi_rank)
                            for(site=0;site<2*SBORD;site++)
                                LAI3D[haut][site] += LAIc[0][haut][site];
                        if(mpi_rank<mpi_size-1)
                            for(site=0;site<2*SBORD;site++)
                                LAI3D[haut][site+sites] += LAIc[1][haut][site];
                    }
                #endif
                    
                    /*** Evolution of the field Seed **/
                    /*********************************/
                    
                    /* Pass seeds across processors => two more fields to be communicated between n.n. (nearest neighbor) processors.
                     NB: dispersal distance is bounded by the value of 'rows'.
                     At least 99 % of the seeds should be dispersed within the stripe or on the n.n. stripe.
                     Hence rows > 4.7*max(dist_moy_dissemination),for an exponential dispersal kernel.*/
                    
                #ifdef DCELL
                    if(iter%iterperyear == 0){
                        for(spp=1;spp<=numesp;spp++) {                              /* External seed rain: constant flux from the metacommunity */
                            for(int dcell=0;dcell<nbdcells;dcell++){
                                // loop over dcells and add exactly s_nbext seeds to s_DCELL
                                S[spp].s_DCELL[dcell]=S[spp].s_nbext;
                                //if(spp<10) cerr << "BeforeDis, dcell#\t" << dcell << "\ts_DCELL[dcell]\t" << S[spp].s_DCELL[dcell] << "\tS[spp].s_nbext\t" << S[spp].s_nbext <<endl;
                            }
                        }
                        for(site=0;site<sites;site++)                                       /* disperse seeds produced by mature trees */
                            if(T[site].t_age)
                                T[site].DisperseSeed();
                #else
        6000 ->         for(site = 0; site < sites; site++)                                       /* disperse seeds produced by mature trees */
        6000 ->             if(T[site].t_age)
        6000 ->                 T[site].DisperseSeed();
                        /* FUTURE: can change to the list storing empty tree sites */
                #endif
                #ifdef DCELL
                    }
                #endif
                    
                #ifdef MPI                                                              /* Seeds passed across processors */
                    for(spp=1;spp<=numesp;spp++) {
                        MPI_ShareSeed(S[spp].s_Gc,sites);
                        S[spp].AddSeed();
                    }
                #endif
                    
                #ifdef DCELL  // This entire section is commented as it is no longer needed in DCELL
                #else
        6000 ->     if(_SEEDTRADEOFF){
        6000 ->         if(!mpi_rank || S[spp].s_nbind*sites > 50000){
        6000 ->             for(spp=1;spp<=numesp;spp++) {                              /* External seed rain: constant flux from the metacommunity */
        6000 ->                 for(int ii=0;ii<S[spp].s_nbext;ii++){
        6000 ->                     site = genrand2i()%sites;
        6000 ->                     if (S[spp].s_Seed[site] == 0) site_has_S[site].push_back(spp);
        6000 ->                     S[spp].s_Seed[site]++;
                                }
                            }
                        }
                    }
                    else {
                        //cout << "nblivetrees " << nblivetrees << endl;
        6000 ->         if(!mpi_rank || S[spp].s_nbind * sites > 50000){
        6000 ->             for(spp = 1; spp <= numesp; spp++) {                              /* External seed rain: constant flux from the metacommunity */
        6000 ->                 for(int ii = 0; ii < S[spp].s_nbext; ii++){
        6000 ->                     site = genrand2i() % sites;
                
                                    /* NEW CHANGE: site_has_S */
        6000 ->                     if (seed_count[site][spp] == 0){        //!!!!
        6000 ->                         seed_count[site][spp] = 1;
        6000 ->                         site_has_S[site].push_back(spp);
                                    }
        6000 ->                     else if (seed_count[site][spp] != 1) seed_count[site][spp] = 1;
                
                
                                }
                            }
                        }
                    }
                #endif
                    
                    
                #ifdef MPI
                    MPI_Barrier(MPI_COMM_WORLD);
                #endif
                    
        6000 ->     if(_NDD){
                        /*** Evolution of the field NDDfield **/
                        /**************************************/
                        
        6000 ->         float normBA=10000.0/(0.001+PI*R*R*BAtot);
        6000 ->         for(site=0;site<sites;site++) {
                            
                            
        6000 ->             for(spp=1;spp<=numesp;spp++) {
                                /*if ((iter == int(nbiter-1))&&(site>80000)&&(site<85000))  {
                                 sor[142]<< T[site].t_NDDfield[spp] << "\t" ;
                                 }*/
        6000 ->                 T[site].t_NDDfield[spp]=0;
                            }
                            //if (iter == int(nbiter-1))  sor[142]<< "\n";
                            
        6000 ->             int row0=T[site].t_site/cols;
        6000 ->             int col0=T[site].t_site%cols;
        6000 ->             for(int col=max(0,col0-R);col<=min(cols-1,col0+R);col++) {
        6000 ->                 for(int row=max(0,row0-R);row<=min(rows-1,row0+R);row++) {                   /* loop over the neighbourhood */
        6000 ->                     int xx=col0-col;
        6000 ->                     int yy=row0-row;
        6000 ->                     float d=sqrt(xx*xx+yy*yy);
        6000 ->                     if((d<=R)&&(d>0))  {                                             /* is the voxel within the neighbourhood?  */
        6000 ->                         int j=cols*row+col;
        6000 ->                         if(T[j].t_age) T[site].t_NDDfield[T[j].t_sp_lab]+= PI* T[j].t_dbh * T[j].t_dbh*0.25*normBA;
                                        
                                    }
                                    
                                    
                                }
                                
                            }
                        }
                    }
        6000 -> }
                
                
                /*##############################
                 ####	Birth, Growth       ####
                 ####	and death of trees  ####
                 ##############################*/
                
        6000 -> void UpdateTree() {
                    
                    int site,spp;
                    float flux;
                    
                #ifdef DCELL
                    
                    for(spp=1;spp<=numesp;spp++) S[spp].UpdateSeed();
                    
                    // A much simpler version of seed recruitment is implemented again based on the idea
                    // of a multinomial sampling of the s_Seed field.
                
                    for(site=0;site<sites;site++){
                        int nbseeds=0;
                        for(spp=1;spp<=numesp;spp++) nbseeds+=S[spp].s_Seed[site];
                        if(T[site].t_age == 0 && nbseeds > 0){
                            //int summ=0;
                            //for(spp=1;spp<=numesp;spp++) summ+=S[spp].s_Seed[site];
                            //cerr << site << "\t" << summ << endl;
                            prior_GERM[0]=0.0;post_GERM[0]=0;
                            for(spp=1;spp<=numesp;spp++){
                                prior_GERM[spp]=double(S[spp].s_Seed[site]*S[spp].s_seedmass);
                                post_GERM[spp]=0;           //whether this needs to be done inside the loop?
                            }
                            //for(spp=1;spp<=numesp;spp++) cerr << prior_GERM[spp] << " ";
                            
                            gsl_ran_multinomial(gslrand,numesp+1,1,prior_GERM,post_GERM);   
                            float sumprior=0.0,sumpost=0;
                            for(int i=1;i<=numesp;i++){
                                sumprior+=prior_GERM[i];sumpost+=post_GERM[i];
                            }
                            //cerr << numesp << "\t"<< sumprior << "\t"<< sumpost << "\n";
                            
                            //for(spp=1;spp<=numesp;spp++)
                            //    cerr << spp << "\tpost_GERM\t" << post_GERM[spp] << endl;
                            int selected_species=0;
                            for(spp=1;spp<=numesp;spp++) if(post_GERM[spp]==1){
                                selected_species=spp;
                                break;}
                            //cerr << "selected species:\t" << spp <<endl;
                            flux = Wmax*exp(-flor(LAI3D[0][site+SBORD])*klight);
                            if(flux>(S[selected_species].s_LCP))
                                T[site].Birth(S,selected_species,site);
                            /* If enough light, germination, initialization of NPP (LCP is the species light compensation point -- here, light is the sole environmental resources tested as a limiting factor for germination, but we should think about adding nutrients (N,P) and water conditions... */
                            for(spp=1;spp<=numesp;spp++) {
                                S[spp].s_Seed[site]=0;
                                site_has_S[site].clear();
                            }
                        }
                    }
                #else
                    int iii;
        6000 ->     if(_SEEDTRADEOFF){
        6000 ->         for(site=0;site<sites;site++) {                                             /***** Local germination *****/
        6000 ->             if(T[site].t_age == 0) {
        6000 ->                 iii=0;
        6000 ->                 float tot=0;                                                        /* _SEEDTRADEOFF */
        6000 ->                 for(spp=1;spp<=numesp;spp++){                                       /* lists all the species with a seed present at given site... */
        6000 ->                     if(S[spp].s_Seed[site]) {
        6000 ->                         SPECIES_GERM[iii]=spp;
        6000 ->                         if(_NDD){
        6000 ->                             float p=S[spp].s_Seed[site]*S[spp].s_seedmass/(T[site].t_NDDfield[spp]*10000+1);
        6000 ->                             PROB_S[iii]=tot+ p;
        6000 ->                             tot+=p;
                                        }
                                        else{
        6000 ->                             PROB_S[iii]=tot+ S[spp].s_Seed[site]*S[spp].s_seedmass;
        6000 ->                             tot+=S[spp].s_Seed[site]*S[spp].s_seedmass;
                                        }
        6000 ->                         iii++;
                                    }
                                }
        6000 ->                 if(iii) {                                                           /* ... and then randomly select one of these species */
        6000 ->                     double p=genrand2();                                    /* if SEEDTRADEOFF is defined, probability of species recruit are proportional to the number of seeds time the seed mass, if NDD is also defined the probablility is also inversly proportional to the species NDDfield term at that site */
        6000 ->                     float itot=1.0/tot;
        6000 ->                     int s=0;
        6000 ->                     while (p>PROB_S[s]*itot) {s++;}
        6000 ->                     spp=SPECIES_GERM[s];
        6000 ->                     flux = Wmax*exp(-flor(LAI3D[0][site+SBORD])*klight); //REPLACE WITH TABLE LOOKUP
        6000 ->                     if(flux>(S[spp].s_LCP)){
                                        /* If enough light, germination, initialization of NPP (LCP is the species light compensation point*/
                                        /* here, light is the sole environmental resources tested as a limiting factor for germination, but we should think about adding nutrients (N,P) and water conditions... */
        6000 ->                         T[site].Birth(S,spp,site);
                                    }
                                }
                            }
                        }
                    }
                    
                    else {
                
                        /* NEW CHANGE: site_has_S */
                        int size;
        6000 ->         for (site = 0; site < sites; ++site){
        6000 ->             if (T[site].t_age == 0){
        6000 ->                 size = site_has_S[site].size();
        6000 ->                 if (size) {
        6000 ->                     spp = site_has_S[site][rand() % size];
        6000 ->                     flux = Wmax * exp(-flor(LAI3D[0][site + SBORD]) * klight);
        6000 ->                     if (flux > S[spp].s_LCP) T[site].Birth(S, spp, site);
                                }
                            }
                            else{
        6000 ->                 for(spp=1;spp<=numesp;++spp) seed_count[site][spp]=0;   // instead of doing here, change to detect with help from site_has[]
        6000 ->                 site_has_S[site].clear();
                            }
                        }
                    }
                
                #endif
                    
        6000 ->     nbdead_n1=nbdead_n10=0;
        6000 ->     if(_BASICTREEFALL){
        6000 ->         nbdead_c1=nbdead_c10=0;
                    }
        6000 ->     for(site=0;site<sites;site++) {
                        /***** Tree evolution: Growth or death *****/
        6000 ->         T[site].Update();
                    }
                    
                #ifdef DCELL
                    // This loop has been moved upwards before the tree birth loop
                #else
        6000 ->     for(spp=1;spp<=numesp;spp++) S[spp].UpdateSeed();
                #endif
                    
        6000 -> }
                
                
                /******************************
                 *** Treefall gap formation ***
                 ******************************/
                
                
        6000 -> void UpdateTreefall(){
                    int site;
                    
        6000 ->     for(site=0;site<sites;site++){
        6000 ->         Thurt[0][site] = Thurt[0][site+2*sites] = 0;
        6000 ->         Thurt[0][site+sites] = 0;
                    }
                    
        6000 ->     nbTreefall1 = 0;
        6000 ->     nbTreefall10=0;
        6000 ->     for(site=0;site<sites;site++)
        6000 ->         if(T[site].t_age) {
        6000 ->             T[site].FallTree();
                        }
                    
                    
                #ifdef MPI
                    /* Treefall field passed to the n.n. procs */
                    MPI_ShareTreefall(Thurt, sites);
                #endif
                    
        6000 ->     for(site=0;site<sites;site++)
                    /* Update of Field hurt */
        6000 ->         if(T[site].t_age) {
        6000 ->             T[site].t_hurt = Thurt[0][site+sites];
                #ifdef MPI
                            if(mpi_rank) T[site].t_hurt = max(T[site].t_hurt,Thurt[1][site]);
                            if(mpi_rank<mpi_size-1) T[site].t_hurt = max(T[site].t_hurt,Thurt[2][site]);
                #endif
                        }
        6000 -> }
                
                
                
                /*###############################################
                 ###############################################
                 #######        Output routines         ########
                 ###############################################
                 ###############################################*/
                
                /*********************************************************
                 *** Calculation of the global averages every timestep ***
                 *********************************************************/
                
        6000 -> void Average(void){
                    
                    int site,spp,i;
        6000 ->     float sum1=0.0,sum10=0.0,sum30=0.0,ba=0.0,npp=0.0,gpp=0.0, ba10=0.0, agb=0.0, rday=0.0, rnight=0.0, rstem=0.0, litterfall=0.0;
                    
        6000 ->     if(!mpi_rank) {
        6000 ->         for(spp=1;spp<=numesp;spp++)
        6000 ->             for(i=0;i<12;i++)
        6000 ->                 S[spp].s_output_field[i]=0;
                        
        6000 ->         float inbcells = 1.0/float(sites*mpi_size);
        6000 ->         float inbhectares = inbcells*NH*NH*10000.0;
        6000 ->         if(_OUTPUT_reduced){
        6000 ->             output[0] << iter << "\t";
        6000 ->             for(spp=1;spp<=numesp;spp++)
        6000 ->                 output[0] << float(S[spp].s_nbind)*inbhectares << "\t";
                        }
                        else{
        6000 ->             for(i=0;i<7;i++) output[i] << iter << "\t";
        6000 ->             for(i=20;i<23;i++) output[i] << iter << "\t";
        6000 ->             for(spp=1;spp<=numesp;spp++) output[0] << float(S[spp].s_nbind)*inbhectares << "\t";
                        }
        6000 ->         for(site=0;site<sites;site++)T[site].Average();
                        
        6000 ->         cout << iter << "\tNBtrees\t"<<nblivetrees << endl;
                        
        6000 ->         for(spp=1;spp<=numesp;spp++) {
        6000 ->             S[spp].s_output_field[1] *= inbhectares;
                            //species number of trees with dbh>10cm
        6000 ->             S[spp].s_output_field[2] *= inbhectares;
                            //species number of trees with dbh>30cm
        6000 ->             S[spp].s_output_field[3] *= 3.1415*0.25*inbhectares;
                            //species basal area
        6000 ->             S[spp].s_output_field[4] *= inbhectares;
                            //species total NPP (sum of t_NPP) in MgC (per timestep)
        6000 ->             S[spp].s_output_field[5] *= inbhectares;
                            //species total GPP (sum of t_GPP) in MgC (per timestep)
        6000 ->             S[spp].s_output_field[6] *= 3.1415*0.25*inbhectares;
                            //species basal area; with only trees with dbh>10cm
        6000 ->             S[spp].s_output_field[7] *= inbhectares;
                            //species aboveground biomass
        6000 ->             S[spp].s_output_field[8] *= inbhectares;
                            /* species leaf Rday in MgC (per timestep) */
        6000 ->             S[spp].s_output_field[9] *= inbhectares;
                            //species leaf Rnight in MgC (per timestep)
        6000 ->             S[spp].s_output_field[10] *= inbhectares;
                            //species Rstem  in MgC (per timestep)
        6000 ->             S[spp].s_output_field[11] *= inbhectares;
                            //species litterfall  in MgC (per timestep)
        6000 ->             sum1+= float(S[spp].s_nbind)*inbhectares;
        6000 ->             sum10 += S[spp].s_output_field[1];
        6000 ->             sum30 += S[spp].s_output_field[2];
        6000 ->             ba += S[spp].s_output_field[3];
        6000 ->             npp += S[spp].s_output_field[4];
        6000 ->             gpp += S[spp].s_output_field[5];
        6000 ->             ba10 += S[spp].s_output_field[6];
        6000 ->             agb += S[spp].s_output_field[7];
        6000 ->             rday += S[spp].s_output_field[8];
        6000 ->             rnight += S[spp].s_output_field[9];
        6000 ->             rstem += S[spp].s_output_field[10];
        6000 ->             litterfall += S[spp].s_output_field[11];
                            
                            
        6000 ->             if(!_OUTPUT_reduced){
        6000 ->                 for(i=1;i<7;i++) output[i] << S[spp].s_output_field[i] << "\t";
        6000 ->                 output[19] << S[spp].s_output_field[7] << "\t";
        6000 ->                 output[20] << S[spp].s_output_field[8] << "\t";
        6000 ->                 output[21] << S[spp].s_output_field[9] << "\t";
        6000 ->                 output[22] << S[spp].s_output_field[10] << "\t";
        6000 ->                 output[27] << S[spp].s_output_field[11] << "\t";
                            }
                            
        6000 ->             output[27] << S[spp].s_output_field[11] << "\t";
                            
        6000 ->             if (_NDD) {
        6000 ->                 BAtot=ba;
                            }
                            
                        }
        6000 ->         if(_OUTPUT_reduced){
        6000 ->             output[0] << sum1 << "\t";                                                     //total number of trees (dbh>1cm=DBH0)
                            
        6000 ->             for(spp=1;spp<=numesp;spp++) output[0] << S[spp].s_output_field[1] << "\t";
        6000 ->             output[0] << sum10 << "\t";                                                    //total number of trees (dbh>10cm=DBH0)
                            
        6000 ->             for(spp=1;spp<=numesp;spp++) output[0] << S[spp].s_output_field[2] << "\t";
        6000 ->             output[0] << sum30 << "\t";                                                    //total number of trees (dbh>30cm=DBH0)
                            
        6000 ->             for(spp=1;spp<=numesp;spp++) output[0] << S[spp].s_output_field[6] << "\t";
        6000 ->             output[0] << ba10 << "\t";
                            
        6000 ->             for(spp=1;spp<=numesp;spp++) output[0] << S[spp].s_output_field[4] << "\t";
        6000 ->             output[0] << npp << "\t";
                            
        6000 ->             for(spp=1;spp<=numesp;spp++) output[0] << S[spp].s_output_field[5] << "\t";
        6000 ->             output[0] << gpp << "\t";
                            
        6000 ->             for(spp=1;spp<=numesp;spp++) output[0] << S[spp].s_output_field[7] << "\t";
        6000 ->             output[0] << agb << endl;
                            
        6000 ->             output[27] << litterfall << endl;
                            
                        }
                        else{
                            
        6000 ->             output[0] << sum1 << endl;          //total number of trees (dbh>1cm=DBH0)
        6000 ->             output[1] << sum10 << endl;         //total number of trees with dbh>10cm
        6000 ->             output[2] << sum30 << endl;         //total number of trees with dbh>30cm
        6000 ->             output[3] << ba << endl;            //total basal area
        6000 ->             output[4] << npp << endl;           //total NPP in MgC per ha (per time step)
        6000 ->             output[5] << gpp << endl;           //total GPP in MgC par ha (per time step)
        6000 ->             output[6] << ba10 << endl;          //total basal area with only trees with dbh>10cm
        6000 ->             output[19] << agb << endl;          //total above ground biomass
        6000 ->             output[20] << rday << endl;         //total leaf day respiration
        6000 ->             output[21] << rnight << endl;       //total leaf night respiration
        6000 ->             output[22] << rstem << endl;        //total stem respiration
        6000 ->             output[27] << litterfall << endl;   //total litterfall
                            
        6000 ->             float tototest=0.0, tototest2=0.0, flux;
        6000 ->             for(site=0;site<sites;site++) {
        6000 ->                 flux = Wmax*exp(-flor(LAI3D[0][site+SBORD])*klight);
        6000 ->                 tototest += flux;
        6000 ->                 tototest2 += flux*flux;
                            }
        6000 ->             tototest /=float(sites*LH*LH);                              // Average light flux (PPFD) on the ground
        6000 ->             tototest2 /=float(sites*LH*LH);
        6000 ->             if(iter)
        6000 ->                 output[7] << iter<< "\tMean PPFDground\t"<< tototest << "\t" << sqrt(tototest2-tototest*tototest) << "\n";
                            
                            
        6000 ->             if(_BASICTREEFALL) output[8] << iter << "\t" << nbdead_n1*inbhectares << "\t" << nbdead_n10*inbhectares<< "\t" << nbdead_c1*inbhectares << "\t" << nbdead_c10*inbhectares << "\t" << nbTreefall1*inbhectares << "\t" << nbTreefall10*inbhectares << "\t" << endl;
        6000 ->             else output[8] << iter << "\t" << nbdead_n1*inbhectares << "\t" << nbdead_n10*inbhectares<< "\t" << endl;
                        }
                    }
                    
                #ifdef MPI
                    MPI_Reduce(&(S[spp].s_nbind),&sind,1,
                               MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
                    MPI_Reduce(S[spp].s_output_field,S[spp].s_output_field,5,
                               MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
                    MPI_Reduce(Mortality,Mortality,4,
                               MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
                    MPI_Reduce(&S[spp].s_output_field[6],&S[spp].s_output_field[6],5,
                               MPI_FLOAT,MPI_MAX,0,MPI_COMM_WORLD);
                #endif
                    
        6000 ->     if(!mpi_rank) {
        6000 ->         if(iter == 200){                                        // State at the 200th iteration (for all living trees: dbh, height, crown radius and depth and dbh increment)
        6000 ->             for(site=0;site<sites;site++) {
        6000 ->                 if(T[site].t_dbh>0.0)
        6000 ->                     output[9] << T[site].t_dbh*LH*100 << "\t" << T[site].t_Tree_Height
        6000 ->                     << "\t" << T[site].t_Crown_Radius*LH
        6000 ->                     << "\t" << T[site].t_Crown_Depth*LV
        6000 ->                     << "\t" << T[site].t_ddbh*LH*100 << "\n";
                            }
                        }
                    }
                    
                #ifdef MPI
                    /* This section corresponds to the parallel version of
                     the reporting of the global diagnostic variables. Since much work has been done
                     on routine Average over the past years, this would need a full rewrite
                     !!!!Action 20/01/2016: rework the parallel version of function Average!!!!
                     
                     MPI_Reduce(&(S[spp].s_nbind),&sind,1,
                     MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
                     MPI_Reduce(S[spp].s_output_field,S[spp].s_output_field,5,
                     MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
                     MPI_Reduce(Mortality,Mortality,4,
                     MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
                     MPI_Reduce(&S[spp].s_output_field[6],&S[spp].s_output_field[6],5,
                     MPI_FLOAT,MPI_MAX,0,MPI_COMM_WORLD);
                     */
                #endif
        6000 ->     cout.flush();
        6000 -> }
                
                
                /*********************************
                 **** Output of Fields Shares ****
                 *********************************/
                
                
        6000 -> void OutputField(){
                    
                    /* output for dbh histogram and mean LAI by height class */
                    
                    int site,haut;
                    
        6000 ->     if((nbout)&&((iter%freqout)==freqout-1)) {
                        // output fields, nbout times during simulation (every freqout iterations)
                        
                        int d;
        6000 ->         for(d=0;d<dbhmaxincm;d++) nbdbh[d]=0;
        6000 ->         for(site=0;site<sites;site++) T[site].histdbh();
                        
        6000 ->         for(haut=0;haut<(HEIGHT+1);haut++){
        6000 ->             layer[haut] = 0;
        6000 ->             for(site=0;site<sites;site++) layer[haut] += LAI3D[haut][site+SBORD];
                        }
                        
                #ifdef MPI
                        MPI_Status status;
                        MPI_Reduce(nbdbh,nbdbh,dbhmaxincm,
                                   MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
                        
                        MPI_Reduce(layer,layer,HEIGHT,
                                   MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
                #endif
                        
        6000 ->         if(!mpi_rank) {
                            
                            // output of the dbh histograms (output[31])
        6000 ->             for(d=1;d<dbhmaxincm;d++) output[31] << d << "\t" << nbdbh[d]  << "\n";
        6000 ->             output[31] <<  "\n";
                            
                            // output of the mean LAI per height class (output[32])
        6000 ->             float norm = 1.0/float(sites*LH*LH*mpi_size);
        6000 ->             for(haut=0;haut<(HEIGHT+1);haut++) output[32] << haut*LV << "\t" << layer[haut]*norm << "\n";
        6000 ->             output[32] <<  "\n";
                        }
                    }
        6000 -> }
                
                /*********************************
                 ******** Output routines ********
                 *********************************/
                
                /* This provides a snapshot of the forest whenever called. Per default, this function is used to create the final pattern */
                
           1 -> void OutputSnapshot(fstream& output){
           1 ->     for(int row=0;row<rows;row++)
           1 ->         for(int col=0;col<cols;col++){
           1 ->             output << col << "\t" << row << "\t" << T[col + cols*row].t_age << "\t" << T[col + cols*row].t_dbh << "\t" << T[col + cols*row].t_Tree_Height << "\t" << T[col + cols*row].t_Crown_Radius << "\t" << T[col + cols*row].t_Crown_Depth << "\t" << T[col + cols*row].t_sp_lab << "\t" << T[col + cols*row].t_leafarea << "\t" << T[col + cols*row].t_ddbh << "\t" << T[col + cols*row].t_GPP   << endl;
                        }
           1 -> }
                
                /* This can be used to take snapshots of the forest in more detail and track its development over time. Currently used for 100 years development analysis. */
                
       ##### -> void OutputSnapshotDetail(fstream& output){
       ##### ->     for(int row=0;row<rows;row++)
       ##### ->         for(int col=0;col<cols;col++){
       ##### ->             output << iter << "\t" << col+cols*row << "\t" << col << "\t" << row << "\t" << T[col + cols*row].t_age << "\t" << T[col + cols*row].t_sp_lab << "\t" << T[col + cols*row].t_dbh << "\t" << T[col + cols*row].t_Tree_Height << "\t" << T[col + cols*row].t_Crown_Radius << "\t" << T[col + cols*row].t_Crown_Depth << "\t" << T[col + cols*row].t_leafarea << "\t" << T[col + cols*row].t_dens << "\t" << T[col + cols*row].t_GPP << "\t" << T[col + cols*row].t_hurt << endl;
                        }
       ##### -> }
                
                /* This provides relevant species parameters whenever called */
                
                
       ##### -> void OutputSpeciesParameters(fstream& output){
       ##### ->     for(int sp=1;sp<=numesp;sp++) output << S[sp].s_name << "\t" << S[sp].s_Nmass << "\t" << S[sp].s_Pmass << "\t" << S[sp].s_LMA << "\t" << S[sp].s_Vcmax << "\t" << S[sp].s_Jmax << "\t" << S[sp].s_Rdark << "\t" << S[sp].s_LCP << "\n";
       ##### -> }
                
                
                /* This creates a Canopy Height Model and LAD profile whenever called */
                
                
       ##### -> void OutputFullLAI(fstream& output_CHM, fstream& output_LAD){
       ##### ->     for(int s=0;s<sites;s++){
       ##### ->         int height_canopy=0;
       ##### ->         for(int h=0;h<(HEIGHT);h++){
       ##### ->             if(LAI3D[h][s+SBORD] > 0) height_canopy = max(h,height_canopy);
                        }
       ##### ->         output_CHM << s << "\t" << int(s/cols) << "\t" << int(s%cols) << "\t"  << height_canopy << endl;
                    }
       ##### ->     float isites = 1.0/sites;
       ##### ->     for(int h=0;h<(HEIGHT);h++){
       ##### ->         float LAI3D_avg = 0.0;
       ##### ->         for(int s=0;s<sites;s++){
       ##### ->             if((LAI3D[h][s+SBORD]-LAI3D[h+1][s+SBORD]) < 0) cerr << "Be careful negative PAD!" << endl;
       ##### ->             LAI3D_avg+=LAI3D[h][s+SBORD]-LAI3D[h+1][s+SBORD];
                        }
       ##### ->         output_LAD << h << "\t" << LAI3D_avg * isites << endl;
                    }
       ##### -> }
                
                /*********************************
                 ********** MPI Routines *********
                 *********************************/
                
                
                #ifdef MPI
                
                /* Communication of border fields in the parallel version of the code */
                /* Only if the MPI option has been enabled */
                void MPI_ShareSeed(unsigned char **c, int n) {
                    
                    MPI_Status status;
                    
                    if(p_rank == size-1)
                        MPI_Sendrecv(c[0],n,MPI_UNSIGNED_CHAR,size-2,0,
                                     c[3],n,MPI_UNSIGNED_CHAR,0,0,MPI_COMM_WORLD,&status);
                    if(p_rank == 0)
                        MPI_Sendrecv(c[0],n,MPI_UNSIGNED_CHAR,size-1,0,
                                     c[3],n,MPI_UNSIGNED_CHAR,1,0,MPI_COMM_WORLD,&status);
                    if((p_rank) && (p_rank < size-1))
                        MPI_Sendrecv(c[0],n,MPI_UNSIGNED_CHAR,p_rank-1,0,
                                     c[3],n,MPI_UNSIGNED_CHAR,p_rank+1,0,MPI_COMM_WORLD,&status);
                    
                    if(p_rank == 0)
                        MPI_Sendrecv(c[1],n,MPI_UNSIGNED_CHAR,1,1,
                                     c[2],n,MPI_UNSIGNED_CHAR,size-1,1,MPI_COMM_WORLD,&status);
                    if(p_rank == size-1)
                        MPI_Sendrecv(c[1],n,MPI_UNSIGNED_CHAR,0,1,
                                     c[2],n,MPI_UNSIGNED_CHAR,size-2,1,MPI_COMM_WORLD,&status);
                    if((p_rank) && (p_rank < size-1))
                        MPI_Sendrecv(c[1],n,MPI_UNSIGNED_CHAR,p_rank+1,1,
                                     c[2],n,MPI_UNSIGNED_CHAR,p_rank-1,1,MPI_COMM_WORLD,&status);
                }
                
                void MPI_ShareField(unsigned short **cl, unsigned short ***cp, int n) {
                    
                    MPI_Status status;
                    for(int haut=0;haut<(HEIGHT+1);haut++) {
                        if(p_rank == 0)
                            MPI_Sendrecv(cl[haut],n,MPI_UNSIGNED_SHORT,size-1,haut,
                                         cp[1][haut],n,MPI_UNSIGNED_SHORT,1,haut,
                                         MPI_COMM_WORLD,&status);
                        if(p_rank == size-1)
                            MPI_Sendrecv(cl[haut],n,MPI_UNSIGNED_SHORT,size-2,haut,
                                         cp[1][haut],n,MPI_UNSIGNED_SHORT,0,haut,
                                         MPI_COMM_WORLD,&status);
                        if((p_rank) && (p_rank < size-1))
                            MPI_Sendrecv(cl[haut],n,MPI_UNSIGNED_SHORT,p_rank-1,haut,
                                         cp[1][haut],n,MPI_UNSIGNED_SHORT,p_rank+1,haut,
                                         MPI_COMM_WORLD,&status);
                        
                        if(p_rank == 0)
                            MPI_Sendrecv(cl[haut]+sites,n,MPI_UNSIGNED_SHORT,1,haut+HEIGHT,
                                         cp[0][haut],n,MPI_UNSIGNED_SHORT,size-1,haut+HEIGHT,
                                         MPI_COMM_WORLD,&status);
                        if(p_rank == size-1)
                            MPI_Sendrecv(cl[haut]+sites,n,MPI_UNSIGNED_SHORT,0,haut+HEIGHT,
                                         cp[0][haut],n,MPI_UNSIGNED_SHORT,size-2,haut+HEIGHT,
                                         MPI_COMM_WORLD,&status);
                        if((p_rank) && (p_rank < size-1))
                            MPI_Sendrecv(cl[haut]+sites,n,MPI_UNSIGNED_SHORT,p_rank+1,haut+HEIGHT,
                                         cp[0][haut],n,MPI_UNSIGNED_SHORT,p_rank-1,haut+HEIGHT,
                                         MPI_COMM_WORLD,&status);
                    }
                }
                
                void MPI_ShareTreefall(unsigned short **c, int n) {
                    
                    MPI_Status status;
                    if(p_rank == 0)
                        MPI_Sendrecv(c[0],n,MPI_UNSIGNED_SHORT,size-1,0,
                                     c[2],n,MPI_UNSIGNED_SHORT,1,0,MPI_COMM_WORLD,&status);
                    if(p_rank == size-1)
                        MPI_Sendrecv(c[0],n,MPI_UNSIGNED_SHORT,size-2,0,
                                     c[2],n,MPI_UNSIGNED_SHORT,0,0,MPI_COMM_WORLD,&status);
                    if((p_rank) && (p_rank < size-1))
                        MPI_Sendrecv(c[0],n,MPI_UNSIGNED_SHORT,p_rank-1,0,
                                     c[2],n,MPI_UNSIGNED_SHORT,p_rank+1,0,MPI_COMM_WORLD,&status);
                    
                    if(p_rank == 0)
                        MPI_Sendrecv(c[0]+2*n,n,MPI_UNSIGNED_SHORT,1,1,
                                     c[1],n,MPI_UNSIGNED_SHORT,size-1,1,MPI_COMM_WORLD,&status);
                    if(p_rank == size-1)
                        MPI_Sendrecv(c[0]+2*n,n,MPI_UNSIGNED_SHORT,0,1,
                                     c[1],n,MPI_UNSIGNED_SHORT,size-2,1,MPI_COMM_WORLD,&status);
                    if((p_rank) && (p_rank < size-1))
                        MPI_Sendrecv(c[0]+2*n,n,MPI_UNSIGNED_SHORT,p_rank+1,1,
                                     c[1],n,MPI_UNSIGNED_SHORT,p_rank-1,1,MPI_COMM_WORLD,&status);
                }
                
                #endif
                
                
                
                /******************************************
                 ******************************************
                 *******  Free dynamic memory  ************
                 ******************************************
                 ******************************************/
                
           1 -> void FreeMem () {
                    
           1 ->     delete [] T;
           1 ->     delete [] S;
           1 ->     delete [] nbdbh;
           1 ->     delete [] layer;
           1 ->     delete [] SPECIES_GERM;
           1 ->     if(_SEEDTRADEOFF){
           1 ->         delete [] PROB_S;
                    }
                    
           1 ->     if(_NDD){
           1 ->         delete [] PROB_S;
                    }
                    
                    int h;
           1 ->     for (h=0; h<(HEIGHT+1); h++) {
           1 ->         delete [] LAI3D[h];
                    }
           1 ->     delete [] LAI3D;
                    
                    int i;
           1 ->     for (i=0; i<3; i++) {
           1 ->         delete [] Thurt[i];
                    }
           1 -> }
                
                
                /***********************************
                 ***********************************
                 ***** RANDOM NUMBER GENERATOR *****
                 ***********************************
                 ***********************************/
                
                /* Copyright (C) 1997 Makoto Matsumoto and Takuji Nishimura.       */
                /* When you use this, send an email to: matumoto@math.keio.ac.jp   */
                /* with an appropriate reference to your work.                     */
                
                //#include<stdio.h>
                
                /* Period parameters */
                #define N 624
                #define M 397
                #define MATRIX_A 0x9908b0df   /* constant vector a */
                #define UPPER_MASK 0x80000000 /* most significant w-r bits */
                #define LOWER_MASK 0x7fffffff /* least significant r bits */
                
                /* Tempering parameters */
                #define TEMPERING_MASK_B 0x9d2c5680
                #define TEMPERING_MASK_C 0xefc60000
                #define TEMPERING_SHIFT_U(y)  (y >> 11)
                #define TEMPERING_SHIFT_S(y)  (y << 7)
                #define TEMPERING_SHIFT_T(y)  (y << 15)
                #define TEMPERING_SHIFT_L(y)  (y >> 18)
                
                static unsigned long mt[N]; /* the array for the state vector  */
                static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */
                
                /* initializing the array with a NONZERO seed */
                void sgenrand2(unsigned long seed)
           1 -> {
                    /* setting initial seeds to mt[N] using         */
                    /* the generator Line 25 of Table 1 in          */
                    /* [KNUTH 1981, The Art of Computer Programming */
                    /*    Vol. 2 (2nd Ed.), pp102]                  */
           1 ->     mt[0]= seed & 0xffffffff;
           1 ->     for (mti=1; mti<N; mti++)
           1 ->         mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;
           1 -> }
                
                /* generating reals */
                /* unsigned long */ /* for integer generation */
                double genrand2()
  2339055096 -> {
                    unsigned long y;
                    static unsigned long mag01[2]={0x0, MATRIX_A};
                    /* mag01[x] = x * MATRIX_A  for x=0,1 */
                    
  2339055096 ->     if (mti >= N) { /* generate N words at one time */
                        int kk;
                        
  2339055096 ->         if (mti == N+1)   /* if sgenrand() has not been called, */
  2339055096 ->             sgenrand2(4357); /* a default initial seed is used   */
                        
  2339055096 ->         for (kk=0;kk<N-M;kk++) {
  2339055096 ->             y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
  2339055096 ->             mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
                        }
  2339055096 ->         for (;kk<N-1;kk++) {
  2339055096 ->             y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
  2339055096 ->             mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1];
                        }
  2339055096 ->         y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
  2339055096 ->         mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1];
                        
  2339055096 ->         mti = 0;
                    }
                    
  2339055096 ->     y = mt[mti++];
  2339055096 ->     y ^= TEMPERING_SHIFT_U(y);
  2339055096 ->     y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
  2339055096 ->     y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
  2339055096 ->     y ^= TEMPERING_SHIFT_L(y);
                    
  2339055096 ->     return ( (double)y / (unsigned long)0xffffffff ); /* reals */
                    /* return y; */ /* for integer generation */
  2339055096 -> }
                
                
                /* initializing the array with a NONZERO seed */
                void sgenrand2i(unsigned long seed)
           1 -> {
                    /* setting initial seeds to mt[N] using         */
                    /* the generator Line 25 of Table 1 in          */
                    /* [KNUTH 1981, The Art of Computer Programming */
                    /*    Vol. 2 (2nd Ed.), pp102]                  */
           1 ->     mt[0]= seed & 0xffffffff;
           1 ->     for (mti=1; mti<N; mti++)
           1 ->         mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;
           1 -> }
                
                unsigned long genrand2i()
   504078704 -> {
                    unsigned long y;
                    static unsigned long mag01[2]={0x0, MATRIX_A};
                    /* mag01[x] = x * MATRIX_A  for x=0,1 */
                    
   504078704 ->     if (mti >= N) { /* generate N words at one time */
                        int kk;
                        
   504078704 ->         if (mti == N+1)   /* if sgenrand() has not been called, */
   504078704 ->             sgenrand2i(4357); /* a default initial seed is used   */
                        
   504078704 ->         for (kk=0;kk<N-M;kk++) {
   504078704 ->             y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
   504078704 ->             mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
                        }
   504078704 ->         for (;kk<N-1;kk++) {
   504078704 ->             y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
   504078704 ->             mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1];
                        }
   504078704 ->         y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
   504078704 ->         mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1];
                        
   504078704 ->         mti = 0;
                    }
                    
   504078704 ->     y = mt[mti++];
   504078704 ->     y ^= TEMPERING_SHIFT_U(y);
   504078704 ->     y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
   504078704 ->     y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
   504078704 ->     y ^= TEMPERING_SHIFT_L(y);
                    
   504078704 ->     return y;
   504078704 -> }
                
                
                /***********************************
                 ***********************************
                 ********** TROLL TOOLBOX **********
                 ***********************************
                 ***********************************/
                
                
                /* This section includes variations of TROLL procedures that could be used interchangeably with already existing procedures */
                /* For reasons of readability (syntax highlighting) these sections are kept within a "toolbox" flag instead of commenting them out */
                /* some of them could also be included as boolean options --> to be discussed */
                
                #ifdef toolbox
                
                /***********************************
                 ************ FINE FLUX ************
                 ***********************************/
                
                /* This is an an alternative version of the flux calculations */
                /* main idea: remove extremely productive top layers of trees that block entire photosynthesis in lower layers
                 * and smear out the effect in a number of finer layers (nb_layers, here chosen to be five) */
                /* be aware: performance cost */
                
                float Tree::Fluxh(int h) {
                    int count = 0,
                    xx, yy, radius_int,
                    nb_layers = 5;                                                   // number of layers for fine resolution of flux
                    t_VPD = 0;
                    t_T = 0;
                    float absorb = 0.0, flux = 0.0;
                    float absorb_highres = 0.0, flux_highres = 0.0, VPD_highres = 0.0, T_highres = 0.0,
                    inb_layers = 1.0 / nb_layers;
                    radius_int = int(t_Crown_Radius);
                
                    if(radius_int == 0) {
                        count = 1;
                        if (h >= HEIGHT) {
                            absorb = 0;
                            flux = exp(- absorb * klight);
                        }
                        else {
                            absorb = LAI3D[h][t_site+SBORD];                              //calculate the absorption to which fine layers will be added
                            
                            if (h == 0) flux = exp(- absorb * klight);
                            else{
                                // spread out LAI over x differentlayers within voxel (assumption: leaf layer every 1/x m, uniform distribution)
                                absorb_highres = (LAI3D[h-1][t_site+SBORD] - LAI3D[h][t_site+SBORD]) * inb_layers;
                                
                                // PROCESS: calculate highly resolved fluxed for every layer within voxel
                                // important: multiplication of absorb with factor i corresponds to gradually increasing optical thickness (LAD)
                                // important: layers have to be added to LAI3D above
                                for(int i = 0; i < nb_layers; i ++){
                                    flux_highres += exp(-(absorb + i * absorb_highres) * klight);
                                    VPD_highres += 0.25 + sqrt(maxf(0.0 , 0.08035714 * (7 - (absorb + i * absorb_highres))));
                                    // this expressions results from fit of observations of relationships between VPD and height within dense canopy (HOBO data on COPAS tower, Shuttleworth et al 1985; Camargo & Kapos 1995 journal of Tropical Ecology)
                                    T_highres += tmax - 0.4285714 * (minf(7,(absorb + i * absorb_highres)));
                                    // 0.4285714=3/7, assuming deltaT between the top canopy and dense understorey is constant = 3°C, could be refined.
                                }
                                flux = flux_highres * inb_layers;
                                t_VPD = VPD_highres * inb_layers;
                                t_T = T_highres * inb_layers;
                            }
                        }
                    }
                    else {
                        int row0, col0;
                        row0 = t_site / cols;
                        col0 = t_site % cols;
                        for(int col = max(0, col0-radius_int); col < min(cols, col0+radius_int+1); col ++) {
                            for(int row = max(0, row0-radius_int); row < min(rows, row0+radius_int+1); row ++) {                     //loop over the tree crown
                                xx = col0 - col;
                                yy = row0 - row;
                                if(xx*xx + yy*yy <= radius_int*radius_int) {                                                  //is the voxel within crown?
                                    flux_highres = 0.0;
                                    VPD_highres = 0.0;
                                    T_highres = 0.0;
                                    count ++;
                                    if (h >= HEIGHT) {
                                        absorb = 0;
                                        flux += exp(-absorb*klight);
                                        t_VPD += 0.25 + sqrt(maxf(0.0 , 0.08035714*(7-absorb)));
                                        t_T += tmax - 0.4285714*(minf(7,absorb));
                                    }
                                    else {
                                        absorb = LAI3D[h][col+cols*row+SBORD];                              //calculate the absorption that will need to be added to fine layers
                                        
                                        if(h==0) flux += exp(-absorb*klight);
                                        else{
                                            // spread out LAI over x differentlayers within voxel (assumption: leaf layer every 1/x m, uniform distribution)
                                            absorb_highres = (LAI3D[h-1][col+cols*row+SBORD]-LAI3D[h][col+cols*row+SBORD])*inb_layers;
                                            
                                            // PROCESS: calculate highly resolved flux for every layer within voxel
                                            // important: multiplication of absorb with factor i corresponds to gradually increasing optical thickness (LAD)
                                            // important: layers have to be added to LAI3D above (absorb)
                                            for(int i = 0; i < nb_layers; i ++){
                                                flux_highres += exp(-(absorb+i*absorb_highres)*klight);
                                                VPD_highres += 0.25+sqrt(maxf(0.0 , 0.08035714*(7-(absorb+i*absorb_highres))));
                                                T_highres += tmax-0.4285714*(minf(7,(absorb+i*absorb_highres)));
                                            }
                                            flux_highres = flux_highres * inb_layers;
                                            VPD_highres = VPD_highres * inb_layers;
                                            T_highres = T_highres * inb_layers;
                                            t_VPD += VPD_highres;
                                            t_T += T_highres;
                                            flux += flux_highres;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    flux *= Wmax / float(count);
                    t_VPD *= VPDmax / float(count);
                    t_T *= 1 / float(count);
                    
                    return flux;
                }
                
                #endif
                


Top 10 Lines:

     Line      Count

      851 35938166619
      354 11780403896
      350 5899500952
      358 4730107229
     3471 2339055096
      906 1500806301
     1269 1500806301
     1202  960000000
     1571  960000000
     1715  960000000

Execution Summary:

     1266   Executable lines in this file
     1266   Lines executed
   100.00   Percent of the file executed

71658622931   Total number of line executions
56602387.78   Average executions per line
