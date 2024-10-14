/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_POOL_HPP
#define NSL_POOL_HPP

# include "SmartPtr.hpp"
# include "IsSubclassOf.hpp"
# include <memory>
# include <deque>
# include <iostream>

class Pool final
{
public:
	Pool();
	template <typename ... TArgs>
	Pool(const TArgs& ...args);
	~Pool();

public:
	class BaseObject
	{
	public: 
		virtual ~BaseObject() = default;
	}; 

	template <typename TObj>
	class Object final : public BaseObject
	{
	public:
		Object(const TObj& addConstRef);
		~Object() override = default;

		operator TObj();

	private:
		TObj	obj;
	};

public:
	template <typename T>
	void	Add(const T& ref);

	void	RemoveAt(int&& index);
	void	RemoveAt(const int& index);
	void	Release(void);

	int		Size(void);
	bool	IsEmpty(void);

	template <typename T, typename ... TArgs>
	Pool::Object<T>&	Acquire(TArgs&& ...p_args);
	template <typename T>
	Pool::Object<T>&	Acquire(void);
	template <typename T>
	Pool::Object<T>*	At(unsigned int&& index);
	template <typename T>
	Pool::Object<T>*	At(const unsigned int& index);

private:
	std::deque<
		SmartPtr<Pool::BaseObject>>	objects;
	int								size;
	bool							deleted = false;
};

# include "template/Pool.inl"
#endif
