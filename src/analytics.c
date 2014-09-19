/*

Multi Timer v3.0

http://matthewtole.com/pebble/multi-timer/

----------------------

The MIT License (MIT)

Copyright © 2013 - 2014 Matthew Tole

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

--------------------

src/analytics.c

*/

#include <pebble.h>
#include "analytics.h"
#include "generated/appinfo.h"
#include <message-queue.h>
#include <pebble-assist.h>

time_t tiw_start;
char analytics_str[64];

void analytics_track_event(char* name, char* data) {
  mqueue_add("ANL", name, data);
}

void analytics_tiw_start(void) {
  tiw_start = time(NULL);
}

void analytics_tiw_end(char* window) {
  snprintf(analytics_str, 64, "window%c%s%cduration%c%d",
    DELIMITER_INNER,
    window,
    DELIMITER_OUTER,
    DELIMITER_INNER,
    (uint16_t) (time(NULL) - tiw_start));
  analytics_track_event("tiw", analytics_str);
}

