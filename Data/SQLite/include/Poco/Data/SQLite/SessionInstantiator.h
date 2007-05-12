//
// SessionInstantiator.h
//
// $Id: //poco/Main/Data/SQLite/include/Poco/Data/SQLite/SessionInstantiator.h#2 $
//
// Library: SQLite
// Package: SQLite
// Module:  SessionInstantiator
//
// Definition of the SessionInstantiator class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
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


#ifndef DataConnectors_SQLite_SessionInstantiator_INCLUDED
#define DataConnectors_SQLite_SessionInstantiator_INCLUDED


#include "Poco/Data/SQLite/SQLite.h"
#include "Poco/Data/SessionInstantiator.h"


namespace Poco {
namespace Data {
namespace SQLite {


class SQLite_API SessionInstantiator: public Poco::Data::SessionInstantiator
	/// SessionInstantiator instantiates SqLite SessionImpl objects.
{
public:
	static const std::string KEY;
		/// Keyword for creating SQLite sessions.

	SessionInstantiator();
		/// Creates the SessionInstantiator.

	~SessionInstantiator();
	/// Destroys the SessionInstantiator.

	Poco::AutoPtr<Poco::Data::SessionImpl> create(const std::string& initString);
		/// Creates a SQLite SessionImpl object and initializes it with the given initString.

	static void addToFactory();
		/// Registers the SessionInstantiator under the Keyword SessionInstantiator::KEY at the Poco::Data::SessionFactory.

	static void removeFromFactory();
		/// Unregisters the SessionInstantiator under the Keyword SessionInstantiator::KEY at the Poco::Data::SessionFactory.
};


} } } // namespace Poco::Data::SQLite


#endif // DataConnectors_SQLite_SessionInstantiator_INCLUDED