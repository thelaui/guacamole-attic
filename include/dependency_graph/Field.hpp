#ifndef FIELD_HPP
#define FIELD_HPP

#ifndef FIELD_TIME_CONFIG
#define FIELD_TIME_CONFIG

#include <boost/date_time/posix_time/posix_time.hpp>

#define TIME_FUNCTION boost::posix_time::microsec_clock::universal_time()
#define TIME_TYPE boost::posix_time::ptime

#endif // FIELD_TIME_CONFIG

class Field {
	public:
		Field( Field* parent = NULL ):
			last_checked_( TIME_FUNCTION ),
			parent_( parent )
		 {};
		virtual ~Field() {};
		TIME_TYPE last_checked( ) const { return last_checked_; };
	protected:
		Field* parent_;	
		TIME_TYPE last_checked_;
};

#endif // FIELD_HPP
