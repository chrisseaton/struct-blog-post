#include <ruby.h>
#include <math.h>
#include <time.h>

/*
VALUE magnitude(VALUE self, VALUE vector) {
  double x = NUM2DBL(rb_funcall(vector, rb_intern("x"), 0));
  double y = NUM2DBL(rb_funcall(vector, rb_intern("y"), 0));
  return DBL2NUM(sqrt(x*x + y*y));
}
*/

struct Vector {
  double x;
  double y;
};

VALUE magnitude(VALUE self, VALUE vector) {
  struct Vector *v = (struct Vector *)vector;
  double x = v->x;
  double y = v->y;
  return DBL2NUM(sqrt(x*x + y*y));
}

/*
VALUE date(VALUE self) {
  time_t seconds = time(NULL);
  struct tm *date = localtime(&seconds);
  VALUE day = rb_funcall(rb_const_get(rb_cObject, rb_intern("OpenStruct")), rb_intern("new"), 0);
  rb_funcall(day, rb_intern("year="), 1, INT2FIX(1900 + date->tm_year));
  rb_funcall(day, rb_intern("month="), 1, INT2FIX(1 + date->tm_mon));
  rb_funcall(day, rb_intern("day="), 1, INT2FIX(date->tm_mday));
  return day;
}
*/

void *malloc_special() {
  return rb_funcall(rb_const_get(rb_cObject, rb_intern("OpenStruct")), rb_intern("new"), 0);
}

struct Day {
  int year;
  int month;
  int day;
};

VALUE date(VALUE self) {
  time_t seconds = time(NULL);
  struct tm *date = localtime(&seconds);
  struct Day *day = (struct Day *)malloc_special();
  day->year = 1900 + date->tm_year;
  day->month = 1 + date->tm_mon;
  day->day = date->tm_mday;
  return day;
}

void Init_cext() {
  rb_require("ostruct");
  rb_define_module_function(rb_mKernel, "magnitude", &magnitude, 1);
  rb_define_module_function(rb_mKernel, "date", &date, 0);
}
