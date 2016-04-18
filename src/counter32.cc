
#include "counter32.h"




Nan::Persistent<v8::Function> Counter32::constructor;


Counter32::Counter32(uint32_t value) : value_(value) {
}

Counter32::~Counter32() {
}

NAN_MODULE_INIT(Counter32::Init) {
  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Counter32").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "plusOne", PlusOne);
  Nan::SetPrototypeMethod(tpl, "plus", Plus);
  Nan::SetPrototypeMethod(tpl, "getValue", GetValue);
  Nan::SetPrototypeMethod(tpl, "setValue", SetValue);

  Nan::SetAccessor(tpl->InstanceTemplate(),
    v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "value"),
    // v8::String::NewFromOneByte(v8::Isolate::GetCurrent(), (const uint8_t *)"value", v8::NewStringType::kNormal, 5),
    ValueAccessorGet,
    ValueAccessorSet);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("Counter32").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(Counter32::New) {
  if (info.IsConstructCall()) {
    uint32_t value = info[0]->IsUndefined() ? 0 : (uint32_t)(Nan::To<double>(info[0]).FromJust());
    Counter32 *obj = new Counter32(value);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = {info[0]};
    v8::Local<v8::Function> cons = Nan::New(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}


NAN_METHOD(Counter32::PlusOne) {
  Counter32* obj = Nan::ObjectWrap::Unwrap<Counter32>(info.This());
  obj->value_ += 1;
}

NAN_METHOD(Counter32::Plus) {
  Counter32* obj = Nan::ObjectWrap::Unwrap<Counter32>(info.This());
  uint32_t value = info[0]->IsUndefined() ? 1 : (uint32_t)(Nan::To<double>(info[0]).FromJust());
  obj->value_ += value;
}

NAN_METHOD(Counter32::SetValue) {
  Counter32* obj = Nan::ObjectWrap::Unwrap<Counter32>(info.This());
  uint32_t value = info[0]->IsUndefined() ? 1 : (uint32_t)(Nan::To<double>(info[0]).FromJust());
  obj->value_ = value;
}

NAN_METHOD(Counter32::GetValue) {
  Counter32* obj = Nan::ObjectWrap::Unwrap<Counter32>(info.This());
  info.GetReturnValue().Set((double)obj->value_);
}

NAN_GETTER(Counter32::ValueAccessorGet){
  Counter32* obj = Nan::ObjectWrap::Unwrap<Counter32>(info.This());
  info.GetReturnValue().Set((double)obj->value_);
}

NAN_SETTER(Counter32::ValueAccessorSet){
  Counter32* obj = Nan::ObjectWrap::Unwrap<Counter32>(info.This());
  uint32_t value2 = value->IsUndefined() ? 0 : (uint32_t)(Nan::To<double>(value).FromJust());
  obj->value_ = value2;
}


NAN_MODULE_INIT(InitAll) {
  Counter32::Init(target);
}

NODE_MODULE(NativeExtension, InitAll)
