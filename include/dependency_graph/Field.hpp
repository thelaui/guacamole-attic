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
			parent_( parent )
		 {};
		virtual ~Field() {};
		T value( ) const { return value_; };
		TIME_TYPE last_changed( ) const { return last_changed_; };
		void touch() { last_changed_ = TIME_FUNCTION ; };
	protected:
		Field* parent_;	
		TIME_TYPE last_changed_;
};

#endif // FIELD_HPP
