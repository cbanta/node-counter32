
#ifndef COUNTER32_H
#define COUNTER32_H

#include <nan.h>



class Counter32 : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init);

 private:
  explicit Counter32(uint32_t value = 0);
  ~Counter32();

  static NAN_METHOD(New);
  static NAN_METHOD(PlusOne);
  static NAN_METHOD(Plus);
  static NAN_METHOD(SetValue);
  static NAN_METHOD(GetValue);

  static NAN_GETTER(ValueAccessorGet);
  static NAN_SETTER(ValueAccessorSet);

  static Nan::Persistent<v8::Function> constructor;
  uint32_t value_;
};


#endif
