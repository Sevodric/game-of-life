#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h> // usr/include/X11/Xlib.h
#include "sg.h"

static Display *sgdisplay = NULL;
static Window sgwindow;
static GC sggc;

#define SG_CHECK(cause) \
  sg_error(__func__, cause)

#define SG_CHECK_OPENABLE \
  SG_CHECK("unable to open the graphics window")

#define SG_CHECK_OPENED \
  SG_CHECK("the graphics window is not opened")

#define SG_FLUSH \
  XFlush(sgdisplay)

static void sg_error(const char *fun, const char *cause) {
  if (sgdisplay == NULL) {
    fprintf(stderr, "%s: %s.\n", fun, cause);
    exit(EXIT_FAILURE);
  }
}

void sg_open(unsigned int width, unsigned int height, unsigned long bgcolor,
    unsigned long fgcolor, const char *title) {
  sgdisplay = XOpenDisplay(NULL);
  SG_CHECK_OPENABLE;
  sgwindow = XCreateSimpleWindow(sgdisplay, DefaultRootWindow(sgdisplay),
          0, 0, width, height, 0, bgcolor, bgcolor);
  XSetWindowAttributes attr;
  attr.backing_store = Always;
  XChangeWindowAttributes(sgdisplay, sgwindow, CWBackingStore, &attr);
  XStoreName(sgdisplay, sgwindow, title);
  XSelectInput(sgdisplay, sgwindow, StructureNotifyMask | KeyPressMask);
  XMapWindow(sgdisplay, sgwindow);
  sggc = XCreateGC(sgdisplay, sgwindow, 0, NULL);
  XSetForeground(sgdisplay, sggc, fgcolor);
  XEvent event;
  do {
    XNextEvent(sgdisplay, &event);
  } while (event.type != MapNotify);
  XClearWindow(sgdisplay, sgwindow);
}

void sg_close(void) {
  SG_CHECK_OPENED;
  XFreeGC(sgdisplay, sggc);
  XDestroyWindow(sgdisplay, sgwindow);
  XCloseDisplay(sgdisplay);
  sgdisplay = NULL;
}

void sg_clear(void) {
  SG_CHECK_OPENED;
  XClearWindow(sgdisplay, sgwindow);
}

void sg_set_fgcolor(unsigned long color) {
  SG_CHECK_OPENED;
  XSetForeground(sgdisplay, sggc, color);
}

void sg_set_title(const char *title) {
  SG_CHECK_OPENED;
  XStoreName(sgdisplay, sgwindow, title);
}

void sg_draw_point(int x, int y) {
  SG_CHECK_OPENED;
  XDrawPoint(sgdisplay, sgwindow, sggc, x, y);
  SG_FLUSH;
}

void sg_draw_line(int x1, int y1, int x2, int y2) {
  SG_CHECK_OPENED;
  XDrawLine(sgdisplay, sgwindow, sggc, x1, y1, x2, y2);
  SG_FLUSH;
}

void sg_draw_rectangle(int x, int y, unsigned int width, unsigned int height) {
  SG_CHECK_OPENED;
  XDrawRectangle(sgdisplay, sgwindow, sggc, x, y, width, height);
  SG_FLUSH;
}

void sg_fill_rectangle(int x, int y, unsigned int width, unsigned int height) {
  SG_CHECK_OPENED;
  XFillRectangle(sgdisplay, sgwindow, sggc, x, y, width, height);
  SG_FLUSH;
}

int sg_key_event(void) {
  SG_CHECK_OPENED;
  SG_FLUSH;
  XEvent event;
  if (!XCheckMaskEvent(sgdisplay, -1, &event) || event.type != KeyPress) {
    return 0;
  }
  XPutBackEvent(sgdisplay, &event);
  return 1;
}

int sg_get_key(void) {
  SG_CHECK_OPENED;
  SG_FLUSH;
  XEvent event;
  do {
    XNextEvent(sgdisplay, &event);
  } while (event.type != KeyPress);
  return (int) XLookupKeysym(&event.xkey, 0);
}
