/*
	Copyright (C) 2013 by Pierre Talbot <ptalbot@mopong.net>
	Part of the Battle for Wesnoth Project http://www.wesnoth.org/

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY.

	See the COPYING file for more details.
*/

#include "umcd/error.hpp"

namespace umcd{

boost::array<std::string, num_error> error_category::error_messages = {{
	"The packet you sent is invalid. It could be a protocol bug and administrators have been contacted, the problem should be fixed soon.", // invalid_packet
	"The request you sent is too large. It can happens if you try to send a really large pbl file, you can claim help on IRC, and we'll find a solution." // request_header_too_large
}};

const char* error_category::name() const
{
	return "umcd";
}

std::string error_category::message(int ev) const
{
	if(ev < 0 || ev >= static_cast<int>(error_messages.size()))
		return std::string("Unknown error");
	return error_messages[ev];
}

}// namespace umcd

// UMCD Error condition factory.
boost::system::error_condition make_error_condition(umcd::error e)
{
	return boost::system::error_condition(e, umcd_category());
}

// UMCD Error code factory.
boost::system::error_code make_error_code(umcd::error e)
{
	return boost::system::error_code(e, umcd_category());
}

const boost::system::error_category& umcd_category()
{
	static const umcd::error_category umcd_category_const;
	return umcd_category_const;
}
