//
// DynamicAnyHolder.h
//
// $Id: //poco/Main/Foundation/include/Poco/DynamicAnyHolder.h#2 $
//
// Library: Poco
// Package: Core
// Module:  DynamicAnyHolder
//
// Definition of the DynamicAnyHolder class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Poco_DynamicAnyHolder_INCLUDED
#define Poco_DynamicAnyHolder_INCLUDED


#include "Poco/Poco.h"
#include "Poco/NumberFormatter.h"
#include "Poco/NumberParser.h"
#include "Poco/String.h"
#include "Poco/Exception.h"
#include <typeinfo>


namespace Poco {


class Foundation_API DynamicAnyHolder
	/// Interface for a data holder used by the DynamicAny class. Provides methods to convert between data types.
	/// Only data types for which a convert method exists are supported, which are
	/// all C++ built-in types, along with std::string.
{
public:
	DynamicAnyHolder();
		/// Creates the DynamicAnyHolder.

	virtual ~DynamicAnyHolder();
		/// Destroys the DynamicAnyHolder.

	virtual DynamicAnyHolder* clone() const = 0;
		/// Deep-copies the DynamicAnyHolder.
		
	virtual const std::type_info& type() const = 0;
		/// Returns the type information of the stored content.

	virtual void convert(Int8& val) const = 0;
	virtual void convert(Int16& val) const = 0;
	virtual void convert(Int32& val) const = 0;
	virtual void convert(Int64& val) const = 0;
	virtual void convert(UInt8& val) const = 0;
	virtual void convert(UInt16& val) const = 0;
	virtual void convert(UInt32& val) const = 0;
	virtual void convert(UInt64& val) const = 0;

#ifndef POCO_LONG_IS_64_BIT
	void convert(long& val) const;
	void convert(unsigned long& val) const;
#endif

	virtual void convert(bool& val) const = 0;
	virtual void convert(float& val) const = 0;
	virtual void convert(double& val) const = 0;
	virtual void convert(char& val) const = 0;
	virtual void convert(std::string& val) const = 0;
};


//
// inlines
//
#ifndef POCO_LONG_IS_64_BIT
inline void DynamicAnyHolder::convert(long& val) const
{
	Int32 tmp;
	convert(tmp);
	val = tmp;
}


inline void DynamicAnyHolder::convert(unsigned long& val) const
{
	UInt32 tmp;
	convert(tmp);
	val = tmp;
}
#endif


template <typename T>
class DynamicAnyHolderImpl: public DynamicAnyHolder
	/// Template based implementation of a DynamicAnyHolder. 
	/// Conversion work happens in the template specializations of this class.
	///
	/// DynamicAny can be used for any type for which a specialization for
	/// DynamicAnyHolderImpl is available.
{
	DynamicAnyHolderImpl()
	{
	}

	~DynamicAnyHolderImpl()
	{
	}
	
	const std::type_info& type() const
	{
		return typeid(T);
	}

	void convert(Int8&) const
	{
		throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
	}

	void convert(Int16&) const
	{
		throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
	}

	void convert(Int32&) const
	{
		throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
	}

	void convert(Int64&) const
	{
		throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
	}
	
	void convert(UInt8&) const
	{
		throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
	}

	void convert(UInt16&) const
	{
		throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
	}

	void convert(UInt32&) const
	{
		throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
	}

	void convert(UInt64&) const
	{
		throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
	}

	void convert(bool& val) const
	{
		throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
	}

	void convert(float& val) const
	{
		throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
	}

	void convert(double& val) const
	{
		throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
	}

	void convert(char& val) const
	{
		throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
	}

	void convert(std::string&) const
	{
		throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
	}

	DynamicAnyHolder* clone() const
	{
		throw NotImplementedException("No DynamicAnyHolder specialization for type", typeid(T).name());
	}
};



template <>
class DynamicAnyHolderImpl<Int8>: public DynamicAnyHolder
{
public:
	DynamicAnyHolderImpl(Int8 val): _val(val)
	{
	}

	~DynamicAnyHolderImpl()
	{
	}
	
	const std::type_info& type() const
	{
		return typeid(Int8);
	}

	void convert(Int8& val) const
	{
		val = _val;
	}

	void convert(Int16& val) const
	{
		val = _val;
	}
	
	void convert(Int32& val) const
	{
		val = _val;
	}

	void convert(Int64& val) const
	{
		val = _val;
	}

	void convert(UInt8& val) const
	{
		val = static_cast<UInt8>(_val);
	}

	void convert(UInt16& val) const
	{
		val = static_cast<UInt16>(_val);
	}
	
	void convert(UInt32& val) const
	{
		val = static_cast<UInt32>(_val);
	}

	void convert(UInt64& val) const
	{
		val = static_cast<UInt64>(_val);
	}

	void convert(bool& val) const
	{
		val = (_val != 0);
	}

	void convert(float& val) const
	{
		val = static_cast<float>(_val);
	}

	void convert(double& val) const
	{
		val = static_cast<double>(_val);
	}

	void convert(char& val) const
	{
		val = static_cast<char>(_val);
	}

	void convert(std::string& val) const
	{
		val = NumberFormatter::format(_val);
	}

	DynamicAnyHolder* clone() const
	{
		return new DynamicAnyHolderImpl(_val);
	}

private:
	Int8 _val;
};



template <>
class DynamicAnyHolderImpl<Int16>: public DynamicAnyHolder
{
public:
	DynamicAnyHolderImpl(Int16 val): _val(val)
	{
	}

	~DynamicAnyHolderImpl()
	{
	}
	
	const std::type_info& type() const
	{
		return typeid(Int16);
	}

	void convert(Int8& val) const
	{
		val = static_cast<Int8>(_val);
	}

	void convert(Int16& val) const
	{
		val = _val;
	}
	
	void convert(Int32& val) const
	{
		val = _val;
	}

	void convert(Int64& val) const
	{
		val = _val;
	}

	void convert(UInt8& val) const
	{
		val = static_cast<UInt8>(_val);
	}

	void convert(UInt16& val) const
	{
		val = static_cast<UInt16>(_val);
	}
	
	void convert(UInt32& val) const
	{
		val = static_cast<UInt32>(_val);
	}

	void convert(UInt64& val) const
	{
		val = static_cast<UInt64>(_val);
	}

	void convert(bool& val) const
	{
		val = (_val != 0);
	}

	void convert(float& val) const
	{
		val = static_cast<float>(_val);
	}

	void convert(double& val) const
	{
		val = static_cast<double>(_val);
	}

	void convert(char& val) const
	{
		val = static_cast<char>(_val);
	}

	void convert(std::string& val) const
	{
		val = NumberFormatter::format(_val);
	}

	DynamicAnyHolder* clone() const
	{
		return new DynamicAnyHolderImpl(_val);
	}

private:
	Int16 _val;
};


template <>
class DynamicAnyHolderImpl<Int32>: public DynamicAnyHolder
{
public:
	DynamicAnyHolderImpl(Int32 val): _val(val)
	{
	}

	~DynamicAnyHolderImpl()
	{
	}

	const std::type_info& type() const
	{
		return typeid(Int32);
	}

	void convert(Int8& val) const
	{
		val = static_cast<Int8>(_val);
	}

	void convert(Int16& val) const
	{
		val = static_cast<Int16>(_val);
	}
	
	void convert(Int32& val) const
	{
		val = _val;
	}

	void convert(Int64& val) const
	{
		val = _val;
	}

	void convert(UInt8& val) const
	{
		val = static_cast<UInt8>(_val);
	}

	void convert(UInt16& val) const
	{
		val = static_cast<UInt16>(_val);
	}
	
	void convert(UInt32& val) const
	{
		val = static_cast<UInt32>(_val);
	}

	void convert(UInt64& val) const
	{
		val = static_cast<UInt64>(_val);
	}

	void convert(bool& val) const
	{
		val = (_val != 0);
	}

	void convert(float& val) const
	{
		val = static_cast<float>(_val);
	}

	void convert(double& val) const
	{
		val = static_cast<double>(_val);
	}

	void convert(char& val) const
	{
		val = static_cast<char>(_val);
	}

	void convert(std::string& val) const
	{
		val = NumberFormatter::format(_val);
	}

	DynamicAnyHolder* clone() const
	{
		return new DynamicAnyHolderImpl(_val);
	}

private:
	Int32 _val;
};


template <>
class DynamicAnyHolderImpl<Int64>: public DynamicAnyHolder
{
public:
	DynamicAnyHolderImpl(Int64 val): _val(val)
	{
	}

	~DynamicAnyHolderImpl()
	{
	}

	const std::type_info& type() const
	{
		return typeid(Int64);
	}

	void convert(Int8& val) const
	{
		val = static_cast<Int8>(_val);
	}

	void convert(Int16& val) const
	{
		val = static_cast<Int16>(_val);
	}
	
	void convert(Int32& val) const
	{
		val = static_cast<Int32>(_val);
	}

	void convert(Int64& val) const
	{
		val = _val;
	}

	void convert(UInt8& val) const
	{
		val = static_cast<UInt8>(_val);
	}

	void convert(UInt16& val) const
	{
		val = static_cast<UInt16>(_val);
	}
	
	void convert(UInt32& val) const
	{
		val = static_cast<UInt32>(_val);
	}

	void convert(UInt64& val) const
	{
		val = static_cast<UInt64>(_val);
	}

	void convert(bool& val) const
	{
		val = (_val != 0);
	}

	void convert(float& val) const
	{
		val = static_cast<float>(_val);
	}

	void convert(double& val) const
	{
		val = static_cast<double>(_val);
	}

	void convert(char& val) const
	{
		val = static_cast<char>(_val);
	}

	void convert(std::string& val) const
	{
		val = NumberFormatter::format(_val);
	}

	DynamicAnyHolder* clone() const
	{
		return new DynamicAnyHolderImpl(_val);
	}

private:
	Int64 _val;
};


template <>
class DynamicAnyHolderImpl<UInt8>: public DynamicAnyHolder
{
public:
	DynamicAnyHolderImpl(UInt8 val): _val(val)
	{
	}

	~DynamicAnyHolderImpl()
	{
	}
	
	const std::type_info& type() const
	{
		return typeid(UInt8);
	}

	void convert(Int8& val) const
	{
		val = static_cast<Int8>(_val);
	}

	void convert(Int16& val) const
	{
		val = static_cast<Int16>(_val);
	}
	
	void convert(Int32& val) const
	{
		val = static_cast<Int32>(_val);
	}

	void convert(Int64& val) const
	{
		val = static_cast<Int64>(_val);
	}

	void convert(UInt8& val) const
	{
		val = _val;
	}

	void convert(UInt16& val) const
	{
		val = _val;
	}
	
	void convert(UInt32& val) const
	{
		val = _val;
	}

	void convert(UInt64& val) const
	{
		val = _val;
	}

	void convert(bool& val) const
	{
		val = (_val != 0);
	}

	void convert(float& val) const
	{
		val = static_cast<float>(_val);
	}

	void convert(double& val) const
	{
		val = static_cast<double>(_val);
	}

	void convert(char& val) const
	{
		val = static_cast<char>(_val);
	}

	void convert(std::string& val) const
	{
		val = NumberFormatter::format(_val);
	}

	DynamicAnyHolder* clone() const
	{
		return new DynamicAnyHolderImpl(_val);
	}

private:
	UInt8 _val;
};


template <>
class DynamicAnyHolderImpl<UInt16>: public DynamicAnyHolder
{
public:
	DynamicAnyHolderImpl(UInt16 val): _val(val)
	{
	}

	~DynamicAnyHolderImpl()
	{
	}

	const std::type_info& type() const
	{
		return typeid(UInt16);
	}

	void convert(Int8& val) const
	{
		val = static_cast<Int8>(_val);
	}

	void convert(Int16& val) const
	{
		val = static_cast<Int16>(_val);
	}
	
	void convert(Int32& val) const
	{
		val = static_cast<Int32>(_val);
	}

	void convert(Int64& val) const
	{
		val = static_cast<Int64>(_val);
	}

	void convert(UInt8& val) const
	{
		val = static_cast<UInt8>(_val);
	}

	void convert(UInt16& val) const
	{
		val = _val;
	}
	
	void convert(UInt32& val) const
	{
		val = _val;
	}

	void convert(UInt64& val) const
	{
		val = _val;
	}

	void convert(bool& val) const
	{
		val = (_val != 0);
	}

	void convert(float& val) const
	{
		val = static_cast<float>(_val);
	}

	void convert(double& val) const
	{
		val = static_cast<double>(_val);
	}

	void convert(char& val) const
	{
		val = static_cast<char>(_val);
	}

	void convert(std::string& val) const
	{
		val = NumberFormatter::format(_val);
	}

	DynamicAnyHolder* clone() const
	{
		return new DynamicAnyHolderImpl(_val);
	}

private:
	UInt16 _val;
};


template <>
class DynamicAnyHolderImpl<UInt32>: public DynamicAnyHolder
{
public:
	DynamicAnyHolderImpl(UInt32 val): _val(val)
	{
	}

	~DynamicAnyHolderImpl()
	{
	}

	const std::type_info& type() const
	{
		return typeid(UInt32);
	}

	void convert(Int8& val) const
	{
		val = static_cast<Int8>(_val);
	}

	void convert(Int16& val) const
	{
		val = static_cast<Int16>(_val);
	}
	
	void convert(Int32& val) const
	{
		val = static_cast<Int32>(_val);
	}

	void convert(Int64& val) const
	{
		val = static_cast<Int64>(_val);
	}

	void convert(UInt8& val) const
	{
		val = static_cast<UInt8>(_val);
	}

	void convert(UInt16& val) const
	{
		val = static_cast<UInt16>(_val);
	}
	
	void convert(UInt32& val) const
	{
		val = _val;
	}

	void convert(UInt64& val) const
	{
		val = _val;
	}

	void convert(bool& val) const
	{
		val = (_val != 0);
	}

	void convert(float& val) const
	{
		val = static_cast<float>(_val);
	}

	void convert(double& val) const
	{
		val = static_cast<double>(_val);
	}

	void convert(char& val) const
	{
		val = static_cast<char>(_val);
	}

	void convert(std::string& val) const
	{
		val = NumberFormatter::format(_val);
	}

	DynamicAnyHolder* clone() const
	{
		return new DynamicAnyHolderImpl(_val);
	}

private:
	UInt32 _val;
};


template <>
class DynamicAnyHolderImpl<UInt64>: public DynamicAnyHolder
{
public:
	DynamicAnyHolderImpl(UInt64 val): _val(val)
	{
	}

	~DynamicAnyHolderImpl()
	{
	}

	const std::type_info& type() const
	{
		return typeid(UInt64);
	}

	void convert(Int8& val) const
	{
		val = static_cast<Int8>(_val);
	}

	void convert(Int16& val) const
	{
		val = static_cast<Int16>(_val);
	}
	
	void convert(Int32& val) const
	{
		val = static_cast<Int32>(_val);
	}

	void convert(Int64& val) const
	{
		val = static_cast<Int64>(_val);
	}

	void convert(UInt8& val) const
	{
		val = static_cast<UInt8>(_val);
	}

	void convert(UInt16& val) const
	{
		val = static_cast<UInt16>(_val);
	}
	
	void convert(UInt32& val) const
	{
		val = static_cast<UInt32>(_val);
	}

	void convert(UInt64& val) const
	{
		val = _val;
	}

	void convert(bool& val) const
	{
		val = (_val != 0);
	}

	void convert(float& val) const
	{
		val = static_cast<float>(_val);
	}

	void convert(double& val) const
	{
		val = static_cast<double>(_val);
	}

	void convert(char& val) const
	{
		val = static_cast<char>(_val);
	}

	void convert(std::string& val) const
	{
		val = NumberFormatter::format(_val);
	}

	DynamicAnyHolder* clone() const
	{
		return new DynamicAnyHolderImpl(_val);
	}

private:
	UInt64 _val;
};


template <>
class DynamicAnyHolderImpl<bool>: public DynamicAnyHolder
{
public:
	DynamicAnyHolderImpl(bool val): _val(val)
	{
	}

	~DynamicAnyHolderImpl()
	{
	}

	const std::type_info& type() const
	{
		return typeid(bool);
	}

	void convert(Int8& val) const
	{
		val = static_cast<Int8>(_val ? 1 : 0);
	}

	void convert(Int16& val) const
	{
		val = static_cast<Int16>(_val ? 1 : 0);
	}
	
	void convert(Int32& val) const
	{
		val = static_cast<Int32>(_val ? 1 : 0);
	}

	void convert(Int64& val) const
	{
		val = static_cast<Int64>(_val ? 1 : 0);
	}

	void convert(UInt8& val) const
	{
		val = static_cast<UInt8>(_val ? 1 : 0);
	}

	void convert(UInt16& val) const
	{
		val = static_cast<UInt16>(_val ? 1 : 0);
	}
	
	void convert(UInt32& val) const
	{
		val = static_cast<UInt32>(_val ? 1 : 0);
	}

	void convert(UInt64& val) const
	{
		val = static_cast<UInt64>(_val ? 1 : 0);
	}

	void convert(bool& val) const
	{
		val = _val;
	}

	void convert(float& val) const
	{
		val = (_val ? 1.0f : 0.0f);
	}

	void convert(double& val) const
	{
		val = (_val ? 1.0 : 0.0);
	}

	void convert(char& val) const
	{
		val = static_cast<char>(_val ? 1 : 0);
	}

	void convert(std::string& val) const
	{
		val = (_val ? "true" : "false");
	}

	DynamicAnyHolder* clone() const
	{
		return new DynamicAnyHolderImpl(_val);
	}

private:
	bool _val;
};


template <>
class DynamicAnyHolderImpl<float>: public DynamicAnyHolder
{
public:
	DynamicAnyHolderImpl(float val): _val(val)
	{
	}

	~DynamicAnyHolderImpl()
	{
	}

	const std::type_info& type() const
	{
		return typeid(float);
	}

	void convert(Int8& val) const
	{
		val = static_cast<Int8>(_val);
	}

	void convert(Int16& val) const
	{
		val = static_cast<Int16>(_val);
	}
	
	void convert(Int32& val) const
	{
		val = static_cast<Int32>(_val);
	}

	void convert(Int64& val) const
	{
		val = static_cast<Int64>(_val);
	}

	void convert(UInt8& val) const
	{
		val = static_cast<UInt8>(_val);
	}

	void convert(UInt16& val) const
	{
		val = static_cast<UInt16>(_val);
	}
	
	void convert(UInt32& val) const
	{
		val = static_cast<UInt32>(_val);
	}

	void convert(UInt64& val) const
	{
		val = static_cast<UInt64>(_val);
	}

	void convert(bool& val) const
	{
		val = !(_val < 0.0001f && _val > -0.0001f);
	}

	void convert(float& val) const
	{
		val = _val;
	}

	void convert(double& val) const
	{
		val = _val;
	}

	void convert(char& val) const
	{
		val = static_cast<char>(_val);
	}

	void convert(std::string& val) const
	{
		val = NumberFormatter::format(_val);
	}

	DynamicAnyHolder* clone() const
	{
		return new DynamicAnyHolderImpl(_val);
	}

private:
	float _val;
};


template <>
class DynamicAnyHolderImpl<double>: public DynamicAnyHolder
{
public:
	DynamicAnyHolderImpl(double val): _val(val)
	{
	}

	~DynamicAnyHolderImpl()
	{
	}

	const std::type_info& type() const
	{
		return typeid(double);
	}

	void convert(Int8& val) const
	{
		val = static_cast<Int8>(_val);
	}

	void convert(Int16& val) const
	{
		val = static_cast<Int16>(_val);
	}
	
	void convert(Int32& val) const
	{
		val = static_cast<Int32>(_val);
	}

	void convert(Int64& val) const
	{
		val = static_cast<Int64>(_val);
	}

	void convert(UInt8& val) const
	{
		val = static_cast<UInt8>(_val);
	}

	void convert(UInt16& val) const
	{
		val = static_cast<UInt16>(_val);
	}
	
	void convert(UInt32& val) const
	{
		val = static_cast<UInt32>(_val);
	}

	void convert(UInt64& val) const
	{
		val = static_cast<UInt64>(_val);
	}

	void convert(bool& val) const
	{
		val = !(_val < 0.0001 && _val > -0.0001);
	}

	void convert(float& val) const
	{
		val = static_cast<float>(_val);
	}

	void convert(double& val) const
	{
		val = _val;
	}

	void convert(char& val) const
	{
		val = static_cast<char>(_val);
	}

	void convert(std::string& val) const
	{
		val = NumberFormatter::format(_val);
	}

	DynamicAnyHolder* clone() const
	{
		return new DynamicAnyHolderImpl(_val);
	}

private:
	double _val;
};


template <>
class DynamicAnyHolderImpl<char>: public DynamicAnyHolder
{
public:
	DynamicAnyHolderImpl(char val): _val(val)
	{
	}

	~DynamicAnyHolderImpl()
	{
	}

	const std::type_info& type() const
	{
		return typeid(char);
	}

	void convert(Int8& val) const
	{
		val = static_cast<Int8>(_val);
	}

	void convert(Int16& val) const
	{
		val = static_cast<Int16>(_val);
	}
	
	void convert(Int32& val) const
	{
		val = static_cast<Int32>(_val);
	}

	void convert(Int64& val) const
	{
		val = static_cast<Int64>(_val);
	}

	void convert(UInt8& val) const
	{
		val = static_cast<UInt8>(_val);
	}

	void convert(UInt16& val) const
	{
		val = static_cast<UInt16>(_val);
	}
	
	void convert(UInt32& val) const
	{
		val = static_cast<UInt32>(_val);
	}

	void convert(UInt64& val) const
	{
		val = static_cast<UInt64>(_val);
	}

	void convert(bool& val) const
	{
		val = (_val != '\0');
	}

	void convert(float& val) const
	{
		val = static_cast<float>(_val);
	}

	void convert(double& val) const
	{
		val = static_cast<double>(_val);
	}

	void convert(char& val) const
	{
		val = _val;
	}

	void convert(std::string& val) const
	{
		val = std::string(1, _val);
	}

	DynamicAnyHolder* clone() const
	{
		return new DynamicAnyHolderImpl(_val);
	}

private:
	char _val;
};


template <>
class DynamicAnyHolderImpl<std::string>: public DynamicAnyHolder
{
public:
	DynamicAnyHolderImpl(const char* pVal): _val(pVal)
	{
	}

	DynamicAnyHolderImpl(const std::string& val): _val(val)
	{
	}

	~DynamicAnyHolderImpl()
	{
	}

	const std::type_info& type() const
	{
		return typeid(std::string);
	}

	void convert(Int8& val) const
	{
		val = static_cast<Int8>(NumberParser::parse(_val));
	}

	void convert(Int16& val) const
	{
		val = static_cast<Int16>(NumberParser::parse(_val));
	}
	
	void convert(Int32& val) const
	{
		val = NumberParser::parse(_val);
	}

	void convert(Int64& val) const
	{
		val = NumberParser::parse64(_val);
	}

	void convert(UInt8& val) const
	{
		val = static_cast<UInt8>(NumberParser::parseUnsigned(_val));
	}

	void convert(UInt16& val) const
	{
		val = static_cast<UInt16>(NumberParser::parseUnsigned(_val));
	}
	
	void convert(UInt32& val) const
	{
		val = NumberParser::parseUnsigned(_val);
	}

	void convert(UInt64& val) const
	{
		val = NumberParser::parseUnsigned64(_val);
	}

	void convert(bool& val) const
	{
		static const std::string VAL_FALSE("false");
		static const std::string VAL_INTFALSE("0");

		if (_val == VAL_INTFALSE || (icompare(_val, VAL_FALSE) == 0))
			val = false;
		else
			val = true;
	}

	void convert(float& val) const
	{
		val = static_cast<float>(NumberParser::parseFloat(_val));
	}

	void convert(double& val) const
	{
		val = NumberParser::parseFloat(_val);
	}

	void convert(char& val) const
	{
		if (_val.empty())
			val = '\0';
		else
			val = _val[0];
	}

	void convert(std::string& val) const
	{
		val = _val;
	}

	DynamicAnyHolder* clone() const
	{
		return new DynamicAnyHolderImpl(_val);
	}

private:
	std::string _val;
};


#ifndef POCO_LONG_IS_64_BIT


template <>
class DynamicAnyHolderImpl<long>: public DynamicAnyHolder
{
public:
	DynamicAnyHolderImpl(long val): _val(val)
	{
	}

	~DynamicAnyHolderImpl()
	{
	}

	const std::type_info& type() const
	{
		return typeid(long);
	}

	void convert(Int8& val) const
	{
		val = static_cast<Int8>(_val);
	}

	void convert(Int16& val) const
	{
		val = static_cast<Int16>(_val);
	}
	
	void convert(Int32& val) const
	{
		val = static_cast<Int32>(_val);
	}

	void convert(Int64& val) const
	{
		val = static_cast<Int64>(_val);
	}

	void convert(UInt8& val) const
	{
		val = static_cast<UInt8>(_val);
	}

	void convert(UInt16& val) const
	{
		val = static_cast<UInt16>(_val);
	}
	
	void convert(UInt32& val) const
	{
		val = static_cast<UInt32>(_val);
	}

	void convert(UInt64& val) const
	{
		val = static_cast<UInt64>(_val);
	}

	void convert(bool& val) const
	{
		val = (_val != 0);
	}

	void convert(float& val) const
	{
		val = static_cast<float>(_val);
	}

	void convert(double& val) const
	{
		val = static_cast<double>(_val);
	}

	void convert(char& val) const
	{
		val = static_cast<char>(_val);
	}

	void convert(std::string& val) const
	{
		val = NumberFormatter::format(_val);
	}

	DynamicAnyHolder* clone() const
	{
		return new DynamicAnyHolderImpl(_val);
	}

private:
	long _val;
};


template <>
class DynamicAnyHolderImpl<unsigned long>: public DynamicAnyHolder
{
public:
	DynamicAnyHolderImpl(unsigned long val): _val(val)
	{
	}

	~DynamicAnyHolderImpl()
	{
	}

	const std::type_info& type() const
	{
		return typeid(unsigned long);
	}

	void convert(Int8& val) const
	{
		val = static_cast<Int8>(_val);
	}

	void convert(Int16& val) const
	{
		val = static_cast<Int16>(_val);
	}
	
	void convert(Int32& val) const
	{
		val = static_cast<Int32>(_val);
	}

	void convert(Int64& val) const
	{
		val = static_cast<Int64>(_val);
	}

	void convert(UInt8& val) const
	{
		val = static_cast<UInt8>(_val);
	}

	void convert(UInt16& val) const
	{
		val = static_cast<UInt16>(_val);
	}
	
	void convert(UInt32& val) const
	{
		val = static_cast<UInt32>(_val);
	}

	void convert(UInt64& val) const
	{
		val = static_cast<UInt64>(_val);
	}

	void convert(bool& val) const
	{
		val = (_val != 0);
	}

	void convert(float& val) const
	{
		val = static_cast<float>(_val);
	}

	void convert(double& val) const
	{
		val = static_cast<double>(_val);
	}

	void convert(char& val) const
	{
		val = static_cast<char>(_val);
	}

	void convert(std::string& val) const
	{
		val = NumberFormatter::format(_val);
	}

	DynamicAnyHolder* clone() const
	{
		return new DynamicAnyHolderImpl(_val);
	}

private:
	unsigned long _val;
};


#endif // 64bit


} // namespace Poco


#endif // Poco_DynamicAnyHolder_INCLUDED
