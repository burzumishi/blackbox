// -*- mode: C++; indent-tabs-mode: nil; c-basic-offset: 2; -*-
// WindowGroup.cpp for Blackbox - an X11 Window manager
// Copyright (c) 2001 - 2005 Sean 'Shaleh' Perry <shaleh@debian.org>
// Copyright (c) 1997 - 2000, 2002 - 2005
//         Bradley T Hughes <bhughes at trolltech.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include "WindowGroup.h"
#include "Window.h"
#include "blackbox.h"

#include <X11/Xlib.h>

#include <assert.h>


BWindowGroup::BWindowGroup(Blackbox *b, Window _group)
  : blackbox(b), group(_group)
{ blackbox->insertWindowGroup(group, this); }


BWindowGroup::~BWindowGroup(void)
{ blackbox->removeWindowGroup(group); }


void BWindowGroup::addWindow(BlackboxWindow *win)
{ windowList.push_front(win); }


void BWindowGroup::removeWindow(BlackboxWindow *win)
{
  windowList.remove(win);
  if (windowList.empty()) {
    assert(transientList.empty());
    delete this;
  }
}


void BWindowGroup::addTransient(BlackboxWindow *win) {
  assert(win->isGroupTransient());
  /*
    even though 'win' is a group transient, the group leader may be a
    managed top-level window, in which case we want the transient to
    be listed in the top-level's transient list, not here
  */
  const BlackboxWindow * const tmp = win->findTransientFor();
  assert(!tmp);
  transientList.push_front(win);
}


void BWindowGroup::removeTransient(BlackboxWindow *win) {
  assert(win->isGroupTransient());
  const BlackboxWindow * const tmp = win->findTransientFor();
  assert(!tmp);
  transientList.remove(win);
}
