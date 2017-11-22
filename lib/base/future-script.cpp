/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012-2017 Icinga Development Team (https://www.icinga.com/)  *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#include "base/future.hpp"
#include "base/scriptframe.hpp"
#include "base/objectlock.hpp"
#include "base/exception.hpp"

using namespace icinga;

static Value FutureGet(void)
{
	ScriptFrame *vframe = ScriptFrame::GetCurrentFrame();
	Future::Ptr self = static_cast<Future::Ptr>(vframe->Self);

	return self->Get();
}

static Future::Ptr FutureContinueWith(const Function::Ptr& callback)
{
	ScriptFrame *vframe = ScriptFrame::GetCurrentFrame();
	Future::Ptr self = static_cast<Future::Ptr>(vframe->Self);

	return self->ContinueWith(callback);
}

Object::Ptr Future::GetPrototype(void)
{
	static Dictionary::Ptr prototype;

	if (!prototype) {
		prototype = new Dictionary();
		prototype->Set("get", new Function("Future#get", FutureGet));
		prototype->Set("continue_with", new Function("Future#continue_with", FutureContinueWith, { "callback" }));
	}

	return prototype;
}
