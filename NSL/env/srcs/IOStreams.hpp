/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_IOSTREAMS_HPP
#define NSL_IOSTREAMS_HPP

# include "String.hpp"
# include "../platform.h"
# include <cstring>
# include <unistd.h>

namespace IO
{
class Streams
{
public:
	Streams()							noexcept;
	Streams(const Streams& s)			noexcept;

	FORCEINLINE const String&	GetStockedText() const noexcept
	{
		return (this->text);
	}
	FORCEINLINE void				ClearStockedText() noexcept
	{
		this->text.Clear();
	}

	static void	__keep__(Streams& s)	noexcept;
	static void	__save__(Streams& s)	noexcept;
	static void	__reset__(Streams& s)	noexcept;
	static void __clear__(Streams& s)	noexcept;
	static void	__flush__(Streams& s)	noexcept;

private:
	String		text;
	bool		keep;
	bool		save;

public:

	/********/
	/*	>>	*/
	/********/

	friend Streams& operator>>(Streams& begin, char& cbuffer)
	{
		read(STDIN_FILENO, &cbuffer, 1);
		return (begin);
	}

	/********/
	/*	<<	*/
	/********/

	friend Streams&	operator<<(Streams& begin, const String& text)
	{
		if (begin.keep || begin.save)
			begin.text.Join(text);
		if (!begin.keep)
			write(STDOUT_FILENO, text.Data(), text.Len());
		return (begin);
	}

	friend Streams&	operator<<(Streams& begin, const char* c)
	{
		if (begin.keep || begin.save)
			begin.text.Join(c);
		if (!begin.keep)
			write(STDOUT_FILENO, c, String::Len(c));
		return (begin);
	}

	friend Streams&	operator<<(Streams& begin, const char& c)
	{
		if (begin.keep || begin.save)
			begin.text.Join(&c);
		if (!begin.keep)
			write(STDOUT_FILENO, &c, 1);
		return (begin);
	}

	friend Streams&	operator<<(Streams& begin, const short& integer)
	{
		String	str = std::to_string(integer);
		if (begin.keep || begin.save)
			begin.text.Join(str);
		if (!begin.keep)
			write(STDOUT_FILENO, str.Data(), str.Len());
		return (begin);
	}

	friend Streams&	operator<<(Streams& begin, const int& integer)
	{
		String	str = std::to_string(integer);
		if (begin.keep || begin.save)
			begin.text.Join(str);
		if (!begin.keep)
			write(STDOUT_FILENO, str.Data(), str.Len());
		return (begin);
	}

	friend Streams&	operator<<(Streams& begin, const long& integer)
	{
		String	str = std::to_string(integer);
		if (begin.keep || begin.save)
			begin.text.Join(str);
		if (!begin.keep)
			write(STDOUT_FILENO, str.Data(), str.Len());
		return (begin);
	}

	friend Streams&	operator<<(Streams& begin, const float& integer)
	{
		String	str = std::to_string(integer);
		if (begin.keep || begin.save)
			begin.text.Join(str);
		if (!begin.keep)
			write(STDOUT_FILENO, str.Data(), str.Len());
		return (begin);
	}

	friend Streams&	operator<<(Streams& begin, const double& integer)
	{
		String	str = std::to_string(integer);
		if (begin.keep || begin.save)
			begin.text.Join(str);
		if (!begin.keep)
			write(STDOUT_FILENO, str.Data(), str.Len());
		return (begin);
	}

	friend Streams&	operator<<(Streams& begin, void (*streams_fn)(Streams& s))
	{
		streams_fn(begin);
		return (begin);
	}
};

thread_local extern Streams		Stream;
thread_local extern Streams&	Echo;
thread_local extern Streams&	Fetch;
thread_local extern void (*KeepMode)(Streams&);
thread_local extern void (*SaveMode)(Streams&);
thread_local extern void (*ResetMode)(Streams&);
thread_local extern void (*Clear)(Streams&);
thread_local extern void (*Flush)(Streams&);

}

/* UTILISATION EXEMPLE :

	IO::Stream << "Bonjour je suis le Pape François III!" << IO::SaveMode/IO::KeepMode << "MOUAHAHA";
	IO::Stream << IO::ResetMode;
	IO::Stream << "Big ez";
	IO::Stream << IO::Flush;
*/

#endif
